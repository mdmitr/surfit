
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "data.h"

namespace surfit {

/*! \class curv
    \brief class for curves. See \ref tcl_curv "Tcl commands" for \ref curv.

  This class describes curve in 2D with two vectors of coordinates (X and Y coordinates).
  These vectors are presented with iX_begin, iX_end, iY_begin and iY_end pointers.
  Curve is a segmented curve, not a smooth line. 

  \sa \ref surfit_curv
*/
class SURFIT_EXPORT curv : public data {
public:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param curv_name name of a curve
	*/
	curv(REAL * iX_begin, REAL * iX_end,
	     REAL * iY_begin, REAL * iY_end,
	     const char * curv_name = NULL);

	//! destructor
	~curv();

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! returns amount of points (segment count + 1)
	int size() const;

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

	//! pointer to the first element of X-coordinates vector
	REAL * X_begin;
	//! pointer to the last+1 element of X-coordinates vector
	REAL * X_end;
	//! pointer to the first element of Y-coordinates vector
	REAL * Y_begin;
	//! pointer to the last+1 element of Y-coordinates vector
	REAL * Y_end;
	
};

}; // namespace surfit;

#endif

