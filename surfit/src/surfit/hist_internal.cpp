
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

#include "hist.h"
#include "hist_internal.h"
#include "surf.h"

#include <float.h>
#include <algorithm>
#include <math.h>

namespace surfit {

void _hist_info(const d_hist * histline) {
	if (!histline) {
		writelog(LOG_WARNING, "_hist_info : NULL pointer given");
		return;
	}
	if (histline->getName()) {
		writelog(LOG_MESSAGE,"hist (%s)",histline->getName());
	} else {
		writelog(LOG_MESSAGE,"hist noname");	
	}
};

void _add_surfit_hists(d_hist * hst) {
	if (!hst)
		return;
	surfit_hists->push_back(hst);
};

bool _surf_histeq(d_surf * srf, const d_hist * ihist)
{

	d_hist * hist = NULL;
	if (ihist)
		hist = _hist_from_surf(srf, ihist->size());
	else 
		hist = _hist_from_surf(srf, 100);
	hist->normalize();

	// create cummulative histogram
	vec * T = create_vec(hist->size()+1,0,0); // don't fill

	REAL surf_maxz = -FLT_MAX;
	REAL surf_minz = FLT_MAX;

	size_t surf_size = srf->getCountX()*srf->getCountY();

	size_t i;
	size_t surf_cnt = 0;
	for (i = 0; i < surf_size; i++) {
		REAL val = srf->getValue(i);
		if (val == srf->undef_value)
			continue;
		surf_cnt++;
		surf_maxz = MAX(val, surf_maxz);
		surf_minz = MIN(val, surf_minz);
	}

	REAL surf_dist = surf_maxz-surf_minz;

	REAL sum = 0;
	size_t T_size = T->size();
	(*T)(0) = 0;
	for (i = 1; i < T_size; i++) {
		sum += (*(hist))(i-1);
		(*T)(i) = sum;
	}

	// transfort to equal histogram
	if (ihist == NULL) 
	{
		for (i = 0; i < surf_size; i++) {
			REAL val = srf->getValue(i);
			if (val == srf->undef_value)
				continue;
			val = (val - surf_minz)/(surf_dist);
			REAL pos = (T_size-1)*val;
			size_t pos2 = floor(pos + 0.5);
			REAL diff = pos-pos2;

			size_t pos1 = diff < 0?pos2 - 1:pos2 + 1;
			if (diff == 0)
				pos1 = pos2;

			if (diff < 0)
				val = (*T)(pos2)*(diff+1) + (*T)(pos1)*-diff;
			else
				val = (*T)(pos1)*diff + (*T)(pos2)*(1-diff);

			val = (val * surf_dist) + surf_minz;
			srf->setValue(i, val);
		}
		T->release();
		hist->release();
		return true;
	}

	d_hist * dest_hist = create_hist(ihist);
	dest_hist->normalize();
	
	vec * Z = create_vec(dest_hist->size()+1,0,0); // don't fill
	sum = 0;
	size_t Z_size = Z->size();
	(*Z)(0) = 0;
	for (i = 1; i < Z_size; i++) {
		sum += (*(dest_hist))(i-1);
		(*Z)(i) = sum;
	}

	// transform to destination histogram
	{
		for (i = 0; i < surf_size; i++) {
			REAL val = srf->getValue(i);
			if (val == srf->undef_value)
				continue;
			val = (val - surf_minz)/(surf_dist);
			REAL pos = (T_size-1)*val;
			size_t pos2 = floor(pos + 0.5);
			REAL diff = pos-pos2;

			size_t pos1 = diff < 0?pos2 - 1:pos2 + 1;
			if (diff == 0)
				pos1 = pos2;

			REAL s;

			if (diff < 0)
				s = (*T)(pos2)*(diff+1) + (*T)(pos1)*-diff;
			else
				s = (*T)(pos1)*diff + (*T)(pos2)*(1-diff);

			vec::const_iterator it = std::lower_bound(Z->const_begin(), Z->const_end(), s);

			pos2 = it-Z->const_begin();
			if (pos2 == 0)
				pos1 = pos2;
			else
				pos1 = pos2 - 1;
			
			
			REAL s1 = (*Z)(pos1);
			REAL s2 = (*Z)(pos2);

			REAL perc1 = (s-s1)/(s2-s1);
			REAL perc2 = 1-perc1;
			
			pos = pos2*perc1 + pos1*perc2;

			val = dest_hist->from() + (dest_hist->to()-dest_hist->from())*pos/REAL(Z_size);
			if (val > 1)
				bool stop = true;

			srf->setValue(i, val);

			bool stop = true;
		}
	}
	
	Z->release();
	dest_hist->release();
	hist->release();
	T->release();
	return true;
};

bool _hist_write(const d_hist * hist, const char * filename) {
	if (!hist) {
		writelog(LOG_WARNING, "NULL pointer to hist.");
		return false;
	};
	if (hist->size() == 0) {
		writelog(LOG_WARNING, "Empty histogram for saving!");
		return false;
	}

	writelog(LOG_MESSAGE,"writing histogram \"%s\" to file %s",
		hist->getName()?hist->getName():"noname", filename);

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

d_hist * _hist_from_surf(d_surf * srf, size_t intervs)
{
	writelog(LOG_MESSAGE,"calculating histogram from surface \"%s\"",
		srf->getName()?srf->getName():"noname");

	REAL minz, maxz;
	srf->getMinMaxZ(minz, maxz);
	maxz += (maxz-minz)*1e-3;
	
	vec * Z = create_vec(intervs);

	d_hist * hst = create_hist(minz, maxz, Z);
	
	REAL step = hst->get_step();

	size_t srf_size = 0;

	size_t i;
	for (i = 0; i < srf->coeff->size(); i++) {
		REAL z = (*(srf->coeff))(i);
		if (z == srf->undef_value)
			continue;
		srf_size += 1;
		size_t pos = (*hst)(z);
		(*Z)(pos) += 1;
	}

	for (i = 0; i < intervs; i++) 
		(*Z)(i) /= (REAL)(srf_size);

	return hst;
}

}; // namespace surfit;

