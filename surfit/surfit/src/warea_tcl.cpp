
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
#include "warea.h"
#include "warea_tcl.h"
#include "area_tcl.h"
#include "curv_tcl.h"
#include "warea_internal.h"
#include "fileio.h"
#include "variables_internal.h"

#include "warea_user.h"
#include "area_user.h"
#include "curv_user.h"

namespace surfit {

bool warea_check() {
	return _warea_check();
};

bool warea_read(const char * filename, const char * wareaname, REAL value, REAL weight,
		int columns, int col1, int col2, 
		const char* delimiter, int grow_by)
{
	_warea_unload();

	surfit_warea = _warea_read(filename, wareaname, value, weight,
	                           columns, col1, col2, grow_by, delimiter);

	return _warea_check();

};

bool warea_write(const char * filename, const char * delimiter) 
{
	if (!_warea_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _warea_write(surfit_warea, filename, buf);
};

bool warea_save(const char * filename, const char * wareaname) {
	if (!_warea_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving warea to file %s", filename);

	if (wareaname)
		surfit_warea->setName(wareaname);

	return _warea_save(surfit_warea, filename, get_rw_mode());
};

bool warea_load(const char * filename, const char * wareaname) {
	_warea_unload();
	surfit_warea = _warea_load(filename, wareaname, get_rw_mode());
	return (surfit_warea != NULL);
};

bool warea_unload() {
	return _warea_unload();
};

bool warea_set(warea * warealine) {
	if (!warealine)
		return false;

	_set_surfit_warea(warealine);
	return true;
};

bool warea_name(const char * new_name, warea * warealine) {
	if (warealine) {
		warealine->setName(new_name);
		return true;
	}
	if (!_warea_check())
		return false;
	if (!new_name) {
		if (surfit_warea->getName())
			writelog(SURFIT_MESSAGE,"surfit_warea name is \"%s\"",surfit_warea->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_warea have no name");
		return true;
	}
	surfit_warea->setName(new_name);
	return true;
};

bool warea_value(REAL value) {
	if (!_warea_check())
		return false;
	surfit_warea->value = value;
	return true;
};

bool warea_weight(REAL weight) {
	if (!_warea_check())
		return false;
	surfit_warea->weight = weight;
	return true;
};

bool warea_to_area() {
	if (!_warea_check())
		return false;
	area_unload();
	surfit_area = surfit_warea;
	surfit_warea = NULL;
	return true;
};

bool warea_to_areas() {
	if (!_warea_check())
		return false;
	surfit_areas->push_back(surfit_warea);
	surfit_warea = NULL;
	return true;
};

bool warea_to_curv() {
	if (!_warea_check())
		return false;
	curv_unload();
	surfit_curv = surfit_warea;
	surfit_warea = NULL;
	return true;
};

bool warea_to_curvs() {
	if (!_warea_check())
		return false;
	surfit_curvs->push_back(surfit_warea);
	surfit_warea = NULL;
	return true;
};

bool warea_to_wareas() {
	if (!_warea_check())
		return false;
	surfit_wareas->push_back(surfit_warea);
	surfit_warea = NULL;
	return true;
};

}; // namespace surfit;

