
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
#include "surf.h"
#include "curv_internal.h"
#include "functional.h"
#include "f_area.h"
#include "f_area_ineq.h"
#include "f_area_surf.h"
#include "f_area_surf_ineq.h"
#include "f_area_mean.h"
#include "f_area_wmean.h"
#include "f_cntr.h"
#include "f_cntr_ineq.h"
#include "f_curv.h"
#include "f_curv_ineq.h"
#include "f_curv_surf.h"
#include "f_curv_surf_ineq.h"
#include "f_completer.h"
#include "variables_tcl.h"
#include "interp.h"

#include <algorithm>

namespace surfit {

struct regexp_fault
{
	regexp_fault(const char * ipos, faultable * _f) : pos(ipos), f(_f) {};
	void operator()(d_curv * fault) 
	{
		if (fault->getName() == NULL)
			return;
		if ( RegExpMatch(pos, fault->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule fault(\"%s\")", 
				 fault->getName()?fault->getName():"noname");
			f->add_fault(fault);
		}
	}
	const char * pos;
	faultable * f;
};

bool fault(const char * pos) {
	if (functionals->size() == 0) {
		writelog(LOG_ERROR,"No gridding rule modifiable with \"fault\" rule present!");
		return false;
	}
	functional * srf = *(functionals->end()-1);

	if ((srf->getType() & F_FAULT) == 0) {
		writelog(LOG_ERROR,"\"%s\" rule is not modifiable with \"fault\" rule!", srf->getName());
		return false;
	}

	faultable * f = static_cast<faultable *>(srf);
	if (f == NULL) {
		writelog(LOG_ERROR,"No gridding rule modifiable with \"fault\" rule present!");
		return false;
	}

	std::for_each( surfit_curvs->begin(), surfit_curvs->end(), regexp_fault(pos, f) );
	return true;
};

bool curve(REAL value, const char * pos) {
	d_curv * crv = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;
	
	f_curv * f = new f_curv(value, crv);
	functionals_push_back(f);
	return true;
};

bool curve_add(REAL value, REAL weight, const char * pos) {
	
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;
	
	d_curv * crv = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;
	
	f_curv * srf2 = new f_curv(value, crv);
	srf->add_functional(srf2, weight);
	return true;
};

bool curve_leq(REAL value, const char * curve_pos, REAL mult) {
	d_curv * curve = get_element<d_curv>(curve_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	f_curv_ineq * f = new f_curv_ineq(value, curve, true, mult);
	functionals_push_back(f);
	return true;
};

bool curve_geq(REAL value, const char * curve_pos, REAL mult) {
	d_curv * curve = get_element<d_curv>(curve_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	f_curv_ineq * f = new f_curv_ineq(value, curve, false, mult);
	functionals_push_back(f);
	return true;
};

bool curve_surf(const char * surf_pos, const char * curv_pos) {
	d_curv * curve = get_element<d_curv>(curv_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	f_curv_surf * f = new f_curv_surf(srf, curve);
	functionals_push_back(f);

	return true;
};

bool curve_surf_add(const char * surf_pos, REAL weight, const char * curv_pos) {
	
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	d_curv * curve = get_element<d_curv>(curv_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	f_curv_surf * f = new f_curv_surf(surf, curve);
	srf->add_functional(f, weight);
	return true;
};

bool curve_surf_leq(const char * surf_pos, const char * curv_pos, REAL mult) {
	
	d_curv * curve = get_element<d_curv>(curv_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	f_curv_surf_ineq * f = new f_curv_surf_ineq(surf, curve, true, mult);
	functionals_push_back(f);
	return true;
};

bool curve_surf_geq(const char * surf_pos, const char * curv_pos, REAL mult) {
	
	d_curv * curve = get_element<d_curv>(curv_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	f_curv_surf_ineq * f = new f_curv_surf_ineq(surf, curve, false, mult);
	functionals_push_back(f);
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
	functionals_push_back(f);
	return true;
};

bool area_add(REAL value, REAL weight, const char * pos, int inside) {
	
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;
	
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;
	
	f_area * srf2 = new f_area(value, area, (inside == 1) );
	srf->add_functional(srf2, weight);
	return true;
};

bool area_leq(REAL value, const char * area_pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_ineq * f = new f_area_ineq(value, area, true, mult, (inside == 1) );
	functionals_push_back(f);
	return true;
};

bool area_geq(REAL value, const char * area_pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_ineq * f = new f_area_ineq(value, area, false, mult, (inside == 1) );
	functionals_push_back(f);
	return true;
};

bool area_surf(const char * surf_pos, const char * area_pos, int inside) {

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_surf * f = new f_area_surf(surf, area, (inside == 1));
	functionals_push_back(f);
	return true;
};

bool area_surf_add(const char * surf_pos, REAL weight, const char * area_pos, int inside) {

	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_surf * f = new f_area_surf(surf, area, (inside == 1));
	srf->add_functional(f, weight);
	return true;
};

bool area_surf_leq(const char * surf_pos, const char * area_pos, REAL mult, int inside) {

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_surf_ineq * f = new f_area_surf_ineq(surf, area, true, mult, (inside == 1) );
	functionals_push_back(f);
	return true;
};

bool area_surf_geq(const char * surf_pos, const char * area_pos, REAL mult, int inside) {

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_surf_ineq * f = new f_area_surf_ineq(surf, area, false, mult, (inside == 1) );
	functionals_push_back(f);
	return true;
};

bool area_mean(REAL mean, const char * pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_area_mean * f = new f_area_mean(mean, area, mult, (inside == 1) );
	functionals_push_back(f);
	return true;
};

bool area_wmean(REAL mean, const char * area_pos, const char * surf_pos, REAL mult, int inside) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	f_area_wmean * f = new f_area_wmean(mean, srf, area, mult, (inside == 1) );
	functionals_push_back(f);
	return true;
};

bool area_completer(const char * area_pos, REAL D1, REAL D2, REAL alpha, REAL w, int inside) {
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_completer * f = new f_completer(D1, D2, alpha, w);
	f->set_area(area, (inside == 1));
	functionals_push_back(f);
	return true;
};

bool area_completer_add(REAL weight, const char * area_pos, REAL D1, REAL D2, REAL alpha, REAL w, int inside) {

	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_completer * f = new f_completer(D1, D2, alpha, w);
	f->set_area(area, (inside == 1));
	srf->add_functional(f, weight);
	return true;
};

struct regexp_contour
{
	regexp_contour(const char * ipos) : pos(ipos) {};
	void operator()(d_cntr * contour) 
	{
		if (contour->getName() == NULL)
			return;
		if ( RegExpMatch(pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour(\"%s\")", 
				 contour->getName()?contour->getName():"noname");
			f_cntr * f = new f_cntr(contour);
			functionals_push_back(f);
		}
	}
	const char * pos;
};

bool contour(const char * pos) {
	std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), regexp_contour(pos));
	return true;
};

struct regexp_contour_add
{
	regexp_contour_add(const char * ipos, functional * isrf, REAL iweight) : 
			   pos(ipos), srf(isrf), weight(iweight) {};
	void operator()(d_cntr * contour)
	{
		if (contour->getName() == NULL)
			return;
		if ( RegExpMatch(pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour_add(\"%s\")", 
				 contour->getName()?contour->getName():"noname");
			f_cntr * srf2 = new f_cntr(contour);
			srf->add_functional(srf2, weight);
		}
	}
	const char * pos;
	functional * srf;
	REAL weight;
};

bool contour_add(REAL weight, const char * pos) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), regexp_contour_add(pos, srf, weight));
	return true;
};

bool contour_leq(const char * cntr_pos, REAL mult) {
	d_cntr * contour = get_element<d_cntr>(cntr_pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;

	f_cntr_ineq * f = new f_cntr_ineq(contour, true, mult);
	functionals_push_back(f);
	return true;
};

bool contour_geq(const char * cntr_pos, REAL mult) {
	d_cntr * contour = get_element<d_cntr>(cntr_pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;

	f_cntr_ineq * f = new f_cntr_ineq(contour, false, mult);
	functionals_push_back(f);
	return true;
};

}; // namespace surfit;


