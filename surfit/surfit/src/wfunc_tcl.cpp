
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
#include "wfunc.h"
#include "wfunc_internal.h"
#include "func_internal.h"
#include "wfunc_tcl.h"
#include "wtask_tcl.h"
#include "func_tcl.h"
#include "vec.h"
#include "fileio.h"
#include "variables_internal.h"

#include "wfunc_user.h"
#include "wtask_user.h"
#include "func_user.h"

namespace surfit {

void wfunc_unload() {
	_wfunc_unload(surfit_wfunc);
};

bool wfunc_check() {
	return (surfit_wfunc != NULL);
};

bool wfunc_load(const char * filename, const char * wfuncname) {
	wfunc_unload();
	surfit_wfunc = _wfunc_load(filename, wfuncname, get_rw_mode());
	return (surfit_wfunc != NULL);
};

bool wfunc_load_grd(const char * filename, REAL weight, const char * wfuncname) {
	wfunc_unload();
	surfit_wfunc = _wfunc_load_grd(filename, weight, wfuncname);
	return (surfit_wfunc != NULL);
};

bool wfunc_save(const char * filename, const char * wfuncname) {
	if (!_wfunc_check())
		return false;
	return _wfunc_save(surfit_wfunc, filename, wfuncname);
};

bool wfunc_save_grd(const char * filename) {

	if (!_wfunc_check())
		return false;

	return _func_save_grd(surfit_wfunc, filename);
	
};

bool wfunc_save_xyz(const char * filename) {

	if (!_wfunc_check())
		return false;
	
	return _func_save_xyz(surfit_wfunc, filename);
	
};

bool wfunc_save_bmp(const char * filename) {
	if (!_wfunc_check())
		return false;

	return _func_save_bmp(surfit_wfunc, filename);
};

REAL wfunc_minz() {
	if (!_wfunc_check())
		return false;
	REAL minZ, maxZ;
	surfit_wfunc->getMinMaxZ(minZ, maxZ);
	return minZ;
};


REAL wfunc_maxz() {
	if (!_wfunc_check())
		return false;
	REAL minZ, maxZ;
	surfit_wfunc->getMinMaxZ(minZ, maxZ);
	return maxZ;
};

REAL wfunc_mean() {
	if (!_wfunc_check())
		return false;
	return surfit_wfunc->mean();
}

REAL wfunc_std(REAL mean) {
	if (!_wfunc_check())
		return false;
	return surfit_wfunc->std(mean);
}

int wfunc_getCountX() {
	if (!_wfunc_check())
		return 0;
	return surfit_wfunc->getCountX();
};

int wfunc_getCountY() {
	if (!_wfunc_check())
		return 0;
	return surfit_wfunc->getCountY();
};

REAL wfunc_getStepX() {
	if (!_wfunc_check())
		return 0;
	return surfit_wfunc->getStepX();
};

REAL wfunc_getStepY() {
	if (!_wfunc_check())
		return 0;
	return surfit_wfunc->getStepY();
};

REAL wfunc_getValue(REAL x, REAL y) {
	if (!_wfunc_check())
		return 0;
	return surfit_wfunc->getValue(x,y);
};

bool wfunc_plus(wfunc * fnc) {
	if (!_wfunc_check())
		return false;

	if (!surfit_wfunc->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"wfunc_plus : different grid");
		return false;
	}

	surfit_wfunc->plus(fnc);

	return true;
};

bool wfunc_minus(wfunc * fnc) {
	if (!_wfunc_check())
		return false;

	if (!surfit_wfunc->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"wfunc_minus : different grid");
		return false;
	}

	surfit_wfunc->minus(fnc);

	return true;
};

bool wfunc_mult(wfunc * fnc) {
	if (!_wfunc_check())
		return false;

	if (!surfit_wfunc->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"wfunc_mult : different grid");
		return false;
	}

	surfit_wfunc->mult(fnc);

	return true;
};

bool wfunc_div(wfunc * fnc) {
	if (!_wfunc_check())
		return false;

	if (!surfit_wfunc->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"wfunc_div : different grid");
		return false;
	}

	surfit_wfunc->div(fnc);

	return true;
};

bool wfunc_set(wfunc * fnc) {
	if (!_wfunc_check())
		return false;

	if (!surfit_wfunc->compare_grid(fnc))	{
		writelog(SURFIT_ERROR,"wfunc_set : different grid");
		return false;
	}

	surfit_wfunc->set(fnc);

	return true;
};

bool wfunc_plus_real(REAL val) {
	if (!_wfunc_check())
		return false;
	surfit_wfunc->plus(val);
	return true;
};

bool wfunc_minus_real(REAL val) {
	if (!_wfunc_check())
		return false;
	surfit_wfunc->minus(val);
	return true;
};

bool wfunc_mult_real(REAL val) {
	if (!_wfunc_check())
		return false;
	surfit_wfunc->mult(val);
	return true;
};

bool wfunc_div_real(REAL val) {
	if (!_wfunc_check())
		return false;
	surfit_wfunc->div(val);
	return true;
};

bool wfunc_set_real(REAL val) {
	if (!_wfunc_check())
		return false;
	surfit_wfunc->set(val);
	return true;
};

//
//
// wavelets section
//
//
int wfunc_get_details_level() {
	if (!_wfunc_check())
		return -1;

	return surfit_wfunc->details_h->size();
};

bool wfunc_decomp() {
	if (!_wfunc_check())
		return false;
	return _func_decomp(surfit_wfunc);
};

bool wfunc_auto_decomp(REAL eps) {
	if (!_wfunc_check())
		return false;
	return _func_auto_decomp(surfit_wfunc, eps);
};

bool wfunc_add_noise(REAL std) {
	if (!_wfunc_check())
		return false;
	return _func_add_noise(surfit_wfunc, std);
};

bool wfunc_recons() {
	if (!_wfunc_check())
		return false;
	return _func_recons(surfit_wfunc);
};

bool wfunc_full_recons() {
	if (!_wfunc_check())
		return false;
	return _func_full_recons(surfit_wfunc);
};

bool wfunc_undef(REAL new_undef_value) {
	if (!_wfunc_check())
		return false;
	surfit_wfunc->undef_value = new_undef_value;
	return true;
};

void wfunc_info(wfunc * fnc) {
	if (fnc==NULL) {
		_wfunc_info(surfit_wfunc);
		return;
	}
	_wfunc_info(fnc);
};

bool wfunc_name(const char * new_name, wfunc * wfnc) {
	if (wfnc) {
		wfnc->setName(new_name);
		return true;
	}
	if (!_wfunc_check())
		return false;
	if (!new_name) {
		if (surfit_wfunc->getName())
			writelog(SURFIT_MESSAGE,"surfit_wfunc name is \"%s\"",surfit_wfunc->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_wfunc have no name");
		return true;
	}
	surfit_wfunc->setName(new_name);
	return true;
};

bool wfunc_to_wtask() {
	writelog(SURFIT_MESSAGE,"Converting wfunc to wtask");
	if (!wfunc_check())
		return false;
	
	wtask_unload();
	surfit_wtask = _wfunc_to_wtask(surfit_wfunc);
	if (!surfit_wtask)
		return false;
	
	return true;	
};

bool wfunc_to_func() {
	if (!_wfunc_check())
		return false;

	if (surfit_func)
		func_unload();

	surfit_func = surfit_wfunc;
	surfit_wfunc = NULL;
	return true;
};

bool wfunc_to_funcs() {
	if (!_wfunc_check())
		return false;

	surfit_funcs->push_back(surfit_wfunc);
	surfit_wfunc = NULL;
	return true;
};

bool wfunc_to_wfuncs() {
	if (!_wfunc_check())
		return false;

	surfit_wfuncs->push_back(surfit_wfunc);
	surfit_wfunc = NULL;
	return true;
};


}; // namespace surfit;

