
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
#include "curv.h"
#include "surf.h"
#include "points.h"
#include "grid.h"
#include "vec.h"

#include "grid_user.h"

namespace surfit {

f_curv_surf_ineq::f_curv_surf_ineq(const d_surf * isrf, const d_curv * icrv, bool ileq, REAL imult) :
f_points_ineq_user("f_curv_surf_ineq", ileq, imult)
{
	crv = icrv;
	srf = isrf;
	if (crv->getName()) {
		setNameF("f_curv_surf_ineq %s", crv->getName());
	}
};

f_curv_surf_ineq::~f_curv_surf_ineq() {};

int f_curv_surf_ineq::this_get_data_count() const 
{
	return 2;
};

const data * f_curv_surf_ineq::this_get_data(int pos) const 
{
	if (pos == 0)
		return crv;
	if (pos == 1)
		return srf;
	return NULL;
};

d_points * f_curv_surf_ineq::get_points()
{
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
	return pnts;
};

}; // namespace surfit;

