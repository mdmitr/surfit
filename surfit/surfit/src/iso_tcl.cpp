
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
#include "iso.h"
#include "wiso.h"
#include "iso_tcl.h"
#include "wiso_tcl.h"
#include "curv_tcl.h"
#include "iso_internal.h"
#include "fileio.h"
#include "variables_internal.h"

#include "iso_user.h"
#include "wiso_user.h"
#include "curv_user.h"

namespace surfit {

bool iso_check() {
	return _iso_check();
};

bool iso_read(const char * filename, const char * isoname, REAL value,
	      int columns, int col1, int col2, 
	      const char* delimiter, int grow_by)
{
	_iso_unload();

	surfit_iso = _iso_read(filename, isoname, value,
                               columns, col1, col2, grow_by, delimiter);

	return _iso_check();

};

bool iso_write(const char * filename, const char * delimiter) 
{
	if (!_iso_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _iso_write(surfit_iso, filename, buf);
};

bool iso_save(const char * filename, const char * isoname) {
	if (!_iso_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving iso to file %s", filename);

	if (isoname)
		surfit_iso->setName(isoname);

	return _iso_save(surfit_iso, filename, get_rw_mode());
};

bool iso_load(const char * filename, const char * isoname) {
	_iso_unload();
	surfit_iso = _iso_load(filename, isoname, get_rw_mode());
	return (surfit_iso != NULL);
};

bool iso_unload() {
	return _iso_unload();
};

bool iso_set(iso * isoline) {
	if (!_iso_check()) 
		return false;

	_set_surfit_iso(isoline);
	return true;
};

bool iso_name(const char * new_name, iso * isoline) {
	if (isoline) {
		isoline->setName(new_name);
		return true;
	}
	if (!_iso_check())
		return false;
	if (!new_name) {
		if (surfit_iso->getName())
			writelog(SURFIT_MESSAGE,"surfit_iso name is \"%s\"",surfit_iso->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_iso have no name");
		return true;
	}
	surfit_iso->setName(new_name);
	return true;
};

bool iso_to_wiso(REAL weight) {
	if (!_iso_check()) 
		return false;
	wiso_unload();
	surfit_wiso = new wiso(surfit_iso, weight);
	delete surfit_iso;
	surfit_iso = NULL;
	return true;
};

bool iso_to_wisos(REAL weight) {
	if (!_iso_check()) 
		return false;
	wiso * wisoline = new wiso(surfit_iso, weight);
	delete surfit_iso;
	surfit_iso = NULL;
	surfit_wisos->push_back(wisoline);
	return true;
};

bool iso_to_curv() {
	if (!_iso_check()) 
		return false;
	curv_unload();
	surfit_curv = surfit_iso;
	surfit_iso = NULL;
	return true;
};

bool iso_to_curvs() {
	if (!_iso_check()) 
		return false;
	surfit_curvs->push_back(surfit_iso);
	surfit_iso = NULL;
	return true;
};

bool iso_to_isos() {
	if (!_iso_check()) 
		return false;
	surfit_isos->push_back(surfit_iso);
	surfit_iso = NULL;
	return true;
};

bool iso_value(REAL value) {
	if (!_iso_check()) 
		return false;
	surfit_iso->value = value;
	return true;
};

}; // namespace surfit;

