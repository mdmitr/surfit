
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
#include "wiso.h"

namespace surfit {

wiso::wiso(REAL * iX_begin, REAL * iX_end,
	   REAL * iY_begin, REAL * iY_end,
	   REAL ivalue, REAL iweight,
	   const char * iso_name) : 
       iso(iX_begin, iX_end,
           iY_begin, iY_end,
	   ivalue, iso_name)
{
	weight = iweight;
};

wiso::wiso(curv * crv, REAL ivalue, REAL iweight) :
      iso(crv->X_begin, crv->X_end,
          crv->Y_begin, crv->Y_end,
	  ivalue, crv->getName())
{
	weight = iweight;
	crv->X_begin = NULL;
	crv->X_end = NULL;
	crv->Y_begin = NULL;
	crv->Y_end = NULL;
};

wiso::wiso(iso * crv, REAL iweight) :
      iso(crv->X_begin, crv->X_end,
          crv->Y_begin, crv->Y_end,
	  crv->value, crv->getName())
{
	weight = iweight;
	crv->X_begin = NULL;
	crv->X_end = NULL;
	crv->Y_begin = NULL;
	crv->Y_end = NULL;
};
	  
wiso::~wiso()
{
};

}; // namespace surfit;

