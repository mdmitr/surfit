
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

#include "f_wmean.h"
#include "vec.h"
#include "vec_alg.h"
#include "bitvec.h"
#include "matr_onesrow.h"
#include "grid_user.h"
#include "surf.h"
#include "surf_internal.h"
#include "grid.h"
#include "grid_internal.h"

namespace surfit {

f_wmean::f_wmean(REAL imean, const d_surf * isrf, REAL imult) :
functional("f_wmean", F_CONDI) 
{
	mean = imean;
	srf = isrf;
	mult = imult;
	w_srf = NULL;
};

f_wmean::~f_wmean() {
	cleanup();
};

void f_wmean::cleanup() {
	if (w_srf)
		w_srf->release_private();
	w_srf = NULL;
};

int f_wmean::this_get_data_count() const {
	return 1;
};

const data * f_wmean::this_get_data(int pos) const {
	if (pos == 1)
		return srf;
	return NULL;
};

bool f_wmean::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	writelog(LOG_MESSAGE,"weighted mean value = %g condition", mean);

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	
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
	
	extvec * weights = create_extvec(matrix_size, 0, false); // don't fill this vector
	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();

	size_t i, j, pos;
	for (i = 0; i < NN; i++) {
		for (j = 0; j < MM; j++) {
			
			two2one(pos, i, j, NN, MM);

			if (method_mask_undefined->get(pos)) {
				(*weights)(pos) = 0;
				mask->set_true(pos);
				continue;
			}

			REAL weight = 0;
			if ((i >= aux_X_from) && (i <= aux_X_to) && (j >= aux_Y_from) && (j <= aux_Y_to)) {
				int I = i-aux_X_from;
				int J = j-aux_Y_from;
				weight = (*(w_srf->coeff))(I + J*nn);
				if (weight == w_srf->undef_value)
					weight = 0;
			}

			if (weight < 0)
				weight = 0;

			(*weights)(pos) = weight;

			denom += weight;

		}
	}

	REAL coeff = matrix_size / denom * mult;
	denom *= coeff;

	for (i = 0; i < matrix_size; i++) {

		(*weights)(i) *= coeff;

		REAL weight = (*weights)(i);
		if (weight == 0) {
			mask->set_true(i);
		}
			
		if (method_mask_undefined->get(i))
			continue;
		
		if (method_mask_solved->get(i)) {
			sum_values_solved += (*method_X)(i)*weight;
			mask->set_true(i);
		}
		
	}

	matr_row * T = new matr_row(matrix_size, mask, weights);
		
	matrix = T;

	REAL v_val = mean*denom - sum_values_solved;

	v = create_extvec(matrix_size, 0, false);
	for (i = 0; i < matrix_size; i++) {
		if ( (method_mask_solved->get(i))  || (method_mask_undefined->get(i)) )
			(*v)(i) = 0;
		else
			(*v)(i) = v_val * (*weights)(i);
	}

	bool solvable = false;

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;

};

bool f_wmean::solvable_without_cond(const bitvec * mask_solved,
				    const bitvec * mask_undefined,
				    const extvec * X)
{
	size_t matrix_size = X->size();
	size_t i;
	for (i = 0; i < matrix_size; i++) {
		if ( (!mask_solved->get(i)) && (!mask_undefined->get(i)) )
			return false;
	}
	return true;
};

void f_wmean::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	
	size_t aux_X_from, aux_X_to;
	size_t aux_Y_from, aux_Y_to;
	get_w_srf(aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	if (w_srf == NULL) {
		mark_sums(mask_solved, mask_undefined);
		return;
	}
	
	size_t matrix_size = mask_solved->size();
	size_t i;
	size_t ii, jj;

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	size_t nn = w_srf->getCountX();
	size_t mm = w_srf->getCountY();

	for (i = 0; i < matrix_size; i++) {
		if (mask_solved->get(i) == true)
			continue;
		if (mask_undefined->get(i) == true)
			continue;

		one2two(i, ii, jj, NN, MM);
		
		if ((ii >= aux_X_from) && (ii <= aux_X_to) && (jj >= aux_Y_from) && (jj <= aux_Y_to)) {
			
			size_t I = ii-aux_X_from;
			size_t J = jj-aux_Y_from;
			
			REAL weight = (*(w_srf->coeff))(I + J*nn);
			if (weight == w_srf->undef_value)
				continue;
			
			if (weight <= 0)
				continue;
			
			mask_solved->set_true(i);
			
		} 
	}

	mark_sums(mask_solved, mask_undefined);
	

};

bool f_wmean::minimize() {

	return false;
};

void f_wmean::get_w_srf(size_t & i_from, size_t & i_to, size_t & j_from, size_t & j_to) {
	
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

void f_wmean::drop_private_data() {
	if (w_srf)
		w_srf->release_private();
	w_srf = NULL;
};


}; // namespace surfit;

