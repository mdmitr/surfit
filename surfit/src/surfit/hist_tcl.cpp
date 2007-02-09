
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

#include "datafile.h"
#include "fileio.h"
#include "sort_alg.h"
#include "vec.h"
#include "stepFunc.h"

#include "hist.h"
#include "hist_tcl.h"
#include "hist_internal.h"
#include "variables_internal.h"
#include "free_elements.h"
#include "surf.h"

#include <math.h>
#include <float.h>

namespace surfit {

bool hist_setName(const char * new_name, const char * pos) {
	d_hist * hst = get_element<d_hist>(pos, surfit_hists->begin(), surfit_hists->end());
	if (hst == NULL)
		return false;
	hst->setName(new_name);
	return true;
};

const char * hist_getName(const char * pos) {
	d_hist * hst = get_element<d_hist>(pos, surfit_hists->begin(), surfit_hists->end());
	if (hst == NULL)
		return false;
	return hst->getName();
};

bool hist_delall() {
	if (surfit_hists->size() == 0) {
		//writelog(SURFIT_WARNING,"hists_delall : empty surfit_hists");
		return false;
	}

	release_elements(surfit_hists->begin(), surfit_hists->end());
	surfit_hists->resize(0);
	return true;
};

bool hist_del(const char * pos) {
	std::vector<d_hist *>::iterator hst = get_iterator<d_hist>(pos, surfit_hists->begin(), surfit_hists->end());
	if (hst == surfit_hists->end())
		return false;
	if (*hst)
		(*hst)->release();
	surfit_hists->erase(hst);
	return true;
};

int hist_size() {
	return surfit_hists->size();
};

void hists_info() {
	size_t hists_counter;
	for (hists_counter = 0; hists_counter < surfit_hists->size(); hists_counter++) {
		d_hist * a_hist = *(surfit_hists->begin()+hists_counter);
		_hist_info(a_hist);
	}
};

bool hist_from_surf(const char * histname, const char * surf_pos, size_t intervs) {
	
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	REAL minz, maxz;
	srf->getMinMaxZ(minz, maxz);
	maxz += (maxz-minz)*1e-3;
	REAL step = stepFunc(minz, maxz, intervs);
	minz = floor(minz/step)*step;
	maxz = floor(maxz/step+1)*step;
	intervs++;

	vec * Z = create_vec(intervs);
	
	size_t srf_size = 0;

	size_t i;
	for (i = 0; i < srf->coeff->size(); i++) {
		REAL z = (*(srf->coeff))(i);
		if (z == srf->undef_value)
			continue;
		srf_size += 1;
		int pos = (int)floor((z-minz)/step + 0.5);
		(*Z)(pos) += 1;
	}

	for (i = 0; i < intervs; i++) 
		(*Z)(i) /= (REAL)(srf_size);

	d_hist * hst = create_hist(minz, maxz, step, Z, histname);
	surfit_hists->push_back(hst);

	return true;
};

bool surf_histeq(const char * surf_pos)
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	return _surf_histeq(srf);
};

}; // namespace surfit;

