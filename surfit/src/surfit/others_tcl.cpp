
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
#include "others_tcl.h"
#include "f_completer.h"
#include "f_value.h"
#include "f_mean.h"
#include "f_wmean.h"
#include "f_ineq.h"
#include "f_hist.h"
#include "variables.h"
#include "curv.h"
#include "curv_internal.h"
#include "surf.h"
#include "hist.h"
#include "interp.h"
#include "boolvec.h"
#include "intvec.h"
#include "strvec.h"

#include <algorithm>

namespace surfit {

bool completer(REAL D1, REAL D2, REAL alpha, REAL w) 
{
	writelog(LOG_MESSAGE,"creating gridding rule completer(%g,%g,%g,%g)",
		D1, D2, alpha, w);
	f_completer * f_cmpltr = new f_completer(D1, D2, alpha, w);
	functionals_push_back(f_cmpltr);
	return true;
};

bool completer_add(REAL weight, REAL D1, REAL D2, REAL alpha, REAL w) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	writelog(LOG_MESSAGE,"creating gridding rule completer_add(%g,%g,%g,%g,%g)",
		weight, D1, D2, alpha, w);
	
	f_completer * f_cmpltr = new f_completer(D1, D2, alpha, w);
	srf->add_functional(f_cmpltr, weight);
	return true;
};

bool value(REAL value) 
{
	writelog(LOG_MESSAGE,"creating gridding rule value(%g)",value);
	f_value * f = new f_value(value);
	functionals_push_back(f);
	return true;
};

bool value_add(REAL weight, REAL value) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	writelog(LOG_MESSAGE,"creating gridding rule value_add(%g,%g)",weight, value);

	f_value * f = new f_value(value);
	srf->add_functional(f, weight);
	return true;
};

bool mean(REAL value, REAL mult) 
{
	writelog(LOG_MESSAGE,"creating gridding rule mean(%g,%g)",value,mult);
	f_mean * f = new f_mean(value, mult);
	functionals_push_back(f);
	return true;
};

struct match_wmean
{
	match_wmean(REAL ivalue, const char * isurf_pos, REAL imult) : value(ivalue), surf_pos(isurf_pos), mult(imult) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule wmean(%g,\"%s\",%g)",
				value, surf->getName(), mult);
			if (res == NULL)
				res = create_boolvec();
			f_wmean * f = new f_wmean(value, surf, mult);
			functionals_push_back(f);
			res->push_back(true);
		}
	}
	REAL value;
	const char * surf_pos;
	REAL mult;
	boolvec * res;
};

boolvec * wmean(REAL value, const char * surf_pos, REAL mult) 
{
	match_wmean qq(value, surf_pos, mult);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

bool leq(REAL value, REAL mult) 
{
	writelog(LOG_MESSAGE,"creating gridding rule leq(%g,%g)",value,mult);
	f_ineq * f = new f_ineq(value, true, mult);
	functionals_push_back(f);
	return true;
};

bool geq(REAL value, REAL mult) 
{
	writelog(LOG_MESSAGE,"creating gridding rule geq(%g,%g)",value,mult);
	f_ineq * f = new f_ineq(value, false, mult);
	functionals_push_back(f);
	return true;
};

struct match_hist 
{
	match_hist(const char * ipos, REAL imult) : pos(ipos), mult(imult) {};
	void operator()(d_hist * hist) 
	{
		if ( StringMatch( pos, hist->getName() ) ) 
		{
			writelog(LOG_MESSAGE, "creating gridding rule hist(\"%s\",%g)",
				hist->getName(), mult);
			f_hist * f = new f_hist(hist, mult);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL mult;
	boolvec * res;
};

boolvec * hist(const char * pos, REAL mult) 
{
	match_hist qq(pos, mult);
	qq = std::for_each(surfit_hists->begin(), surfit_hists->end(), qq);
	return qq.res;
};

}; // namespace surfit;


