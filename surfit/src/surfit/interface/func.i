
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
#include "surf_tcl.h"
#include "mask_tcl.h"

#include "surfs_tcl.h"
%}

namespace surfit {

surfit::boolvec * surface(const char * surface_name = "*");
surfit::boolvec * surface_add(REAL weight, const char * surface_name = "*");
surfit::boolvec * surface_leq(const char * surface_name = "*", REAL penalty_factor = 0);
surfit::boolvec * surface_geq(const char * surface_name = "*", REAL penalty_factor = 0);
surfit::boolvec * trend(REAL D1 = 1, REAL D2 = 2, const char * surface_name = "*");
surfit::boolvec * trend_add(REAL weight, REAL D1 = 1, REAL D2 = 0, const char * surface_name = "*");
surfit::boolvec * mask(const char * val, const char * mask_name = "*");
surfit::boolvec * mask_add(REAL val, REAL weigh = 1, const char * mask_name = "*");
surfit::boolvec * mask_leq(REAL value, const char * mask_name = "*", REAL penalty_factor = 0);
surfit::boolvec * mask_geq(REAL value, const char * mask_name = "*", REAL penalty_factor = 0);
surfit::boolvec * mask_surf(const char * surf_name = "*", const char * mask_name = "*");
surfit::boolvec * mask_surf_add(const char * surf_name = "*", REAL weight = 1, const char * mask_name = "*");
surfit::boolvec * mask_surf_leq(const char * surf_name = "*", const char * mask_name = "*", REAL penalty_factor = 0);
surfit::boolvec * mask_surf_geq(const char * surf_name = "*", const char * mask_name = "*", REAL penalty_factor = 0);
surfit::boolvec * mask_mean(REAL mean, const char * mask_name = "*", REAL penalty_factor = -2);
surfit::boolvec * mask_wmean(REAL mean, const char * mask_name = "*", const char * surf_name = "*", REAL penalty_factor = -2);
surfit::boolvec * mask_completer(const char * mask_name = "*", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);
surfit::boolvec * mask_completer_add(REAL weight = 1, const char * mask_name = "*", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);

//
// surf
//

// save_load
surfit::boolvec * surf_load(const char * filename, const char * surfname = NULL);
surfit::boolvec * surf_save(const char * filename, const char * surface_name = "*");
surfit::boolvec * surf_plot(const char * filename, const char * surface_name = "*", bool draw_isos = true, size_t number_of_levels = 16);
// MATH OPERATIONS
surfit::vec * surf_getValue(REAL x, REAL y, const char * surface_name = "*");
surfit::vec * surf_getValueIJ(int I, int J, const char * surface_name = "*");
surfit::boolvec * surf_resid(const char * filename, const char * surface_name = "*", const char * pnts_pos = "*");
surfit::vec * surf_D1(const char * surface_name = "*");
surfit::vec * surf_D2(const char * surface_name = "*");
surfit::boolvec * surf_gradient(const char * surface_name = "*", const char * newname = NULL);
surfit::boolvec * surf_project(const char * surface_name = "*", const char * newname = NULL);
void surf_add_noise(REAL std, const char * surface_name = "*");
surfit::vec * surf_minz(const char * surface_name = "*");
surfit::vec * surf_area_minz(const char * area_name = "*", const char * surface_name = "*");
surfit::vec * surf_maxz(const char * surface_name = "*");
surfit::vec * surf_area_maxz(const char * area_name = "*", const char * surface_name = "*");
surfit::vec * surf_mean(const char * surface_name = "*");
surfit::vec * surf_area_mean(const char * area_name = "*", const char * surface_name = "*");
surfit::vec * surf_mask_mean(const char * mask_name = "*", const char * surface_name = "*");
surfit::vec * surf_wmean(const char * wsurface_name = "*", const char * surface_name = "*");
surfit::vec * surf_area_wmean(const char * area_name = "*", const char * wsurface_name = "*", const char * surface_name = "*");
surfit::vec * surf_mask_wmean(const char * mask_name = "*", const char * wsurface_name = "*", const char * surface_name = "*");
surfit::vec * surf_std(REAL mean, const char * surface_name = "*");
surfit::vec * surf_sum(const char * surface_name = "*");
surfit::vec * surf_sum_area(const char * area_pos = "*",  const char * surface_name = "*");
surfit::intvec * surf_cells_in_area(const char * curv_pos = "*",  const char * surface_name = "*");
surfit::boolvec * surf_plus(const char * surface1_name, const char * surface2_name);
surfit::boolvec * surf_minus(const char * surface1_name, const char * surface2_name);
surfit::boolvec * surf_mult(const char * surface1_name, const char * surface2_name);
surfit::boolvec * surf_div(const char * surface1_name, const char * surface2_name);
surfit::boolvec * surf_set(const char * surface1_name, const char * surface2_name);
surfit::boolvec * surf_plus_area(const char * surface1_name, const char * area_name, const char * surface2_name);
surfit::boolvec * surf_minus_area(const char * surface1_name, const char * area_name, const char * surface2_name);
surfit::boolvec * surf_mult_area(const char * surface1_name, const char * area_name, const char * surface2_name);
surfit::boolvec * surf_div_area(const char * surface1_name, const char * area_name, const char * surface2_name);
surfit::boolvec * surf_set_area(const char * surface1_name, const char * area_name, const char * surface2_name);
surfit::boolvec * surf_plus_value(REAL val, const char * surface_name = "*");
surfit::boolvec * surf_minus_value(REAL val, const char * surface_name = "*");
surfit::boolvec * surf_mult_value(REAL val, const char * surface_name = "*");
surfit::boolvec * surf_div_value(REAL val, const char * surface_name = "*");
surfit::boolvec * surf_set_value(REAL val, const char * surface_name = "*");
surfit::boolvec * surf_plus_value_area(REAL val, const char * area_name = "*", const char * surface_name = "*");
surfit::boolvec * surf_minus_value_area(REAL val, const char * area_name = "*", const char * surface_name = "*");
surfit::boolvec * surf_mult_value_area(REAL val, const char * area_name = "*", const char * surface_name = "*");
surfit::boolvec * surf_div_value_area(REAL val, const char * area_name = "*", const char * surface_name = "*");
surfit::boolvec * surf_set_value_area(const char * val, const char * area_name = "*", const char * surface_name = "*");

surfit::boolvec * surf_filter_by_mask(const char * surface_name = "*", const char * mask_name = "*");
surfit::boolvec * surf_filter_in_area(const char * surface_name = "*", const char * area_name = "*");
surfit::boolvec * surf_filter_out_area(const char * surface_name = "*", const char * area_name = "*");
surfit::boolvec * surf_filter_by_surf(REAL eps, const char * surface1_name = "*", const char * surface2_name = "*");
surfit::boolvec * surf_swapxy(const char * surface_name = "*");

// WAVELETS SECTION
surfit::intvec * surf_get_details_level(const char * surface_name = "*");
surfit::boolvec * surf_decomp(const char * surface_name = "*");
surfit::boolvec * surf_auto_decomp(REAL eps, const char * surface_name = "*");
surfit::boolvec * surf_recons(const char * surface_name = "*");
surfit::boolvec * surf_full_recons(const char * surface_name = "*");
// CONVERTING
surfit::boolvec * surf_to_pnts(const char * surface_name = "*");
surfit::boolvec * surf_to_mask(REAL true_from, REAL true_to, const char * surface_name = "*");
// OTHER
surfit::intvec * surf_getCountX(const char * surface_name = "*");
surfit::intvec * surf_getCountY(const char * surface_name = "*");
surfit::vec * surf_getStepX(const char * surface_name = "*");
surfit::vec * surf_getStepY(const char * surface_name = "*");
surfit::boolvec * surf_undef(REAL new_undef_value, const char * surface_name = "*");
void surf_info(const char * surface_name = "*");
surfit::strvec * surf_getName(const char * surface_name = "*");
const char * surf_getNameAt(int pos);
surfit::intvec * surf_getId(const char * surface_name = "*");
surfit::boolvec * surf_setName(const char * new_name, const char * surface_name = "*");
void surf_del(const char * surface_name = "*");
int surf_size();
void surfs_info();
surfit::boolvec * surf_trace_cntr(const char * surface_name = "*", REAL step = FLT_MAX, REAL from = FLT_MAX, REAL to = FLT_MAX);

//
// mask
//

//save and load
surfit::boolvec * mask_load(const char * filename, const char * maskname = NULL);
surfit::boolvec * mask_save(const char * filename, const char * mask_name = "*");
//
// math
//
surfit::boolvec * mask_getValue(REAL x, REAL y, const char * mask_name = "*");
void mask_and(const char * mask1_name = "*", const char * mask2_name = "*");
void mask_not(const char * mask1_name = "*", const char * mask2_name = "*");
void mask_or (const char * mask1_name = "*", const char * mask2_name = "*");
void mask_xor(const char * mask1_name = "*", const char * mask2_name = "*");
// CONVERTING
void mask_to_surf(const char * mask_name = "*");
// OTHER
void mask_from_surf(const char * surface_name = "*");
surfit::boolvec * mask_apply_to_surf(const char * mask_name = "*", const char * surface_name = "*");
surfit::strvec * mask_getName(const char * mask_name = "*");
const char * mask_getNameAt(int pos);
surfit::intvec * mask_getId(const char * mask_name = "*");
void mask_setName(const char * new_name, const char * mask_name = "*");
void mask_del(const char * mask_name = "*");
int mask_size();
void mask_info(const char * mask_name = "*");


}; // namespace surfit;

