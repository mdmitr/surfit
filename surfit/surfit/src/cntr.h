
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

#ifndef __surfit_cntr_included__
#define __surfit_cntr_included__

#include "curv.h"

namespace surfit {

/*! \class cntr
    \brief 3D contour for interpolation (see \ref surfit_cntr). See \ref tcl_cntr "Tcl commands" for \ref cntr.
*/
class SURFIT_EXPORT cntr : public curv {
public:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param iZ_begin pointer to the first element of line values vector
	    \param iZ_end   pointer to the last+1 element of line values vector
	    \param cntr_name name of contour
	*/
	cntr(REAL * iX_begin, REAL * iX_end,
	     REAL * iY_begin, REAL * iY_end,
	     REAL * iZ_begin, REAL * iZ_end,
	     const char * cntr_name = NULL);

	//! Z = Z + value
	void plus(REAL value);
	//! Z = Z - value
	void minus(REAL value);
	//! Z = Z * value
	void mult(REAL value);
	//! Z = Z / value
	void div(REAL value);

	//! destructor
	~cntr();

	//! returns minimum Z value of all data-points
	REAL minz() const;

	//! returns maximum Z value of all data-points
	REAL maxz() const;

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! pointer to the first element of line values vector
	REAL * Z_begin;
	
	//! pointer to the last+1 element of line values vector
	REAL * Z_end;

};

}; // namespace surfit;

#endif

