
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

#ifndef __surfit_dynamic_included__
#define __surfit_dynamic_included__

#include "data.h"

namespace surfit {

/*! \class dynamic
    \brief dynamically loadable data class (see \ref surfit_dynamic). See \ref tcl_dynamic "Tcl commands" for \ref dynamic.
*/
class dynamic : public data 
{
public:

	/*! constructor
	    \param iload_proc_name name of tcl-procedure for load data
	    \param iunload_proc_name name of tcl-procedure for unload data
	*/
	dynamic(const char * iload_proc_name, const char * iunload_proc_name);

	//! destructor
	~dynamic();

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! executes load procedure
	const char * load();
	//! executes unload procedure
	const char * unload();

	//! name of tcl-procedure for load data
	char * load_proc_name;
	//! name of tcl-procedure for unload data
	char * unload_proc_name;

};

}; // namespace surfit;

#endif

