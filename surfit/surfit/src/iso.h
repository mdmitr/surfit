
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

#ifndef __surfit_iso_included__
#define __surfit_iso_included__

#include "curv.h"

namespace surfit {

/*! \class iso
    \brief line with a constant value (isoline) for interpolation (see \ref surfit_iso). See \ref tcl_iso "Tcl commands" for \ref iso.
*/
class SURFIT_EXPORT iso : public curv {
public:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param ivalue   value for isoline
	    \param iso_name name of isoline
	*/
	iso(REAL * iX_begin, REAL * iX_end,
	    REAL * iY_begin, REAL * iY_end,
	    REAL ivalue,
	    const char * iso_name = NULL);

	//! constructor
	iso(curv * crv, REAL ivalue);

	//! destructor
	virtual ~iso();

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! value for isoline
	REAL value;

};

}; // namespace surfit;

#endif

