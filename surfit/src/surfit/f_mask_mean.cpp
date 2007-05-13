
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

#include "f_mask_mean.h"
#include "vec.h"
#include "bitvec.h"
#include "matr_onesrow.h"
#include "grid_user.h"
#include "mask.h"
#include "grid_line.h"
#include "grid.h"

#include "grid_line_user.h"

namespace surfit {

f_mask_mean::f_mask_mean(REAL imean, const d_mask * imask, REAL imult) :
functional("f_mask_mean", F_CONDITION) 
{
	mean = imean;
	mask = imask;
	mult = imult;
	
	if (mask->getName()) {
		setNameF("f_mask_mean %s", mask->getName());
	}

};

f_mask_mean::~f_mask_mean() {
	cleanup();
};

void f_mask_mean::cleanup() {
};

int f_mask_mean::this_get_data_count() const {
	return 1;
};

const data * f_mask_mean::this_get_data(int pos) const {
	if (pos == 0)
		return mask;
	return NULL;
};

bool f_mask_mean::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) 
{
	writelog(LOG_MESSAGE,"mask_mean %s value = %g condition", mask->getName(), mean);
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;

	bitvec * matr_mask = create_bitvec(matrix_size);
	matr_mask->init_true();

	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;

	size_t N = 0;
	REAL sum_values_solved = 0;
	size_t I, J;
	REAL x,y;

	size_t i;
	for (i = 0; i < matrix_size; i++) {

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		if (mask->getValue(x,y) == false)
			continue;
		else
			N++;
		
		if (mask_undefined->get(i)) {
			N--;
			continue;
		}
		if (mask_solved->get(i) ) {
			sum_values_solved += (*method_X)(i)*mult;
			continue;
		}
		matr_mask->set_false(i);
	}

	matr_onesrow * T = new matr_onesrow(mult, matrix_size, matr_mask);
	
	matrix = T;

	REAL v_val = (mean*mult)*N - sum_values_solved;

	v = create_extvec(matrix_size, 0, false);
	for (i = 0; i < matrix_size; i++) {
		if ( matr_mask->get(i) ) 
			(*v)(i) = 0;
		else
			(*v)(i) = v_val;
	}

	bool solvable = false;

	solvable = wrap_sums(matrix, v, mask_solved, mask_undefined) || solvable;
	return solvable;

};

bool f_mask_mean::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const extvec * X)
{

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;
	size_t I, J;
	REAL x, y;
	size_t i;
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

void f_mask_mean::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;
	size_t I, J;
	REAL x, y;
	size_t i;
		
	for (i = 0; i < matrix_size; i++) {

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);
	
		if (mask->getValue(x,y) == false)
			continue;
		
		if (mask_solved->get(i) == true)
			continue;
		if (mask_undefined->get(i) == true)
			continue;

		mask_solved->set_true(i);
		
	}
	
	mark_sums(mask_solved, mask_undefined);
	return;
};

bool f_mask_mean::minimize() {

	return false;
};

void f_mask_mean::drop_private_data() {
};

}; // namespace surfit;

