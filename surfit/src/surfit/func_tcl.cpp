
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


#include "func.h"
#include "func_internal.h"
#include "func_tcl.h"
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

bool func_load(const char * filename, const char * funcname) {
	d_func * fnc = _func_load(filename, funcname);
	if (fnc != NULL) {
		surfit_funcs->push_back(fnc);
		return true;
	}
	return false;
};

bool func_save(const char * filename, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;

	return _func_save(fnc, filename);
};

bool func_resid(const char * filename, const char * func_pos, const char * pnts_pos) {
	
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (!pnts)
		return false;
	
	return _func_resid(fnc, pnts, filename);
};

REAL func_minz(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	
	REAL minZ, maxZ;
	fnc->getMinMaxZ(minZ, maxZ);
	return minZ;
};

REAL func_area_minz(const char * area_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return FLT_MAX;

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);

	REAL minZ, maxZ;
	fnc->getMinMaxZ_mask(minZ, maxZ, mask);

	if (mask)
		mask->release();
	return minZ;
};

REAL func_maxz(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	REAL minZ, maxZ;
	fnc->getMinMaxZ(minZ, maxZ);
	return maxZ;
};

REAL func_area_maxz(const char * area_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return FLT_MAX;

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	
	REAL minZ, maxZ;
	fnc->getMinMaxZ_mask(minZ, maxZ, mask);

	if (mask)
		mask->release();
	return maxZ;
};

REAL func_mean(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return fnc->mean();
};

REAL func_wmean(const char * wfunc_pos, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;

	d_func * fncw = get_element<d_func>(wfunc_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fncw)
		return FLT_MAX;

	return fnc->wmean(fncw);
};

REAL func_std(REAL mean, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return fnc->std(mean);
};

REAL func_sum(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return fnc->sum();
};

bool func_save_grd(const char * filename, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return _func_save_grd(fnc, filename);
};

bool func_load_grd(const char * filename, const char * funcname) {
	d_func * fnc = _func_load_grd(filename, funcname);
	if (fnc) {
		surfit_funcs->push_back(fnc);
		return true;
	}
	return false;
};

bool func_save_xyz(const char * filename, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return _func_save_xyz(fnc, filename);
};

bool func_to_pnts(const char * func_pos) {
	
	writelog(LOG_MESSAGE,"converting func to points");
	
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	d_points * pnts = _func_to_pnts(fnc);

	if (!pnts)
		return false;

	surfit_pnts->push_back(pnts);
	
	return true;
	
}

int func_getCountX(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return 0;
	return fnc->getCountX();
};

int func_getCountY(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return 0;
	return fnc->getCountY();
};

REAL func_getStepX(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return fnc->getStepX();
};

REAL func_getStepY(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return fnc->getStepY();
};

REAL func_getValue(REAL x, REAL y, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return fnc->getValue(x,y);
};

REAL func_getValueIJ(int i, int j, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return fnc->getValueIJ(i,j);
};

bool func_plus(const char * pos1, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_plus : different grid");
		return false;
	}

	fnc1->plus(fnc2);

	return true;
};

bool func_plus_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_plus : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, fnc1->grd);
	fnc1->plus_mask(fnc2, mask);
	if (mask)
		mask->release();

	return true;
};

bool func_minus(const char * pos1, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_minus : different grid");
		return false;
	}

	fnc1->minus(fnc2);

	return true;
};

bool func_minus_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_minus : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, fnc1->grd);
	fnc1->minus_mask(fnc2, mask);
	if (mask)
		mask->release();

	return true;
};

bool func_minus_undef(const char * pos1, const char * pos2) {
	
	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_minus_undef : different grid");
		return false;
	}

	fnc1->minus_undef(fnc2);

	return true;
};

bool func_minus_undef_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_minus_undef : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, fnc1->grd);
	fnc1->minus_undef_mask(fnc2, mask);
	if (mask)
		mask->release();

	return true;
};

bool func_mult(const char * pos1, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_mult : different grid");
		return false;
	}

	fnc1->mult(fnc2);

	return true;
};

bool func_mult_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_mult : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, fnc1->grd);
	fnc1->mult_mask(fnc2, mask);
	if (mask)
		mask->release();

	return true;
};

bool func_div(const char * pos1, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_div : different grid");
		return false;
	}

	fnc1->div(fnc2);

	return true;
};

bool func_div_undef(const char * pos1, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_div : different grid");
		return false;
	}

	fnc1->div_undef(fnc2);

	return true;
};

bool func_div_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_div : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, fnc1->grd);
	fnc1->div_mask(fnc2, mask);
	if (mask)
		mask->release();

	return true;
};

bool func_set(const char * pos1, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_set : different grid");
		return false;
	}

	fnc1->set(fnc2);

	return true;
};

bool func_set_area(const char * pos1, const char * area_pos, const char * pos2) {

	d_func * fnc1 = get_element<d_func>(pos1, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc1)
		return false;

	d_func * fnc2 = get_element<d_func>(pos2, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc2)
		return false;

	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	if (!fnc1->compare_grid(fnc2))	{
		writelog(LOG_ERROR,"func_set : different grid");
		return false;
	}

	bitvec * mask = nodes_in_area_mask(area, fnc1->grd);
	fnc1->set_mask(fnc2, mask);
	if (mask)
		mask->release();

	return true;
};

bool func_plus_value(REAL val, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	fnc->plus(val);
	return true;
};

bool func_plus_value_area(REAL val, const char * func_pos, const char * area_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return false;

	fnc->plus_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool func_minus_value(REAL val, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	fnc->minus(val);
	return true;
};

bool func_minus_value_area(REAL val, const char * area_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return false;

	fnc->minus_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool func_mult_value(REAL val, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	fnc->mult(val);
	return true;
};

bool func_mult_value_area(REAL val, const char * area_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return false;

	fnc->mult_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool func_div_value(REAL val, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	fnc->div(val);
	return true;
};

bool func_div_value_area(REAL val, const char * area_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return false;

	fnc->div_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool func_set_value(REAL val, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	fnc->set(val);
	return true;
};

bool func_set_value_area(const char * Value, const char * area_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return false;

	REAL val = fnc->undef_value;

	if ( strcmp("undef", Value) != 0 )
		val = atof(Value);

	fnc->set_mask(val, mask);
	if (mask)
		mask->release();
	return true;
};

bool func_to_mask(REAL true_from, REAL true_to, const char * pos)
{
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	bitvec * bcoeff = create_bitvec( fnc->coeff->size() );
	int i;
	REAL val;
	for (i = 0; i < fnc->coeff->size(); i++) {
		val = (*(fnc->coeff))(i);
		bool bval = ( (val >= true_from) && (val <= true_to) );
		if (bval)
			bcoeff->set_true(i);
		else
			bcoeff->set_false(i);
	};

	d_grid * fgrd = fnc->grd;
	d_grid * grd = new d_grid(fgrd);

	d_mask * msk = create_mask(bcoeff, grd);
	msk->setName(fnc->getName());
	surfit_masks->push_back(msk);

	/*
	std::vector<d_func *>::iterator pfunc = get_iterator<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (*pfunc)
		(*pfunc)->release();
	surfit_funcs->erase(pfunc);
	*/

	return true;
};

//
//
// wavelets section
//
//
bool func_decomp(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return _func_decomp(fnc);
};

bool func_auto_decomp(REAL eps, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return _func_auto_decomp(fnc,eps);
};

bool func_add_noise(REAL std, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return _func_add_noise(fnc, std);
};

bool func_recons(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return _func_recons(fnc);
};

bool func_full_recons(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return _func_full_recons(fnc);
};

int func_get_details_level(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return -1;
	return fnc->details_h->size();
};

bool func_undef(REAL new_undef_value, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	fnc->set_undef_value(new_undef_value);
	return true;
};

REAL func_D1(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return _func_D1(fnc);
};

REAL func_D2(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return FLT_MAX;
	return _func_D2(fnc);
};

void func_info(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return;
	_func_info(fnc);
};

bool func_project(const char * newname, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	if (!_grid_check())
		return false;

	if (!(fnc->grd->operator == (surfit_grid))) {
		d_func * res_func2 = _func_project(fnc, surfit_grid);
		if (res_func2) {
			if (newname)
				res_func2->setName(newname);
			surfit_funcs->push_back(res_func2);
			return true;
		}
		return false;
	}
	return false;
};

bool func_gradient(const char * newname, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	d_func * res = _func_gradient(fnc);
	if (res) {
		res->setName(newname);
		surfit_funcs->push_back(res);
		return true;
	}
	return false;
};

const char * func_getName(const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	return fnc->getName();
};

bool func_setName(const char * new_name, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	fnc->setName(new_name);
	return true;
};

bool func_delall() {

	if (surfit_funcs->size() == 0) {
		return false;
	}
	
	release_elements(surfit_funcs->begin(), surfit_funcs->end());
	surfit_funcs->resize(0);

	return true;
};

bool func_del(const char * pos) {
	std::vector<d_func *>::iterator fnc = get_iterator<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (fnc == surfit_funcs->end())
		return false;
	if (*fnc)
		(*fnc)->release();
	surfit_funcs->erase(fnc);
	return true;
};

int func_size() {
	return surfit_funcs->size();
};

void funcs_info() {
	if (surfit_funcs->size() > 0) {
		unsigned int func_cnt;
		for (func_cnt = 0; func_cnt < surfit_funcs->size(); func_cnt++) {
			d_func * a_fnc = *(surfit_funcs->begin()+func_cnt);
			if (a_fnc) {
				_func_info(a_fnc);
			}
		}
	}
};

void surfit_func_add(d_func * fnc) {
	surfit_funcs->push_back(fnc);
};

bool func_project_with_faults(const char * newname, const char * pos) {
	d_func * fnc = get_element<d_func>(pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;
	
	if (!_grid_check())
		return false;

	d_func * fnc2 = _func_project_with_faults(fnc, surfit_grid);
	if (fnc2) {
		if (newname)
			fnc2->setName(newname);
		surfit_funcs->push_back(fnc2);
		return true;
	}

	return false;
};

REAL func_area_mean(const char * area_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _func_mean_area(fnc, area);
};

REAL func_area_wmean(const char * area_pos, const char * wfunc_pos, const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;

	d_func * wfnc = get_element<d_func>(wfunc_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!wfnc)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _func_wmean_area(fnc, wfnc, area);
};

REAL func_sum_area(const char * area_pos,  const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _func_sum_area(fnc, area);
};

int func_cells_in_area(const char * area_pos,  const char * func_pos) {
	d_func * fnc = get_element<d_func>(func_pos, surfit_funcs->begin(), surfit_funcs->end());
	if (!fnc)
		return false;


	d_area * area = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (!area)
		return false;

	return _func_cells_in_area(fnc, area);
};

}; // namespace surfit;

