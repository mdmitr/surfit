
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

#ifndef __surfit_hist_included__
#define __surfit_hist_included__

#include "surfit_data.h"

namespace surfit {

class d_hist;
class vec;

SURFIT_EXPORT
d_hist * create_hist(REAL ifrom, REAL ito,
		     vec * iZ = NULL,
		     const char * hist_name = NULL);

SURFIT_EXPORT
d_hist * create_hist(const d_hist * ihist);

class SURFIT_EXPORT d_hist : public data {
protected:
	
	d_hist(REAL ifrom, REAL ito,
	       vec * iZ = NULL,
	       const char * hist_name = NULL);

	d_hist(const d_hist * ihist);
       
	~d_hist();

public:

	friend SURFIT_EXPORT
	d_hist * create_hist(REAL ifrom, REAL ito,
		             vec * iZ,
			     const char * hist_name);

	friend SURFIT_EXPORT
	d_hist * create_hist(const d_hist * ihist);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	size_t operator()(REAL value) const;
	
	const REAL operator()(size_t pos) const;

	REAL & operator[](size_t pos);
	
	bool get_interv(size_t pos, REAL & from, REAL & to, REAL & value) const;
	size_t size() const;

	REAL get_step() const;
	REAL from() const;
	REAL to() const;

	vec * get_cumulative_hist();

	//! normalize histogram
	void normalize();

private:
	REAL z_from;
	REAL z_to;
	REAL z_step;

	size_t cnt;

public:
	vec * hst;
	
};

class SURFIT_EXPORT hists_container : public objects_container<d_hist>
{
public:
	virtual void push_back(d_hist * elem);
};

extern SURFIT_EXPORT hists_container * surfit_hists;

}; // namespace surfit;

#endif

