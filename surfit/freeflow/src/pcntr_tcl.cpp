
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
#include "pcntr.h"
#include "pcntr_tcl.h"
#include "pcntr_internal.h"
#include "variables_internal.h"
#include "fileio.h"
#include "curv_tcl.h"

#include "pcntr_user.h"
#include "curv_user.h"

namespace surfit {

bool pcntr_check() {
	return _pcntr_check();
};

bool pcntr_read(const char * filename, const char * pcntrname,
                int columns, 
                int col1, int col2, int col3,
                const char * delimiter, int grow_by)
{
	_pcntr_unload();

	flow_pcntr = _pcntr_read(filename, pcntrname,
	                           columns, 
				   col1, col2, col3,
				   grow_by, delimiter);

	return _pcntr_check();

};

bool pcntr_write(const char * filename, const char * delimiter) 
{
	if (!_pcntr_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _pcntr_write(flow_pcntr, filename, buf);
};

bool pcntr_save(const char * filename, const char * pcntrname) {
	if (!_pcntr_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving cntr to file %s", filename);

	if (pcntrname)
		flow_pcntr->setName(pcntrname);

	return _pcntr_save(flow_pcntr, filename, get_rw_mode());
};

bool pcntr_load(const char * filename, const char * pcntrname) {
	_pcntr_unload();
	flow_pcntr = _pcntr_load(filename, pcntrname, get_rw_mode());
	return (flow_pcntr != NULL);
};

bool pcntr_unload() {
	return _pcntr_unload();
};

bool pcntr_set(pcntr * pcontour) {
	if (!pcontour)
		return false;

	_set_flow_pcntr(pcontour);
	return true;
};

bool pcntr_plus_real(REAL value) {
	if (!_pcntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Increasing pcntr Z-values at %lf", value);
	flow_pcntr->plus(value);
	return true;
};

bool pcntr_minus_real(REAL value) {
	if (!_pcntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Decreasing pcntr Z-values at %lf", value);
	flow_pcntr->minus(value);
	return true;
};

bool pcntr_mult_real(REAL value) {
	if (!_pcntr_check())
		return false;

	writelog(SURFIT_MESSAGE,"Multiplying pcntr Z-values at %lf", value);
	flow_pcntr->mult(value);
	return true;
};

bool pcntr_div_real(REAL value) {
	if (!_pcntr_check())
		return false;
	writelog(SURFIT_MESSAGE,"Dividing pcntr Z-values at %lf", value);
	flow_pcntr->div(value);
	return true;
};

bool pcntr_to_curv() {
	if (!_pcntr_check())
		return false;
	curv_unload();
	surfit_curv = flow_pcntr;
	flow_pcntr = NULL;
	return true;
};

bool pcntr_to_curvs() {
	if (!_pcntr_check())
		return false;
	surfit_curvs->push_back(flow_pcntr);
	flow_pcntr = NULL;
	return true;
};

bool pcntr_name(const char * new_name, pcntr * contour) {
	if (contour) {
		contour->setName(new_name);
		return true;
	}
	if (!_pcntr_check())
		return false;
	if (!new_name) {
		if (flow_pcntr->getName())
			writelog(SURFIT_MESSAGE,"flow_pcntr name is \"%s\"",flow_pcntr->getName());
		else 
			writelog(SURFIT_MESSAGE,"flow_pcntr have no name");
		return true;
	}
	flow_pcntr->setName(new_name);
	return true;
};

bool pcntr_to_pcntrs() {
	if (!_pcntr_check())
		return false;
	flow_pcntrs->push_back(flow_pcntr);
	flow_pcntr = NULL;
	return true;
};

}; // namespace surfit;

