
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "surfit_ie.h"
#include "surfit.h"

#include <string.h>

namespace surfit {

	/*
bool init_surfit_lib(Tcl_Interp * interp) {


	char * lib = NULL; 
	lib = getenv("SURFIT_LIB");
	
	char libsurfit[] = "libsurfit[info sharedlibextension]";

	bool libs_loaded = false;
	char * surfit;

	if (lib) {
		
		surfit = (char *) malloc(strlen(lib)+strlen(libsurfit)+7);
		strcpy(surfit, "load ");
		strcat(surfit, lib);
		strcat(surfit, "/");
		strcat(surfit, libsurfit);
		
		libs_loaded = true;
		
		// trying to open libsurfit
		Tcl_SetErrno(0);
		int res = Tcl_EvalEx(interp, surfit, -1, TCL_EVAL_DIRECT);
		if (res != TCL_OK)
			libs_loaded = false;
		
		free(surfit);
	}

	if (!libs_loaded) {
		// searching in current directory
		surfit = (char *) malloc(strlen(libsurfit)+6);
		strcpy(surfit, "load ");
		strcat(surfit, libsurfit);
		
		bool local_libs_loaded = true;

		int res = Tcl_EvalEx(interp, surfit, -1, TCL_EVAL_DIRECT);
			
		if (res != TCL_OK)
			local_libs_loaded = false;

		free(surfit);
		return local_libs_loaded;

	}
	
	return libs_loaded;
};
*/

}; // namespace surfit;

