
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

#ifndef __freeflow_f_lcm_simple_tcl_included__
#define __freeflow_f_lcm_simple_tcl_included__

namespace surfit {

/*! \ingroup tcl_freeflow_rules
    \fn bool lcm_simple(REAL permeability = 1, REAL viscosity = 1, REAL scale = 1);

    \par Tcl syntax:
    lcm_simple permeability viscosity multiplier

    \par Description:
    This gridding rule implements the law of conservation of mass in the simplest formulation 
    (with constant formation permeability and constant liquid viscosity).

    \param permeability constant value for a formation permeability (\f$ m^2 \f$).
    \param viscosity constant value for liquid viscosity (\f$ Pa \cdot sec \f$)
    \param scale scale factor.

    \par Math:
    
\f[
A_{i,j} = -\frac{1}{2} 
\left(S \cdot \frac{k}{\mu}\right)
\left[
\frac{h_y h_z}{h_x} \left(u_{i+1,j} - u_{i,j} \right)^2 +
\frac{h_x h_z}{h_y} \left(u_{i,j+1} - u_{i,j} \right)^2 +
\frac{h_y h_z}{h_x} \left(u_{i,j} - u_{i-1,j} \right)^2 +
\frac{h_x h_z}{h_y} \left(u_{i,j} - u_{i,j-1} \right)^2
\right],
\f]
where 
\li \f$ k \f$ - formation permeability (\f$ m^2 \f$)
\li \f$ \mu \f$ - liquid viscosity (\f$ Pa \cdot sec \f$)
\li \f$ S \f$ - scale factor
\li \f$ u_{i,j} \f$ - pressure in (i,j) cell (\f$ Pa \f$)
\li \f$ h_x, h_y, h_z \f$ - cell size (\f$ m \f$) in X, Y and Z direction ( \f$ h_z \f$ is equal to formation thick ) 
*/
FLOW_EXPORT
bool lcm_simple(REAL permeability = 1, REAL viscosity = 1, REAL multiplier = 1);

FLOW_EXPORT
bool lcm_simple_add(REAL weight, REAL permeability = 1, REAL viscosity = 1, REAL multiplier = 1);

}; // namespace surfit;

#endif

