
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

#ifndef __surfit_area_included__
#define __surfit_area_included__

#include "surfit_data.h"
#include <vector>

namespace surfit {

class d_curv;
class d_area;
class boolvec;

SURFIT_EXPORT
d_area * create_area(std::vector<d_curv *> * icurves,
		     boolvec * iorients,
		     const char * area_name = NULL);

SURFIT_EXPORT
d_area * create_area(d_curv * crv, bool orient, const char * area_name = NULL);


/*! \class d_area
    \brief this class defines some region
*/
class SURFIT_EXPORT d_area : public data 
{
protected:
	//! constructor
	d_area(std::vector<d_curv *> * icurves,
		 boolvec * iorients,
	         const char * area_name = NULL);

	//! destructor
	~d_area();

public:

	friend SURFIT_EXPORT
	//! constructor
	d_area * create_area(std::vector<d_curv *> * iarealines,
				 boolvec * iorients,
	                         const char * area_name);

	friend SURFIT_EXPORT
	//! constructor
	d_area * create_area(std::vector<d_curv *> * icurves,
				 bool * orients_begin, bool * orients_end,
				 const char * area_name);

	friend SURFIT_EXPORT
	//! constructor
	d_area * create_area(d_curv * crv, bool orient, const char * area_name);

	bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! returns amount of curves, creating areagon
	int size() const;

	bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! retuns true if point with coordinates (x,y) is inside area
	bool in_region(REAL x, REAL y) const;

	//! returns i'th curv 
	const d_curv * get_curv(int i) const;

	//! returns curv orientation
	bool get_curv_orient(int i) const;

	//! returns flag
	void invert();

	//! collections of curves
	std::vector<d_curv *> * curves;
	//! collections of orientations values
	boolvec * orients;

	//! flag
	bool inverted;
	
};


/*! \ingroup surfit_variables_collections
    \var std::vector<d_area *> * surfit_areas;
    collection of \ref area objects
*/
//extern SURFIT_EXPORT std::vector<d_area *> * surfit_areas;

class SURFIT_EXPORT areas_container : public objects_container<d_area>
{
public:
	virtual void push_back(d_area * elem);
};

extern SURFIT_EXPORT
areas_container * surfit_areas;

void draw_area_matlab(FILE * ff, const d_area * area, const char * color = "green", short width = 3);

}; // namespace surfit;

#endif

