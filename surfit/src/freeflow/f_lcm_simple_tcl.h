
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

FLOW_EXPORT
bool lcm_simple(REAL permeability = 1, REAL viscosity = 1, REAL multiplier = 1);

FLOW_EXPORT
bool lcm_simple_add(REAL weight, REAL permeability = 1, REAL viscosity = 1, REAL multiplier = 1);

}; // namespace surfit;

#endif

