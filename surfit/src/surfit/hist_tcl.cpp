
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
#include "points.h"

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

	writelog(LOG_MESSAGE,"removing all histograms from memory");

	if (surfit_hists == NULL)
		return false;

	if (surfit_hists->size() == 0) {
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

bool hist_from_surf(const char * surf_pos, size_t intervs, const char * histname, REAL from, REAL to) {

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	d_hist * hst = _hist_from_surf(srf, intervs, from, to);

	hst->setName(histname?histname:srf->getName());

	surfit_hists->push_back(hst);

	return true;
};

bool hist_from_pnts(const char * pnts_pos, size_t intervs, const char * histname, REAL from, REAL to) {

	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_hist * hst = _hist_from_points(pnts, intervs, from, to);

	hst->setName(histname?histname:pnts->getName());

	surfit_hists->push_back(hst);

	return true;
};

bool surf_histeq(const char * surf_pos, const char * hist_pos)
{
	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	d_hist * hist = NULL;
	if (hist_pos) {
		hist = get_element<d_hist>(hist_pos, surfit_hists->begin(), surfit_hists->end());
		if (hist == NULL)
			return false;
	}

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

bool hist_write(const char * filename, const char * pos, bool three_columns)
{
	d_hist * hist = get_element<d_hist>(pos, surfit_hists->begin(), surfit_hists->end());
	if (hist == NULL)
		return false;

	return _hist_write(hist, filename, three_columns);
};

}; // namespace surfit;

