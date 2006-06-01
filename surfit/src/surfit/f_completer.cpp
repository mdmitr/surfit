
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
 *	See COPYING file for copying and redistribution conditions.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; version 2 of the License.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	Contact info: surfit.sourceforge.net
 *----------------------------------------------------------------------------*/

#include "surfit_ie.h"

#include "fileio.h"

#include "f_completer.h"
#include "bitvec.h"
#include "matr.h"
#include "vec.h"
#include "solvers.h"
#include "variables_tcl.h"
#include "grid.h"
#include "matrD1.h"
#include "matrD2.h"
#include "curv.h"
#include "grid_line.h"
#include "surf.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_completer::f_completer(REAL iD1, REAL iD2) :
faultable("f_completer", F_USUAL|F_FAULT)
{
	D1 = iD1;
	D2 = iD2;
};

f_completer::~f_completer() {
};

int f_completer::this_get_data_count() const {
	return 0;
};

const data * f_completer::this_get_data(int pos) const {
	return NULL;
};

bool f_completer::make_matrix_and_vector(matr *& matrix, vec *& v) {

	int matrix_size = method_basis_cntX*method_basis_cntY;
	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();

	matrD1 * oD1 = new matrD1(matrix_size, NN, 
		method_stepX, method_stepY,
		method_mask_solved, method_mask_undefined, 
		gfaults); 
	
	matrD2 * oD2 = new matrD2(matrix_size, NN, 
		method_stepX, method_stepY,
		method_mask_solved, method_mask_undefined, 
		gfaults); 
	
	matr_sum *  T = new matr_sum(D1, oD1, D2, oD2);

	v = create_vec(matrix_size);

	size_t points = calcVecV(matrix_size, method_X, T, v, NN, MM, method_mask_solved, method_mask_undefined);

	matrix = T;

	bool solvable = completer_solvable(points, D1, D2);

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_completer::minimize_step() {

	matr * A = NULL;
	vec * b = NULL;
	bool solvable = make_matrix_and_vector(A,b);

	int matrix_size = method_basis_cntX*method_basis_cntY;

	if ( !cond() ) {
		if (solvable == false) {
			delete A;
			if (b)
				b->release();
			return false;
		}
		
		method_X->resize(b->size());
		solve(A,b,method_X);
		method_X->resize(matrix_size);
		
		delete A;
		if (b)
			b->release();
		
		return true;
	} else {
		return solve_with_penalties(this, A, b, method_X);
	}
	return false;
};

bool f_completer::minimize() {

	writelog(LOG_MESSAGE,"completer : processing...");

	bool res = true;

	if (gfaults)
		gfaults->release();
	gfaults = NULL;
	if (faults->size() > 0) {
		int q;
		for (q = 0; q < (int)faults->size(); q++) {

			const d_curv * flt = (*faults)[q];

			if (flt->getName())
				writelog(LOG_MESSAGE,"          : fault %s", flt->getName());
			else
				writelog(LOG_MESSAGE,"          : fault (noname)");
		
			gfaults = curv_to_grid_line(gfaults, flt, method_grid);
		};
	};

	if ( cond() ) {

		res = minimize_step() && res;

	} else { // use some optimizations

		if (reproject_faults && gfaults) {
			if (method_prev_grid != NULL) {
				
				bitvec * saved_mask_solved = create_bitvec(method_mask_solved);
				method_mask_solved->init_false();
				
				int size = method_mask_solved->size();
				int i;
				for (i = 0; i < size; i++) {
					
					if (!check_for_node(gfaults, i)) 
						method_mask_solved->set_true(i);
					
				};
				
				// res = minimize_step() && res;
				minimize_step();
								
				method_mask_solved->copy(saved_mask_solved);
				if (saved_mask_solved)
					saved_mask_solved->release();
			}
			
		}

		if (reproject_undef_areas) {
			if (method_prev_grid != NULL) {
				writelog(LOG_MESSAGE,"reprojecting with undef areas...");
											
				grid_line * undef_grd_line = trace_undef_grd_line(method_mask_undefined, method_grid->getCountX());
				if (undef_grd_line) {
					
					bitvec * saved_mask_solved = create_bitvec(method_mask_solved);
					int size = method_mask_solved->size();
					int i;
					
					for (i = 0; i < size; i++) {
						if (!check_for_node(undef_grd_line, i)) 
							method_mask_solved->set_true(i);
					};
					
					//res = minimize_step() && res;
					minimize_step();
					
					undef_grd_line->release();
					method_mask_solved->copy(saved_mask_solved);
					if (saved_mask_solved)
						saved_mask_solved->release();
					
				}

			}
		}

		int matrix_size = method_basis_cntX*method_basis_cntY;

		std::vector<short int> * flood_areas = new std::vector<short int>(matrix_size);
		int flood_areas_cnt = 0;

		fill_all_areas(flood_areas, method_grid, gfaults, flood_areas_cnt, method_mask_undefined);

		if ((flood_areas_cnt > 1) && (process_isolated_areas)) {
			
			writelog(LOG_MESSAGE,"completer : flood_areas_cnt = %d", flood_areas_cnt);
			writelog(LOG_MESSAGE,"completer : processing each isolated area (%d)...", flood_areas_cnt);
			
			bitvec * saved_mask_solved = create_bitvec(method_mask_solved);
			bitvec * saved_mask_undefined = create_bitvec(method_mask_undefined);
			
			int color;
			int f_size = flood_areas->size();
			
			bool undef, solved;
			
			int pos = 0;
			int exists = 0;
			
			for (color = 1; color <= flood_areas_cnt; color++) {

				writelog(LOG_MESSAGE,"completer : isolated area N%d", color);
				
				method_mask_undefined->copy(saved_mask_undefined);
				method_mask_solved->copy(saved_mask_solved);
				
				for (pos = 0; pos < f_size; pos++) {
					if ( (*flood_areas)[pos] != color ) {
						method_mask_undefined->set_true(pos);
						method_mask_solved->set_false(pos);
					}
				}
				
				//res = minimize_step() && res;
				minimize_step();
				
				for (pos = 0; pos < f_size; pos++) {
					if ( (*flood_areas)[pos] == color ) {
						
						undef = method_mask_undefined->get(pos);
						if (undef)
							saved_mask_undefined->set_true(pos);
						else 
							saved_mask_undefined->set_false(pos);
						
						solved = method_mask_solved->get(pos);	
						if (solved)
							saved_mask_solved->set_true(pos);
						else
							saved_mask_solved->set_false(pos);
						
					}
				}
				
			};
			
			method_mask_solved->copy(saved_mask_solved);
			method_mask_undefined->copy(saved_mask_undefined);
			
			if (saved_mask_solved)
				saved_mask_solved->release();
			if (saved_mask_undefined)
				saved_mask_undefined->release();
			
		}

		delete flood_areas;
		
		writelog(LOG_MESSAGE,"completer : processing whole area");
		res = minimize_step() && res;

	}

	return res;
};

void f_completer::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
	set_solved(mask_solved, mask_undefined);
	mark_sums(mask_solved, mask_undefined);

};

bool f_completer::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const vec * X)
{
	int matrix_size = method_basis_cntX*method_basis_cntY;
	int i, cnt = 0;
	for (i = 0; i < matrix_size; i++) {
		if (mask_solved->get(i))
			cnt++;
		if (D2 == 0) {
			if (cnt == 1)
				goto sss;
		}
		if (cnt == 3)
			goto sss;

	};
	return false;

sss:
	return true;
};

size_t calcVecV(size_t size, 
	     vec * X,
	     matr * T, 
	     vec *& res,
	     size_t NN, size_t MM,
	     const bitvec * mask_solved,
	     const bitvec * mask_undefined,
	     size_t x_from, size_t x_to,
	     size_t y_from, size_t y_to,
	     d_surf * trend) 
{
	int points = 0;

	if (!res)
		res = create_vec(size);

	size_t i,j;
	size_t pos, pos_x, pos_y;
	REAL val, mult;

	bool use_rect = ( (x_from != UINT_MAX) && (x_to != UINT_MAX) && (y_from != UINT_MAX) && (y_to != UINT_MAX) );
	size_t nn = NN;
	if (use_rect) {
		nn = x_to - x_from + 1;
	}

	pos_x = UINT_MAX;
	pos_y = UINT_MAX;

	for (pos = 0; pos < mask_solved->size(); pos++) {

		size_t local_pos = pos;

		if (use_rect) {

			pos_x = pos % NN;
			pos_y = (pos - pos_x)/NN;

			if  (!( (pos_x >= x_from) && (pos_x <= x_to) && (pos_y >= y_from) && (pos_y <= y_to) ))
				continue;
			local_pos = pos_x-x_from + (pos_y-y_from)*nn;

		}

		if (trend) {
			
			REAL trend_val = (*(trend->coeff))(local_pos);
			if (trend_val != undef_value) {
				for (j = 0; j < T->rows();) {
					size_t prev_j = j;
					mult = T->element_at(pos,j,&j);
					if (trend && (mult != 0)) {
						(*res)(prev_j) += mult*trend_val;
					}
				}
			}

		}

		if (!mask_solved->get(pos))
			continue;

		val = (*X)(pos);

		for (j = 0; j < T->rows();) {
			int prev_j = j;
			mult = T->element_at(pos,j,&j);
			(*res)(prev_j) -= val*mult;
		}

		
	}
	
	for (i = 0; i < mask_solved->size(); i++) {
		if (mask_solved->get(i)) {
			(*res)(i) = 0;
			points++;
		}
	}

	if (use_rect) {
		size_t n,m;
		for (m = 0; m < MM; m++) {
			for (n = 0; n < NN; n++) {
				if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
					(*res)(n + m*NN) = 0;
			}
		}
	}

	return points;
};

bool completer_solvable(int points, REAL D1, REAL D2) {
	if (D1 != 0)
		return (points > 0);
	return (points > 2);
};

void set_solved(bitvec * mask_solved, bitvec * mask_undefined) {
	int N = mask_solved->size();
	int i;
	for (i = 0; i < N; i++) {
		if (!mask_undefined->get(i))
			mask_solved->set_true(i);
	}
};

}; // namespace surfit;

