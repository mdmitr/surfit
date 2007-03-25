
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

#include "real.h"
#include "datafile.h"
#include "fileio.h"
#include "interp.h"
#include "stepFunc.h"

#include "surf.h"
#include "surf_internal.h"
#include "surf_tcl.h"
#include "variables_internal.h"
#include "points.h"
#include "pnts_internal.h"
#include "pnts_tcl.h"
#include "mask.h"
#include "mask_tcl.h"
#include "grid.h"
#include "grid_internal.h"
#include "bitvec.h"
#include "vec.h"
#include "grid_line.h"
#include "free_elements.h"
#include "curv.h"
#include "area.h"
#include "cntr.h"
#include "cntr_trace.h"

#include "grid_user.h"
#include "findfile.h"

#include <float.h>
#include <algorithm>

namespace surfit {

bool surf_load(const char * filename, const char * surfname) 
{
	const char * fname = find_first(filename);
	bool res = false;

	while (fname != NULL) {
		d_surf * srf = _surf_load(fname, surfname);
		if (srf != NULL) {
			surfit_surfs->push_back(srf);
			res = true;
		}
		fname = find_next();
	}
	find_close();
	return res;
};

bool surf_save(const char * filename, const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;

	return _surf_save(srf, filename);
};

bool surf_resid(const char * filename, const char * surf_pos, const char * pnts_pos) 
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (!pnts)
		return false;
	
	return _surf_resid(srf, pnts, filename);
};

REAL surf_minz(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	
	REAL minZ, maxZ;
	srf->getMinMaxZ(minZ, maxZ);
	return minZ;
};

REAL surf_area_minz(const char * area_pos, const char * surf_pos) 
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return FLT_MAX;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (area == NULL)
		return FLT_MAX;

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return FLT_MAX;

	REAL minZ, maxZ;
	srf->getMinMaxZ_mask(minZ, maxZ, mask);

	if (mask)
		mask->release();
	return minZ;
};

REAL surf_maxz(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	REAL minZ, maxZ;
	srf->getMinMaxZ(minZ, maxZ);
	return maxZ;
};

REAL surf_area_maxz(const char * area_pos, const char * surf_pos) 
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return FLT_MAX;

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	
	REAL minZ, maxZ;
	srf->getMinMaxZ_mask(minZ, maxZ, mask);

	if (mask)
		mask->release();
	return maxZ;
};

REAL surf_mean(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->mean();
};

REAL surf_wmean(const char * wsurf_pos, const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;

	d_surf * srfw = get_element<d_surf>(wsurf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srfw)
		return FLT_MAX;

	return srf->wmean(srfw);
};

REAL surf_std(REAL mean, const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->std(mean);
};

REAL surf_sum(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->sum();
};

struct match_surf_to_pnts
{
	match_surf_to_pnts(const char * ipos) : pos(ipos), res(false) {};
	void operator()(d_surf * srf) 
	{
		if ( StringMatch( pos, srf->getName() ) )
		{
			writelog(LOG_MESSAGE,"converting surface \"%s\" to points", srf->getName());
			d_points * pnts = _surf_to_pnts(srf);
			if (!pnts)
				return;
			
			surfit_pnts->push_back(pnts);
			res = true;
		}
	};
	bool res;
	const char * pos;
};

bool surf_to_pnts(const char * surf_pos) 
{
	match_surf_to_pnts msp(surf_pos);
	msp = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), msp);
	return msp.res;
}

int surf_getCountX(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return 0;
	return srf->getCountX();
};

int surf_getCountY(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return 0;
	return srf->getCountY();
};

REAL surf_getStepX(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getStepX();
};

REAL surf_getStepY(const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getStepY();
};

REAL surf_getValue(REAL x, REAL y, const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getValue(x,y);
};

REAL surf_getValueIJ(int i, int j, const char * pos) 
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getValueIJ(i,j);
};

struct surf_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2) = 0;
};

struct match_surf_oper2
{
	match_surf_oper2(d_surf * isurf1, const char * ipos2, surf_oper * ioper) : surf1(isurf1), pos2(ipos2), res(false), oper(ioper) {};
	void operator()(d_surf * surf2)
	{
		if ( StringMatch(pos2, surf2->getName()) )
		{
			res = oper->do_oper(surf1, surf2);	
			
		}
	}
	d_surf * surf1;
	const char * pos2;
	bool res;
	surf_oper * oper;
};

struct match_surf_oper
{
	match_surf_oper(const char * ipos1, const char * ipos2, surf_oper * ioper) : pos1(ipos1), pos2(ipos2), res(false), oper(ioper) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos1, surf->getName()) )
		{
			match_surf_oper2 qq(surf, pos2, oper);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			res = qq.res;
		}
	}
	const char * pos1;
	const char * pos2;
	bool res;
	surf_oper * oper;
};

struct surf_oper_plus : public surf_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2)
	{
		writelog(LOG_MESSAGE,"surf_plus: \"%s\" += \"%s\"", surf1->getName(),surf2->getName());
		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_plus : different grid");
			return false;
		}
		surf1->plus(surf2);
		return true;
	}
};

bool surf_plus(const char * pos1, const char * pos2) 
{
	surf_oper_plus oper_plus;
	match_surf_oper qq(pos1, pos2, &oper_plus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_oper_minus : public surf_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2)
	{
		writelog(LOG_MESSAGE,"surf_minus: \"%s\" -= \"%s\"",surf1->getName(),surf2->getName());
		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_minus : different grid");
			return false;
		}
		surf1->minus(surf2);
		return true;
	}
};

bool surf_minus(const char * pos1, const char * pos2) 
{
	surf_oper_minus oper_minus;
	match_surf_oper qq(pos1, pos2, &oper_minus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_oper_mult : public surf_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2)
	{
		writelog(LOG_MESSAGE,"surf_mult: \"%s\" *= \"%s\"",surf1->getName(),surf2->getName());
		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_mult : different grid");
			return false;
		}
		surf1->mult(surf2);
		return true;
	}
};

bool surf_mult(const char * pos1, const char * pos2) 
{
	surf_oper_mult oper_mult;
	match_surf_oper qq(pos1, pos2, &oper_mult);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_oper_div : public surf_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2)
	{
		writelog(LOG_MESSAGE,"surf_div: \"%s\" /= \"%s\"",surf1->getName(),surf2->getName());
		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_div : different grid");
			return false;
		}
		surf1->div(surf2);
		return true;
	}
};

bool surf_div(const char * pos1, const char * pos2) 
{
	surf_oper_div oper_div;
	match_surf_oper qq(pos1, pos2, &oper_div);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_oper_set : public surf_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2)
	{
		writelog(LOG_MESSAGE,"surf_set: \"%s\" = \"%s\"",surf1->getName(),surf2->getName());
		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_set : different grid");
			return false;
		}
		surf1->set(surf2);
		return true;
	}
};

bool surf_set(const char * pos1, const char * pos2) 
{
	surf_oper_set oper_set;
	match_surf_oper qq(pos1, pos2, &oper_set);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};


struct surf_area_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2, d_area * area) = 0;
};

struct match_surf_area_oper3
{
	match_surf_area_oper3(d_surf * isurf1, d_surf * isurf2, const char * iarea_pos, surf_area_oper * ioper) : surf1(isurf1), surf2(isurf2), res(false), oper(ioper), area_pos(iarea_pos) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			res = oper->do_oper(surf1, surf2, area);
		}
	}
	d_surf * surf1;
	d_surf * surf2;
	const char * area_pos;
	bool res;
	surf_area_oper * oper;
};


struct match_surf_area_oper2
{
	match_surf_area_oper2(d_surf * isurf1, const char * ipos2, const char * iarea_pos, surf_area_oper * ioper) : surf1(isurf1), pos2(ipos2), res(false), oper(ioper), area_pos(iarea_pos) {};
	void operator()(d_surf * surf2)
	{
		if ( StringMatch(pos2, surf2->getName()) )
		{
			match_surf_area_oper3 qq(surf1, surf2, area_pos, oper);	
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			res = qq.res;
		}
	}
	d_surf * surf1;
	const char * pos2;
	const char * area_pos;
	bool res;
	surf_area_oper * oper;
};

struct match_surf_area_oper
{
	match_surf_area_oper(const char * ipos1, const char * ipos2, const char * iarea_pos, surf_area_oper * ioper) : pos1(ipos1), pos2(ipos2), res(false), oper(ioper), area_pos(iarea_pos) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos1, surf->getName()) )
		{
			match_surf_area_oper2 qq(surf, pos2, area_pos, oper);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			res = qq.res;
		}
	}
	const char * pos1;
	const char * pos2;
	const char * area_pos;
	bool res;
	surf_area_oper * oper;
};

struct surf_area_oper_plus : public surf_area_oper
{
	bool do_oper(d_surf * surf1, d_surf * surf2, d_area * area)
	{
		writelog(LOG_MESSAGE,"surf_plus_area : \"%s\" += \"%s\" in area \"%s\"",
			surf1->getName(),surf2->getName(),area->getName());

		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_plus : different grid");
			return false;
		}

		bitvec * mask = nodes_in_area_mask(area, surf1->grd);
		surf1->plus_mask(surf2, mask);
		if (mask)
			mask->release();
		
		return true;
	}
};

bool surf_plus_area(const char * pos1, const char * area_pos, const char * pos2) 
{
	surf_area_oper_plus oper_plus;
	match_surf_area_oper qq(pos1, pos2, area_pos, &oper_plus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_area_oper_minus : public surf_area_oper
{
	bool do_oper(d_surf * surf1, d_surf * surf2, d_area * area)
	{
		writelog(LOG_MESSAGE,"surf_minus_area : \"%s\" -= \"%s\" in area \"%s\"",
			surf1->getName(),surf2->getName(),area->getName());

		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_minus : different grid");
			return false;
		}

		bitvec * mask = nodes_in_area_mask(area, surf1->grd);
		surf1->minus_mask(surf2, mask);
		if (mask)
			mask->release();
		
		return true;
	}
};

bool surf_minus_area(const char * pos1, const char * area_pos, const char * pos2) 
{
	surf_area_oper_minus oper_minus;
	match_surf_area_oper qq(pos1, pos2, area_pos, &oper_minus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_area_oper_mult : public surf_area_oper
{
	bool do_oper(d_surf * surf1, d_surf * surf2, d_area * area)
	{
		writelog(LOG_MESSAGE,"surf_mult_area : \"%s\" *= \"%s\" in area \"%s\"",
			surf1->getName(),surf2->getName(),area->getName());

		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_mult : different grid");
			return false;
		}

		bitvec * mask = nodes_in_area_mask(area, surf1->grd);
		surf1->mult_mask(surf2, mask);
		if (mask)
			mask->release();
		
		return true;
	}
};

bool surf_mult_area(const char * pos1, const char * area_pos, const char * pos2) 
{
	surf_area_oper_mult oper_mult;
	match_surf_area_oper qq(pos1, pos2, area_pos, &oper_mult);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_area_oper_div : public surf_area_oper
{
	bool do_oper(d_surf * surf1, d_surf * surf2, d_area * area)
	{
		writelog(LOG_MESSAGE,"surf_div_area : \"%s\" /= \"%s\" in area \"%s\"",
			surf1->getName(),surf2->getName(),area->getName());

		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_div : different grid");
			return false;
		}

		bitvec * mask = nodes_in_area_mask(area, surf1->grd);
		surf1->div_mask(surf2, mask);
		if (mask)
			mask->release();
		
		return true;
	}
};

bool surf_div_area(const char * pos1, const char * area_pos, const char * pos2) 
{
	surf_area_oper_div oper_div;
	match_surf_area_oper qq(pos1, pos2, area_pos, &oper_div);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_area_oper_set : public surf_area_oper
{
	bool do_oper(d_surf * surf1, d_surf * surf2, d_area * area)
	{
		writelog(LOG_MESSAGE,"surf_set_area : \"%s\" = \"%s\" in area \"%s\"",
			surf1->getName(),surf2->getName(),area->getName());

		if (!surf1->compare_grid(surf2))	{
			writelog(LOG_ERROR,"surf_set : different grid");
			return false;
		}

		bitvec * mask = nodes_in_area_mask(area, surf1->grd);
		surf1->set_mask(surf2, mask);
		if (mask)
			mask->release();
		
		return true;
	}
};

bool surf_set_area(const char * pos1, const char * area_pos, const char * pos2) 
{
	surf_area_oper_set oper_set;
	match_surf_area_oper qq(pos1, pos2, area_pos, &oper_set);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper 
{
	virtual bool do_oper(REAL val, d_surf * surf) = 0;
};

struct match_val_oper
{
	match_val_oper(REAL ival, const char * ipos, surf_val_oper * ioper) : val(ival), pos(ipos), res(false), oper(ioper) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName()) )
		{
			res = oper->do_oper(val, surf); 
		}
	}
	REAL val;
	const char * pos;
	bool res;
	surf_val_oper * oper;
};

struct surf_val_oper_plus : public surf_val_oper
{
	bool do_oper(REAL val, d_surf * surf)
	{
		writelog(LOG_MESSAGE,"surf_plus_value: \"%s\" += %g",surf->getName(),val);
		surf->plus(val);
		return true;
	}
};

bool surf_plus_value(REAL val, const char * pos) 
{
	surf_val_oper_plus oper_plus;
	match_val_oper qq(val, pos, &oper_plus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_minus : public surf_val_oper
{
	bool do_oper(REAL val, d_surf * surf)
	{
		writelog(LOG_MESSAGE,"surf_minus_value: \"%s\" -= %g",surf->getName(),val);
		surf->minus(val);
		return true;
	}
};

bool surf_minus_value(REAL val, const char * pos) 
{
	surf_val_oper_minus oper_minus;
	match_val_oper qq(val, pos, &oper_minus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_mult : public surf_val_oper
{
	bool do_oper(REAL val, d_surf * surf)
	{
		writelog(LOG_MESSAGE,"surf_mult_value: \"%s\" *= %g",surf->getName(),val);
		surf->mult(val);
		return true;
	}
};

bool surf_mult_value(REAL val, const char * pos) 
{
	surf_val_oper_mult oper_mult;
	match_val_oper qq(val, pos, &oper_mult);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_div : public surf_val_oper
{
	bool do_oper(REAL val, d_surf * surf)
	{
		writelog(LOG_MESSAGE,"surf_div_value: \"%s\" /= %g",surf->getName(),val);
		surf->div(val);
		return true;
	}
};

bool surf_div_value(REAL val, const char * pos) 
{
	surf_val_oper_div oper_div;
	match_val_oper qq(val, pos, &oper_div);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_set : public surf_val_oper
{
	bool do_oper(REAL val, d_surf * surf)
	{
		writelog(LOG_MESSAGE,"surf_set_value: \"%s\" = %g",surf->getName(),val);
		surf->set(val);
		return true;
	}
};

bool surf_set_value(REAL val, const char * pos) 
{
	surf_val_oper_set oper_set;
	match_val_oper qq(val, pos, &oper_set);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

bool surf_plus_value_area(REAL val, const char * surf_pos, const char * area_pos) 
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	writelog(LOG_MESSAGE,"surf_plus_value_area: \"%s\" += %g in area \"%s\"",
		srf->getName()?srf->getName():surf_pos,val,
		area->getName()?area->getName():area_pos);

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->plus_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_minus_value_area(REAL val, const char * area_pos, const char * surf_pos) 
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	writelog(LOG_MESSAGE,"surf_minus_value_area: \"%s\" -= %g in area \"%s\"",
		srf->getName()?srf->getName():surf_pos,val,
		area->getName()?area->getName():area_pos);

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->minus_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_mult_value_area(REAL val, const char * area_pos, const char * surf_pos) 
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	writelog(LOG_MESSAGE,"surf_mult_value_area: \"%s\" *= %g in area \"%s\"",
		srf->getName()?srf->getName():surf_pos,val,
		area->getName()?area->getName():area_pos);

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->mult_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_div_value_area(REAL val, const char * area_pos, const char * surf_pos) 
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	writelog(LOG_MESSAGE,"surf_div_value_area: \"%s\" /= %g in area \"%s\"",
		srf->getName()?srf->getName():surf_pos,val,
		area->getName()?area->getName():area_pos);

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->div_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_set_value_area(const char * Value, const char * area_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	writelog(LOG_MESSAGE,"surf_set_value_area: \"%s\" = %s in area \"%s\"",
		srf->getName()?srf->getName():surf_pos,Value,
		area->getName()?area->getName():area_pos);

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	REAL val = srf->undef_value;

	if ( strcmp("undef", Value) != 0 )
		val = atof(Value);

	srf->set_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_to_mask(REAL true_from, REAL true_to, const char * pos)
{
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;

	writelog(LOG_MESSAGE,"converting surface \"%s\" to mask",
		srf->getName()?srf->getName():pos);
	
	bitvec * bcoeff = create_bitvec( srf->coeff->size() );
	size_t i;
	REAL val;
	for (i = 0; i < srf->coeff->size(); i++) {
		val = (*(srf->coeff))(i);
		bool bval = ( (val >= true_from) && (val <= true_to) );
		if (bval)
			bcoeff->set_true(i);
		else
			bcoeff->set_false(i);
	};

	d_grid * fgrd = srf->grd;
	d_grid * grd = create_grid(fgrd);

	d_mask * msk = create_mask(bcoeff, grd);
	msk->setName(srf->getName());
	surfit_masks->push_back(msk);

	return true;
};

//
//
// wavelets section
//
//
bool surf_decomp(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_decomp(srf);
};

bool surf_auto_decomp(REAL eps, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_auto_decomp(srf,eps);
};

bool surf_add_noise(REAL std, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_add_noise(srf, std);
};

bool surf_recons(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_recons(srf);
};

bool surf_full_recons(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_full_recons(srf);
};

int surf_get_details_level(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return -1;
	return srf->details_h->size();
};

bool surf_undef(REAL new_undef_value, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	srf->set_undef_value(new_undef_value);
	return true;
};

REAL surf_D1(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return _surf_D1(srf);
};

REAL surf_D2(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return _surf_D2(srf);
};

void surf_info(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return;
	_surf_info(srf);
};

bool surf_project(const char * newname, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	if (!_grid_check())
		return false;

	if (!(srf->grd->operator == (surfit_grid))) {
		d_surf * res_surf2 = _surf_project(srf, surfit_grid);
		if (res_surf2) {
			if (newname)
				res_surf2->setName(newname);
			surfit_surfs->push_back(res_surf2);
			return true;
		}
		return false;
	}
	return false;
};

bool surf_gradient(const char * newname, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	d_surf * res = _surf_gradient(srf);
	if (res) {
		res->setName(newname);
		surfit_surfs->push_back(res);
		return true;
	}
	return false;
};

const char * surf_getName(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return srf->getName();
};

bool surf_setName(const char * new_name, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	srf->setName(new_name);
	return true;
};

bool surf_delall() {

	writelog(LOG_MESSAGE,"removing all surfaces from memory");

	if (surfit_surfs == NULL)
		return false;

	if (surfit_surfs->size() == 0) {
		return false;
	}
	
	release_elements(surfit_surfs->begin(), surfit_surfs->end());
	surfit_surfs->resize(0);

	return true;
};

bool surf_del(const char * pos) {
	std::vector<d_surf *>::iterator srf = get_iterator<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == surfit_surfs->end())
		return false;

	if (*srf == NULL)
		return false;

	writelog(LOG_MESSAGE,"removing surface \"%s\" from memory", (*srf)->getName()?(*srf)->getName():pos);

	if (*srf)
		(*srf)->release();
	surfit_surfs->erase(srf);
	return true;
};

int surf_size() {
	return surfit_surfs->size();
};

void surfs_info() {
	if (surfit_surfs->size() > 0) {
		size_t surf_cnt;
		for (surf_cnt = 0; surf_cnt < surfit_surfs->size(); surf_cnt++) {
			d_surf * a_srf = *(surfit_surfs->begin()+surf_cnt);
			if (a_srf) {
				_surf_info(a_srf);
			}
		}
	}
};

REAL surf_area_mean(const char * area_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _surf_mean_area(srf, area);
};

REAL surf_mask_mean(const char * mask_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;


	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (!mask)
		return false;

	return _surf_mean_mask(srf, mask);
};

REAL surf_area_wmean(const char * area_pos, const char * wsurf_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;

	d_surf * wsrf = get_element<d_surf>(wsurf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!wsrf)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _surf_wmean_area(srf, wsrf, area);
};

REAL surf_mask_wmean(const char * mask_pos, const char * wsurf_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;

	d_surf * wsrf = get_element<d_surf>(wsurf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!wsrf)
		return false;


	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (!mask)
		return false;

	return _surf_wmean_mask(srf, wsrf, mask);
};

REAL surf_sum_area(const char * area_pos,  const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _surf_sum_area(srf, area);
};

int surf_cells_in_area(const char * area_pos,  const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _surf_cells_in_area(srf, area);
};

bool surf_filter_by_mask(const char * surf_pos, const char * def_pos) {
	
	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_mask * msk = get_element<d_mask>(def_pos, surfit_masks->begin(), surfit_masks->end());
	if (msk == NULL)
		return false;

	writelog(LOG_MESSAGE,"filtering surface \"%s\" with mask \"%s\"",
		surf->getName(), msk->getName());
		
	size_t i,j;
	REAL x,y;
	bool val;
	
	size_t NN = surf->getCountX();
	size_t MM = surf->getCountY();
	size_t pos;

	for (i = 0; i < NN; i++) {
		x = surf->getCoordNodeX(i);
		for (j = 0; j < MM; j++) {
			y = surf->getCoordNodeY(j);
			val = msk->getValue(x,y);
			if (val == false) {
				pos = two2one(i, j, NN, MM);
				(*(surf->coeff))( pos ) = surf->undef_value;
			}
		}
	}
	
	return true;
};

struct match_sfa_by_area
{
	match_sfa_by_area(const char * iarea_pos, d_surf * isrf, bool iin_area) : area_pos(iarea_pos), srf(isrf), in_area(iin_area) {};
	
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"filtering surface \"%s\" inside area \"%s\"", srf->getName()?srf->getName():"noname", area->getName());
			
			bitvec * area_mask = nodes_in_area_mask(area, srf->grd);
			if (area_mask == NULL)
				return;
			
			size_t i,j,pos;
			bool val;
			size_t NN = srf->getCountX();
			size_t MM = srf->getCountY();
			
			for (i = 0; i < NN; i++) {
				for (j = 0; j < MM; j++) {
					pos = two2one(i, j, NN, MM);
					val = area_mask->get(pos);
					if (val == in_area) {
						(*(srf->coeff))( pos ) = srf->undef_value;
					}
				}
			}	
		}
	};

	const char * area_pos;
	d_surf * srf;
	bool in_area;
};


struct match_sfa_by_surf
{
	match_sfa_by_surf(const char * isurf_pos, const char * iarea_pos, bool iin_area) : surf_pos(isurf_pos), area_pos(iarea_pos), in_area(iin_area) {};
	
	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			std::for_each( surfit_areas->begin(), surfit_areas->end(), match_sfa_by_area(area_pos, srf, in_area));		
		}
	};

	const char * surf_pos;
	const char * area_pos;
	bool in_area;
};


void surf_filter_in_area(const char * surf_pos, const char * area_pos) 
{
	std::for_each( surfit_surfs->begin(), surfit_surfs->end(), match_sfa_by_surf(surf_pos, area_pos, true) );
};

void surf_filter_out_area(const char * surf_pos, const char * area_pos) 
{
	std::for_each( surfit_surfs->begin(), surfit_surfs->end(), match_sfa_by_surf(surf_pos, area_pos, false) );
};

struct match_sfbs2
{
	match_sfbs2(REAL ieps, d_surf * isurf1, const char * isurf2_pos) : eps(ieps), surf1(isurf1), surf2_pos(isurf2_pos), res(false) {};
	void operator()(d_surf * surf2)
	{
		if ( StringMatch(surf2_pos, surf2->getName()) )
		{
			writelog(LOG_MESSAGE,"filtering surface \"%s\" values with surface \"%s\" values",
				surf1->getName(),surf2->getName());
			
			size_t i,j;
			REAL x,y;
			REAL val1, val2;
			
			size_t NN = surf1->getCountX();
			size_t MM = surf1->getCountY();
			size_t pos;
			
			for (i = 0; i < NN; i++) {
				x = surf1->getCoordNodeX(i);
				for (j = 0; j < MM; j++) {
					y = surf1->getCoordNodeY(j);
					val1 = surf1->getValueIJ(i,j);
					if (val1 == surf1->undef_value)
						continue;
					val2 = surf2->getValue(x,y);
					if (val2 == surf2->undef_value)
						continue;
					if ( fabs(val2 - val1) < eps ) {
						pos = two2one(i, j, NN, MM);
						(*(surf1->coeff))( pos ) = surf1->undef_value;
					}
				}
			}
			res = true;
		}
	}
	bool res;
	REAL eps;
	d_surf * surf1;
	const char * surf2_pos;
};

struct match_sfbs
{
	match_sfbs(REAL ieps, const char * isurf1_pos, const char * isurf2_pos) : eps(ieps), surf1_pos(isurf1_pos), surf2_pos(isurf2_pos), res(false) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf1_pos, surf->getName()) )
		{
			match_sfbs2 qq(eps, surf, surf2_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			res = qq.res;
		}
	}
	REAL eps;
	const char * surf1_pos;
	const char * surf2_pos;
	bool res;
};

bool surf_filter_by_surf(REAL eps, const char * surf1_pos, const char * surf2_pos) 
{
	match_sfbs qq(eps, surf1_pos, surf2_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_swapxy
{
	match_swapxy(const char * ipos) : pos(ipos), res(false) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"changing axes for surface \"%s\"",surf->getName());
			
			if (surf->coeff == NULL)
				return;
			
			if (surf->grd == NULL)
				return;
			
			extvec * new_coeff = create_extvec(surf->coeff->size());
			
			size_t NN = surf->getCountX();
			size_t MM = surf->getCountY();
			size_t pos;
			REAL val;
			
			size_t i,j, I, J;
			for (i = 0; i < NN; i++) {
				for (j = 0; j < MM; j++) {
					val = surf->getValueIJ(i,j);
					J = i;
					I = j;
					pos = two2one(I, J, MM, NN);
					(*new_coeff)( pos ) = val;
				}
			}
			
			surf->coeff->release();
			surf->coeff = new_coeff;
			
			std::swap(surf->grd->startX, surf->grd->startY);
			std::swap(surf->grd->stepX, surf->grd->stepY);
			std::swap(surf->grd->endX, surf->grd->endY);
			res = true;
		}
	}
	const char * pos;
	bool res;
};

bool surf_swapxy(const char * surf_pos)
{
	match_swapxy qq(surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_trace
{
	match_trace(const char * ipos, REAL ifrom, REAL ito, REAL istep) : pos(ipos), from(ifrom), to(ito), step(istep), res(false) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (from == FLT_MAX)
				surf->getMinMaxZ(from, to);	
			if (to == FLT_MAX)
				to = from;

			if (step == FLT_MAX)
			{
				step = stepFunc(from, to, 10);
			}

			vec * levels = create_vec();
			REAL level;
			for (level = from; level <= to; level += step)
				levels->push_back(level);

			size_t levels_count = levels->size();
			size_t NN = surf->getCountX(), MM = surf->getCountY();
			size_t q,p;
			REAL x,y;
			
			vec * x_coords = create_vec(NN,0,0);
			for (q = 0; q < NN; q++) {
				surf->getCoordNode(q,0,x,y);
				(*x_coords)(q) = x;
			}

			vec * y_coords = create_vec(MM,0,0);
			for (q = 0; q < MM; q++) {
				surf->getCoordNode(0,q,x,y);
				(*y_coords)(q) = y;
			}

			extvec * data = create_extvec(*(surf->coeff)); // don't fill;
			
			writelog(LOG_MESSAGE,"tracing %d contours from surface \"%s\"", levels_count, surf->getName());
			std::vector<fiso *> * isos = trace_isos(levels, x_coords, y_coords, data, NN, MM, surf->undef_value, false);
			levels->release();
			x_coords->release();
			y_coords->release();
			data->release();

			std::vector<int> cnts(levels_count);
			char buf[512];
						
			for (q = 0; q < isos->size(); q++)
			{
				fiso * iso = (*isos)[q];
				size_t level_num = iso->get_level_number();
				bool prev_visible = false;
				d_cntr * cntr = NULL;
				vec * x = NULL;
				vec * y = NULL;
				vec * z = NULL;
				REAL iso_level = iso->get_level();
				for (p = 0; p < iso->size(); p++) {

					double px, py;
					bool visible;
					iso->get_point(p, px, py, visible);
					if (visible != prev_visible) {
						if (prev_visible == false) {
							if (cntr) {
								if (cntr->size() > 0)
									surfit_cntrs->push_back(cntr);
								else {
									if (x)
										x->release();
									if (y)
										y->release();
									if (z)
										z->release();
								}
							}
							cnts[level_num]++;
							if (cnts[level_num] == 1)
								sprintf(buf,"%s_%g",surf->getName(), iso->get_level());
							else
								sprintf(buf,"%s_%g_%d",surf->getName(), iso->get_level(), cnts[level_num]);
							x = create_vec();
							y = create_vec();
							z = create_vec();
							cntr = create_cntr(x, y, z, buf);
						}
					}
					if (visible) {
						x->push_back(px);
						y->push_back(py);
						z->push_back(iso_level);
					}
					prev_visible = visible;
				}
				if (cntr) {
					if (cntr->size() > 0)
						surfit_cntrs->push_back(cntr);
					else {
						if (x)
							x->release();
						if (y)
							y->release();
						if (z)
							z->release();
					}
				}
				
			}

			delete isos;

			res = true;
		}
	};
	const char * pos;
	REAL from;
	REAL to;
	REAL step;
	bool res;
};

bool surf_trace_cntr(const char * surface_name_or_position, REAL from, REAL to, REAL step)
{
	match_trace qq(surface_name_or_position, from, to, step);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

}; // namespace surfit;

