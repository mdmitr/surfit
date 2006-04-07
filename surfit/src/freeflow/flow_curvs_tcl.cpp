
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
#include "flow_curvs_tcl.h"
#include "variables.h"
#include "f_lcm_simple.h"
#include "curv.h"
#include "area.h"
#include "cntr.h"
#include "flow_area.h"
#include "flow_curv.h"
#include "flow_cntr.h"

namespace surfit {

bool flow_area(REAL value, const char * pos) {

	functional * fnc = get_modifiable_functional();
	if (fnc == NULL)
		return false;
	f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
	if (f == NULL)
		return false;
	
	d_area * area = get_element<d_area>(pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return false;

	f_flow_area * ff = new f_flow_area(value, area);
	f->add_flow(ff);
	return true;

};

bool flow_curve(REAL value, const char * pos) {

	functional * fnc = get_modifiable_functional();
	if (fnc == NULL)
		return false;
	f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
	if (f == NULL)
		return false;
	
	d_curv * crv = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;

	f_flow_curv * ff = new f_flow_curv(value, crv);
	f->add_flow(ff);
	return true;

};

bool flow_contour(const char * pos) {

	functional * fnc = get_modifiable_functional();
	if (fnc == NULL)
		return false;
	f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
	if (f == NULL)
		return false;
	
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;

	f_flow_cntr * ff = new f_flow_cntr(contour);
	f->add_flow(ff);
	return true;

};

}; // namespace surfit;

