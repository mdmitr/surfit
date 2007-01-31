
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
#include "f_curv_surf_ineq.h"
#include "f_points_ineq.h"
#include "curv.h"
#include "surf.h"
#include "points.h"
#include "grid.h"
#include "vec.h"

#include "grid_user.h"

namespace surfit {

f_curv_surf_ineq::f_curv_surf_ineq(const d_surf * isrf, const d_curv * icrv, bool ileq, REAL imult) :
functional("f_curv_surf_ineq", F_CONDI)
{
	crv = icrv;
	srf = isrf;
	leq = ileq;
	mult = imult;
	if (crv->getName()) {
		setNameF("f_curv_surf_ineq %s", crv->getName());
	}
	f_pnts_ineq = NULL;
	pnts = NULL;
};

f_curv_surf_ineq::~f_curv_surf_ineq() {
	cleanup();
};

void f_curv_surf_ineq::cleanup() {
	delete f_pnts_ineq;
	if (pnts)
		pnts->release_private();
	f_pnts_ineq = NULL;
	pnts = NULL;
};

int f_curv_surf_ineq::this_get_data_count() const {
	return 2;
};

const data * f_curv_surf_ineq::this_get_data(int pos) const {
	if (pos == 0)
		return crv;
	if (pos == 1)
		return srf;
	return NULL;
};

void f_curv_surf_ineq::create_f_points_ineq() {

	if (pnts == NULL) {
		d_grid * grd = create_last_grd();
		pnts = discretize_curv(crv, grd, 0, crv->getName());
		if (pnts) {
			int i;
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
	}

	if (f_pnts_ineq == NULL)
		f_pnts_ineq = new f_points_ineq(pnts, leq, mult, "curve");

	if ( cond() ) { 
		if (f_pnts_ineq->cond())
			f_pnts_ineq->cond_erase_all();
		int i;
		for (i = 0; i < (int)functionals_cond->size(); i++) {
			functional * cnd = (*functionals_cond)[i];
			f_pnts_ineq->cond_add(cnd);
		}
		
	}
};

bool f_curv_surf_ineq::minimize() {
	create_f_points_ineq();
	return f_pnts_ineq->minimize();
};

bool f_curv_surf_ineq::make_matrix_and_vector(matr *& matrix, extvec *& v) {
	create_f_points_ineq();
	return f_pnts_ineq->make_matrix_and_vector(matrix, v);
};

void f_curv_surf_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	create_f_points_ineq();
	f_pnts_ineq->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
};

bool f_curv_surf_ineq::solvable_without_cond(const bitvec * mask_solved,
				  const bitvec * mask_undefined,
				  const extvec * X)
{
	return true;
};

void f_curv_surf_ineq::drop_private_data() {};

}; // namespace surfit;

