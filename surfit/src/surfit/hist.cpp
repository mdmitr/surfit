
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

#include "vec.h"
#include "vec_alg.h"

#include "hist.h"
#include "free_elements.h"

namespace surfit {

d_hist * create_hist(vec * iX1, vec * iX2, vec * iZ,
		     const char * hist_name)
{
	return new d_hist(iX1, iX2, iZ, hist_name);
};

d_hist * create_hist2(REAL ifrom, REAL ito, REAL istep,
		      vec * iZ,
		      const char * hist_name)
{
	return new d_hist(ifrom, ito, istep, iZ, hist_name);
};

d_hist::d_hist(vec * iX1, vec * iX2, vec * iZ, 
	       const char * iname) : data("d_hist")
{
	X1 = iX1;
	X2 = iX2;
	Z = iZ;
	setName(iname);
	normalize();
};

d_hist::d_hist(REAL from, REAL to, REAL step,
	       vec * iZ, 
	       const char * iname) : data("d_hist")
{
	int cnt = int((to-from)/step - 1);
	X1 = create_vec(cnt);
	X2 = create_vec(cnt);
	int i;
	for (i = 0; i < cnt; i++) {
		(*X1)(i) = from + i*step;
		(*X2)(i) = from + (i+1)*step;
	}	

	Z = iZ;
	Z = iZ;
	setName(iname);
	normalize();
};

d_hist::~d_hist() {
	if (X1)
		X1->release();
	if (X2)
		X2->release();
	if (Z)
		Z->release();
};

void d_hist::normalize() {
	if (size() == 0)
		return;

	REAL sum = sum_value(Z->begin(), Z->end(), FLT_MAX);	

	REAL mult = 100./sum;
	if (mult == 1)
		return;

	int i;
	for (i = 0; i < size(); i++) 
		(*Z)(i) *= mult;
};

bool d_hist::get_interv(REAL value, int & pos) const 
{
	int i;
	REAL from, to;
	for (i = 0; i < size(); i++) {
		from = (*X1)(i);
		to = (*X2)(i);
		if ( (from <= value) && (value < to) ) {
			pos = i;
			return true;
		}
	}
	return false;
};

bool d_hist::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const 
{
	return false;
};
	
bool d_hist::getMinMaxZ(REAL & minz, REAL & maxz) const 
{
	return false;
};

int d_hist::size() const {
	if (Z == NULL)
		return 0;
	return Z->size();
};

std::vector<d_hist *>     * surfit_hists     = NULL;

/*! \struct hist_garbage
    \brief struct for deletion of \ref hist pointers
*/
struct hist_garbage : public binman {
	//! inits \ref surfit_hist and \ref surfit_hists
	hist_garbage() {
		surfit_hists = new std::vector<d_hist *>;
	}
	//! removes \ref surfit_hist and \ref surfit_hists
	~hist_garbage() {
		if (surfit_hists) {
			release_elements(surfit_hists->begin(), surfit_hists->end());
			delete surfit_hists;
		}
	}

};

hist_garbage hist_garb;

}; // namespace surfit;

