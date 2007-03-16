
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

bool mask_load(const char * filename, const char * defname) 
{
	const char * fname = find_first(filename);
	bool res = false;

	while (fname != NULL) {
		d_mask * msk = _mask_load(fname, defname);
		if (msk) {
			surfit_masks->push_back(msk);
			res = true;
		}
		fname = find_next();
	}

	find_close();
	return res;
};

bool mask_save(const char * filename, const char * pos) 
{
	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (!msk)
		return false;

	return _mask_save(msk, filename);
};

bool mask_save_grd(const char * filename, const char * pos) 
{
	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (!msk)
		return false;

	if (!filename)
		return false;

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	writelog(LOG_MESSAGE,"Saving mask %s to file %s (grd-ASCII)", msk->getName(), filename);

	fprintf(f,"DSAA\n");
	int nx = msk->getCountX();
	int ny = msk->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", msk->getMinX(), msk->getMaxX());
	fprintf(f,"%lf %lf\n", msk->getMinY(), msk->getMaxY());
	fprintf(f,"0 1\n");

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = msk->coeff->get( ix + nx*iy );
			fprintf(f,"%lf ", val);
			if (ncnt>9) { 
				fprintf(f,"\n");
				ncnt = 0;
			}
			ncnt++;
		}
		fprintf(f,"\n");
	}

	fclose(f);

	return true;
};

bool mask_save_xyz(const char * filename, const char * pos) 
{
	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (!msk)
		return false;

	if (!filename)
		return false;

	writelog(LOG_MESSAGE,"Saving mask %s to file %s (xyz-ASCII)", msk->getName(), filename);

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	int nx = msk->getCountX();
	int ny = msk->getCountY();

	int iy, ix;
	int cnt = 0;
	REAL val;
	REAL x_coord, y_coord;
	
    
	for(iy=0; iy<ny; iy++)	{
		for(ix=0; ix<nx; ix++)	{
			msk->getCoordNode(ix, iy, x_coord, y_coord);
			val = msk->coeff->get( ix + nx*iy );
			fprintf(f,"%lf %lf %lf \n", x_coord, y_coord, val);
		}
	}

	fclose(f);

	return true;
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

struct match_mask_by_surf
{
	match_mask_by_surf(const char * isurf_pos) : surf_pos(isurf_pos), res(false) {};
	void operator()(d_surf * surf) 
	{
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			writelog(LOG_MESSAGE,"creating mask by surface %s", surf->getName());
			d_mask * msk = _mask_by_surf(surf);
			if (msk) {
				surfit_masks->push_back(msk);
				res = true;
			}
		}
			
	};
	const char * surf_pos;
	bool res;
};

bool mask_by_surf(const char * surf_pos) 
{
	match_mask_by_surf mm(surf_pos);
	mm = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), mm);
	return mm.res;
};

struct match_mask_apply_to_surf2
{
	match_mask_apply_to_surf2(d_mask * imask, const char * isurf_pos) : mask(imask), surf_pos(isurf_pos), res(false) {};
	void operator()(d_surf * surf) {
		if ( StringMatch( surf_pos, surf->getName() ) )
		{
			res = _mask_apply_to_surf(mask, surf);		
		}
	};
	d_mask * mask;
	const char * surf_pos;
	bool res;
};

struct match_mask_apply_to_surf
{
	match_mask_apply_to_surf(const char * idef_pos, const char * isurf_pos) : def_pos(idef_pos), surf_pos(isurf_pos), res(false) {};
	void operator()(d_mask * mask) {
		if ( StringMatch( def_pos, mask->getName() ) )
		{
			match_mask_apply_to_surf2 ss(mask, surf_pos);
			ss = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), ss);
			res = ss.res;
		}
	};
	const char * def_pos;
	const char * surf_pos;
	bool res;
};

bool mask_apply_to_surf(const char * def_pos, const char * surf_pos) 
{
	match_mask_apply_to_surf ss(def_pos, surf_pos);
	ss = std::for_each(surfit_masks->begin(), surfit_masks->end(), ss);
	return ss.res;
};

bool mask_setName(const char * new_name, const char * pos) 
{
	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (!msk)
		return false;

	writelog(LOG_MESSAGE,"setting name \"%s\" to mask \"%s\"",
		new_name, msk->getName());

	msk->setName(new_name);
	return true;
};

const char * mask_getName(const char * pos) 
{
	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (!msk)
		return false;
	return msk->getName();
};

bool mask_getValue(REAL x, REAL y, const char * pos) 
{
	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (!msk)
		return false;
	return msk->getValue(x,y);
};

struct match_mask_to_surf
{
	match_mask_to_surf(const char * ipos) : pos(ipos), res(false) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			writelog(LOG_MESSAGE,"converting mask \"%s\" to surface", mask->getName());
			d_surf * srf = create_surf_by_mask(mask);
			surfit_surfs->push_back(srf);
			res = true;
		}
	}
	const char * pos;
	bool res;
};

bool mask_to_surf(const char * pos) 
{
	match_mask_to_surf mms(pos);
	mms = std::for_each(surfit_masks->begin(), surfit_masks->end(), mms);
	return mms.res;
};

bool mask_delall() {

	size_t i;

	writelog(LOG_MESSAGE,"removing all masks from memory");

	if (surfit_masks == NULL)
		return false;

	if (surfit_masks->size() == 0) {
		return false;
	}
	
	for (i = 0; i < surfit_masks->size(); i++) {
		d_mask * msk = (*surfit_masks)[i];
		if (msk)
			msk->release();
	}
	
	surfit_masks->resize(0);

	return true;
};

struct match_mask_del
{
	match_mask_del(const char * ipos) : pos(ipos), res(false) {};
	void operator()(d_mask * mask)
	{
		if ( StringMatch( pos, mask->getName() ) )
		{
			std::vector<d_mask *>::iterator it = std::find(surfit_masks->begin(), surfit_masks->end(), mask);
			if (it != surfit_masks->end())
			{
				writelog(LOG_MESSAGE,"removing mask \"%s\" from memory", mask->getName());
				surfit_masks->erase(it);	
				res = true;
			}
		}
	};
	const char * pos;
	bool res;
};

bool mask_del(const char * pos) 
{
	match_mask_del mmd(pos);
	mmd = std::for_each(surfit_masks->begin(), surfit_masks->end(), mmd);
	return mmd.res;
};

void masks_info() {
	if (surfit_masks->size() > 0) {
		size_t mask_cnt;
		for (mask_cnt = 0; mask_cnt < surfit_masks->size(); mask_cnt++) {
			d_mask * a_srf = *(surfit_masks->begin()+mask_cnt);
			if (a_srf) {
				_mask_info(a_srf);
			}
		}
	}
};

int mask_size() {
	return surfit_masks->size();
};

}; // namespace surfit;

