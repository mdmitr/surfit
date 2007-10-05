
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

//! constructor for \ref d_hist
SURFIT_EXPORT
d_hist * create_hist(REAL ifrom, REAL ito,
		     vec * iZ = NULL,
		     const char * hist_name = NULL);

//! constructor for \ref d_hist
SURFIT_EXPORT
d_hist * create_hist(const d_hist * ihist);

/*! \class d_hist
    \brief class for operating with histogram
*/
class SURFIT_EXPORT d_hist : public data {
protected:
	
	//! constructor
	d_hist(REAL ifrom, REAL ito,
	       vec * iZ = NULL,
	       const char * hist_name = NULL);

	//! constructor
	d_hist(const d_hist * ihist);
       
	//! destructor
	~d_hist();

public:

	//! constructor
	friend SURFIT_EXPORT
	d_hist * create_hist(REAL ifrom, REAL ito,
		             vec * iZ,
			     const char * hist_name);

	//! constructor
	friend SURFIT_EXPORT
	d_hist * create_hist(const d_hist * ihist);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! returns bin number for given value
	size_t operator()(REAL value) const;
	
	//! returns histogram value for given bin
	const REAL operator()(size_t pos) const;

	//! returns reference to histogram value for given bin
	REAL & operator[](size_t pos);
	
	//! returns bin
	bool get_interv(size_t pos, REAL & from, REAL & to, REAL & value) const;
	
	//! returns number of histogram bins
	size_t size() const;

	//! returns bin width
	REAL get_step() const;
	
	//! returns left bound for the first bin
	REAL from() const;

	//! return right bound for the last bin
	REAL to() const;

	//! calculates cumulative histogram
	vec * get_cumulative_hist();

	//! normalize histogram
	void normalize();

private:
	
	//! left bound for the first bin
	REAL z_from;
	//! right bound for the last bin
	REAL z_to;
	//! bin width
	REAL z_step;

	//! number of bins
	size_t cnt;

public:

	//! histogram values
	vec * hst;
	
};

//! collection of \ref d_hist objects
class SURFIT_EXPORT hists_container : public objects_container<d_hist>
{
public:
	virtual void push_back(d_hist * elem);
};

//! container of \ref d_hist objects
extern SURFIT_EXPORT hists_container * surfit_hists;

}; // namespace surfit;

#endif

