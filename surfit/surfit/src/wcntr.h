
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

#ifndef __surfit_wcntr_included__
#define __surfit_wcntr_included__

#include "cntr.h"

namespace surfit {

/*! \class wcntr
    \brief 3D contour for approximation (see \ref surfit_wcntr). See \ref tcl_wcntr "Tcl commands" for \ref wcntr.
*/
class SURFIT_EXPORT wcntr : public cntr {
public:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param iZ_begin pointer to the first element of line values vector
	    \param iZ_end   pointer to the last+1 element of line values vector
	    \param iweight  informational weight for contour
	    \param cntr_name name of contour
	*/
	wcntr(REAL * iX_begin, REAL * iX_end,
	      REAL * iY_begin, REAL * iY_end,
	      REAL * iZ_begin, REAL * iZ_end,
	      REAL iweight,
	      const char * cntr_name = NULL);

	//! destructor
	~wcntr();

	//! informational weight
	REAL weight;

};

}; // namespace surfit;

#endif

