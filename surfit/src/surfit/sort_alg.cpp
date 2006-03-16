
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

namespace surfit {

void getPointsInRect(REAL x_left, REAL x_right, REAL y_down, REAL y_up, 
		     REAL ** sortx_begin, REAL ** sortx_end,
		     REAL ** sorty_begin, REAL ** sorty_end,
		     REAL * beginx, REAL * beginy,
		     std::vector<unsigned int> &nn) {

	if (x_left > x_right) return;
	if (y_down > y_up) return;

	typedef REAL **  i_psVec;
	i_psVec i_sortx_from, i_sortx_to, ix;
	i_psVec i_sorty_from, i_sorty_to, iy;
	
	// Находим первую точку, меньше x_left
	i_sortx_from = std::lower_bound(sortx_begin,sortx_end,&x_left,ptr_vector_less);
	if (i_sortx_from == sortx_end) return;
	// Находим первую точку, больше x_right
	i_sortx_to = std::lower_bound(i_sortx_from,sortx_end,&x_right,ptr_vector_less);

	// Находим первую точку, меньше y_down
	i_sorty_from = std::lower_bound(sorty_begin,sorty_end,&y_down,ptr_vector_less);
	if (i_sortx_from == sortx_end) return;
	// Находим первую точку, больше y_up
	i_sorty_to = std::lower_bound(i_sorty_from,sorty_end,&y_up,ptr_vector_less);
	
	typedef std::vector<unsigned int> vecInt;

	vecInt nx(i_sortx_to-i_sortx_from);
	int pos = 0;
	for (ix = i_sortx_from; ix != i_sortx_to; ++ix) {
		nx[pos] = (*ix-beginx);
		pos++;
	}
	std::stable_sort(nx.begin(),nx.end());

	vecInt ny(i_sorty_to-i_sorty_from);
	pos = 0;
	for (iy = i_sorty_from; iy != i_sorty_to; ++iy) {
		ny[pos] = (*iy-beginy);
		if ( *iy-beginy == 0 ) {
			if (pos == 13497) {
				bool br = true;
			}
		}
		pos++;
	}
	std::stable_sort(ny.begin(),ny.end());
	
	std::set_intersection(nx.begin(),nx.end(),
                          ny.begin(),ny.end(), 
                          std::back_inserter(nn) );

};

void getPointsInRect(REAL x_left, REAL x_right, REAL y_down, REAL y_up, 
		     REAL ** sortx_begin, REAL ** sortx_end,
		     REAL ** sorty_begin, REAL ** sorty_end,
		     REAL * beginx, REAL * beginy,
		     std::vector<unsigned int> &nn,
		     REAL **& i_sortx_from, REAL **& i_sortx_to,
		     REAL **& i_sorty_from, REAL **& i_sorty_to) {

	if (x_left > x_right) return;
	if (y_down > y_up) return;

	typedef REAL **  i_psVec;
	i_psVec ix;
	i_psVec iy;
	
	// Находим первую точку, меньше x_left
	i_sortx_from = std::lower_bound(sortx_begin,sortx_end,&x_left,ptr_vector_less);
	if (i_sortx_from == sortx_end) return;
	// Находим первую точку, больше x_right
	i_sortx_to = std::lower_bound(i_sortx_from,sortx_end,&x_right,ptr_vector_less);

	// Находим первую точку, меньше y_down
	i_sorty_from = std::lower_bound(sorty_begin,sorty_end,&y_down,ptr_vector_less);
	if (i_sortx_from == sortx_end) return;
	// Находим первую точку, больше y_up
	i_sorty_to = std::lower_bound(i_sorty_from,sorty_end,&y_up,ptr_vector_less);
	
	typedef std::vector<unsigned int> vecInt;

	vecInt nx(i_sortx_to-i_sortx_from);
	int pos = 0;
	for (ix = i_sortx_from; ix != i_sortx_to; ++ix) {
		nx[pos] = (*ix-beginx);
		pos++;
	}
	std::stable_sort(nx.begin(),nx.end());

	vecInt ny(i_sorty_to-i_sorty_from);
	pos = 0;
	for (iy = i_sorty_from; iy != i_sorty_to; ++iy) {
		ny[pos] = (*iy-beginy);
		pos++;
	}
	std::stable_sort(ny.begin(),ny.end());
	
	std::set_intersection(nx.begin(),nx.end(),
                          ny.begin(),ny.end(), 
                          std::back_inserter(nn) );

};

void getPointsInSegment(REAL x_left, REAL x_right,
			REAL ** sortx_begin, REAL ** sortx_end,
			REAL * beginx,
			std::vector<unsigned int> &nn) {

	if (x_left > x_right) return;
	
	typedef REAL **  i_psVec;
	i_psVec i_sortx_from, i_sortx_to, ix;
		
	// Находим первую точку, меньше x_left
	i_sortx_from = std::lower_bound(sortx_begin,sortx_end,&x_left,ptr_vector_less);
	if (i_sortx_from == sortx_end) return;
	// Находим первую точку, больше x_right
	i_sortx_to = std::lower_bound(i_sortx_from,sortx_end,&x_right,ptr_vector_less);

	nn.resize(i_sortx_to-i_sortx_from);
	int pos = 0;
	for (ix = i_sortx_from; ix != i_sortx_to; ++ix) {
		nn[pos] = (*ix-beginx);
		pos++;
	}
	std::stable_sort(nn.begin(),nn.end());

};

void getPointsInSegment(REAL x_left, REAL x_right,
			REAL ** sort_begin, REAL ** sort_end,
			REAL * beginx,
			std::vector<unsigned int> &nn,
			REAL **& i_sort_from, REAL **& i_sort_to) {

	if (x_left > x_right) return;
	
	typedef REAL **  i_psVec;
	i_psVec ix;
		
	// Находим первую точку, меньше x_left
	i_sort_from = std::lower_bound(sort_begin,sort_end,&x_left,ptr_vector_less);
	if (i_sort_from == sort_end) return;
	// Находим первую точку, больше x_right
	i_sort_to = std::lower_bound(i_sort_from,sort_end,&x_right,ptr_vector_less);

	nn.resize(i_sort_to-i_sort_from);
	int pos = 0;
	for (ix = i_sort_from; ix != i_sort_to; ++ix) {
		nn[pos] = (*ix-beginx);
		pos++;
	}
	std::stable_sort(nn.begin(),nn.end());

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

