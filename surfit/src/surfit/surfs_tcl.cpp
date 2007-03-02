
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

#include <algorithm>

namespace surfit {

struct match_surface
{
	match_surface(const char * ipos) : pos(ipos) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule surface(\"%s\")",surf->getName());
			f_surf * f = new f_surf(surf);
			functionals_push_back(f);
		}
	};
	const char * pos;
};

bool surface(const char * pos) 
{
	std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_surface(pos));
	return true;
};

struct match_surface_add
{
	match_surface_add(REAL iweight, const char * ipos, functional * iff) : weight(iweight), pos(ipos), ff(iff) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule surface_add(%g,\"%s\")",weight, surf->getName());
			f_surf * srf2 = new f_surf(surf);
			ff->add_functional(srf2, weight);
		}
	};
	REAL weight;
	const char * pos;
	functional * ff;
};

bool surface_add(REAL weight, const char * pos) 
{
	functional * f = get_modifiable_functional();
	if (f == NULL)
		return false;

	std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_surface_add(weight, pos, f));
	return true;
};

struct match_surface_leq
{
	match_surface_leq(const char * ipos, REAL imult) : pos(ipos), mult(imult) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule surface_leq(\"%s\",%g)",
				surf->getName(), mult);
			f_surf_ineq * f = new f_surf_ineq(surf, true, mult);
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL mult;
};

bool surface_leq(const char * pos, REAL mult) 
{
	std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_surface_leq(pos, mult));
	return true;
};

struct match_surface_geq
{
	match_surface_geq(const char * ipos, REAL imult) : pos(ipos), mult(imult) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule surface_geq(\"%s\",%g)",
				surf->getName(), mult);
			f_surf_ineq * f = new f_surf_ineq(surf, false, mult);
			functionals_push_back(f);
		}
	}
	const char * pos;
	REAL mult;
};

bool surface_geq(const char * pos, REAL mult) 
{
	std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_surface_geq(pos, mult));
	return true;
};

struct match_trend
{
	match_trend(REAL iD1, REAL iD2, const char * ipos) : D1(iD1), D2(iD2), pos(ipos) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule trend(%g,%g,\"%s\")",
				D1, D2, surf->getName());
			f_trend * f = new f_trend(D1, D2, surf);
			functionals_push_back(f);
		}
	};
	REAL D1;
	REAL D2;
	const char * pos;
};

bool trend(REAL D1, REAL D2, const char * pos) 
{
	std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_trend(D1, D2, pos));
	return true;
};

struct match_trend_add
{
	match_trend_add(REAL iweight, REAL iD1, REAL iD2, const char * ipos, functional * iff) : weight(iweight), D1(iD1), D2(iD2), pos(ipos), ff(iff) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule trend_add(%g,%g,%g,\"%s\")",
				weight, D1, D2, surf->getName());
			f_trend * srf2 = new f_trend(D1, D2, surf);
			ff->add_functional(srf2, weight);
		}
	};
	REAL weight;
	REAL D1;
	REAL D2;
	const char * pos;
	functional * ff;
};

bool trend_add(REAL weight, REAL D1, REAL D2, const char * pos) 
{
	functional * f = get_modifiable_functional();
	if (f == NULL)
		return false;

	std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_trend_add(weight, D1, D2, pos, f));
	return true;
};

struct match_mask
{
	match_mask(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos) {};
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
		}
	};
	REAL value;
	const char * pos;
};

bool mask(const char * Value, const char * pos) 
{
	REAL value = undef_value;
	if (strcmp(Value,"undef") != 0) {
		value = atof(Value);
	}

	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask(value, pos));
	return true;
};

struct match_mask_add
{
	match_mask_add(REAL iweight, REAL ivalue, const char * ipos, functional * iff) : weight(iweight), value(ivalue), pos(ipos), ff(iff) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_add(%g, %g,\"%s\")",value,weight,mask->getName());
			f_mask * f = new f_mask(mask, value);
			ff->add_functional(f, weight);
		}
	};
	REAL weight;
	REAL value;
	const char * pos;
	functional * ff;
};

bool mask_add(REAL value, REAL weight, const char * pos) 
{
	functional * mf = get_modifiable_functional();
	if (mf == NULL)
		return false;

	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_add(weight, value, pos, mf));
	return true;
};

struct match_mask_leq
{
	match_mask_leq(REAL ivalue, const char * imask_pos, REAL imult) : value(ivalue), mask_pos(imask_pos), mult(imult) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_leq(%g,\"%s\",%g)",
				value, mask->getName(), mult);
			f_mask_ineq * f = new f_mask_ineq(value, mask, true, mult);
			functionals_push_back(f);
		}
	};
	REAL value;
	const char * mask_pos;
	REAL mult;
};

bool mask_leq(REAL value, const char * mask_pos, REAL mult) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_leq(value, mask_pos, mult));
	return true;
};

struct match_mask_geq
{
	match_mask_geq(REAL ivalue, const char * imask_pos, REAL imult) : value(ivalue), mask_pos(imask_pos), mult(imult) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_geq(%g,\"%s\",%g)",
				value, mask->getName(), mult);
			f_mask_ineq * f = new f_mask_ineq(value, mask, false, mult);
			functionals_push_back(f);
		}
	};
	REAL value;
	const char * mask_pos;
	REAL mult;
};

bool mask_geq(REAL value, const char * mask_pos, REAL mult) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_geq(value, mask_pos, mult));
	return true;
};

struct match_mask_surf2
{
	match_mask_surf2(const char * isurf_pos, d_mask * imask) : surf_pos(isurf_pos), mask(imask) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf(\"%s\",\"%s\")",
				surf->getName(), mask->getName());
			f_mask_surf * f = new f_mask_surf(surf, mask);
			functionals_push_back(f);		
		}
	};
	const char * surf_pos;
	d_mask * mask;
};

struct match_mask_surf
{
	match_mask_surf(const char * isurf_pos, const char * imask_pos) : surf_pos(isurf_pos), mask_pos(imask_pos) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_mask_surf2(surf_pos, mask));
		}
	};
	const char * surf_pos;
	const char * mask_pos;
};

bool mask_surf(const char * surf_pos, const char * mask_pos) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_surf(surf_pos, mask_pos));
	return true;
};

struct match_mask_surf_add2
{
	match_mask_surf_add2(REAL iweight, const char * isurf_pos, d_mask * imask, functional * iff) : weight(iweight), surf_pos(isurf_pos), mask(imask), ff(iff) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf_add(\"%s\",%g,\"%s\")",
				surf->getName(), weight, mask->getName());
			f_mask_surf * f = new f_mask_surf(surf, mask);
			ff->add_functional(f, weight);
		}
	};
	REAL weight;
	const char * surf_pos;
	d_mask * mask;
	functional * ff;
};

struct match_mask_surf_add
{
	match_mask_surf_add(REAL iweight, const char * isurf_pos, const char * imask_pos, functional * iff) : weight(iweight), surf_pos(isurf_pos), mask_pos(imask_pos), ff(iff) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_mask_surf_add2(weight, surf_pos, mask, ff));
		}
	};
	const char * surf_pos;
	const char * mask_pos;
	REAL weight;
	functional * ff;
};

bool mask_surf_add(const char * surf_pos, REAL weight, const char * mask_pos) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_surf_add(weight, surf_pos, mask_pos, srf));
	return true;
};

struct match_mask_surf_leq2
{
	match_mask_surf_leq2(const char * isurf_pos, d_mask * imask, REAL imult)  : surf_pos(isurf_pos), mask(imask), mult(imult) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf_leq(\"%s\",\"%s\",%g)",
				surf->getName(), mask->getName(), mult);
			f_mask_surf_ineq * f = new f_mask_surf_ineq(surf, mask, true, mult);
			functionals_push_back(f);
		}
	};
	const char * surf_pos;
	d_mask * mask;
	REAL mult;
};

struct match_mask_surf_leq
{
	match_mask_surf_leq(const char * isurf_pos, const char * imask_pos, REAL imult)  : surf_pos(isurf_pos), mask_pos(imask_pos), mult(imult) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_mask_surf_leq2(surf_pos, mask, mult));
		}
	};
	const char * surf_pos;
	const char * mask_pos;
	REAL mult;
};

bool mask_surf_leq(const char * surf_pos, const char * mask_pos, REAL mult) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_surf_leq(surf_pos, mask_pos, mult));
	return true;
};

struct match_mask_surf_geq2
{
	match_mask_surf_geq2(const char * isurf_pos, d_mask * imask, REAL imult)  : surf_pos(isurf_pos), mask(imask), mult(imult) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_surf_geq(\"%s\",\"%s\",%g)",
				surf->getName(), mask->getName(), mult);
			f_mask_surf_ineq * f = new f_mask_surf_ineq(surf, mask, false, mult);
			functionals_push_back(f);
		}
	};
	const char * surf_pos;
	d_mask * mask;
	REAL mult;
};

struct match_mask_surf_geq
{
	match_mask_surf_geq(const char * isurf_pos, const char * imask_pos, REAL imult)  : surf_pos(isurf_pos), mask_pos(imask_pos), mult(imult) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_mask_surf_geq2(surf_pos, mask, mult));
		}
	};
	const char * surf_pos;
	const char * mask_pos;
	REAL mult;
};

bool mask_surf_geq(const char * surf_pos, const char * mask_pos, REAL mult) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_surf_geq(surf_pos, mask_pos, mult));
	return true;
};

struct match_mask_mean
{
	match_mask_mean(REAL imean, const char * ipos, REAL imult) : mean(imean), pos(ipos), mult(imult) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_mean(%g,\"%s\",%g)",
				mean, pos, mult);
			f_mask_mean * f = new f_mask_mean(mean, mask, mult);
			functionals_push_back(f);
		}
	};
	REAL mean;
	const char * pos;
	REAL mult;
};

bool mask_mean(REAL mean, const char * pos, REAL mult) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_mean(mean, pos, mult));
	return true;
};

struct match_mask_wmean2
{
	match_mask_wmean2(REAL imean, d_mask * imask, const char * isurf_pos, REAL imult) : mean(imean), mask(imask), surf_pos(isurf_pos), mult(imult) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_wmean(%g,\"%s\",\"%s\",%g)",
				mean, mask->getName(), surf->getName(), mult);
			f_mask_wmean * f = new f_mask_wmean(mean, surf, mask, mult);
			functionals_push_back(f);	
		}
	};
	REAL mean;
	d_mask * mask;
	const char * surf_pos;
	REAL mult;
};

struct match_mask_wmean
{
	match_mask_wmean(REAL imean, const char * imask_pos, const char * isurf_pos, REAL imult) : mean(imean), mask_pos(imask_pos), surf_pos(isurf_pos), mult(imult) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_mask_wmean2(mean, mask, surf_pos, mult));
		}
	};
	REAL mean;
	const char * mask_pos;
	const char * surf_pos;
	REAL mult;
};

bool mask_wmean(REAL mean, const char * mask_pos, const char * surf_pos, REAL mult) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_wmean(mean, mask_pos, surf_pos, mult));
	return true;
};

struct match_mask_completer
{
	match_mask_completer(const char * imask_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw) : mask_pos(imask_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_completer(\"%s\",%g,%g,%g,%g)",
				mask->getName(), D1, D2, alpha, w);
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_mask(mask);
			functionals_push_back(f);
		}
	};
	const char * mask_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
};

bool mask_completer(const char * mask_pos, REAL D1, REAL D2, REAL alpha, REAL w) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_completer(mask_pos, D1, D2, alpha, w));
	return true;
};

struct match_mask_completer_add
{
	match_mask_completer_add(REAL iweight, const char * imask_pos, REAL iD1, REAL iD2, REAL ialpha, REAL iw, functional * iff) : weight(iweight), mask_pos(imask_pos), D1(iD1), D2(iD2), alpha(ialpha), w(iw), ff(iff) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( mask_pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating gridding rule mask_completer_add(%g,\"%s\",%g,%g,%g,%g)",
				weight, mask->getName(), D1, D2, alpha, w);
			f_completer * f = new f_completer(D1, D2, alpha, w);
			f->set_mask(mask);
			ff->add_functional(f, weight);
		}
	};
	REAL weight;
	const char * mask_pos;
	REAL D1;
	REAL D2;
	REAL alpha;
	REAL w;
	functional * ff;
};

bool mask_completer_add(REAL weight, const char * mask_pos, REAL D1, REAL D2, REAL alpha, REAL w) 
{
	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_completer_add(weight, mask_pos, D1, D2, alpha, w, srf));
	return true;
};

}; // namespace surfit;

