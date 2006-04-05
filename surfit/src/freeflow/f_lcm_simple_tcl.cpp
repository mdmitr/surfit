
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
#include "variables.h"
#include "f_lcm_simple.h"

namespace surfit {

bool lcm_simple(REAL permeability, REAL viscosity, REAL multiplier) {
	f_lcm_simple * f = new f_lcm_simple(permeability, viscosity, multiplier);
	functionals_push_back(f);
	return true;
};

bool lcm_simple_add(REAL weight, REAL permeability, REAL viscosity, REAL multiplier) {
	functional * fnc = get_modifiable_functional();
	if (fnc == NULL)
		return false;
	f_lcm_simple * f = new f_lcm_simple(permeability, viscosity, multiplier);
	fnc->add_functional(f, weight);
	return true;
};

}; // namespace surfit;

