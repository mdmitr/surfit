
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
#include "flow_points_tcl.h"
#include "points.h"
#include "flow_points.h"
#include "variables.h"
#include "f_lcm_simple.h"
#include "boolvec.h"

#include <algorithm>

namespace surfit {

struct match_flow_points
{
	match_flow_points(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch(pos, pnts->getName()) )
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

			f_flow_points * ff = new f_flow_points(pnts);
			f->add_flow(ff);
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * flow_points(const char * pos) 
{
	match_flow_points qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

}; // namespace surfit;

