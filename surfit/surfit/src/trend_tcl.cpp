
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
#include "trend.h"
#include "grid.h"
#include "grid_line.h"
#include "trend_internal.h"
#include "task_internal.h"
#include "func_internal.h"
#include "grid_internal.h"
#include "trend_tcl.h"
#include "variables_internal.h"
#include "fileio.h"
#include "func_tcl.h"

#include "trend_user.h"
#include "task_user.h"
#include "grid_user.h"
#include "flt_user.h"
#include "func_user.h"

#include <float.h>

namespace surfit {

void trend_unload() {
	_trend_unload(surfit_trend);
};

bool trend_check() {
	return (surfit_trend != NULL);
};

bool trend_save(const char * filename, const char * funcname) {
	if (!_trend_check())
		return false;
	return _trend_save(surfit_trend, filename, funcname);
};

bool trend_load(const char * filename, const char * funcname) {
	trend_unload();
	surfit_trend = _trend_load(filename, funcname, get_rw_mode());
	return (surfit_trend != NULL);
};

REAL trend_minz() {
	if (!_trend_check())
		return false;
	REAL minZ, maxZ;
	surfit_trend->getMinMaxZ(minZ, maxZ);
	return minZ;
};

REAL trend_maxz() {
	if (!_trend_check())
		return false;
	REAL minZ, maxZ;
	surfit_trend->getMinMaxZ(minZ, maxZ);
	return maxZ;
};

REAL trend_mean() {
	if (!_trend_check())
		return false;
	return surfit_trend->mean();
}

REAL trend_std(REAL mean) {
	if (!_trend_check())
		return false;
	return surfit_trend->std(mean);
}

bool trend_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname) {
	trend_unload();
	surfit_trend = _trend_load_grd(filename, D1, D2, trendname);
	return (surfit_trend != NULL);
};

int trend_getCountX() {
	if (!_trend_check())
		return 0;
	return surfit_trend->getCountX();
};

int trend_getCountY() {
	if (!_trend_check())
		return 0;
	return surfit_trend->getCountY();
};

void trend_info(trend * fnc) {
	if (!fnc)
		_trend_info(surfit_trend);
	else
		_trend_info(fnc);
};

bool trend_name(const char * new_name, trend * trnd) {
	if (trnd) {
		trnd->setName(new_name);
		return true;
	}
	if (!_trend_check())
		return false;
	if (!new_name) {
		if (surfit_trend->getName())
			writelog(SURFIT_MESSAGE,"surfit_trend name is \"%s\"",surfit_trend->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_trend have no name");
		return true;
	}
	surfit_trend->setName(new_name);
	return true;
};

bool trend_save_grd(const char * filename) {
	if (!_trend_check())
		return false;
	return _func_save_grd(surfit_trend, filename);
};

bool trend_save_xyz(const char * filename) {
	if (!_trend_check())
		return false;
	return _func_save_xyz(surfit_trend, filename);
};

bool trend_save_bmp(const char * filename) {
	if (!_trend_check())
		return false;
	return _func_save_bmp(surfit_trend, filename);
};

REAL trend_getValue(REAL x, REAL y) {
	if (!_trend_check())
		return FLT_MAX;
	return surfit_trend->getValue(x,y);
};

bool trend_resid(const char * filename) {
	if (!_trend_check())
		return false;
	if (!_task_check())
		return false;
	return _func_resid(surfit_trend, surfit_task, filename);
};

bool trend_project() {
	if (!_trend_check())
		return false;
	if (!_grid_check())
		return false;

	if (!(surfit_trend->grd->operator == (surfit_grid))) {
		
		grid_line * fault_grd_line1 = trace_faults(INT_MAX, surfit_trend->grd);
		grid_line * fault_grd_line2 = trace_faults(INT_MAX, surfit_grid);
		
		func * res_func2 = _func_project(surfit_trend, surfit_grid, fault_grd_line1);
		trend * res_trend2 = new trend(res_func2, surfit_trend->D1, surfit_trend->D2);
		
		delete res_func2;
		delete surfit_trend;
		surfit_trend = res_trend2;
		res_trend2 = NULL;

		delete fault_grd_line1;
		delete fault_grd_line2;
	}
	return true;
};

bool trend_plus(trend * fnc) {
	if (!_trend_check())
		return false;

	if (!surfit_trend->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"trend_plus : different grid");
		return false;
	}

	surfit_trend->plus(fnc);

	return true;
};

bool trend_minus(trend * fnc) {
	if (!_trend_check())
		return false;

	if (!surfit_trend->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"trend_minus : different grid");
		return false;
	}

	surfit_trend->minus(fnc);

	return true;
};

bool trend_minus_undef(trend * fnc) {
	if (!_trend_check())
		return false;

	if (!surfit_trend->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"trend_minus : different grid");
		return false;
	}

	surfit_trend->minus_undef(fnc);

	return true;
};


bool trend_mult(trend * fnc) {
	if (!_trend_check())
		return false;

	if (!surfit_trend->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"trend_mult : different grid");
		return false;
	}

	surfit_trend->mult(fnc);

	return true;
};

bool trend_div(trend * fnc) {
	if (!_trend_check())
		return false;

	if (!surfit_trend->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"trend_div : different grid");
		return false;
	}

	surfit_trend->div(fnc);

	return true;
};

bool trend_set(trend * fnc) {
	if (!_trend_check())
		return false;

	if (!surfit_trend->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"trend_set : different grid");
		return false;
	}

	surfit_trend->set(fnc);

	return true;
};

bool trend_plus_real(REAL val) {
	if (!_trend_check())
		return false;
	surfit_trend->plus(val);
	return true;
};

bool trend_minus_real(REAL val) {
	if (!_trend_check())
		return false;
	surfit_trend->minus(val);
	return true;
};

bool trend_mult_real(REAL val) {
	if (!_trend_check())
		return false;
	surfit_trend->mult(val);
	return true;
};

bool trend_div_real(REAL val) {
	if (!_trend_check())
		return false;
	surfit_trend->div(val);
	return true;
};

bool trend_set_real(REAL val) {
	if (!_trend_check())
		return false;
	surfit_trend->set(val);
	return true;
};

//
//
// wavelets section
//
//
bool trend_decomp() {
	if (!_trend_check())
		return false;
	return _func_decomp(surfit_trend);
};

bool trend_auto_decomp(REAL eps) {
	if (!_trend_check())
		return false;
	return _func_auto_decomp(surfit_trend,eps);
};

bool trend_recons() {
	if (!_trend_check())
		return false;
	return _func_recons(surfit_trend);
};

bool trend_full_recons() {
	if (!_trend_check())
		return false;
	return _func_full_recons(surfit_trend);
};

int trend_get_details_level() {
	if (!_trend_check())
		return -1;

	return surfit_trend->details_h->size();
};

//
// convers
//
bool trend_to_func() {
	if (!_trend_check())
		return false;

	if (surfit_func)
		func_unload();

	surfit_func = surfit_trend;
	surfit_trend = NULL;
	return true;
};

bool trend_to_funcs() {
	if (!_trend_check())
		return false;

	surfit_funcs->push_back(surfit_trend);
	surfit_trend = NULL;
	return true;
};

bool trend_to_trends() {
	if (!_trend_check())
		return false;

	surfit_trends->push_back(surfit_trend);
	surfit_trend = NULL;
	return true;
};

REAL trend_getStepX() {
	if (!_trend_check())
		return 0;
	return surfit_trend->getStepX();
};

REAL trend_getStepY() {
	if (!_trend_check())
		return 0;
	return surfit_trend->getStepY();
};

bool trend_undef(REAL new_undef_value) {
	if (!_trend_check())
		return false;
	surfit_trend->undef_value = new_undef_value;
	return true;
};


}; // namespace surfit;

