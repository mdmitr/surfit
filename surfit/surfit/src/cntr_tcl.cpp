
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
#include "cntr.h"
#include "cntr_tcl.h"
#include "curv_tcl.h"
#include "cntr_internal.h"
#include "fileio.h"
#include "wcntr_tcl.h"
#include "variables_internal.h"

#include "cntr_user.h"
#include "wcntr_user.h"
#include "curv_user.h"

namespace surfit {

bool cntr_check() {
	return _cntr_check();
};

bool cntr_read(const char * filename, const char * cntrname,
               int columns, 
	       int col1, int col2, int col3,
	       const char* delimiter, int grow_by)
{
	_cntr_unload();

	surfit_cntr = _cntr_read(filename, cntrname,
	                         columns, 
				 col1, col2, col3,
				 grow_by, delimiter);

	return _cntr_check();

};

bool cntr_write(const char * filename, const char * delimiter) 
{
	if (!_cntr_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _cntr_write(surfit_cntr, filename, buf);
};

bool cntr_save(const char * filename, const char * cntrname) {
	if (!_cntr_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving cntr to file %s", filename);

	if (cntrname)
		surfit_cntr->setName(cntrname);

	return _cntr_save(surfit_cntr, filename, get_rw_mode());
};

bool cntr_load(const char * filename, const char * cntrname) {
	_cntr_unload();
	surfit_cntr = _cntr_load(filename, cntrname, get_rw_mode());
	return (surfit_cntr != NULL);
};

bool cntr_unload() {
	return _cntr_unload();
};

bool cntr_set(cntr * contour) {
	if (!contour)
		return false;

	_set_surfit_cntr(contour);
	return true;
};

bool cntr_plus_real(REAL value) {
	if (!_cntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Increasing cntr Z-values at %lf", value);
	surfit_cntr->plus(value);
	return true;
};

bool cntr_minus_real(REAL value) {
	if (!_cntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Decreasing cntr Z-values at %lf", value);
	surfit_cntr->minus(value);
	return true;
};

bool cntr_mult_real(REAL value) {
	if (!_cntr_check())
		return false;

	writelog(SURFIT_MESSAGE,"Multiplying cntr Z-values at %lf", value);
	surfit_cntr->mult(value);
	return true;
};

bool cntr_div_real(REAL value) {
	if (!_cntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Dividing cntr Z-values at %lf", value);
	surfit_cntr->div(value);
	return true;
};

bool cntr_to_wcntr(REAL weight) {
	if (!_cntr_check())
		return false;
	wcntr_unload();
	surfit_wcntr = _cntr_to_wcntr(surfit_cntr, weight);
	if (surfit_wcntr != NULL) {
		cntr_unload();
		return true;
	}
	return false;
};

bool cntr_to_wcntrs(REAL weight) {
	if (!_cntr_check())
		return false;
	wcntr * wc = _cntr_to_wcntr(surfit_cntr, weight);
	if (wc != NULL) {
		surfit_wcntrs->push_back(wc);
		return true;
	}
	return false;
};

bool cntr_to_curv() {
	if (!_cntr_check())
		return false;
	curv_unload();
	surfit_curv = surfit_cntr;
	surfit_cntr = NULL;
	return true;
};

bool cntr_to_curvs() {
	if (!_cntr_check())
		return false;
	surfit_curvs->push_back(surfit_cntr);
	surfit_cntr = NULL;
	return true;
};

bool cntr_to_cntrs() {
	if (!_cntr_check())
		return false;
	surfit_cntrs->push_back(surfit_cntr);
	surfit_cntr = NULL;
	return true;
};

bool cntr_name(const char * new_name, cntr * contour) {
	if (contour) {
		contour->setName(new_name);
		return true;
	}
	if (!_cntr_check())
		return false;
	if (!new_name) {
		if (surfit_cntr->getName())
			writelog(SURFIT_MESSAGE,"surfit_cntr name is \"%s\"",surfit_cntr->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_cntr have no name");
		return true;
	}
	surfit_cntr->setName(new_name);
	return true;
};

}; // namespace surfit;

