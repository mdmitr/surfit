
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
#include "f_completer.h"

#include <algorithm>
#include <float.h>

namespace surfit {

f_hist::f_hist(const d_hist * ihst, REAL imult) :
functional("f_hist", F_CONDI) 
{
	hist = ihst;
	mult = imult;
	mask = NULL;
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

bool f_hist::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	writelog(LOG_MESSAGE,"histogram \"%s\"", 
		hist->getName()?hist->getName():"noname");
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;

	REAL minz = FLT_MAX, maxz = -FLT_MAX;
	size_t i;
	for (i = 0; i < matrix_size; i++) {
		
		if (method_mask_solved->get(i))
			continue;
		if (method_mask_undefined->get(i))
			continue;

		REAL val = (*method_X)(i);
		if (val == FLT_MAX)
			continue;
		minz = MIN(minz, val);
		maxz = MAX(maxz, val);
	}

	if ((minz == FLT_MAX) || (maxz == -FLT_MAX))
		return false;

	if (mask)
		mask->release();
	mask = create_bitvec(matrix_size);
	mask->init_true();

	bitvec * mask_solved_undefined = create_bitvec(method_mask_solved);
	mask_solved_undefined->OR(method_mask_undefined);
	size_t solved_or_undefined = mask_solved_undefined->true_size();

	size_t intervs = hist->size();

	d_hist * surf_hist = _hist_from_extvec(method_X, minz, maxz, intervs, FLT_MAX, mask_solved_undefined);

	if (surf_hist->get_step() == 0) {
		mask_solved_undefined->release();
		surf_hist->release();
		return false;
	}
	
	surf_hist->normalize();
	vec * T = surf_hist->get_cumulative_hist();

	d_hist * dest_hist = create_hist(hist);
	dest_hist->normalize();
	REAL elem = REAL(1)/matrix_size;
	REAL dest_minz = dest_hist->from();
	REAL dest_maxz = dest_hist->to();
	
	for (i = 0; i < matrix_size; i++) {
		if (method_mask_solved->get(i) == false)
			continue;
		
		REAL val = (*method_X)(i);

		if (val > dest_maxz)
			continue;
		if (val < dest_minz)
			continue;

		size_t pos = (*dest_hist)(val);
		
		(*dest_hist)[pos] = MAX(0, (*dest_hist)(pos)-elem);
	}

	dest_hist->normalize();

	vec * Z = dest_hist->get_cumulative_hist();

	size_t points = 0;

	v = create_extvec(matrix_size);
	extvec * diag = create_extvec(matrix_size);

	for (i = 0; i < matrix_size; i++) {
		if (mask_solved_undefined->get(i) == true) {
			mask->set_false(i);
			continue;
		}
		REAL val = (*method_X)(i);
		REAL eqval = get_eq_value(T, Z, val,
					  minz, maxz,
					  dest_minz, dest_maxz);

		if (val != eqval) {
			REAL dist = fabs(eqval - val);
			(*v)(i) = eqval*mult;
			(*diag)(i) = mult;
			points++;
		}
	}

	mask_solved_undefined->release();

	matr_diag * M = new matr_diag(diag, matrix_size, mask);
	matrix = M;
	
	if (points == 0) {
		delete M;
		M = NULL;
		matrix = NULL;
		if (v)
			v->release();
		v = NULL;
	}
	
	if (T)
		T->release();
	if (Z)
		Z->release();
	if (surf_hist)
		surf_hist->release();
	if (dest_hist)
		dest_hist->release();

	bool solvable = (points > 0);

	solvable = wrap_sums(matrix, v) || solvable;
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

void f_hist::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
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

