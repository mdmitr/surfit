
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
#include "boolvec.h"
#include "strvec.h"
#include "intvec.h"

#include "variables.h"
#include "variables_internal.h"
#include "variables_tcl.h"
#include "data_manager.h"
#include "license.h"
#include "others_tcl.h"
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

%typemap(out) char * {
   Tcl_SetObjResult(interp,Tcl_NewStringObj($1,-1));
   free($1);
};

%typemap(out) const char * {
   Tcl_SetObjResult(interp,Tcl_NewStringObj($1,-1));
};

%typemap(out) surfit::vec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			double val = (double)(*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewDoubleObj(val));
		}
		($1)->release();
	}
}

%typemap(out) surfit::intvec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			int val = (int)(*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewIntObj(val));
		}
		($1)->release();
	}
}

%typemap(out) surfit::boolvec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			bool val = (bool)(*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewBooleanObj(val));
		}
		($1)->release();
	}
}

%typemap(out) surfit::strvec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			char * val = (*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewStringObj(val,-1));
		}
		($1)->release();
	}
}

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

extern size_t penalty_max_iter;
extern REAL penalty_weight;
extern REAL penalty_weight_mult;

void init_threads(int amount);
int get_threads();
void clear_data();
void mem_info();
char * types_info();

void putlog(const char * str);

const char * datafile_mode();
const char * datafile_new();
const char * datafile_append();
void file_load(const char * filename);
bool file_save(const char * filename);
char * file_info(const char * filename);

bool completer(REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);
bool completer_add(REAL weight = 1, REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);
bool value(const char * value = "undef");
bool value_add(REAL weight = 1, REAL val = 0);
bool mean(REAL value, REAL penalty_factor = -2);
surfit::boolvec * wmean(REAL value, const char * surface_name = "*", REAL penalty_factor = -2);
bool leq(REAL value, REAL penalty_factor = 0);
bool geq(REAL value, REAL penalty_factor = 0);
bool triangulate();

// license
void show_w();
void show_c();

}; // namespace surfit;

%include "interface/fileio.i"
%include "interface/task.i"
%include "interface/geom.i"
%include "interface/solve.i"
%include "interface/func.i"
%include "interface/curv.i"	
%include "interface/hist.i"	
