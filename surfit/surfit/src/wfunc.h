
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

#ifndef __surfit__wfunc__
#define __surfit__wfunc__

#include <vector>

#include "func.h"

namespace surfit {

class vec;
class datafile;
class grid;
class task;

/*! \class wfunc
    \brief class for function with informational weight, based on the 
    equidistant \ref grid with values set at the centers of the cells 
    (see \ref surfit_wfunc). See \ref tcl_wfunc "Tcl commands" for \ref wfunc.
*/
class SURFIT_EXPORT wfunc : public func {

public:

	//! constructor
	wfunc(vec *icoeff, grid *igrd, REAL iweight,
	      const char * funcname = 0);

	//! constructor
	wfunc(func * fnc, REAL iweight,
	      const char * funcname = 0);

	//! destructor
	virtual ~wfunc();

	//! writes tag for saving func to datafile 
	virtual bool writeTags(datafile * df) const;

	//! informational weight
	REAL weight;
	
};

}; // namespace surfit;

#endif

