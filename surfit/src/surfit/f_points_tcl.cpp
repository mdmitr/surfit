
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
#include "boolvec.h"

#include <algorithm>

namespace surfit {

struct match_points
{
	match_points(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"creating gridding rule points(\"%s\")", pnts->getName());
			f_points * fnc = new f_points(pnts);
			functionals_push_back(fnc);
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * points(const char * pos) 
{
	match_points qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_points_add
{
	match_points_add(const char * ipos, REAL iweight) : pos(ipos), weight(iweight), res(NULL) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule points_add(%g,\"%s\")", weight, pnts->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * ff = get_modifiable_functional();
			if (ff == NULL) {
				res->push_back(false);
				return;
			}
			f_points * fnc2 = new f_points(pnts);
			ff->add_functional(fnc2, weight);
			res->push_back(true);
		}
	}
	const char * pos;
	REAL weight;
	boolvec * res;
};

boolvec * points_add(REAL weight, const char * pos) 
{
	match_points_add qq(pos, weight);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_points_leq
{
	match_points_leq(const char * ipos, REAL ipenalty_factor) : pos(ipos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule points_leq(\"%s\",%g)", pnts->getName(), get_mult(penalty_factor));
			if (res == NULL)
				res = create_boolvec();
			f_points_ineq * inpnts = new f_points_ineq(pnts, true, get_mult(penalty_factor));
			functionals_push_back(inpnts);
			res->push_back(true);
		}
	}
	const char * pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * points_leq(const char * pos, REAL penalty_factor) 
{
	match_points_leq qq(pos, penalty_factor);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_points_geq
{
	match_points_geq(const char * ipos, REAL ipenalty_factor) : pos(ipos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch( pos, pnts->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule points_geq(\"%s\",%g)", pnts->getName(), get_mult(penalty_factor));
			f_points_ineq * inpnts = new f_points_ineq(pnts, false, get_mult(penalty_factor));
			functionals_push_back(inpnts);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * points_geq(const char * pos, REAL penalty_factor) 
{
	match_points_geq qq(pos, penalty_factor);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

}; // namespace surfit;

