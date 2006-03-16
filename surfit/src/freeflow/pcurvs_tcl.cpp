
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

#include "flow_ie.h"
#include "pcurvs_tcl.h"
#include "variables.h"
#include "f_lcm_simple.h"
#include "curv.h"
#include "area.h"
#include "cntr.h"
#include "prod_area.h"
#include "prod_iso.h"
#include "prod_cntr.h"

namespace surfit {

bool prod_area(REAL value, const char * pos) {

	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
	if (f == NULL)
		return false;
	
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_prod_area * ff = new f_prod_area(value, area);
	f->add_production(ff);
	return true;

};

bool prod_isoline(REAL value, const char * pos) {

	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
	if (f == NULL)
		return false;
	
	d_curv * crv = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;

	f_prod_iso * ff = new f_prod_iso(value, crv);
	f->add_production(ff);
	return true;

};

bool prod_contour(const char * pos) {

	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
	if (f == NULL)
		return false;
	
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;

	f_prod_cntr * ff = new f_prod_cntr(contour);
	f->add_production(ff);
	return true;

};

}; // namespace surfit;

