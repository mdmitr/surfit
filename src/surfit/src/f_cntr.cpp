
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
#include "cntr.h"

#include "grid_user.h"

namespace surfit {

f_cntr::f_cntr(const d_cntr * icontour) :
f_points_user("f_cntr")
{
	contour = icontour;
	if (contour->getName()) {
		setNameF("f_cntr %s", contour->getName());
	}
};

f_cntr::~f_cntr() {};

int f_cntr::this_get_data_count() const 
{
	return 1;
};

const data * f_cntr::this_get_data(int pos) const 
{
	if (pos == 0)
		return contour;
	return NULL;
};

d_points * f_cntr::get_points() 
{
	d_grid * grd = create_last_grd();
	//pnts = discretize_cntr8(contour, grd, contour->getName());
	pnts = discretize_cntr(contour, MIN(grd->stepX, grd->stepY)/2., contour->getName());
	if (grd)
		grd->release();
	return pnts;
};

}; // namespace surfit;

