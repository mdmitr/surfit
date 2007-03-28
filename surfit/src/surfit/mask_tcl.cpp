
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
#include "boolvec.h"
#include "strvec.h"

#include "mask.h"
#include "surf.h"
#include "mask_internal.h"
#include "mask_tcl.h"
#include "surf_internal.h"
#include "surf_tcl.h"
#include "grid.h"
#include "bitvec.h"
#include "variables_internal.h"
#include "findfile.h"

#include <errno.h>
#include <float.h>

#include <algorithm>

namespace surfit {

boolvec * mask_load(const char * filename, const char * defname) 
{
	const char * fname = find_first(filename);
	boolvec * res = create_boolvec();

	while (fname != NULL) {
		d_mask * msk = _mask_load(fname, defname);
		if (msk) {
			surfit_masks->push_back(msk);
			res->push_back(true);
		} else
			res->push_back(false);
		fname = find_next();
	}

	find_close();
	return res;
};

struct match_mask_save
{
	match_mask_save(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(pos, mask->getName()) )
		{
			bool r = _mask_save(mask, filename);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(r);
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * mask_save(const char * filename, const char * pos) 
{
	match_mask_save qq(filename, pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct mask_oper
{
	virtual void do_oper(d_mask * mask1, d_mask * mask2) = 0;
};

struct match_mask_oper2
{
	match_mask_oper2(const char * ipos2, d_mask * imask1, mask_oper * ioper) : mask1(imask1), pos2(ipos2), oper(ioper) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( pos2, mask->getName() ) )
		{
			oper->do_oper(mask1, mask);
		}
	};
	const char * pos2;
	d_mask * mask1;
	mask_oper * oper;
};

struct match_mask_oper
{
	match_mask_oper(const char * ipos1, const char * ipos2, mask_oper * ioper) : pos1(ipos1), pos2(ipos2), oper(ioper) {};
	void operator()(d_mask * mask) 
	{
		if ( StringMatch( pos1, mask->getName() ) )
		{
			std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_oper2(pos2, mask, oper));
		}
	}
	const char * pos1;
	const char * pos2;
	mask_oper * oper;
};

struct mask_or_oper : public mask_oper
{
	void do_oper(d_mask * mask1, d_mask * mask2) {
		writelog(LOG_MESSAGE,"mask : %s = %s OR %s", mask1->getName(), mask1->getName(), mask2->getName());
		mask1->OR(mask2);
	}
};

void mask_or(const char * pos1, const char * pos2) 
{
	mask_or_oper or_oper;
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_oper(pos1, pos2, &or_oper));	
};

struct mask_xor_oper : public mask_oper
{
	void do_oper(d_mask * mask1, d_mask * mask2) {
		writelog(LOG_MESSAGE,"mask : %s = %s XOR %s", mask1->getName(), mask1->getName(), mask2->getName());
		mask1->XOR(mask2);
	}
};

void mask_xor(const char * pos1, const char * pos2) 
{
	mask_xor_oper xor_oper;
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_oper(pos1, pos2, &xor_oper));	
};

struct mask_and_oper : public mask_oper
{
	void do_oper(d_mask * mask1, d_mask * mask2) {
		writelog(LOG_MESSAGE,"mask : %s = %s AND %s", mask1->getName(), mask1->getName(), mask2->getName());
		mask1->AND(mask2);
	}
};

void mask_and(const char * pos1, const char * pos2) 
{
	mask_and_oper and_oper;
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_oper(pos1, pos2, &and_oper));	
};

struct mask_not_oper : public mask_oper
{
	void do_oper(d_mask * mask1, d_mask * mask2) {
		writelog(LOG_MESSAGE,"mask : %s = %s NOT %s", mask1->getName(), mask1->getName(), mask2->getName());
		mask1->NOT(mask2);
	}
};

void mask_not(const char * pos1, const char * pos2) 
{
	mask_not_oper not_oper;
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_oper(pos1, pos2, &not_oper));	
};

struct match_mask_from_surf
{
	match_mask_from_surf(const char * isurf_pos) : surf_pos(isurf_pos) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating mask by surface %s", surf->getName());
			d_mask * msk = _mask_by_surf(surf);
			surfit_masks->push_back(msk);
		}
			
	};
	const char * surf_pos;
};

void mask_from_surf(const char * surf_pos) 
{
	match_mask_from_surf mm(surf_pos);
	mm = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), mm);
};

struct match_mask_apply_to_surf2
{
	match_mask_apply_to_surf2(d_mask * imask, const char * isurf_pos) : mask(imask), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_surf * surf) {
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			bool r = _mask_apply_to_surf(mask, surf);		
			if (res == NULL)
				res = create_boolvec();
			res->push_back(r);
		}
	};
	d_mask * mask;
	const char * surf_pos;
	boolvec * res;
};

struct match_mask_apply_to_surf
{
	match_mask_apply_to_surf(const char * idef_pos, const char * isurf_pos) : def_pos(idef_pos), surf_pos(isurf_pos), res(NULL) {};
	void operator()(d_mask * mask) {
		if ( StringMatch( def_pos, mask->getName() ) )
		{
			if (res == NULL)
				res = create_boolvec();
			match_mask_apply_to_surf2 ss(mask, surf_pos);
			ss = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), ss);
			if (ss.res) {
				res->push_back(ss.res);
				ss.res->release();
			}
		}
	};
	const char * def_pos;
	const char * surf_pos;
	boolvec * res;
};

boolvec * mask_apply_to_surf(const char * def_pos, const char * surf_pos) 
{
	match_mask_apply_to_surf ss(def_pos, surf_pos);
	ss = std::for_each(surfit_masks->begin(), surfit_masks->end(), ss);
	return ss.res;
};

struct match_mask_setName
{
	match_mask_setName(const char * inew_name, const char * ipos) : new_name(inew_name), pos(ipos) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(pos, mask->getName()) )
		{
			writelog(LOG_MESSAGE,"setting name \"%s\" to mask \"%s\"",
				 new_name, mask->getName());
			mask->setName(new_name);
		}
	}
	const char * new_name;
	const char * pos;
};

void mask_setName(const char * new_name, const char * pos) 
{
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_setName(new_name, pos));
};

struct match_mask_getName 
{
	match_mask_getName(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(pos, mask->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( strdup(mask->getName()) );
		}
	}
	const char * pos;
	strvec * res;
};


strvec * mask_getName(const char * pos) 
{
	match_mask_getName qq(pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_getValue
{
	match_mask_getValue(REAL ix, REAL iy, const char * ipos) : x(ix), y(iy), pos(ipos), res(NULL) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(pos, mask->getName()) )
		{
			bool r = mask->getValue(x,y);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(r);
		}
	}
	REAL x, y;
	const char * pos;
	boolvec * res;
};

boolvec * mask_getValue(REAL x, REAL y, const char * pos) 
{
	match_mask_getValue qq(x, y, pos);
	qq = std::for_each(surfit_masks->begin(), surfit_masks->end(), qq);
	return qq.res;
};

struct match_mask_to_surf
{
	match_mask_to_surf(const char * ipos) : pos(ipos) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"converting mask \"%s\" to surface", mask->getName());
			d_surf * srf = create_surf_by_mask(mask);
			surfit_surfs->push_back(srf);
		}
	}
	const char * pos;
};

void mask_to_surf(const char * pos) 
{
	match_mask_to_surf mms(pos);
	mms = std::for_each(surfit_masks->begin(), surfit_masks->end(), mms);
};

void mask_del(const char * pos) 
{
	size_t i;
	for (i = surfit_masks->size()-1; i >= 0; i--)
	{
		d_mask * mask = (*surfit_masks)[i];
		if ( StringMatch(pos, mask->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing mask \"%s\" from memory", mask->getName());
			mask->release();
			surfit_masks->erase(surfit_masks->begin()+i);
		}
		if (i == 0)
			break;
	}
	//std::for_each(surfit_masks->rbegin(), surfit_masks->rend(), match_mask_del(pos));
};

struct match_mask_info {
	match_mask_info(const char * ipos) : pos(ipos) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch(pos, mask->getName()) )
		{
			_mask_info(mask);
		}
	}
	const char * pos;
};

void mask_info(const char * pos) {
	std::for_each(surfit_masks->begin(), surfit_masks->end(), match_mask_info(pos));
};

int mask_size() {
	return surfit_masks->size();
};

}; // namespace surfit;

