
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
#include "func.h"
#include "trend.h"
#include "grid.h"
#include "vec.h"
#include "datafile.h"

namespace surfit {

trend::trend(vec * icoeff, grid * igeom,
             REAL iD1, REAL iD2,
	     const char * funcname) :
             func(icoeff, igeom, funcname) 
{
	D1 = iD1; 
	D2 = iD2;
};

trend::trend(func *& fnc, REAL iD1, REAL iD2) : 
func(fnc->coeff, fnc->grd, fnc->getName())
{
	D1 = iD1;
	D2 = iD2;
	fnc->coeff = NULL;
	fnc->grd = NULL;
	
	delete fnc;

	fnc = NULL;
};

bool trend::writeTags(datafile *df) const {
		
	bool res = true;
	bool op;
	
	op = df->writeTag("trend");		res = (res && op);

	if (getName()) {
		op = df->writeString("name", getName()); res = (res && op);
	}
	
	// grdetry
	op = grd->writeTags(df);			res = (res && op);
		
	op = df->writeRealArray("coeff", coeff->begin(), coeff->size()); res = (res && op);

	op = df->writeReal("undef_value", undef_value); res = (res && op);

	op = df->writeReal("D1", D1); res = (res && op);
	op = df->writeReal("D2", D2); res = (res && op);
		
	op = df->writeEndTag();					res = (res && op);

	return res;
	
};

}; // namespace surfit;

