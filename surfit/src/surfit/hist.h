
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
d_hist * create_hist(vec * iX, vec * iX2, vec * iZ,
		     const char * hist_name = NULL);

SURFIT_EXPORT
d_hist * create_hist2(REAL ifrom, REAL ito, REAL istep,
		      vec * iZ,
		      const char * hist_name = NULL);

class SURFIT_EXPORT d_hist : public data {
protected:
	
	d_hist(REAL ifrom, REAL ito, REAL istep,
	       vec * iZ,
	       const char * hist_name = NULL);

	d_hist(vec * iX1, vec * iX2, vec * iZ,
	       const char * hist_name = NULL);
	       
	~d_hist();

public:

	friend SURFIT_EXPORT
	d_hist * create_hist(vec * iX1, vec * iX2, vec * iZ,
			     const char * hist_name);

	friend SURFIT_EXPORT
	d_hist * create_hist2(REAL ifrom, REAL ito, REAL istep,
		              vec * iZ,
			      const char * hist_name);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	void normalize();
	bool get_interv(REAL value, int & pos) const;

	int size() const;

	vec * X1;
	vec * X2;
	vec * Z;
	
};

extern SURFIT_EXPORT std::vector<d_hist *> * surfit_hists;

}; // namespace surfit;

#endif

