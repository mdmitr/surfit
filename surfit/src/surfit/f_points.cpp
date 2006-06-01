
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

#include "f_points.h"
#include "vec.h"
#include "free_elements.h"
#include "bitvec.h"
#include "variables_tcl.h"
#include "solvers.h"
#include "matr_eye.h"
#include "grid.h"
#include "pnts_internal.h"
#include "variables.h"

#include "points.h"
#include "grid_user.h"

namespace surfit {

f_points::f_points(const d_points * ipnts, const char * iprint_name) :
functional("f_points", F_USUAL)
{
	pnts = ipnts;
	if (pnts->getName()) {
		setNameF("f_points %s", pnts->getName());
	}
	f_sub_pnts = NULL;
	mask = NULL;
	binded_grid = NULL;
	print_name = NULL;
	if (iprint_name != NULL)
		print_name = strdup(iprint_name);
	else
		print_name = strdup("points");
};

f_points::~f_points() {
	cleanup();
	
	if (print_name)
		free(print_name);
};

void f_points::cleanup() {
	if (f_sub_pnts)
		release_elements(f_sub_pnts->begin(), f_sub_pnts->end());
	delete f_sub_pnts;
	f_sub_pnts = NULL;

	if (mask)
		mask->release();
	mask = NULL;

	if (binded_grid)
		binded_grid->release();
	binded_grid = NULL;
};

int f_points::this_get_data_count() const {
	return 1;
};

const data * f_points::this_get_data(int pos) const {
	if (pos == 0)
		return pnts;
	return NULL;
};

bool f_points::minimize() {

	if ((functionals_add->size() == 0) && ( !cond() )) {
		return minimize_only_points();
	} else {

		int matrix_size = method_basis_cntX*method_basis_cntY;

		matr * A = NULL;
		vec * b = NULL;
		bool solvable = make_matrix_and_vector(A,b);

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
		
	}
	return false;
};

bool f_points::make_matrix_and_vector(matr *& matrix, vec *& v) {

	if (f_sub_pnts == NULL) {
		prepare_scattered_points(pnts, f_sub_pnts);
	}
	
	int points = 0;
	int i;
	
	int matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_vec(matrix_size);

	int pnts_size = pnts->size();
		
	if (pnts->getName()) {
		writelog(LOG_MESSAGE,"%s : (%s)", print_name, pnts->getName());
	} else {
		writelog(LOG_MESSAGE,"%s : noname dataset", print_name);
	}
		
	// avoiding two-times bind_points_to_grid calling for the same grid
	if (binded_grid) {
		if (binded_grid->operator ==(method_grid) == false) {
			bind_points_to_grid(method_sub_grid, pnts, f_sub_pnts, method_grid);
			if (binded_grid)
				binded_grid->release();
			binded_grid = create_grid(method_grid);
		}
	} else {
		bind_points_to_grid(method_sub_grid, pnts, f_sub_pnts, method_grid);
		if (binded_grid)
			binded_grid = create_grid(method_grid);
	}

	if (mask)
		mask->release();
	mask = create_bitvec(matrix_size);
	mask->init_false();

	for (i = 0; i < (int)f_sub_pnts->size(); i++) {
		
		sub_points * sub_pnts = (*f_sub_pnts)[i];

		int pos = sub_pnts->cell_number;

		if ( (!method_mask_solved->get(pos)) && 
		     (!method_mask_undefined->get(pos)) ) 
		{
			REAL value = sub_pnts->value(pnts);
			(*v)(sub_pnts->cell_number) = value;
			mask->set_true(sub_pnts->cell_number);
			points++;
		}
	}

	matr_eye * T = new matr_eye(1, matrix_size, mask, method_mask_solved, method_mask_undefined);
	mask = NULL;
	matrix = T;

	bool solvable = (points > 0);

	solvable = wrap_sums(matrix, v) || solvable;
	
	return solvable;
};

bool f_points::minimize_only_points() {

	if (f_sub_pnts == NULL) {
		prepare_scattered_points(pnts, f_sub_pnts);
	}

	int pnts_size = pnts->size();
	if (pnts_size > 0) {
		if (pnts->getName()) {
			writelog(LOG_MESSAGE,"%s : (%s)", print_name, pnts->getName());
		} else {
			writelog(LOG_MESSAGE,"%s : noname dataset", print_name);
		}
		
		// avoiding two-times bind_points_to_grid calling for the same grid
		if (binded_grid) {
			if (binded_grid->operator ==(method_grid) == false) {
				bind_points_to_grid(method_sub_grid, pnts, f_sub_pnts, method_grid);
				if (binded_grid)
					binded_grid->release();
				binded_grid = create_grid(method_grid);
			}
		} else {
			bind_points_to_grid(method_sub_grid, pnts, f_sub_pnts, method_grid);
			if (binded_grid)
				binded_grid->release();
			binded_grid = create_grid(method_grid);
		}
				
		size_t i;
		int num;
		sub_points * sub_pnts;
		REAL value;

		int solved_add_size = 0;
		int undefined_add_size = 0;

		size_t pnts_size = f_sub_pnts->size();
	
		for (i = 0; i < pnts_size; i++) {
			sub_pnts = (*f_sub_pnts)[i];
			num = sub_pnts->cell_number;

			// check for existance
			if (method_mask_solved->get(num))
				continue;
			if (method_mask_undefined->get(num))
				continue;
		
			value = sub_pnts->value(pnts);

			(*method_X)(num) = value;
		
			if (value == undef_value) {
				method_mask_undefined->set_true(num);
			} else {
				method_mask_solved->set_true(num);
			}
		
		}

	}

	return true;
};

void f_points::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	if ((functionals_add->size() == 0) && ( !cond() ) && (i_am_cond == false) )
		return;

	if (f_sub_pnts == NULL) {
		prepare_scattered_points(pnts, f_sub_pnts);
	}
	
	size_t pnts_size = f_sub_pnts->size();

	size_t i;
	int num;
	sub_points * sub_pnts;
	REAL value;

	for (i = 0; i < pnts_size; i++) {
		sub_pnts = (*f_sub_pnts)[i];
		num = sub_pnts->cell_number;
		// check for existance
		if (mask_solved->get(num))
			continue;
		if (mask_undefined->get(num))
			continue;
	
		value = sub_pnts->value(pnts);
	
		if (value == undef_value) {
			mask_undefined->set_true(num);
		} else {
			mask_solved->set_true(num);
		}
	}

	mark_sums(mask_solved, mask_undefined);

};

bool f_points::solvable_without_cond(const bitvec * mask_solved,
				     const bitvec * mask_undefined,
				     const vec * X)
{
	return true;
};

}; // namespace surfit;

