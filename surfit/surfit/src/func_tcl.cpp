
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

#include "ie.h"
#include "real.h"
#include "func.h"
#include "func_internal.h"
#include "func_tcl.h"
#include "wfunc_tcl.h"
#include "variables_internal.h"
#include "trend.h"
#include "trend_internal.h"
#include "trend_tcl.h"
#include "task.h"
#include "task_internal.h"
#include "task_tcl.h"
#include "defarea.h"
#include "defarea_tcl.h"
#include "grid.h"
#include "grid_internal.h"
#include "fileio.h"
#include "boolvec.h"
#include "grid_line.h"
#include "flt.h"

#include "func_user.h"
#include "wfunc_user.h"
#include "task_user.h"
#include "defarea_user.h"
#include "grid_user.h"
#include "trend_user.h"
#include "flt_user.h"

#include <float.h>

namespace surfit {

void func_unload() {
	_func_unload(surfit_func);
};

bool func_check() {
	return (surfit_func != NULL);
};

bool func_load(const char * filename, const char * funcname) {
	func_unload();
	surfit_func = _func_load(filename, funcname, get_rw_mode());
	return (surfit_func != NULL);
};

bool func_save(const char * filename, const char * funcname) {
	if (!_func_check())
		return false;
	return _func_save(surfit_func, filename, funcname);
};

bool func_resid(const char * filename) {
	if (!_func_check())
		return false;
	if (!_task_check())
		return false;
	return _func_resid(surfit_func, surfit_task, filename);
};

REAL func_minz() {
	if (!_func_check())
		return FLT_MAX;
	REAL minZ, maxZ;
	surfit_func->getMinMaxZ(minZ, maxZ);
	return minZ;
};


REAL func_maxz() {
	if (!_func_check())
		return FLT_MAX;
	REAL minZ, maxZ;
	surfit_func->getMinMaxZ(minZ, maxZ);
	return maxZ;
};

REAL func_mean() {
	if (!_func_check())
		return FLT_MAX;
	return surfit_func->mean();
};

REAL func_std(REAL mean) {
	if (!_func_check())
		return FLT_MAX;
	return surfit_func->std(mean);
};

REAL func_sum() {
	if (!_func_check())
		return FLT_MAX;
	return surfit_func->sum();
};

bool func_save_grd(const char * filename) {
	if (!_func_check())
		return false;
	return _func_save_grd(surfit_func, filename);
};

bool func_load_grd(const char * filename, const char * funcname) {
	func_unload();
	surfit_func = _func_load_grd(filename, funcname);
	if (surfit_func)
		surfit_func->setName(funcname);
	return (surfit_func != NULL);
};

bool func_save_xyz(const char * filename) {
	if (!_func_check())
		return false;
	return _func_save_xyz(surfit_func, filename);
};

bool func_save_bmp(const char * filename) {
	if (!_func_check())
		return false;
	return _func_save_bmp(surfit_func, filename);
};

bool func_to_task() {
	writelog(SURFIT_MESSAGE,"Converting func to task");
	if (!func_check())
		return false;
	
	task_unload();
	surfit_task = _func_to_task(surfit_func);
	if (!surfit_task)
		return false;
	
	return true;
	
}

int func_getCountX() {
	if (!_func_check())
		return 0;
	return surfit_func->getCountX();
};

int func_getCountY() {
	if (!_func_check())
		return 0;
	return surfit_func->getCountY();
};

REAL func_getStepX() {
	if (!_func_check())
		return FLT_MAX;
	return surfit_func->getStepX();
};

REAL func_getStepY() {
	if (!_func_check())
		return FLT_MAX;
	return surfit_func->getStepY();
};

REAL func_getValue(REAL x, REAL y) {
	if (!_func_check())
		return FLT_MAX;
	return surfit_func->getValue(x,y);
};

bool func_plus(func * fnc) {
	if (!_func_check())
		return false;

	if (!surfit_func->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"func_plus : different grid");
		return false;
	}

	surfit_func->plus(fnc);

	return true;
};

bool func_minus(func * fnc) {
	if (!_func_check())
		return false;

	if (!surfit_func->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"func_minus : different grid");
		return false;
	}

	surfit_func->minus(fnc);

	return true;
};

bool func_minus_undef(func * fnc) {
	if (!_func_check())
		return false;

	if (!surfit_func->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"func_minus : different grid");
		return false;
	}

	surfit_func->minus_undef(fnc);

	return true;
};


bool func_mult(func * fnc) {
	if (!_func_check())
		return false;

	if (!surfit_func->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"func_mult : different grid");
		return false;
	}

	surfit_func->mult(fnc);

	return true;
};

bool func_div(func * fnc) {
	if (!_func_check())
		return false;

	if (!surfit_func->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"func_div : different grid");
		return false;
	}

	surfit_func->div(fnc);

	return true;
};

bool func_set(func * fnc) {
	if (!_func_check())
		return false;

	if (!surfit_func->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"func_set : different grid");
		return false;
	}

	surfit_func->set(fnc);

	return true;
};

bool func_plus_real(REAL val) {
	if (!_func_check())
		return false;
	surfit_func->plus(val);
	return true;
};

bool func_minus_real(REAL val) {
	if (!_func_check())
		return false;
	surfit_func->minus(val);
	return true;
};

bool func_mult_real(REAL val) {
	if (!_func_check())
		return false;
	surfit_func->mult(val);
	return true;
};

bool func_div_real(REAL val) {
	if (!_func_check())
		return false;
	surfit_func->div(val);
	return true;
};

bool func_set_real(REAL val) {
	if (!_func_check())
		return false;
	surfit_func->set(val);
	return true;
};

bool func_to_defarea(REAL true_from, REAL true_to)
{
	if (!_func_check())
		return false;
	defarea_unload();

	boolvec * bcoeff = new boolvec( surfit_func->coeff->size() );
	int i;
	REAL val;
	for (i = 0; i < surfit_func->coeff->size(); i++) {
		val = (*(surfit_func->coeff))(i);
		(*bcoeff)(i) = ( (val >= true_from) && (val <= true_to) );
	};

	grid * fgrd = surfit_func->grd;
	grid * grd = new grid(fgrd);

	surfit_defarea = new defarea(bcoeff, grd);

	return true;
};

bool func_to_defareas(REAL true_from, REAL true_to)
{
	if (!_func_check())
		return false;

	boolvec * bcoeff = new boolvec( surfit_func->coeff->size() );
	int i;
	REAL val;
	for (i = 0; i < surfit_func->coeff->size(); i++) {
		val = (*(surfit_func->coeff))(i);
		(*bcoeff)(i) = ( (val >= true_from) && (val <= true_to) );
	};

	grid * fgrd = surfit_func->grd;
	grid * grd = new grid(fgrd);

	defarea * def = new defarea(bcoeff, grd);
	surfit_defareas->push_back(def);

	return true;
};

//
//
// wavelets section
//
//
bool func_decomp() {
	if (!_func_check())
		return false;
	return _func_decomp(surfit_func);
};

bool func_auto_decomp(REAL eps) {
	if (!_func_check())
		return false;
	return _func_auto_decomp(surfit_func,eps);
};

bool func_add_noise(REAL std) {
	if (!_func_check())
		return false;
	return _func_add_noise(surfit_func, std);
};

bool func_recons() {
	if (!_func_check())
		return false;
	return _func_recons(surfit_func);
};

bool func_full_recons() {
	if (!_func_check())
		return false;
	return _func_full_recons(surfit_func);
};

int func_get_details_level() {
	if (!_func_check())
		return -1;

	return surfit_func->details_h->size();
};

bool func_undef(REAL new_undef_value) {
	if (!_func_check())
		return false;
	surfit_func->undef_value = new_undef_value;
	return true;
};

REAL func_D1() {
	if (!_func_check())
		return FLT_MAX;
	return _func_D1(surfit_func);
};

REAL func_D2() {
	if (!_func_check())
		return FLT_MAX;
	return _func_D2(surfit_func);
};

void func_info(func * fnc) {
	if (fnc==NULL) {
		_func_info(surfit_func);
		return;
	}
	_func_info(fnc);
};

bool func_project() {
	if (!_func_check())
		return false;
	if (!_grid_check())
		return false;

	if (!(surfit_func->grd->operator == (surfit_grid))) {
		
		grid_line * fault_grd_line1 = trace_faults(INT_MAX, surfit_func->grd);
		grid_line * fault_grd_line2 = trace_faults(INT_MAX, surfit_grid);
		
		func * res_func2 = _func_project(surfit_func, surfit_grid, fault_grd_line1);
		delete surfit_func;
		surfit_func = res_func2;
		res_func2 = NULL;

		delete fault_grd_line1;
		delete fault_grd_line2;
	}
	return true;
};

bool func_gradient() {
	if (!_func_check())
		return false;
	func * res = _func_gradient(surfit_func);
	if (res) {
		delete surfit_func;
		surfit_func = res;
		return true;
	}
	return false;
};

bool func_to_trend(REAL D1, REAL D2) {
	if (!_func_check())
		return false;
	if (surfit_trend)
		trend_unload();

	trend * res = new trend(surfit_func->coeff, surfit_func->grd, D1, D2, surfit_func->getName());
	surfit_func->coeff = NULL;
	surfit_func->grd = NULL;
	surfit_trend = res;
	func_unload();
	return true;
};

bool func_to_trends(REAL D1, REAL D2) {
	if (!_func_check())
		return false;
	
	trend * res = new trend(surfit_func->coeff, surfit_func->grd, D1, D2, surfit_func->getName());
	surfit_func->coeff = NULL;
	surfit_func->grd = NULL;
	func_unload();
	surfit_trends->push_back(res);
	return true;
};

bool func_to_wfunc(REAL weight) {
	if (!_func_check())
		return false;
	
	wfunc * wfnc = _func_to_wfunc(surfit_func, weight);
	if (!wfnc)
		return false;
	
	if (surfit_wfunc)
		wfunc_unload();
	surfit_wfunc = wfnc;
	func_unload();
	return true;
};

bool func_to_wfuncs(REAL weight) {
	if (!_func_check())
		return false;
	
	wfunc * wfnc = _func_to_wfunc(surfit_func, weight);
	if (!wfnc)
		return false;
	func_unload();
	surfit_wfuncs->push_back(wfnc);
	return true;
};


bool func_to_funcs() {
	if (!_func_check())
		return false;
	surfit_funcs->push_back(surfit_func);
	surfit_func = NULL;
	return true;
};

bool func_name(const char * new_name, func * fnc) {
	if (fnc) {
		fnc->setName(new_name);
		return true;
	}
	if (!_func_check())
		return false;
	if (!new_name) {
		if (surfit_func->getName())
			writelog(SURFIT_MESSAGE,"surfit_func name is \"%s\"",surfit_func->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_func have no name");
		return true;
	}
	surfit_func->setName(new_name);
	return true;
};

}; // namespace surfit;

