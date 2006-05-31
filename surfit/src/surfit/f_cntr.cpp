
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
#include "f_cntr.h"
#include "f_points.h"
#include "points.h"
#include "grid.h"
#include "cntr.h"

#include "grid_user.h"

namespace surfit {

f_cntr::f_cntr(const d_cntr * icontour) :
functional("f_cntr", F_USUAL)
{
	contour = icontour;
	if (contour->getName()) {
		setNameF("f_cntr %s", contour->getName());
	}
	f_pnts = NULL;
	pnts = NULL;
};

f_cntr::~f_cntr() {
	cleanup();
};

void f_cntr::cleanup() {
	delete f_pnts;
	if (pnts)
		pnts->release_private();
	f_pnts = NULL;
	pnts = NULL;
};

int f_cntr::this_get_data_count() const {
	return 1;
};

const data * f_cntr::this_get_data(int pos) const {
	if (pos == 0)
		return contour;
	return NULL;
};

void f_cntr::create_f_approx_points() {

	if (pnts == NULL) {
		d_grid * grd = create_last_grd();
		pnts = discretize_cntr(contour, grd, contour->getName());
		if (grd)
			grd->release();
	}

	if (f_pnts == NULL)
		f_pnts = new f_points(pnts, "contour");

	if ( cond() ) { 
		if (f_pnts->cond())
			f_pnts->cond_erase_all();
		int i;
		for (i = 0; i < (int)functionals_cond->size(); i++) {
			functional * cnd = (*functionals_cond)[i];
			f_pnts->cond_add(cnd);
		}
		
	}
};

bool f_cntr::minimize() {
	create_f_approx_points();
	return f_pnts->minimize();
};

bool f_cntr::make_matrix_and_vector(matr *& matrix, vec *& v) {
	create_f_approx_points();
	return f_pnts->make_matrix_and_vector(matrix, v);
};

void f_cntr::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	create_f_approx_points();
	f_pnts->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
};

bool f_cntr::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const vec * X)
{
	return true;
};

}; // namespace surfit;

