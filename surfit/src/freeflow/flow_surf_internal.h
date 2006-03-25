
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

#ifndef __surfit_flow_surf_internal_included__
#define __surfit_flow_surf_internal_included__

namespace surfit {

class d_surf;

FLOW_EXPORT
/*!  \ingroup internal_psurf
     \fn REAL _surf_debit(d_surf * srf, REAL x, REAL y, REAL perm, REAL visc, REAL mult);
     \brief calculates debit at point (x,y), using four neighbour cells
*/
REAL _surf_debit(d_surf * srf, REAL x, REAL y, REAL perm, REAL visc, REAL mult);

FLOW_EXPORT
/*! \ingroup internal_psurf
    \fn REAL _surf_debit_rect(d_surf * srf, REAL x1, REAL y1, REAL x2, REAL y2, REAL perm, REAL visc, REAL mult);
    \brief calculates debit in rect
*/
REAL _surf_debit_rect(d_surf * srf, REAL x1, REAL y1, REAL x2, REAL y2, REAL perm, REAL visc, REAL mult);

}; // namespace surfit;

#endif

