
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

#include "area.h"
#include "area_io.h"

namespace surfit {

bool area_load_bln(const char * filename, const char * areaname) {
	
	bool res = false;
	
	d_area * area = _area_load_bln(filename, areaname);
	if (area) {
		surfit_areas->push_back(area);
		res = true;
	}
	
	return res;
};

bool area_load_shp(const char * filename, const char * areaname) {
	d_area * area = _area_load_shp(filename, areaname);
	if (area) {
		surfit_areas->push_back(area);
		return true;
	}
	return false;
};

bool areas_load_shp(const char * filename) {
	return _areas_load_shp(filename);
};

bool area_save_bln(const char * filename, const char * area_pos, int orient) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;
	
	bool res = _area_save_bln(area, filename);
	return res;
};

bool area_save_shp(const char * filename, const char * pos) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	writelog(LOG_MESSAGE,"Saving area to ERSI shape file %s", filename);

	return _area_save_shp(area, filename);
};

}; // namespace surfit;


