
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

#include "flow_ie.h"

#include "fileio.h"

#include "f_lcm_simple.h"
#include "free_elements.h"
#include "matrD1.h"
#include "vec.h"
#include "shortvec.h"
#include "bitvec.h"
#include "grid.h"
#include "curv.h"
#include "grid_line.h"
#include "variables_tcl.h"
#include "solvers.h"
#include "f_completer.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_lcm_simple::f_lcm_simple(REAL ipermeability, REAL iviscosity, REAL imultiplier) :
faultable("f_lcm_simple", F_USUAL|F_FAULT) 
{
	permeability = ipermeability;
	viscosity = iviscosity;
	multiplier = imultiplier;
	flows = new std::vector<functional *>;
};

f_lcm_simple::~f_lcm_simple() {
	cleanup();
};

void f_lcm_simple::cleanup() {
	if (flows) {
		release_elements(flows->begin(), flows->end());
		delete flows;
	}
	flows = NULL;
};

int f_lcm_simple::this_get_data_count() const {
	return 0;
};

const data * f_lcm_simple::this_get_data(int pos) const {
	return NULL;
};

void f_lcm_simple::add_flow(functional * fnc) {
	flows->push_back(fnc);
};

bool f_lcm_simple::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();

	matrD1 * oD1 = new matrD1(matrix_size, NN, 
		method_stepX, method_stepY,
		method_mask_solved, method_mask_undefined, 
		gfaults); 
	
	v = create_extvec(matrix_size);

	size_t points = calcVecV(matrix_size, method_X, oD1, v, NN, MM, method_mask_solved, method_mask_undefined);

	size_t i;
	for (i = 0; i < flows->size(); i++) {
		functional * ff = (*flows)[i];
		if (!ff)
			continue;
		matr * T = NULL;
		extvec * V = NULL;
		if (!ff->make_matrix_and_vector(T, V)) {
			delete T;
			if (V)
				V->release();
			continue;
		}
		delete T;
		if (V == NULL)
			continue;
		size_t j;
		REAL prod_val;

		REAL mult = REAL(1)/(permeability/viscosity*multiplier);
		for (j = 0; j < V->size(); j++) {
			prod_val = (*V)(j);
			if (prod_val != 0)
				points++;
			else 
				continue;
			(*v)(j) += mult*prod_val;
		}
		if (V)
			V->release();
	};

	matrix = oD1;

	bool solvable = completer_solvable(points, 1, 0);

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_lcm_simple::minimize_step() {

	matr * A = NULL;
	extvec * b = NULL;
	bool solvable = make_matrix_and_vector(A,b);

	size_t matrix_size = method_basis_cntX*method_basis_cntY;

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

bool f_lcm_simple::minimize() {

	writelog(LOG_MESSAGE,"lcm_simple : processing...");

	bool res = true;

	if (gfaults)
		gfaults->release();

	gfaults = NULL;
	if (faults->size() > 0) {
		int q;
		for (q = 0; q < (int)faults->size(); q++) {

			const d_curv * flt = (*faults)[q];
			writelog(LOG_MESSAGE,"           : fault %s", flt->getName());
			gfaults = curv_to_grid_line(gfaults, flt, method_grid);
		};
	};

	if ( cond() ) {

		res = minimize_step() && res;

	} else { // use some optimizations

		if (reproject_faults && gfaults) {
			if (method_prev_grid != NULL) {
				writelog(LOG_MESSAGE,"reprojecting with faults...");
				
				bitvec * saved_mask_solved = create_bitvec(method_mask_solved);
				method_mask_solved->init_false();
				
				int size = method_mask_solved->size();
				int i;
				for (i = 0; i < size; i++) {
					
					if (!gfaults->check_for_node(i)) 
						method_mask_solved->set_true(i);
					
				};
				
				res = minimize_step() && res;

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
						if (!undef_grd_line->check_for_node(i)) 
							method_mask_solved->set_true(i);
					};
					
					res = minimize_step() && res;
					
					undef_grd_line->release();
					method_mask_solved->copy(saved_mask_solved);
					if (saved_mask_solved)
						saved_mask_solved->release();
					
				}

			}
		}

		size_t matrix_size = method_basis_cntX*method_basis_cntY;

		shortvec * flood_areas = create_shortvec(matrix_size);
		int flood_areas_cnt = 0;

		fill_all_areas(flood_areas, method_grid, gfaults, flood_areas_cnt, method_mask_undefined);

		if ((flood_areas_cnt > 1) && (process_isolated_areas)) {
			
			writelog(LOG_MESSAGE,"flood_areas_cnt = %d", flood_areas_cnt);
			writelog(LOG_MESSAGE,"processing each isolated area (%d)...", flood_areas_cnt);
			
			bitvec * saved_mask_solved = create_bitvec(method_mask_solved);
			bitvec * saved_mask_undefined = create_bitvec(method_mask_undefined);
			
			int color;
			size_t f_size = flood_areas->size();
			
			bool undef, solved;
			
			size_t pos = 0;
			int exists = 0;
			
			for (color = 1; color <= flood_areas_cnt; color++) {
				
				method_mask_undefined->copy(saved_mask_undefined);
				method_mask_solved->copy(saved_mask_solved);
				
				for (pos = 0; pos < f_size; pos++) {
					if ( (*flood_areas)(pos) != color ) {
						method_mask_undefined->set_true(pos);
						method_mask_solved->set_false(pos);
					}
				}
				
				res = minimize_step() && res;
				
				for (pos = 0; pos < f_size; pos++) {
					if ( (*flood_areas)(pos) == color ) {
						
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

		if (flood_areas)
			flood_areas->release();
		
		writelog(LOG_MESSAGE,"processing whole grid...");
		res = minimize_step(); // && res;

	}

	return res;
};

void f_lcm_simple::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
	set_solved(mask_solved, mask_undefined);
	mark_sums(mask_solved, mask_undefined);

};

bool f_lcm_simple::solvable_without_cond(const bitvec * mask_solved,
					 const bitvec * mask_undefined,
					 const extvec * X)
{
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	size_t i, cnt = 0;
	for (i = 0; i < matrix_size; i++) {
		if (mask_solved->get(i)) {
			cnt++;
			if (cnt == 1)
				goto sss;
		}
	};
	return false;

sss:
	bool res = true;

	if ( cond() )
		res = cond_solvable(mask_solved, mask_undefined, X) && res;
	
	return res;
};

}; // namespace surfit;

