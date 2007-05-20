
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
#include "f_points_ineq.h"
#include "points.h"
#include "pnts_internal.h"
#include "vec.h"
#include "free_elements.h"
#include "grid.h"
#include "variables_tcl.h"
#include "bitvec.h"
#include "matr_diag.h"

#include "grid_user.h"

#include <float.h>
#include <algorithm>

namespace surfit {

f_points_ineq::f_points_ineq(const d_points * ipnts, bool ileq, REAL imult, const char * iprint_name) :
functional("f_points_ineq", F_CONDITION)
{
	leq = ileq;
	pnts = ipnts;
	if (pnts->getName()) {
		setNameF("f_points_ineq %s", pnts->getName());
	}
	f_sub_pnts = NULL;
	binded_grid = NULL;
	mult = imult;
	print_name = NULL;
	if (iprint_name != NULL)
		print_name = strdup(iprint_name);
	else
		print_name = strdup("points");
};

f_points_ineq::~f_points_ineq() {
	cleanup();
	if (binded_grid)
		binded_grid->release();
	if (print_name)
		free(print_name);
};

void f_points_ineq::cleanup() {
	if (f_sub_pnts)
		release_elements(f_sub_pnts->begin(), f_sub_pnts->end());
	delete f_sub_pnts;
	f_sub_pnts = NULL;
};

int f_points_ineq::this_get_data_count() const {
	return 1;
};

const data * f_points_ineq::this_get_data(int pos) const {
	if (pos == 0)
		return pnts;
	return NULL;
};

bool f_points_ineq::minimize() {

	return false;

};

bool f_points_ineq::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) 
{
	if (f_sub_pnts == NULL) {
		prepare_scattered_points(pnts, f_sub_pnts);
	}
	
	size_t points = 0;
	size_t i;
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	size_t pnts_size = pnts->size();
		
	writelog(LOG_MESSAGE,"%s inequality: (%s)", print_name, pnts->getName());
		
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

	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();

	extvec * diag = create_extvec(matrix_size);

	for (i = 0; i < (int)f_sub_pnts->size(); i++) {
		
		sub_points * sub_pnts = (*f_sub_pnts)[i];
		int num = sub_pnts->cell_number;

		if (mask_solved->get(num))
			continue;
		if (mask_undefined->get(num))
			continue;
		
		REAL cond_value = sub_pnts->value(pnts);

		if (cond_value == undef_value)
			continue;
		
		REAL x_value = (*method_X)(num);
		REAL dist = fabs(cond_value - x_value);
		
		if (leq) {
			if (x_value > cond_value) {
				mask->set_true(num);
				(*v)(num) = cond_value*mult*(dist + 1);
				(*diag)(num) = mult*(dist + 1);
				points++;
			}
		} else {
			if (x_value < cond_value) {
				mask->set_true(num);
				(*v)(num) = cond_value*mult*(dist + 1);
				(*diag)(num) = mult*(dist + 1);
				points++;
			}
		}

		
	}

	matr_diag * T = new matr_diag(diag, matrix_size, mask);
	matrix = T;
	
	bool solvable = (points > 0);

	if (points == 0) {
		delete T;
		matrix = NULL;
		if (v)
			v->release();
		v = NULL;
	}

	solvable = wrap_sums(matrix, v, mask_solved, mask_undefined) || solvable;
	return solvable;
};

void f_points_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	if (f_sub_pnts == NULL) {
		prepare_scattered_points(pnts, f_sub_pnts);
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

	unsigned int pnts_size = f_sub_pnts->size();

	unsigned int i;
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

bool f_points_ineq::solvable_without_cond(const bitvec * mask_solved,
					  const bitvec * mask_undefined,
					  const extvec * X) 
{
	return true;
	/*
	if (f_sub_pnts == NULL) {
		prepare_scattered_points(pnts, f_sub_pnts);
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

	int i;
	for (i = 0; i < (int)f_sub_pnts->size(); i++) {
		
		sub_points * sub_pnts = (*f_sub_pnts)[i];
		int num = sub_pnts->cell_number;

		if (mask_solved->get(num))
			continue;
		if (mask_undefined->get(num))
			continue;

		return false;

	}
	
	return true;
	*/
};

//
//
// f_points_ineq_user
//
//

f_points_ineq_user::f_points_ineq_user(const char * ifunctional_name, bool ileq, REAL imult) :
functional(ifunctional_name, F_USUAL)
{
	f_pnts_ineq = NULL;
	pnts = NULL;
	functional_name = ifunctional_name;
	leq = ileq;
	mult = imult;
};

f_points_ineq_user::~f_points_ineq_user() {
	cleanup();
};

void f_points_ineq_user::cleanup() {
	delete f_pnts_ineq;
	if (pnts)
		pnts->release_private();
	f_pnts_ineq = NULL;
	pnts = NULL;
};

void f_points_ineq_user::create_f_points_ineq() 
{
	if (pnts == NULL) {
		pnts = get_points();
		if (pnts == NULL)
			return;
	}

	if (f_pnts_ineq == NULL)
		f_pnts_ineq = new f_points_ineq(pnts, leq, mult, functional_name);

	if ( cond() ) { 
		if (f_pnts_ineq->cond())
			f_pnts_ineq->cond_erase_all();
		int i;
		for (i = 0; i < (int)functionals_cond->size(); i++) {
			functional * cnd = (*functionals_cond)[i];
			f_pnts_ineq->cond_add(cnd);
		}
		
	}
	if ( functionals_add->size() > 0 )
	{
		size_t i;
		for (i = 0; i < functionals_add->size(); i++) {
			functional * add = (*functionals_add)[i];
			f_pnts_ineq->add_functional(add, (*weights)[i]);
		}
	}
};

bool f_points_ineq_user::minimize() 
{
	create_f_points_ineq();
	if (f_pnts_ineq)
		return f_pnts_ineq->minimize();
	return true;
};

bool f_points_ineq_user::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) 
{
	create_f_points_ineq();
	if (f_pnts_ineq)
		return f_pnts_ineq->make_matrix_and_vector(matrix, v, mask_solved, mask_undefined);
	return false;
};

void f_points_ineq_user::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	create_f_points_ineq();
	if (f_pnts_ineq)
		f_pnts_ineq->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
};

bool f_points_ineq_user::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	return true;
};


}; // namespace surfit;

