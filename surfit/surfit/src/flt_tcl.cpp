
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
#include "flt.h"
#include "grid_line.h"
#include "flt_tcl.h"
#include "curv_tcl.h"
#include "flt_internal.h"
#include "grid_internal.h"
#include "fileio.h"
#include "variables_internal.h"

#include "flt_user.h"
#include "curv_user.h"
#include "grid_line_user.h"
#include "grid_user.h"

namespace surfit {

bool flt_check() {
	return _flt_check();
};

bool flt_read(const char * filename, const char * fltname, int columns, 
	      int col1, int col2, 
	      const char* delimiter, int grow_by)
{
	_flt_unload();

	surfit_flt = _flt_read(filename, fltname, columns,
	                       col1, col2, grow_by, delimiter);

	return _flt_check();

};

bool flt_write(const char * filename, const char * delimiter) 
{
	if (!_flt_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _flt_write(surfit_flt, filename, buf);
};

bool flt_save(const char * filename, const char * fltname) {
	if (!_flt_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving flt to file %s", filename);

	if (fltname)
		surfit_flt->setName(fltname);

	return _flt_save(surfit_flt, filename, get_rw_mode());
};

bool flt_load(const char * filename, const char * fltname) {
	_flt_unload();
	surfit_flt = _flt_load(filename, fltname, get_rw_mode());
	return (surfit_flt != NULL);
};

bool flt_unload() {
	return _flt_unload();
};

bool flt_set(flt * fault) {
	if (!_flt_check()) 
		return false;

	_set_surfit_flt(fault);
	return true;
};

bool flt_name(const char * new_name, flt * fault) {
	if (fault) {
		fault->setName(new_name);
		return true;
	}
	if (!_flt_check())
		return false;
	if (!new_name) {
		if (surfit_flt->getName())
			writelog(SURFIT_MESSAGE,"surfit_flt name is \"%s\"",surfit_flt->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_flt have no name");
		return true;
	}
	surfit_flt->setName(new_name);
	return true;
};

bool flt_to_curv() {
	if (!_flt_check()) 
		return false;
	curv_unload();
	surfit_curv = surfit_flt;
	surfit_flt = NULL;
	return false;
};

bool flt_to_curvs() {
	if (!_flt_check()) 
		return false;
	surfit_curvs->push_back(surfit_flt);
	surfit_flt = NULL;
	return false;
};

bool flt_to_flts() {
	if (!_flt_check()) 
		return false;
	surfit_flts->push_back(surfit_flt);
	surfit_flt = NULL;
	return false;
};

bool flt_to_grid_line() {

	if (!_grid_check())
		return false;

	if (!_flt_check())
		return false;

	delete surfit_grid_line;
	surfit_grid_line = NULL;


	if (_flt_check()) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_flt, surfit_grid);
	}
		
	if (!surfit_grid_line)
		return false;

	return true;
};

}; // namespace surfit;

