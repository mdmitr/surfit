
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

#include "ie.h"

#ifdef HAVE_GL_WORKS

#include "projector.h"
#include "func.h"
#include "func_internal.h"
#include "funcs.h"

#include <float.h>

namespace surfit {

REAL get_projected_value(REAL x, REAL y) {

	REAL z = 0;
	REAL val;
	int cnt = 0;

	surfit::func * fnc = surfit::_get_surfit_func();
	if (fnc) {
		val = fnc->getValue(x,y); 
		if (val != fnc->undef_value) {
			z += val;
			cnt++;
		}
	}

	int size = surfit::funcs_size();
	int i;
	for (i = 0; i < size; i++) {
		fnc = surfit::funcs_at(i);
		if (fnc) {
			val = fnc->getValue(x,y); 
			if (val != fnc->undef_value) {
				z += val;
				cnt++;
			}
		}
	}

	if (cnt == 0)
		return FLT_MAX;

	return z/cnt;
};

}; // namespace surfit;

#endif

