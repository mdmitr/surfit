
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
#include "surf_internal.h"
#include "dem_internal.h"
#include "dem_tcl.h"
#include "surf.h"
#include "surf_tcl.h"
#include "globe_surf_internal.h"

#include <float.h>

namespace surfit {

bool surf_to_dem(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_dem * d = _surf_to_dem(srf);
	if (!d)
		return false;

	globe_dems->push_back(d);
	return true;
};

}; // namespace surfit;

