
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

#include "ie.h"
#include "area.h"
#include "area_tcl.h"
#include "curv_tcl.h"
#include "area_internal.h"
#include "fileio.h"
#include "variables_internal.h"

#include "area_user.h"
#include "curv_user.h"

namespace surfit {

bool area_check() {
	return _area_check();
};

bool area_read(const char * filename, const char * areaname, REAL value,
               int columns, int col1, int col2, 
	       const char* delimiter, int grow_by)
{
	_area_unload();

	surfit_area = _area_read(filename, areaname, value,
	                         columns, col1, col2, grow_by, delimiter);

	return _area_check();

};

bool area_write(const char * filename, const char * delimiter) 
{
	if (!_area_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _area_write(surfit_area, filename, buf);
};

bool area_save(const char * filename, const char * areaname) {
	if (!_area_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving area to file %s", filename);

	if (areaname)
		surfit_area->setName(areaname);

	return _area_save(surfit_area, filename, get_rw_mode());
};

bool area_load(const char * filename, const char * areaname) {
	_area_unload();
	surfit_area = _area_load(filename, areaname, get_rw_mode());
	return (surfit_area != NULL);
};

bool area_unload() {
	return _area_unload();
};

bool area_set(area * arealine) {
	if (!arealine)
		return false;

	_set_surfit_area(arealine);
	return true;
};

bool area_name(const char * new_name, area * arealine) {
	if (arealine) {
		arealine->setName(new_name);
		return true;
	}
	if (!_area_check())
		return false;
	if (!new_name) {
		if (surfit_area->getName())
			writelog(SURFIT_MESSAGE,"surfit_area name is \"%s\"",surfit_area->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_area have no name");
		return true;
	}
	surfit_area->setName(new_name);
	return true;
};

bool area_to_areas() {
	if (!_area_check())
		return false;
	surfit_areas->push_back(surfit_area);
	surfit_area = NULL;
	return true;
};

bool area_to_curvs() {
	if (!_area_check())
		return false;
	surfit_curvs->push_back(surfit_area);
	surfit_area = NULL;
	return true;
};

bool area_to_curv() {
	if (!_area_check())
		return false;
	curv_unload();
	surfit_curv = surfit_area;
	surfit_area = NULL;
	return true;
};

bool area_value(REAL value) {
	if (!_area_check())
		return false;
	surfit_area->value = value;
	return true;
};

bool area_value_undef() {
	if (!_area_check())
		return false;
	surfit_area->value = undef_value;
	return true;
};

}; // namespace surfit;

