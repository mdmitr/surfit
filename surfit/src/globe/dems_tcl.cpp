
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
#include "dems_tcl.h"
#include "dem.h"
#include "f_dem.h"
#include "variables.h"

namespace surfit {

bool dem(const char * pos) {
	d_dem * fnc = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (fnc == NULL)
		return false;
	
	f_dem * f = new f_dem(fnc);
	functionals->push_back(f);
	return true;
};

bool dem_add(REAL weight, const char * pos) {
	
	if (functionals->size() == 0)
		return false;
	functional * f = *(functionals->end()-1);

	d_dem * fnc = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (fnc == NULL)
		return false;

	f_dem * fnc2 = new f_dem(fnc);
	f->add_functional(fnc2, weight);
	return true;
};

}; // namespace surfit;

