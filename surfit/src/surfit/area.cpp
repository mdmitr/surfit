
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
#include "area.h"
#include "curv.h"
#include "boolvec.h"
#include "free_elements.h"

#include <float.h>

namespace surfit {

d_area * create_area(std::vector<d_curv *> * curves, boolvec * orients, const char * iname) {
	return new d_area(curves, orients, iname);
};

d_area * create_area(d_curv * crv, bool orient, const char * areaname) {
	std::vector<d_curv *> * curves = new std::vector<d_curv *>;
	curves->push_back(crv);
	boolvec * orients = create_boolvec();
	orients->push_back(orient);
	return new d_area(curves, orients, areaname);
};

d_area::d_area(std::vector<d_curv *> * icurves,
		   boolvec * iorients,
                   const char * area_name) : data("area")
{
	curves = icurves;
	orients = iorients;
	setName(area_name);
	inverted = false;
};

d_area::~d_area() {
	if (curves)
		release_elements(curves->begin(), curves->end());
	delete curves;
	if (orients)
		orients->release();
};

bool d_area::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	if (curves == NULL)
		return false;

	minx = FLT_MAX;
	maxx = -FLT_MAX;
	miny = FLT_MAX;
	maxy = -FLT_MAX;

	REAL Minx;
	REAL Maxx;
	REAL Miny;
	REAL Maxy;

	bool res = false;

	int i;
	for (i = 0; i < (int)curves->size(); i++) {
		d_curv * crv = (*curves)[i];
		if (crv->bounds(Minx, Maxx, Miny, Maxy)) {
			res = true;
			minx = MIN(minx, Minx);
			maxx = MAX(maxx, Maxx);
			miny = MIN(miny, Miny);
			maxy = MAX(maxy, Maxy);
		}
	}

	return res;
};

bool d_area::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

int d_area::size() const {
	if (curves == NULL)
		return 0;
	return curves->size();
};

const d_curv * d_area::get_curv(int i) const {
	return (*curves)[i];
};

bool d_area::get_curv_orient(int i) const {
	return (*orients)(i);
};

bool d_area::in_region(REAL x, REAL y) const {

	bool res = false;
	int i;
	for (i = 0; i < size(); i++) {
		const d_curv * crv = get_curv(i);
		bool inside = get_curv_orient(i);

		bool crv_res = crv->in_region(x,y);

		if (inside == true) {
			res = res || crv_res;
		} else {
			res = res ^ crv_res;
		}
	}

	if (inverted == false)
		return res;

	return !res;
};

void d_area::invert() {
	inverted = !inverted;
};

std::vector<d_area *>     * surfit_areas     = NULL;

/*! \struct area_garbage
    \brief struct for deletion of \ref area pointers
*/
struct area_garbage : public binman {
	//! inits \ref surfit_area and \ref surfit_areas
	area_garbage() {
		surfit_areas = new std::vector<d_area *>;
	}
	//! removes \ref surfit_area and \ref surfit_areas
	~area_garbage() {
		if (surfit_areas) {
			release_elements(surfit_areas->begin(), surfit_areas->end());
			delete surfit_areas;
			surfit_areas = NULL;
		}
	}

};

area_garbage area_garb;

}; // namespace surfit;

