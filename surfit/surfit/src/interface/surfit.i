
/* File : surfit.i */

%module surfit
%{

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
#include "real.h"
#include "variables_internal.h"
#include "variables_tcl.h"
#include "fileio.h"
#include "color_scale.h"
#include "file_manager.h"
#include "completer_tcl.h"
#include "license.h"
#include "fill_with_tcl.h"
%}

%init 
%{
surfit::surfit_init_variables(interp);
%}

namespace surfit {

//
%exception {
        try {
                $action
        }
        catch(...) {
                return TCL_ERROR;
        }
};


%include "real.h"

extern float tol; 
extern int datafile_mode;
extern int priority;
extern REAL undef_value;

extern REAL sor_omega;
extern REAL ssor_omega;

extern char * map_name;

void rw_mode_set(const char * newmode);
const char * rw_mode_get();

void clear_data();
void mem_info();

void putlog(const char * str);

void set_color_scale(REAL from, REAL to, REAL step,
                     int r1, int g1, int b1,
		     int r2, int g2, int b2);

void set_default_color_scale();

void file_load(const char * filename);
bool file_save(const char * filename);

bool completer_set(REAL D1, REAL D2);


//
// fill_with
//
void fill_with_set(REAL value = FLT_MAX);
bool fill_with_unload();
bool fill_with_check();


// license stuff
void show_w();
void show_c();

}; // namespace surfit;

%include "interface/fileio.i"
%include "interface/task.i"
%include "interface/geom.i"
%include "interface/solve.i"
%include "interface/func.i"
%include "interface/mrf.i"	
%include "interface/curv.i"	
%include "interface/draw.i"