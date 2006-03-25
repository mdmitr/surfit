
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

#include "sstuff_ie.h"
#include "vec_alg.h"

namespace surfit {

REAL sum_value(const REAL * begin, const REAL * end, REAL undef) {
	REAL res = REAL(0);
	const REAL * ptr;
	
	for (ptr = begin; ptr != end; ptr++)  {
		if (*ptr == undef)
			continue;
		res += *ptr;
	}
	
	return res;
	
};

REAL mean_value(const REAL * begin, const REAL * end, REAL undef) {
	REAL res = REAL(0);
	const REAL * ptr;
	int total = 0;
	
	for (ptr = begin; ptr != end; ptr++)  {
		if (*ptr == undef)
			continue;
		res += *ptr;
		total++;
	}
	
	return res/REAL(total);
	
};

REAL std_value(REAL mean_value, const REAL * begin, const REAL * end, REAL undef) {

	REAL res = REAL(0);

	const REAL * ptr;

	for (ptr = begin; ptr != end; ptr++) {
		if (*ptr == undef)
			continue;
		res += (*ptr - mean_value)*(*ptr - mean_value);
	}

	res /= REAL(end-begin);

	return REAL(sqrt(res));

};

REAL norm2(const REAL * x_begin, const REAL * x_end, REAL undef) {
	REAL res = REAL(0);
	REAL val;
	int i;
	int size = x_end-x_begin;
	for (i = 0; i < size; i++) {
		val = *(x_begin+i);
		if (val == undef)
			continue;
		res += val*val;
	};
	return (REAL)sqrt(res);
};

}; // namespace surfit


