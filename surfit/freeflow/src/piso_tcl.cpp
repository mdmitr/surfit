
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
#include "piso.h"
#include "piso_tcl.h"
#include "piso_internal.h"
#include "fileio.h"
#include "variables_internal.h"
#include "curv_tcl.h"

#include "piso_user.h"
#include "curv_user.h"

namespace surfit {

bool piso_check() {
	return _piso_check();
};

bool piso_read(const char * filename, const char * pisoname, REAL value,
	       int columns, int col1, int col2, const char * delimiter, int grow_by)
{
	_piso_unload();

	flow_piso = _piso_read(filename, pisoname, value,
	                         columns, col1, col2, grow_by, delimiter);

	return _piso_check();

};

bool piso_write(const char * filename, const char * delimiter) 
{
	if (!_piso_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _piso_write(flow_piso, filename, buf);
};

bool piso_save(const char * filename, const char * pisoname) {
	if (!_piso_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving piso to file %s", filename);

	if (pisoname)
		flow_piso->setName(pisoname);

	return _piso_save(flow_piso, filename, get_rw_mode());
};

bool piso_load(const char * filename, const char * pisoname) {
	_piso_unload();
	flow_piso = _piso_load(filename, pisoname, get_rw_mode());
	return (flow_piso != NULL);
};

bool piso_unload() {
	return _piso_unload();
};

bool piso_set(piso * pisoline) {
	if (!pisoline)
		return false;

	_set_flow_piso(pisoline);
	return true;
};

bool piso_to_curv() {
	if (!_piso_check()) 
		return false;
	curv_unload();
	surfit_curv = flow_piso;
	flow_piso = NULL;
	return true;
};

bool piso_to_curvs() {
	if (!_piso_check()) 
		return false;
	surfit_curvs->push_back(flow_piso);
	flow_piso = NULL;
	return true;
};

bool piso_to_pisos() {
	if (!_piso_check()) 
		return false;
	flow_pisos->push_back(flow_piso);
	flow_piso = NULL;
	return true;
};

bool piso_value(REAL value) {
	if (!_piso_check()) 
		return false;
	flow_piso->value = value;
	return true;
};

bool piso_name(const char * new_name, piso * pisoline) {
	if (pisoline) {
		pisoline->setName(new_name);
		return true;
	}
	if (!_piso_check())
		return false;
	if (!new_name) {
		if (flow_piso->getName())
			writelog(SURFIT_MESSAGE,"flow_piso name is \"%s\"",flow_piso->getName());
		else 
			writelog(SURFIT_MESSAGE,"flow_piso have no name");
		return true;
	}
	flow_piso->setName(new_name);
	return true;
};

}; // namespace surfit;

