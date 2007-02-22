
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

#include <assert.h>

namespace surfit {

d_hist * create_hist(REAL ifrom, REAL ito,
		     vec * iZ,
		     const char * hist_name)
{
	return new d_hist(ifrom, ito, iZ, hist_name);
};

d_hist * create_hist(const d_hist * ihist)
{
	return new d_hist(ihist);
};

d_hist::d_hist(REAL from, REAL to,
	       vec * iZ, 
	       const char * iname) : data("d_hist")
{
	z_from = from;
	z_to = to;
	cnt = iZ->size();
	z_step = (z_to-z_from)/REAL(cnt);
	
	hst = iZ;

	setName(iname);
};

d_hist::d_hist(const d_hist * ihist) : data("d_hist")
{
	z_from = ihist->from();
	z_to = ihist->to();
	cnt = ihist->hst->size();
	z_step = ihist->get_step();

	hst = create_vec(*(ihist->hst));

	setName(ihist->getName());
};

d_hist::~d_hist() {
	if (hst)
		hst->release();
};

size_t d_hist::operator()(REAL value) const 
{
	if (value < z_from) {
		assert(0);
		return UINT_MAX;
	}
	if (value > z_to) {
		assert(0);
		return UINT_MAX;
	}

	size_t pos = (size_t)((value-z_from)/z_step);
	return MIN(size()-1,pos);
};

const REAL d_hist::operator ()(size_t pos) const
{
	return (*hst)(pos);
};

REAL & d_hist::operator [](size_t pos) 
{
	return (*hst)(pos);
};

bool d_hist::get_interv(size_t pos, REAL & value_from, REAL & value_to, REAL & hst_value) const
{
	if (pos > size())
		return false;
	value_from = z_from + pos*z_step;
	value_to = value_from + z_step;
	hst_value = (*hst)(pos);
	return true;
};

bool d_hist::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const 
{
	return false;
};
	
bool d_hist::getMinMaxZ(REAL & minz, REAL & maxz) const 
{
	return false;
};

size_t d_hist::size() const {
	return cnt;
};

REAL d_hist::get_step() const {
	return z_step;
};

REAL d_hist::from() const {
	return z_from;
};

REAL d_hist::to() const {
	return z_to;
};

void d_hist::normalize()
{
	REAL sum = 0;
	size_t i;
	for (i = 0; i < hst->size(); i++) 
		sum += (*hst)(i);

	if (sum == 1)
		return;

	for (i = 0; i < hst->size(); i++) 
		(*hst)(i) /= sum;
};

vec * d_hist::get_cumulative_hist()
{
	vec * res = create_vec(size()+1,0,0); // don't fill
	REAL sum = 0;
	size_t res_size = res->size(), i;
	(*res)(0) = 0;
	for (i = 1; i < res_size; i++) {
		sum += (*hst)(i-1);
		(*res)(i) = sum;
	}
	return res;
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
			surfit_hists = NULL;
		}
	}

};

hist_garbage hist_garb;

}; // namespace surfit;

