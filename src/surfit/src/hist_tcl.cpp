
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
#include "findfile.h"

#include "hist.h"
#include "hist_tcl.h"
#include "hist_internal.h"
#include "variables_internal.h"
#include "free_elements.h"
#include "surf.h"
#include "points.h"
#include "boolvec.h"
#include "strvec.h"
#include "intvec.h"

#include <math.h>
#include <float.h>
#include <algorithm>

namespace surfit {

struct match_hist_setName
{
	match_hist_setName(const char * inew_name, const char * ipos) : new_name(inew_name), pos(ipos), res(NULL) {};
	void operator()(d_hist * hist)
	{
		if ( StringMatch(pos, hist->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			hist->setName(new_name);
			res->push_back(true);
		}
	}
	const char * new_name;
	const char * pos;
	boolvec * res;
};

boolvec * hist_setName(const char * new_name, const char * pos) 
{
	match_hist_setName qq(new_name, pos);
	qq = std::for_each(surfit_hists->begin(), surfit_hists->end(), qq);
	return qq.res;
};

struct match_hist_getName
{
	match_hist_getName(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_hist * hist)
	{
		if ( StringMatch(pos, hist->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( hist->getName() );
		}
	}
	const char * new_name;
	const char * pos;
	strvec * res;
};

strvec * hist_getName(const char * pos) 
{
	match_hist_getName qq(pos);
	qq = std::for_each(surfit_hists->begin(), surfit_hists->end(), qq);
	return qq.res;
};

const char * hist_getNameAt(int pos)
{
	if ((size_t)pos > surfit_hists->size())
		return NULL;
	return (*surfit_hists)[pos]->getName();
};

void hist_del(const char * pos) 
{
	if (surfit_hists->size() == 0)
		return;
	size_t i;
	for (i = surfit_hists->size()-1; i >= 0; i--)
	{
		d_hist * hist = (*surfit_hists)[i];
		if ( StringMatch(pos, hist->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing hist \"%s\" from memory", hist->getName());
			hist->release();
			surfit_hists->erase(surfit_hists->begin()+i);
		}
		if (i == 0)
			break;
	}
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

struct match_hist_from_surf
{
	match_hist_from_surf(const char * isurf_pos, size_t iintervs, REAL ifrom, REAL ito, const char * ihistname) 
		: surf_pos(isurf_pos), intervs(iintervs), histname(ihistname), from(ifrom), to(ito), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			d_hist * hst = _hist_from_surf(surf, intervs, from, to);
			if (hst == NULL)
			{
				res->push_back(false);
				return;
			}
			hst->setName(histname?histname:surf->getName());
			surfit_hists->push_back(hst);
			res->push_back(true);
		}
	}
	const char * surf_pos;
	size_t intervs;
	const char * histname;
	REAL from;
	REAL to;
	boolvec * res;
};

boolvec * hist_from_surf(const char * surf_pos, size_t intervs, REAL from, REAL to, const char * histname) 
{
	match_hist_from_surf qq(surf_pos, intervs, from, to, histname);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct match_hist_from_pnts
{
	match_hist_from_pnts(const char * ipnts_pos, size_t iintervs, REAL ifrom, REAL ito, const char * ihistname) 
		: pnts_pos(ipnts_pos), intervs(iintervs), histname(ihistname), from(ifrom), to(ito), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pnts_pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			d_hist * hst = _hist_from_points(pnts, intervs, from, to);
			if (hst == NULL)
			{
				res->push_back(false);
				return;
			}
			hst->setName(histname?histname:pnts->getName());
			surfit_hists->push_back(hst);
			res->push_back(true);
		}
	}
	const char * pnts_pos;
	size_t intervs;
	const char * histname;
	REAL from;
	REAL to;
	boolvec * res;
};

boolvec * hist_from_pnts(const char * pnts_pos, size_t intervs, REAL from, REAL to, const char * histname) 
{
	match_hist_from_pnts qq(pnts_pos, intervs, from, to, histname);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_surf_adj_hist2
{
	match_surf_adj_hist2(d_surf * isurf, const char * ihist_pos) : surf(isurf), hist_pos(ihist_pos), res(NULL) {};
	void operator()(d_hist * hist)
	{
		if ( StringMatch(hist_pos, hist->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _surf_adj_hist(surf, hist) );
		}
	}
	d_surf * surf;
	const char * hist_pos;
	boolvec * res;
};

struct match_surf_adj_hist
{
	match_surf_adj_hist(const char * isurf_pos, const char * ihist_pos) : surf_pos(isurf_pos), hist_pos(ihist_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			match_surf_adj_hist2 qq(surf, hist_pos);
			qq = std::for_each(surfit_hists->begin(), surfit_hists->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * surf_pos;
	const char * hist_pos;
	boolvec * res;
};

boolvec * surf_adj_hist(const char * surf_pos, const char * hist_pos)
{
	match_surf_adj_hist qq(surf_pos, hist_pos);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

boolvec * hist_read(const char * filename, REAL minz, REAL maxz, const char * histname, 
	       int col1, const char * delimiter, int skip_lines, int grow_by)
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_hist * hist = _hist_read(fname, minz, maxz, histname, col1, delimiter, skip_lines, grow_by);
		if (hist) {
			surfit_hists->push_back(hist);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();
	};

	find_close();
	return res;
};

struct match_hist_write
{
	match_hist_write(const char * ifilename, const char * ipos, bool ithree_columns) 
		: filename(ifilename), pos(ipos), three_columns(ithree_columns), res(NULL) {};
	void operator()(d_hist * hist)
	{
		if ( StringMatch(pos, hist->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _hist_write(hist, filename, three_columns) );
		}
	}
	const char * pos;
	const char * filename;
	bool three_columns;
	boolvec * res;
};

boolvec * hist_write(const char * filename, const char * pos, bool three_columns)
{
	match_hist_write qq(filename, pos, three_columns);
	qq = std::for_each(surfit_hists->begin(), surfit_hists->end(), qq);
	return qq.res;
};

}; // namespace surfit;

