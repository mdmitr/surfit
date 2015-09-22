
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

#ifndef __surfit__vec_alg__
#define __surfit__vec_alg__

/*! \file
    \brief declares some math functions for working with vec class
*/
#include <math.h>

#include "fileio.h"

#include <float.h>
#include "vec.h"

namespace surfit {

//! calculates L2 norm
template <class V>
REAL norm2(const V * x, REAL undef = FLT_MAX) {
	REAL res = REAL(0);
	REAL val;
	size_t i;
	for (i = 0; i < x->size(); i++) {
		val = (*x)(i);
		if (val == undef)
			continue;
		res += val*val;
	};
	return (REAL)sqrt(res);
};

//! calculates L2 norm
template <class iter>
REAL norm2(iter x_begin, iter x_end, REAL undef = FLT_MAX) {
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

//! calculates times of two vectors
template <class V>
REAL times(const V * x, const V * y) {
	REAL res = REAL(0);
	size_t i;
	for (i = 0; i < x->size(); i++) {
		res += (*x)(i)*(*y)(i);
	};
	return res;
};

//! calculates sum of all vector values
template<class iter>
REAL sum_value(iter begin, iter end, REAL undef)
{
	REAL res = REAL(0);
	iter ptr;
	
	for (ptr = begin; ptr != end; ptr++)  {
		if (*ptr == undef)
			continue;
		res += *ptr;
	}
	
	return res;
};

//! calculates mean of all vector values
template<class iter>
REAL mean_value(iter begin, iter end, REAL undef) {
	REAL res = REAL(0);
	iter ptr;
	int total = 0;
	
	for (ptr = begin; ptr != end; ptr++)  {
		if (*ptr == undef)
			continue;
		res += *ptr;
		total++;
	}
	
	return res/REAL(total);
};

//! calculates standart deviation from given mean_value for all vector values
template<class iter>
REAL std_value(REAL mean_value, iter begin, iter end, REAL undef) {

	REAL res = REAL(0);

	iter ptr;

	for (ptr = begin; ptr != end; ptr++) {
		if (*ptr == undef)
			continue;
		res += (*ptr - mean_value)*(*ptr - mean_value);
	}

	res /= REAL(end-begin);

	return REAL(sqrt(res));

};

//! calculates minimum and maximum values for all vector values
template<class iter, class val>
void minmax_value(iter begin, iter end, val & min_value, val & max_value, val undef_value) {
	
	iter ptr;

	max_value = undef_value;
	min_value = undef_value;

	for (ptr = begin+1; ptr != end; ptr++)  {
		if (*ptr != undef_value) {
			max_value = *ptr;
			min_value = *ptr;
			break;
		}
	}
	
	for (ptr = begin+1; ptr != end; ptr++)  {
		if (*ptr == undef_value)
			continue;
        	min_value = MIN(*ptr,min_value);
		max_value = MAX(*ptr,max_value);
	}

	return;
};

//! calculates minimum and maximum values for all vector values
template<class iter, class val>
void minmax_value(iter begin, iter end, val & min_value, val & max_value) {
	max_value = *begin;
	min_value = *begin;
	iter ptr;

	for (ptr = begin+1; ptr != end; ptr++)  {
        	min_value = MIN(*ptr,min_value);
		max_value = MAX(*ptr,max_value);
	}

	return;
};


}; // namespace surfit;

#endif

