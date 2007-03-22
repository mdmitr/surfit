
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

#include "fileio.h"
#include "datafile.h"
#include "vec.h"
#include "read_txt.h"
#include "sstuff.h"
#include "bitvec.h"

#include "hist.h"
#include "hist_internal.h"
#include "surf.h"
#include "points.h"

#include <float.h>
#include <algorithm>
#include <math.h>

namespace surfit {

void _hist_info(const d_hist * histline) {
	if (!histline) {
		writelog(LOG_WARNING, "_hist_info : NULL pointer given");
		return;
	}
	writelog(LOG_MESSAGE,"hist (%s)",histline->getName());
};

void _add_surfit_hists(d_hist * hst) {
	if (!hst)
		return;
	surfit_hists->push_back(hst);
};

REAL get_eq_value(const vec * T, const vec * Z, REAL val,
		  REAL surf_minz, REAL surf_maxz,
		  REAL dest_minz, REAL dest_maxz)
{
	val = (val - surf_minz)/(surf_maxz-surf_minz);

	size_t T_size = T->size();
	
	REAL pos = (T_size-1)*val;
	size_t pos2 = size_t(floor(pos + 0.5));
	REAL diff = pos-pos2;
	
	size_t pos1 = diff < 0?pos2 - 1:pos2 + 1;
	if (diff == 0)
		pos1 = pos2;
	
	REAL s;
	
	if (diff < 0)
		s = (*T)(pos2)*(diff+1) + (*T)(pos1)*-diff;
	else
		s = (*T)(pos1)*diff + (*T)(pos2)*(1-diff);

	REAL s1 = (*T)(MIN(pos1,pos2));
	REAL s2 = (*T)(MAX(pos1,pos2));
	
	if (Z == NULL) {
		val = val * (surf_maxz - surf_minz) + surf_minz;
		return val;
	}
	
	size_t Z_size = Z->size();

	vec::const_iterator it = std::lower_bound(Z->const_begin(), Z->const_end(), s);
	
	pos2 = MIN(Z_size-1,(size_t)(it-Z->const_begin()));
	
	if (pos2 == 0)
		pos1 = pos2;
	else
		pos1 = pos2 - 1;
	
	s1 = (*Z)(pos1);
	s2 = (*Z)(pos2);
	
	REAL perc1;
	if (s1 == s2)
		perc1 = 0;
	else
		perc1 = MAX(0,MIN(1,(s-s1)/(s2-s1)));
	REAL perc2 = 1-perc1;
	
	pos = pos2*perc1 + pos1*perc2;
	
	val = dest_minz + (dest_maxz-dest_minz)*pos/REAL(Z_size-1);

	return val;
};

bool _surf_histeq(d_surf * srf, const d_hist * ihist)
{

	d_hist * hist = NULL;
	if (ihist)
		hist = _hist_from_surf(srf, ihist->size());
	else 
		hist = _hist_from_surf(srf, 100);
	hist->normalize();

	size_t i;
	REAL surf_minz, surf_maxz;
	size_t surf_size = srf->getCountX()*srf->getCountY();
	srf->getMinMaxZ(surf_minz, surf_maxz);

	vec * T = hist->get_cumulative_hist();
	
	// transfort to equal histogram
	if (ihist == NULL) 
	{
		for (i = 0; i < surf_size; i++) {
			REAL val = srf->getValue(i);
			if (val == srf->undef_value)
				continue;

			val = get_eq_value(T, NULL, val,
					   surf_minz, surf_maxz,
					   FLT_MAX, FLT_MAX);
			
			srf->setValue(i, val);
		}
		T->release();
		hist->release();
		return true;
	}

	d_hist * dest_hist = create_hist(ihist);
	dest_hist->normalize();
	
	vec * Z = dest_hist->get_cumulative_hist();

	// transform to destination histogram
	{
		for (i = 0; i < surf_size; i++) {
			REAL val = srf->getValue(i);
			if (val == srf->undef_value)
				continue;
			
			val = get_eq_value(T, Z, val,
					   surf_minz, surf_maxz,
					   dest_hist->from(), dest_hist->to());
			
			srf->setValue(i, val);
		}
	}
	
	Z->release();
	dest_hist->release();
	hist->release();
	T->release();
	return true;
};

bool _hist_write(const d_hist * hist, const char * filename, bool three_columns) {
	if (!hist) {
		writelog(LOG_WARNING, "NULL pointer to hist.");
		return false;
	};
	if (hist->size() == 0) {
		writelog(LOG_WARNING, "Empty histogram for saving!");
		return false;
	}

	writelog(LOG_MESSAGE,"writing histogram \"%s\" to file %s",
		hist->getName(), filename);

	if (three_columns) {
		vec * Z_from = create_vec(hist->size(),0,0); // don't fill
		vec * Z_to = create_vec(hist->size(),0,0); // don't fill
		size_t i;
		for (i = 0; i < hist->size(); i++) {
			(*Z_from)(i) = hist->from() + i*hist->get_step();
			(*Z_to)(i) = hist->from() + (i+1)*hist->get_step();
		}
		bool res = three_columns_write(filename,"%g\t%g\t%g\n", hist->hst, Z_from, Z_to);
		Z_from->release();
		Z_to->release();
		return res;
	} else
		return one_columns_write(filename, "%g\n", hist->hst);
};

d_hist * _hist_read(const char * filename, REAL minz, REAL maxz, const char * histname, int col1, const char * delimiter, int skip_lines, int grow_by) {

	if (histname)
		writelog(LOG_MESSAGE,"reading histogram \"%s\" from file %s", histname, filename);
	else 
		writelog(LOG_MESSAGE,"reading histogram from file %s", filename);

	vec * vcol1 = NULL;
	d_hist * res = NULL;

	if (!one_columns_read(filename, col1, 
			      skip_lines, delimiter, grow_by, vcol1))
		return NULL;
		
	res = create_hist(minz, maxz, vcol1, histname);

	if (histname == NULL) {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}
	
	return res;
};

d_hist * _hist_from_vec(const vec * data, REAL minz, REAL maxz, size_t intervs,
			REAL undef_value, const bitvec * mask)
{
	vec * Z = create_vec(intervs);

	maxz += (maxz-minz)*1e-3;

	d_hist * hst = create_hist(minz, maxz, Z);
	
	REAL step = hst->get_step();

	size_t cnt = 0;

	size_t i;
	for (i = 0; i < data->size(); i++) {
		if (mask) {
			if (mask->get(i) == true)
				continue;
		}
		REAL z = (*data)(i);
		if (z == undef_value)
			continue;
		cnt += 1;
		size_t pos = (*hst)(z);
		(*Z)(pos) += 1;
	}

	for (i = 0; i < intervs; i++) 
		(*Z)(i) /= (REAL)(cnt);

	return hst;
};

d_hist * _hist_from_extvec(const extvec * data, REAL minz, REAL maxz, size_t intervs,
			REAL undef_value, const bitvec * mask)
{
	vec * Z = create_vec(intervs);

	maxz += (maxz-minz)*1e-3;

	d_hist * hst = create_hist(minz, maxz, Z);
	
	REAL step = hst->get_step();

	size_t cnt = 0;

	size_t i;
	for (i = 0; i < data->size(); i++) {
		if (mask) {
			if (mask->get(i) == true)
				continue;
		}
		REAL z = (*data)(i);
		if (z == undef_value)
			continue;
		cnt += 1;
		size_t pos = (*hst)(z);
		(*Z)(pos) += 1;
	}

	for (i = 0; i < intervs; i++) 
		(*Z)(i) /= (REAL)(cnt);

	return hst;
};

d_hist * _hist_from_surf(const d_surf * srf, size_t intervs, REAL from, REAL to)
{
	writelog(LOG_MESSAGE,"calculating histogram from surface \"%s\"",srf->getName());

	REAL minz, maxz;
	srf->getMinMaxZ(minz, maxz);

	if (from == FLT_MAX)
		from = minz;
	if (to == FLT_MAX)
		to = maxz;

	return _hist_from_extvec( srf->coeff, from, to, intervs, srf->undef_value );
};

d_hist * _hist_from_points(const d_points * pnts, size_t intervs, REAL from, REAL to)
{
	writelog(LOG_MESSAGE,"calculating histogram from points \"%s\"",pnts->getName());

	REAL minz, maxz;
	pnts->getMinMaxZ(minz, maxz);

	if (from == FLT_MAX)
		from = minz;
	if (to == FLT_MAX)
		to = maxz;

	return _hist_from_vec( pnts->Z, from, to, intervs );
};

}; // namespace surfit;

