
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
#include "vec.h"

#include <float.h>
#include <algorithm>

namespace surfit {

struct match_surf_debit
{
	match_surf_debit(REAL ix, REAL iy, REAL iperm, REAL ivisc, REAL imult, const char * ipos) 
		: x(ix), y(iy), perm(iperm), visc(ivisc), mult(imult), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			res->push_back( _surf_debit(surf, x, y, perm, visc, mult) );
		}
	}
	REAL x;
	REAL y;
	REAL perm;
	REAL visc;
	REAL mult;
	const char * pos;
	vec * res;
};

vec * surf_debit(REAL x, REAL y, REAL perm, REAL visc, REAL mult, const char * pos) 
{
	match_surf_debit qq(x,y,perm, visc, mult, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_debit_rect
{
	match_surf_debit_rect(REAL ix1, REAL iy1, REAL ix2, REAL iy2, REAL iperm, REAL ivisc, REAL imult, const char * ipos) 
		: x1(ix1), y1(iy1), x2(ix2), y2(iy2), perm(iperm), visc(ivisc), mult(imult), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			res->push_back( _surf_debit_rect(surf, x1, y1, x2, y2, perm, visc, mult) );
		}
	}
	REAL x1, y1;
	REAL x2, y2;
	REAL perm;
	REAL visc;
	REAL mult;
	const char * pos;
	vec * res;
};

vec * surf_debit_rect(REAL x1, REAL y1, REAL x2, REAL y2, 
		     REAL perm, REAL visc, REAL mult, 
		     const char * pos) 
{
	match_surf_debit_rect qq(x1, y1, x2, y2, perm, visc, mult, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

}; // namespace surfit;

