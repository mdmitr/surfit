
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

#ifndef __surfit_flt_included__
#define __surfit_flt_included__

#include "curv.h"

namespace surfit {

/*! \class flt
    \brief tectonical fault line (see \ref surfit_flt). See \ref tcl_flt "Tcl commands" for \ref flt.
*/
class SURFIT_EXPORT flt : public curv {
public:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param flt_name name of fault line
	*/
	flt(REAL * iX_begin, REAL * iX_end,
	    REAL * iY_begin, REAL * iY_end,
	    const char * flt_name = NULL);

	//! constructor
	flt(curv * crv);

	//! destructor
	virtual ~flt();

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

};

}; // namespace surfit;

#endif

