
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
#include "boolvec.h"
#include "intvec.h"
#include "strvec.h"
#include "read_txt.h"

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
#include "variables_tcl.h"

#include "grid_user.h"
#include "findfile.h"

#include <float.h>
#include <algorithm>

namespace surfit {

boolvec * surf_load(const char * filename, const char * surfname) 
{
	const char * fname = find_first(filename);
	boolvec * res = create_boolvec();

	while (fname != NULL) {
		d_surf * srf = _surf_load(fname, surfname);
		if (srf != NULL) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		} else
			res->push_back(false);
		fname = find_next();
	}
	find_close();
	return res;
};

struct match_surf_save
{
	match_surf_save(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			bool r = _surf_save(surf, filename);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(r);
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * surf_save(const char * filename, const char * pos) 
{
	match_surf_save qq(filename, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
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

struct match_surf_minz
{
	match_surf_minz(const char * ipos)  : pos(ipos), res(NULL) {}
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating minimum surface \"%s\" value", surf->getName());
			REAL minZ, maxZ;
			surf->getMinMaxZ(minZ, maxZ);
			res->push_back(minZ);
		}
	}
	const char * pos;
	vec * res;
};

vec * surf_minz(const char * pos) 
{
	match_surf_minz qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_area_minz2
{
	match_surf_area_minz2(d_surf * isurf, const char * iarea_pos) : surf(isurf), area_pos(iarea_pos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			if (res == NULL)
				res = create_vec();

			writelog(LOG_MESSAGE,"calculating minimum surface \"%s\" value inside area \"%s\"", surf->getName(), area->getName());

			bitvec * mask = nodes_in_area_mask(area, surf->grd);
			if (mask == NULL) {
				res->push_back(surf->undef_value);
				return;
			}

			REAL minZ, maxZ;
			surf->getMinMaxZ_mask(minZ, maxZ, mask);
			res->push_back(minZ);

			if (mask)
				mask->release();
		}
	}
	d_surf * surf;
	const char * area_pos;
	vec * res;
};

struct match_surf_area_minz
{
	match_surf_area_minz(const char * iarea_pos, const char * isurf_pos) : area_pos(iarea_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_area_minz2 qq(surf, area_pos);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * area_pos; 
	const char * surf_pos;
	vec * res;
};

vec * surf_area_minz(const char * area_pos, const char * surf_pos) 
{
	match_surf_area_minz qq(area_pos, surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_maxz
{
	match_surf_maxz(const char * ipos)  : pos(ipos), res(NULL) {}
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating maximum surface \"%s\" value", surf->getName());
			REAL minZ, maxZ;
			surf->getMinMaxZ(minZ, maxZ);
			res->push_back(maxZ);
		}
	}
	const char * pos;
	vec * res;
};

vec * surf_maxz(const char * pos) 
{
	match_surf_maxz qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_area_maxz2
{
	match_surf_area_maxz2(d_surf * isurf, const char * iarea_pos) : surf(isurf), area_pos(iarea_pos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			if (res == NULL)
				res = create_vec();

			writelog(LOG_MESSAGE,"calculating maximum surface \"%s\" value inside area \"%s\"", surf->getName(), area->getName());

			bitvec * mask = nodes_in_area_mask(area, surf->grd);
			if (mask == NULL) {
				res->push_back(surf->undef_value);
				return;
			}

			REAL minZ, maxZ;
			surf->getMinMaxZ_mask(minZ, maxZ, mask);
			res->push_back(maxZ);

			if (mask)
				mask->release();
		}
	}
	d_surf * surf;
	const char * area_pos;
	vec * res;
};

struct match_surf_area_maxz
{
	match_surf_area_maxz(const char * iarea_pos, const char * isurf_pos) : area_pos(iarea_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_area_maxz2 qq(surf, area_pos);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * area_pos; 
	const char * surf_pos;
	vec * res;
};

vec * surf_area_maxz(const char * area_pos, const char * surf_pos) 
{
	match_surf_area_maxz qq(area_pos, surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_mean
{
	match_surf_mean(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating surface \"%s\" mean value", surf->getName());
			res->push_back(surf->mean());
		}
	}
	const char * pos;
	vec * res;
};

vec * surf_mean(const char * pos) 
{
	match_surf_mean qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_wmean2
{
	match_surf_wmean2(d_surf * iwsurf, const char * isurf_pos) : wsurf(iwsurf), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating surface \"%s\" weighted mean value with weight surface \"%s\"",surf->getName(), wsurf->getName());
			res->push_back( surf->wmean(wsurf) );
		}
	}
	d_surf * wsurf;
	const char * surf_pos;
	vec * res;
};

struct match_surf_wmean
{
	match_surf_wmean(const char * iwsurf_pos, const char * isurf_pos) : wsurf_pos(iwsurf_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * wsurf)
	{
		if ( StringMatch(wsurf_pos, wsurf->getName()) )
		{
			match_surf_wmean2 qq(wsurf, surf_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * wsurf_pos;
	const char * surf_pos;
	vec * res;
};

vec * surf_wmean(const char * wsurf_pos, const char * pos) 
{
	match_surf_wmean qq(wsurf_pos, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_std
{
	match_surf_std(REAL imean, const char * ipos) : mean(imean), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating std for surface \"%s\" with mean %g", surf->getName(), mean);
			res->push_back( surf->std(mean) );
		}
	}
	REAL mean;
	const char * pos;
	vec * res;
};

vec * surf_std(REAL mean, const char * pos) 
{
	match_surf_std qq(mean, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_sum
{
	match_surf_sum(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating sum of all surface \"%s\" cell values", surf->getName());
			res->push_back( surf->sum() );
		}
	}
	const char * pos;
	vec * res;
};

vec * surf_sum(const char * pos) 
{
	match_surf_sum qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_to_pnts
{
	match_surf_to_pnts(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * srf) 
	{
		if ( StringMatch( pos, srf->getName() ) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"converting surface \"%s\" to points", srf->getName());
			d_points * pnts = _surf_to_pnts(srf);
			if (!pnts) {
				res->push_back(false);
				return;
			}
			
			surfit_pnts->push_back(pnts);
			res->push_back(true);
		}
	};
	boolvec * res;
	const char * pos;
};

boolvec * surf_to_pnts(const char * surf_pos) 
{
	match_surf_to_pnts msp(surf_pos);
	msp = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), msp);
	return msp.res;
}

struct match_surf_getCountX
{
	match_surf_getCountX(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			if (res == NULL)
				res = create_intvec();
			writelog(LOG_MESSAGE, "surf_getCountX : \"%s\"", surf->getName());
			res->push_back( surf->getCountX() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * surf_getCountX(const char * pos) 
{
	match_surf_getCountX qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_getCountY
{
	match_surf_getCountY(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			if (res == NULL)
				res = create_intvec();
			writelog(LOG_MESSAGE, "surf_getCountY : \"%s\"", surf->getName());
			res->push_back( surf->getCountY() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * surf_getCountY(const char * pos) 
{
	match_surf_getCountY qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_getStepX {
	match_surf_getStepX(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			if (res == NULL)
				res = create_vec();
			res->push_back( surf->getStepX() );
		};
	};
	const char * pos;
	vec * res;
};

vec * surf_getStepX(const char * pos) 
{
	match_surf_getStepX qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_getStepY {
	match_surf_getStepY(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName() ) )
		{
			if (res == NULL)
				res = create_vec();
			res->push_back( surf->getStepY() );
		};
	};
	const char * pos;
	vec * res;
};

vec * surf_getStepY(const char * pos) 
{
	match_surf_getStepY qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_getValue
{
	match_surf_getValue(REAL ix, REAL iy, const char * ipos) : x(ix), y(iy), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			double val = surf->getValue(x,y);
			res->push_back(val);
		}
	}
	REAL x, y;
	const char * pos;
	vec * res;
};

vec * surf_getValue(REAL x, REAL y, const char * pos) 
{
	match_surf_getValue qq(x,y,pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_getValueIJ
{
	match_surf_getValueIJ(int ii, int ij, const char * ipos) : i(ii), j(ij), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			double val = surf->getValueIJ(i,j);
			res->push_back(val);
		}
	}
	int i, j;
	const char * pos;
	vec * res;
};


vec * surf_getValueIJ(int i, int j, const char * pos) 
{
	match_surf_getValueIJ qq(i,j,pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_oper
{
	virtual bool do_oper(d_surf * surf1, d_surf * surf2) = 0;
};

struct match_surf_oper2
{
	match_surf_oper2(d_surf * isurf1, const char * ipos2, surf_oper * ioper) : surf1(isurf1), pos2(ipos2), res(NULL), oper(ioper) {};
	void operator()(d_surf * surf2)
	{
		if ( StringMatch(pos2, surf2->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(surf1, surf2) );
		}
	}
	d_surf * surf1;
	const char * pos2;
	boolvec * res;
	surf_oper * oper;
};

struct match_surf_oper
{
	match_surf_oper(const char * ipos1, const char * ipos2, surf_oper * ioper) : pos1(ipos1), pos2(ipos2), res(NULL), oper(ioper) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos1, surf->getName()) )
		{
			match_surf_oper2 qq(surf, pos2, oper);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pos1;
	const char * pos2;
	boolvec * res;
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

boolvec * surf_plus(const char * pos1, const char * pos2) 
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

boolvec * surf_minus(const char * pos1, const char * pos2) 
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

boolvec * surf_mult(const char * pos1, const char * pos2) 
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

boolvec * surf_div(const char * pos1, const char * pos2) 
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

boolvec * surf_set(const char * pos1, const char * pos2) 
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
	match_surf_area_oper3(d_surf * isurf1, d_surf * isurf2, const char * iarea_pos, surf_area_oper * ioper) : surf1(isurf1), surf2(isurf2), res(NULL), oper(ioper), area_pos(iarea_pos) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(surf1, surf2, area) );
		}
	}
	d_surf * surf1;
	d_surf * surf2;
	const char * area_pos;
	boolvec * res;
	surf_area_oper * oper;
};


struct match_surf_area_oper2
{
	match_surf_area_oper2(d_surf * isurf1, const char * ipos2, const char * iarea_pos, surf_area_oper * ioper) : surf1(isurf1), pos2(ipos2), res(NULL), oper(ioper), area_pos(iarea_pos) {};
	void operator()(d_surf * surf2)
	{
		if ( StringMatch(pos2, surf2->getName()) )
		{
			match_surf_area_oper3 qq(surf1, surf2, area_pos, oper);	
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back( qq.res );
		}
	}
	d_surf * surf1;
	const char * pos2;
	const char * area_pos;
	boolvec * res;
	surf_area_oper * oper;
};

struct match_surf_area_oper
{
	match_surf_area_oper(const char * ipos1, const char * ipos2, const char * iarea_pos, surf_area_oper * ioper) : pos1(ipos1), pos2(ipos2), res(NULL), oper(ioper), area_pos(iarea_pos) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos1, surf->getName()) )
		{
			match_surf_area_oper2 qq(surf, pos2, area_pos, oper);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back( qq.res );
		}
	}
	const char * pos1;
	const char * pos2;
	const char * area_pos;
	boolvec * res;
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

boolvec * surf_plus_area(const char * pos1, const char * area_pos, const char * pos2) 
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

boolvec * surf_minus_area(const char * pos1, const char * area_pos, const char * pos2) 
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

boolvec * surf_mult_area(const char * pos1, const char * area_pos, const char * pos2) 
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

boolvec * surf_div_area(const char * pos1, const char * area_pos, const char * pos2) 
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

boolvec * surf_set_area(const char * pos1, const char * area_pos, const char * pos2) 
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
	match_val_oper(REAL ival, const char * ipos, surf_val_oper * ioper) : val(ival), pos(ipos), res(NULL), oper(ioper) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(val, surf) ); 
		}
	}
	REAL val;
	const char * pos;
	boolvec * res;
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

boolvec * surf_plus_value(REAL val, const char * pos) 
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

boolvec * surf_minus_value(REAL val, const char * pos) 
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

boolvec * surf_mult_value(REAL val, const char * pos) 
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

boolvec * surf_div_value(REAL val, const char * pos) 
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

boolvec * surf_set_value(REAL val, const char * pos) 
{
	surf_val_oper_set oper_set;
	match_val_oper qq(val, pos, &oper_set);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_area 
{
	virtual bool do_oper(REAL val, d_surf * surf, d_area * area) = 0;
};

struct match_val_oper_area2
{
	match_val_oper_area2(REAL ival, d_surf * isurf, const char * iarea_pos, surf_val_oper_area * ioper_area) : val(ival), surf(isurf), area_pos(iarea_pos), oper(ioper_area), res(NULL) {};
	void operator()(d_area * area) 
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(val, surf, area) );
		}
	}
	REAL val;
	d_surf * surf;
	const char * area_pos;
	boolvec * res;
	surf_val_oper_area * oper;
};

struct match_val_oper_area
{
	match_val_oper_area(REAL ival, const char * isurf_pos, const char * iarea_pos, surf_val_oper_area * ioper_area) 
		: val(ival), surf_pos(isurf_pos), area_pos(iarea_pos), res(NULL), oper(ioper_area) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName()) )
		{
			match_val_oper_area2 qq(val, surf, area_pos, oper);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back( qq.res ); 
		}
	}
	REAL val;
	const char * surf_pos;
	const char * area_pos;
	boolvec * res;
	surf_val_oper_area * oper;
};

struct surf_val_oper_area_plus : public surf_val_oper_area
{
	virtual bool do_oper(REAL val, d_surf * surf, d_area * area) 
	{
		writelog(LOG_MESSAGE,"surf_plus_value_area: \"%s\" += %g in area \"%s\"",
			surf->getName(),val,area->getName());

		bitvec * mask = nodes_in_area_mask(area, surf->grd);
		if (mask == NULL)
			return false;

		surf->plus_mask(val, mask);
		if (mask)
			mask->release();
		return true;
	};
};

boolvec * surf_plus_value_area(REAL val, const char * surf_pos, const char * area_pos) 
{
	surf_val_oper_area_plus oper_plus;
	match_val_oper_area qq(val, surf_pos, area_pos, &oper_plus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_area_minus : public surf_val_oper_area
{
	virtual bool do_oper(REAL val, d_surf * surf, d_area * area) 
	{
		writelog(LOG_MESSAGE,"surf_minus_value_area: \"%s\" -= %g in area \"%s\"",
			surf->getName(),val,area->getName());

		bitvec * mask = nodes_in_area_mask(area, surf->grd);
		if (mask == NULL)
			return false;

		surf->minus_mask(val, mask);
		if (mask)
			mask->release();
		return true;
	};
};

boolvec * surf_minus_value_area(REAL val, const char * area_pos, const char * surf_pos) 
{
	surf_val_oper_area_minus oper_minus;
	match_val_oper_area qq(val, surf_pos, area_pos, &oper_minus);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_area_mult : public surf_val_oper_area
{
	virtual bool do_oper(REAL val, d_surf * surf, d_area * area) 
	{
		writelog(LOG_MESSAGE,"surf_mult_value_area: \"%s\" *= %g in area \"%s\"",
			surf->getName(),val,area->getName());

		bitvec * mask = nodes_in_area_mask(area, surf->grd);
		if (mask == NULL)
			return false;

		surf->minus_mask(val, mask);
		if (mask)
			mask->release();
		return true;
	};
};

boolvec * surf_mult_value_area(REAL val, const char * area_pos, const char * surf_pos) 
{
	surf_val_oper_area_mult oper_mult;
	match_val_oper_area qq(val, surf_pos, area_pos, &oper_mult);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_area_div : public surf_val_oper_area
{
	virtual bool do_oper(REAL val, d_surf * surf, d_area * area) 
	{
		writelog(LOG_MESSAGE,"surf_div_value_area: \"%s\" /= %g in area \"%s\"",
			surf->getName(),val,area->getName());

		bitvec * mask = nodes_in_area_mask(area, surf->grd);
		if (mask == NULL)
			return false;

		surf->minus_mask(val, mask);
		if (mask)
			mask->release();
		return true;
	};
};

boolvec * surf_div_value_area(REAL val, const char * area_pos, const char * surf_pos) 
{
	surf_val_oper_area_div oper_div;
	match_val_oper_area qq(val, surf_pos, area_pos, &oper_div);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct surf_val_oper_area_set : public surf_val_oper_area
{
	virtual bool do_oper(REAL val, d_surf * surf, d_area * area) 
	{
		writelog(LOG_MESSAGE,"surf_set_value_area: \"%s\" = %g in area \"%s\"",
			surf->getName(),val,area->getName());

		bitvec * mask = nodes_in_area_mask(area, surf->grd);
		if (mask == NULL)
			return false;

		surf->minus_mask(val, mask);
		if (mask)
			mask->release();
		return true;
	};
};

boolvec * surf_set_value_area(const char * Val, const char * area_pos, const char * surf_pos) 
{
	char * cp = strdup(Val);
	REAL val = ator(cp);
	free(cp);
	if (strcmp(Val,"undef") == 0)
		val = undef_value;
	surf_val_oper_area_set oper_set;
	match_val_oper_area qq(val, surf_pos, area_pos, &oper_set);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_to_mask
{
	match_surf_to_mask(REAL itrue_from, REAL itrue_to, const char * ipos) : true_from(itrue_from), true_to(itrue_to), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"converting surface \"%s\" to mask",surf->getName());

			bitvec * bcoeff = create_bitvec( surf->coeff->size() );
			size_t i;
			REAL val;
			for (i = 0; i < surf->coeff->size(); i++) {
				val = (*(surf->coeff))(i);
				bool bval = ( (val >= true_from) && (val <= true_to) );
				if (bval)
					bcoeff->set_true(i);
				else
					bcoeff->set_false(i);
			};

			d_grid * fgrd = surf->grd;
			d_grid * grd = create_grid(fgrd);

			d_mask * msk = create_mask(bcoeff, grd);
			msk->setName(surf->getName());
			surfit_masks->push_back(msk);
			res->push_back(true);
		}
	}
	REAL true_from; 
	REAL true_to; 
	const char * pos;
	boolvec * res;
};

boolvec * surf_to_mask(REAL true_from, REAL true_to, const char * pos)
{
	match_surf_to_mask qq(true_from, true_to, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

//
//
// wavelets section
//
//

struct match_surf_decomp
{
	match_surf_decomp(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _surf_decomp(surf) );
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * surf_decomp(const char * pos) 
{
	match_surf_decomp qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_auto_decomp
{
	match_surf_auto_decomp(REAL ieps, const char * ipos) : pos(ipos), res(NULL), eps(ieps) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _surf_auto_decomp(surf,eps) );
		}
	}
	const char * pos;
	boolvec * res;
	REAL eps;
};

boolvec * surf_auto_decomp(REAL eps, const char * pos) 
{
	match_surf_auto_decomp qq(eps, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_add_noise
{
	match_surf_add_noise(REAL istd, const char * ipos) : std(istd), pos(ipos) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"adding noise N(0,%g) to surface \"%s\"", std, surf->getName());
			_surf_add_noise(surf, std);
		}
	}
	REAL std;
	const char * pos;
};

void surf_add_noise(REAL std, const char * pos) 
{
	std::for_each(surfit_surfs->begin(), surfit_surfs->end(), match_surf_add_noise(std, pos));
};

struct match_surf_recons
{
	match_surf_recons(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _surf_recons(surf) );
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * surf_recons(const char * pos) 
{
	match_surf_recons qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_full_recons
{
	match_surf_full_recons(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _surf_full_recons(surf) );
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * surf_full_recons(const char * pos) 
{
	match_surf_full_recons qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_get_details_level
{
	match_surf_get_details_level(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( (int)surf->details_h->size() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * surf_get_details_level(const char * pos) 
{
	match_surf_get_details_level qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_undef
{
	match_surf_undef(REAL inew_undef_value, const char * ipos) : new_undef_value(inew_undef_value), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			surf->undef_value = new_undef_value;
			res->push_back( true );
		}
	}
	REAL new_undef_value;
	const char * pos;
	boolvec * res;
};

boolvec * surf_undef(REAL new_undef_value, const char * pos) 
{
	match_surf_undef qq(new_undef_value, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_D1
{	
	match_surf_D1(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			double val = _surf_D1(surf);
			res->push_back(val);
		}
	}
	const char * pos;
	vec * res;
};

vec * surf_D1(const char * pos) 
{
	match_surf_D1 qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_D2
{	
	match_surf_D2(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			double val = _surf_D2(surf);
			res->push_back(val);
		}
	}
	const char * pos;
	vec * res;
};

vec * surf_D2(const char * pos) 
{
	match_surf_D2 qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

void surf_info(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return;
	_surf_info(srf);
};

struct match_surf_project
{
	match_surf_project(const char * ipos, const char * inewname) : pos(ipos), newname(inewname), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			if (!_grid_check()) {
				res->push_back(false);
				return;
			}
			if (!(surf->grd->operator == (surfit_grid))) {
				d_surf * res_surf2 = _surf_project(surf, surfit_grid);
				if (res_surf2) {
					if (newname)
						res_surf2->setName(newname);
					else {
						char buf[512];
						sprintf(buf, "%s_proj", surf->getName());
						res_surf2->setName(buf);
					}
					surfs.push_back(res_surf2);
					res->push_back(true);
					return;
				}
			}
			res->push_back(false);
			return;
		}
	}
	const char * pos;
	const char * newname;
	boolvec * res;
	std::vector<d_surf *> surfs;
};

boolvec * surf_project(const char * pos, const char * newname) 
{
	match_surf_project qq(pos, newname);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	size_t i;
	for (i = 0; i < qq.surfs.size(); i++)
		surfit_surfs->push_back( qq.surfs[i] );
	return qq.res;
};

struct match_surf_gradient
{
	match_surf_gradient(const char * inewname, const char * ipos) : newname(inewname), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			d_surf * ss = _surf_gradient(surf);
			if (ss) {
				if (newname)
					ss->setName(newname);
				else {
					char buf[512];
					sprintf(buf, "%s_grad", surf->getName());
					ss->setName(buf);
				}
				surfs.push_back(ss);
				res->push_back(true);
			} else
				res->push_back(false);

		}
	}
	const char * newname;
	const char * pos;
	boolvec * res;
	std::vector<d_surf *> surfs;
};

boolvec * surf_gradient(const char * pos, const char * newname) 
{
	match_surf_gradient qq(newname, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	size_t i;
	for (i = 0; i < qq.surfs.size(); i++)
		surfit_surfs->push_back( qq.surfs[i] );
	return qq.res;
};

struct match_surf_getName {
	match_surf_getName(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( surf->getName() );
		}
	};
	const char * pos;
	strvec * res;
};

strvec * surf_getName(const char * pos) 
{
	match_surf_getName qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_getId {
	match_surf_getId(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( surf->getId() );
		}
	};
	const char * pos;
	intvec * res;
};

intvec * surf_getId(const char * pos) 
{
	match_surf_getId qq(pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_setName {
	match_surf_setName(const char * inewname, const char * ipos) : newname(inewname), pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			surf->setName(newname);
			res->push_back(true);
		}
	};
	const char * pos;
	const char * newname;
	boolvec * res;
};

boolvec * surf_setName(const char * new_name, const char * pos) 
{
	match_surf_setName qq(new_name, pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

void surf_del(const char * pos) 
{
	if (surfit_surfs->size() == 0)
		return;
	size_t i;
	for (i = surfit_surfs->size()-1; i >= 0; i--)
	{
		d_surf * surf = (*surfit_surfs)[i];
		if ( StringMatch(pos, surf->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing surface \"%s\" from memory", surf->getName());
			surf->release();
			surfit_surfs->erase(surfit_surfs->begin()+i);
		}
		if (i == 0)
			break;
	}
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

struct match_surf_area_mean2
{
	match_surf_area_mean2(d_surf * isurf, const char * iarea_pos) : surf(isurf), area_pos(iarea_pos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating surface \"%s\" mean value inside area \"%s\"", surf->getName(), area->getName());
			res->push_back(_surf_mean_area(surf, area));
		}
	}
	d_surf * surf;
	const char * area_pos;
	vec * res;
};

struct match_surf_area_mean
{
	match_surf_area_mean(const char * iarea_pos, const char * isurf_pos) : area_pos(iarea_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_area_mean2 qq(surf, area_pos);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * area_pos; 
	const char * surf_pos;
	vec * res;
};

vec * surf_area_mean(const char * area_pos, const char * surf_pos) 
{
	match_surf_area_mean qq(area_pos, surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_mask_mean2
{
	match_surf_mask_mean2(d_surf * isurf, const char * imask_pos) : surf(isurf), mask_pos(imask_pos), res(NULL) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(mask_pos, mask->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating surface \"%s\" mean value where mask \"%s\" is true", surf->getName(), mask->getName());
			res->push_back(_surf_mean_mask(surf, mask));
		}
	}
	d_surf * surf;
	const char * mask_pos;
	vec * res;
};

struct match_surf_mask_mean
{
	match_surf_mask_mean(const char * imask_pos, const char * isurf_pos) : mask_pos(imask_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_mask_mean2 qq(surf, mask_pos);
			qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * mask_pos; 
	const char * surf_pos;
	vec * res;
};

vec * surf_mask_mean(const char * mask_pos, const char * surf_pos) 
{
	match_surf_mask_mean qq(mask_pos, surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_area_wmean3
{
	match_surf_area_wmean3(d_area * iarea, d_surf * iwsurf, const char * isurf_pos) :
				area(iarea), wsurf(iwsurf), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating surface \"%s\" weighted mean value with weight surface \"%s\" inside area \"%s\"", 
				surf->getName(), wsurf->getName(), area->getName());
			res->push_back( _surf_wmean_area(surf, wsurf, area) );
		}
	}
	d_area * area;
	d_surf * wsurf;
	const char * surf_pos;
	vec * res;
};

struct match_surf_area_wmean2
{
	match_surf_area_wmean2(d_area * iarea, const char * iwsurf_pos, const char * isurf_pos) :
				area(iarea), wsurf_pos(iwsurf_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * wsurf)
	{
		if ( StringMatch(wsurf_pos, wsurf->getName()) )
		{
			match_surf_area_wmean3 qq(area, wsurf, surf_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	d_area * area;
	const char * wsurf_pos;
	const char * surf_pos;
	vec * res;
};

struct match_surf_area_wmean
{
	match_surf_area_wmean(const char * iarea_pos, const char * iwsurf_pos, const char * isurf_pos) :
				area_pos(iarea_pos), wsurf_pos(iwsurf_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			match_surf_area_wmean2 qq(area, wsurf_pos, surf_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * area_pos;
	const char * wsurf_pos;
	const char * surf_pos;
	vec * res;
};

vec * surf_area_wmean(const char * area_pos, const char * wsurf_pos, const char * surf_pos) 
{
	match_surf_area_wmean qq(area_pos, wsurf_pos, surf_pos);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_surf_mask_wmean3
{
	match_surf_mask_wmean3(d_mask * imask, d_surf * iwsurf, const char * isurf_pos) :
				mask(imask), wsurf(iwsurf), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating surface \"%s\" weighted mean value with weight surface \"%s\" where mask \"%s\" is true", 
				surf->getName(), wsurf->getName(), mask->getName());
			res->push_back( _surf_wmean_mask(surf, wsurf, mask) );
		}
	}
	d_mask * mask;
	d_surf * wsurf;
	const char * surf_pos;
	vec * res;
};

struct match_surf_mask_wmean2
{
	match_surf_mask_wmean2(d_mask * imask, const char * iwsurf_pos, const char * isurf_pos) :
				mask(imask), wsurf_pos(iwsurf_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * wsurf)
	{
		if ( StringMatch(wsurf_pos, wsurf->getName()) )
		{
			match_surf_mask_wmean3 qq(mask, wsurf, surf_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	d_mask * mask;
	const char * wsurf_pos;
	const char * surf_pos;
	vec * res;
};

struct match_surf_mask_wmean
{
	match_surf_mask_wmean(const char * imask_pos, const char * iwsurf_pos, const char * isurf_pos) :
				mask_pos(imask_pos), wsurf_pos(iwsurf_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(mask_pos, mask->getName()) )
		{
			match_surf_mask_wmean2 qq(mask, wsurf_pos, surf_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * mask_pos;
	const char * wsurf_pos;
	const char * surf_pos;
	vec * res;
};

vec * surf_mask_wmean(const char * mask_pos, const char * wsurf_pos, const char * surf_pos) 
{
	match_surf_mask_wmean qq(mask_pos, wsurf_pos, surf_pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_surf_sum_area2
{
	match_surf_sum_area2(const char * iarea_pos, d_surf * isurf) : area_pos(iarea_pos), surf(isurf), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating sum of surface \"%s\" cell values for cells inside area \"%s\"", surf->getName(), area->getName());
			res->push_back( _surf_sum_area(surf, area) );
		}
	}
	const char * area_pos; 
	d_surf * surf;
	vec * res;
};

struct match_surf_sum_area
{
	match_surf_sum_area(const char * iarea_pos,  const char * isurf_pos) : area_pos(iarea_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_sum_area2 qq(area_pos, surf);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_vec();
			res->push_back(qq.res);
		}
	}
	const char * area_pos; 
	const char * surf_pos;
	vec * res;
};

vec * surf_sum_area(const char * area_pos,  const char * surf_pos) 
{
	match_surf_sum_area qq(area_pos, surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_cells_in_area2
{
	match_surf_cells_in_area2(const char * iarea_pos,  d_surf * isurf) : area_pos(iarea_pos), surf(isurf), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			writelog(LOG_MESSAGE,"calculating amount of surface \"%s\" cells inside area \"%s\"",surf->getName(), area->getName());
			res->push_back( _surf_cells_in_area(surf, area) );
		}
	}
	const char * area_pos;
	d_surf * surf;
	intvec * res;
};

struct match_surf_cells_in_area
{
	match_surf_cells_in_area(const char * iarea_pos,  const char * isurf_pos) : area_pos(iarea_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_cells_in_area2 qq(area_pos, surf);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_intvec();
			res->push_back(qq.res);
		}
	}
	const char * area_pos;
	const char * surf_pos;
	intvec * res;
};

intvec * surf_cells_in_area(const char * area_pos,  const char * surf_pos) 
{
	match_surf_cells_in_area qq(area_pos,surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_surf_filter_by_mask2
{
	match_surf_filter_by_mask2(d_surf * isurf, const char * imask_pos) : surf(isurf), mask_pos(imask_pos), res(NULL) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(mask_pos, mask->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"filtering surface \"%s\" with mask \"%s\"",
				surf->getName(), mask->getName());

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
					val = mask->getValue(x,y);
					if (val == false) {
						pos = two2one(i, j, NN, MM);
						(*(surf->coeff))( pos ) = surf->undef_value;
					}
				}
			}
			res->push_back(true);
		}
	}
	d_surf * surf;
	const char * mask_pos;
	boolvec * res;
};

struct match_surf_filter_by_mask
{
	match_surf_filter_by_mask(const char * isurf_pos, const char * imask_pos) : surf_pos(isurf_pos), mask_pos(imask_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_filter_by_mask2 qq(surf, mask_pos);
			qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * mask_pos;
	boolvec * res;
};

boolvec * surf_filter_by_mask(const char * surf_pos, const char * mask_pos) 
{
	match_surf_filter_by_mask qq(surf_pos, mask_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_sfa_by_area
{
	match_sfa_by_area(const char * iarea_pos, d_surf * isrf, bool iin_area) : area_pos(iarea_pos), srf(isrf), in_area(iin_area), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"filtering surface \"%s\" inside area \"%s\"", srf->getName(), area->getName());
			if (res == NULL)
				res = create_boolvec();
			bitvec * area_mask = nodes_in_area_mask(area, srf->grd);
			if (area_mask == NULL) {
				res->push_back(false);
				return;
			}
			
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
			res->push_back(true);
		}
	};

	const char * area_pos;
	d_surf * srf;
	bool in_area;
	boolvec * res;
};

struct match_sfa_by_surf
{
	match_sfa_by_surf(const char * isurf_pos, const char * iarea_pos, bool iin_area) : surf_pos(isurf_pos), area_pos(iarea_pos), in_area(iin_area), res(NULL) {};
	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			match_sfa_by_area qq(area_pos, srf, in_area);
			qq = std::for_each( surfit_areas->begin(), surfit_areas->end(), qq);		
			res->push_back( qq.res );
		}
	};

	const char * surf_pos;
	const char * area_pos;
	bool in_area;
	boolvec * res;
};


boolvec * surf_filter_in_area(const char * surf_pos, const char * area_pos) 
{
	match_sfa_by_surf qq(surf_pos, area_pos, true);
	qq = std::for_each( surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

boolvec * surf_filter_out_area(const char * surf_pos, const char * area_pos) 
{
	match_sfa_by_surf qq(surf_pos, area_pos, false);
	qq = std::for_each( surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_sfbs2
{
	match_sfbs2(REAL ieps, d_surf * isurf1, const char * isurf2_pos) : eps(ieps), surf1(isurf1), surf2_pos(isurf2_pos), res(NULL) {};
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
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	boolvec * res;
	REAL eps;
	d_surf * surf1;
	const char * surf2_pos;
};

struct match_sfbs
{
	match_sfbs(REAL ieps, const char * isurf1_pos, const char * isurf2_pos) : eps(ieps), surf1_pos(isurf1_pos), surf2_pos(isurf2_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf1_pos, surf->getName()) )
		{
			match_sfbs2 qq(eps, surf, surf2_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back( qq.res );
		}
	}
	REAL eps;
	const char * surf1_pos;
	const char * surf2_pos;
	boolvec * res;
};

boolvec * surf_filter_by_surf(REAL eps, const char * surf1_pos, const char * surf2_pos) 
{
	match_sfbs qq(eps, surf1_pos, surf2_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_swapxy
{
	match_swapxy(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			writelog(LOG_MESSAGE,"changing axes for surface \"%s\"",surf->getName());
			boolvec * res = create_boolvec();
			
			if (surf->coeff == NULL) {
				res->push_back(false);
				return;
			}
			
			if (surf->grd == NULL) {
				res->push_back(false);
				return;
			}
			
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
			
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * surf_swapxy(const char * surf_pos)
{
	match_swapxy qq(surf_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_trace
{
	match_trace(const char * ipos, REAL ifrom, REAL ito, REAL istep) : pos(ipos), from(ifrom), to(ito), step(istep), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
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
			res->push_back(true);
		}
	};
	const char * pos;
	REAL from;
	REAL to;
	REAL step;
	boolvec * res;
};

boolvec * surf_trace_cntr(const char * surface_name_or_position, REAL from, REAL to, REAL step)
{
	match_trace qq(surface_name_or_position, from, to, step);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

}; // namespace surfit;

