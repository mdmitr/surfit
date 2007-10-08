
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

#include "curvs_tcl.h"
%}

namespace surfit {

surfit::boolvec * fault(const char * curv_name = "*");

surfit::boolvec * curve(REAL value, const char * curv_name = "*");
surfit::boolvec * curve_add(REAL value, REAL weight, const char * curv_name = "*");
surfit::boolvec * curve_leq(REAL value, const char * curv_name = "*", REAL penalty_factor = 0);
surfit::boolvec * curve_geq(REAL value, const char * curv_name = "*", REAL penalty_factor = 0);
surfit::boolvec * curve_surf(const char * surf_name = "*", const char * curv_name = "*");
surfit::boolvec * curve_surf_add(const char * surf_name = "*", REAL weight = 1, const char * curv_name = "*");
surfit::boolvec * curve_surf_leq(const char * surf_name = "*", const char * curv_name = "*", REAL penalty_factor = 0);
surfit::boolvec * curve_surf_geq(const char * surf_name = "*", const char * curv_name = "*", REAL penalty_factor = 0);

surfit::boolvec * area(const char * value = "undef", const char * area_name = "*", int inside = 1);
surfit::boolvec * area_add(REAL value, REAL weight, const char * area_name = "*", int inside = 1);
surfit::boolvec * area_leq(REAL value, const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);
surfit::boolvec * area_geq(REAL value, const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);
surfit::boolvec * area_surf(const char * surf_name = "*", const char * area_name = "*", int inside = 1);
surfit::boolvec * area_surf_add(const char * surf_name = "*", REAL weight = 1, const char * area_name = "*", int inside = 1);
surfit::boolvec * area_surf_leq(const char * surf_name = "*", const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);
surfit::boolvec * area_surf_geq(const char * surf_name = "*", const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);
surfit::boolvec * area_mean(REAL mean, const char * area_name = "*", REAL penalty_factor = -2, int inside = 1);
surfit::boolvec * area_wmean(REAL mean, const char * area_name = "*", const char * surf_name = "*", REAL penalty_factor = -2, int inside = 1);
surfit::boolvec * area_completer(const char * area_name = "*", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);
surfit::boolvec * area_completer_add(REAL weight = 1, const char * area_name = "*", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);
surfit::boolvec * area_hist(const char * area_name = "*", const char * histogram_name = "*", REAL penalty_factor = -1, int inside = 1);

surfit::boolvec * contour(const char * cntr_name = "*");
surfit::boolvec * contour_add(REAL weight, const char * cntr_name = "*");
surfit::boolvec * contour_leq(const char * cntr_name = "*", REAL penalty_factor = 0);
surfit::boolvec * contour_geq(const char * cntr_name = "*", REAL penalty_factor = 0);
surfit::boolvec * smooth_contour(const char * cntr_name = "*", REAL penalty_factor = 0);
surfit::boolvec * smooth_contour_add(REAL weight = 50, const char * cntr_name = "*");
//
// 2D
//

class cntr;
class curv;
class area;

//
// Curves
//

//saveload
surfit::boolvec * curv_read(const char * filename, const char * curvname=NULL, 
							int col1=1, int col2=2,
							const char * delimiters=" \t", int skip_lines = 0, int grow_by=250);
surfit::boolvec * curv_load(const char * filename, const char * curvname = NULL);

surfit::boolvec * curv_write(const char * filename, const char * curv_name = "*", const char * delimiter = "\t");
surfit::boolvec * curv_save(const char * filename, const char * curv_name = "*");

// other
surfit::strvec * curv_getName(const char * curv_name = "*");
const char * curv_getNameAt(int pos);
surfit::intvec * curv_getId(const char * curv_name = "*");
surfit::boolvec * curv_setName(const char * new_name, const char * curv_name = "*");
void curv_del(const char * curv_name = "*");
int curv_size();
void curvs_info();

//
// Contours
//

//saveload
surfit::boolvec * cntr_read(const char * filename, const char * cntrname, 
							int col1=1, int col2=2, int col3=3,
						    const char * delimiter=" \t", int skip_lines = 0, int grow_by=250);
surfit::boolvec * cntr_load(const char * filename, const char * cntrname = NULL);
surfit::boolvec * cntr_write(const char * filename, const char * cntr_name = "*", const char * delimiter = "\t");
surfit::boolvec * cntr_save(const char * filename, const char * cntr_name = "*");
// math
surfit::boolvec * cntr_plus_real(REAL value, const char * cntr_name = "*");
surfit::boolvec * cntr_minus_real(REAL value, const char * cntr_name = "*");
surfit::boolvec * cntr_mult_real(REAL value, const char * cntr_name = "*");
surfit::boolvec * cntr_div_real(REAL value, const char * cntr_name = "*");
// convers
surfit::boolvec * cntr_to_curv(const char * cntr_name = "*");
surfit::boolvec * cntr_to_pnts(REAL step, const char * cntr_name = "*");
// other
surfit::strvec * cntr_getName(const char * cntr_name = "*");
const char * cntr_getNameAt(int pos);
surfit::intvec * cntr_getId(const char * cntr_name = "*");
surfit::boolvec * cntr_setName(const char * new_name, const char * cntr_name = "*");
void cntr_del(const char * cntr_name_or_position);
int cntr_size();
void cntrs_info();
surfit::boolvec * cntr_smooth(const char * cntr_name = "*", size_t cnt = 1);

//
// areas
//
surfit::boolvec * area_read(const char * filename, const char * areaname=NULL, 
     					    int col1=1, int col2=2,
						    const char * delimiter=" \t", int skip_lines = 0, int grow_by=250);
surfit::boolvec * area_load(const char * filename, const char * areaname = NULL);
surfit::boolvec * area_write(const char * filename, const char * area_name = "*", const char * delimiter = "\t");
surfit::boolvec * area_save(const char * filename, const char * area_name = "*");

// other
surfit::strvec * area_getName(const char * area_name = "*");
const char * area_getNameAt(int pos);
surfit::intvec * area_getId(const char * area_name = "*");
surfit::boolvec * area_setName(const char * new_name, const char * area_name = "*");
void area_del(const char * area_name = "*");
int area_size();
surfit::boolvec * area_invert(const char * area_name = "*");
void areas_info();

}; // namespace surfit

