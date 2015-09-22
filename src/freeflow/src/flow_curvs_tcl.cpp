
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
#include "flow_curvs_tcl.h"
#include "variables.h"
#include "f_lcm_simple.h"
#include "curv.h"
#include "area.h"
#include "cntr.h"
#include "flow_area.h"
#include "flow_curv.h"
#include "flow_cntr.h"
#include "boolvec.h"

#include <algorithm>

namespace surfit {

struct match_flow_area
{
	match_flow_area(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			functional * fnc = get_modifiable_functional();
			if (fnc == NULL) {
				res->push_back(false);
				return;
			}
			f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
			if (f == NULL) {
				res->push_back(false);
				return;
			}

			writelog(LOG_MESSAGE,"creating gridding rule flow_area \"%s\"(%g)",area->getName(),value);
			f_flow_area * ff = new f_flow_area(value, area);
			f->add_flow(ff);
			res->push_back(true);	
		}
	}
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec * flow_area(REAL value, const char * pos) 
{
	match_flow_area qq(value, pos);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_flow_curve
{
	match_flow_curve(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_curv * curve)
	{
		if ( StringMatch(pos, curve->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			functional * fnc = get_modifiable_functional();
			if (fnc == NULL) {
				res->push_back(false);
				return;
			}
			f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
			if (f == NULL) {
				res->push_back(false);
				return;
			}

			writelog(LOG_MESSAGE,"creating gridding rule flow_curve \"%s\"(%g)",curve->getName(),value);
			f_flow_curv * ff = new f_flow_curv(value, curve);
			f->add_flow(ff);
			res->push_back(true);	
		}
	}
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec * flow_curve(REAL value, const char * pos)
{
	match_flow_curve qq(value, pos);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_flow_contour
{
	match_flow_contour(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_cntr * contour)
	{
		if ( StringMatch(pos, contour->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			functional * fnc = get_modifiable_functional();
			if (fnc == NULL) {
				res->push_back(false);
				return;
			}
			f_lcm_simple * f = dynamic_cast<f_lcm_simple *>(fnc);
			if (f == NULL) {
				res->push_back(false);
				return;
			}
			writelog(LOG_MESSAGE,"creating gridding rule flow_cntr \"%s\"",contour->getName());
			f_flow_cntr * ff = new f_flow_cntr(contour);
			f->add_flow(ff);
			res->push_back(true);	
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * flow_contour(const char * pos) 
{
	match_flow_contour qq(pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

}; // namespace surfit;

