
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
#include <math.h>
#include "curv.h"
#include <algorithm>

namespace surfit {

curv::curv(REAL * iX_begin, REAL * iX_end,
	   REAL * iY_begin, REAL * iY_end,
	   const char * curv_name) : data() 
{
	X_begin = iX_begin;
	X_end = iX_end;
	Y_begin = iY_begin;
	Y_end = iY_end;
	setName(curv_name);
};

curv::~curv() {
	free(X_begin);
	free(Y_begin);
};

bool curv::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	minx = *std::min_element(X_begin, X_end);
	maxx = *std::max_element(X_begin, X_end);
	miny = *std::min_element(Y_begin, Y_end);
	maxy = *std::max_element(Y_begin, Y_end);
	return true;
};

int curv::size() const {
	if ((!X_begin) || (!X_end)) return 0;
	return X_end-X_begin;
};

REAL curv::minx() const {
	return *std::min_element(X_begin, X_end);
};

REAL curv::maxx() const {
	return *std::max_element(X_begin, X_end);
};

REAL curv::miny() const {
	return *std::min_element(Y_begin, Y_end);
};

REAL curv::maxy() const {
	return *std::max_element(Y_begin, Y_end);
};

REAL curv::length_xy() const {
	REAL len = REAL(0);
	
	const REAL * x_ptr = X_begin;
	const REAL * y_ptr = Y_begin;

	if (size() == 0)
		return len;

	while (x_ptr != X_end-1) {
		len += sqrt( (*x_ptr - *(x_ptr+1))*(*x_ptr - *(x_ptr+1)) + (*y_ptr - *(y_ptr+1))*(*y_ptr - *(y_ptr+1)) );
		x_ptr++;
		y_ptr++;
	}
	return len;
};

bool curv::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

}; // namespace surfit;

