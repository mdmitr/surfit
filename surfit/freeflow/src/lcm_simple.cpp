
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

#include "flow_ie.h"
#include "lcm_simple.h"

namespace surfit {

lcm_simple::lcm_simple(REAL ipermeability, REAL iviscosity, REAL imultiplier, const char * newname) {
	permeability = ipermeability;
	viscosity = iviscosity;
	multiplier = imultiplier;
	setName(newname);
};

bool lcm_simple::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	return false;
};

bool lcm_simple::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

}; // namespace surfit

