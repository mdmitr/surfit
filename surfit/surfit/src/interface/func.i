
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
#include "func_tcl.h"
#include "funcs.h"
#include "wfunc_tcl.h"
#include "wfuncs.h"
#include "trends.h"
#include "trend_tcl.h"
#include "defarea_tcl.h"
#include "defareas.h"
%}

namespace surfit {

class func;
class wfunc;
class trend;
class defarea;

//
// func
//

// save_load
bool func_load(const char * filename, const char * funcname = NULL);
bool func_load_grd(const char * filename, const char * funcname = NULL);
void func_unload();
bool func_save(const char * filename, const char * funcname = NULL);
bool func_save_grd(const char * filename);
bool func_save_xyz(const char * filename);
bool func_save_bmp(const char * filename);
// math
REAL func_getValue(REAL x, REAL y);
bool func_resid(const char * filename);
REAL func_D1();
REAL func_D2();
void func_gradient();
bool func_project();
bool func_add_noise(REAL std);
REAL func_minz();
REAL func_maxz();
REAL func_mean();
REAL func_std(REAL mean_value);
REAL func_sum();
bool func_plus(func * func);
bool func_minus(func * func);
bool func_minus_undef(func * func);
bool func_mult(func * func);
bool func_div(func * func);
bool func_set(func * func);
bool func_plus_real(REAL val);
bool func_minus_real(REAL val);
bool func_mult_real(REAL val);
bool func_div_real(REAL val);
bool func_set_real(REAL val);
// wavelet
int  func_get_details_level();
bool func_decomp();
bool func_auto_decomp(REAL eps);
bool func_recons();
bool func_full_recons();
// converting
bool func_to_task();
bool func_to_defarea(REAL true_from, REAL true_to);
bool func_to_defareas(REAL true_from, REAL true_to);
bool func_to_trend(REAL D1, REAL D2);
bool func_to_trends(REAL D1, REAL D2);
bool func_to_wfunc(REAL weight);
bool func_to_wfuncs(REAL weight);
bool func_to_funcs();
// other
bool func_check();
int  func_getCountX();
int  func_getCountY();
REAL func_getStepX();
REAL func_getStepY();
bool func_undef(REAL new_undef_value);
void func_info(func * func = NULL);
bool func_name(const char * new_name = NULL, func * fnc = NULL);
// operations with func collections
bool funcs_delall(); 
bool funcs_del(int pos); 
bool funcs_load(const char *filename, const char *funcname=0);
bool funcs_load_grd(const char *filename, const char *funcname=NULL); 
bool funcs_unload(const char *name);
func * funcs_at(int pos);
func * funcs_first();
func * funcs_last();
int funcs_size();
int funcs_info();


//
// WFUNC
//

// save-load
bool wfunc_load(const char * filename, const char * wfuncname = NULL);
bool wfunc_load_grd(const char * filename, REAL weight, const char * wfuncname = NULL);
void wfunc_unload();
bool wfunc_save(const char * filename, const char * wfuncname = NULL);
bool wfunc_save_grd(const char * filename);
bool wfunc_save_xyz(const char * filename);
bool wfunc_save_bmp(const char * filename);
//math
REAL wfunc_getValue(REAL x, REAL y);
bool wfunc_add_noise(REAL std);
REAL wfunc_minz();
REAL wfunc_maxz();
REAL wfunc_mean();
REAL wfunc_std(REAL mean_value);
bool wfunc_plus(wfunc * fnc);
bool wfunc_minus(wfunc * fnc); 
bool wfunc_mult(wfunc * fnc); 
bool wfunc_div(wfunc * fnc); 
bool wfunc_set(wfunc * fnc); 
bool wfunc_plus_real(REAL val); 
bool wfunc_mult_real(REAL val); 
bool wfunc_div_real(REAL val); 
bool wfunc_set_real(REAL val); 
//wavan
int wfunc_get_details_level(); 
bool wfunc_decomp(); 
bool wfunc_auto_decomp(REAL eps);
bool wfunc_recons();
bool wfunc_full_recons();
//conv
bool wfunc_to_wtask(); 
bool wfunc_to_func(); 
bool wfunc_to_funcs(); 
bool wfunc_to_wfuncs(); 
//other
bool wfunc_check(); 
int wfunc_getCountX(); 
int wfunc_getCountY(); 
REAL wfunc_getStepX(); 
REAL wfunc_getStepY(); 
bool wfunc_undef(REAL new_undef_value); 
void wfunc_info(wfunc *fnc=NULL); 
bool wfunc_name(const char *new_name=NULL, wfunc *wfnc=NULL); 
//operations with wfunc collections
bool wfuncs_delall(); 
bool wfuncs_del(int pos);
bool wfuncs_load(const char *filename, const char *wfuncname=0);
bool wfuncs_load_grd(const char *filename, REAL weight, const char *wfuncname=NULL);
bool wfuncs_unload(const char *name);
wfunc * wfuncs_at(int pos);
wfunc * wfuncs_first();
wfunc * wfuncs_last();
int wfuncs_size();
int wfuncs_info();


//
// TREND
//

//saving and loading
bool trend_load(const char *filename, const char *funcname=0);
bool trend_load_grd(const char *filename, REAL D1=1, REAL D2=0, const char *trendname=NULL);
void trend_unload();
bool trend_save(const char *filename, const char *funcname=0);
bool trend_save_grd(const char *filename);
bool trend_save_xyz(const char *filename);
bool trend_save_bmp(const char *filename);
//math
REAL trend_getValue(REAL x, REAL y);
bool trend_resid(const char *filename);
bool trend_project();
REAL trend_minz();
REAL trend_maxz();
REAL trend_mean();
REAL trend_std(REAL mean);
bool trend_plus(trend *fnc);
bool trend_minus(trend *fnc);
bool trend_minus_undef(trend *fnc);
bool trend_mult(trend *fnc);
bool trend_div(trend *fnc);
bool trend_set(trend *fnc);
bool trend_plus_real(REAL val);
bool trend_minus_real(REAL val);
bool trend_mult_real(REAL val);
bool trend_div_real(REAL val);
bool trend_set_real(REAL val);
//wavan
int trend_get_details_level(); 
bool trend_decomp(); 
bool trend_auto_decomp(REAL eps);
bool trend_recons();
bool trend_full_recons();
//convers
bool trend_to_func(); 
bool trend_to_funcs(); 
bool trend_to_trends(); 
//other
bool trend_check();
int trend_getCountX();
int trend_getCountY();
REAL trend_getStepX();
REAL trend_getStepY();
bool trend_undef(REAL new_undef_value);
void trend_info(trend *fnc=NULL);
bool trend_name(const char *new_name=NULL, trend *trnd=NULL);
// operations with trend collections
bool trends_delall(); 
bool trends_del(int pos); 
bool trends_load(const char *filename, const char *trendname=0);
bool trends_load_grd(const char *filename, REAL D1, REAL D2, const char *trendname=NULL);
bool trends_unload(const char *name);
trend * trends_at(int pos);
trend * trends_first();
trend * trends_last();
int trends_size();
int trends_info();


//
// DEFAREA
//

//save and load
bool defarea_load(const char *filename, const char *defname=0);
void defarea_unload();
bool defarea_save(const char *filename, const char *defname=0);
bool defarea_save_grd(const char *filename);
bool defarea_save_xyz(const char *filename);
//math
bool defarea_getValue(REAL x, REAL y); 
bool defarea_and(defarea *def);
bool defarea_not(defarea *def=NULL);
bool defarea_or(defarea *def);
bool defarea_xor(defarea *def);
//conv
bool defarea_to_func(); 
bool defarea_to_funcs(); 
bool defarea_to_defareas();
//other
bool defarea_check(); 
bool defarea_by_func(); 
bool defarea_apply_to_func(); 
bool defarea_name(const char *new_name=NULL, defarea *def=NULL);
//operations with defarea collections
bool defareas_delall();
bool defareas_del(int pos);
bool defareas_load(const char *filename, const char *defareaname=0);
bool defareas_load_grd(const char *filename, const char *defareaname=NULL);
bool defareas_unload(const char *name);
defarea * defareas_at(int pos);
defarea * defareas_first();
defarea * defareas_last();
int defareas_size();
int defareas_info();

}; // namespace surfit;

