
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

#include "surfit_ie.h"

#include "datafile.h"
#include "fileio.h"

#include "area.h"
#include "area_tcl.h"
#include "area_internal.h"
#include "variables_internal.h"
#include "free_elements.h"

namespace surfit {

bool area_read(const char * filename, const char * areaname,
               int col1, int col2,
               const char* delimiter, int skip_lines, int grow_by)
{
	d_area * area = _area_read(filename, areaname,
				   col1, col2, skip_lines, 
				   grow_by, delimiter);

	if (area != NULL) {
		surfit_areas->push_back(area);
		return true;
	}
	return false;

};

bool area_read_bln(const char * filename, const char * areaname) {
	
	bool res = false;
	
	d_area * area = _area_read_bln(filename, areaname);
	if (area) {
		surfit_areas->push_back(area);
		res = true;
	}
	
	return res;
};

bool area_load(const char * filename, const char * areaname) {
	d_area * area = _area_load(filename, areaname);
	if (area) {
		surfit_areas->push_back(area);
		return true;
	}
	return false;
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

bool area_write(const char * filename, const char * pos, const char * delimiter) 
{
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _area_write(area, filename, buf);
};

bool area_write_bln(const char * filename, const char * area_pos, int orient) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;
	
	bool res = _area_write_bln(area, filename);
	return res;
};

bool area_save(const char * filename, const char * pos) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	writelog(LOG_MESSAGE,"Saving area to file %s", filename);

	return _area_save(area, filename);
};

bool area_save_shp(const char * filename, const char * pos) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	writelog(LOG_MESSAGE,"Saving area to ERSI shape file %s", filename);

	return _area_save_shp(area, filename);
};

bool area_setName(const char * new_name, const char * pos) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;
	area->setName(new_name);
	return true;
};

const char * area_getName(const char * pos) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;
	return area->getName();
};

bool area_delall() {

	if (surfit_areas == NULL)
		return false;

	if (surfit_areas->size() == 0) {
		//writelog(SURFIT_WARNING,"areas_delall : empty surfit_areas");
		return false;
	}

	release_elements(surfit_areas->begin(), surfit_areas->end());
	surfit_areas->resize(0);
	return true;
};

bool area_del(const char * pos) {
	std::vector<d_area *>::iterator area = get_iterator<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == surfit_areas->end())
		return false;
	if (*area)
		(*area)->release();
	surfit_areas->erase(area);
	return true;
};

bool area_invert(const char * pos) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	area->invert();
	return true;
};

int area_size() {
	return surfit_areas->size();
};

void areas_info() {
	size_t areas_counter;
	for (areas_counter = 0; areas_counter < surfit_areas->size(); areas_counter++) {
		d_area * a_area = *(surfit_areas->begin()+areas_counter);
		_area_info(a_area);
	}
};

}; // namespace surfit;

