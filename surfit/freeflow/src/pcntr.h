
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

#ifndef __flow_pcntr_included__
#define __flow_pcntr_included__

#include "cntr.h"

namespace surfit {

/*! \class pcntr
    \brief line with "production" values
*/
class FLOW_EXPORT pcntr : public cntr {
public:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param iZ_begin pointer to the first element of line values vector
	    \param iZ_end   pointer to the last+1 element of line values vector
	    \param pcntr_name name of contour
	*/
	pcntr(REAL * iX_begin, REAL * iX_end,
	      REAL * iY_begin, REAL * iY_end,
	      REAL * iZ_begin, REAL * iZ_end,
	      const char * pcntr_name = NULL);

};

}; // namespace surfit;

#endif

