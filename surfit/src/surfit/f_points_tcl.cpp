
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

#include "surfit_ie.h"
#include "f_points_tcl.h"
#include "pnts_internal.h"
#include "variables.h"
#include "f_points.h"
#include "surfit_data.h"
#include "points.h"
#include "f_points_ineq.h"
#include "interp.h"

#include <algorithm>

namespace surfit {

struct match_points
{
	match_points(const char * ipos) : pos(ipos) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule points(\"%s\")", pnts->getName());
			f_points * fnc = new f_points(pnts);
			functionals_push_back(fnc);
		}
	}
	const char * pos;
};

bool points(const char * pos) 
{
	std::for_each(surfit_pnts->begin(), surfit_pnts->end(), match_points(pos));
	return true;
};

struct match_points_add
{
	match_points_add(const char * ipos, REAL iweight, functional * iff) : pos(ipos), weight(iweight), ff(iff) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule points_add(%g,\"%s\")", weight, pnts->getName());
			f_points * fnc2 = new f_points(pnts);
			ff->add_functional(fnc2, weight);
		}
	}
	const char * pos;
	REAL weight;
	functional * ff;
};

bool points_add(REAL weight, const char * pos) 
{
	functional * fnc = get_modifiable_functional();
	if (fnc == NULL)
		return false;

	std::for_each(surfit_pnts->begin(), surfit_pnts->end(), match_points_add(pos, weight, fnc));
	return true;
};

struct match_points_leq
{
	match_points_leq(const char * ipos, REAL imult) : pos(ipos), mult(imult) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule points_leq(\"%s\",%g)", pnts->getName(), mult);
			f_points_ineq * inpnts = new f_points_ineq(pnts, true, mult);
			functionals_push_back(inpnts);
		}
	}
	const char * pos;
	REAL mult;
};

bool points_leq(const char * pos, REAL mult) 
{
	std::for_each(surfit_pnts->begin(), surfit_pnts->end(), match_points_leq(pos, mult));
	return true;
};

struct match_points_geq
{
	match_points_geq(const char * ipos, REAL imult) : pos(ipos), mult(imult) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule points_geq(\"%s\",%g)", pnts->getName(), mult);
			f_points_ineq * inpnts = new f_points_ineq(pnts, true, mult);
			functionals_push_back(inpnts);
		}
	}
	const char * pos;
	REAL mult;
};

bool points_geq(const char * pos, REAL mult) 
{
	std::for_each(surfit_pnts->begin(), surfit_pnts->end(), match_points_geq(pos, mult));
	return true;
};

}; // namespace surfit;

