
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

#include <algorithm>

namespace surfit {

struct regexp_dem
{
	regexp_dem(const char * ipos) : pos(ipos) {};
	void operator()(d_dem * dem) 
	{
		if (dem->getName() == NULL)
			return;
		if ( RegExpMatch(pos, dem->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule dem(\"%s\")", 
				 dem->getName()?dem->getName():"noname");
			f_dem * f = new f_dem(dem);
			functionals_push_back(f);
		}
	}
	const char * pos;
};

bool dem(const char * pos) {
	std::for_each(globe_dems->begin(), globe_dems->end(), regexp_dem(pos));
	return true;
};

struct regexp_dem_add
{
	regexp_dem_add(const char * ipos, functional * isrf, REAL iweight) : 
			   pos(ipos), srf(isrf), weight(iweight) {};
	void operator()(d_dem * dem)
	{
		if (dem->getName() == NULL)
			return;
		if ( RegExpMatch(pos, dem->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule dem_add(\"%s\")", 
				 dem->getName()?dem->getName():"noname");
			f_dem * srf2 = new f_dem(dem);
			srf->add_functional(srf2, weight);
		}
	}
	const char * pos;
	functional * srf;
	REAL weight;
};

bool dem_add(REAL weight, const char * pos) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(globe_dems->begin(), globe_dems->end(), regexp_dem_add(pos, srf, weight));
	return true;
};

}; // namespace surfit;

