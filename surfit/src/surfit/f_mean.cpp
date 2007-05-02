
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

#include "f_mean.h"
#include "vec.h"
#include "bitvec.h"
#include "matr_onesrow.h"
#include "grid_user.h"
#include "f_completer.h"

namespace surfit {

f_mean::f_mean(REAL imean, REAL imult) :
functional("f_mean", F_CONDITION) 
{
	mean = imean;
	mult = imult;
};

f_mean::~f_mean() {};

int f_mean::this_get_data_count() const {
	return 0;
};

const data * f_mean::this_get_data(int pos) const {
	return NULL;
};

bool f_mean::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	writelog(LOG_MESSAGE,"mean value = %g condition", mean);

	bitvec * mask = create_bitvec(method_mask_solved);
	mask->OR(method_mask_undefined);
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	matr_onesrow * T = new matr_onesrow(mult, matrix_size, mask);

	size_t N = matrix_size;
	REAL sum_values_solved = 0;

	size_t i;
	for (i = 0; i < matrix_size; i++) {
		if (method_mask_undefined->get(i)) {
			N--;
			continue;
		}
		
		if (method_mask_solved->get(i)) 
			sum_values_solved += (*method_X)(i)*mult;
		
	}
	
	matrix = T;

	REAL v_val = (mean*mult)*N - sum_values_solved;

	v = create_extvec(matrix_size, 0, false);
	for (i = 0; i < matrix_size; i++) {
		if ( (method_mask_solved->get(i))  || (method_mask_undefined->get(i)) )
			(*v)(i) = 0;
		else
			(*v)(i) = v_val;
	}

	bool solvable = false;

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_mean::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X) 
{
	size_t matrix_size = X->size();
	size_t i;
	for (i = 0; i < matrix_size; i++) {
		if (mask_solved->get(i))
			continue;
		if (mask_undefined->get(i))
			continue;
		
		return false;
	}
	return true;
};

void f_mean::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
	set_solved(mask_solved, mask_undefined);
	mark_sums(mask_solved, mask_undefined);

};

bool f_mean::minimize() {

	return false;
};

}; // namespace surfit;

