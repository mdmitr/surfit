
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

#ifndef __surfit_cntr_included__
#define __surfit_cntr_included__

#include "curv.h"

namespace surfit {

class d_cntr;
class vec;

//! constructor for \ref d_cntr class
SURFIT_EXPORT
d_cntr * create_cntr(vec * iX, vec * iY, vec * iZ,
	             const char * cntr_name = NULL);


//! constructor for \ref d_cntr class
SURFIT_EXPORT
d_cntr * create_cntr(d_curv * crv,  REAL z_value,
	             const char * cntr_name = NULL);

/*! \class d_cntr
    \brief 3D contour 
*/
class SURFIT_EXPORT d_cntr : public d_curv {
protected:
	//! constructor
	d_cntr(vec * iX, vec * iY, vec * iZ,
	       const char * cntr_name = NULL);

	//! constructor
	d_cntr(d_curv * curve, REAL z_value,
	       const char * cntr_name = NULL);

	//! destructor
	~d_cntr();

public:

	//! constructor
	friend SURFIT_EXPORT
	d_cntr * create_cntr(vec * iX, vec * iY, vec * iZ,
	                     const char * cntr_name);

	//! constructor
	friend SURFIT_EXPORT
	d_cntr * create_cntr(d_curv * crv, REAL z_value,
	                     const char * cntr_name);

	//! Z = Z + value
	void plus(REAL value);
	//! Z = Z - value
	void minus(REAL value);
	//! Z = Z * value
	void mult(REAL value);
	//! Z = Z / value
	void div(REAL value);

	//! returns minimum Z value of all data-points
	REAL minz() const;

	//! returns maximum Z value of all data-points
	REAL maxz() const;

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! pointer to the first element of line values vector
	vec * Z;

	//! removes dupe points
	void normalize(REAL eps = 1e-8);

};

class d_points;
class d_grid;

//! collection of \ref d_cntr objects
class SURFIT_EXPORT cntrs_container : public objects_container<d_cntr>
{
public:
	virtual void push_back(d_cntr * elem);
};

//! containter of \ref d_cntr objects
extern SURFIT_EXPORT cntrs_container * surfit_cntrs;

//! converts \ref d_cntr to \ref d_points (uses 4 directions)
SURFIT_EXPORT
d_points * discretize_cntr(const d_cntr * crv, d_grid * grd, const char * pnts_name);

//! converts \ref d_cntr to \ref d_points (uses 8 directions)
SURFIT_EXPORT
d_points * discretize_cntr8(const d_cntr * crv, d_grid * grd, const char * pnts_name);

//! converts \ref d_cntr to \ref d_points
SURFIT_EXPORT
d_points * discretize_cntr(const d_cntr * crv, REAL step, const char * pnts_name);

}; // namespace surfit;

#endif

