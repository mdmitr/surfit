
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

#ifndef __init_surfit_included__
#define __init_surfit_included__

#include <tcl.h>
#include <stdlib.h>

bool init_surfit_libs(char * lib, Tcl_Interp * interp, Tcl_Channel * chan) {
	
	if (!lib) 
		lib = getenv("SURFIT_LIB");
	
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	char libsurfit[] = "libsurfit.dll";
	char libfreeflow[] = "libfreeflow.dll";
//	char libsurfit_gl[] = "libsurfit_gl.dll";
#else
	char libsurfit[] = "libsurfit.so";
	char libfreeflow[] = "libfreeflow.so";
//	char libsurfit_gl[] = "libsurfit_gl.so";
#endif

	bool libs_loaded = false;
	char * surfit;
	char * freeflow;
	//char * surfit_gl;
	int res;

	if (lib) {
		
		surfit = (char *) malloc(strlen(lib)+strlen(libsurfit)+7);
		strcpy(surfit, "load ");
		strcat(surfit, lib);
		strcat(surfit, "/");
		strcat(surfit, libsurfit);

		freeflow = (char *) malloc(strlen(lib)+strlen(libfreeflow)+7);
		strcpy(freeflow, "load ");
		strcat(freeflow, lib);
		strcat(freeflow, "/");
		strcat(freeflow, libfreeflow);
		
		/*
		surfit_gl = (char *) malloc(strlen(lib)+strlen(libsurfit_gl)+7);
		strcpy(surfit_gl, "load ");
		strcat(surfit_gl, lib);
		strcat(surfit_gl, "/");
		strcat(surfit_gl, libsurfit_gl);
		*/
		
		libs_loaded = true;
		
		// trying to load libsurfit
		res = Tcl_EvalEx(interp, surfit, -1, TCL_EVAL_DIRECT);
		if (chan) 
			Tcl_Flush(*chan);
		if (res != TCL_OK)
			libs_loaded = false;

		// trying to load libfreeflow
		if (libs_loaded) {
			res = Tcl_EvalEx(interp, freeflow, -1, TCL_EVAL_DIRECT);
			if (chan) 
				Tcl_Flush(*chan);
			if (res != TCL_OK)
				libs_loaded = false;
		}
	
		/*
				
		if (libs_loaded) {
			res = Tcl_EvalEx(interp, surfit_gl, -1, TCL_EVAL_DIRECT);
			if (chan)
				Tcl_Flush(*chan);
			if (res != TCL_OK)
				libs_loaded = false;
		}
		*/
		
		free(surfit);
		free(freeflow);
		//free(surfit_gl);
		
	}

	if (!libs_loaded) {
		// searching in current directory
		surfit = (char *) malloc(strlen(libsurfit)+6);
		strcpy(surfit, "load ");
		strcat(surfit, libsurfit);

		freeflow = (char *) malloc(strlen(libfreeflow)+6);
		strcpy(freeflow, "load ");
		strcat(freeflow, libfreeflow);
		
		/*
		surfit_gl = (char *) malloc(strlen(libsurfit_gl)+6);
		strcpy(surfit_gl, "load ");
		strcat(surfit_gl, libsurfit_gl);
		*/

		bool local_libs_loaded = true;

		res = Tcl_EvalEx(interp, surfit, -1, TCL_EVAL_DIRECT);
		if (chan)
			Tcl_Flush(*chan);
		if (res != TCL_OK)
			local_libs_loaded = false;

		if (local_libs_loaded) {
			res = Tcl_EvalEx(interp, freeflow, -1, TCL_EVAL_DIRECT);
			if (chan)
				Tcl_Flush(*chan);
		}

		/*
		if (local_libs_loaded) {
		res = Tcl_EvalEx(interp, surfit_gl, -1, TCL_EVAL_DIRECT);
		if (chan)
			Tcl_Flush(*chan);
		}
				
		if (res != TCL_OK)
			local_libs_loaded = false;
			*/

		free(surfit);
		free(freeflow);
		//free(surfit_gl);
		
		return local_libs_loaded;

	}
	
	return libs_loaded;
};

#endif

