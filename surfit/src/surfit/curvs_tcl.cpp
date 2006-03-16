
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
#include "curvs_tcl.h"
#include "variables.h"
#include "curv.h"
#include "area.h"
#include "cntr.h"
#include "func.h"
#include "curv_internal.h"
#include "functional.h"
#include "f_area.h"
#include "f_area_ineq.h"
#include "f_area_func_ineq.h"
#include "f_area_mean.h"
#include "f_area_wmean.h"
#include "f_cntr.h"
#include "f_cntr_ineq.h"
#include "f_curv.h"
#include "f_curv_ineq.h"
#include "variables_tcl.h"

namespace surfit {

bool fault_add(const char * pos) {
	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	faultable * f = dynamic_cast<faultable *>(fnc);
	if (f == NULL)
		return false;

	d_curv * crv = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;

	f->add_fault(crv);
	return true;
};

bool curve(REAL value, const char * pos) {
	d_curv * crv = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;
	
	f_curv * f = new f_curv(value, crv);
	functionals->push_back(f);
	return true;
};

bool curve_add(REAL value, REAL weight, const char * pos) {
	
	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	
	d_curv * crv = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;
	
	f_curv * fnc2 = new f_curv(value, crv);
	fnc->add_functional(fnc2, weight);
	return true;
};

bool curve_leq(REAL value, const char * curve_pos, REAL mult) {
	d_curv * curve = get_element<d_curv>(curve_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	f_curv_ineq * f = new f_curv_ineq(value, curve, true, mult);
	functionals->push_back(f);
	return true;
};

bool curve_geq(REAL value, const char * curve_pos, REAL mult) {
	d_curv * curve = get_element<d_curv>(curve_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	f_curv_ineq * f = new f_curv_ineq(value, curve, false, mult);
	functionals->push_back(f);
	return true;
};

bool area(const char * Value, const char * pos, int inside) {

	REAL value = undef_value;
	if (strcmp(Value,"undef") != 0) {
		value = atof(Value);
	}

	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;
	
	f_area * f = new f_area(value, area, (inside == 1) );
	functionals->push_back(f);
	return true;
};

bool area_add(REAL value, REAL weight, const char * pos, int inside) {
	
	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;
	
	f_area * fnc2 = new f_area(value, area, (inside == 1) );
	fnc->add_functional(fnc2, weight);
	return true;
};

bool area_leq(REAL value, const char * area_pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_ineq * f = new f_area_ineq(value, area, true, mult, (inside == 1) );
	functionals->push_back(f);
	return true;
};

bool area_geq(REAL value, const char * area_pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_ineq * f = new f_area_ineq(value, area, false, mult, (inside == 1) );
	functionals->push_back(f);
	return true;
};

bool area_func_leq(const char * func_pos, const char * area_pos, REAL mult, int inside) {

	d_func * func = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (func == NULL)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_func_ineq * f = new f_area_func_ineq(func, area, true, mult, (inside == 1) );
	functionals->push_back(f);
	return true;
};

bool area_func_geq(const char * func_pos, const char * area_pos, REAL mult, int inside) {

	d_func * func = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (func == NULL)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_func_ineq * f = new f_area_func_ineq(func, area, false, mult, (inside == 1) );
	functionals->push_back(f);
	return true;
};

bool area_mean(REAL mean, const char * pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_mean * f = new f_area_mean(mean, area, mult, (inside == 1) );
	functionals->push_back(f);
	return true;
};

bool area_wmean(REAL mean, const char * area_pos, const char * func_pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == NULL)
		return false;

	f_area_wmean * f = new f_area_wmean(mean, fnc, area, mult, (inside == 1) );
	functionals->push_back(f);
	return true;
};

bool contour(const char * pos) {
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	
	f_cntr * f = new f_cntr(contour);
	functionals->push_back(f);
	return true;
};

bool contour_add(REAL weight, const char * pos) {
	
	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	
	f_cntr * fnc2 = new f_cntr(contour);
	fnc->add_functional(fnc2, weight);
	return true;
};

bool contour_leq(const char * cntr_pos, REAL mult) {
	d_cntr * contour = get_element<d_cntr>(cntr_pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;

	f_cntr_ineq * f = new f_cntr_ineq(contour, true, mult);
	functionals->push_back(f);
	return true;
};

bool contour_geq(const char * cntr_pos, REAL mult) {
	d_cntr * contour = get_element<d_cntr>(cntr_pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;

	f_cntr_ineq * f = new f_cntr_ineq(contour, false, mult);
	functionals->push_back(f);
	return true;
};

}; // namespace surfit;


