
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

#ifndef __surfit_trend_included__
#define __surfit_trend_included__

#include "func.h"

namespace surfit {

/*! \class trend
    \brief class for special function called "trend" (see \ref surfit_trend). See \ref tcl_trend "Tcl commands" for \ref trend.
*/
class SURFIT_EXPORT trend : public func {
public:

	/*! constructor
	    \param icoeff vector with values at the center of the cells
	    \param igrd grid for function
	    \param D1 weight number for operD1 operator
	    \param D2 weight number for operD2 operator
	    \param funcname function name
	*/
	trend(vec * icoeff, grid *igrd,
             REAL D1, REAL D2,
             const char * funcname = 0);

	/*! constructor
	    \param fnc function with values at the center of the cells
	    \param D1 weight number for operD1 operator
	    \param D2 weight number for operD2 operator
	*/
	trend(func *& fnc,
          REAL D1, REAL D2);

	bool writeTags(datafile * df) const;

	//! weight number for operD1 operator
	REAL D1;
	//! weight number for operD2 operator
	REAL D2;

};

}; // namespace surfit;

#endif

