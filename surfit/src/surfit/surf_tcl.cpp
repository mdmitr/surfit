
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

#include "grid_user.h"

#include <float.h>

namespace surfit {

bool surf_load(const char * filename, const char * surfname) {
	d_surf * srf = _surf_load(filename, surfname);
	if (srf != NULL) {
		surfit_surfs->push_back(srf);
		return true;
	}
	return false;
};

bool surf_save(const char * filename, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;

	return _surf_save(srf, filename);
};

bool surf_resid(const char * filename, const char * surf_pos, const char * pnts_pos) {
	
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (!pnts)
		return false;
	
	return _surf_resid(srf, pnts, filename);
};

REAL surf_minz(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	
	REAL minZ, maxZ;
	srf->getMinMaxZ(minZ, maxZ);
	return minZ;
};

REAL surf_area_minz(const char * area_pos, const char * surf_pos) {
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
	return minZ;
};

REAL surf_maxz(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	REAL minZ, maxZ;
	srf->getMinMaxZ(minZ, maxZ);
	return maxZ;
};

REAL surf_area_maxz(const char * area_pos, const char * surf_pos) {
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

REAL surf_mean(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->mean();
};

REAL surf_wmean(const char * wsurf_pos, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;

	d_surf * srfw = get_element<d_surf>(wsurf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srfw)
		return FLT_MAX;

	return srf->wmean(srfw);
};

REAL surf_std(REAL mean, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->std(mean);
};

REAL surf_sum(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->sum();
};

bool surf_to_pnts(const char * surf_pos) {
	
	writelog(LOG_MESSAGE,"converting surf to points");
	
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_points * pnts = _surf_to_pnts(srf);

	if (!pnts)
		return false;

	surfit_pnts->push_back(pnts);
	
	return true;
	
}

int surf_getCountX(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return 0;
	return srf->getCountX();
};

int surf_getCountY(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return 0;
	return srf->getCountY();
};

REAL surf_getStepX(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getStepX();
};

REAL surf_getStepY(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getStepY();
};

REAL surf_getValue(REAL x, REAL y, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getValue(x,y);
};

REAL surf_getValueIJ(int i, int j, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return FLT_MAX;
	return srf->getValueIJ(i,j);
};

bool surf_plus(const char * pos1, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_plus : different grid");
		return false;
	}

	srf1->plus(srf2);

	return true;
};

bool surf_plus_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_plus : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, srf1->grd);
	srf1->plus_mask(srf2, mask);
	if (mask)
		mask->release();

	return true;
};

bool surf_minus(const char * pos1, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_minus : different grid");
		return false;
	}

	srf1->minus(srf2);

	return true;
};

bool surf_minus_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_minus : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, srf1->grd);
	srf1->minus_mask(srf2, mask);
	if (mask)
		mask->release();

	return true;
};

bool surf_mult(const char * pos1, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_mult : different grid");
		return false;
	}

	srf1->mult(srf2);

	return true;
};

bool surf_mult_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_mult : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, srf1->grd);
	srf1->mult_mask(srf2, mask);
	if (mask)
		mask->release();

	return true;
};

bool surf_div(const char * pos1, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_div : different grid");
		return false;
	}

	srf1->div(srf2);

	return true;
};

bool surf_div_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_div : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, srf1->grd);
	srf1->div_mask(srf2, mask);
	if (mask)
		mask->release();

	return true;
};

bool surf_set(const char * pos1, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_set : different grid");
		return false;
	}

	srf1->set(srf2);

	return true;
};

bool surf_set_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_surf * srf1 = get_element<d_surf>(pos1, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf1)
		return false;

	d_surf * srf2 = get_element<d_surf>(pos2, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!srf1->compare_grid(srf2))	{
		writelog(LOG_ERROR,"surf_set : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, srf1->grd);
	srf1->set_mask(srf2, mask);
	if (mask)
		mask->release();

	return true;
};

bool surf_plus_value(REAL val, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	srf->plus(val);
	return true;
};

bool surf_plus_value_area(REAL val, const char * surf_pos, const char * area_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->plus_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_minus_value(REAL val, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	srf->minus(val);
	return true;
};

bool surf_minus_value_area(REAL val, const char * area_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->minus_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_mult_value(REAL val, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	srf->mult(val);
	return true;
};

bool surf_mult_value_area(REAL val, const char * area_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->mult_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_div_value(REAL val, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	srf->div(val);
	return true;
};

bool surf_div_value_area(REAL val, const char * area_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return false;

	srf->div_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool surf_set_value(REAL val, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	srf->set(val);
	return true;
};

bool surf_set_value_area(const char * Value, const char * area_pos, const char * surf_pos) {
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

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

	/*
	std::vector<d_surf *>::iterator psurf = get_iterator<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (*psurf)
		(*psurf)->release();
	surfit_surfs->erase(psurf);
	*/

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

}; // namespace surfit;

