
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
#include "flt.h"

namespace surfit {

flt::flt(REAL * iX_begin, REAL * iX_end,
	 REAL * iY_begin, REAL * iY_end,
	 const char * flt_name) : 
    curv(iX_begin, iX_end,
         iY_begin, iY_end,
         flt_name)
{

};

flt::flt(curv * crv) : 
    curv(crv->X_begin, crv->X_end,
         crv->Y_begin, crv->Y_end,
         crv->getName())
{
	crv->X_begin = NULL;
	crv->X_end = NULL;
	crv->Y_begin = NULL;
	crv->Y_end = NULL;
};
	  
flt::~flt()
{
};

bool flt::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

}; // namespace surfit;

