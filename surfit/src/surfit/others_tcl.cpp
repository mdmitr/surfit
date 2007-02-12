
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
#include "others_tcl.h"
#include "f_completer.h"
#include "f_value.h"
#include "f_mean.h"
#include "f_wmean.h"
#include "f_ineq.h"
#include "f_hist.h"
#include "variables.h"
#include "curv.h"
#include "curv_internal.h"
#include "surf.h"
#include "hist.h"

namespace surfit {

bool completer(REAL D1, REAL D2, REAL alpha, REAL w) {
	f_completer * f_cmpltr = new f_completer(D1, D2, alpha, w);
	functionals_push_back(f_cmpltr);
	return true;
};

bool completer_add(REAL weight, REAL D1, REAL D2, REAL alpha, REAL w) {
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;
	
	f_completer * f_cmpltr = new f_completer(D1, D2, alpha, w);
	srf->add_functional(f_cmpltr, weight);
	return true;
};

bool value(REAL value) {
	f_value * f = new f_value(value);
	functionals_push_back(f);
	return true;
};

bool value_add(REAL weight, REAL value) {
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;
	f_value * f = new f_value(value);
	srf->add_functional(f, weight);
	return true;
};

bool mean(REAL value, REAL mult) {
	f_mean * f = new f_mean(value, mult);
	functionals_push_back(f);
	return true;
};

bool wmean(REAL value, const char * surf_pos, REAL mult) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	f_wmean * f = new f_wmean(value, srf, mult);
	functionals_push_back(f);
	return true;
};

bool leq(REAL value, REAL mult) {
	f_ineq * f = new f_ineq(value, true, mult);
	functionals_push_back(f);
	return true;
};

bool geq(REAL value, REAL mult) {
	f_ineq * f = new f_ineq(value, false, mult);
	functionals_push_back(f);
	return true;
};

bool hist(const char * pos, REAL mult) {
	d_hist * hst = get_element<d_hist>(pos, surfit_hists->begin(), surfit_hists->end());
	if (hst == NULL)
		return false;

	f_hist * f = new f_hist(hst, mult);
	functionals_push_back(f);
	return true;
};

}; // namespace surfit;


