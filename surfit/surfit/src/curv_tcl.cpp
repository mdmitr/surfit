
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
#include "curv.h"
#include "curv_tcl.h"
#include "curv_internal.h"
#include "fileio.h"
#include "variables_internal.h"
#include "iso.h"
#include "iso_tcl.h"
#include "wiso.h"
#include "wiso_tcl.h"
#include "flt.h"
#include "flt_tcl.h"
#include "area.h"
#include "area_tcl.h"
#include "warea.h"
#include "warea_tcl.h"

#include "curv_user.h"
#include "iso_user.h"
#include "wiso_user.h"
#include "flt_user.h"
#include "area_user.h"
#include "warea_user.h"

namespace surfit {

bool curv_check() {
	return _curv_check();
};

bool curv_read(const char * filename, const char * curvname,
               int columns, 
	       int col1, int col2,
	       const char* delimiter, int grow_by)
{
	_curv_unload();

	surfit_curv = _curv_read(filename, curvname,
				 columns, 
				 col1, col2,
				 grow_by, delimiter);

	return _curv_check();

};

bool curv_write(const char * filename, const char * delimiter) 
{
	if (!_curv_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _curv_write(surfit_curv, filename, buf);
};

bool curv_save(const char * filename, const char * curvname) {
	if (!_curv_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving curv to file %s", filename);

	if (curvname)
		surfit_curv->setName(curvname);

	return _curv_save(surfit_curv, filename, get_rw_mode());
};

bool curv_load(const char * filename, const char * curvname) {
	_curv_unload();
	surfit_curv = _curv_load(filename, curvname, get_rw_mode());
	return (surfit_curv != NULL);
};

bool curv_unload() {
	return _curv_unload();
};

bool curv_set(curv * contour) {
	if (!contour)
		return false;

	_set_surfit_curv(contour);
	return true;
};

bool curv_name(const char * new_name, curv * crv) {
	if (crv) {
		crv->setName(new_name);
		return true;
	}
	if (!_curv_check())
		return false;
	if (!new_name) {
		if (surfit_curv->getName())
			writelog(SURFIT_MESSAGE,"surfit_curv name is \"%s\"",surfit_curv->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_curv have no name");
		return true;
	}
	surfit_curv->setName(new_name);
	return true;
};

bool curv_to_iso(REAL value) {
	if (!_curv_check()) 
		return false;
	iso_unload();
	surfit_iso = new iso(surfit_curv, value);
	delete surfit_curv;
	surfit_curv = NULL;
	return true;
};

bool curv_to_isos(REAL value) {
	if (!_curv_check()) 
		return false;
	iso * isoline = new iso(surfit_curv, value);
	delete surfit_curv;
	surfit_curv = NULL;
	surfit_isos->push_back(isoline);
	return true;
};

bool curv_to_wiso(REAL value, REAL weight) {
	if (!_curv_check()) 
		return false;
	wiso_unload();
	surfit_wiso = new wiso(surfit_curv, value, weight);
	delete surfit_curv;
	surfit_curv = NULL;
	return true;
};

bool curv_to_wisos(REAL value, REAL weight) {
	if (!_curv_check()) 
		return false;
	wiso * wisoline = new wiso(surfit_curv, value, weight);
	delete surfit_curv;
	surfit_curv = NULL;
	surfit_wisos->push_back(wisoline);
	return true;
};

bool curv_to_flt() {
	if (!_curv_check()) 
		return false;
	flt_unload();
	surfit_flt = new flt(surfit_curv);
	delete surfit_curv;
	surfit_curv = NULL;
	return true;
};

bool curv_to_flts() {
	if (!_curv_check()) 
		return false;
	flt * fault = new flt(surfit_curv);
	delete surfit_curv;
	surfit_curv = NULL;
	surfit_flts->push_back(fault);
	return true;
};

bool curv_to_area(REAL value) {
	if (!_curv_check()) 
		return false;
	area_unload();
	surfit_area = new area(surfit_curv, value);
	delete surfit_curv;
	surfit_curv = NULL;
	return true;
};

bool curv_to_areas(REAL value) {
	if (!_curv_check()) 
		return false;
	area * arealine = new area(surfit_curv, value);
	delete surfit_curv;
	surfit_curv = NULL;
	surfit_areas->push_back(arealine);
	return true;
};

bool curv_to_warea(REAL value, REAL weight) {
	if (!_curv_check()) 
		return false;
	warea_unload();
	surfit_warea = new warea(surfit_curv, value, weight);
	delete surfit_curv;
	surfit_curv = NULL;
	return true;
};

bool curv_to_wareas(REAL value, REAL weight) {
	if (!_curv_check()) 
		return false;
	warea * warealine = new warea(surfit_curv, value, weight);
	delete surfit_curv;
	surfit_curv = NULL;
	surfit_wareas->push_back(warealine);
	return true;
};

}; // namespace surfit;

