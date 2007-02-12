
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
#include "f_points_tcl.h"
#include "pnts_internal.h"
#include "variables.h"
#include "f_points.h"
#include "surfit_data.h"
#include "points.h"
#include "f_points_ineq.h"

namespace surfit {

bool points(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	f_points * fnc = new f_points(pnts);
	functionals_push_back(fnc);
	return true;
};

bool points_add(REAL weight, const char * pos) {
	
	functional * fnc = get_modifiable_functional();
	if (fnc == NULL)
		return false;

	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	f_points * fnc2 = new f_points(pnts);
	fnc->add_functional(fnc2, weight);
	return true;
};

bool points_leq(const char * pos, REAL mult) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	f_points_ineq * inpnts = new f_points_ineq(pnts, true, mult);
	functionals_push_back(inpnts);
	return true;
};

bool points_geq(const char * pos, REAL mult) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	f_points_ineq * inpnts = new f_points_ineq(pnts, false, mult);
	functionals_push_back(inpnts);
	return true;
};

}; // namespace surfit;

