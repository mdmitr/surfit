
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

#ifndef __surfit__wtask__
#define __surfit__wtask__

#include "task.h"

namespace surfit {

/*! \class wtask
    \brief approximation points (see \ref surfit_wtask). See \ref tcl_wtask "Tcl commands" for \ref wtask.
*/
class SURFIT_EXPORT wtask : public task {
public:

	//! constructor
	wtask();
	//! another constructor
	wtask(REAL *& X_begin, REAL * X_end, 
              REAL *& Y_begin, REAL * Y_end, 
              REAL *& Z_begin, REAL * Z_end,
	      REAL *& W_begin, REAL * W_end,
              const char * taskname = NULL);

	//! destructor
	virtual ~wtask();

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! pointer to begin of Weights data array
	REAL * W_begin;
	//! pointer to end of Weights data array
	REAL * W_end;

};

}; // namespace surfit;

#endif

