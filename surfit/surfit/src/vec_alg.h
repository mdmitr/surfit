
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

#ifndef __surfit__vec_alg__
#define __surfit__vec_alg__

#include <math.h>

#include "fileio.h"
#include "real.h"

#include <float.h>

namespace surfit {

template <class V>
REAL norm2(const V * x, REAL undef = FLT_MAX) {
	REAL res = REAL(0);
	REAL val;
	int i;
	for (i = 0; i < x->size(); i++) {
		val = (*x)(i);
		if (val == undef)
			continue;
		res += val*val;
	};
	return sqrt(res);
}

template <class V>
REAL times(const V * x, const V * y) {
	REAL res = REAL(0);
	if (x->size() != y->size()) {
		writelog(SURFIT_ERROR,"Vectors times : wrong vectors size.");
		return res;
	};
	int i;
	for (i = 0; i < x->size(); i++) {
		res += (*x)(i)*(*y)(i);
	};
	return res;
};

REAL sum_value(const REAL * begin, const REAL * end, REAL undef);
REAL mean_value(const REAL * begin, const REAL * end, REAL undef);
REAL std_value(REAL mean_value, const REAL * begin, const REAL * end, REAL undef);

template <class T>
void minmax_value(const T * begin, const T * end, T & min_value, T & max_value) {
	max_value = *begin;
	min_value = *begin;
	const T * ptr;

	for (ptr = begin+1; ptr != end; ptr++)  {
        	min_value = MIN(*ptr,min_value);
		max_value = MAX(*ptr,max_value);
	}

	return;
};


}; // namespace surfit;

#endif

