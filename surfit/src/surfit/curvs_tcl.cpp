
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
#include "curvs_tcl.h"
#include "variables.h"
#include "curv.h"
#include "area.h"
#include "cntr.h"
#include "surf.h"
#include "hist.h"
#include "curv_internal.h"
#include "functional.h"
#include "f_area.h"
#include "f_area_ineq.h"
#include "f_area_surf.h"
#include "f_area_surf_ineq.h"
#include "f_area_mean.h"
#include "f_area_wmean.h"
#include "f_area_hist.h"
#include "f_cntr.h"
#include "f_cntr_ineq.h"
#include "f_curv.h"
#include "f_curv_ineq.h"
#include "f_curv_surf.h"
#include "f_curv_surf_ineq.h"
#include "f_completer.h"
#include "variables_tcl.h"
#include "interp.h"

#include <algorithm>

namespace surfit {

struct match_fault
{
	match_fault(const char * ipos, faultable * _f) : pos(ipos), f(_f) {};
	void operator()(d_curv * fault) 
	{
		if ( StringMatch(pos, fault->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule fault(\"%s\")",fault->getName());
			f->add_fault(fault);
		}
	}
	const char * pos;
	faultable * f;
};

bool fault(const char * pos) {
	if (functionals->size() == 0) {
		writelog(LOG_ERROR,"No gridding rule modifiable with \"fault\" rule present!");
		return false;
	}
	functional * srf = *(functionals->end()-1);

	if ((srf->getType() & F_FAULT) == 0) {
		writelog(LOG_ERROR,"\"%s\" rule is not modifiable with \"fault\" rule!", srf->getName());
		return false;
	}

	faultable * f = static_cast<faultable *>(srf);
	if (f == NULL) {
		writelog(LOG_ERROR,"No gridding rule modifiable with \"fault\" rule present!");
		return false;
	}

	std::for_each( surfit_curvs->begin(), surfit_curvs->end(), match_fault(pos, f) );
	return true;
};

struct match_curve
{
	match_curve(const char * ipos, REAL ival) : pos(ipos), val(ival) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve(%g,\"%s\")",
				 val, crv->getName());
			f_curv * f = new f_curv(val, crv);
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL val;
};

bool curve(REAL value, const char * pos) 
{
	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve(pos, value));
	return true;
};

struct match_curve_add
{
	match_curve_add(const char * ipos, REAL ival, REAL iweight, functional * iff) : pos(ipos), val(ival), weight(iweight), ff(iff) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve(%g,%g,\"%s\")", 
				 val, weight, crv->getName());
			f_curv * f = new f_curv(val, crv);
			ff->add_functional(f, weight);
		}
	}
	const char * pos;
	REAL val;
	REAL weight;
	functional * ff;
};

bool curve_add(REAL value, REAL weight, const char * pos) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve_add(pos, value, weight, srf));
	return true;
};

struct match_curve_leq
{
	match_curve_leq(const char * ipos, REAL ival, REAL imult) : pos(ipos), val(ival), mult(imult) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_leq(%g,\"%s\",%g)", 
				 val, crv->getName()), mult;
			f_curv_ineq * f = new f_curv_ineq(val, crv, true, mult);
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL val;
	REAL mult;
};

bool curve_leq(REAL value, const char * curve_pos, REAL mult) 
{
	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve_leq(curve_pos, value, mult));
	return true;
};

struct match_curve_geq
{
	match_curve_geq(const char * ipos, REAL ival, REAL imult) : pos(ipos), val(ival), mult(imult) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_geq(%g,\"%s\",%g)", 
				 val, crv->getName(), mult);
			f_curv_ineq * f = new f_curv_ineq(val, crv, false, mult);
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL val;
	REAL mult;
};

bool curve_geq(REAL value, const char * curve_pos, REAL mult) 
{
	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve_geq(curve_pos, value, mult));
	return true;
};

struct match_curve_surf2
{
	match_curve_surf2(const char * isurf_pos, d_curv * icrv) : surf_pos(isurf_pos), crv(icrv) {};

	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf(\"%s\",\"%s\")", 
				 srf->getName(),crv->getName());
			f_curv_surf * f = new f_curv_surf(srf, crv);
			functionals_push_back(f);
		}
	}

	const char * surf_pos;
	d_curv * crv;
};

struct match_curve_surf
{
	match_curve_surf(const char * isurf_pos, const char * icurv_pos) : surf_pos(isurf_pos), curv_pos(icurv_pos) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_curve_surf2(surf_pos, crv));
		}
	}
	const char * surf_pos;
	const char * curv_pos;
};

bool curve_surf(const char * surf_pos, const char * curv_pos) 
{
	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve_surf(surf_pos, curv_pos));
	return true;
};

struct match_curve_surf_add2
{
	match_curve_surf_add2(const char * isurf_pos, d_curv * icrv, REAL iweight, functional * iff) : surf_pos(isurf_pos), crv(icrv), weight(iweight), ff(iff) {};

	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf_add(\"%s\",%g,\"%s\")", 
				 srf->getName(),weight,crv->getName());
			f_curv_surf * f = new f_curv_surf(srf, crv);
			ff->add_functional(f, weight);
		}
	}

	const char * surf_pos;
	d_curv * crv;
	REAL weight;
	functional * ff;
};

struct match_curve_surf_add
{
	match_curve_surf_add(const char * isurf_pos, const char * icurv_pos, REAL iweight, functional * iff) : surf_pos(isurf_pos), curv_pos(icurv_pos), weight(iweight), ff(iff) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_curve_surf_add2(surf_pos, crv, weight, ff));
		}
	}
	const char * surf_pos;
	const char * curv_pos;
	REAL weight;
	functional * ff;
};

bool curve_surf_add(const char * surf_pos, REAL weight, const char * curv_pos) {
	
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve_surf_add(surf_pos, curv_pos, weight, srf));
	return true;
};

struct match_curve_surf_leq2
{
	match_curve_surf_leq2(const char * isurf_pos, d_curv * icrv, REAL imult) : surf_pos(isurf_pos), crv(icrv), mult(imult) {};

	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf_leq(\"%s\",\"%s\",%g)", 
				 srf->getName(),crv->getName(),mult);
			f_curv_surf_ineq * f = new f_curv_surf_ineq(srf, crv, true, mult);
			functionals_push_back(f);
		}
	}

	const char * surf_pos;
	d_curv * crv;
	REAL mult;
};

struct match_curve_surf_leq
{
	match_curve_surf_leq(const char * isurf_pos, const char * icurv_pos, REAL imult) : surf_pos(isurf_pos), curv_pos(icurv_pos), mult(imult) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_curve_surf_leq2(surf_pos, crv, mult));
		}
	}
	const char * surf_pos;
	const char * curv_pos;
	REAL mult;
};

bool curve_surf_leq(const char * surf_pos, const char * curv_pos, REAL mult) 
{
	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve_surf_leq(surf_pos, curv_pos, mult));	
	return true;
};

struct match_curve_surf_geq2
{
	match_curve_surf_geq2(const char * isurf_pos, d_curv * icrv, REAL imult) : surf_pos(isurf_pos), crv(icrv), mult(imult) {};

	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf_geq(\"%s\",\"%s\",%g)", 
				 srf->getName(),crv->getName(),mult);
			f_curv_surf_ineq * f = new f_curv_surf_ineq(srf, crv, false, mult);
			functionals_push_back(f);
		}
	}

	const char * surf_pos;
	d_curv * crv;
	REAL mult;
};

struct match_curve_surf_geq
{
	match_curve_surf_geq(const char * isurf_pos, const char * icurv_pos, REAL imult) : surf_pos(isurf_pos), curv_pos(icurv_pos), mult(imult) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_curve_surf_geq2(surf_pos, crv, mult));
		}
	}
	const char * surf_pos;
	const char * curv_pos;
	REAL mult;
};

bool curve_surf_geq(const char * surf_pos, const char * curv_pos, REAL mult) 
{
	std::for_each(surfit_curvs->begin(), surfit_curvs->end(), match_curve_surf_geq(surf_pos, curv_pos, mult));	
	return true;
};

struct match_area
{
	match_area(const char * ipos, REAL ivalue, int iinside) : pos(ipos), value(ivalue), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (value == undef_value) 
				writelog(LOG_MESSAGE,"creating gridding rule area(undef,\"%s\")", area->getName());
			else
			writelog(LOG_MESSAGE,"creating gridding rule area(%g,\"%s\")", 
				 value, area->getName());
			f_area * f = new f_area(value, area, (inside == 1));
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL value;
	int inside;
};

bool area(const char * Value, const char * pos, int inside) 
{
	REAL value = undef_value;
	if (strcmp(Value,"undef") != 0) {
		value = atof(Value);
	}

	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area(pos, value, inside));
	return true;
};

struct match_area_add
{
	match_area_add(const char * ipos, REAL ivalue, REAL iweight, int iinside, functional * iff) : pos(ipos), value(ivalue), weight(iweight), inside(iinside), ff(iff) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_add(%g,%g,\"%s\")", 
				 value,weight,area->getName());
			f_area * f = new f_area(value, area, (inside == 1));
			ff->add_functional(f, weight);
		}
	}
	const char * pos;
	REAL value;
	REAL weight;
	int inside;
	functional * ff;
};

bool area_add(REAL value, REAL weight, const char * pos, int inside) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;
		
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_add(pos, value, weight, inside, srf));
	return true;
};

struct match_area_leq
{
	match_area_leq(const char * ipos, REAL ivalue, REAL imult, int iinside) : pos(ipos), value(ivalue), mult(imult), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_leq(%g,\"%s\",%g,%d)", 
				 value, area->getName(), mult, inside);
			f_area_ineq * f = new f_area_ineq(value, area, true, (inside == 1));
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL value;
	REAL mult;
	int inside;
};

bool area_leq(REAL value, const char * area_pos, REAL mult, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_leq(area_pos, value, mult, inside));
	return true;
};

struct match_area_geq
{
	match_area_geq(const char * ipos, REAL ivalue, REAL imult, int iinside) : pos(ipos), value(ivalue), mult(imult), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_geq(%g,\"%s\",%g,%d)", 
				 value, area->getName(), mult, inside);
			f_area_ineq * f = new f_area_ineq(value, area, false, (inside == 1));
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL value;
	REAL mult;
	int inside;
};

bool area_geq(REAL value, const char * area_pos, REAL mult, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_geq(area_pos, value, mult, inside));
	return true;
};

struct match_area_surf2
{
	match_area_surf2(const char * isurf_pos, d_area * iarea, int iinside) : surf_pos(isurf_pos), area(iarea), inside(iinside) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf(\"%s\",\"%s\")",
				surf->getName(),area->getName());
			f_area_surf * f = new f_area_surf(surf, area, (inside==1));
			functionals_push_back(f);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
};

struct match_area_surf
{
	match_area_surf(const char * isurf_pos, const char * iarea_pos, int iinside) : surf_pos(isurf_pos), area_pos(iarea_pos), inside(iinside) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_area_surf2(surf_pos, area, inside));
		}

	}
	const char * surf_pos;
	const char * area_pos;
	int inside;
};

bool area_surf(const char * surf_pos, const char * area_pos, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_surf(surf_pos, area_pos, inside));
	return true;
};

struct match_area_surf_add2
{
	match_area_surf_add2(const char * isurf_pos, d_area * iarea, int iinside, REAL iweight, functional * iff) : surf_pos(isurf_pos), area(iarea), inside(iinside), weight(iweight), ff(iff) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf_add(\"%s\",%g,\"%s\")",
				surf->getName(),weight,area->getName());
			f_area_surf * f = new f_area_surf(surf, area, (inside==1));
			ff->add_functional(f, weight);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
	REAL weight;
	functional * ff;
};

struct match_area_surf_add
{
	match_area_surf_add(const char * isurf_pos, const char * iarea_pos, int iinside, REAL iweight, functional * iff) : surf_pos(isurf_pos), area_pos(iarea_pos), inside(iinside), weight(iweight), ff(iff) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_area_surf_add2(surf_pos, area, inside, weight, ff));
		}

	}
	const char * surf_pos;
	const char * area_pos;
	int inside;
	REAL weight;
	functional * ff;
};

bool area_surf_add(const char * surf_pos, REAL weight, const char * area_pos, int inside) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_surf_add(surf_pos, area_pos, inside, weight, srf));
	return true;
};

struct match_area_surf_leq2
{
	match_area_surf_leq2(const char * isurf_pos, d_area * iarea, REAL imult, int iinside) : surf_pos(isurf_pos), area(iarea), mult(imult), inside(iinside) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf_leq(\"%s\",\"%s\",%g,%d)",
				surf->getName(),area->getName(),mult, inside);
			f_area_surf_ineq * f = new f_area_surf_ineq(surf, area, true, mult, (inside == 1) );
			functionals_push_back(f);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
	REAL mult;
};

struct match_area_surf_leq
{
	match_area_surf_leq(const char * isurf_pos, const char * iarea_pos, REAL imult, int iinside) : surf_pos(isurf_pos), area_pos(iarea_pos), mult(imult), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_area_surf_leq2(surf_pos, area, mult, inside));
		}
	}
	const char * surf_pos;
	const char * area_pos;
	REAL mult;
	int inside;
};

bool area_surf_leq(const char * surf_pos, const char * area_pos, REAL mult, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_surf_leq(surf_pos, area_pos, mult, inside));
	return true;
};

struct match_area_surf_geq2
{
	match_area_surf_geq2(const char * isurf_pos, d_area * iarea, REAL imult, int iinside) : surf_pos(isurf_pos), area(iarea), mult(imult), inside(iinside) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf_geq(\"%s\",\"%s\",%g,%d)",
				surf->getName(),area->getName(),mult, inside);
			f_area_surf_ineq * f = new f_area_surf_ineq(surf, area, false, mult, (inside == 1) );
			functionals_push_back(f);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
	REAL mult;
};

struct match_area_surf_geq
{
	match_area_surf_geq(const char * isurf_pos, const char * iarea_pos, REAL imult, int iinside) : surf_pos(isurf_pos), area_pos(iarea_pos), mult(imult), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_area_surf_geq2(surf_pos, area, mult, inside));
		}
	}
	const char * surf_pos;
	const char * area_pos;
	REAL mult;
	int inside;
};

bool area_surf_geq(const char * surf_pos, const char * area_pos, REAL mult, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_surf_geq(surf_pos, area_pos, mult, inside));
	return true;
};

struct match_area_mean
{
	match_area_mean(REAL imean, const char * ipos, REAL imult, int iinside) : mean(imean), pos(ipos), mult(imult), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_mean(%g,\"%s\",%g,%d)",
				mean,area->getName(),mult, inside);
			f_area_mean * f = new f_area_mean(mean, area, mult, (inside == 1) );
			functionals_push_back(f);
		}
	}
	REAL mean;
	const char * pos;
	REAL mult;
	int inside;
};

bool area_mean(REAL mean, const char * pos, REAL mult, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_mean(mean, pos, mult, inside));
	return true;
};

struct match_area_wmean2
{
	match_area_wmean2(REAL imean, d_area * iarea, const char * isurf_pos, REAL imult, int iinside) : mean(imean), area(iarea), surf_pos(isurf_pos), mult(imult), inside(iinside) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_wmean(%g,\"%s\",\"%s\",%g,%d)",
				mean, area->getName(), surf->getName(), mult, inside);
			f_area_wmean * f = new f_area_wmean(mean, surf, area, mult, (inside == 1) );
			functionals_push_back(f);
		}
	}
	REAL mean;
	d_area * area;
	const char * surf_pos;
	REAL mult;
	int inside;
};

struct match_area_wmean
{
	match_area_wmean(REAL imean, const char * iarea_pos, const char * isurf_pos, REAL imult, int iinside) : mean(imean), area_pos(iarea_pos), surf_pos(isurf_pos), mult(imult), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			std::for_each(surfit_surfs->begin(),surfit_surfs->end(), match_area_wmean2(mean, area, surf_pos, mult, inside));
		}
	}
	REAL mean;
	const char * area_pos;
	const char * surf_pos;
	REAL mult;
	int inside;
};

bool area_wmean(REAL mean, const char * area_pos, const char * surf_pos, REAL mult, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_wmean(mean, area_pos, surf_pos, mult, inside));
	return true;
};

struct match_area_completer
{
	match_area_completer(const char * iarea_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw, int iinside) : area_pos(iarea_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_completer(\"%s\",%g,%g,%g,%g,%d)",
				area->getName(), D1, D2, alpha, w, inside);
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_area(area, (inside == 1));
			functionals_push_back(f);
		}
	}
	const char * area_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
	int inside;
};

bool area_completer(const char * area_pos, REAL D1, REAL D2, REAL alpha, REAL w, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_completer(area_pos, D1, D2, alpha, w, inside));
	return true;
};

struct match_area_completer_add
{
	match_area_completer_add(const char * iarea_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw, int iinside, REAL iweight, functional * iff) : area_pos(iarea_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw), inside(iinside), weight(iweight), ff(iff) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_completer_add(%g,\"%s\",%g,%g,%g,%g,%d)",
				weight, area->getName(), D1, D2, alpha, w, inside);
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_area(area, (inside == 1));
			ff->add_functional(f, weight);
		}
	}
	const char * area_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
	int inside;
	REAL weight;
	functional * ff;
};

bool area_completer_add(REAL weight, const char * area_pos, REAL D1, REAL D2, REAL alpha, REAL w, int inside) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_completer_add(area_pos, D1, D2, alpha, w, inside, weight, srf));
	return true;
};

struct match_area_hist2
{
	match_area_hist2(d_area * iarea, const char * ihist_pos, REAL imult, int iinside) : area(iarea), hist_pos(ihist_pos), mult(imult), inside(iinside) {};
	void operator()(d_hist * hist) 
	{
		if ( StringMatch(hist_pos, hist->getName()) )
		{
			writelog(LOG_MESSAGE,"creating functional area_hist(\"%s\",\"%s\",%g,%d)",
				area->getName(), hist->getName(), mult, inside);
			f_area_hist * f = new f_area_hist(area, hist, mult, (inside==1));
			functionals_push_back(f);					
		}
	}
	d_area * area;
	const char * hist_pos;
	REAL mult; 
	int inside;
};

struct match_area_hist
{
	match_area_hist(const char * iarea_pos, const char * ihist_pos, REAL imult, int iinside) : area_pos(iarea_pos), hist_pos(ihist_pos), mult(imult), inside(iinside) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			std::for_each(surfit_hists->begin(), surfit_hists->end(), match_area_hist2(area, hist_pos, mult, inside));
		}
	}
	const char * area_pos;
	const char * hist_pos;
	REAL mult; 
	int inside;
};

bool area_hist(const char * area_pos, const char * hist_pos, REAL mult, int inside) 
{
	std::for_each(surfit_areas->begin(), surfit_areas->end(), match_area_hist(area_pos, hist_pos, mult, inside));
	return true;
};

struct match_contour
{
	match_contour(const char * ipos) : pos(ipos) {};
	void operator()(d_cntr * contour) 
	{
		if ( StringMatch(pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour(\"%s\")", contour->getName());
			f_cntr * f = new f_cntr(contour);
			functionals_push_back(f);
		}
	}
	const char * pos;
};

bool contour(const char * pos) {
	std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), match_contour(pos));
	return true;
};

struct match_contour_add
{
	match_contour_add(const char * ipos, functional * isrf, REAL iweight) : 
			   pos(ipos), srf(isrf), weight(iweight) {};
	void operator()(d_cntr * contour)
	{
		if ( StringMatch(pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour_add(\"%s\")",contour->getName());
			f_cntr * srf2 = new f_cntr(contour);
			srf->add_functional(srf2, weight);
		}
	}
	const char * pos;
	functional * srf;
	REAL weight;
};

bool contour_add(REAL weight, const char * pos) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), match_contour_add(pos, srf, weight));
	return true;
};

struct match_contour_leq
{
	match_contour_leq(const char * icntr_pos, REAL imult) : cntr_pos(icntr_pos), mult(imult) {};
	void operator()(d_cntr * contour)
	{
		if ( StringMatch(cntr_pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour_leq(\"%s\",%d)",
				contour->getName(), mult);
			f_cntr_ineq * f = new f_cntr_ineq(contour, true, mult);
			functionals_push_back(f);
		}
	}
	const char * cntr_pos;
	REAL mult;
};

bool contour_leq(const char * cntr_pos, REAL mult) 
{
	std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), match_contour_leq(cntr_pos, mult));
	return true;
};

struct match_contour_geq
{
	match_contour_geq(const char * icntr_pos, REAL imult) : cntr_pos(icntr_pos), mult(imult) {};
	void operator()(d_cntr * contour)
	{
		if ( StringMatch(cntr_pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour_geq(\"%s\",%d)",
				contour->getName(), mult);
			f_cntr_ineq * f = new f_cntr_ineq(contour, false, mult);
			functionals_push_back(f);
		}
	}
	const char * cntr_pos;
	REAL mult;
};

bool contour_geq(const char * cntr_pos, REAL mult) 
{
	std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), match_contour_geq(cntr_pos, mult));
	return true;};

}; // namespace surfit;


