
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

#include "f_cntr_ineq.h"
#include "bitvec.h"
#include "vec.h"
#include "matr_diag.h"
#include "cntr.h"
#include "grid_line.h"
#include "grid.h"
#include "points.h"
#include "f_points_ineq.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_cntr_ineq::f_cntr_ineq(const d_cntr * icntr, bool ileq, REAL imult) :
functional("f_cntr_ineq", F_CONDITION)
{
	leq = ileq;
	mult = imult;
	cntr = icntr;
	f_pnts_ineq = NULL;
	pnts = NULL;
};

f_cntr_ineq::~f_cntr_ineq() {
	cleanup();
};

void f_cntr_ineq::cleanup() {
	delete f_pnts_ineq;
	if (pnts)
		pnts->release_private();
	f_pnts_ineq = NULL;
	pnts = NULL;
};

int f_cntr_ineq::this_get_data_count() const {
	return 1;
};

const data * f_cntr_ineq::this_get_data(int pos) const {
	return cntr;
};

bool f_cntr_ineq::minimize() {

	create_f_points_ineq();
	if (f_pnts_ineq == NULL)
		return false;
	return f_pnts_ineq->minimize();

};

bool f_cntr_ineq::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) 
{
	create_f_points_ineq();
	if (f_pnts_ineq)
		return f_pnts_ineq->make_matrix_and_vector(matrix, v, mask_solved, mask_undefined);
	return true;
};

void f_cntr_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	create_f_points_ineq();
	if (f_pnts_ineq)
		f_pnts_ineq->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
	mark_sums(mask_solved, mask_undefined);
};

bool f_cntr_ineq::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const extvec * X)
{
	create_f_points_ineq();
	if (f_pnts_ineq == NULL)
		return true;
	return f_pnts_ineq->solvable_without_cond(mask_solved, mask_undefined, X);
};

void f_cntr_ineq::drop_private_data() {};

void f_cntr_ineq::create_f_points_ineq() {

	if (pnts == NULL) {
		d_grid * grd = create_last_grd();
		//pnts = discretize_cntr8(cntr, grd, cntr->getName());
		pnts = discretize_cntr(cntr, MIN(grd->stepX, grd->stepY)/2., cntr->getName());
		if (pnts == NULL)
			return;
		if (grd)
			grd->release();
	}

	if (pnts == NULL)
		return;

	if (f_pnts_ineq == NULL)
		f_pnts_ineq = new f_points_ineq(pnts, leq, mult, "contour");

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


}; // namespace surfit;

