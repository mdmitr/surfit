
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

#ifndef __flow_lcm_simple_included__
#define __flow_lcm_simple_included__

#include "data.h"

namespace surfit {

class vec;
class intvec;

/*! \class lcm_simple
    \brief law of conservation of mass for homogeneous formation 
    (constants for formation permeability, thick and liquid viscosity) 
    and stationary filtration.
*/
class FLOW_EXPORT lcm_simple : public data {
public:
	//! constructor
	lcm_simple(REAL ipermeability, REAL iviscosity, REAL imultiplier, const char * name = NULL);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! formation permeability (constant for all area)
	REAL permeability; 

	//! fluid viscosity (constant for all area)
	REAL viscosity;    

	//! multiplier coefficient for Darcy law: speed = - permeability/viscosity*multiplier * grad(pressure)
	REAL multiplier;   
	
};

}; // namespace surfit;

#endif

