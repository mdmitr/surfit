
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
// surftionals
//
surfit::boolvec * points(const char * points_name = "*");
surfit::boolvec * points_add(REAL weight = 1, const char * points_name = "*");
surfit::boolvec * points_leq(const char * points_name = "*", REAL penalty_factor = 0);
surfit::boolvec * points_geq(const char * points_name = "*", REAL penalty_factor = 0);


//
// points
//

//save load
surfit::boolvec * pnts_load(const char * filename, const char * pntsname=NULL);
surfit::boolvec * pnts_read(const char * filename, const char * pntsname=NULL, int col1=1, int col2=2, int col3=3, int col4=0, const char *delimiter=" \t", int skip_lines = 0, int grow_by=250);
surfit::boolvec * pnts_save(const char * filename, const char * points_name = "*");
surfit::boolvec * pnts_write(const char * filename, const char * points_name = "*", const char * delimiter = "\t");
// math
surfit::boolvec * pnts_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name = "*");
surfit::boolvec * pnts_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name = "*");
surfit::boolvec * pnts_rotate(REAL centerX, REAL centerY, REAL angle, const char * points_name = "*");
surfit::boolvec * pnts_filter_by_mask(const char * points_name = "*", const char * mask_name = "*");
surfit::boolvec * pnts_filter_in_area(const char * points_name = "*", const char * curv_pos = "*");
surfit::boolvec * pnts_filter_out_area(const char * points_name = "*", const char * curv_pos = "*");
surfit::boolvec * pnts_filter_by_surf(REAL eps, const char * points_name = "*", const char * surf_name = "*");
surfit::boolvec * pnts_update_by_surf(const char * points_name = "*", const char * surf_name = "*");
surfit::vec * pnts_minx(const char * points_name = "*");
surfit::vec * pnts_maxx(const char * points_name = "*");
surfit::vec * pnts_miny(const char * points_name = "*");
surfit::vec * pnts_maxy(const char * points_name = "*");
surfit::vec * pnts_minz(const char * points_name = "*");
surfit::vec * pnts_maxz(const char * points_name = "*");
surfit::vec * pnts_mean(const char * points_name = "*");
surfit::vec * pnts_std(REAL mean, const char * points_name = "*");
surfit::boolvec * pnts_abs(const char * points_name = "*");
surfit::boolvec * pnts_add_noise(REAL std, const char * points_name = "*");
surfit::boolvec * pnts_plus(const char * points_name1, const char * points_name2);
surfit::boolvec * pnts_minus(const char * points_name1, const char * points_name2);
surfit::boolvec * pnts_mult(const char * points_name1, const char * points_name2);
surfit::boolvec * pnts_div(const char * points_name1, const char * points_name2);
surfit::boolvec * pnts_set(const char * points_name1, const char * points_name2);
surfit::boolvec * pnts_plus_real(REAL val, const char * points_name = "*");
surfit::boolvec * pnts_minus_real(REAL val, const char * points_name = "*");
surfit::boolvec * pnts_mult_real(REAL val, const char * points_name = "*");
surfit::boolvec * pnts_div_real(REAL val, const char * points_name = "*");
surfit::boolvec * pnts_set_real(REAL val, const char * points_name = "*");
surfit::boolvec * pnts_plus_surf(const char * points_name = "*", const char * surf_name = "*");
surfit::boolvec * pnts_minus_surf(const char * points_name = "*", const char * surf_name = "*");
surfit::boolvec * pnts_mult_surf(const char * points_name = "*", const char * surf_name = "*");
surfit::boolvec * pnts_div_surf(const char * points_name = "*", const char * surf_name = "*");
surfit::boolvec * pnts_set_surf(const char * points_name = "*", const char * surf_name = "*");
surfit::boolvec * pnts_concat(const char * points_name1, const char * points_name2);

// other
surfit::boolvec * pnts_to_cntrs(const char * points_name = "*");
surfit::intvec * pnts_getCount(const char * points_name = "*");
surfit::strvec * pnts_getName(const char * points_name = "*");
const char * pnts_getNameAt(int pos);
surfit::intvec * pnts_getId(const char * points_name = "*");
surfit::boolvec * pnts_setName(const char * new_name, const char * points_name = "*");
void pnts_del(const char * points_name = "*");
int pnts_size();
void pnts_info();

}; // namespace surfit;

