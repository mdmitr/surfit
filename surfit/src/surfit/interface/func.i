
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
#include "func_tcl.h"
#include "mask_tcl.h"

#include "funcs_tcl.h"
%}

namespace surfit {

bool func(const char * pos = "0");
bool func_add(REAL weight, const char * pos = "0");
bool func_leq(const char * pos = "0", REAL mult = 0.001);
bool func_geq(const char * pos = "0", REAL mult = 0.001);
bool trend(REAL D1 = 1, REAL D2 = 2, const char * pos = "0");
bool trend_add(REAL weight, REAL D1 = 1, REAL D2 = 2, const char * pos = "0");
bool mask(const char * Value, const char * pos = "0");

//
// func
//

// save_load
bool func_load(const char * filename, const char * funcname = 0);
bool func_load_grd(const char * filename, const char * funcname = 0);
bool func_save(const char * filename, const char * pos = "0");
bool func_save_grd(const char * filename, const char * pos = "0");
bool func_save_xyz(const char * filename, const char * pos = "0");
// MATH OPERATIONS
REAL func_getValue(REAL x, REAL y, const char * pos = "0");
REAL func_getValueIJ(int I, int J, const char * pos = "0");
bool func_resid(const char * filename, const char * func_pos = "0", const char * pnts_pos = "0");
REAL func_D1(const char * pos = "0");
REAL func_D2(const char * pos = "0");
bool func_gradient(const char * newname, const char * pos = "0");
bool func_project(const char * newname, const char * pos = "0");
bool func_project_with_faults(const char * newname, const char * pos = "0");
bool func_add_noise(REAL std, const char * pos = "0");
REAL func_minz(const char * pos = "0");
REAL func_area_minz(const char * area_pos = "0", const char * func_pos = "0");
REAL func_maxz(const char * pos = "0");
REAL func_area_maxz(const char * area_pos = "0", const char * func_pos = "0");
REAL func_mean(const char * pos = "0");
REAL func_area_mean(const char * area_pos = "0", const char * func_pos = "0");
REAL func_wmean(const char * wfunc_pos = "0", const char * pos = "0");
REAL func_area_wmean(const char * area_pos = "0", const char * wfunc_pos = "0", const char * func_pos = "0");
REAL func_std(REAL mean, const char * pos = "0");
REAL func_sum(const char * pos = "0");
bool func_plus(const char * pos1, const char * pos2);
bool func_plus_area(const char * pos1, const char * area_pos, const char * pos2);
bool func_minus(const char * pos1, const char * pos2);
bool func_minus_area(const char * pos1, const char * area_pos, const char * pos2);
bool func_minus_undef(const char * pos1, const char * pos2);
bool func_minus_undef_area(const char * pos1, const char * area_pos, const char * pos2);
bool func_mult(const char * pos1, const char * pos2);
bool func_mult_area(const char * pos1, const char * area_pos, const char * pos2);
bool func_div(const char * pos1, const char * pos2);
bool func_div_undef(const char * pos1, const char * pos2);
bool func_div_area(const char * pos1, const char * area_pos, const char * pos2);
bool func_set(const char * pos1, const char * pos2);
bool func_set_area(const char * pos1, const char * area_pos, const char * pos2);
bool func_plus_value(REAL val, const char * pos = "0");
bool func_plus_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
bool func_minus_value(REAL val, const char * pos = "0");
bool func_minus_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
bool func_mult_value(REAL val, const char * pos = "0");
bool func_mult_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
bool func_div_value(REAL val, const char * pos = "0");
bool func_div_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
bool func_set_value(REAL val, const char * pos = "0");
bool func_set_value_area(const char * Value, const char * area_pos = "0", const char * func_pos = "0");
REAL func_sum_area(const char * curv_pos = "0",  const char * func_pos = "0");
int func_cells_in_area(const char * curv_pos = "0",  const char * func_pos = "0");
// WAVELETS SECTION
int func_get_details_level(const char * pos = "0");
bool func_decomp(const char * pos = "0");
bool func_auto_decomp(REAL eps, const char * pos = "0");
bool func_recons(const char * pos = "0");
bool func_full_recons(const char * pos = "0");
// CONVERTING
bool func_to_pnts(const char * func_pos = "0");
bool func_to_mask(REAL true_from, REAL true_to, const char * pos = "0");
// OTHER
int func_getCountX(const char * pos = "0");
int func_getCountY(const char * pos = "0");
REAL func_getStepX(const char * pos = "0");
REAL func_getStepY(const char * pos = "0");
bool func_undef(REAL new_undef_value, const char * pos = "0");
void func_info(const char * pos = "0");
const char * func_getName(const char * pos = "0");
bool func_setName(const char * new_name, const char * pos = "0");
bool func_delall();
bool func_del(const char * pos = "0");
int func_size();
void funcs_info();

//
// mask
//

//save and load
bool mask_load(const char * filename, const char * defname = 0);
bool mask_save(const char * filename, const char * pos = "0");
bool mask_save_grd(const char * filename, const char * pos = "0");
bool mask_save_xyz(const char * filename, const char * pos = "0");
//
// math
//
bool mask_getValue(REAL x, REAL y, const char * pos = "0");
bool mask_and(const char * pos1 = "0", const char * pos2 = "0");
bool mask_not(const char * pos1 = "0", const char * pos2 = "0");
bool  mask_or(const char * pos1 = "0", const char * pos2 = "0");
bool mask_xor(const char * pos1 = "0", const char * pos2 = "0");
// CONVERTING
bool mask_to_func(const char * pos = "0");
// OTHER
bool mask_by_func(const char * func_pos = "0");
bool mask_apply_to_func(const char * def_pos = "0", const char * func_pos = "0");
const char * mask_getName(const char * pos = "0");
bool mask_setName(const char * new_name, const char * pos = "0");
bool mask_delall();
bool mask_del(const char * pos = "0");
int mask_size();
void masks_info();


}; // namespace surfit;

