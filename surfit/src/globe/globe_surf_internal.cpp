
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
#include "surf_tcl.h"
#include "shortvec.h"
#include "vec.h"
#include "surf.h"
#include "grid.h"

#include <float.h>

namespace surfit {

d_dem * _surf_to_dem(d_surf * srf) {
	shortvec * coeff = create_shortvec( srf->coeff->size() );
	size_t i;
	REAL val;
	for (i = 0; i < srf->coeff->size(); i++) {
		val = (*(srf->coeff))(i);
		if (val == srf->undef_value)
			(*coeff)(i) = SHRT_MAX;
		else
			(*coeff)(i) = (short)val;
	};

	d_grid * fgrd = srf->grd;
	d_grid * grd = create_grid(fgrd);

	d_dem * res = create_dem(coeff, grd);
	res->undef_value = SHRT_MAX;
	res->setName(srf->getName());

	return res;
};

}; // namespace surfit;

