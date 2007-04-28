
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
#include "f_curv_ineq.h"
#include "f_points_ineq.h"
#include "curv.h"
#include "points.h"
#include "grid.h"

#include "grid_user.h"

namespace surfit {

f_curv_ineq::f_curv_ineq(REAL ivalue, const d_curv * icrv, bool ileq, REAL imult) :
functional("f_curv_ineq", F_CONDI)
{
	crv = icrv;
	value = ivalue;
	leq = ileq;
	mult = imult;
	if (crv->getName()) {
		setNameF("f_curv_ineq %s", crv->getName());
	}
	f_pnts_ineq = NULL;
	pnts = NULL;
};

f_curv_ineq::~f_curv_ineq() {
	cleanup();	
};

void f_curv_ineq::cleanup() {
	delete f_pnts_ineq;
	if (pnts)
		pnts->release_private();
	f_pnts_ineq = NULL;
	pnts = NULL;
};

int f_curv_ineq::this_get_data_count() const {
	return 1;
};

const data * f_curv_ineq::this_get_data(int pos) const {
	if (pos == 0)
		return crv;
	return NULL;
};

void f_curv_ineq::create_f_points_ineq() {

	if (pnts == NULL) {
		d_grid * grd = create_last_grd();
		pnts = discretize_curv(crv, grd, value, crv->getName());
		if (pnts == NULL)
			return;
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

bool f_curv_ineq::minimize() {
	create_f_points_ineq();
	if (f_pnts_ineq)
		return f_pnts_ineq->minimize();
	return true;
};

bool f_curv_ineq::make_matrix_and_vector(matr *& matrix, extvec *& v) {
	create_f_points_ineq();
	if (f_pnts_ineq)
		return f_pnts_ineq->make_matrix_and_vector(matrix, v);
	return false;
};

void f_curv_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	create_f_points_ineq();
	if (f_pnts_ineq)
		f_pnts_ineq->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
};

bool f_curv_ineq::solvable_without_cond(const bitvec * mask_solved,
				  const bitvec * mask_undefined,
				  const extvec * X)
{
	create_f_points_ineq();
	if (f_pnts_ineq == NULL)
		return true;
	return f_pnts_ineq->solvable_without_cond(mask_solved, mask_undefined, X);
};

void f_curv_ineq::drop_private_data() {};

}; // namespace surfit;

