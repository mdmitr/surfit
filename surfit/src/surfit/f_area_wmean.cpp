
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

#include "f_area_wmean.h"
#include "vec.h"
#include "bitvec.h"
#include "matr_onesrow.h"
#include "grid_user.h"
#include "area.h"
#include "grid_line.h"
#include "grid.h"
#include "grid_internal.h"
#include "surf.h"
#include "surf_internal.h"

#include "grid_line_user.h"

namespace surfit {

f_area_wmean::f_area_wmean(REAL imean, const d_surf * isrf, const d_area * iarea, REAL imult, bool iinside) :
functional("f_area_wmean", F_CONDI) 
{
	mean = imean;
	area = iarea;
	srf = isrf;
	mult = imult;
	inside = iinside;
	if (area->getName()) {
		setNameF("f_area_wmean %s", area->getName());
	}
	w_srf = NULL;
	area_mask = NULL;
};

f_area_wmean::~f_area_wmean() {
	cleanup();	
};

void f_area_wmean::cleanup() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
	if (w_srf)
		w_srf->release_private();
	w_srf = NULL;
};

int f_area_wmean::this_get_data_count() const {
	return 2;
};

const data * f_area_wmean::this_get_data(int pos) const {
	if (pos == 0)
		return srf;
	if (pos == 1)
		return area;
	return NULL;
};

bool f_area_wmean::make_matrix_and_vector(matr *& matrix, vec *& v) {

	if (area->getName())
		writelog(LOG_MESSAGE,"area_wmean %s value = %g condition", area->getName(), mean);
	else
		writelog(LOG_MESSAGE,"noname area_wmean value = %g condition", mean);
	
	int matrix_size = method_basis_cntX*method_basis_cntY;

	get_area_mask();
	if (area_mask == false) 
		return false;
	
	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	get_w_srf(aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	if (w_srf == NULL)
		return false;

	REAL denom = 0;
	REAL sum_values_solved = 0;

	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();
	int nn = w_srf->getCountX();
	int mm = w_srf->getCountY();
	
	vec * weights = create_vec(matrix_size); 
	bitvec * mask = create_bitvec(matrix_size);
	mask->init_true();

	int i;
	int ii, jj;
	for (i = 0; i < area_mask->size(); i++) {
		
		if (area_mask->get(i) == false)
			continue;
		
		if (method_mask_undefined->get(i)) 
			continue;
		
		one2two(i, ii, jj, NN, MM);
		
		REAL weight = 0;

		if ((ii >= aux_X_from) && (ii <= aux_X_to) && (jj >= aux_Y_from) && (jj <= aux_Y_to)) {
			int I = ii-aux_X_from;
			int J = jj-aux_Y_from;
			weight = (*(w_srf->coeff))(I + J*nn);
			if (weight == w_srf->undef_value)
				weight = 0;
		}

		if (weight < 0)
			weight = 0;
		
		(*weights)(i) = weight;
		
		denom += weight;

	};

	REAL coeff = area_mask->size() / denom * mult;
	denom *= coeff;

	for (i = 0; i < area_mask->size(); i++) {

		if (area_mask->get(i) == false)
			continue;
		
		if (method_mask_undefined->get(i))
			continue;

		(*weights)(i) *= coeff;

		REAL weight = (*weights)(i);
		if (weight == 0)
			continue;
		
		if (method_mask_solved->get(i)) {
			sum_values_solved += (*method_X)(i)*weight;
			continue;
		}
		mask->set_false(i);
	}

	matr_row * T = new matr_row(matrix_size, mask, weights);
	
	matrix = T;

	REAL v_val = mean*denom - sum_values_solved;

	v = create_vec(matrix_size, 0, false);
	for (i = 0; i < matrix_size; i++) {
		if ( mask->get(i) ) 
			(*v)(i) = 0;
		else
			(*v)(i) = v_val*(*weights)(i);
	}

	bool solvable = false;

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_area_wmean::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const vec * X)
{
	get_area_mask();
	if (area_mask == NULL)
		return false;
	
	unsigned int i;
	
	for (i = 0; i < (unsigned int)area_mask->size(); i++) {
		
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

void f_area_wmean::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
	get_area_mask();
	if (area_mask == NULL) 
		return;

	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	
	get_w_srf(aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	if (w_srf == NULL)
		return;
	
	unsigned int i;
	int ii, jj;

	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();
	int nn = w_srf->getCountX();
	int mm = w_srf->getCountY();
	
	for (i = 0; i < (unsigned int)area_mask->size(); i++) {
		
		if (area_mask->get(i) == false)
			continue;
		
		if (mask_solved->get(i) == true)
			continue;
		if (mask_undefined->get(i) == true)
			continue;

		one2two(i, ii, jj, NN, MM);
		
		if ((ii >= aux_X_from) && (ii <= aux_X_to) && (jj >= aux_Y_from) && (jj <= aux_Y_to)) {
			
			int I = ii-aux_X_from;
			int J = jj-aux_Y_from;
			
			REAL weight = (*(w_srf->coeff))(I + J*nn);
			if (weight == w_srf->undef_value)
				continue;
			
			if (weight <= 0)
				continue;
			
			mask_solved->set_true(i);
			
		} 
		
	};

	mark_sums(mask_solved, mask_undefined);
		
	return;
	
};

bool f_area_wmean::minimize() {

	return false;
};

void f_area_wmean::get_w_srf(int & i_from, int & i_to, int & j_from, int & j_to) {
	
	_grid_intersect1(method_grid, srf->grd, i_from, i_to, j_from, j_to);
	d_grid * aux_grid = _create_sub_grid(method_grid, i_from, i_to, j_from, j_to);

	if (w_srf == NULL)
		w_srf = _surf_project(srf, aux_grid);
	else {
		if (w_srf->grd->operator==(aux_grid) == false) {
			w_srf->release();
			w_srf = _surf_project(srf, aux_grid);
		}
	}
	
	if (aux_grid)
		aux_grid->release();
};

void f_area_wmean::get_area_mask() {

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

void f_area_wmean::drop_private_data() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
	if (w_srf)
		w_srf->release_private();
	w_srf = NULL;
};

}; // namespace surfit;

