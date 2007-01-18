
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

namespace surfit {

inline
bool ptr_vector_less(REAL * it1, REAL * it2) 
{
	return *it1 < *it2;
};

inline
bool ptr_less(int * it1, int * it2) 
{
	return *it1 < *it2;
};

inline
bool ptr_size_t_less(size_t * it1, size_t * it2) 
{
	return *it1 < *it2;
};

SURFIT_EXPORT
void getPointsInRect(REAL x_left, REAL x_right, REAL y_down, REAL y_up, 
		     REAL ** sortx_begin, REAL ** sortx_end,
		     REAL ** sorty_begin, REAL ** sorty_end,
		     REAL * beginx, REAL * beginy,
		     std::vector<size_t> &nn);

SURFIT_EXPORT
void getPointsInRect(REAL x_left, REAL x_right, REAL y_down, REAL y_up, 
		     REAL ** sortx_begin, REAL ** sortx_end,
		     REAL ** sorty_begin, REAL ** sorty_end,
		     REAL * beginx, REAL * beginy,
		     std::vector<size_t> &nn,
		     REAL **& i_sortx_begin, REAL **& i_sortx_end,
		     REAL **& i_sorty_begin, REAL **& i_sorty_end);

SURFIT_EXPORT
void getPointsInSegment(REAL x_left, REAL x_right, 
			REAL ** sortx_begin, REAL ** sortx_end,
			REAL * beginx,
			std::vector<size_t> &nn);

SURFIT_EXPORT
void getPointsInSegment(REAL x_left, REAL x_right,
			REAL ** sortx_begin, REAL ** sortx_end,
			REAL * beginx,
			std::vector<size_t> &nn,
			REAL **& i_sort_from, REAL **& i_sort_to);

}; // namespace surfit;

#endif

