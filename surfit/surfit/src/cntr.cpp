
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
#include "cntr.h"
#include "vec_alg.h"
#include <algorithm>

namespace surfit {

cntr::cntr(REAL * iX_begin, REAL * iX_end,
	   REAL * iY_begin, REAL * iY_end,
	   REAL * iZ_begin, REAL * iZ_end,
	   const char * cntr_name) : 
curv(iX_begin, iX_end,
	 iY_begin, iY_end,
	 cntr_name) 
{
	Z_begin = iZ_begin;
	Z_end = iZ_end;
};

cntr::~cntr() {
	free(Z_begin);
};

REAL cntr::minz() const {
	return *std::min_element(Z_begin, Z_end);
};

REAL cntr::maxz() const {
	return *std::max_element(Z_begin, Z_end);
};

bool cntr::getMinMaxZ(REAL & minz, REAL & maxz) const {
	minmax_value(Z_begin, Z_end, minz, maxz);
	return true;
};

void cntr::plus(REAL value) {
	REAL * ptr = NULL;
	for (ptr = Z_begin; ptr != Z_end; ptr++) 
		*ptr += value;
}; 
	
void cntr::minus(REAL value) {
	REAL * ptr = NULL;
	for (ptr = Z_begin; ptr != Z_end; ptr++) 
		*ptr -= value;
};

void cntr::mult(REAL value) {
	REAL * ptr = NULL;
	for (ptr = Z_begin; ptr != Z_end; ptr++) 
		*ptr *= value;
};

void cntr::div(REAL value) {
	REAL * ptr = NULL;
	for (ptr = Z_begin; ptr != Z_end; ptr++) 
		*ptr /= value;
};

}; // namespace surfit;

