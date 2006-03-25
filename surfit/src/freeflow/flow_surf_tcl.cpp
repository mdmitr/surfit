
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
#include "flow_surf_tcl.h"
#include "flow_surf_internal.h"
#include "surf.h"
#include <float.h>

namespace surfit {

REAL surf_debit(REAL x, REAL y, REAL perm, REAL visc, REAL mult, const char * pos) {
	d_surf * fnc = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!fnc)
		return FLT_MAX;
	return _surf_debit(fnc, x, y, perm, visc, mult);

};

REAL surf_debit_rect(REAL x1, REAL y1, REAL x2, REAL y2, 
		     REAL perm, REAL visc, REAL mult, 
		     const char * pos) {
	d_surf * fnc = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!fnc)
		return FLT_MAX;
	return _surf_debit_rect(fnc, x1, y1, x2, y2, perm, visc, mult);

};

}; // namespace surfit;

