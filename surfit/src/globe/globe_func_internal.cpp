
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

#include "globe_ie.h"
#include "dem.h"
#include "func_tcl.h"
#include "shortvec.h"
#include "vec.h"
#include "func.h"
#include "grid.h"

#include <float.h>

namespace surfit {

d_dem * _func_to_dem(d_func * fnc) {
	shortvec * coeff = create_shortvec( fnc->coeff->size() );
	int i;
	REAL val;
	for (i = 0; i < fnc->coeff->size(); i++) {
		val = (*(fnc->coeff))(i);
		if (val == fnc->undef_value)
			(*coeff)(i) = SHRT_MAX;
		else
			(*coeff)(i) = (short)val;
	};

	d_grid * fgrd = fnc->grd;
	d_grid * grd = new d_grid(fgrd);

	d_dem * res = create_dem(coeff, grd);
	res->undef_value = SHRT_MAX;
	res->setName(fnc->getName());

	return res;
};

}; // namespace surfit;

