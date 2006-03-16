
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
#include "prod_points_tcl.h"
#include "points.h"
#include "prod_points.h"
#include "variables.h"
#include "f_lcm_simple.h"

namespace surfit {

bool prod_points(const char * pos) {

	if (functionals->size() == 0)
		return false;
	functional * fnc = *(functionals->end()-1);
	f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
	if (f == NULL)
		return false;
	
	d_points * tsk = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (tsk == NULL)
		return false;

	f_prod_points * ff = new f_prod_points(tsk);
	f->add_production(ff);
	return true;

};

}; // namespace surfit;

