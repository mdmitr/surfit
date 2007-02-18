
/* File : surfit.i */

%module surfit
%{

/*------------------------------------------------------------------------------
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

#include "real.h"
#include "fileio.h"
#include "interp.h"

#include "variables.h"
#include "variables_internal.h"
#include "variables_tcl.h"
#include "data_manager.h"
#include "license.h"
#include "others_tcl.h"
#include "hist_tcl.h"
#include "threads.h"
#include "solvers.h"
#include "other_tcl.h"

TCL_DECLARE_MUTEX(surfitMutex)

%}

%init 
%{
surfit::surfit_init_variables(interp);
%}

namespace surfit {
///*
%exception {
        try {
		if (surfit::stop_execution == 0) {
                $action
		}
        }
	catch ( const char * str ) {
		surfit::writelog(LOG_ERROR_TCL,"%s",str);
		return TCL_ERROR;
	}
	catch(...) {
		return TCL_ERROR;
        }
};
//*/

/*
%typemap(in) const char * {
	Tcl_Encoding enc = Tcl_GetEncoding(interp, NULL);
	Tcl_DString str;
	$1 = Tcl_GetStringFromObj($input,NULL);
	char * qq = Tcl_UtfToExternalDString(enc, $1, strlen($1), &str);
	$1 = strdup(qq);
};
*/

%typemap(out) char * {
   Tcl_SetObjResult(interp,Tcl_NewStringObj($1,-1));
   free($1);
};

%typemap(out) const char * {
   Tcl_SetObjResult(interp,Tcl_NewStringObj($1,-1));
};

%include "../../src/sstuff/real.h"

extern bool stop_execution;

extern float tol; 
extern REAL undef_value;

extern REAL sor_omega;
extern REAL ssor_omega;

extern char * map_name;

extern int reproject_faults;
extern int reproject_undef_areas;
extern int process_isolated_areas;

extern int penalty_max_iter;
extern REAL penalty_weight;
extern REAL penalty_weight_mult;

void init_threads(int amount);
int get_threads();
void clear_data();
void mem_info();
char * types_info();

void putlog(const char * str);

void file_load(const char * filename);
bool file_save(const char * filename);
char * file_info(const char * filename);

bool completer(REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);
bool completer_add(REAL weight = 1, REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);
bool value(REAL val = 0);
bool value_add(REAL weight = 1, REAL val = 0);
bool mean(REAL value, REAL mult = 0.001);
bool wmean(REAL value, const char * surface_name_or_position = "0", REAL mult = 0.001);
bool leq(REAL value, REAL mult = 1);
bool geq(REAL value, REAL mult = 1);
bool hist(const char * pos = "0", REAL mult = 0.001);

// hist
bool hist_read(const char * filename, REAL minz, REAL maxz, const char * histname = NULL, 
	       int col1 = 1, const char * delimiter = " \t", int skip_lines = 0, int grow_by = 250);
bool hist_write(const char * filename, const char * hist_name_or_position = "0", bool three_columns = true);

bool hist_from_surf(const char * surf_pos = "0", size_t intervs = 64, const char * histname = NULL, REAL from = FLT_MAX, REAL to = FLT_MAX);
bool hist_from_pnts(const char * pnts_pos = "0", size_t intervs = 64, const char * histname = NULL, REAL from = FLT_MAX, REAL to = FLT_MAX);

const char * hist_getName(const char * pos = "0");
bool hist_setName(const char * new_name, const char * pos = "0");
bool hist_delall();
bool hist_del(const char * pos = "0");
int hist_size();
void hists_info();
bool surf_histeq(const char * surf_name = "0", const char * hist_name = NULL);


// license stuff
void show_w();
void show_c();

}; // namespace surfit;

%include "interface/fileio.i"
%include "interface/task.i"
%include "interface/geom.i"
%include "interface/solve.i"
%include "interface/func.i"
%include "interface/curv.i"	
