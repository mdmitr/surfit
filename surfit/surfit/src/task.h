
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

#ifndef __surfit__task__
#define __surfit__task__

#include "points.h"

namespace surfit {

/*! \class task
    \brief interpolation points (see \ref surfit_task). See \ref tcl_task "Tcl commands" for \ref task.
*/
class SURFIT_EXPORT task : public points, public data {
public:

	//! constructor
	task();
	//! another constructor
	task(REAL *& X_begin, REAL * X_end, 
             REAL *& Y_begin, REAL * Y_end, 
             REAL *& Z_begin, REAL * Z_end,
             const char * taskname = NULL);

	virtual ~task();

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;
	
};

}; // namespace surfit;

#endif

