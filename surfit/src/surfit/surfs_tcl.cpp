
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
#include "surfs_tcl.h"
#include "surf.h"
#include "mask.h"
#include "f_surf.h"
#include "f_surf_ineq.h"
#include "f_trend.h"
#include "f_mask.h"
#include "f_mask_ineq.h"
#include "f_mask_surf.h"
#include "f_mask_surf_ineq.h"
#include "f_mask_mean.h"
#include "f_mask_wmean.h"
#include "f_completer.h"
#include "variables.h"
#include "variables_tcl.h"
#include "interp.h"
#include "boolvec.h"

#include <algorithm>

namespace surfit {

struct match_surface
{
	match_surface(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule surface(\"%s\")",surf->getName());
			f_surf * f = new f_surf(surf);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	const char * pos;
	boolvec * res;
};

boolvec * surface(const char * pos) 
{
	match_surface qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surface_add
{
	match_surface_add(REAL iweight, const char * ipos) : weight(iweight), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"creating gridding rule surface_add(%g,\"%s\")",weight, surf->getName());
			functional * f = get_modifiable_functional();
			if (f == NULL) {
				res->push_back(false);
				return;
			}
			f_surf * srf2 = new f_surf(surf);
			f->add_functional(srf2, weight);
			res->push_back(true);
		}
	};
	REAL weight;
	const char * pos;
	boolvec * res;
};

boolvec * surface_add(REAL weight, const char * pos) 
{
	match_surface_add qq(weight, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surface_leq
{
	match_surface_leq(const char * ipos, REAL ipenalty_factor) : pos(ipos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule surface_leq(\"%s\",%g)",
				surf->getName(), get_mult(penalty_factor));
			f_surf_ineq * f = new f_surf_ineq(surf, true, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * surface_leq(const char * pos, REAL penalty_factor) 
{
	match_surface_leq qq(pos, penalty_factor);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surface_geq
{
	match_surface_geq(const char * ipos, REAL ipenalty_factor) : pos(ipos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule surface_geq(\"%s\",%g)",
				surf->getName(), get_mult(penalty_factor));
			f_surf_ineq * f = new f_surf_ineq(surf, false, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	const char * pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * surface_geq(const char * pos, REAL penalty_factor) 
{
	match_surface_geq qq(pos, penalty_factor);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_trend
{
	match_trend(REAL iD1, REAL iD2, const char * ipos) : D1(iD1), D2(iD2), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule trend(%g,%g,\"%s\")",
				D1, D2, surf->getName());
			f_trend * f = new f_trend(D1, D2, surf);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	REAL D1;
	REAL D2;
	const char * pos;
	boolvec * res;
};

boolvec * trend(REAL D1, REAL D2, const char * pos) 
{
	match_trend qq(D1, D2, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_trend_add
{
	match_trend_add(REAL iweight, REAL iD1, REAL iD2, const char * ipos) : weight(iweight), D1(iD1), D2(iD2), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule trend_add(%g,%g,%g,\"%s\")",
				weight, D1, D2, surf->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * f = get_modifiable_functional();
			if (f == NULL){
				res->push_back(false);
				return;
			}
			f_trend * srf2 = new f_trend(D1, D2, surf);
			f->add_functional(srf2, weight);
			res->push_back(true);
		}
	};
	REAL weight;
	REAL D1;
	REAL D2;
	const char * pos;
	boolvec * res;
};

boolvec * trend_add(REAL weight, REAL D1, REAL D2, const char * pos) 
{
	match_trend_add qq(weight, D1, D2, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_mask
{
	match_mask(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			if (value == undef_value)
				writelog(LOG_MESSAGE,"creating gridding rule mask(\"undef\",\"%s\")",mask->getName());
			else
				writelog(LOG_MESSAGE,"creating gridding rule mask(%g,\"%s\")",value,mask->getName());
			f_mask * f = new f_mask(mask, value);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec *  mask(const char * Value, const char * pos) 
{
	REAL value = undef_value;
	if (strcmp(Value,"undef") != 0) {
		value = atof(Value);
	}
	match_mask qq(value, pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_add
{
	match_mask_add(REAL iweight, REAL ivalue, const char * ipos) : weight(iweight), value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_add(%g, %g,\"%s\")",value,weight,mask->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * mf = get_modifiable_functional();
			if (mf == NULL) {
				res->push_back(false);
				return;
			}
			f_mask * f = new f_mask(mask, value);
			mf->add_functional(f, weight);
			res->push_back(true);
		}
	};
	REAL weight;
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec * mask_add(REAL value, REAL weight, const char * pos) 
{
	match_mask_add qq(weight, value, pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_leq
{
	match_mask_leq(REAL ivalue, const char * imask_pos, REAL ipenalty_factor) : value(ivalue), mask_pos(imask_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_leq(%g,\"%s\",%g)",
				value, mask->getName(), get_mult(penalty_factor));
			f_mask_ineq * f = new f_mask_ineq(value, mask, true, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	REAL value;
	const char * mask_pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * mask_leq(REAL value, const char * mask_pos, REAL penalty_factor) 
{
	match_mask_leq qq(value, mask_pos, penalty_factor);
	std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_geq
{
	match_mask_geq(REAL ivalue, const char * imask_pos, REAL ipenalty_factor) : value(ivalue), mask_pos(imask_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_geq(%g,\"%s\",%g)",
				value, mask->getName(), get_mult(penalty_factor));
			f_mask_ineq * f = new f_mask_ineq(value, mask, false, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	REAL value;
	const char * mask_pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * mask_geq(REAL value, const char * mask_pos, REAL penalty_factor) 
{
	match_mask_geq qq(value, mask_pos, penalty_factor);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_surf2
{
	match_mask_surf2(const char * isurf_pos, d_mask * imask) : surf_pos(isurf_pos), mask(imask), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf(\"%s\",\"%s\")",
				surf->getName(), mask->getName());
			f_mask_surf * f = new f_mask_surf(surf, mask);
			functionals_push_back(f);		
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	const char * surf_pos;
	d_mask * mask;
	boolvec * res;
};

struct match_mask_surf
{
	match_mask_surf(const char * isurf_pos, const char * imask_pos) : surf_pos(isurf_pos), mask_pos(imask_pos), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			match_mask_surf2 qq(surf_pos, mask);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	};
	const char * surf_pos;
	const char * mask_pos;
	boolvec * res;
};

boolvec * mask_surf(const char * surf_pos, const char * mask_pos) 
{
	match_mask_surf qq(surf_pos, mask_pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_surf_add2
{
	match_mask_surf_add2(REAL iweight, const char * isurf_pos, d_mask * imask) : weight(iweight), surf_pos(isurf_pos), mask(imask), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf_add(\"%s\",%g,\"%s\")",
				surf->getName(), weight, mask->getName());
			if (res == NULL)
				res = create_boolvec();
			functional * srf = get_modifiable_functional();
			if (srf == NULL) {
				res->push_back(false);
				return;
			}
			f_mask_surf * f = new f_mask_surf(surf, mask);
			srf->add_functional(f, weight);
			res->push_back(true);
		}
	};
	REAL weight;
	const char * surf_pos;
	d_mask * mask;
	boolvec * res;
};

struct match_mask_surf_add
{
	match_mask_surf_add(REAL iweight, const char * isurf_pos, const char * imask_pos) : weight(iweight), surf_pos(isurf_pos), mask_pos(imask_pos), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			if (res == NULL)
				res = create_boolvec();
			match_mask_surf_add2 qq(weight, surf_pos, mask);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			res->push_back(qq.res);
		}
	};
	const char * surf_pos;
	const char * mask_pos;
	REAL weight;
	boolvec * res;
};

boolvec * mask_surf_add(const char * surf_pos, REAL weight, const char * mask_pos) 
{
	match_mask_surf_add qq(weight, surf_pos, mask_pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_surf_leq2
{
	match_mask_surf_leq2(const char * isurf_pos, d_mask * imask, REAL ipenalty_factor)  : surf_pos(isurf_pos), mask(imask), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf_leq(\"%s\",\"%s\",%g)",
				surf->getName(), mask->getName(), get_mult(penalty_factor));
			f_mask_surf_ineq * f = new f_mask_surf_ineq(surf, mask, true, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	const char * surf_pos;
	d_mask * mask;
	REAL penalty_factor;
	boolvec * res;
};

struct match_mask_surf_leq
{
	match_mask_surf_leq(const char * isurf_pos, const char * imask_pos, REAL ipenalty_factor)  : surf_pos(isurf_pos), mask_pos(imask_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			match_mask_surf_leq2 qq(surf_pos, mask, penalty_factor);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	};
	const char * surf_pos;
	const char * mask_pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * mask_surf_leq(const char * surf_pos, const char * mask_pos, REAL penalty_factor) 
{
	match_mask_surf_leq qq(surf_pos, mask_pos, penalty_factor);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_surf_geq2
{
	match_mask_surf_geq2(const char * isurf_pos, d_mask * imask, REAL ipenalty_factor)  : surf_pos(isurf_pos), mask(imask), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf_geq(\"%s\",\"%s\",%g)",
				surf->getName(), mask->getName(), get_mult(penalty_factor));
			f_mask_surf_ineq * f = new f_mask_surf_ineq(surf, mask, false, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	const char * surf_pos;
	d_mask * mask;
	REAL penalty_factor;
	boolvec * res;
};

struct match_mask_surf_geq
{
	match_mask_surf_geq(const char * isurf_pos, const char * imask_pos, REAL ipenalty_factor)  : surf_pos(isurf_pos), mask_pos(imask_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			match_mask_surf_geq2 qq(surf_pos, mask, penalty_factor);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	};
	const char * surf_pos;
	const char * mask_pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * mask_surf_geq(const char * surf_pos, const char * mask_pos, REAL mult) 
{
	match_mask_surf_geq qq(surf_pos, mask_pos, mult);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_mean
{
	match_mask_mean(REAL imean, const char * ipos, REAL ipenalty_factor) : mean(imean), pos(ipos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_mean(%g,\"%s\",%g)",
				mean, pos, get_mult(penalty_factor));
			f_mask_mean * f = new f_mask_mean(mean, mask, get_mult(penalty_factor));
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	REAL mean;
	const char * pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * mask_mean(REAL mean, const char * pos, REAL penalty_factor) 
{
	match_mask_mean qq(mean, pos, penalty_factor);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_wmean2
{
	match_mask_wmean2(REAL imean, d_mask * imask, const char * isurf_pos, REAL ipenalty_factor) : mean(imean), mask(imask), surf_pos(isurf_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_wmean(%g,\"%s\",\"%s\",%g)",
				mean, mask->getName(), surf->getName(), get_mult(penalty_factor));
			f_mask_wmean * f = new f_mask_wmean(mean, surf, mask, get_mult(penalty_factor));
			functionals_push_back(f);	
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	REAL mean;
	d_mask * mask;
	const char * surf_pos;
	REAL penalty_factor;
	boolvec * res;
};

struct match_mask_wmean
{
	match_mask_wmean(REAL imean, const char * imask_pos, const char * isurf_pos, REAL ipenalty_factor) : mean(imean), mask_pos(imask_pos), surf_pos(isurf_pos), penalty_factor(ipenalty_factor), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			match_mask_wmean2 qq(mean, mask, surf_pos, penalty_factor);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	};
	REAL mean;
	const char * mask_pos;
	const char * surf_pos;
	REAL penalty_factor;
	boolvec * res;
};

boolvec * mask_wmean(REAL mean, const char * mask_pos, const char * surf_pos, REAL penalty_factor) 
{
	match_mask_wmean qq(mean, mask_pos, surf_pos, penalty_factor);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_completer
{
	match_mask_completer(const char * imask_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw) : mask_pos(imask_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_completer(\"%s\",%g,%g,%g,%g)",
				mask->getName(), D1, D2, alpha, w);
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_mask(mask);
			functionals_push_back(f);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	};
	const char * mask_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
	boolvec * res;
};

boolvec * mask_completer(const char * mask_pos, REAL D1, REAL D2, REAL alpha, REAL w) 
{
	match_mask_completer qq(mask_pos, D1, D2, alpha, w);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_completer_add
{
	match_mask_completer_add(REAL iweight, const char * imask_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw) : weight(iweight), mask_pos(imask_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw), res(NULL) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_completer_add(%g,\"%s\",%g,%g,%g,%g)",
				weight, mask->getName(), D1, D2, alpha, w);
			if (res == NULL)
				res = create_boolvec();
			functional * srf = get_modifiable_functional();
			if (srf == NULL) {
				res->push_back(false);
				return;
			}
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_mask(mask);
			srf->add_functional(f, weight);
			res->push_back(true);
		}
	};
	REAL weight;
	const char * mask_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
	boolvec * res;
};

boolvec * mask_completer_add(REAL weight, const char * mask_pos, REAL D1, REAL D2, REAL alpha, REAL w) 
{
	match_mask_completer_add qq(weight, mask_pos, D1, D2, alpha, w);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

}; // namespace surfit;

