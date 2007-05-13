
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
#include "f_curv_surf.h"
#include "f_points.h"
#include "curv.h"
#include "points.h"
#include "surf.h"
#include "grid.h"
#include "vec.h"

#include "grid_user.h"

namespace surfit {

f_curv_surf::f_curv_surf(const d_surf * isurf, const d_curv * icrv) :
functional("f_curv_surf", F_USUAL)
{
	crv = icrv;
	srf = isurf;
	if (crv->getName()) {
		setNameF("f_curv_surf %s", crv->getName());
	}
	f_pnts = NULL;
	pnts = NULL;
};

f_curv_surf::~f_curv_surf() {
	cleanup();
};

void f_curv_surf::cleanup() {
	delete f_pnts;
	if (pnts)
		pnts->release_private();
	f_pnts = NULL;
	pnts = NULL;
};

int f_curv_surf::this_get_data_count() const {
	return 2;
};

const data * f_curv_surf::this_get_data(int pos) const {
	if (pos == 0)
		return crv;
	if (pos == 1)
		return srf;
	return NULL;
};

void f_curv_surf::create_f_approx_points() {

	if (pnts == NULL) {
		d_grid * grd = create_last_grd();
		pnts = discretize_curv(crv, grd, 0, crv->getName());
		if (pnts) {
			size_t i;
			REAL x, y, z;
			for (i = 0; i < pnts->size(); i++) {
				x = (*(pnts->X))(i);
				y = (*(pnts->Y))(i);
				z = srf->getInterpValue(x,y);
				(*(pnts->Z))(i) = z;
			}
			pnts->remove_with_value(srf->undef_value);
		}
		if (grd)
			grd->release();
		if (pnts == NULL)
			return;
	}

	if (f_pnts == NULL)
		f_pnts = new f_points(pnts, "curve+surface");

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

bool f_curv_surf::minimize() {
	create_f_approx_points();
	if (f_pnts)
		return f_pnts->minimize();
	return true;
};

bool f_curv_surf::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) 
{
	create_f_approx_points();
	if (f_pnts)
		return f_pnts->make_matrix_and_vector(matrix, v, mask_solved, mask_undefined);
	return false;
};

void f_curv_surf::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	create_f_approx_points();
	if (f_pnts)
		f_pnts->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
	mark_sums(mask_solved, mask_undefined);
};

bool f_curv_surf::solvable_without_cond(const bitvec * mask_solved,
				  const bitvec * mask_undefined,
				  const extvec * X)
{
	return true;
};

}; // namespace surfit;

