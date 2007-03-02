
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
#include "f_mask_surf.h"
#include "mask.h"
#include "grid.h"
#include "surf.h"
#include "vec.h"
#include "matr.h"
#include "matr_eye.h"
#include "solvers.h"
#include "variables_tcl.h"
#include "bitvec.h"
#include "grid_line.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_mask_surf::f_mask_surf(const d_surf * isurf, const d_mask * imask) :
functional("f_mask_surf", F_USUAL)
{
	mask = imask;
	srf = isurf;
	if (mask->getName()) {
		setNameF("f_mask_surf %s", mask->getName());
	}
};

f_mask_surf::~f_mask_surf() {
	cleanup();
};

void f_mask_surf::cleanup() {
};

int f_mask_surf::this_get_data_count() const {
	return 2;
};

const data * f_mask_surf::this_get_data(int pos) const {
	if (pos == 0)
		return mask;
	if (pos == 1)
		return srf;
	return NULL;
};

bool f_mask_surf::minimize() {
	if (((functionals_add->size() == 0) && ( !cond() )) ) {
		return minimize_only_mask_surf();
	} else {
		
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

	}
	return false;
};

bool f_mask_surf::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	writelog(LOG_MESSAGE,"mask_surf (%s+%s)", mask->getName(), srf->getName());

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	size_t i, I, J;
	size_t points = 0;
	REAL x,y,z;
	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();

	bitvec * matr_mask = create_bitvec(matrix_size);
	matr_mask->init_false();

	for (i = 0; i < matrix_size; i++) {

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		if (mask->getValue(x,y) == false) 
			continue;
				
		if ( (method_mask_solved->get(i)) ) {
			matr_mask->set_true(i);
			continue;
		}

		if ( (method_mask_undefined->get(i)) ) {
			matr_mask->set_true(i);
			continue;
		}
		
		z = srf->getInterpValue(x,y);
		if (z == srf->undef_value)
			continue;
		
		(*v)(i) = z;
		points++;
		matr_mask->set_true(i);
	
	}

	matr_eye * T = new matr_eye(1, matrix_size, matr_mask, method_mask_solved, method_mask_undefined);
	matrix = T;

	bool solvable = (points > 0);

	solvable = wrap_sums(matrix, v) || solvable;
	
	return solvable;
};

void f_mask_surf::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	if ((functionals_add->size() == 0) && ( !cond() ) && (i_am_cond == false) )
		return;	

	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;
	size_t matrix_size = NN*MM;

	size_t i;
	size_t I,J;
	REAL x,y;
		
	for (i = 0; i < (size_t)matrix_size; i++) {
	
		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		if (mask->getValue(x,y) == false)
			continue;
		if ( (mask_solved->get(i) == false) && (mask_undefined->get(i) == false) ) {
			mask_solved->set_true(i);
		}
	}

	mark_sums(mask_solved, mask_undefined);
	
};

bool f_mask_surf::minimize_only_mask_surf() {
	
	writelog(LOG_MESSAGE,"mask_surf (%s+%s)", mask->getName(), srf->getName());

	size_t i;
	size_t I, J;
	size_t NN, MM;
	REAL x, y, z;
	NN = method_grid->getCountX();
	MM = method_grid->getCountY();
	size_t matrix_size = NN*MM;
	
	for (i = 0; i < matrix_size; i++) {

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		if (mask->getValue(x,y) == false)
			continue;
		if ( (method_mask_solved->get(i) == false) && (method_mask_undefined->get(i) == false) ) 
		{
			z = srf->getInterpValue(x,y);
			if (z == srf->undef_value)
				continue;

			method_mask_solved->set_true(i);
			(*method_X)(i) = z;
		}
	}
	
	return true;
};

bool f_mask_surf::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	return true;
};

void f_mask_surf::drop_private_data() {
};


}; // namespace surfit;

