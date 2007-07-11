
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
#include "f_cntr_smooth.h"
#include "f_cntr_ineq.h"
#include "f_curv.h"
#include "f_curv_ineq.h"
#include "f_curv_surf.h"
#include "f_curv_surf_ineq.h"
#include "f_completer.h"
#include "f_fault.h"
#include "variables_tcl.h"
#include "interp.h"
#include "boolvec.h"

#include <algorithm>

namespace surfit {

struct match_fault
{
	match_fault(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_curv * fault) 
	{
		if ( StringMatch(pos, fault->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule fault(\"%s\")",fault->getName());
			if (res == NULL)
				res = create_boolvec();
			
			f_fault * f = new f_fault(fault);
			functionals_push_back(f);
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * fault(const char * pos) 
{
	match_fault qq(pos);
	qq = std::for_each( surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curve
{
	match_curve(const char * ipos, REAL ival) : pos(ipos), val(ival), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve(%g,\"%s\")",
				 val, crv->getName());
			f_curv * f = new f_curv(val, crv);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL val;
	boolvec * res;
};

boolvec * curve(REAL value, const char * pos) 
{
	match_curve qq(pos, value);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curve_add
{
	match_curve_add(const char * ipos, REAL ival, REAL iweight) : pos(ipos), val(ival), weight(iweight), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve(%g,%g,\"%s\")", 
				 val, weight, crv->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * srf = get_modifiable_functional();
			if (srf == NULL) {
				res->push_back(false);
				return;
			}
			f_curv * f = new f_curv(val, crv);
			srf->add_functional(f, weight);
			res->push_back(true);
		}
	}
	const char * pos;
	REAL val;
	REAL weight;
	boolvec * res;
};

boolvec * curve_add(REAL value, REAL weight, const char * pos) 
{
	match_curve_add qq(pos, value, weight);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curve_leq
{
	match_curve_leq(const char * ipos, REAL ival, REAL ipenalty_factor) : pos(ipos), val(ival), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_leq(%g,\"%s\",%g)", 
				 val, crv->getName(), get_mult(penalty_factor));
			f_curv_ineq * f = new f_curv_ineq(val, crv, true, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL val;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * curve_leq(REAL value, const char * curve_pos, REAL penalty_factor) 
{
	match_curve_leq qq(curve_pos, value, penalty_factor);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curve_geq
{
	match_curve_geq(const char * ipos, REAL ival, REAL ipenalty_factor) : pos(ipos), val(ival), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_geq(%g,\"%s\",%g)", 
				 val, crv->getName(), get_mult(penalty_factor));
			f_curv_ineq * f = new f_curv_ineq(val, crv, false, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL val;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * curve_geq(REAL value, const char * curve_pos, REAL penalty_factor) 
{
	match_curve_geq qq(curve_pos, value, penalty_factor);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curve_surf2
{
	match_curve_surf2(const char * isurf_pos, d_curv * icrv) : surf_pos(isurf_pos), crv(icrv), res(NULL) {};
	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf(\"%s\",\"%s\")", 
				 srf->getName(),crv->getName());
			f_curv_surf * f = new f_curv_surf(srf, crv);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}

	const char * surf_pos;
	d_curv * crv;
	boolvec * res;
};

struct match_curve_surf
{
	match_curve_surf(const char * isurf_pos, const char * icurv_pos) : surf_pos(isurf_pos), curv_pos(icurv_pos), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			match_curve_surf2 qq(surf_pos, crv);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * curv_pos;
	boolvec * res;
};

boolvec * curve_surf(const char * surf_pos, const char * curv_pos) 
{
	match_curve_surf qq(surf_pos, curv_pos);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curve_surf_add2
{
	match_curve_surf_add2(const char * isurf_pos, d_curv * icrv, REAL iweight) : surf_pos(isurf_pos), crv(icrv), weight(iweight), res(NULL) {};
	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf_add(\"%s\",%g,\"%s\")", 
				 srf->getName(),weight,crv->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * ff = get_modifiable_functional();
			if (ff == NULL) {
				res->push_back(false);
				return;
			}
			f_curv_surf * f = new f_curv_surf(srf, crv);
			ff->add_functional(f, weight);
			res->push_back(true);
		}
	}

	const char * surf_pos;
	d_curv * crv;
	REAL weight;
	boolvec * res;
};

struct match_curve_surf_add
{
	match_curve_surf_add(const char * isurf_pos, const char * icurv_pos, REAL iweight) : surf_pos(isurf_pos), curv_pos(icurv_pos), weight(iweight), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			match_curve_surf_add2 qq(surf_pos, crv, weight);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * curv_pos;
	REAL weight;
	boolvec * res;
};

boolvec * curve_surf_add(const char * surf_pos, REAL weight, const char * curv_pos) 
{
	match_curve_surf_add qq(surf_pos, curv_pos, weight);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curve_surf_leq2
{
	match_curve_surf_leq2(const char * isurf_pos, d_curv * icrv, REAL ipenalty_factor) : surf_pos(isurf_pos), crv(icrv), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf_leq(\"%s\",\"%s\",%g)", 
				 srf->getName(),crv->getName(), get_mult(penalty_factor));
			f_curv_surf_ineq * f = new f_curv_surf_ineq(srf, crv, true, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}

	const char * surf_pos;
	d_curv * crv;
	REAL penalty_factor;
	boolvec * res;
};

struct match_curve_surf_leq
{
	match_curve_surf_leq(const char * isurf_pos, const char * icurv_pos, REAL ipenalty_factor) : surf_pos(isurf_pos), curv_pos(icurv_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			match_curve_surf_leq2 qq(surf_pos, crv, penalty_factor);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * curv_pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * curve_surf_leq(const char * surf_pos, const char * curv_pos, REAL penalty_factor) 
{
	match_curve_surf_leq qq(surf_pos, curv_pos, penalty_factor);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);	
	return qq.res;
};

struct match_curve_surf_geq2
{
	match_curve_surf_geq2(const char * isurf_pos, d_curv * icrv, REAL ipenalty_factor) : surf_pos(isurf_pos), crv(icrv), penalty_factor(ipenalty_factor), res(NULL) {};

	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule curve_surf_geq(\"%s\",\"%s\",%g)", 
				 srf->getName(),crv->getName(),get_mult(penalty_factor));
			f_curv_surf_ineq * f = new f_curv_surf_ineq(srf, crv, false, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}

	const char * surf_pos;
	d_curv * crv;
	REAL penalty_factor;
	boolvec * res;
};

struct match_curve_surf_geq
{
	match_curve_surf_geq(const char * isurf_pos, const char * icurv_pos, REAL ipenalty_factor) : surf_pos(isurf_pos), curv_pos(icurv_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_curv * crv) 
	{
		if ( StringMatch(curv_pos, crv->getName()) )
		{
			match_curve_surf_geq2 qq(surf_pos, crv, penalty_factor);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * curv_pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * curve_surf_geq(const char * surf_pos, const char * curv_pos, REAL penalty_factor) 
{
	match_curve_surf_geq qq(surf_pos, curv_pos, penalty_factor);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);	
	return qq.res;
};

struct match_area
{
	match_area(const char * ipos, REAL ivalue, int iinside) : pos(ipos), value(ivalue), inside(iinside), res(NULL) {};
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
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL value;
	int inside;
	boolvec * res;
};

boolvec * area(const char * Value, const char * pos, int inside) 
{
	REAL value = undef_value;
	if (strcmp(Value,"undef") != 0) {
		value = atof(Value);
	}
	match_area qq(pos, value, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_add
{
	match_area_add(const char * ipos, REAL ivalue, REAL iweight, int iinside) : pos(ipos), value(ivalue), weight(iweight), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_add(%g,%g,\"%s\")", 
				 value,weight,area->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * ff = get_modifiable_functional();
			if (ff == NULL) {
				res->push_back(false);
				return;
			}
			f_area * f = new f_area(value, area, (inside == 1));
			ff->add_functional(f, weight);
			res->push_back(true);
		}
	}
	const char * pos;
	REAL value;
	REAL weight;
	int inside;
	boolvec * res;
};

boolvec * area_add(REAL value, REAL weight, const char * pos, int inside) 
{
	match_area_add qq(pos, value, weight, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_leq
{
	match_area_leq(const char * ipos, REAL ivalue, REAL imult, int iinside) : pos(ipos), value(ivalue), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_leq(%g,\"%s\",%g,%d)", 
				 value, area->getName(), mult, inside);
			f_area_ineq * f = new f_area_ineq(value, area, true, mult, (inside == 1));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL value;
	REAL mult;
	int inside;
	boolvec * res;
};

boolvec * area_leq(REAL value, const char * area_pos, REAL mult, int inside) 
{
	match_area_leq qq(area_pos, value, mult, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_geq
{
	match_area_geq(const char * ipos, REAL ivalue, REAL imult, int iinside) : pos(ipos), value(ivalue), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_geq(%g,\"%s\",%g,%d)", 
				 value, area->getName(), mult, inside);
			f_area_ineq * f = new f_area_ineq(value, area, false, (inside == 1));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL value;
	REAL mult;
	int inside;
	boolvec * res;
};

boolvec * area_geq(REAL value, const char * area_pos, REAL mult, int inside) 
{
	match_area_geq qq(area_pos, value, mult, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_surf2
{
	match_area_surf2(const char * isurf_pos, d_area * iarea, int iinside) : surf_pos(isurf_pos), area(iarea), inside(iinside), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf(\"%s\",\"%s\")",
				surf->getName(),area->getName());
			f_area_surf * f = new f_area_surf(surf, area, (inside==1));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
	boolvec * res;
};

struct match_area_surf
{
	match_area_surf(const char * isurf_pos, const char * iarea_pos, int iinside) : surf_pos(isurf_pos), area_pos(iarea_pos), inside(iinside), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			match_area_surf2 qq(surf_pos, area, inside);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}

	}
	const char * surf_pos;
	const char * area_pos;
	int inside;
	boolvec * res;
};

boolvec * area_surf(const char * surf_pos, const char * area_pos, int inside) 
{
	match_area_surf qq(surf_pos, area_pos, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_surf_add2
{
	match_area_surf_add2(const char * isurf_pos, d_area * iarea, int iinside, REAL iweight) : surf_pos(isurf_pos), area(iarea), inside(iinside), weight(iweight), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf_add(\"%s\",%g,\"%s\")",
				surf->getName(),weight,area->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * ff = get_modifiable_functional();
			if (ff == NULL) {
				res->push_back(false);
				return;
			}
			f_area_surf * f = new f_area_surf(surf, area, (inside==1));
			ff->add_functional(f, weight);
			res->push_back(true);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
	REAL weight;
	boolvec * res;
};

struct match_area_surf_add
{
	match_area_surf_add(const char * isurf_pos, const char * iarea_pos, int iinside, REAL iweight) : surf_pos(isurf_pos), area_pos(iarea_pos), inside(iinside), weight(iweight), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			match_area_surf_add2 qq(surf_pos, area, inside, weight);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}

	}
	const char * surf_pos;
	const char * area_pos;
	int inside;
	REAL weight;
	boolvec * res;
};

boolvec * area_surf_add(const char * surf_pos, REAL weight, const char * area_pos, int inside) 
{
	match_area_surf_add qq(surf_pos, area_pos, inside, weight);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_surf_leq2
{
	match_area_surf_leq2(const char * isurf_pos, d_area * iarea, REAL imult, int iinside) : surf_pos(isurf_pos), area(iarea), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf_leq(\"%s\",\"%s\",%g,%d)",
				surf->getName(),area->getName(),mult, inside);
			f_area_surf_ineq * f = new f_area_surf_ineq(surf, area, true, mult, (inside == 1) );
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
	REAL mult;
	boolvec * res;
};

struct match_area_surf_leq
{
	match_area_surf_leq(const char * isurf_pos, const char * iarea_pos, REAL imult, int iinside) : surf_pos(isurf_pos), area_pos(iarea_pos), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			match_area_surf_leq2 qq(surf_pos, area, mult, inside);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * area_pos;
	REAL mult;
	int inside;
	boolvec * res;
};

boolvec * area_surf_leq(const char * surf_pos, const char * area_pos, REAL mult, int inside) 
{
	match_area_surf_leq qq(surf_pos, area_pos, mult, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_surf_geq2
{
	match_area_surf_geq2(const char * isurf_pos, d_area * iarea, REAL imult, int iinside) : surf_pos(isurf_pos), area(iarea), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_surf_geq(\"%s\",\"%s\",%g,%d)",
				surf->getName(),area->getName(),mult, inside);
			f_area_surf_ineq * f = new f_area_surf_ineq(surf, area, false, mult, (inside == 1) );
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * surf_pos;
	d_area * area;
	int inside;
	REAL mult;
	boolvec * res;
};

struct match_area_surf_geq
{
	match_area_surf_geq(const char * isurf_pos, const char * iarea_pos, REAL imult, int iinside) : surf_pos(isurf_pos), area_pos(iarea_pos), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			match_area_surf_geq2 qq(surf_pos, area, mult, inside);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * area_pos;
	REAL mult;
	int inside;
	boolvec * res;
};

boolvec * area_surf_geq(const char * surf_pos, const char * area_pos, REAL mult, int inside) 
{
	match_area_surf_geq qq(surf_pos, area_pos, mult, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_mean
{
	match_area_mean(REAL imean, const char * ipos, REAL ipenalty_factor, int iinside) : mean(imean), pos(ipos), penalty_factor(ipenalty_factor), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_mean(%g,\"%s\",%g,%d)",
				mean,area->getName(), get_mult(penalty_factor), inside);
			f_area_mean * f = new f_area_mean(mean, area, get_mult(penalty_factor), (inside == 1) );
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	REAL mean;
	const char * pos;
	REAL penalty_factor;
	int inside;
	boolvec * res;
};

boolvec * area_mean(REAL mean, const char * pos, REAL penalty_factor, int inside) 
{
	match_area_mean qq(mean, pos, penalty_factor, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_wmean2
{
	match_area_wmean2(REAL imean, d_area * iarea, const char * isurf_pos, REAL imult, int iinside) : mean(imean), area(iarea), surf_pos(isurf_pos), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_wmean(%g,\"%s\",\"%s\",%g,%d)",
				mean, area->getName(), surf->getName(), mult, inside);
			f_area_wmean * f = new f_area_wmean(mean, surf, area, mult, (inside == 1) );
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	REAL mean;
	d_area * area;
	const char * surf_pos;
	REAL mult;
	int inside;
	boolvec * res;
};

struct match_area_wmean
{
	match_area_wmean(REAL imean, const char * iarea_pos, const char * isurf_pos, REAL imult, int iinside) : mean(imean), area_pos(iarea_pos), surf_pos(isurf_pos), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			match_area_wmean2 qq(mean, area, surf_pos, mult, inside);
			qq = std::for_each(surfit_surfs->begin(),surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	REAL mean;
	const char * area_pos;
	const char * surf_pos;
	REAL mult;
	int inside;
	boolvec * res;
};

boolvec * area_wmean(REAL mean, const char * area_pos, const char * surf_pos, REAL mult, int inside) 
{
	match_area_wmean qq(mean, area_pos, surf_pos, mult, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_completer
{
	match_area_completer(const char * iarea_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw, int iinside) : area_pos(iarea_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_completer(\"%s\",%g,%g,%g,%g,%d)",
				area->getName(), D1, D2, alpha, w, inside);
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_area(area, (inside == 1));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * area_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
	int inside;
	boolvec * res;
};

boolvec * area_completer(const char * area_pos, REAL D1, REAL D2, REAL alpha, REAL w, int inside) 
{
	match_area_completer qq(area_pos, D1, D2, alpha, w, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_completer_add
{
	match_area_completer_add(const char * iarea_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw, int iinside, REAL iweight) : area_pos(iarea_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw), inside(iinside), weight(iweight), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule area_completer_add(%g,\"%s\",%g,%g,%g,%g,%d)",
				weight, area->getName(), D1, D2, alpha, w, inside);
			if (res == NULL)
				res = create_boolvec();
			functional * ff = get_modifiable_functional();
			if (ff == NULL) {
				res->push_back(false);
				return;
			}
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_area(area, (inside == 1));
			ff->add_functional(f, weight);
			res->push_back(true);
		}
	}
	const char * area_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
	int inside;
	REAL weight;
	boolvec * res;
};

boolvec * area_completer_add(REAL weight, const char * area_pos, REAL D1, REAL D2, REAL alpha, REAL w, int inside) 
{
	match_area_completer_add qq(area_pos, D1, D2, alpha, w, inside, weight);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_hist2
{
	match_area_hist2(d_area * iarea, const char * ihist_pos, REAL imult, int iinside) : area(iarea), hist_pos(ihist_pos), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_hist * hist) 
	{
		if ( StringMatch(hist_pos, hist->getName()) )
		{
			writelog(LOG_MESSAGE,"creating functional area_hist(\"%s\",\"%s\",%g,%d)",
				area->getName(), hist->getName(), mult, inside);
			f_area_hist * f = new f_area_hist(area, hist, mult, (inside==1));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	d_area * area;
	const char * hist_pos;
	REAL mult; 
	int inside;
	boolvec * res;
};

struct match_area_hist
{
	match_area_hist(const char * iarea_pos, const char * ihist_pos, REAL imult, int iinside) : area_pos(iarea_pos), hist_pos(ihist_pos), mult(imult), inside(iinside), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			match_area_hist2 qq(area, hist_pos, mult, inside);
			qq = std::for_each(surfit_hists->begin(), surfit_hists->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * area_pos;
	const char * hist_pos;
	REAL mult; 
	int inside;
	boolvec * res;
};

boolvec * area_hist(const char * area_pos, const char * hist_pos, REAL mult, int inside) 
{
	match_area_hist qq(area_pos, hist_pos, mult, inside);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_contour
{
	match_contour(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_cntr * contour) 
	{
		if ( StringMatch(pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour(\"%s\")", contour->getName());
			f_cntr * f = new f_cntr(contour);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * contour(const char * pos) 
{
	match_contour qq(pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_contour_add
{
	match_contour_add(const char * ipos, REAL iweight) : 
			   pos(ipos), weight(iweight), res(NULL) {};
	void operator()(d_cntr * contour)
	{
		if ( StringMatch(pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour_add(\"%s\")",contour->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * srf = get_modifiable_functional();
			if (srf == NULL) {
				res->push_back(false);
				return;
			}
			f_cntr * srf2 = new f_cntr(contour);
			srf->add_functional(srf2, weight);
			res->push_back(true);
		}
	}
	const char * pos;
	REAL weight;
	boolvec * res;
};

boolvec * contour_add(REAL weight, const char * pos) 
{
	match_contour_add qq(pos, weight);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_contours
{
	match_contours(const char * ipos, REAL imult) : pos(ipos), res(NULL), mult(imult) {};
	void operator()(d_cntr * contour) 
	{
		if ( StringMatch(pos, contour->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"creating gridding rule contours(\"%s\")", contour->getName());
			if (functionals->size() > 0)
			{
				f_cntr_smooth * f = dynamic_cast<f_cntr_smooth*>( *(functionals->end()-1) );
				if (f != NULL)
				{
					f->add_contour(contour);
					res->push_back(true);
					return;
				}
			}
			f_cntr_smooth * f = new f_cntr_smooth(mult);
			f->add_contour(contour);
			functionals_push_back(f);
			res->push_back(true);
		}
	}
	REAL mult;
	const char * pos;
	boolvec * res;
};

boolvec * contours(const char * pos, REAL mult) 
{
	match_contours qq(pos, mult);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_contours_add
{
	match_contours_add(REAL iweight, const char * ipos) : weight(iweight), pos(ipos), res(NULL) {};
	void operator()(d_cntr * contour) 
	{
		if ( StringMatch(pos, contour->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			functional * srf = get_modifiable_functional();
			if (srf == NULL) {
				res->push_back(false);
				return;
			}
			functional * ff = srf->get_last_added();
			if (ff != NULL) {
				f_cntr_smooth * f = dynamic_cast<f_cntr_smooth*>(ff);
				if (f != NULL) {
					f->add_contour(contour);
					res->push_back(true);
					return;
				}
			}
			f_cntr_smooth * f = new f_cntr_smooth();
			f->add_contour(contour);
			srf->add_functional(f, weight);
			res->push_back(true);
		}
	}
	REAL weight;
	const char * pos;
	boolvec * res;
};

boolvec * contours_add(REAL weight, const char * pos)
{
	match_contours_add qq(weight, pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_contour_leq
{
	match_contour_leq(const char * icntr_pos, REAL imult) : cntr_pos(icntr_pos), mult(imult), res(NULL) {};
	void operator()(d_cntr * contour)
	{
		if ( StringMatch(cntr_pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour_leq(\"%s\",%g)",
				contour->getName(), mult);
			f_cntr_ineq * f = new f_cntr_ineq(contour, true, mult);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * cntr_pos;
	REAL mult;
	boolvec * res;
};

boolvec * contour_leq(const char * cntr_pos, REAL mult) 
{
	match_contour_leq qq(cntr_pos, mult);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_contour_geq
{
	match_contour_geq(const char * icntr_pos, REAL imult) : cntr_pos(icntr_pos), mult(imult), res(NULL) {};
	void operator()(d_cntr * contour)
	{
		if ( StringMatch(cntr_pos, contour->getName()) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule contour_geq(\"%s\",%g)",
				contour->getName(), mult);
			f_cntr_ineq * f = new f_cntr_ineq(contour, false, mult);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * cntr_pos;
	REAL mult;
	boolvec * res;
};

boolvec * contour_geq(const char * cntr_pos, REAL mult) 
{
	match_contour_geq qq(cntr_pos, mult);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

}; // namespace surfit;


