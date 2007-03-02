
/*------------------------------------------------------------------------------
 *	$Id: f_area_hist.cpp 973 2007-02-18 12:44:36Z mishadm $
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

#include "f_area_hist.h"
#include "area.h"
#include "hist.h"
#include "hist_internal.h"
#include "vec.h"
#include "bitvec.h"
#include "intvec.h"
#include "grid_user.h"
#include "sort_alg.h"
#include "matr_diag.h"
#include "f_completer.h"
#include "grid_line.h"
#include "grid.h"

#include <algorithm>
#include <float.h>

namespace surfit {

f_area_hist::f_area_hist(const d_area * iarea, const d_hist * ihst, REAL imult, bool iinside) :
functional("f_area_hist", F_CONDI) 
{
	hist = ihst;
	mult = imult;
	mask = NULL;
	area = iarea;
	inside = iinside;
	area_mask = NULL;
};

f_area_hist::~f_area_hist() {
	cleanup();
};

void f_area_hist::cleanup() {
	if (mask)
		mask->release();
	mask = NULL;
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
};

int f_area_hist::this_get_data_count() const {
	return 2;
};

const data * f_area_hist::this_get_data(int pos) const {
	if (pos == 0)
		return hist;
	if (pos == 1)
		return area;
	return NULL;
};

bool f_area_hist::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	writelog(LOG_MESSAGE,"histogram \"%s\" in area \"%s\"", 
		hist->getName(),area->getName());
	
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

	get_area_mask();

	bitvec * mask_solved_undefined = create_bitvec(method_mask_solved);
	mask_solved_undefined->OR(method_mask_undefined);
	mask_solved_undefined->OR(area_mask);
	size_t solved_or_undefined = mask_solved_undefined->true_size();

	size_t intervs = hist->size();

	d_hist * surf_area_hist = _hist_from_extvec(method_X, minz, maxz, intervs, FLT_MAX, mask_solved_undefined);

	if (surf_area_hist->get_step() == 0) {
		mask_solved_undefined->release();
		surf_area_hist->release();
		return false;
	}
	
	surf_area_hist->normalize();
	vec * T = surf_area_hist->get_cumulative_hist();

	d_hist * dest_hist = create_hist(hist);
	dest_hist->normalize();
	REAL elem = REAL(1)/matrix_size;
	REAL dest_minz = dest_hist->from();
	REAL dest_maxz = dest_hist->to();
	
	for (i = 0; i < matrix_size; i++) {
		if (area_mask->get(i) == false)
			continue;
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
	if (surf_area_hist)
		surf_area_hist->release();
	if (dest_hist)
		dest_hist->release();

	bool solvable = (points > 0);

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_area_hist::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	size_t matrix_size = method_basis_cntX*method_basis_cntY;

	get_area_mask();

	size_t i;
	for (i = 0; i < matrix_size; i++) {
		
		if (area_mask->get(i) == false)
			continue;
		if (mask_solved->get(i))
			continue;
		if (mask_undefined->get(i))
			continue;

		return false;

	}
	
	return true;
};

void f_area_hist::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
	set_solved(mask_solved, mask_undefined);
	mark_sums(mask_solved, mask_undefined);

};

bool f_area_hist::minimize() {

	return false;
};

void f_area_hist::get_area_mask() {

	if (area_mask == NULL) {
		area_mask = nodes_in_area_mask(area, method_grid, method_mask_undefined);
		if (inside == true)
			area_mask->invert();
	} else {
		if (area_mask->size() != method_grid->getCountX()*method_grid->getCountY()) {
			if (area_mask)
				area_mask->release();
			area_mask = nodes_in_area_mask(area, method_grid, method_mask_undefined);
			if (inside == true)
				area_mask->invert();
		}
	}

};

void f_area_hist::drop_private_data() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
	if (mask)
		mask->release();
	mask = NULL;
};

}; // namespace surfit;

