
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

#include "surfit_ie.h"
#include "funcs_tcl.h"
#include "func.h"
#include "mask.h"
#include "f_func.h"
#include "f_func_ineq.h"
#include "f_trend.h"
#include "f_mask.h"
#include "variables.h"
#include "variables_tcl.h"

namespace surfit {

bool func(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == NULL)
		return false;
	
	f_func * f = new f_func(fnc);
	functionals->push_back(f);
	return true;
};

bool func_add(REAL weight, const char * pos) {
	
	if (functionals->size() == 0)
		return false;
	functional * f = *(functionals->end()-1);

	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == NULL)
		return false;

	f_func * fnc2 = new f_func(fnc);
	f->add_functional(fnc2, weight);
	return true;
};

bool func_leq(const char * pos, REAL mult) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == NULL)
		return false;
	f_func_ineq * f = new f_func_ineq(fnc, true, mult);
	functionals->push_back(f);
	return true;
};

bool func_geq(const char * pos, REAL mult) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == NULL)
		return false;
	f_func_ineq * f = new f_func_ineq(fnc, false, mult);
	functionals->push_back(f);
	return true;
};

bool trend(REAL D1, REAL D2, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == NULL)
		return false;
	
	f_trend * f = new f_trend(D1, D2, fnc);
	functionals->push_back(f);
	return true;
};

bool trend_add(REAL weight, REAL D1, REAL D2, const char * pos) {
	
	if (functionals->size() == 0)
		return false;
	functional * f = *(functionals->end()-1);

	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == NULL)
		return false;

	f_trend * fnc2 = new f_trend(D1, D2, fnc);
	f->add_functional(fnc2, weight);
	return true;
};

bool mask(const char * Value, const char * pos) {
	
	REAL value = undef_value;
	if (strcmp(Value,"undef") != 0) {
		value = atof(Value);
	}

	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (msk == NULL)
		return false;
	
	f_mask * f = new f_mask(msk, value);
	functionals->push_back(f);
	return true;
};

}; // namespace surfit;

