
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

#include "f_trend.h"
#include "func.h"
#include "grid_line.h"
#include "vec.h"
#include "matr.h"
#include "matrD1.h"
#include "matrD2.h"
#include "solvers.h"
#include "variables_tcl.h"
#include "bitvec.h"
#include "grid.h"
#include "curv.h"
#include "func_internal.h"
#include "f_completer.h"
#include "grid_internal.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_trend::f_trend(REAL iD1, REAL iD2, const d_func * ifnc) :
functional("f_trend")
{
	fnc = ifnc;
	D1 = iD1;
	D2 = iD2;
	if (fnc->getName()) {
		setNameF("f_trend %s", fnc->getName());
	}
	tr_fnc = NULL;
};

f_trend::~f_trend() {
	if (tr_fnc)
		tr_fnc->release_private();
};

int f_trend::this_get_data_count() const {
	return 1;
};

const data * f_trend::this_get_data(int pos) const {
	if (pos == 0)
		return fnc;
	return NULL;
};

bool f_trend::minimize() {

	if (fnc->getName())
		writelog(LOG_MESSAGE,"trend (%s) : processing...",fnc->getName());
	else 
		writelog(LOG_MESSAGE,"trend : processing...");

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
				int NN = method_prev_grid->getCountX();
				int MM = method_prev_grid->getCountY();
				
				int newNN = NN;
				int newMM = MM;
				
				if (doubleX)
					newNN *= 2;
				if (doubleY)
					newMM *= 2;
				
				bitvec * saved_mask_solved = create_bitvec(method_mask_solved);
				method_mask_solved->init_false();
				
				int size = method_mask_solved->size();
				int i;
				for (i = 0; i < size; i++) {
					
					if (!check_for_node(gfaults, i)) 
						method_mask_solved->set_true(i);
					
				};
				
				minimize_step();
								
				method_mask_solved->copy(saved_mask_solved);
				if (saved_mask_solved)
					saved_mask_solved->release();
			}
			
		}

		int matrix_size = method_basis_cntX*method_basis_cntY;

		std::vector<short int> * flood_areas = new std::vector<short int>(matrix_size);
		int flood_areas_cnt = 0;

		fill_all_areas(flood_areas, method_grid, gfaults, flood_areas_cnt, method_mask_undefined);

		if ((flood_areas_cnt > 1) && (process_isolated_areas)) {
			
			writelog(LOG_MESSAGE,"trend : flood_areas_cnt = %d", flood_areas_cnt);
			writelog(LOG_MESSAGE,"trend : processing each isolated area (%d)...", flood_areas_cnt);
			
			bitvec * saved_mask_solved = create_bitvec(method_mask_solved);
			bitvec * saved_mask_undefined = create_bitvec(method_mask_undefined);
			
			int color;
			int f_size = flood_areas->size();
			
			bool undef, solved;
			
			int pos = 0;
			int exists = 0;
			
			for (color = 1; color <= flood_areas_cnt; color++) {

				writelog(LOG_MESSAGE, "trend : proccessing trend area N%d",color);
				
				method_mask_undefined->copy(saved_mask_undefined);
				method_mask_solved->copy(saved_mask_solved);
				
				for (pos = 0; pos < f_size; pos++) {
					if ( (*flood_areas)[pos] != color ) {
						method_mask_undefined->set_true(pos);
						method_mask_solved->set_false(pos);
					}
				}
				
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

		writelog(LOG_MESSAGE, "trend : proccessing whole trend area...");
		
		res = minimize_step() && res;

	}

	return true;
};

bool f_trend::make_matrix_and_vector(matr *& matrix, vec *& v) {
	
	int matrix_size = method_basis_cntX*method_basis_cntY;
	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();

	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	get_tr_fnc(aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	if (tr_fnc == NULL)
		return false;
	
	matrD1_rect * oD1 = new matrD1_rect(matrix_size, NN, 
		method_stepX, method_stepY,
		aux_X_from, aux_X_to,
		aux_Y_from, aux_Y_to,
		method_mask_solved, method_mask_undefined, 
		gfaults); 
	
	matrD2_rect * oD2 = new matrD2_rect(matrix_size, NN, 
		method_stepX, method_stepY,
		aux_X_from, aux_X_to,
		aux_Y_from, aux_Y_to,
		method_mask_solved, method_mask_undefined, 
		gfaults); 
	
	matr_sum *  T = new matr_sum(D1, oD1, D2, oD2);

	v = create_vec(matrix_size);

	int points = calcVecV(matrix_size, method_X, T, v, NN, MM, 
			      method_mask_solved, 
			      method_mask_undefined, 
			      aux_X_from, aux_X_to,
			      aux_Y_from, aux_Y_to,
			      tr_fnc);
	
	matrix = T;

	bool solvable = completer_solvable(points, D1, D2);

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;
};

void f_trend::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	int NN = method_grid->getCountX();

	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	_grid_intersect1(method_grid, fnc->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	
	int i,j,pos;
	for (j = aux_Y_from; j <= aux_Y_to; j++) {
		for (i = aux_X_from; i <= aux_X_to; i++) {
			pos = i + j*NN;
			if (!mask_undefined->get(pos))
				mask_solved->set_true(pos);
		}
	}

};

bool f_trend::minimize_step() {
	
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

bool f_trend::solvable_without_cond(const bitvec * mask_solved,
				    const bitvec * mask_undefined,
				    const vec * X)
{

	int NN = method_grid->getCountX();

	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	_grid_intersect1(method_grid, fnc->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	
	int i,j,pos;
	int cnt = 0;
	for (j = aux_Y_from; j <= aux_Y_to; j++) {
		for (i = aux_X_from; i <= aux_X_to; i++) {
			pos = i + j*NN;
			if (mask_solved->get(pos))
				cnt++;
			if (D2 == 0) {
				if (cnt == 1) {
					goto sss;
				}
			}
			if (cnt == 3) {
				goto sss;
			}
		}
	}
	
	return false;

sss:

	bool res = true;
	
	return res;

};

void f_trend::get_tr_fnc(int & i_from, int & i_to, int & j_from, int & j_to) {
	
	_grid_intersect1(method_grid, fnc->grd, i_from, i_to, j_from, j_to);
	d_grid * aux_grid = _create_sub_grid(method_grid, i_from, i_to, j_from, j_to);

	if (tr_fnc == NULL)
		tr_fnc = _func_project(fnc, aux_grid);
	else {
		if (tr_fnc->grd->operator==(aux_grid) == false) {
			tr_fnc->release();
			tr_fnc = _func_project(fnc, aux_grid);
		}
	}
	
	delete aux_grid;
};

void f_trend::drop_private_data() {
	if (tr_fnc)
		tr_fnc->release_private();
	tr_fnc = NULL;
};


}; // namespace surfit;

