
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

#ifndef __surfit_flow_surf_tcl_included__
#define __surfit_flow_surf_tcl_included__

namespace surfit {

/*! \ingroup tcl_freeflow_surf
    \fn REAL surf_debit(REAL x, REAL y, REAL perm, REAL visc, REAL mult, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_debit x y perm visc mult "surface_name_or_position"

    \par Description:
    calculates debit at point (x,y), using four neighbour cells
*/
REAL surf_debit(REAL x, REAL y, REAL perm, REAL visc, REAL mult, const char * surface_name_or_position = "0");

/*! \ingroup tcl_freeflow_surf
    \fn REAL surf_debit_rect(REAL x1, REAL y1, REAL x2, REAL y2, REAL perm, REAL visc, REAL mult, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_debit_rect x1 y1 x2 y2 perm visc mult "surface_name_or_position"

    \par Description:
    calculates debit in rect
*/
REAL surf_debit_rect(REAL x1, REAL y1, REAL x2, REAL y2, REAL perm, REAL visc, REAL mult, const char * surface_name_or_position = "0");


}; // namespace surfit;

#endif

