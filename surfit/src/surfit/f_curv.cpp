
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
#include "f_curv.h"
#include "f_points.h"
#include "curv.h"
#include "points.h"
#include "grid.h"

#include "grid_user.h"

namespace surfit {

f_curv::f_curv(REAL ivalue, const d_curv * icrv) :
functional("f_curv", F_CONDI)
{
	crv = icrv;
	value = ivalue;
	if (crv->getName()) {
		setNameF("f_curv %s", crv->getName());
	}
	f_pnts = NULL;
	pnts = NULL;
};

f_curv::~f_curv() {
	delete f_pnts;
	if (pnts)
		pnts->release_private();
};

int f_curv::this_get_data_count() const {
	return 1;
};

const data * f_curv::this_get_data(int pos) const {
	if (pos == 0)
		return crv;
	return NULL;
};

void f_curv::create_f_approx_points() {

	if (pnts == NULL) {
		d_grid * grd = create_last_grd();
		pnts = discretize_curv(crv, grd, value, crv->getName());
		delete grd;
	}

	if (f_pnts == NULL)
		f_pnts = new f_points(pnts, "curve");

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

bool f_curv::minimize() {
	create_f_approx_points();
	return f_pnts->minimize();
};

bool f_curv::make_matrix_and_vector(matr *& matrix, vec *& v) {
	create_f_approx_points();
	return f_pnts->make_matrix_and_vector(matrix, v);
};

void f_curv::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	create_f_approx_points();
	f_pnts->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
};

bool f_curv::solvable_without_cond(const bitvec * mask_solved,
				  const bitvec * mask_undefined,
				  const vec * X)
{
	return true;
};

}; // namespace surfit;

