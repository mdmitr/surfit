
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
#include "dynamic.h"
#include "fileio.h"
#include "variables_internal.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "dynamic_user.h"

#include <tcl.h>

namespace surfit {

dynamic::dynamic(const char * iload_proc_name, const char * iunload_proc_name) : data()
{
	load_proc_name = strdup(iload_proc_name);
	unload_proc_name = strdup(iunload_proc_name);
};

dynamic::~dynamic() {
	free(load_proc_name);
	free(unload_proc_name);
};

bool dynamic::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	return false;
};

bool dynamic::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

const char * dynamic::load() {
	Tcl_EvalEx(surfit_interp, load_proc_name, -1, TCL_EVAL_DIRECT);
	const char * res = Tcl_GetStringResult(surfit_interp);
	if (strlen(res) > 0)
		writelog(SURFIT_MESSAGE,"%s",res);
	return NULL;
};

const char * dynamic::unload() {
	Tcl_EvalEx(surfit_interp, unload_proc_name, -1, TCL_EVAL_DIRECT);
	const char * res = Tcl_GetStringResult(surfit_interp);
	if (strlen(res) > 0)
		writelog(SURFIT_MESSAGE,"%s",res);
	return NULL;
};

}; // namespace surfit;

