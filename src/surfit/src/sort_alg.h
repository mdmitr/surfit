
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

#ifndef __surfit_sort_alg__
#define __surfit_sort_alg__

#include <vector>
#include "vec.h"

namespace surfit {

//! function for vec sorting
inline
bool ptr_vector_less(REAL * it1, REAL * it2) 
{
	return *it1 < *it2;
};

//! function for vec sorting
inline
bool ptr_const_it_less(vec::const_iterator it1, vec::const_iterator it2) 
{
	return *it1 < *it2;
};

//! function for sorting by pointers
inline
bool ptr_less(int * it1, int * it2) 
{
	return *it1 < *it2;
};

//! function for sorting by pointers
inline
bool ptr_size_t_less(size_t * it1, size_t * it2) 
{
	return *it1 < *it2;
};

//! finds numbers of points inside rect
SURFIT_EXPORT
void getPointsInRect(const REAL x_left, const REAL x_right, const REAL y_down, const REAL y_up, 
		     const std::vector<size_t> & sortx,
		     const std::vector<size_t> & sorty,
		     const vec * X, const vec * Y,
		     std::vector<size_t> &nn);

}; // namespace surfit;

#endif

