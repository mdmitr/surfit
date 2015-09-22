
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
#include "dems_tcl.h"
#include "dem.h"
#include "f_dem.h"
#include "variables.h"
#include "interp.h"
#include "boolvec.h"

#include <algorithm>

namespace surfit {

struct match_dem
{
	match_dem(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule dem(\"%s\")", dem->getName());
			if (res == NULL)
				res = create_boolvec();
			f_dem * f = new f_dem(dem);
			functionals_push_back(f);
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * dem(const char * pos) 
{
	match_dem qq(pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_add
{
	match_dem_add(const char * ipos, REAL iweight) : 
			   pos(ipos), weight(iweight), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule dem_add(\"%s\")",dem->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * srf = get_modifiable_functional();
			if (srf == NULL) {
				res->push_back(false);
				return;
			}
			f_dem * srf2 = new f_dem(dem);
			srf->add_functional(srf2, weight);
			res->push_back(true);
		}
	}
	const char * pos;
	REAL weight;
	boolvec * res;
};

boolvec * dem_add(REAL weight, const char * pos) 
{
	match_dem_add qq(pos, weight);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

}; // namespace surfit;

