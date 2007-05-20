
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
#include "surf.h"
#include "surf_internal.h"

#include "grid_user.h"

#include <float.h>

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
	return 1;;
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

//
//
// f_cntr2
//
//

f_cntr2::f_cntr2() :
f_points_user("f_cntr2")
{
	contours = new std::vector<const d_cntr *>();
	setNameF("f_contours");
};

f_cntr2::~f_cntr2() {};

int f_cntr2::this_get_data_count() const 
{
	return contours->size();
};

const data * f_cntr2::this_get_data(int pos) const 
{
	if (pos == 0)
		return (*contours)[pos];
	return NULL;
};

void f_cntr2::add_contour(const d_cntr * cntr)
{
	contours->push_back(cntr);
};

d_points * f_cntr2::get_points() 
{
	d_grid * grd = create_last_grd();
	// create points for triangulation
	vec * x = create_vec();
	vec * y = create_vec();
	vec * z = create_vec();
	size_t i,j;
	for (i = 0; i < contours->size(); i++) {
		const d_cntr * cntr = (*contours)[i];
		x->reserve( x->size() + cntr->size() );
		y->reserve( y->size() + cntr->size() );
		z->reserve( z->size() + cntr->size() );
		for (j = 0; j < cntr->size(); j++) {
			x->push_back( (*(cntr->X))(j) );
			y->push_back( (*(cntr->Y))(j) );
			z->push_back( (*(cntr->Z))(j) );
		}
	}
	d_points * tri_pnts = create_points(x, y, z);

	d_surf * tri_surf = triangulate_points(tri_pnts, grd);
	tri_pnts->release();
	tri_pnts = NULL;
	if (tri_surf == NULL) {
		grd->release();
		return NULL;
	}

	x = create_vec();
	y = create_vec();
	z = create_vec();
	for (i = 0; i < contours->size(); i++) {
		const d_cntr * cntr = (*contours)[i];
		d_points * pnts = discretize_curv(cntr, grd, FLT_MAX);
		if (pnts == NULL)
			continue;
		x->reserve(x->size() + pnts->size());
		y->reserve(y->size() + pnts->size());
		for (j = 0; j < pnts->size(); j++) {
			REAL X = (*(pnts->X))(j);
			REAL Y = (*(pnts->Y))(j);
			REAL Z = tri_surf->getInterpValue(X,Y);
			if (Z == tri_surf->undef_value)
				continue;
			x->push_back( X );
			y->push_back( Y );
			z->push_back( Z );
		}
	}

	tri_surf->release();
	if (grd)
		grd->release();
	d_points * pnts = create_points(x, y, z);
	return pnts;
};

}; // namespace surfit;

