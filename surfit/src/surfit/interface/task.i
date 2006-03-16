
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
#include "pnts_tcl.h"
#include "f_points_tcl.h"
%}

namespace surfit {

class points;

//
// functionals
//
bool points(const char * points_name_or_position = "0");
bool points_add(REAL weight = 1, const char * points_name_or_position = "0");
bool points_leq(const char * points_name_or_position = "0", REAL mult = 0.001);
bool points_geq(const char * points_name_or_position = "0", REAL mult = 0.001);


//
// points
//

//save load
bool pnts_load(const char *filename, const char *pntsname=NULL);
void pnts_read(const char *filename, const char *pntsname=NULL, int col1=1, int col2=2, int col3=3, int col4=0, const char *delimiter=" \t", int skip_lines = 0, int grow_by=250);
bool pnts_save(const char * filename, const char * points_name_or_position = "0");
bool pnts_write(const char * filename, const char * delimiter = "\t", const char * points_name_or_position = "0");
// math
bool pnts_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name_or_position = "0");
bool pnts_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name_or_position = "0");
bool pnts_rotate(REAL centerX, REAL centerY, REAL angle, const char * points_name_or_position = "0");
bool pnts_filter_by_mask(const char * points_name_or_position = "0", const char * mask_name_or_position = "0");
bool pnts_filter_in_area(const char * points_name_or_position = "0", const char * curv_pos = "0");
bool pnts_filter_out_area(const char * points_name_or_position = "0", const char * curv_pos = "0");
bool pnts_filter_by_func(REAL eps, const char * points_name_or_position = "0", const char * func_name_or_position = "0");
bool pnts_update_by_func(const char * points_name_or_position = "0", const char * func_name_or_position = "0");
REAL pnts_minx(const char * points_name_or_position = "0");
REAL pnts_maxx(const char * points_name_or_position = "0");
REAL pnts_miny(const char * points_name_or_position = "0");
REAL pnts_maxy(const char * points_name_or_position = "0");
REAL pnts_minz(const char * points_name_or_position = "0");
REAL pnts_maxz(const char * points_name_or_position = "0");
bool pnts_add_noise(REAL std, const char * points_name_or_position = "0");
REAL pnts_mean(const char * points_name_or_position = "0");
REAL pnts_std(REAL mean, const char * points_name_or_position = "0");
bool pnts_plus(const char * points_name_or_position1, const char * points_name_or_position2);
bool pnts_minus(const char * points_name_or_position1, const char * points_name_or_position2);
bool pnts_mult(const char * points_name_or_position1, const char * points_name_or_position2);
bool pnts_div(const char * points_name_or_position1, const char * points_name_or_position2);
bool pnts_set(const char * points_name_or_position1, const char * points_name_or_position2);
bool pnts_plus_real(REAL val, const char * points_name_or_position = "0");
bool pnts_minus_real(REAL val, const char * points_name_or_position = "0");
bool pnts_mult_real(REAL val, const char * points_name_or_position = "0");
bool pnts_div_real(REAL val, const char * points_name_or_position = "0");
bool pnts_set_real(REAL val, const char * points_name_or_position = "0");
bool pnts_plus_func(const char * points_name_or_position = "0", const char * func_name_or_position = "0");
bool pnts_minus_func(const char * points_name_or_position = "0", const char * func_name_or_position = "0");
bool pnts_mult_func(const char * points_name_or_position = "0", const char * func_name_or_position = "0");
bool pnts_div_func(const char * points_name_or_position = "0", const char * func_name_or_position = "0");
bool pnts_set_func(const char * points_name_or_position = "0", const char * func_name_or_position = "0");

// other
int pnts_getCount(const char * points_name_or_position = "0");
const char * pnts_getName(const char * points_name_or_position = "0");
bool pnts_setName(const char * new_name, const char * points_name_or_position = "0");
bool pnts_delall();
bool pnts_del(const char * points_name_or_position = "0");
bool pnts_concat(const char * points_name_or_position1, const char * points_name_or_position2);
int pnts_size();
void pnts_info();

}; // namespace surfit;

