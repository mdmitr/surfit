
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

#include "surfit_io_ie.h"

#include "points.h"
#include "pnts_io.h"

namespace surfit {

bool pnts_load_shp(const char * filename, const char * pntsname, const char * param) {
	d_points * pnts = _pnts_load_shp(filename, pntsname, param);
	if (pnts) {
		surfit_pnts->push_back(pnts);
		return true;
	}
	return false;
};

bool pnts_save_shp(const char * filename, const char * pos) {
	
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	writelog(LOG_MESSAGE,"Saving points to ESRI shapefile format %s", filename);

	return _pnts_save_shp(pnts, filename);
};

}; // namespace surfit;


