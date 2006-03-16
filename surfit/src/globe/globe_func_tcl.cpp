
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "globe_ie.h"
#include "dem.h"
#include "func_internal.h"
#include "dem_internal.h"
#include "dem_tcl.h"
#include "func.h"
#include "func_tcl.h"
#include "globe_func_internal.h"

#include <float.h>

namespace surfit {

bool func_to_dem(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	d_dem * d = _func_to_dem(fnc);
	if (!d)
		return false;

	globe_dems->push_back(d);
	return true;
};

}; // namespace surfit;

