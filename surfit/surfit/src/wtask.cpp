
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
#include "wtask.h"
#include "vec_alg.h"

#include <algorithm>

namespace surfit {

wtask::wtask() : task()
{
};

wtask::wtask(REAL *& iX_begin, REAL * iX_end, 
             REAL *& iY_begin, REAL * iY_end, 
             REAL *& iZ_begin, REAL * iZ_end,
	     REAL *& iW_begin, REAL * iW_end,
             const char * itaskname) : 
        task(iX_begin, iX_end,
	     iY_begin, iY_end,
	     iZ_begin, iZ_end,
	     itaskname)
{
	W_begin = iW_begin;
	iW_begin = NULL;
	W_end = iW_end;
};

bool wtask::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	minx = *std::min_element(X_begin, X_end);
	maxx = *std::max_element(X_begin, X_end);
	miny = *std::min_element(Y_begin, Y_end);
	maxy = *std::max_element(Y_begin, Y_end);
	return true;
};

wtask::~wtask() {
	free(W_begin);
};

}; // namespace surfit;

