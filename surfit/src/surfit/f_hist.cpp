
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

#include "f_hist.h"
#include "hist.h"
#include "hist_internal.h"
#include "vec.h"
#include "bitvec.h"
#include "intvec.h"
#include "grid_user.h"
#include "sort_alg.h"
#include "matr_diag.h"
#include "variables_internal.h"

#include <algorithm>
#include <float.h>

namespace surfit {

f_hist::f_hist(const d_hist * ihst, REAL imult, size_t itrshold) :
functional("f_hist", F_CONDITION) 
{
	hist = ihst;
	mult = imult;
	mask = NULL;
	trshold = itrshold;
};

f_hist::~f_hist() {
	cleanup();
};

void f_hist::cleanup() {
	if (mask)
		mask->release();
	mask = NULL;
};

int f_hist::this_get_data_count() const {
	return 1;
};

const data * f_hist::this_get_data(int pos) const {
	if (pos == 0)
		return hist;
	return NULL;
};

bool f_hist::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) 
{
	writelog(LOG_MESSAGE,"histogram \"%s\"", hist->getName());

	size_t matrix_size = method_basis_cntX*method_basis_cntY;

	v = _extvec_adj_hist(method_X, hist, mask_solved, mask_undefined, FLT_MAX);
	if (v == NULL) {
		return false;
	}
	extvec * diag = create_extvec(matrix_size);

	if (mask)
		mask->release();
	mask = create_bitvec(matrix_size);
	mask->init_true();

	REAL prc = (trshold-MIN(trshold,penalty_iter_counter))/REAL(trshold);

	size_t i;
	for (i = 0; i < matrix_size; i++) {
		if (mask_solved->get(i) == true) {
			(*v)(i) = 0;
			mask->set_false(i);
			continue;
		}
		if (mask_undefined->get(i) == true) {
			(*v)(i) = 0;
			mask->set_false(i);
			continue;
		}
		if ((*v)(i) == (*method_X)(i)) {
			(*v)(i) = 0;
			mask->set_false(i);
			continue;
		}
		(*diag)(i) = mult;
		REAL val1 = (*method_X)(i);
		REAL val2 = (*v)(i);
		REAL val = val1*(1-prc) + val2*prc;
		(*v)(i) = val*mult;
	}

	matr_diag * M = new matr_diag(diag, matrix_size, mask);
	matrix = M;

	bool solvable = true;
	
	solvable = wrap_sums(matrix, v, mask_solved, mask_undefined) || solvable;
	return solvable;

};

bool f_hist::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	size_t matrix_size = method_basis_cntX*method_basis_cntY;

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

void f_hist::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	set_solved(mask_solved, mask_undefined);
	mark_sums(mask_solved, mask_undefined);
};

bool f_hist::minimize() {

	return false;
};

void f_hist::drop_private_data() {
	if (mask)
		mask->release();
	mask = NULL;
};

}; // namespace surfit;

