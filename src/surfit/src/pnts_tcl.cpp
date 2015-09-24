
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
#include "vec.h"
#include "rnd.h"
#include "geom_alg.h"
#include "findfile.h"

#include <math.h>
#include <algorithm>

#include "points.h"
#include "pnts_internal.h"
#include "pnts_tcl.h"
#include "surf.h"
#include "surf_internal.h"
#include "mask.h"
#include "mask_internal.h"
#include "variables_internal.h"
#include "curv_internal.h"
#include "curv.h"
#include "area.h"
#include "free_elements.h"
#include "boolvec.h"
#include "intvec.h"
#include "strvec.h"

namespace surfit {

boolvec * pnts_load(const char * filename, const char * pntsname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);
	
	while (fname != NULL) {
		d_points * pnts = _pnts_load(fname, pntsname);
		if (pnts != NULL) {
			surfit_pnts->push_back(pnts);
			res->push_back(true);
		} else
			res->push_back(false);
		fname = find_next();
	}
	find_close();
	return res;
};

struct match_add_noise
{
	match_add_noise(REAL istd, const char * ipos) : pos(ipos), std(istd), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			writelog(LOG_MESSAGE,"adding noise N(0,%g) to points \"%s\"", std, pnts->getName());	
			
			vec::iterator ptr;
			for (ptr = pnts->Z->begin(); ptr != pnts->Z->end(); ptr++) {
				*ptr += norm_rand(std);
			}
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	REAL std;
	const char * pos;
	boolvec * res;
};

boolvec * pnts_add_noise(REAL std, const char * pos) 
{
	match_add_noise qq(std, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_mean
{
	match_pnts_mean(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating mean for points \"%s\"", pnts->getName());
			res->push_back( pnts->mean() );
		}
	}
	const char * pos;
	vec * res;
};

vec * pnts_mean(const char * pos) 
{
	match_pnts_mean qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_std
{
	match_pnts_std(REAL imean, const char * ipos) : pos(ipos), mean(imean), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating std for points \"%s\"", pnts->getName());
			res->push_back( pnts->std(mean) );
		}
	}
	const char * pos;
	vec * res;
	REAL mean;
};

vec * pnts_std(REAL mean, const char * pos) 
{
	match_pnts_std qq(mean, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_save
{
	match_pnts_save(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Saving points to file %s", filename);
			res->push_back( _pnts_save(pnts, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * pnts_save(const char * filename, const char * pos) 
{
	match_pnts_save qq(filename, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_getCount
{
	match_pnts_getCount(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( pnts->size() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * pnts_getCount(const char * pos) 
{
	match_pnts_getCount qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

boolvec * pnts_read(const char * filename, const char * pntsname, int col1, int col2, int col3, int col4, const char * delimiter, int skip_lines, int grow_by) 
{
	const char * fname = find_first(filename);
	boolvec * res = create_boolvec();

	while (fname != NULL)
	{
		d_points * pnts = _pnts_read(fname, pntsname, col1, col2, col3, col4, delimiter, skip_lines, grow_by);
		if (pnts) {
			surfit_pnts->push_back(pnts);
			res->push_back(true);
		} else
			res->push_back(false);
		fname = find_next();
	}
	find_close();
	return res;
};

struct match_pnts_write
{
	match_pnts_write(const char * ifilename, const char * ipos, const char * idelimiter) : filename(ifilename), pos(ipos), delimiter(idelimiter), res(NULL), first(false) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			char buf[80];
			strcpy( buf, "%lf" );
			strcat( buf, delimiter );
			strcat( buf, "%lf" );
			strcat( buf, delimiter );
			strcat( buf, "%lf" );
			strcat( buf, delimiter );
			strcat( buf, "\n" );
			if (first == false)
				fileio_append = false;
			else
				fileio_append = true;
			res->push_back ( _pnts_write(pnts, filename, buf) );
			first = true;
		}
	}
	const char * filename;
	const char * pos;
	const char * delimiter;
	boolvec * res;
	bool first;
};

boolvec * pnts_write(const char * filename, const char * pos, const char * delimiter) 
{
	match_pnts_write qq(filename, pos, delimiter);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	fileio_append = false;
	return qq.res;
};

struct match_pfbs2
{
	match_pfbs2(REAL ieps, d_points * ipnts, const char * isurf_pos)  :  eps(ieps), pnts(ipnts), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * srf)
	{
		if ( StringMatch(surf_pos, srf->getName()) )
		{
			size_t old_size = pnts->size();
			if (old_size == 0)
				return;
			
			vec::iterator old_X_ptr = pnts->X->begin();
			vec::iterator old_Y_ptr = pnts->Y->begin();
			vec::iterator old_Z_ptr = pnts->Z->begin();
			
			vec::iterator new_X_ptr = pnts->X->begin();
			vec::iterator new_Y_ptr = pnts->Y->begin();
			vec::iterator new_Z_ptr = pnts->Z->begin();
			
			REAL z_value;
			
			for (;old_X_ptr != pnts->X->end(); old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
				z_value = srf->getValue(*old_X_ptr, *old_Y_ptr);
				if ( fabs(z_value - *old_Z_ptr) < eps ) {
					*new_X_ptr = *old_X_ptr;
					*new_Y_ptr = *old_Y_ptr;
					*new_Z_ptr = *old_Z_ptr;
					new_X_ptr++;
					new_Y_ptr++;
					new_Z_ptr++;
				}
			}
			
			size_t new_size = new_X_ptr - pnts->X->begin();
			
			pnts->X->resize(new_size);
			pnts->Y->resize(new_size);
			pnts->Z->resize(new_size);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		};
	}
	REAL eps;
	d_points * pnts;
	const char * surf_pos;
	boolvec * res;
};

struct match_pfbs
{
	match_pfbs(REAL ieps, const char * ipnts_pos, const char * isurf_pos)  :  eps(ieps), pnts_pos(ipnts_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch( pnts_pos, pnts->getName() ) )
		{
			match_pfbs2 qq(eps, pnts, surf_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	REAL eps;
	const char * pnts_pos;
	const char * surf_pos;
	boolvec * res;

};

boolvec * pnts_filter_by_surf(REAL eps, const char * pnts_pos, const char * surf_pos) 
{
	match_pfbs qq(eps, pnts_pos, surf_pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_fpfoa2
{
	match_fpfoa2(d_points * ipnts, const char * iarea_pos) : pnts(ipnts), area_pos(iarea_pos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"removing points \"%s\" outside area \"%s\"",pnts->getName(), area->getName());
			
			size_t old_size = pnts->size();
			
			vec::iterator old_X_ptr = pnts->X->begin();
			vec::iterator old_Y_ptr = pnts->Y->begin();
			vec::iterator old_Z_ptr = pnts->Z->begin();
			
			vec::iterator new_X_ptr = pnts->X->begin();
			vec::iterator new_Y_ptr = pnts->Y->begin();
			vec::iterator new_Z_ptr = pnts->Z->begin();
			
			for (;old_X_ptr != pnts->X->end(); old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
				
				bool in_reg = area->in_region(*old_X_ptr, *old_Y_ptr);
				if ( in_reg ) {
					*new_X_ptr = *old_X_ptr;
					*new_Y_ptr = *old_Y_ptr;
					*new_Z_ptr = *old_Z_ptr;
					new_X_ptr++;
					new_Y_ptr++;
					new_Z_ptr++;
				}
			}
			
			size_t new_size = new_X_ptr - pnts->X->begin();
			
			pnts->X->resize(new_size);
			pnts->Y->resize(new_size);
			pnts->Z->resize(new_size);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	d_points * pnts;
	const char * area_pos;
	boolvec * res;
};

struct match_fpfoa
{
	match_fpfoa(const char * ipnts_pos, const char * iarea_pos) : pnts_pos(ipnts_pos), area_pos(iarea_pos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pnts_pos, pnts->getName()) )
		{
			match_fpfoa2 qq(pnts, area_pos);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pnts_pos;
	const char * area_pos;
	boolvec * res;
};

boolvec * pnts_filter_out_area(const char * pnts_pos, const char * area_pos) 
{
	match_fpfoa qq(pnts_pos, area_pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_fpfia2
{
	match_fpfia2(d_points * ipnts, const char * iarea_pos) : pnts(ipnts), area_pos(iarea_pos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(area_pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"removing points \"%s\" inside area \"%s\"",pnts->getName(), area->getName());
			
			size_t old_size = pnts->size();
			
			vec::iterator old_X_ptr = pnts->X->begin();
			vec::iterator old_Y_ptr = pnts->Y->begin();
			vec::iterator old_Z_ptr = pnts->Z->begin();
			
			vec::iterator new_X_ptr = pnts->X->begin();
			vec::iterator new_Y_ptr = pnts->Y->begin();
			vec::iterator new_Z_ptr = pnts->Z->begin();
			
			for (;old_X_ptr != pnts->X->end(); old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
				
				bool in_reg = area->in_region(*old_X_ptr, *old_Y_ptr);
				if ( !in_reg ) {
					*new_X_ptr = *old_X_ptr;
					*new_Y_ptr = *old_Y_ptr;
					*new_Z_ptr = *old_Z_ptr;
					new_X_ptr++;
					new_Y_ptr++;
					new_Z_ptr++;
				}
			}
			
			size_t new_size = new_X_ptr - pnts->X->begin();
			
			pnts->X->resize(new_size);
			pnts->Y->resize(new_size);
			pnts->Z->resize(new_size);

			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	d_points * pnts;
	const char * area_pos;
	boolvec * res;
};

struct match_fpfia
{
	match_fpfia(const char * ipnts_pos, const char * iarea_pos) : pnts_pos(ipnts_pos), area_pos(iarea_pos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pnts_pos, pnts->getName()) )
		{
			match_fpfia2 qq(pnts, area_pos);
			qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pnts_pos;
	const char * area_pos;
	boolvec * res;
};

boolvec * pnts_filter_in_area(const char * pnts_pos, const char * area_pos) 
{
	match_fpfia qq(pnts_pos, area_pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_fbm2
{
	match_fbm2(d_points * ipnts, const char * idef_pos) : pnts(ipnts), def_pos(idef_pos), res(false) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(def_pos, mask->getName()) )
		{
			writelog(LOG_MESSAGE,"filtering points \"%s\" with mask \"%s\"", pnts->getName(), mask->getName());

			size_t cnt = pnts->size();
			if (cnt == 0)
				return;

			size_t i,j;
			REAL x,y;
			bool val;
			j = 0;
			vec::iterator x_ptr = pnts->X->begin();
			vec::iterator y_ptr = pnts->Y->begin();
			vec::iterator z_ptr = pnts->Z->begin();
			
			for (i = 0; i < cnt; i++) {
				x = *(x_ptr + i);
				y = *(y_ptr + i);
				val = mask->getValue(x,y);
				if (val) {
					*(x_ptr + j) = x;
					*(y_ptr + j) = y;
					*(z_ptr + j) = *(z_ptr + i);
					j++;
				}
			}
			
			pnts->X->resize(j);
			pnts->Y->resize(j);
			pnts->Z->resize(j);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(true);
		}
	}
	d_points * pnts;
	const char * def_pos;
	boolvec * res;
};

struct match_fbm
{
	match_fbm(const char * ipnts_pos, const char * idef_pos) : pnts_pos(ipnts_pos), def_pos(idef_pos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pnts_pos, pnts->getName()) )
		{
			match_fbm2 qq(pnts, def_pos);
			qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pnts_pos;
	const char * def_pos;
	boolvec * res;
};

boolvec * pnts_filter_by_mask(const char * pnts_pos, const char * def_pos) 
{
	match_fbm qq(pnts_pos, def_pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper
{
	virtual bool do_oper(d_points * pnts1, d_points * pnts2) = 0;
};

struct match_pnts_oper2
{
	match_pnts_oper2(d_points * ipnts1, const char * ipos2, pnts_oper * ioper) : oper(ioper), pnts1(ipnts1), pos2(ipos2), res(NULL) {};
	void operator()(d_points * pnts2)
	{
		if ( StringMatch(pos2, pnts2->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(pnts1, pnts2) );
		}
	}
	d_points * pnts1;
	const char * pos2;
	boolvec * res;
	pnts_oper * oper;
};

struct match_pnts_oper
{
	match_pnts_oper(const char * ipos1, const char * ipos2, pnts_oper * ioper) : oper(ioper), pos1(ipos1), pos2(ipos2), res(NULL) {};
	void operator()(d_points * pnts1)
	{
		if ( StringMatch(pos1, pnts1->getName()) )
		{
			match_pnts_oper2 qq(pnts1, pos2, oper);
			qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pos1;
	const char * pos2;
	boolvec * res;
	pnts_oper * oper;
};

struct pnts_oper_plus : public pnts_oper
{
	virtual bool do_oper(d_points * pnts1, d_points * pnts2)
	{
		return pnts1->plus(pnts2);
	}
};

boolvec * pnts_plus(const char * pos1, const char * pos2) 
{
	pnts_oper_plus oper_plus;
	match_pnts_oper qq(pos1, pos2, &oper_plus);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_minus : public pnts_oper
{
	virtual bool do_oper(d_points * pnts1, d_points * pnts2)
	{
		return pnts1->minus(pnts2);
	}
};

boolvec * pnts_minus(const char * pos1, const char * pos2) 
{
	pnts_oper_minus oper_minus;
	match_pnts_oper qq(pos1, pos2, &oper_minus);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_mult : public pnts_oper
{
	virtual bool do_oper(d_points * pnts1, d_points * pnts2)
	{
		return pnts1->mult(pnts2);
	}
};

boolvec * pnts_mult(const char * pos1, const char * pos2) 
{
	pnts_oper_mult oper_mult;
	match_pnts_oper qq(pos1, pos2, &oper_mult);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_div : public pnts_oper
{
	virtual bool do_oper(d_points * pnts1, d_points * pnts2)
	{
		return pnts1->div(pnts2);
	}
};

boolvec * pnts_div(const char * pos1, const char * pos2) 
{
	pnts_oper_div oper_div;
	match_pnts_oper qq(pos1, pos2, &oper_div);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_set : public pnts_oper
{
	virtual bool do_oper(d_points * pnts1, d_points * pnts2)
	{
		return pnts1->set(pnts2);
	}
};

boolvec * pnts_set(const char * pos1, const char * pos2) 
{
	pnts_oper_set oper_set;
	match_pnts_oper qq(pos1, pos2, &oper_set);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_real
{
	virtual bool do_oper(REAL val, d_points * pnts) = 0;
};

struct match_pnts_oper_real
{
	match_pnts_oper_real(REAL ival, const char * ipos, pnts_oper_real * ioper) : oper(ioper), val(ival), pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(val, pnts) );
		}
	}
	REAL val;
	const char * pos;
	boolvec * res;
	pnts_oper_real * oper;
};

struct pnts_oper_real_plus : public pnts_oper_real
{
	virtual bool do_oper(REAL val, d_points * pnts) {
		writelog(LOG_MESSAGE,"calculating pnts_plus_real: \"%s\" + %g",pnts->getName(), val);
		pnts->plus(val);
		return true;
	}
};

boolvec * pnts_plus_real(REAL val, const char * pos) 
{
	pnts_oper_real_plus oper;
	match_pnts_oper_real qq(val, pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_real_minus : public pnts_oper_real
{
	virtual bool do_oper(REAL val, d_points * pnts) {
		writelog(LOG_MESSAGE,"calculating pnts_minus_real: \"%s\" + %g",pnts->getName(), val);
		pnts->minus(val);
		return true;
	}
};

boolvec * pnts_minus_real(REAL val, const char * pos) 
{
	pnts_oper_real_minus oper;
	match_pnts_oper_real qq(val, pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_real_mult : public pnts_oper_real
{
	virtual bool do_oper(REAL val, d_points * pnts) {
		writelog(LOG_MESSAGE,"calculating pnts_mult_real: \"%s\" + %g",pnts->getName(), val);
		pnts->mult(val);
		return true;
	}
};

boolvec * pnts_mult_real(REAL val, const char * pos) 
{
	pnts_oper_real_mult oper;
	match_pnts_oper_real qq(val, pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_real_div : public pnts_oper_real
{
	virtual bool do_oper(REAL val, d_points * pnts) {
		writelog(LOG_MESSAGE,"calculating pnts_div_real: \"%s\" + %g",pnts->getName(), val);
		pnts->div(val);
		return true;
	}
};

boolvec * pnts_div_real(REAL val, const char * pos) 
{
	pnts_oper_real_div oper;
	match_pnts_oper_real qq(val, pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_real_set : public pnts_oper_real
{
	virtual bool do_oper(REAL val, d_points * pnts) {
		writelog(LOG_MESSAGE,"calculating pnts_set_real: \"%s\" + %g",pnts->getName(), val);
		pnts->set(val);
		return true;
	}
};

boolvec * pnts_set_real(REAL val, const char * pos) 
{
	pnts_oper_real_set oper;
	match_pnts_oper_real qq(val, pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_surf
{
	virtual bool do_oper(d_points * pnts, d_surf * surf) = 0;
};

struct match_pnts_oper_surf2
{
	match_pnts_oper_surf2(d_points * ipnts, const char * isurf_pos, pnts_oper_surf * ioper) : oper(ioper), pnts(ipnts), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(pnts, surf) );
		}
	}
	d_points * pnts;
	const char * surf_pos;
	boolvec * res;
	pnts_oper_surf * oper;
};

struct match_pnts_oper_surf
{
	match_pnts_oper_surf(const char * ipnts_pos, const char * isurf_pos, pnts_oper_surf * ioper) : oper(ioper), pnts_pos(ipnts_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pnts_pos, pnts->getName()) )
		{
			match_pnts_oper_surf2 qq(pnts, surf_pos, oper);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pnts_pos;
	const char * surf_pos;
	boolvec * res;
	pnts_oper_surf * oper;
};

struct pnts_oper_surf_plus : public pnts_oper_surf
{
	virtual bool do_oper(d_points * pnts, d_surf * srf)
	{
		writelog(LOG_MESSAGE,"calculating pnts_plus_surf for points \"%s\" and surface \"%s\"", pnts->getName(), srf->getName());
		if (pnts->size() == 0)
			return false;

		size_t i;
		REAL x,y,z, Z;
		vec::iterator x_ptr = pnts->X->begin();
		vec::iterator y_ptr = pnts->Y->begin();
		vec::iterator z_ptr = pnts->Z->begin();
		for (i = 0; i < pnts->size(); i++) {
			x = *(x_ptr + i);
			y = *(y_ptr + i);
			z = *(z_ptr + i);
			Z = srf->getValue(x,y);
			if (Z != srf->undef_value) {
				*(z_ptr + i) = z + Z;
			}
		}

		return true;
	};
};

boolvec * pnts_plus_surf(const char * pos, const char * surf_pos) 
{
	pnts_oper_surf_plus oper;
	match_pnts_oper_surf qq(pos, surf_pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_surf_minus : public pnts_oper_surf
{
	virtual bool do_oper(d_points * pnts, d_surf * srf)
	{
		writelog(LOG_MESSAGE,"calculating pnts_minus_surf for points \"%s\" and surface \"%s\"", pnts->getName(), srf->getName());
		if (pnts->size() == 0)
			return false;

		size_t i;
		REAL x,y,z, Z;
		vec::iterator x_ptr = pnts->X->begin();
		vec::iterator y_ptr = pnts->Y->begin();
		vec::iterator z_ptr = pnts->Z->begin();
		for (i = 0; i < pnts->size(); i++) {
			x = *(x_ptr + i);
			y = *(y_ptr + i);
			z = *(z_ptr + i);
			Z = srf->getValue(x,y);
			if (Z != srf->undef_value) {
				*(z_ptr + i) = z - Z;
			}
		}

		return true;
	};
};

boolvec * pnts_minus_surf(const char * pos, const char * surf_pos) 
{
	pnts_oper_surf_minus oper;
	match_pnts_oper_surf qq(pos, surf_pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_surf_mult : public pnts_oper_surf
{
	virtual bool do_oper(d_points * pnts, d_surf * srf)
	{
		writelog(LOG_MESSAGE,"calculating pnts_mult_surf for points \"%s\" and surface \"%s\"", pnts->getName(), srf->getName());
		if (pnts->size() == 0)
			return false;

		size_t i;
		REAL x,y,z, Z;
		vec::iterator x_ptr = pnts->X->begin();
		vec::iterator y_ptr = pnts->Y->begin();
		vec::iterator z_ptr = pnts->Z->begin();
		for (i = 0; i < pnts->size(); i++) {
			x = *(x_ptr + i);
			y = *(y_ptr + i);
			z = *(z_ptr + i);
			Z = srf->getValue(x,y);
			if (Z != srf->undef_value) {
				*(z_ptr + i) = z * Z;
			}
		}

		return true;
	};
};

boolvec * pnts_mult_surf(const char * pos, const char * surf_pos) 
{
	pnts_oper_surf_mult oper;
	match_pnts_oper_surf qq(pos, surf_pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_surf_div : public pnts_oper_surf
{
	virtual bool do_oper(d_points * pnts, d_surf * srf)
	{
		writelog(LOG_MESSAGE,"calculating pnts_div_surf for points \"%s\" and surface \"%s\"", pnts->getName(), srf->getName());
		if (pnts->size() == 0)
			return false;

		size_t i;
		REAL x,y,z, Z;
		vec::iterator x_ptr = pnts->X->begin();
		vec::iterator y_ptr = pnts->Y->begin();
		vec::iterator z_ptr = pnts->Z->begin();
		for (i = 0; i < pnts->size(); i++) {
			x = *(x_ptr + i);
			y = *(y_ptr + i);
			z = *(z_ptr + i);
			Z = srf->getValue(x,y);
			if (Z != srf->undef_value) {
				if (Z != 0)
					*(z_ptr + i) = z / Z;
				else
					*(z_ptr + i) = 0;
			}
		}

		return true;
	};
};

boolvec * pnts_div_surf(const char * pos, const char * surf_pos) 
{
	pnts_oper_surf_div oper;
	match_pnts_oper_surf qq(pos, surf_pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct pnts_oper_surf_set : public pnts_oper_surf
{
	virtual bool do_oper(d_points * pnts, d_surf * srf)
	{
		writelog(LOG_MESSAGE,"calculating pnts_set_surf for points \"%s\" and surface \"%s\"", pnts->getName(), srf->getName());
		if (pnts->size() == 0)
			return false;

		size_t i;
		REAL x,y, Z;
		vec::iterator x_ptr = pnts->X->begin();
		vec::iterator y_ptr = pnts->Y->begin();
		vec::iterator z_ptr = pnts->Z->begin();
		for (i = 0; i < pnts->size(); i++) {
			x = *(x_ptr + i);
			y = *(y_ptr + i);
			Z = srf->getValue(x,y);
			if (Z != srf->undef_value) {
				*(z_ptr + i) = Z;
			}
		}

		return true;
	};
};

boolvec * pnts_set_surf(const char * pos, const char * surf_pos) 
{
	pnts_oper_surf_set oper;
	match_pnts_oper_surf qq(pos, surf_pos, &oper);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_update_by_surf2
{
	match_pnts_update_by_surf2(d_points * ipnts, const char * isurf_pos) : pnts(ipnts), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(surf_pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			size_t i;
			REAL x,y,z;
			vec::iterator x_ptr = pnts->X->begin();
			vec::iterator y_ptr = pnts->Y->begin();
			vec::iterator z_ptr = pnts->Z->begin();
			for (i = 0; i < pnts->size(); i++) {
				x = *(x_ptr + i);
				y = *(y_ptr + i);
				z = surf->getValue(x,y);
				*(z_ptr + i) = z;
			}
			res->push_back(true);
		}
	}
	d_points * pnts;
	const char * surf_pos;
	boolvec * res;
};

struct match_pnts_update_by_surf
{
	match_pnts_update_by_surf(const char * ipnts_pos, const char * isurf_pos) : pnts_pos(ipnts_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pnts_pos, pnts->getName()) )
		{
			match_pnts_update_by_surf2 qq(pnts, surf_pos);
			qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pnts_pos;
	const char * surf_pos;
	boolvec * res;
};

boolvec * pnts_update_by_surf(const char * pnts_pos, const char * surf_pos) 
{
	match_pnts_update_by_surf qq(pnts_pos, surf_pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_minx
{
	match_pnts_minx(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating minx for points \"%s\"", pnts->getName());
			res->push_back( pnts->minx() );
		}
	}
	const char * pos;
	vec * res;
};

vec * pnts_minx(const char * pos) 
{
	match_pnts_minx qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_maxx
{
	match_pnts_maxx(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating maxx for points \"%s\"", pnts->getName());
			res->push_back( pnts->maxx() );
		}
	}
	const char * pos;
	vec * res;
};

vec * pnts_maxx(const char * pos) 
{
	match_pnts_maxx qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_miny
{
	match_pnts_miny(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating miny for points \"%s\"", pnts->getName());
			res->push_back( pnts->miny() );
		}
	}
	const char * pos;
	vec * res;
};

vec * pnts_miny(const char * pos) 
{
	match_pnts_miny qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_maxy
{
	match_pnts_maxy(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating maxy for points \"%s\"", pnts->getName());
			res->push_back( pnts->maxy() );
		}
	}
	const char * pos;
	vec * res;
};

vec * pnts_maxy(const char * pos) 
{
	match_pnts_maxy qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_minz
{
	match_pnts_minz(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating minz for points \"%s\"", pnts->getName());
			res->push_back( pnts->minz() );
		}
	}
	const char * pos;
	vec * res;
};

vec * pnts_minz(const char * pos) 
{
	match_pnts_minz qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_maxz
{
	match_pnts_maxz(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			writelog(LOG_MESSAGE,"calculating maxz for points \"%s\"", pnts->getName());
			res->push_back( pnts->maxz() );
		}
	}
	const char * pos;
	vec * res;
};

vec * pnts_maxz(const char * pos) 
{
	match_pnts_maxz qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_abs
{
	match_pnts_abs(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			pnts->abs();
			res->push_back(true);
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * pnts_abs(const char * pos) 
{
	match_pnts_abs qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_setName {
	match_pnts_setName(const char * inewname, const char * ipos) : newname(inewname), pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			pnts->setName(newname);
			res->push_back(true);
		}
	};
	const char * pos;
	const char * newname;
	boolvec * res;
};

boolvec * pnts_setName(const char * new_name, const char * pos) 
{
	match_pnts_setName qq(new_name, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_getName {
	match_pnts_getName(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( pnts->getName() );
		}
	};
	const char * pos;
	strvec * res;
};

strvec * pnts_getName(const char * pos) 
{
	match_pnts_getName qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

const char * pnts_getNameAt(int pos)
{
	if ((size_t)pos > surfit_pnts->size())
		return NULL;
	return (*surfit_pnts)[pos]->getName();
};

struct match_pnts_getId {
	match_pnts_getId(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( pnts->getId() );
		}
	};
	const char * pos;
	intvec * res;
};

intvec * pnts_getId(const char * pos) 
{
	match_pnts_getId qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_transform 
{
	match_pnts_transform(REAL ishiftX, REAL iscaleX, REAL ishiftY, REAL iscaleY, const char * ipos) :
			     shiftX(ishiftX), scaleX(iscaleX), scaleY(iscaleY), pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			_points_transform(pnts->X, pnts->Y, shiftX, scaleX, shiftY, scaleY);
			res->push_back(true);
		}
	}
	REAL shiftX;
	REAL scaleX;
	REAL shiftY;
	REAL scaleY;
	const char * pos;
	boolvec * res;
};

boolvec * pnts_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * pos) 
{
	match_pnts_transform qq(shiftX, scaleX, shiftY, scaleY, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_inverse_transform 
{
	match_pnts_inverse_transform(REAL ishiftX, REAL iscaleX, REAL ishiftY, REAL iscaleY, const char * ipos) :
			     shiftX(ishiftX), scaleX(iscaleX), scaleY(iscaleY), pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			_inverse_points_transform(pnts, shiftX, scaleX, shiftY, scaleY);
			res->push_back(true);
		}
	}
	REAL shiftX;
	REAL scaleX;
	REAL shiftY;
	REAL scaleY;
	const char * pos;
	boolvec * res;
};

boolvec * pnts_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * pos) 
{
	match_pnts_inverse_transform qq(shiftX, scaleX, shiftY, scaleY, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

struct match_pnts_rotate 
{
	match_pnts_rotate(REAL icenterX, REAL icenterY, REAL iangle, const char * ipos) :
			  centerX(icenterX), centerY(icenterY), angle(iangle), pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back ( rotate(centerX, centerY, angle, 
					 pnts->X->begin(), pnts->X->end(),
					 pnts->Y->begin(), pnts->Y->end()) );
		}
	}
	REAL centerX;
	REAL centerY;
	REAL angle;
	const char * pos;
	boolvec * res;
};

boolvec * pnts_rotate(REAL centerX, REAL centerY, REAL angle, const char * pos) 
{
	match_pnts_rotate qq(centerX, centerY, angle, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

void pnts_del(const char * pos) 
{
	if (surfit_pnts->size() == 0)
		return;
	size_t i;
	for (i = surfit_pnts->size()-1; i >= 0; i--)
	{
		d_points * pnts = (*surfit_pnts)[i];
		if ( StringMatch(pos, pnts->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing points \"%s\" from memory", pnts->getName());
			pnts->release();
			surfit_pnts->erase(surfit_pnts->begin()+i);
		}
		if (i == 0)
			break;
	}
};

struct pnts_oper_concat : public pnts_oper
{
	virtual bool do_oper(d_points * pnts1, d_points * pnts2)
	{
		if (pnts2->size() == 0)
			return false;

		int old_cnt = pnts1->size();
		int cnt = old_cnt + pnts2->size();

		if (pnts1->X == NULL)
			pnts1->X = create_vec();
		if (pnts1->Y == NULL)
			pnts1->Y = create_vec();
		if (pnts1->Z == NULL)
			pnts1->Z = create_vec();

		pnts1->X->resize(cnt);
		pnts1->Y->resize(cnt);
		pnts1->Z->resize(cnt);

		vec::iterator ptr;

		ptr = pnts1->X->begin() + old_cnt;
#ifdef XXL
		std::copy(pnts2->X->const_begin(), pnts2->X->const_end(), ptr);
#else
		memcpy(ptr, pnts2->X->begin(), pnts2->size()*sizeof(REAL));
#endif

		ptr = pnts1->Y->begin() + old_cnt;
#ifdef XXL
		std::copy(pnts2->Y->const_begin(), pnts2->Y->const_end(), ptr);
#else
		memcpy(ptr, pnts2->Y->begin(), pnts2->size()*sizeof(REAL));
#endif

		ptr = pnts1->Z->begin() + old_cnt;
#ifdef XXL
		std::copy(pnts2->Z->const_begin(), pnts2->Z->const_end(), ptr);
#else
		memcpy(ptr, pnts2->Z->begin(), pnts2->size()*sizeof(REAL));
#endif

		return true;
	};
};

boolvec * pnts_concat(const char * pos1, const char * pos2) 
{
	pnts_oper_concat oper_concat;
	match_pnts_oper qq(pos1, pos2, &oper_concat);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

int pnts_size() {
	return surfit_pnts->size();
};

void pnts_info() {
	size_t pnts_counter;
	for (pnts_counter = 0; pnts_counter < surfit_pnts->size(); pnts_counter++) {
		d_points * pnts = *(surfit_pnts->begin()+pnts_counter);
		_pnts_info(pnts);
		
	}
};

struct match_pnts_to_cntrs
{
	match_pnts_to_cntrs(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back ( _pnts_to_cntrs(pnts) );
		}
	}
	REAL centerX;
	REAL centerY;
	REAL angle;
	const char * pos;
	boolvec * res;
};

boolvec * pnts_to_cntrs(const char * pos) 
{
	match_pnts_to_cntrs qq(pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

}; // namespace surfit;

