
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

#include "f_value.h"
#include "bitvec.h"
#include "vec.h"
#include "variables_tcl.h"
#include "bitvec.h"
#include "matr_eye.h"
#include "solvers.h"
#include "f_completer.h"

#include "grid_user.h"

namespace surfit {

f_value::f_value(REAL ivalue) :
functional("f_value", F_USUAL) {
	value = ivalue;
	mask = NULL;
};

f_value::~f_value() {
	cleanup();
};

void f_value::cleanup() {
	if (mask)
		mask->release();
	mask = NULL;
};

int f_value::this_get_data_count() const {
	return 0;
};

const data * f_value::this_get_data(int pos) const {
	return NULL;
};

bool f_value::minimize() {
	if ((functionals_add->size() == 0) && ( !cond() )) {
		return minimize_alone();
	} else {
		
		size_t matrix_size = method_basis_cntX*method_basis_cntY;

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

bool f_value::minimize_alone() {

	if (value != undef_value)
		writelog(LOG_MESSAGE,"fill_with : %g", value);
	else 
		writelog(LOG_MESSAGE,"fill_with : undef_value");

	int size = method_mask_solved->size();
	int i;
	for (i = 0; i < size; i++) {
		if ( !method_mask_solved->get(i) && !method_mask_undefined->get(i) ) {
			if (value != undef_value) {
				(*method_X)(i) = value;
				method_mask_solved->set_true(i);
			} else {
				method_mask_undefined->set_true(i);
			};
		}
	};

	return true;
};

bool f_value::make_matrix_and_vector(matr *& matrix, vec *& v) {

	size_t matrix_size = method_mask_solved->size();

	if (mask)
		mask->release();
	mask = create_bitvec(matrix_size);
	size_t i;

	v = create_vec(matrix_size);
	matrix = NULL;

	size_t points = 0;

	for (i = 0; i < matrix_size; i++) {
		if (method_mask_solved->get(i))
			continue;
		if (method_mask_undefined->get(i))
			continue;

		(*v)(i) = value;
		mask->set_true(i);
		points++;
	}

	if (points > 0) {
		
		matr_eye * T = new matr_eye(1, matrix_size, mask, method_mask_solved, method_mask_undefined);
		matrix = T;
		
	} else {

		if (mask)
			mask->release();
		mask = NULL;
		if (v)
			v->release();
		v = NULL;
	}
	
	return true;
};

void f_value::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	set_solved(mask_solved, mask_undefined);
	mark_sums(mask_solved, mask_undefined);

};

bool f_value::solvable_without_cond(const bitvec * mask_solved,
					 const bitvec * mask_undefined,
					 const vec * X)
{
	return true;
};


}; // namespace surfit;

