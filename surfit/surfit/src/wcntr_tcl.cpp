
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
#include "wcntr.h"
#include "wcntr_tcl.h"
#include "cntr_tcl.h"
#include "curv_tcl.h"
#include "wcntr_internal.h"
#include "cntr_internal.h"
#include "fileio.h"
#include "variables_internal.h"

#include "wcntr_user.h"
#include "cntr_user.h"
#include "curv_user.h"

namespace surfit {

bool wcntr_check() {
	return _wcntr_check();
};

bool wcntr_read(const char * filename, const char * wcntrname, REAL weight,
                int columns, 
		int col1, int col2, int col3,
		const char* delimiter, int grow_by)
{
	_wcntr_unload();

	surfit_wcntr = _wcntr_read(filename, wcntrname, weight,
	                           columns, 
				   col1, col2, col3,
				   grow_by, delimiter);

	return _wcntr_check();

};

bool wcntr_write(const char * filename, const char * delimiter) 
{
	if (!_wcntr_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _cntr_write(surfit_wcntr, filename, buf);
};

bool wcntr_save(const char * filename, const char * wcntrname) {
	if (!_wcntr_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving wcntr to file %s", filename);

	if (wcntrname)
		surfit_wcntr->setName(wcntrname);

	return _wcntr_save(surfit_wcntr, filename, get_rw_mode());
};

bool wcntr_load(const char * filename, const char * wcntrname) {
	_wcntr_unload();
	surfit_wcntr = _wcntr_load(filename, wcntrname, get_rw_mode());
	return (surfit_wcntr != NULL);
};

bool wcntr_unload() {
	return _wcntr_unload();
};

bool wcntr_set(wcntr * contour) {
	if (!contour)
		return false;

	_set_surfit_wcntr(contour);
	return true;
};

bool wcntr_plus_real(REAL value) {
	if (!_wcntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Increasing wcntr Z-values at %lf", value);
	surfit_wcntr->plus(value);
	return true;
};

bool wcntr_minus_real(REAL value) {
	if (!_wcntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Decreasing wcntr Z-values at %lf", value);
	surfit_wcntr->minus(value);
	return true;
};

bool wcntr_mult_real(REAL value) {
	if (!_wcntr_check())
		return false;

	writelog(SURFIT_MESSAGE,"Multiplying wcntr Z-values at %lf", value);
	surfit_wcntr->mult(value);
	return true;
};

bool wcntr_div_real(REAL value) {
	if (!_wcntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Dividing wcntr Z-values at %lf", value);
	surfit_wcntr->div(value);
	return true;
};

bool wcntr_name(const char * new_name, wcntr * wcontour) {
	if (wcontour) {
		wcontour->setName(new_name);
		return true;
	}
	if (!_wcntr_check())
		return false;
	if (!new_name) {
		if (surfit_wcntr->getName())
			writelog(SURFIT_MESSAGE,"surfit_wcntr name is \"%s\"",surfit_wcntr->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_wcntr have no name");
		return true;
	}
	surfit_wcntr->setName(new_name);
	return true;
};

bool wcntr_to_cntr() {
	if (!_wcntr_check())
		return false;
	cntr_unload();
	surfit_cntr = surfit_wcntr;
	surfit_wcntr = NULL;
	return true;
};

bool wcntr_to_cntrs() {
	if (!_wcntr_check())
		return false;
	surfit_cntrs->push_back(surfit_wcntr);
	surfit_wcntr = NULL;
	return true;
};

bool wcntr_to_curv() {
	if (!_wcntr_check())
		return false;
	cntr_unload();
	surfit_curv = surfit_wcntr;
	surfit_wcntr = NULL;
	return true;
};

bool wcntr_to_curvs() {
	if (!_wcntr_check())
		return false;
	surfit_curvs->push_back(surfit_wcntr);
	surfit_wcntr = NULL;
	return true;
};

bool wcntr_to_wcntrs() {
	if (!_wcntr_check())
		return false;
	surfit_wcntrs->push_back(surfit_wcntr);
	surfit_wcntr = NULL;
	return true;
};

}; // namespace surfit;

