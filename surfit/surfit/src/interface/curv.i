
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
%{
#include "curv_tcl.h"
#include "curvs.h"
#include "flt_tcl.h"
#include "flts.h"
#include "iso_tcl.h"
#include "isos.h"
#include "wiso_tcl.h"
#include "wisos.h"
#include "area_tcl.h"
#include "areas.h"
#include "warea_tcl.h"
#include "wareas.h"
#include "cntr_tcl.h"
#include "cntrs.h"
#include "wcntr_tcl.h"
#include "wcntrs.h"
#include "grid_line_tcl.h"
%}

namespace surfit {

//
// 2D
//

class flt;
class iso;
class wiso;
class area;
class warea;
class cntr;
class wcntr;
class curv;
class grid_line;

//
// Curves
//

//saveload
bool curv_read(const char *filename, const char *curvname, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool curv_write(const char *filename, const char *delimiter);
bool curv_save(const char *filename, const char *curvname=NULL);
bool curv_load(const char *filename, const char *curvname=NULL);
bool curv_unload();
//convers
bool curv_to_iso(REAL value);
bool curv_to_isos(REAL value);
bool curv_to_wiso(REAL value, REAL weight);
bool curv_to_wisos(REAL value, REAL weight);
bool curv_to_flt();
bool curv_to_flts();
bool curv_to_area(REAL value);
bool curv_to_areas(REAL value);
bool curv_to_warea(REAL value, REAL weight);
bool curv_to_wareas(REAL value, REAL weight);
//other
bool curv_check();
bool curv_set(curv *contour);
bool curv_name(const char *name=NULL, curv *crv=NULL);
//operations with curv collections
bool curvs_delall();
bool curvs_del(int pos);
bool curvs_read(const char *filename, const char *curvname=NULL, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool curvs_load(const char *filename, const char *curvname=NULL);
curv * curvs_at(int pos);
curv * curvs_first();
curv * curvs_last();
int curvs_size();
int curvs_info();

//
// Faults
//

//saveload
bool flt_read(const char *filename, const char *fltname, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool flt_write(const char *filename, const char *delimiter);
bool flt_save(const char *filename, const char *fltname=NULL);
bool flt_load(const char *filename, const char *fltname=NULL);
bool flt_unload();
//convers
bool flt_to_curv();
bool flt_to_curvs();
bool flt_to_grid_line();
bool flt_to_flts();
//other
bool flt_check();
bool flt_set(flt *fault);
bool flt_name(const char *new_name=NULL, flt *fault=NULL);
//operations with flt collections
bool flts_delall();
bool flts_del(int pos);
bool flts_read(const char *filename, const char *fltname, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool flts_load(const char *filename, const char *fltname=NULL);
flt * flts_at(int pos);
flt * flts_first();
flt * flts_last();
int flts_size();
int flts_info();

//
// Isolines
//

//saveload
bool iso_read(const char *filename, const char *isoname, REAL value, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool iso_write(const char *filename, const char *delimiter);
bool iso_save(const char *filename, const char *isoname=NULL);
bool iso_load(const char *filename, const char *isoname=NULL);
bool iso_unload();
//convers
bool iso_to_wiso(REAL weight);
bool iso_to_wisos(REAL weight);
bool iso_to_curv();
bool iso_to_curvs();
bool iso_to_isos();
//other
bool iso_check();
bool iso_value(REAL value);
bool iso_set(iso *isoline);
bool iso_name(const char *new_name=NULL, iso *isoline=NULL);
//operations with iso collections
bool isos_delall();
bool isos_del(int pos);
bool isos_read(const char *filename, const char *isoname, REAL value, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool isos_load(const char *filename, const char *isoname=NULL);
iso * isos_at(int pos);
iso * isos_first();
iso * isos_last();
int isos_size();
int isos_info();

//
// WIsolines
//

//saveload
bool wiso_read(const char *filename, const char *isoname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool wiso_write(const char *filename, const char *delimiter);
bool wiso_save(const char *filename, const char *isoname=NULL);
bool wiso_load(const char *filename, const char *isoname=NULL);
bool wiso_unload();
//convers
bool wiso_to_iso();
bool wiso_to_isos();
bool wiso_to_curv();
bool wiso_to_curvs();
bool wiso_to_wisos();
//other
bool wiso_check();
bool wiso_value(REAL value);
bool wiso_weight(REAL weight);
bool wiso_set(wiso *wisoline);
bool wiso_name(const char *name=NULL, wiso *wisoline=NULL);
//operations with wiso collections
bool wisos_delall();
bool wisos_del(int pos);
bool wisos_read(const char *filename, const char *wisoname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool wisos_load(const char *filename, const char *wisoname=NULL);
wiso * wisos_at(int pos);
wiso * wisos_first();
wiso * wisos_last();
int wisos_size();
int wisos_info();

//
// Areas
//

//saveload
bool area_read(const char *filename, const char *areaname, REAL value=undef_value, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool area_write(const char *filename, const char *delimiter=" ");
bool area_save(const char *filename, const char *areaname=NULL);
bool area_load(const char *filename, const char *areaname=NULL);
bool area_unload();
//convers
bool area_to_curv();
bool area_to_curvs();
bool area_to_areas();
//other
bool area_check();
bool area_value(REAL value);
bool area_value_undef();
bool area_set(area *arealine);
bool area_name(const char *new_name=NULL, area *arealine=NULL);
//operations with area collections
bool areas_delall();
bool areas_del(int pos);
bool areas_read(const char *filename, const char *areaname, REAL value=undef_value, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool areas_load(const char *filename, const char *areaname=NULL);
area * areas_at(int pos);
area * areas_first();
area * areas_last();
int areas_size();
int areas_info();

// 
// Wareas
//

//saveload
bool warea_read(const char *filename, const char *wareaname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool warea_write(const char *filename, const char *delimiter);
bool warea_save(const char *filename, const char *wareaname=NULL);
bool warea_load(const char *filename, const char *wareaname=NULL);
bool warea_unload();
bool warea_set(warea *warealine);
bool warea_name(const char *new_name=NULL, warea *warealine=NULL);
//convers
bool warea_to_area();
bool warea_to_areas();
bool warea_to_curv();
bool warea_to_curvs();
bool warea_to_wareas();
//other
bool warea_check();
bool warea_value(REAL value);
bool warea_weight(REAL weight);
//operations with warea collections
bool wareas_delall();
bool wareas_del(int pos);
bool wareas_read(const char *filename, const char *wareaname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=" ", int grow_by=250);
bool wareas_load(const char *filename, const char *wareaname=NULL);
warea * wareas_at(int pos);
warea * wareas_first();
warea * wareas_last();
int wareas_size();
int wareas_info();

//
// Contours
//

//saveload
bool cntr_read(const char *filename, const char *cntrname, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool cntr_write(const char *filename, const char *delimiter);
bool cntr_save(const char *filename, const char *cntrname=NULL);
bool cntr_load(const char *filename, const char *cntrname=NULL);
bool cntr_unload();
//math
bool cntr_plus_real(REAL value);
bool cntr_minus_real(REAL value);
bool cntr_mult_real(REAL value);
bool cntr_div_real(REAL value);
//conv
bool cntr_to_wcntr(REAL weight);
bool cntr_to_wcntrs(REAL weight);
bool cntr_to_curv();
bool cntr_to_curvs();
bool cntr_to_cntrs();
//other
bool cntr_check();
bool cntr_set(cntr *contour);
bool cntr_name(const char *new_name=NULL, cntr *contour=NULL);
//operations with cntr collections
bool cntrs_delall();
bool cntrs_del(int pos);
bool cntrs_read(const char *filename, const char *cntrname, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool cntrs_load(const char *filename, const char *cntrname=NULL);
cntr * cntrs_at(int pos);
cntr * cntrs_first();
cntr * cntrs_last();
int cntrs_size();
int cntrs_info();
bool cntrs_to_wcntrs(REAL weight);

//
// WContours
//

//saveload
bool wcntr_read(const char *filename, const char *cntrname, REAL weight, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool wcntr_write(const char *filename, const char *delimiter);
bool wcntr_save(const char *filename, const char *cntrname=NULL);
bool wcntr_load(const char *filename, const char *cntrname=NULL);
bool wcntr_unload();
//math
bool wcntr_plus_real(REAL value);
bool wcntr_minus_real(REAL value);
bool wcntr_mult_real(REAL value);
bool wcntr_div_real(REAL value);
//convers
bool wcntr_to_cntr();
bool wcntr_to_cntrs();
bool wcntr_to_curv();
bool wcntr_to_curvs();
bool wcntr_to_wcntrs();
//other
bool wcntr_check();
bool wcntr_set(wcntr *wcontour);
bool wcntr_name(const char *new_name=NULL, wcntr *wcontour=NULL);
//operations with wcntr collections
bool wcntrs_delall();
bool wcntrs_del(int pos);
bool wcntrs_read(const char *filename, const char *cntrname, REAL weight, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool wcntrs_load(const char *filename, const char *cntrname=NULL);
wcntr * wcntrs_at(int pos);
wcntr * wcntrs_first();
wcntr * wcntrs_last();
int wcntrs_size();
int wcntrs_info();

//
// Grid lines
//

bool grid_line_check();
bool grid_line_write(const char * filename, const char * delimiter = " ");
bool grid_line_save(const char * filename, const char * grid_linename = NULL);
bool grid_line_unload();
bool trace_grid_line();
bool grid_line_fill_true(REAL x, REAL y);

}; // namespace surfit

