
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

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_cntr_ineq::f_cntr_ineq(const d_cntr * icntr, bool ileq, REAL imult) :
f_points_ineq_user("f_cntr_ineq", ileq, imult)
{
	cntr = icntr;
};

f_cntr_ineq::~f_cntr_ineq() {};

int f_cntr_ineq::this_get_data_count() const {
	return 1;
};

const data * f_cntr_ineq::this_get_data(int pos) const {
	return cntr;
};

d_points * f_cntr_ineq::get_points() 
{
	d_grid * grd = create_last_grd();
	//pnts = discretize_cntr8(cntr, grd, cntr->getName());
	pnts = discretize_cntr(cntr, MIN(grd->stepX, grd->stepY)/2., cntr->getName());
	if (grd)
		grd->release();
	return pnts;
};


}; // namespace surfit;

