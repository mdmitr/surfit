
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

#ifndef __surfit_area_included__
#define __surfit_area_included__

#include "curv.h"

namespace surfit {

/*! \class area
    \brief area with a constant value (see \ref surfit_area). See \ref tcl_area "Tcl commands" for \ref area.
*/
class SURFIT_EXPORT area : public curv {
public:

	/*! constructor
	\param iX_begin pointer to the first element of X-coordinates vector
	\param iX_end   pointer to the last+1 element of X-coordinates vector
	\param iY_begin pointer to the first element of Y-coordinates vector
	\param iY_end   pointer to the last+1 element of Y-coordinates vector
	\param ivalue   value for area
	\param area_name name of area
	*/
	area(REAL * iX_begin, REAL * iX_end,
	     REAL * iY_begin, REAL * iY_end,
	     REAL ivalue,
	     const char * area_name = NULL);

	//! constructor
	area(curv * crv, REAL ivalue);

	//! destructor
	virtual ~area();

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! value for area
	REAL value;

};

}; // namespace surfit;

#endif

