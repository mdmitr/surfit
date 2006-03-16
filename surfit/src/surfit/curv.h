
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

#ifndef __surfit_curv_included__
#define __surfit_curv_included__

#include "surfit_data.h"

namespace surfit {

class d_curv;
class vec;

SURFIT_EXPORT
d_curv * create_curv(vec * iX, vec * iY,
		     const char * curv_name = NULL);

SURFIT_EXPORT
d_curv * create_curv(const d_curv * src);

/*! \class curv
    \brief class for curves. See \ref tcl_curv "Tcl commands" for \ref curv.

  This class describes curve in 2D with two vectors of coordinates (X and Y coordinates).
  These vectors are presented with iX_begin, iX_end, iY_begin and iY_end pointers.
  Curve is a segmented curve, not a smooth line. 

  \sa \ref surfit_curv
*/
class SURFIT_EXPORT d_curv : public data {
protected:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param curv_name name of a curve
	*/
	d_curv(vec * iX, vec * iY,
	       const char * curv_name = NULL);

	//! destructor
	~d_curv();

public:

	friend SURFIT_EXPORT
	d_curv * create_curv(vec * iX, vec * iY,
		             const char * curv_name);

	friend SURFIT_EXPORT
	d_curv * create_curv(const d_curv * src);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! returns amount of points (segment count + 1)
	virtual int size() const;

	//! returns true if curve is closed
	bool is_closed() const;

	//! makes curve closed
	void close();

	//! returns minimum X value of all points
	REAL minx() const;

	//! returns maximum X value of all points
	REAL maxx() const;

	//! returns minimum Y value of all points
	REAL miny() const;

	//! returns maximum Y value of all points
	REAL maxy() const;

	//! returns curve lenght in XoY plane
	REAL length_xy() const;

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	bool in_region(REAL x, REAL y) const;

	//! pointer to the first element of X-coordinates vector
	vec * X;
	//! pointer to the last+1 element of X-coordinates vector
	vec * Y;
	
};

class d_points;
class d_grid;

/*! \ingroup surfit_variables_collections
    \var std::vector<d_curv *> * surfit_curvs;
    collection of \ref curv objects
*/
extern SURFIT_EXPORT std::vector<d_curv *> * surfit_curvs;

SURFIT_EXPORT
d_points * discretize_curv(const d_curv * crv, d_grid * grd, REAL value, const char * pnts_name);


}; // namespace surfit;

#endif
