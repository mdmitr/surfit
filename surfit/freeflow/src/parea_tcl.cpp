
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

#include "flow_ie.h"
#include "parea.h"
#include "parea_internal.h"
#include "parea_tcl.h"
#include "variables_internal.h"
#include "fileio.h"
#include "curv_tcl.h"

#include "parea_user.h"
#include "curv_user.h"

namespace surfit {

bool parea_check() {
	return _parea_check();
};

bool parea_read(const char * filename, const char * pareaname, REAL value,
		int columns, int col1, int col2, const char * delimiter, int grow_by)
{
	_parea_unload();

	flow_parea = _parea_read(filename, pareaname, value,
	                           columns, col1, col2, grow_by, delimiter);

	return _parea_check();

};

bool parea_write(const char * filename, const char * delimiter) 
{
	if (!_parea_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _parea_write(flow_parea, filename, buf);
};

bool parea_save(const char * filename, const char * pareaname) {
	if (!_parea_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving parea to file %s", filename);

	if (pareaname)
		flow_parea->setName(pareaname);

	return _parea_save(flow_parea, filename, get_rw_mode());
};

bool parea_load(const char * filename, const char * pareaname) {
	_parea_unload();
	flow_parea = _parea_load(filename, pareaname, get_rw_mode());
	return (flow_parea != NULL);
};

bool parea_unload() {
	return _parea_unload();
};

bool parea_set(parea * par) {
	if (!par)
		return false;

	_set_flow_parea(par);
	return true;
};

bool parea_to_pareas() {
	if (!_parea_check())
		return false;
	flow_pareas->push_back(flow_parea);
	flow_parea = NULL;
	return true;
};

bool parea_to_curvs() {
	if (!_parea_check())
		return false;
	surfit_curvs->push_back(flow_parea);
	flow_parea = NULL;
	return true;
};

bool parea_to_curv() {
	if (!_parea_check())
		return false;
	curv_unload();
	surfit_curv = flow_parea;
	flow_parea = NULL;
	return true;
};

bool parea_value(REAL value) {
	if (!_parea_check())
		return false;
	flow_parea->value = value;
	return true;
};

bool parea_name(const char * new_name, parea * parealine) {
	if (parealine) {
		parealine->setName(new_name);
		return true;
	}
	if (!_parea_check())
		return false;
	if (!new_name) {
		if (flow_parea->getName())
			writelog(SURFIT_MESSAGE,"flow_parea name is \"%s\"",flow_parea->getName());
		else 
			writelog(SURFIT_MESSAGE,"flow_parea have no name");
		return true;
	}
	flow_parea->setName(new_name);
	return true;
};


}; // namespace surfit;

