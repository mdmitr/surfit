
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
#include "iso.h"

namespace surfit {

iso::iso(REAL * iX_begin, REAL * iX_end,
	 REAL * iY_begin, REAL * iY_end,
	 REAL ivalue,
	 const char * iso_name) : 
    curv(iX_begin, iX_end,
         iY_begin, iY_end,
         iso_name)
{
	value = ivalue;
};

iso::iso(curv * crv, REAL ivalue)  :
    curv(crv->X_begin, crv->X_end,
	 crv->Y_begin, crv->Y_end,
	 crv->getName())
{
	value = ivalue;
	crv->X_begin = NULL;
	crv->X_end = NULL;
	crv->Y_begin = NULL;
	crv->Y_end = NULL;
};
	  
iso::~iso()
{
};

bool iso::getMinMaxZ(REAL & minz, REAL & maxz) const {
	minz = MIN(minz, value);
	maxz = MAX(maxz, value);
	return true;
};

}; // namespace surfit;

