
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
#include "wiso.h"
#include "wiso_tcl.h"
#include "iso_tcl.h"
#include "curv_tcl.h"
#include "wiso_internal.h"
#include "fileio.h"
#include "variables_internal.h"

#include "wiso_user.h"
#include "iso_user.h"
#include "curv_user.h"

namespace surfit {

bool wiso_check() {
	return _wiso_check();
};

bool wiso_read(const char * filename, const char * wisoname, REAL value, REAL weight,
	       int columns, int col1, int col2, const char* delimiter, int grow_by)
{
	_wiso_unload();

	surfit_wiso = _wiso_read(filename, wisoname, value, weight,
	                         columns, col1, col2, grow_by, delimiter);

	return _wiso_check();

};

bool wiso_write(const char * filename, const char * delimiter) 
{
	if (!_wiso_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _wiso_write(surfit_wiso, filename, buf);
};

bool wiso_save(const char * filename, const char * wisoname) {
	if (!_wiso_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving wiso to file %s", filename);

	if (wisoname)
		surfit_wiso->setName(wisoname);

	return _wiso_save(surfit_wiso, filename, get_rw_mode());
};

bool wiso_load(const char * filename, const char * wisoname) {
	_wiso_unload();
	surfit_wiso = _wiso_load(filename, wisoname, get_rw_mode());
	return (surfit_wiso != NULL);
};

bool wiso_unload() {
	return _wiso_unload();
};

bool wiso_set(wiso * wisoline) {
	if (!_wiso_check()) 
		return false;

	_set_surfit_wiso(wisoline);
	return true;
};

bool wiso_name(const char * new_name, wiso * wisoline) {
	if (wisoline) {
		wisoline->setName(new_name);
		return true;
	}
	if (!_wiso_check())
		return false;
	if (!new_name) {
		if (surfit_wiso->getName())
			writelog(SURFIT_MESSAGE,"surfit_wiso name is \"%s\"",surfit_wiso->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_wiso have no name");
		return true;
	}
	surfit_wiso->setName(new_name);
	return true;
};

bool wiso_to_iso() {
	if (!_wiso_check()) 
		return false;
	iso_unload();
	surfit_iso = surfit_wiso;
	surfit_wiso = NULL;
	return true;
};

bool wiso_to_isos() {
	if (!_wiso_check()) 
		return false;
	surfit_isos->push_back(surfit_wiso);
	surfit_wiso = NULL;
	return true;
};

bool wiso_to_curv() {
	if (!_wiso_check()) 
		return false;
	curv_unload();
	surfit_curv = surfit_wiso;
	surfit_wiso = NULL;
	return true;
};

bool wiso_to_curvs() {
	if (!_wiso_check()) 
		return false;
	surfit_curvs->push_back(surfit_wiso);
	surfit_wiso = NULL;
	return true;
};

bool wiso_to_wisos() {
	if (!_wiso_check()) 
		return false;
	surfit_wisos->push_back(surfit_wiso);
	surfit_wiso = NULL;
	return true;
};

bool wiso_value(REAL value) {
	if (!_wiso_check()) 
		return false;
	surfit_wiso->value = value;
	return true;
};

bool wiso_weight(REAL weight) {
	if (!_wiso_check()) 
		return false;
	surfit_wiso->weight = weight;
	return true;
};

}; // namespace surfit;

