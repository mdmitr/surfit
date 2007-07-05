
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
#include "variables_tcl.h"

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

bool _surf_adj_hist(d_surf * srf, const d_hist * ihist)
{
	extvec * new_coeff = _extvec_adj_hist(srf->coeff, ihist, NULL, NULL, srf->undef_value);
	if (new_coeff == NULL)
		return false;
	srf->coeff->release();
	srf->coeff = new_coeff;
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

	res->normalize();
	
	return res;
};

d_hist * _hist_from_vec(const vec * data, REAL minz, REAL maxz, size_t intervs,
			REAL undef_value, const bitvec * mask, const bitvec * mask_undef)
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
		if (mask_undef) {
			if (mask_undef->get(i) == true)
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
			   REAL undef_value, const bitvec * mask, const bitvec * mask_undef)
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
		if (mask_undef) {
			if (mask_undef->get(i) == true)
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

extvec * _extvec_adj_hist(const extvec * X, const d_hist * dest, const bitvec * mask, const bitvec * mask_undef, REAL uval)
{
	size_t intervs = dest->size();
	size_t i;

	d_hist * dhst = create_hist(dest);
	dhst->normalize();

	size_t X_size = X->size();

	//
	//  modify destination histogram with respect to solved cells
	//

	for (i = 0; i < X->size(); i++) {
		if (mask_undef) {
			if (mask_undef->get(i) == false)
				continue;
		}

		REAL val = (*X)(i);
		if (val == uval)
			continue;

		X_size--;
	}
	
	REAL elem = REAL(1)/X_size;
	REAL dest_minz = dhst->from();
	REAL dest_maxz = dhst->to();
	
	for (i = 0; i < X->size(); i++) {
		if (mask->get(i) == false)
			continue;
		
		REAL val = (*X)(i);

		if (val > dest_maxz)
			continue;
		if (val < dest_minz)
			continue;

		size_t pos = (*dhst)(val);
		
		(*dhst)[pos] = MAX(0, (*dhst)(pos)-elem);
	}

	dhst->normalize();
	vec * Z = dhst->get_cumulative_hist();

	size_t q;
	extvec * res = create_extvec(*X);

	REAL prev_err = FLT_MAX;

	for (q = 0; q < 5; q++) 
	{

		//
		// calculating minimum and maximum values if vector X with respect to mask
		//
		REAL minz = FLT_MAX, maxz = -FLT_MAX;
		for (i = 0; i < res->size(); i++) {

			if (mask->get(i))
				continue;

			if (mask_undef) {
				if (mask_undef->get(i))
					continue;
			}

			REAL val = (*res)(i);
			if (val == FLT_MAX)
				continue;
			minz = MIN(minz, val);
			maxz = MAX(maxz, val);
		}

		d_hist * hst = _hist_from_extvec(res, minz, maxz, intervs, FLT_MAX, mask, mask_undef);

		if (hst->get_step() == 0) {
			hst->release();
			goto failed_exit;
		}

		// histogram normalization
		hst->normalize();

		// calculate cumulative histogram
		vec * T = hst->get_cumulative_hist();

		extvec * new_res = create_extvec(*res);

		size_t j;
		for (j = 0; j < X->size(); j++) 
		{
			if (mask->get(j) == true)
				continue;
			if (mask_undef) {
				if (mask_undef->get(j) == true)
					continue;
			}
			REAL val = (*res)(j);
			REAL eqval = get_eq_value(T, Z, val,
						  minz, maxz,
						  dest_minz, dest_maxz);

			if (val == eqval)
				continue;

			(*new_res)(j) = eqval;
		}

		REAL max_err = -FLT_MAX;
		for (j = 0; j < res->size(); j++)
		{
			max_err = MAX(max_err, fabs((*res)(j) - (*new_res)(j)));
		}

		if ((max_err > prev_err) || (max_err < tol*100)) {
			new_res->release();
			T->release();
			hst->release();
			break;
		}

		prev_err = max_err;
		res->release();
		res = new_res;
		
		T->release();
		hst->release();
	}

	return res;

failed_exit:
	res->release();
	dhst->release();
	Z->release();
	return NULL;
};

}; // namespace surfit;

