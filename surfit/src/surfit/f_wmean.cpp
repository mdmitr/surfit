
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
functional("f_wmean") 
{
	mean = imean;
	srf = isrf;
	mult = imult;
	w_srf = NULL;
};

f_wmean::~f_wmean() {
	if (w_srf)
		w_srf->release_private();
};

int f_wmean::this_get_data_count() const {
	return 1;
};

const data * f_wmean::this_get_data(int pos) const {
	if (pos == 1)
		return srf;
	return NULL;
};

bool f_wmean::make_matrix_and_vector(matr *& matrix, vec *& v) {

	writelog(LOG_MESSAGE,"weighted mean value = %g condition", mean);

	int matrix_size = method_basis_cntX*method_basis_cntY;
	
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
	
	vec * weights = create_vec(matrix_size, 0, false); // don't fill this vector
	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();

	int i, j, pos;
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

	v = create_vec(matrix_size, 0, false);
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
				    const vec * X)
{
	int matrix_size = X->size();
	int i;
	for (i = 0; i < matrix_size; i++) {
		if ( (!mask_solved->get(i)) || (!mask_undefined->get(i)) )
			return false;
	}
	return true;
};

void f_wmean::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	

	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	get_w_srf(aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	if (w_srf == NULL) {
		mark_sums(mask_solved, mask_undefined);
		return;
	}
	
	int matrix_size = mask_solved->size();
	int i;
	int ii, jj;

	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();
	int nn = w_srf->getCountX();
	int mm = w_srf->getCountY();

	for (i = 0; i < matrix_size; i++) {
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
	}

	mark_sums(mask_solved, mask_undefined);
	

};

bool f_wmean::minimize() {

	return false;
};

void f_wmean::get_w_srf(int & i_from, int & i_to, int & j_from, int & j_to) {
	
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
	
	delete aux_grid;
};

void f_wmean::drop_private_data() {
	if (w_srf)
		w_srf->release_private();
	w_srf = NULL;
};


}; // namespace surfit;

