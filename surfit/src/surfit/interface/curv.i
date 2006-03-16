
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
%{
#include "curv_tcl.h"
#include "cntr_tcl.h"
#include "area_tcl.h"
#include "grid_line_tcl.h"

#include "curvs_tcl.h"
%}

namespace surfit {

bool fault_add(const char * curv_name_or_position = "0");
bool curve(REAL value, const char * curv_name_or_position = "0");
bool curve_add(REAL value, REAL weight, const char * curv_name_or_position = "0");
bool curve_leq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);
bool curve_geq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);
bool area(const char * value = "undef", const char * area_name_or_position = "0", int inside = 1);
bool area_add(REAL value, REAL weight, const char * area_name_or_position = "0", int inside = 1);
bool area_leq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
bool area_geq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
bool area_func_leq(const char * func_name_or_position = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
bool area_func_geq(const char * func_name_or_position = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
bool area_mean(REAL mean, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
bool area_wmean(REAL mean, const char * area_name_or_position = "0", const char * func_name_or_position = "0", REAL mult = 0.001, int inside = 1);
bool contour(const char * cntr_name_or_position = "0");
bool contour_add(REAL weight, const char * cntr_name_or_position = "0");
bool contour_leq(const char * cntr_name_or_position = "0", REAL mult = 0.001);
bool contour_geq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

//
// 2D
//

class cntr;
class curv;
class area;
class grid_line;

//
// Curves
//

//saveload
bool curv_read(const char * filename, const char * curvname=NULL, 
               int col1=1, int col2=2,
	       const char * delimiters=" \t", int skip_lines = 0, int grow_by=250);
bool curv_read_bln(const char * filename);
bool curv_write(const char * filename, const char * curv_name_or_position = "0", const char * delimiter = "\t");
bool curv_write_bln(const char * filename, const char * curv_name_or_position = "0", int orient = 1);
bool curv_save(const char * filename, const char * curv_name_or_position = "0");
bool curv_load(const char * filename, const char * curvname = NULL);
// other
const char * curv_getName(const char * curv_name_or_position = "0");
bool curv_setName(const char * new_name, const char * curv_name_or_position = "0");
bool curv_delall();
bool curv_del(const char * curv_name_or_position = "0");
int curv_size();
void curvs_info();

//
// Contours
//

//saveload
bool cntr_read(const char * filename, const char * cntrname, 
		       int col1=1, int col2=2, int col3=3,
		       const char * delimiter=" \t", int skip_lines = 0, int grow_by=250);
bool cntr_write(const char * filename, const char * cntr_name_or_position = "0", const char * delimiter = "\t");
bool cntr_save(const char * filename, const char * cntr_name_or_position = "0");
bool cntr_load(const char * filename, const char * cntrname = NULL);
// math
bool cntr_plus_real(REAL value, const char * cntr_name_or_position = "0");
bool cntr_minus_real(REAL value, const char * cntr_name_or_position = "0");
bool cntr_mult_real(REAL value, const char * cntr_name_or_position = "0");
bool cntr_div_real(REAL value, const char * cntr_name_or_position = "0");
// convers
bool cntr_to_curv(const char * cntr_name_or_position = "0");
// other
const char * cntr_getName(const char * cntr_name_or_position = "0");
bool cntr_setName(const char * new_name, const char * cntr_name_or_position = "0");
bool cntr_delall();
bool cntr_del(const char * cntr_name_or_position);
int cntr_size();
void cntrs_info();

//
// areas
//
bool area_read(const char * filename, const char * areaname=NULL, 
     	       int col1=1, int col2=2,
	       const char * delimiter=" \t", int skip_lines = 0, int grow_by=250);
bool area_read_bln(const char * filename, const char * areaname = NULL);
bool area_write(const char * filename, const char * area_name_or_position = "0", const char * delimiter = "\t");
bool area_write_bln(const char * filename, const char * area_name_or_position = "0", int orient = 1);
bool area_save(const char * filename, const char * area_name_or_position = "0");
bool area_load(const char * filename, const char * areaname = NULL);
// other
const char * area_getName(const char * area_name_or_position = "0");
bool area_setName(const char * new_name, const char * area_name_or_position = "0");
bool area_delall();
bool area_del(const char * area_name_or_position = "0");
int area_size();
bool area_invert(const char * area_name_or_position = "0");
void areas_info();

//
// Grid lines
//

bool grid_line_check();
bool grid_line_write(const char * filename, const char * delimiter = "\t");
bool grid_line_save(const char * filename, const char * grid_linename = NULL);
bool grid_line_unload();
bool trace_grid_line();

}; // namespace surfit

