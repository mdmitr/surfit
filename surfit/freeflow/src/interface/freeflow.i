
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

/* File : freeflow.i */

%module freeflow
%{
#include "real.h"
#include "flow_ie.h"
#include "flow.h"
#include "variables.h"
#include "flow_variables.h"
#include "ptask_tcl.h"
#include "ptasks.h"
#include "parea_tcl.h"
#include "pareas.h"
#include "pcntr_tcl.h"
#include "pcntrs.h"
#include "piso_tcl.h"
#include "pisos.h"
#include <float.h>
%}

%init 
%{
surfit::freeflow_init_variables(interp);
%}

namespace surfit {

%exception {
        try {
                $action
        }
        catch(...) {
                return TCL_ERROR;
        }
};

%include "../../surfit/src/real.h"

void flow();

class ptask;
class parea;
class pcntr;
class piso;

//
// ptask
//

//saveload
bool ptask_load(const char *filename, const char *ptaskname=NULL);
void ptask_read(const char *filename, const char *ptaskname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
void ptask_unload();
bool ptask_save(const char *filename, const char *ptaskname=NULL);
bool ptask_write(const char *filename, const char *delimiter=" ");
//math
void ptask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
void ptask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
bool ptask_filter_by_defarea();
bool ptask_filter_by_func(REAL eps);
bool ptask_update_by_func();
REAL ptask_minx();
REAL ptask_maxx();
REAL ptask_miny();
REAL ptask_maxy();
REAL ptask_minz();
REAL ptask_maxz();
bool ptask_add_noise(REAL std);
REAL ptask_mean();
REAL ptask_std(REAL mean);
bool ptask_plus(ptask *ptsk);
bool ptask_minus(ptask *ptsk);
bool ptask_mult(ptask *ptsk);
bool ptask_div(ptask *ptsk);
bool ptask_set(ptask *ptsk);
bool ptask_plus_real(REAL val);
bool ptask_minus_real(REAL val);	
bool ptask_mult_real(REAL val);
bool ptask_div_real(REAL val);
bool ptask_set_real(REAL val);
//conv
bool ptask_to_task();
bool ptask_to_tasks();
bool task_to_ptask();
bool task_to_ptasks();
bool ptask_to_ptasks();
//other
bool ptask_check();
int ptask_size();
bool ptask_name(const char *new_name);
//ptasks
bool ptasks_load(const char *filename, const char *ptaskname=NULL);
bool ptasks_read(const char *filename, const char *ptaskname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool ptasks_delall();
bool ptasks_del(int pos);
ptask * ptasks_at(int pos);
ptask * ptasks_first();
ptask * ptasks_last();
bool ptask_concat(ptask *ptsk);
int ptasks_size();
int ptasks_info();

//
// parea
//

//saveload
bool parea_read(const char *filename, const char *pareaname=NULL, REAL value=0, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool parea_write(const char *filename, const char *delimiter);
bool parea_save(const char *filename, const char *pareaname);
bool parea_load(const char *filename, const char *pareaname);
bool parea_unload();
//convers
bool parea_to_curv();
bool parea_to_curvs();
bool parea_to_pareas();
//other
bool parea_check();
bool parea_value(REAL value);
bool parea_set(parea *par);
bool parea_name(const char *new_name=NULL, parea *ar=NULL);
//operations with parea collections
bool pareas_delall();
bool pareas_del(int pos);
bool pareas_read(const char *filename, const char *pareaname=NULL, REAL value=0, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool pareas_load(const char *filename, const char *pareaname);
parea * pareas_at(int pos);
parea * pareas_first();
parea * pareas_last();
int pareas_size();
int pareas_info();

//
// PContours
//

//saveload 
bool pcntr_read(const char *filename, const char *pcntrname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool pcntr_write(const char *filename, const char *delimiter=" ");
bool pcntr_save(const char *filename, const char *pcntrname=NULL);
bool pcntr_load(const char *filename, const char *pcntrname=NULL);
bool pcntr_unload();
//math
bool pcntr_plus_real(REAL value);
bool pcntr_minus_real(REAL value);
bool pcntr_mult_real(REAL value);
bool pcntr_div_real(REAL value);
//convers
bool pcntr_to_curv();
bool pcntr_to_curvs();
bool pcntr_to_pcntrs();
//other
bool pcntr_check();
bool pcntr_set(pcntr *pcontour);
bool pcntr_name(const char *new_name=NULL, pcntr *contour=NULL);
//collections
bool pcntrs_delall();
bool pcntrs_del(int pos);
bool pcntrs_read(const char *filename, const char *pcntrname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool pcntrs_load(const char *filename, const char *pcntrname=NULL);
pcntr * pcntrs_at(int pos);
pcntr * pcntrs_first();
pcntr * pcntrs_last();
int pcntrs_size();
int pcntrs_info();

//
// PIso
//

//saveload
bool piso_read(const char *filename, const char *pisoname=NULL, REAL value=0, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool piso_write(const char *filename, const char *delimiter);
bool piso_save(const char *filename, const char *pisoname);
bool piso_load(const char *filename, const char *pisoname);
bool piso_unload();
//convers
bool piso_to_curv();
bool piso_to_curvs();
bool piso_to_pisos();
//other 
bool piso_check();
bool piso_value(REAL value);
bool piso_set(piso *pisoline);
bool piso_name(const char *new_name=NULL, piso *pisoline=NULL);
//collections
bool pisos_delall();
bool pisos_del(int pos);
bool pisos_read(const char *filename, const char *pisoname=NULL, REAL value=0, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool pisos_load(const char *filename, const char *pisoname);
piso * pisos_at(int pos);
piso * pisos_first();
piso * pisos_last();
int pisos_size();
int pisos_info();

}; // namespace surfit;

%include "interface/lcm.i"
%include "interface/flow_draw.i"