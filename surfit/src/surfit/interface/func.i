
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

bool surface(const char * surface_name_or_position = "0");
bool surface_add(REAL weight, const char * surface_name_or_position = "0");
bool surface_leq(const char * surface_name_or_position = "0", REAL mult = 0.001);
bool surface_geq(const char * surface_name_or_position = "0", REAL mult = 0.001);
bool trend(REAL D1 = 1, REAL D2 = 2, const char * surface_name_or_position = "0");
bool trend_add(REAL weight, REAL D1 = 1, REAL D2 = 0, const char * surface_name_or_position = "0");
bool mask(const char * val, const char * mask_name_or_position = "0");
bool mask_add(REAL val, REAL weigh = 1, const char * mask_name_or_position = "0");
bool mask_leq(REAL value, const char * mask_name_or_position = "0", REAL mult = 0.001);
bool mask_geq(REAL value, const char * mask_name_or_position = "0", REAL mult = 0.001);
bool mask_surf(const char * surf_name_or_position = "0", const char * mask_name_or_position = "0");
bool mask_surf_add(const char * surf_name_or_position = "0", REAL weight = 1, const char * mask_name_or_position = "0");
bool mask_surf_leq(const char * surf_name_or_position = "0", const char * mask_name_or_position = "0", REAL mult = 0.001);
bool mask_surf_geq(const char * surf_name_or_position = "0", const char * mask_name_or_position = "0", REAL mult = 0.001);
bool mask_mean(REAL mean, const char * mask_name_or_position = "0", REAL mult = 0.001);
bool mask_wmean(REAL mean, const char * mask_name_or_position = "0", const char * surf_name_or_position = "0", REAL mult = 0.001);
bool mask_completer(const char * mask_name_or_position = "0", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);
bool mask_completer_add(REAL weight = 1, const char * mask_name_or_position = "0", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);

//
// surf
//

// save_load
bool surf_load(const char * filename, const char * surfname = 0);
bool surf_save(const char * filename, const char * surface_name_or_position = "0");
// MATH OPERATIONS
REAL surf_getValue(REAL x, REAL y, const char * surface_name_or_position = "0");
REAL surf_getValueIJ(int I, int J, const char * surface_name_or_position = "0");
bool surf_resid(const char * filename, const char * surface_name_or_position = "0", const char * pnts_pos = "0");
REAL surf_D1(const char * surface_name_or_position = "0");
REAL surf_D2(const char * surface_name_or_position = "0");
bool surf_gradient(const char * newname, const char * surface_name_or_position = "0");
bool surf_project(const char * newname, const char * surface_name_or_position = "0");
bool surf_add_noise(REAL std, const char * surface_name_or_position = "0");
REAL surf_minz(const char * surface_name_or_position = "0");
REAL surf_area_minz(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_maxz(const char * surface_name_or_position = "0");
REAL surf_area_maxz(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_mean(const char * surface_name_or_position = "0");
REAL surf_area_mean(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_mask_mean(const char * mask_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_wmean(const char * surface_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_area_wmean(const char * area_name_or_position = "0", const char * wsurface_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_mask_wmean(const char * mask_name_or_position = "0", const char * wsurface_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_std(REAL mean, const char * surface_name_or_position = "0");
REAL surf_sum(const char * surface_name_or_position = "0");
bool surf_plus(const char * surface1_name_or_position, const char * surface2_name_or_position);
bool surf_plus_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
bool surf_minus(const char * surface1_name_or_position, const char * surface2_name_or_position);
bool surf_minus_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
bool surf_mult(const char * surface1_name_or_position, const char * surface2_name_or_position);
bool surf_mult_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
bool surf_div(const char * surface1_name_or_position, const char * surface2_name_or_position);
bool surf_div_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
bool surf_set(const char * surface1_name_or_position, const char * surface2_name_or_position);
bool surf_set_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
bool surf_plus_value(REAL val, const char * surface_name_or_position = "0");
bool surf_plus_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
bool surf_minus_value(REAL val, const char * surface_name_or_position = "0");
bool surf_minus_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
bool surf_mult_value(REAL val, const char * surface_name_or_position = "0");
bool surf_mult_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
bool surf_div_value(REAL val, const char * surface_name_or_position = "0");
bool surf_div_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
bool surf_set_value(REAL val, const char * surface_name_or_position = "0");
bool surf_set_value_area(const char * val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
REAL surf_sum_area(const char * curv_pos = "0",  const char * surface_name_or_position = "0");
int surf_cells_in_area(const char * curv_pos = "0",  const char * surface_name_or_position = "0");
bool surf_filter_by_mask(const char * surface_name_or_position = "0", const char * mask_name_or_position = "0");
void surf_filter_in_area(const char * surface_name_or_position = "0", const char * area_name_or_position = "0");
void surf_filter_out_area(const char * surface_name_or_position = "0", const char * area_name_or_position = "0");
bool surf_filter_by_surf(REAL eps, const char * surface1_name_or_position = "0", const char * surface2_name_or_position = "0");
bool surf_swapxy(const char * surface_name_or_position = "0");

// WAVELETS SECTION
int surf_get_details_level(const char * surface_name_or_position = "0");
bool surf_decomp(const char * surface_name_or_position = "0");
bool surf_auto_decomp(REAL eps, const char * surface_name_or_position = "0");
bool surf_recons(const char * surface_name_or_position = "0");
bool surf_full_recons(const char * surface_name_or_position = "0");
// CONVERTING
bool surf_to_pnts(const char * surface_name_or_position = "0");
bool surf_to_mask(REAL true_from, REAL true_to, const char * surface_name_or_position = "0");
// OTHER
int surf_getCountX(const char * surface_name_or_position = "0");
int surf_getCountY(const char * surface_name_or_position = "0");
REAL surf_getStepX(const char * surface_name_or_position = "0");
REAL surf_getStepY(const char * surface_name_or_position = "0");
bool surf_undef(REAL new_undef_value, const char * surface_name_or_position = "0");
void surf_info(const char * surface_name_or_position = "0");
const char * surf_getName(const char * surface_name_or_position = "0");
bool surf_setName(const char * new_name, const char * surface_name_or_position = "0");
bool surf_delall();
bool surf_del(const char * surface_name_or_position = "0");
int surf_size();
void surfs_info();

//
// mask
//

//save and load
bool mask_load(const char * filename, const char * maskname = "*");
bool mask_save(const char * filename, const char * mask_name_or_position = "0");
bool mask_save_grd(const char * filename, const char * mask_name_or_position = "0");
bool mask_save_xyz(const char * filename, const char * mask_name_or_position = "0");
//
// math
//
bool mask_getValue(REAL x, REAL y, const char * mask_name_or_position = "0");
void mask_and(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");
void mask_not(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");
void mask_or(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");
void mask_xor(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");
// CONVERTING
bool mask_to_surf(const char * mask_name_or_position = "0");
// OTHER
bool mask_by_surf(const char * surface_name_or_position = "0");
bool mask_apply_to_surf(const char * mask_name_or_position = "0", const char * surface_name_or_position = "0");
const char * mask_getName(const char * mask_name_or_position = "0");
bool mask_setName(const char * new_name, const char * mask_name_or_position = "0");
bool mask_delall();
bool mask_del(const char * mask_name_or_position = "0");
int mask_size();
void masks_info();


}; // namespace surfit;

