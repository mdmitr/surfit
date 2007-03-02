
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

#include "f_area_mean.h"
#include "vec.h"
#include "bitvec.h"
#include "matr_onesrow.h"
#include "grid_user.h"
#include "area.h"
#include "grid_line.h"
#include "grid.h"

#include "grid_line_user.h"

namespace surfit {

f_area_mean::f_area_mean(REAL imean, const d_area * iarea, REAL imult, bool iinside) :
functional("f_area_mean", F_CONDI) 
{
	mean = imean;
	area = iarea;
	mult = imult;
	inside = iinside;

	if (area->getName()) {
		setNameF("f_area_mean %s", area->getName());
	}

	area_mask = NULL;
};

f_area_mean::~f_area_mean() {
	cleanup();
};

void f_area_mean::cleanup() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
};

int f_area_mean::this_get_data_count() const {
	return 1;
};

const data * f_area_mean::this_get_data(int pos) const {
	if (pos == 0)
		return area;
	return NULL;
};

bool f_area_mean::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	writelog(LOG_MESSAGE,"area_mean %s value = %g condition", area->getName(), mean);
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;

	get_area_mask();
	if (area_mask == NULL) 
		return false;
	
	bitvec * mask = create_bitvec(matrix_size);
	mask->init_true();

	size_t N = area_mask->true_size();
	REAL sum_values_solved = 0;

	size_t i;
	for (i = 0; i < area_mask->size(); i++) {
		if (area_mask->get(i) == false)
			continue;
		
		if (method_mask_undefined->get(i)) {
			N--;
			continue;
		}
		if ( method_mask_solved->get(i) ) {
			sum_values_solved += (*method_X)(i)*mult;
			continue;
		}
		mask->set_false(i);
	}

	matr_onesrow * T = new matr_onesrow(mult, matrix_size, mask);
	
	matrix = T;

	REAL v_val = (mean*mult)*N - sum_values_solved;

	v = create_extvec(matrix_size, 0, false);
	for (i = 0; i < matrix_size; i++) {
		if ( mask->get(i) ) 
			(*v)(i) = 0;
		else
			(*v)(i) = v_val;
	}

	bool solvable = false;

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_area_mean::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const extvec * X)
{

	get_area_mask();
			
	if (area_mask == NULL) 
		return false;
		
	size_t i;
	for (i = 0; i < (size_t)area_mask->size(); i++) {
		
		if (area_mask->get(i) == false)
			continue;
		
		if ( (mask_solved->get(i) == false) && 
		     (mask_undefined->get(i) == false) ) 
		{
			return false;
		}
	}

	return true;
};

void f_area_mean::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	get_area_mask();
	if (area_mask == NULL)
		return;
	
	size_t i;
		
	for (i = 0; i < (size_t)area_mask->size(); i++) {
	
		if (area_mask->get(i) == false)
			continue;
		
		if (mask_solved->get(i) == true)
			continue;
		if (mask_undefined->get(i) == true)
			continue;

		mask_solved->set_true(i);
		
	}
	
	return;

};

bool f_area_mean::minimize() {

	return false;
};

void f_area_mean::get_area_mask() {

	if (area_mask == NULL) {
		area_mask = nodes_in_area_mask(area, method_grid, method_mask_undefined);
		if (inside == false)
			area_mask->invert();
	} else {
		if (area_mask->size() != method_grid->getCountX()*method_grid->getCountY()) {
			if (area_mask)
				area_mask->release();
			area_mask = nodes_in_area_mask(area, method_grid, method_mask_undefined);
			if (inside == false)
				area_mask->invert();
		}
	}

};

void f_area_mean::drop_private_data() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
};

}; // namespace surfit;

