
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

#include "datafile.h"
#include "fileio.h"

#include "dem.h"
#include "dem_internal.h"
#include "dem_tcl.h"
#include "points.h"
#include "pnts_internal.h"
#include "pnts_tcl.h"
#include "mask_tcl.h"
#include "func_tcl.h"
#include "grid.h"
#include "grid_internal.h"
#include "grid_line.h"
#include "variables_internal.h"
#include "free_elements.h"
#include "func.h"

#include "grid_user.h"

#include <float.h>

namespace surfit {

bool dem_load(const char * filename, const char * demname) {
	d_dem * d = _dem_load(filename, demname);
	if (d) {
		globe_dems->push_back(d);
		return true;
	}
	return false;
};

bool dem_save(const char * filename, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	return _dem_save(d, filename);
};

bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename) {
	d_dem * d = _dem_load_dtm(hdr_filename, bin_filename);
	if (d && name) {
		d->setName(name);
		globe_dems->push_back(d);
		return true;
	}
	return false;
};

bool dem_load_hgt_zip(const char * hgt_zip_filename, const char * dem_name) {
	d_dem * d = _dem_load_hgt_zip(hgt_zip_filename);
	if (d) {
		if (dem_name)
			d->setName(dem_name);
		globe_dems->push_back(d);
		return true;
	}
	return false;
};

bool dem_load_hgt(const char * hgt_filename, const char * dem_name) {
	d_dem * d = _dem_load_hgt(hgt_filename);
	if (d) {
		if (dem_name)
			d->setName(dem_name);
		globe_dems->push_back(d);
		return true;
	}
	return false;
};

bool dem_load_globe(const char * filename, const char * dem_name) {
	d_dem * d = _dem_load_globe(filename);
	if (d) {
		if (dem_name)
			d->setName(dem_name);
		globe_dems->push_back(d);
		return true;
	}
	return false;
};

bool dem_save_dtm(const char * filename, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	return _dem_save_dtm(d, filename);
};

bool dem_resid(const char * filename, const char * dem_pos, const char * pnts_pos) {
	d_dem * d = get_element<d_dem>(dem_pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;

	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (!pnts)
		return false;
	return _dem_resid(d, pnts, filename);
};

REAL dem_minz(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return FLT_MAX;
	REAL minZ, maxZ;
	d->getMinMaxZ(minZ, maxZ);
	return minZ;
};


REAL dem_maxz(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return FLT_MAX;
	REAL minZ, maxZ;
	d->getMinMaxZ(minZ, maxZ);
	return maxZ;
};

bool dem_save_grd(const char * filename, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	return _dem_save_grd(d, filename);
};

bool dem_load_grd(const char * filename, const char * demname) {
	d_dem * d = _dem_load_grd(filename, demname);
	if (d) {
		d->setName(demname);
		globe_dems->push_back(d);
		return true;
	}
	return false;
};

bool dem_save_xyz(const char * filename, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	return _dem_save_xyz(d, filename);
};

int dem_getCountX(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return 0;
	return d->getCountX();
};

int dem_getCountY(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return 0;
	return d->getCountY();
};

REAL dem_getStepX(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return FLT_MAX;
	return d->getStepX();
};

REAL dem_getStepY(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return FLT_MAX;
	return d->getStepY();
};

REAL dem_getValue(REAL x, REAL y, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return FLT_MAX;
	return d->getValue(x,y);
};

bool dem_plus(const char * pos1, const char * pos2) {

	d_dem * dem1 = get_element<d_dem>(pos1, globe_dems->begin(), globe_dems->end());
	if (!dem1)
		return false;
	d_dem * dem2 = get_element<d_dem>(pos2, globe_dems->begin(), globe_dems->end());
	if (!dem2)
		return false;

	if (!dem1->compare_grid(dem2))	{
		writelog(LOG_ERROR,"dem_plus : different grids");
		return false;
	}

	dem1->plus(dem2);

	return true;
};

bool dem_minus(const char * pos1, const char * pos2) {
	
	d_dem * dem1 = get_element<d_dem>(pos1, globe_dems->begin(), globe_dems->end());
	if (!dem1)
		return false;
	d_dem * dem2 = get_element<d_dem>(pos2, globe_dems->begin(), globe_dems->end());
	if (!dem2)
		return false;

	if (!dem1->compare_grid(dem2))	{
		writelog(LOG_ERROR,"dem_plus : different grids");
		return false;
	}

	dem1->minus(dem2);

	return true;
};

bool dem_minus_undef(const char * pos1, const char * pos2) {
	
	d_dem * dem1 = get_element<d_dem>(pos1, globe_dems->begin(), globe_dems->end());
	if (!dem1)
		return false;
	d_dem * dem2 = get_element<d_dem>(pos2, globe_dems->begin(), globe_dems->end());
	if (!dem2)
		return false;

	if (!dem1->compare_grid(dem2))	{
		writelog(LOG_ERROR,"dem_plus : different grids");
		return false;
	}

	dem1->minus_undef(dem2);

	return true;
};


bool dem_mult(const char * pos1, const char * pos2) {
	
	d_dem * dem1 = get_element<d_dem>(pos1, globe_dems->begin(), globe_dems->end());
	if (!dem1)
		return false;
	d_dem * dem2 = get_element<d_dem>(pos2, globe_dems->begin(), globe_dems->end());
	if (!dem2)
		return false;

	if (!dem1->compare_grid(dem2))	{
		writelog(LOG_ERROR,"dem_plus : different grids");
		return false;
	}

	dem1->mult(dem2);

	return true;
};

bool dem_div(const char * pos1, const char * pos2) {
	
	d_dem * dem1 = get_element<d_dem>(pos1, globe_dems->begin(), globe_dems->end());
	if (!dem1)
		return false;
	d_dem * dem2 = get_element<d_dem>(pos2, globe_dems->begin(), globe_dems->end());
	if (!dem2)
		return false;

	if (!dem1->compare_grid(dem2))	{
		writelog(LOG_ERROR,"dem_plus : different grids");
		return false;
	}

	dem1->div(dem2);

	return true;
};

bool dem_set(const char * pos1, const char * pos2) {
	
	d_dem * dem1 = get_element<d_dem>(pos1, globe_dems->begin(), globe_dems->end());
	if (!dem1)
		return false;
	d_dem * dem2 = get_element<d_dem>(pos2, globe_dems->begin(), globe_dems->end());
	if (!dem2)
		return false;

	if (!dem1->compare_grid(dem2))	{
		writelog(LOG_ERROR,"dem_plus : different grids");
		return false;
	}

	dem1->set(dem2);

	return true;
};

bool dem_plus_real(REAL val, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	d->plus((short int)val);
	return true;
};

bool dem_minus_real(REAL val, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	d->minus((short int)val);
	return true;
};

bool dem_mult_real(REAL val, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	d->mult((short int)val);
	return true;
};

bool dem_div_real(REAL val, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	d->div((short int)val);
	return true;
};

bool dem_set_real(REAL val, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	d->set((short int)val);
	return true;
};

bool dem_undef(REAL new_undef_value, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	d->undef_value = (short int)new_undef_value;
	return true;
};

REAL dem_D1(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return FLT_MAX;
	return _dem_D1(d);
};

REAL dem_D2(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return FLT_MAX;
	return _dem_D2(d);
};

bool dem_project(const char * pos) {

	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	
	if (!_grid_check())
		return false;

	if (!(d->grd->operator == (surfit_grid))) {
		d_dem * res_dem2 = _dem_project(d, surfit_grid);
		if (res_dem2) {
			globe_dems->push_back(res_dem2);
			return true;
		}
		return false;
	}
	return true;
};

bool dem_gradient(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;

	d_dem * res = _dem_gradient(d);
	if (res) {
		globe_dems->push_back(res);
		return true;
	}
	return false;
};

bool dem_to_points(const char * pos, const char * new_name) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;

	writelog(LOG_MESSAGE,"converting dem to points");
	
	d_points * pnts = _dem_to_points(d);
	if (!pnts)
		return false;

	if (new_name)
		pnts->setName(new_name);
	else
		pnts->setName(d->getName());

	surfit_pnts_add(pnts);
	
	return true;
	
};

bool dem_to_func(const char * pos, const char * new_name)
{
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;

	d_func * fnc = _dem_to_func(d);
	if (!fnc)
		return false;

	if (new_name)
		fnc->setName(new_name);
	else
		fnc->setName(d->getName());

	surfit_func_add(fnc);
	return true;
};

bool dem_to_mask(short true_from, short true_to, const char * pos)
{
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;

	d_mask * msk = _dem_to_mask(d, true_from, true_to);
	if (!msk)
		return false;

	surfit_mask_add(msk);
	return true;
};

bool dem_setName(const char * new_name, const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return false;
	
	d->setName(new_name);
	return true;
};

const char * dem_getName(const char * pos) {
	d_dem * d = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!d) 
		return NULL;
	return d->getName();
};

bool dem_delall() {

	if (globe_dems->size() == 0) {
		return false;
	}
	
	release_elements(globe_dems->begin(), globe_dems->end());
	globe_dems->resize(0);

	return true;
};

bool dem_del(const char * pos) {
	std::vector<d_dem *>::iterator d = get_iterator<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (d == globe_dems->end())
		return false;
	if (*d)
		(*d)->release();
	globe_dems->erase(d);
	return true;
};

int dem_size() {
	return globe_dems->size();
};

void dems_info() {
	if (globe_dems->size() > 0) {
		unsigned int dem_cnt;
		for (dem_cnt = 0; dem_cnt < globe_dems->size(); dem_cnt++) {
			d_dem * a_fnc = *(globe_dems->begin()+dem_cnt);
			if (a_fnc) {
				_dem_info(a_fnc);
			}
		}
	}
};

//
//
// wavelets section
//
//
bool dem_decomp(const char * pos) {
	d_dem * fnc = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!fnc)
		return false;
	return _dem_decomp(fnc);
};

bool dem_auto_decomp(REAL eps, const char * pos) {
	d_dem * fnc = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!fnc)
		return false;
	return _dem_auto_decomp(fnc,eps);
};

bool dem_recons(const char * pos) {
	d_dem * fnc = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!fnc)
		return false;
	return _dem_recons(fnc);
};

bool dem_full_recons(const char * pos) {
	d_dem * fnc = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!fnc)
		return false;
	return _dem_full_recons(fnc);
};

int dem_get_details_level(const char * pos) {
	d_dem * fnc = get_element<d_dem>(pos, globe_dems->begin(), globe_dems->end());
	if (!fnc)
		return -1;
	return fnc->coeffs_store->size();
};

}; // namespace surfit;

