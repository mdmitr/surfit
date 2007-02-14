
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

bool hist_from_surf(const char * surf_pos, size_t intervs, const char * histname) {

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	writelog(LOG_MESSAGE,"calculating histogram from surface \"%s\"",
		srf->getName()?srf->getName():"noname");

	REAL minz, maxz;
	srf->getMinMaxZ(minz, maxz);
	maxz += (maxz-minz)*1e-3;
	
	vec * Z = create_vec(intervs);

	d_hist * hst = create_hist(minz, maxz, Z, histname?histname:srf->getName());
	
	REAL step = hst->get_step();

	size_t srf_size = 0;

	size_t i;
	for (i = 0; i < srf->coeff->size(); i++) {
		REAL z = (*(srf->coeff))(i);
		if (z == srf->undef_value)
			continue;
		srf_size += 1;
		size_t pos = (*hst)(z);
		if ( (pos >= intervs) || (pos == UINT_MAX) ) {
			bool stop = true;
		}
		(*Z)(pos) += 1;
	}

	for (i = 0; i < intervs; i++) 
		(*Z)(i) /= (REAL)(srf_size);
	
	surfit_hists->push_back(hst);

	return true;
};

bool surf_histeq(const char * surf_pos, const char * hist_pos)
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	d_hist * hist = get_element<d_hist>(hist_pos, surfit_hists->begin(), surfit_hists->end());
	if (hist == NULL)
		return false;

	return _surf_histeq(srf, hist);
};

bool hist_read(const char * filename, REAL minz, REAL maxz, const char * histname, 
	       int col1, const char * delimiter, int skip_lines, int grow_by)
{
	d_hist * hist = _hist_read(filename, minz, maxz, histname, col1, delimiter, skip_lines, grow_by);
	if (hist) {
		surfit_hists->push_back(hist);
		return true;
	}
	return false;
};

bool hist_write(const char * filename, const char * pos)
{
	d_hist * hist = get_element<d_hist>(pos, surfit_hists->begin(), surfit_hists->end());
	if (hist == NULL)
		return false;

	return _hist_write(hist, filename);
};

}; // namespace surfit;

