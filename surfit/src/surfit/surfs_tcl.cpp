
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

namespace surfit {

bool surface(const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;
	
	f_surf * f = new f_surf(srf);
	functionals_push_back(f);
	return true;
};

bool surface_add(REAL weight, const char * pos) {
	
	functional * f = get_modifiable_functional();
	if (f == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	f_surf * srf2 = new f_surf(srf);
	f->add_functional(srf2, weight);
	return true;
};

bool surface_leq(const char * pos, REAL mult) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;
	f_surf_ineq * f = new f_surf_ineq(srf, true, mult);
	functionals_push_back(f);
	return true;
};

bool surface_geq(const char * pos, REAL mult) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;
	f_surf_ineq * f = new f_surf_ineq(srf, false, mult);
	functionals_push_back(f);
	return true;
};

bool trend(REAL D1, REAL D2, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;
	
	f_trend * f = new f_trend(D1, D2, srf);
	functionals_push_back(f);
	return true;
};

bool trend_add(REAL weight, REAL D1, REAL D2, const char * pos) {
	
	functional * f = get_modifiable_functional();
	if (f == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	f_trend * srf2 = new f_trend(D1, D2, srf);
	f->add_functional(srf2, weight);
	return true;
};

bool mask(const char * Value, const char * pos) {
	
	REAL value = undef_value;
	if (strcmp(Value,"undef") != 0) {
		value = atof(Value);
	}

	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (msk == NULL)
		return false;
	
	f_mask * f = new f_mask(msk, value);
	functionals_push_back(f);
	return true;
};

bool mask_add(REAL value, REAL weight, const char * pos) {
	functional * mf = get_modifiable_functional();
	if (mf == NULL)
		return false;

	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (msk == NULL)
		return false;

	f_mask * f = new f_mask(msk, value);
	mf->add_functional(f, weight);
	return true;
};

bool mask_leq(REAL value, const char * mask_pos, REAL mult) {
	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_mask_ineq * f = new f_mask_ineq(value, mask, true, mult);
	functionals_push_back(f);
	return true;
};

bool mask_geq(REAL value, const char * mask_pos, REAL mult) {
	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_mask_ineq * f = new f_mask_ineq(value, mask, false, mult);
	functionals_push_back(f);
	return true;
};

bool mask_surf(const char * surf_pos, const char * mask_pos) {

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_mask_surf * f = new f_mask_surf(surf, mask);
	functionals_push_back(f);
	return true;
};

bool mask_surf_add(const char * surf_pos, REAL weight, const char * mask_pos) {

	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_mask_surf * f = new f_mask_surf(surf, mask);
	srf->add_functional(f, weight);
	return true;
};

bool mask_surf_leq(const char * surf_pos, const char * mask_pos, REAL mult) {

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_mask_surf_ineq * f = new f_mask_surf_ineq(surf, mask, true, mult);
	functionals_push_back(f);
	return true;
};

bool mask_surf_geq(const char * surf_pos, const char * mask_pos, REAL mult) {

	d_surf * surf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (surf == NULL)
		return false;

	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_mask_surf_ineq * f = new f_mask_surf_ineq(surf, mask, false, mult);
	functionals_push_back(f);
	return true;
};

bool mask_mean(REAL mean, const char * pos, REAL mult) {
	d_mask * mask = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_mask_mean * f = new f_mask_mean(mean, mask, mult);
	functionals_push_back(f);
	return true;
};

bool mask_wmean(REAL mean, const char * mask_pos, const char * surf_pos, REAL mult) {
	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	f_mask_wmean * f = new f_mask_wmean(mean, srf, mask, mult);
	functionals_push_back(f);
	return true;
};

bool mask_completer(const char * mask_pos, REAL D1, REAL D2, REAL alpha, REAL w) {
	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_completer * f = new f_completer(D1, D2, alpha, w);
	f->set_mask(mask);
	functionals_push_back(f);
	return true;
};

bool mask_completer_add(REAL weight, const char * mask_pos, REAL D1, REAL D2, REAL alpha, REAL w) {

	functional * srf = get_modifiable_functional();
	if (srf == NULL)
		return false;

	d_mask * mask = get_element<d_mask>(mask_pos, surfit_masks->begin(), surfit_masks->end());
	if (mask == NULL)
		return false;

	f_completer * f = new f_completer(D1, D2, alpha, w);
	f->set_mask(mask);
	srf->add_functional(f, weight);
	return true;
};

}; // namespace surfit;

