
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "ie.h"
#include "wfunc.h"
#include "datafile.h"
#include "grid.h"
#include "vec.h"

namespace surfit {

wfunc::wfunc(vec * icoeff, grid * igrd, REAL iweight, const char * funcname)
: func(icoeff, igrd, funcname) {
	weight = iweight;
};

wfunc::wfunc(func * fnc, REAL iweight, const char * funcname)
: func(fnc->coeff, fnc->grd, funcname) {
	weight = iweight;
	fnc->coeff = NULL;
	fnc->grd = NULL;
};

wfunc::~wfunc() {};

bool wfunc::writeTags(datafile *df) const {
		
	bool res = true;
	bool op;
	
	op = df->writeTag("wfunc");		res = (res && op);

	if (getName()) {
		op = df->writeString("name", getName()); res = (res && op);
	}
	
	op = grd->writeTags(df);			res = (res && op);
	op = df->writeRealArray("coeff", coeff->begin(), coeff->size()); res = (res && op);
	op = df->writeReal("undef_value", undef_value); res = (res && op);
	op = df->writeReal("weight", weight); res = (res && op);
	op = df->writeEndTag();					res = (res && op);

	return res;
	
};

}; // namespace surfit;

