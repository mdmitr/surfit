
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

#include "surfit_ie.h"
#include "sort_alg.h"

#include <algorithm>
#include <vector>

#include <math.h>
#include <float.h>
#include <limits.h>

namespace surfit {

struct search_points {

	search_points(const vec * iV, const REAL isearch_val)
	{
		V = iV;
		search_val = isearch_val;
	}

	bool operator ()( size_t left, size_t right )
	{
		if (left == UINT_MAX)
			return (search_val < (*V)(right));
		if (right == UINT_MAX)
			return ((*V)(left) < search_val);
		return ((*V)(left) < (*V)(right));
	}

private:
	const vec * V;
	REAL search_val;
};

void getPointsInRect(const REAL x_left, const REAL x_right, const REAL y_down, const REAL y_up, 
		     const std::vector<size_t> & sortx,
		     const std::vector<size_t> & sorty,
		     const vec * X, const vec * Y,
		     std::vector<size_t> &nn) {

	if (x_left > x_right) return;
	if (y_down > y_up) return;

	std::vector<size_t>::const_iterator i_sortx_from, i_sortx_to, ix;
	std::vector<size_t>::const_iterator i_sorty_from, i_sorty_to, iy;
	
	// find first point less than x_left
	{
		search_points search_x_left(X, x_left);
		i_sortx_from = std::lower_bound(sortx.begin(),sortx.end(),UINT_MAX,search_x_left);
		if (i_sortx_from == sortx.end()) return;
	}
	
	// find first point greater than x_right
	{
		search_points search_x_right(X, x_right);
		i_sortx_to = std::lower_bound(i_sortx_from,sortx.end(),UINT_MAX,search_x_right);
	}

	// find first point less than y_down
	{
		search_points search_y_down(Y, y_down);
		i_sorty_from = std::lower_bound(sorty.begin(),sorty.end(),UINT_MAX,search_y_down);
		if (i_sorty_from == sorty.end()) return;
	}
	// find first point greater than y_up
	{
		search_points search_y_up(Y, y_up);
		i_sorty_to = std::lower_bound(i_sorty_from,sorty.end(),UINT_MAX,search_y_up);
	}
	
	typedef std::vector<size_t> vecInt;

	vecInt nx(i_sortx_to-i_sortx_from);
	size_t pos = 0;
	for (ix = i_sortx_from; ix != i_sortx_to; ++ix) {
		nx[pos] = *ix;;
		pos++;
	}
	std::stable_sort(nx.begin(),nx.end());

	vecInt ny(i_sorty_to-i_sorty_from);
	pos = 0;
	for (iy = i_sorty_from; iy != i_sorty_to; ++iy) {
		ny[pos] = *iy;
		pos++;
	}
	std::stable_sort(ny.begin(),ny.end());
	
	std::set_intersection(nx.begin(),nx.end(),
                              ny.begin(),ny.end(), 
                              std::back_inserter(nn) );

};


/*
template <class T>
void merge_sort(T *& nns_solved, int divide_pos) {
	if (nns_solved->size() == 1)
		return;
	if ((divide_pos == nns_solved->size()) || (divide_pos == 0))
		return;
	T * buf = new T(nns_solved->size());

	T::iterator m1_begin, m1_end, m2_begin, m2_end, ptr;
	m1_begin = nns_solved->begin();
	m1_end = m1_begin + divide_pos;
	m2_begin = m1_end;
	m2_end = nns_solved->end();
	ptr = buf->begin();

	while (ptr != buf->end()) {

		if (*m1_begin <= *m2_begin) {
			*ptr = *m1_begin;
			ptr++;
			m1_begin++;
		} else {
			*ptr = *m2_begin;
			ptr++;
			m2_begin++;
		}
		
		if (m1_begin == m1_end) {
			// fill with m2
			while (m2_begin != m2_end) {
				*ptr = *m2_begin;
				ptr++;
				m2_begin++;
			}
			goto exit;
		}

		if (m2_begin == m2_end) {
			// fill with m1
			while (m1_begin != m1_end) {
				*ptr = *m1_begin;
				ptr++;
				m1_begin++;
			}
			goto exit;
		}

	}

exit:

	delete nns_solved;
	nns_solved = buf;

};
*/

}; // namespace surfit;

