
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

#include "f_mask_wmean.h"
#include "vec.h"
#include "bitvec.h"
#include "matr_onesrow.h"
#include "grid_user.h"
#include "mask.h"
#include "grid_line.h"
#include "grid.h"
#include "grid_internal.h"
#include "surf.h"
#include "surf_internal.h"

#include "grid_line_user.h"

namespace surfit {

f_mask_wmean::f_mask_wmean(REAL imean, const d_surf * isrf, const d_mask * imask, REAL imult) :
functional("f_mask_wmean", F_CONDI) 
{
	mean = imean;
	mask = imask;
	srf = isrf;
	mult = imult;
	if (mask->getName()) {
		setNameF("f_mask_wmean %s", mask->getName());
	}
	w_srf = NULL;
};

f_mask_wmean::~f_mask_wmean() {
	cleanup();	
};

void f_mask_wmean::cleanup() {
	if (w_srf)
		w_srf->release_private();
	w_srf = NULL;
};

int f_mask_wmean::this_get_data_count() const {
	return 2;
};

const data * f_mask_wmean::this_get_data(int pos) const {
	if (pos == 0)
		return srf;
	if (pos == 1)
		return mask;
	return NULL;
};

bool f_mask_wmean::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	writelog(LOG_MESSAGE,"mask_wmean %s value = %g condition", mask->getName(), mean);
	
	size_t aux_X_from, aux_X_to;
	size_t aux_Y_from, aux_Y_to;
	get_w_srf(aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	if (w_srf == NULL)
		return false;

	REAL denom = 0;
	REAL sum_values_solved = 0;

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	size_t nn = w_srf->getCountX();
	size_t mm = w_srf->getCountY();

	size_t matrix_size = NN*MM;
	
	extvec * weights = create_extvec(matrix_size, 0, false); // don't fill this vector
	bitvec * matr_mask = create_bitvec(matrix_size);
	matr_mask->init_false();

	size_t i;
	size_t ii, jj;
	REAL x,y;

	for (i = 0; i < matrix_size; i++) {
		
		one2two(i, ii, jj, NN, MM);
		method_grid->getCoordNode(ii, jj, x, y);

		if (mask->getValue(x,y) == false) {
			(*weights)(i) = 0;
			matr_mask->set_true(i);
			continue;
		}
		
		if (method_mask_undefined->get(i)) {
			(*weights)(i) = 0;
			matr_mask->set_true(i);
			continue;
		}
						
		REAL weight = w_srf->getValue(x,y);
		if (weight < 0)
			weight = 0;
		if (weight == w_srf->undef_value)
			weight = 0;
		
		(*weights)(i) = weight;
		
		denom += weight;

	};

	REAL coeff = matrix_size / denom * mult;
	denom *= coeff;

	for (i = 0; i < matrix_size; i++) {

		(*weights)(i) *= coeff;

		REAL weight = (*weights)(i);
		if (weight == 0) {
			matr_mask->set_true(i);
		}

		one2two(i, ii, jj, NN, MM);
		method_grid->getCoordNode(ii, jj, x, y);

		if (mask->getValue(x,y) == false)
			continue;
			
		if (method_mask_undefined->get(i))
			continue;
		
		if (method_mask_solved->get(i)) {
			sum_values_solved += (*method_X)(i)*weight;
			matr_mask->set_true(i);
		}
	}

	matr_row * T = new matr_row(matrix_size, matr_mask, weights);
	
	matrix = T;

	REAL v_val = mean*denom - sum_values_solved;

	v = create_extvec(matrix_size, 0, false);
	for (i = 0; i < matrix_size; i++) {
		
		if ( matr_mask->get(i) )
			(*v)(i) = 0;
		else
			(*v)(i) = v_val*(*weights)(i);
	}

	bool solvable = false;

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_mask_wmean::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const extvec * X)
{
	size_t i;
	size_t NN = method_basis_cntX;
	size_t MM = method_basis_cntY;
	size_t matrix_size = NN*MM;

	size_t ii, jj;
	REAL x, y;
	
	for (i = 0; i < matrix_size; i++) {

		one2two(i, ii, jj, NN, MM);
		method_grid->getCoordNode(ii, jj, x, y);
		
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

void f_mask_wmean::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
	size_t aux_X_from, aux_X_to;
	size_t aux_Y_from, aux_Y_to;
	
	get_w_srf(aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	if (w_srf == NULL)
		return;
	
	size_t i;
	size_t ii, jj;

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	size_t matrix_size = NN*MM;
	size_t nn = w_srf->getCountX();
	size_t mm = w_srf->getCountY();

	REAL x, y;
	
	for (i = 0; i < matrix_size; i++) {

		one2two(i, ii, jj, NN, MM);
		method_grid->getCoordNode(ii, jj, x, y);
		
		if (mask->getValue(x,y) == false)
			continue;
		
		if (mask_solved->get(i) == true)
			continue;
		if (mask_undefined->get(i) == true)
			continue;

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

bool f_mask_wmean::minimize() {

	return false;
};

void f_mask_wmean::get_w_srf(size_t & i_from, size_t & i_to, size_t & j_from, size_t & j_to) {
	
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

void f_mask_wmean::drop_private_data() {
	if (w_srf)
		w_srf->release_private();
	w_srf = NULL;
};

}; // namespace surfit;

