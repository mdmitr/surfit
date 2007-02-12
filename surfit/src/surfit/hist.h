
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
d_hist * create_hist(REAL ifrom, REAL ito, REAL istep,
		     vec * iZ = NULL,
		     const char * hist_name = NULL);

class SURFIT_EXPORT d_hist : public data {
protected:
	
	d_hist(REAL ifrom, REAL ito, REAL istep,
	       vec * iZ = NULL,
	       const char * hist_name = NULL);
       
	~d_hist();

public:

	friend SURFIT_EXPORT
	d_hist * create_hist(REAL ifrom, REAL ito, REAL istep,
		             vec * iZ,
			     const char * hist_name);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	bool get_interv_number(REAL value, size_t & pos) const;
	bool get_interv(size_t pos, REAL & value_from, REAL & value_to, REAL & hst_value) const;

	size_t size() const;

private:
	double z_from;
	double z_to;
	double z_step;

	size_t cnt;

	vec * hst;
	
};

extern SURFIT_EXPORT std::vector<d_hist *> * surfit_hists;

}; // namespace surfit;

#endif

