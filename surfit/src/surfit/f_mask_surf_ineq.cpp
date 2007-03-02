
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

#include "f_mask_surf_ineq.h"
#include "bitvec.h"
#include "vec.h"
#include "matr_diag.h"
#include "mask.h"
#include "grid_line.h"
#include "grid.h"
#include "surf.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_mask_surf_ineq::f_mask_surf_ineq(const d_surf * ifnc, const d_mask * imask, bool ileq, REAL imult) :
functional("f_mask_surf_ineq", F_CONDI)
{
	leq = ileq;
	mult = imult;
	mask = imask;
	fnc = ifnc;
};

f_mask_surf_ineq::~f_mask_surf_ineq() {
	cleanup();
};

void f_mask_surf_ineq::cleanup() {
};

int f_mask_surf_ineq::this_get_data_count() const {
	return 2;
};

const data * f_mask_surf_ineq::this_get_data(int pos) const {
	if (pos == 0)
		return mask;
	if (pos == 1)
		return fnc;
	return NULL;
};

bool f_mask_surf_ineq::minimize() {

	return false;

};

bool f_mask_surf_ineq::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	size_t points = 0;
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	if (leq) 
		writelog(LOG_MESSAGE,"inequality for mask (%s) leq surface", mask->getName());
	else 
		writelog(LOG_MESSAGE,"inequality for mask (%s) geq surface", mask->getName());
	
	bitvec * matr_mask = create_bitvec(matrix_size);
	matr_mask->init_false();

	extvec * diag = create_extvec(matrix_size);

	REAL x, y, value;
	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;
	size_t I, J;

	size_t i;
	for (i = 0; i < matrix_size; i++) {

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		if (mask->getValue(x,y) == false)
			continue;
		
		if (method_mask_solved->get(i))
			continue;
		if (method_mask_undefined->get(i))
			continue;

		//value = fnc->getMeanValue(x-stepX2, x+stepX2, y-stepY2, y+stepY2);
		value = fnc->getInterpValue(x, y);

		if (value == fnc->undef_value)
			continue;
		
		REAL x_value = (*method_X)(i);
		REAL dist = fabs(value - x_value);
		
		if (leq) {
			if (x_value > value) {
				matr_mask->set_true(i);
				(*v)(i) = value*mult*(dist + 1);
				(*diag)(i) = mult*(dist + 1);
				points++;
			}
		} else {
			if (x_value < value) {
				matr_mask->set_true(i);
				(*v)(i) = value*mult*(dist + 1);
				(*diag)(i) = mult*(dist + 1);
				points++;
			}
		}
		
	}

	matr_diag * T = new matr_diag(diag, matrix_size, matr_mask);
	matr_mask = NULL;
	matrix = T;

	if (points == 0) {
		delete T;
		T = NULL;
		matrix = NULL;
		if (v)
			v->release();
		v = NULL;
	}

	bool solvable = true;

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;
};

void f_mask_surf_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;
	
	size_t i;
	size_t I,J;
	REAL x,y;

	for (i = 0; i < matrix_size; i++) {

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		if (mask->getValue(x,y) == false)
			continue;
		
		if (mask_solved->get(i))
			continue;
		if (mask_undefined->get(i))
			continue;

		mask_solved->set_true(i);
		
	}

};

bool f_mask_surf_ineq::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const extvec * X)
{

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;
	
	size_t i;
	size_t I,J;
	REAL x,y;

	for (i = 0; i < matrix_size; i++) {

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		if (mask->getValue(x,y) == false)
			continue;
		
		if ( (mask_solved->get(i) == false) && 
		     (mask_undefined->get(i) == false) ) 
		{
			return false;
		}
	}

	return true;

};

void f_mask_surf_ineq::drop_private_data() {
};



}; // namespace surfit;

