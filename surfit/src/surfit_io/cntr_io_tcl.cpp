
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

#include "cntr.h"
#include "cntr_io.h"

namespace surfit {

bool cntr_load_shp(const char * filename, const char * cntrname) {
	
	d_cntr * contour = _cntr_load_shp(filename, cntrname);
	if (contour) {
		surfit_cntrs->push_back(contour);
		return true;
	}
	return false;
};

bool cntrs_load_shp(const char * filename) {
	return _cntrs_load_shp(filename);
};

bool cntr_save_shp(const char * filename, const char * pos) {

	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	
	writelog(LOG_MESSAGE,"Saving cntr to ESRI shape file %s", filename);

	return _cntr_save_shp(contour, filename);
};

}; // namespace surfit;


