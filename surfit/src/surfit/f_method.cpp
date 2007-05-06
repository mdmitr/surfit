
/*------------------------------------------------------------------------------
 *	$Id: $
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
#include "f_method.h"
#include "grid_user.h"
#include "matr.h"
#include "solvers.h"
#include "fileio.h"
#include "bitvec.h"
#include "surf.h"
#include "surf_internal.h"
#include "points.h"
#include "matr_eye.h"
#include "f_surf.h"

#include "f_completer.h"

namespace surfit {

f_method::f_method(const char * method_name) : functional(method_name, F_USUAL) 
{
	f_srf = NULL;
	method_surf = NULL;
};

f_method::~f_method()
{
	cleanup();
};

void f_method::cleanup() {
	if (method_surf)
		method_surf->release();
	method_surf = NULL;
	delete f_srf;
	f_srf = NULL;
};

int f_method::this_get_data_count() const {
	return 0;
};

const data * f_method::this_get_data(int pos) const {
	return NULL;
};

void f_method::create_f_surf() 
{
	if (method_surf == NULL)
		method_surf = get_method_surf();
	if (method_surf == NULL)
		return;

	// check for grid was enlarged
	if (method_surf != NULL) {
		if (method_surf->grd->operator ==(method_grid) == false)
		{
			method_surf->release();
			method_surf = get_method_surf();
			if (method_surf == NULL)
				return;
		}
	}

	if (f_srf) {
		if (f_srf->get_surf() != method_surf) {
			delete f_srf;
			f_srf = NULL;
		} else
			return;
	}
	f_srf = new f_surf(method_surf, get_method_name());
	
	if ( cond() ) { 
		if (f_srf->cond())
			f_srf->cond_erase_all();
		int i;
		for (i = 0; i < (int)functionals_cond->size(); i++) {
			functional * cnd = (*functionals_cond)[i];
			f_srf->cond_add(cnd);
		}
	}
};

bool f_method::minimize() 
{
	create_f_surf();
	if (f_srf == NULL)
		return false;
	return f_srf->minimize();
};

bool f_method::make_matrix_and_vector(matr *& matrix, extvec *& v) 
{
	create_f_surf();
	if (f_srf == NULL)
		return false;
	return f_srf->make_matrix_and_vector(matrix, v);
};

void f_method::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	create_f_surf();
	if (f_srf == NULL)
		return;
	f_srf->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
	mark_sums(mask_solved, mask_undefined);
};

bool f_method::solvable_without_cond(const bitvec * mask_solved,
					  const bitvec * mask_undefined,
					  const extvec * X)
{
	create_f_surf();
	if (f_srf == NULL)
		return false;
	return f_srf->solvable_without_cond(mask_solved, mask_undefined, X);
};

}; // namespace surfit;


