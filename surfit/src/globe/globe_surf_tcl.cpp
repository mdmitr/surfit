
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
#include "boolvec.h"

#include <float.h>
#include <algorithm>

namespace surfit {

struct match_surf_to_dem
{
	match_surf_to_dem(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			d_dem * d = _surf_to_dem(surf);
			if (!d) {
				res->push_back(false);
				return;
			}

			globe_dems->push_back(d);
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * surf_to_dem(const char * pos) 
{
	match_surf_to_dem qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

}; // namespace surfit;

