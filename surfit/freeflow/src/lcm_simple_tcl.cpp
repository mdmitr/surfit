
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
#include "lcm_simple_tcl.h"
#include "lcm_simple_internal.h"
#include "flow_variables.h"
#include "lcm_simple.h"
#include "fileio.h"
#include "variables_internal.h"

#include "lcm_simple_user.h"

namespace surfit {

void lcm_simple_set(REAL permeability, REAL viscosity, REAL multiplier) {
	
	lcm_simple_unload();
	flow_lcm_simple = new lcm_simple(permeability, viscosity, multiplier);

};

bool lcm_simple_unload() {
	if (flow_lcm_simple) {
		writelog(SURFIT_MESSAGE,"unloading lcm_simple");
		delete flow_lcm_simple;
		flow_lcm_simple = NULL;
		return true;
	}
	return false;
}

bool lcm_simple_read(const char * filename, const char * lcm_simple_name) {
	lcm_simple * lcm = _lcm_simple_read(filename, lcm_simple_name);
	if (lcm) {
		lcm_simple_unload();
		flow_lcm_simple = lcm;
		return true;
	}
	return false;
};

bool lcm_simple_load(const char * filename, const char * lcm_simple_name) {
	lcm_simple_unload();
	lcm_simple * lcm = _lcm_simple_load(filename, lcm_simple_name, get_rw_mode());
	if (lcm) {
		flow_lcm_simple = lcm;
		return true;
	}
	return false;
};

bool lcm_simple_write(const char * filename) {
	if (!_lcm_simple_check())
		return false;
	return _lcm_simple_write(flow_lcm_simple, filename);
};

bool lcm_simple_save(const char * filename, const char * lcm_simple_name) {
	if (!_lcm_simple_check())
		return false;
	if (lcm_simple_name)
		flow_lcm_simple->setName(lcm_simple_name);
	return _lcm_simple_save(flow_lcm_simple, filename, get_rw_mode());
};

bool lcm_simple_check() {
	return (flow_lcm_simple != NULL);
};

int lcm_simple_info() {
	if (!_lcm_simple_check())
		return 0;
	return _lcm_simple_info(flow_lcm_simple);
};

}; // namespace surfit;

