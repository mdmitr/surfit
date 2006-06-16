
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

#include "fileio.h"
#include "bitvec.h"
#include "boolvec.h"

#include "grid_line.h"
#include "sort_alg.h"

// for floodfill
#include "grid.h"
#include <algorithm>
#include "area.h"

#include "grid_user.h"
#include "grid_line_user.h"

#include <assert.h>

namespace surfit {

grid_line * create_grid_line(std::vector<size_t> * ifirst, std::vector<size_t> * isecond) {
	return new grid_line(ifirst, isecond);
};

grid_line::grid_line(std::vector<size_t> * ifirst, std::vector<size_t> * isecond) : data("grid_line") {

	first = ifirst;
	second = isecond;
	
	sort_by_first_begin = NULL;
	sort_by_first_end = NULL;
	sort_by_second_begin = NULL;
	sort_by_second_end = NULL;

	sort();
	
};

grid_line::~grid_line() {
	delete first;
	delete second;
	free(sort_by_first_begin);
	free(sort_by_second_begin);
};

bool grid_line::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	return false;
};

size_t grid_line::size() const {
	if (first)
		return first->size();
	return 0;
};

void grid_line::sort() {
	if (first == NULL)
		return;
	// sorting
	int size = first->size();;

	free(sort_by_first_begin);
	free(sort_by_second_begin);
	
	sort_by_first_begin = (std::vector<size_t>::iterator*)malloc(size*sizeof(std::vector<size_t>::iterator *));
	sort_by_first_end = sort_by_first_begin + size;

	std::vector<size_t>::iterator ptr;
	std::vector<size_t>::iterator * pptr;
	for (ptr = first->begin(), pptr = sort_by_first_begin; ptr != first->end(); ptr++, pptr++)
		*pptr = ptr;
	
	std::sort(sort_by_first_begin, sort_by_first_end, ptr_size_t_less);

	sort_by_second_begin = (std::vector<size_t>::iterator *)malloc(size*sizeof(std::vector<size_t>::iterator *));
	sort_by_second_end = sort_by_second_begin + size;

	for (ptr = second->begin(), pptr = sort_by_second_begin; ptr != second->end(); ptr++, pptr++)
		*pptr = ptr;

	std::sort(sort_by_second_begin, sort_by_second_end, ptr_size_t_less);
};

void grid_line::add(std::vector<size_t> *& ifirst, std::vector<size_t> *& isecond) 
{
	if (ifirst == NULL)
		return;
	if (isecond == NULL)
		return;
	if (ifirst->size() != isecond->size())
		return;
	
	int add_size = ifirst->size();
	int old_size = size();

	first->resize(old_size+add_size);
	std::copy(ifirst->begin(), ifirst->begin() + add_size, first->begin() + old_size);
	//memcpy(first->begin() + old_size, ifirst->begin(), add_size*sizeof(int));
	delete ifirst;
	ifirst = NULL;
	
	second->resize(old_size+add_size);
	std::copy(isecond->begin(), isecond->begin() + add_size, second->begin() + old_size);
	//memcpy(second->begin() + old_size, isecond->begin(), add_size*sizeof(int));
	delete isecond;
	isecond = NULL;
	
	sort();
	
};

void grid_line::add(grid_line * line) {
	if (!line)
		return;
	add(line->first, line->second);
};

void grid_line::compress() {

	// make unique records!

};

void fault_points_D1(size_t n, size_t m, 
		     size_t NN, size_t MM, 
		     grid_line * fault,
		     bool & first_x, bool & second_x, 
		     bool & first_y, bool & second_y,
		     size_t offset_x, size_t offset_y) 
{
	if (!fault)
		return;

	size_t J = (n+offset_x) + (m+offset_y)*NN;
	size_t pos;
	size_t J2;
	size_t diff;

	// _first_

	size_t ** ptr_from = fault->sort_by_first_begin;
	size_t ** ptr;

	size_t pos2find;
	
first_find_J:

	if (first_y || second_y || first_x || second_x ) {
		pos2find = J; 
		
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       &pos2find, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				diff = abs(pos2find - J2);
				
				// vertical
				if (diff == 1) {
					if (J2 > pos2find)
						first_x = false;
					else
						second_x = false;
				}
				
				// horizontal
				if (diff == NN) {
					if (J2 > pos2find)
						first_y = false;
					else
						second_y = false;
				}
				
				ptr_from = ptr+1;
				goto first_find_J;
				
			}
		}
	}

	// _second_

	ptr_from = fault->sort_by_second_begin;

second_find_J:

	if (first_x || second_x || first_y || second_y) {
		
		pos2find = J; 
		
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       &pos2find, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				diff = abs(pos2find - J2);
				
				// vertical
				if (diff == 1) {
					if (J2 > pos2find)
						first_x = false;
					else
						second_x = false;
				}
				
				// horizontal
				if (diff == NN) {
					if (J2 > pos2find)
						first_y = false;
					else
						second_y = false;
				}
				
				ptr_from = ptr+1;
				goto second_find_J;
				
			}
		}
		
	}
	
	return;

};

void fault_points_D1_aniso(size_t n, size_t m, 
			   size_t NN, size_t MM, 
			   grid_line * fault,
			   bool & first_x, bool & second_x, 
			   bool & first_y, bool & second_y,
			   bool & first_xy, bool & first_yx,
			   bool & second_xy, bool & second_yx,
			   size_t offset_x, size_t offset_y) 
{
	if (!fault)
		return;

	size_t J = (n+offset_x) + (m+offset_y)*NN;
	size_t pos;
	size_t J2;
	size_t diff;

	// _first_

	std::vector<size_t>::iterator * ptr_from = fault->sort_by_first_begin;
	std::vector<size_t>::iterator * ptr;

	size_t pos2find;

first_find_J__NN:

	if ( second_xy ) {

		pos2find = J-NN; 
		std::vector<size_t>::iterator it(&pos2find);
				
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
								
				// vertical
				if (diff == 1) {
					if (J2 > pos2find) { // fault between $u_{i+1,j-}$ and $u_{i,j-1}$
						second_xy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto first_find_J__NN;
				
			}
		}

	}
	
first_find_J__1:

	if ( second_yx ) {

		pos2find = J-1; 
		std::vector<size_t>::iterator it(&pos2find);
				
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
								
				// horizontal
				if (diff == NN) {
					if (J2 > pos2find) { // fault between $u_{i-1,j}$ and $u_{i-1,j+1}$
						second_yx = false;
					}
				}
				
				ptr_from = ptr+1;
				goto first_find_J__1;
				
			}
		}

	}

first_find_J:

	if ( first_y || second_y || first_x || second_x || first_xy || first_yx || second_xy || second_yx) {
		pos2find = J; 
		std::vector<size_t>::iterator it(&pos2find);
				
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
								
				// vertical
				if (diff == 1) {
					if (J2 > pos2find) { // fault between $u_{i+1,j}$ and $u_{i,j}$
						first_x = false;
						first_xy = false;
						first_yx = false;
					} else { // fault between $u_{i-1.j}$ and $u_{i,j}$
						second_x = false;
						second_yx = false;
					}
				}
				
				// horizontal
				if (diff == NN) {
					if (J2 > pos2find) { // fault between $u_{i,j+1}$ and $u_{i,j}$
						first_y = false;
						first_xy = false;
						first_yx = false;
					} else { // fault between $u_{i,j-1}$ and $u_{i,j}$
						second_y = false;
						second_xy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto first_find_J;
				
			}
		}
	}

	// _second_

	ptr_from = fault->sort_by_second_begin;

second_find_J__NN:

	if ( second_xy ) {
		
		pos2find = J-NN; 
		std::vector<size_t>::iterator it(&pos2find);

		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
			
				// vertical
				if (diff == 1) {
					if (J2 > pos2find) { // fault between $u_{i+1,j-}$ and $u_{i,j-1}$
						second_xy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto second_find_J__NN;
				
			}
		}
		
	}

second_find_J__1:

	if ( second_yx ) {
		
		pos2find = J-1; 
		std::vector<size_t>::iterator it(&pos2find);

		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
			
				// horizontal
				if (diff == NN) {
					if (J2 > pos2find) { // fault between $u_{i-1,j}$ and $u_{i-1,j+1}$
						second_yx = false;
					}
				}
				
				ptr_from = ptr+1;
				goto second_find_J__1;
				
			}
		}
		
	}

second_find_J:

	if (first_x || second_x || first_y || second_y || first_xy || first_yx || second_xy || second_yx) {
		
		pos2find = J; 
		std::vector<size_t>::iterator it(&pos2find);

		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				// vertical
				if (diff == 1) {
					if (J2 > pos2find) { // fault between $u_{i+1,j}$ and $u_{i,j}$
						first_x = false;
						first_xy = false;
						first_yx = false;
					} else { // fault between $u_{i-1.j}$ and $u_{i,j}$
						second_x = false;
						second_yx = false;
					}
				}
				
				// horizontal
				if (diff == NN) {
					if (J2 > pos2find) { // fault between $u_{i,j+1}$ and $u_{i,j}$
						first_y = false;
						first_xy = false;
						first_yx = false;
					} else { // fault between $u_{i,j-1}$ and $u_{i,j}$
						second_y = false;
						second_xy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto second_find_J;
				
			}
		}
		
	}
	
	return;

};

void fault_points_D2(size_t n, size_t m, size_t NN, size_t MM, 
		     grid_line * fault,
		     bool & first_x,  bool & second_x,  bool & third_x, 
		     bool & first_xx, bool & second_xx,
		     bool & first_yy, bool & second_yy,
		     bool & first_y,  bool & second_y,  bool & third_y,
		     size_t offset_x , size_t offset_y)
{

	if (!fault)
		return;

	size_t J = (n+offset_x) + (m+offset_y)*NN;

	size_t J2;
	size_t diff;
	size_t pos;
	size_t pos2find;


	std::vector<size_t>::iterator * ptr_from = fault->sort_by_first_begin;
	std::vector<size_t>::iterator * ptr;

first_find_J__NN:

	if ( second_y || third_y || first_yy || second_yy ) {		
		pos2find = J - NN; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						first_yy = false;
					} else {
						second_yy = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						second_y = false;
						third_y = false;
						first_yy = false;
						second_yy = false;
					} else {
						third_y = false;
					}
				}
				
				ptr_from = ptr+1;
				goto first_find_J__NN;
				
			};
		}
		
	}

first_find_J__1:

	if ( second_x || third_x || first_xx || second_xx || second_yy )	{
		
		pos2find = J - 1; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						second_x = false;
						third_x = false;
						second_xx = false;
						second_yy = false;
					} else {
						third_x = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						second_xx = false;
					} else {
						second_yy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto first_find_J__1;
				
			};
		}
		
	}


first_find_J_1:

	if ( first_x || second_x || first_xx || first_yy )	{
		
		pos2find = J + 1; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						first_x = false;
					} else {
						first_x = false;
						second_x = false;
						first_xx = false;
						first_yy = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						first_xx = false;
					} else {
						first_yy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto first_find_J_1;
				
			};
		}
	}

first_find_J_NN:

	if ( first_y || second_y || first_xx || second_xx ) {		
		pos2find = J + NN; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_first_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_first_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->first->begin();
				J2 = *(fault->second->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						first_xx = false;
					} else {
						second_xx = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						first_y = false; 
					} else {
						first_y = false;
						second_y = false;
						first_xx = false;
						second_xx = false;
					}
				}
				
				ptr_from = ptr+1;
				goto first_find_J_NN;
				
			};
		}
		
	}


ptr_from = fault->sort_by_second_begin;

second_find_J__NN:

	if ( second_y || third_y || first_yy || second_yy ) {
		
		pos2find = J - NN; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						first_yy = false;
					} else {
						second_yy = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						second_y = false;
						third_y = false;
						first_yy = false;
						second_yy = false;
					} else {
						third_y = false;
					}
				}
				
				ptr_from = ptr+1;
				goto second_find_J__NN;
				
			};
		}
		
	}

second_find_J__1:

	if ( second_x || third_x || first_xx || second_xx || second_yy ) {
		
		pos2find = J - 1; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						second_x = false;
						third_x = false;
						second_xx = false;
						second_yy = false;
					} else {
						third_x = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						second_xx = false;
					} else {
						second_yy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto second_find_J__1;
				
			};
		}
		
	}

second_find_J_1:

	if ( first_x || second_x || first_xx || first_yy )	{
		
		pos2find = J + 1; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						first_x = false;
					} else {
						first_x = false;
						second_x = false;
						first_xx = false;
						first_yy = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						first_xx = false;
					} else {
						first_yy = false;
					}
				}
				
				ptr_from = ptr+1;
				goto second_find_J_1;
				
			};
		}
	}

second_find_J_NN:

	if ( first_y || second_y || first_xx || second_xx ) {		
		pos2find = J + NN; 
		std::vector<size_t>::iterator it(&pos2find);
		ptr = std::lower_bound(ptr_from, 
				       fault->sort_by_second_end, 
				       it, 
				       ptr_size_t_less);
		
		if (ptr && (ptr != fault->sort_by_second_end)) {
			if (**ptr == pos2find) {
				
				pos = *ptr - fault->second->begin();
				J2 = *(fault->first->begin() + pos);
				if (pos2find > J2)
					diff = pos2find - J2;
				else 
					diff = J2 - pos2find;
				
				if (diff == 1) {  // vertical fault line
					if (J2 > pos2find) {
						first_xx = false;
					} else {
						second_xx = false;
					}
				} else { // horizontal fault line
					if (J2 > pos2find) {
						first_y = false; 
					} else {
						first_y = false;
						second_y = false;
						first_xx = false;
						second_xx = false;
					}
				}
				
				ptr_from = ptr+1;
				goto second_find_J_NN;
				
			};
		}
		
	}

	return;

};

bool check_for_node(grid_line * fault, size_t nn) {
	
	std::vector<size_t>::iterator * ptr;
	std::vector<size_t>::iterator it(&nn);
	ptr = std::lower_bound(fault->sort_by_first_begin, 
			       fault->sort_by_first_end, 
	                       it, 
			       ptr_size_t_less);

	if (ptr && (ptr != fault->sort_by_first_end))
		if (**ptr == nn)
			return true;

	ptr = std::lower_bound(fault->sort_by_second_begin, 
			       fault->sort_by_second_end, 
	                       it, 
			       ptr_size_t_less);

	if (ptr && (ptr != fault->sort_by_second_end))
		if (**ptr == nn)
			return true;

    return false;

};



bool check_for_pair(grid_line * fault, size_t nn1, size_t nn2) {
	
	std::vector<size_t>::iterator * ptr;

	std::vector<size_t>::iterator * ptr_from = fault->sort_by_first_begin;
	size_t pos;

	if (nn1 < nn2) {
		size_t temp = nn2;
		nn2 = nn1;
		nn1 = temp;
	}

	std::vector<size_t>::iterator it1(&nn1);
	std::vector<size_t>::iterator it2(&nn2);

first_again_nn1:
	
	ptr = std::lower_bound(ptr_from, 
			       fault->sort_by_first_end, 
	                       it1, 
			       ptr_size_t_less);

	if (ptr && (ptr != fault->sort_by_first_end)) {
		if (**ptr == nn1) {
			pos = *ptr - fault->first->begin();
			if ( nn2 == *(fault->second->begin() + pos) )
				return true;
			ptr_from = ptr+1;
			goto first_again_nn1;
		}
	}

	ptr_from = ptr; //fault->sort_by_first_begin;

first_again_nn2:
	
	
	ptr = std::lower_bound(ptr_from, 
			       fault->sort_by_first_end, 
	                       it2, 
			       ptr_size_t_less);

	if (ptr && (ptr != fault->sort_by_first_end)) {
		if (**ptr == nn2) {
			pos = *ptr - fault->first->begin();
			if ( nn1 == *(fault->second->begin() + pos) )
				return true;
			ptr_from = ptr+1;
			goto first_again_nn2;
		}
	}

	ptr_from = fault->sort_by_second_begin;

second_again_nn1:

	ptr = std::lower_bound(ptr_from, 
			       fault->sort_by_second_end, 
	                       it1, 
			       ptr_size_t_less);

	if (ptr && (ptr != fault->sort_by_second_end)) {
		if (**ptr == nn1) {
			pos = *ptr - fault->second->begin();
			if ( nn2 == *(fault->first->begin() + pos) )
				return true;
			ptr_from = ptr+1;
			goto second_again_nn1;
		}
	}

	ptr_from = ptr;//fault->sort_by_second_begin;

second_again_nn2:

	ptr = std::lower_bound(ptr_from, 
			       fault->sort_by_second_end, 
	                       it2, 
			       ptr_size_t_less);

	if (ptr && (ptr != fault->sort_by_second_end)) {
		if (**ptr == nn2) {
			pos = *ptr - fault->second->begin();
			if ( nn1 == *(fault->first->begin() + pos) )
				return true;
			ptr_from = ptr+1;
			goto second_again_nn2;
		}
	}

	return false;

};

void flood_fill(d_grid * grd,
		grid_line * line, 
		std::vector<short int> * data,
		size_t fill_pos,
		short int fill_val,
		const bitvec * mask_undefined) {

	// floodfill algorithm
	size_t max_i = grd->getCountX();
	size_t NN = max_i;
	size_t max_j = grd->getCountY();
	size_t MM = max_j;
	size_t grid_size = max_i*max_j;

	if (mask_undefined)
		assert(grid_size == mask_undefined->size());
	
	if (data->size() != grid_size)
		return;

	size_t fill_i, fill_j;
	one2two(fill_pos, fill_i, fill_j, NN, MM);
	 
	std::vector<size_t> * flood_points = new std::vector<size_t>();
	size_t push_pos, push_pos2;
	flood_points->push_back(fill_pos);
	
	size_t max_points = 1;
	size_t i;
	for (i = 0; i < max_points; i++) {
		
		bool flood;

		size_t pos = (*flood_points)[i];

		if ( (*data)[pos] != 0 )
			continue;

		one2two(pos, fill_i, fill_j, NN, MM);
		
		// find left edge
		size_t left_i = fill_i;
		size_t left_j = fill_j;
				
		while (true) {
			
			if ((left_i >= 0) && (left_i < max_i) && (left_j >= 0) && (left_j < max_j)) {
				two2one(push_pos, left_i, left_j, NN, MM);
				if ( (*data)[push_pos] == 0 )
					(*data)[push_pos] = fill_val;
			}
			else
				break;
			
			left_i--;
			two2one(push_pos, left_i, left_j, NN, MM);
			two2one(push_pos2, left_i + 1, left_j, NN, MM);

			bool bound = ((left_i >= 0) && (left_i < max_i) && (left_j >= 0) && (left_j < max_j));
			if (!bound)
				break;
			
			flood = true;
			
			if (line)
				flood = !check_for_pair(line, push_pos, push_pos2);// check_flood(left_i, left_j, left_i+1, left_j);

			if (mask_undefined && flood && bound) {
				flood = flood && !mask_undefined->get(push_pos);
			}
			
			if (flood && bound)
				flood = flood && ( (*data)[push_pos] == 0 );
			
			if (!flood)
				break;
		};
		left_i++;

		// find right edge
		size_t right_i = fill_i;
		size_t right_j = fill_j;
		
		// find right edge
		while (true) {
			
			right_i++;
			two2one(push_pos, right_i, right_j, NN, MM);
			two2one(push_pos2, right_i - 1, right_j, NN, MM);
			
			flood = true;
			bool bound = ((right_i >= 0) && (right_i < max_i) && (right_j >= 0) && (right_j < max_j));
			if (!bound)
				break;
			
			if (line)
				flood = !check_for_pair(line, push_pos, push_pos2);//check_flood(right_i, right_j, right_i-1, right_j);
			
			if (mask_undefined && flood && bound) {
				flood = flood && !mask_undefined->get(push_pos);
			}
							
			if (flood && bound)
			    	flood = flood && ( (*data)[push_pos] == 0 );
			
			if (!flood)
				break;

			if (bound) {
				if ( (*data)[push_pos] == 0 )
					(*data)[push_pos] = fill_val;
			}
			else
				break;

		};
		right_i--;
		
		// start the loop upwards and downwards
		size_t i_pos;
		for (i_pos = left_i; i_pos <= right_i; i_pos++) {

			// upwards
			two2one(push_pos, i_pos, fill_j+1, NN, MM);
			two2one(push_pos2, i_pos, fill_j, NN, MM);
			if (( push_pos >= 0 ) && (push_pos < grid_size)) {
				if ( (*data)[push_pos] == 0 ) {
					
					flood = true;
					
					if (line)
						flood = !check_for_pair(line, push_pos2, push_pos);
					
					if (mask_undefined && flood && (push_pos > 0)) {
						flood = flood && !mask_undefined->get(push_pos);
					}
						
					if (flood && (fill_j+1 < MM))
						flood = flood && ( (*data)[push_pos] == 0 );
					
					if (flood && (fill_j+1 < MM))
						flood_points->push_back(push_pos);
				}
			}
			
			// downwards
			two2one(push_pos, i_pos, fill_j-1, NN, MM);
			two2one(push_pos2, i_pos, fill_j, NN, MM);
			if (( push_pos >= 0 ) && (push_pos < grid_size)) {
				if ( (*data)[push_pos] == 0 ) {
					
					flood = true;
					
					if (line)
						flood = !check_for_pair(line, push_pos2, push_pos);
					
					if (mask_undefined && flood && (push_pos > 0)) {
						flood = flood && !mask_undefined->get(push_pos);
					}

					if (flood && (fill_j-1 > 0))
						flood = flood && ( (*data)[push_pos] == 0 );
					
					if (flood && (fill_j-1 > 0))
						flood_points->push_back(push_pos);
				}
			}

		}

		max_points = flood_points->size();
				
	}

	delete flood_points;
		
	return;
};

void flood_fill_boolvec(d_grid * grd,
			grid_line * line, 
			boolvec * data,
			size_t fill_pos,
			const bitvec * mask_undefined) {

	// floodfill algorithm
	size_t max_i = grd->getCountX();
	size_t NN = max_i;
	size_t max_j = grd->getCountY();
	size_t grid_size = max_i*max_j;

	if (data->size() != grid_size)
		return;

	size_t fill_i = fill_pos % NN;
	size_t fill_j = (fill_pos - fill_i)/NN;

	std::vector<size_t> * flood_points = new std::vector<size_t>();
	flood_points->push_back(fill_i + NN * fill_j);

	size_t max_points = 1;
	size_t i;
	for (i = 0; i < max_points; i++) {
		
		bool flood;

		size_t pos = (*flood_points)[i];

		if ( (*data)(pos) != false )
			continue;

		fill_i = pos % NN;
		fill_j = (pos - fill_i)/NN;

		size_t left_i = fill_i;
		size_t left_j = fill_j;
		
		// find left edge
		while (true) {
			
			if ((left_i >= 0) && (left_i < max_i) && (left_j >= 0) && (left_j < max_j)) {
				if ( (*data)(left_i + left_j*NN) == false )
					(*data)(left_i + left_j*NN) = true;
			}
			else
				break;
			
			left_i--;
			flood = check_for_pair(line, left_i + left_j*NN, left_i + left_j*NN + 1);// check_flood(left_i, left_j, left_i+1, left_j);
			if (flood)
				break;
		};
		left_i++;

		size_t right_i = fill_i, right_j = fill_j;
		
		// find right edge
		while (true) {
			
			right_i++;
			flood = check_for_pair(line, right_i + right_j*NN, right_i + right_j*NN - 1);//check_flood(right_i, right_j, right_i-1, right_j);
			if (flood)
				break;

			if ((right_i >= 0) && (right_i < max_i) && (right_j >= 0) && (right_j < max_j)) {
				if ( (*data)(right_i + right_j*NN) == false )
					(*data)(right_i + right_j*NN) = true;
			}
			else
				break;

		};
		right_i--;
		
		// start the loop upwards and downwards
		size_t i_pos;
		size_t new_pos;
		for (i_pos = left_i; i_pos <= right_i; i_pos++) {

			// upwards
			new_pos = i_pos+NN + fill_j*NN;
			if (( new_pos >= 0 ) && (new_pos < grid_size)) {
				if ( (*data)(new_pos) == false ) {
					flood = check_for_pair(line, i_pos + fill_j*NN, new_pos);
					if (!flood)
						flood_points->push_back(new_pos);
				}
			}
			
			// downwards
			new_pos = i_pos-NN + fill_j*NN;
			if (( new_pos >= 0 ) && (new_pos < grid_size)) {
				if ( (*data)(new_pos) == false ) {
					flood = check_for_pair(line, i_pos + fill_j*NN, new_pos);
					if (!flood)
						flood_points->push_back(new_pos);
				}
			}

		}

		max_points = flood_points->size();
				
	}

	delete flood_points;
		
	return;
};


std::vector<short int>::iterator 
find_first(std::vector<short int>::iterator it1, 
	   std::vector<short int>::iterator it2,
	   short int val) {

	while (it1 != it2) {
		if (*it1 == val)
			return it1;
		it1++;
	}

	return it2;

};

void fill_all_areas(std::vector<short int> *& flood_areas, 
		    d_grid * grd, 
		    grid_line * line, 
		    int & flood_areas_cnt,
		    const bitvec * mask_undefined)
{
	
	size_t pos ;

	size_t max_pos = grd->getCountX()*grd->getCountY();

	if (!flood_areas)
		flood_areas = new std::vector<short int>(max_pos);
	std::vector<short int>::iterator it;

	short int color = 1;

	if (!line && !mask_undefined)
	{
		size_t i;
		for (i = 0; i < flood_areas->size(); i++) {
			(*flood_areas)[i] = color;
			flood_areas_cnt = 1;
		}
		return;
	}

	if (mask_undefined) {
		for (pos = 0; pos < max_pos; pos++) {
			if (mask_undefined->get(pos))
				(*flood_areas)[pos] = -1;
		}
	}

	pos = 0;
	while ( pos < max_pos) {
		
		flood_fill(grd, line, flood_areas, pos, color, NULL);

		short int val = 0;
		
		it = find_first(flood_areas->begin()+pos, flood_areas->end(), val);

		if (it == flood_areas->end())
			break;

		pos = it - flood_areas->begin();
		color++;

	}

	flood_areas_cnt = color;

	/*
	FILE * ff = fopen("c:\\qqq.m","w+");
	fprintf(ff,"hold on\n");
				
	// draw grid
	{
		int i;
		REAL x0, y0;
		grd->getCoordNode(0,0,x0,y0);
		REAL xN, yM;
		grd->getCoordNode(grd->getCountX()-1,grd->getCountY()-1,xN,yM);
		
		REAL stepX = grd->stepX/REAL(2);
		REAL stepY = grd->stepY/REAL(2);
		
		REAL x_0, x_1;
		REAL y_0, y_1;
		
		y_0 = y0 - stepY;
		y_1 = yM + stepY;
		for (i = 0; i < grd->getCountX()+1; i++) {
			x_0 = grd->getCoordNodeX(i)-stepX;
			x_1 = x_0;//grd->getCoordNodeX(i+1)+stepX;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		x_0 = x0 - stepX;
		x_1 = xN + stepX;
		for (i = 0; i < grd->getCountY()+1; i++) {
			y_0 = grd->getCoordNodeY(i)-stepY;
			y_1 = y_0;//grd->getCoordNodeY(i+1)+stepY;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,yM);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,yM);
		
	}

	fflush(ff);
				
	// draw fault line
	if (line)
	{
		int fl_size = line->first_end - line->first->begin();
		int i;
		int J1, J2;
		for (i = 0; i < fl_size; i++) {
			J1 = *(line->first->begin() + i);
			J2 = *(line->second->begin() + i);
			
			REAL x, y;
			int NN = grd->getCountX();
			
			REAL stepX2 = grd->stepX/REAL(2);
			REAL stepY2 = grd->stepY/REAL(2);
			
			int n = J1 % NN;
			int m = (J1 - n)/NN;
			
			grd->getCoordNode(n,m,x,y);
			
			int diff = (J2-J1);
			
			// right line
			if (diff == 1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x+stepX2, x+stepX2, y-stepY2, y+stepY2);
			}
			
			// left line
			if (diff == -1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x-stepX2, y-stepY2, y+stepY2);
			}
			
			// up line 
			if (diff == NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y+stepY2, y+stepY2);
			}
			
			// down line
			if (diff == -NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y-stepY2, y-stepY2);
			}
			
		}
	}

	fflush(ff);


	int nn = grd->getCountX();
	for (pos = 0; pos < max_pos; pos++) {
		
		// paint flowed area
		
			int n = pos % nn;
			int m = (pos - n)/nn;
			
			REAL x, y;
			grd->getCoordNode(n,m,x,y);
			
			REAL stepX = grd->stepX/REAL(2);
			REAL stepY = grd->stepY/REAL(2);
			
			REAL x_, y_;
			
			y_ = y - stepY;
			x_ = x - stepX;

			int j = (*flood_areas)[pos];

			while (j > 7)
				j-=7;
	
			if (j == 1)
				fprintf(ff,"plot(%lf, %lf,'.','color','green');\n",x,y);
			if (j == 2)
				fprintf(ff,"plot(%lf, %lf,'.','color','red');\n",x,y);
			if (j == 3)
				fprintf(ff,"plot(%lf, %lf,'.','color','blue');\n",x,y);
			if (j == 4)
				fprintf(ff,"plot(%lf, %lf,'.','color','magenta');\n",x,y);
			if (j == 5)
				fprintf(ff,"plot(%lf, %lf,'.','color','cyan');\n",x,y);
			if (j == 6)
				fprintf(ff,"plot(%lf, %lf,'.','color','black');\n",x,y);
			if (j == 7)
				fprintf(ff,"plot(%lf, %lf,'.','color','yellow');\n",x,y);
				
	}
		
	fclose(ff);
	*/

	return;

};

std::vector<size_t> * nodes_in_curv(grid_line * line, d_grid * grd, bitvec * mask_undefined) {

	if (!line)
		return NULL;

	if (line->size() == 0)
		return NULL;

	std::vector<size_t> * res = new std::vector<size_t>;

	size_t min_i = UINT_MAX, min_j = UINT_MAX, max_i = 0, max_j = 0;

	size_t i, j; 
	size_t pos;
	size_t pos_i, pos_j;
	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();
	for (i = 0; i < line->size(); i++) {
		pos = *(line->first->begin()+i);
		pos_i = pos % NN;
		pos_j = (pos - pos_i)/NN;
		min_i = MIN(min_i, pos_i);
		max_i = MAX(max_i, pos_i);
		min_j = MIN(min_j, pos_j);
		max_j = MAX(max_j, pos_j);

		pos = *(line->second->begin()+i);
		pos_i = pos % NN;
		pos_j = (pos - pos_i)/NN;
		min_i = MIN(min_i, pos_i);
		max_i = MAX(max_i, pos_i);
		min_j = MIN(min_j, pos_j);
		max_j = MAX(max_j, pos_j);
	};

	min_i = MAX(min_i, 0);
	min_j = MAX(min_j, 0);
	max_i = MIN(max_i, NN-1);
	max_j = MIN(max_j, MM-1);

	// расширяем сознание
	min_i--;
	min_j--;
	max_i++;
	max_j++;

	size_t nn = max_i-min_i+1;
	size_t mm = max_j-min_j+1;

	d_grid * small_grd = create_grid(grd);

	REAL old_startX = grd->startX;
	REAL old_endX = grd->endX;
	REAL old_startY = grd->startY;
	REAL old_endY = grd->endY;

	grd->startX += grd->stepX*min_i;
	grd->startY += grd->stepY*min_j;
	grd->endX    = grd->startX + grd->stepX*(nn-1);
	grd->endY    = grd->startY + grd->stepY*(mm-1);

	nn = grd->getCountX();
	mm = grd->getCountY();

	for (i = 0; i < line->size(); i++) {
		pos = *(line->first->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		pos_i -= min_i;
		pos_j -= min_j;
		two2one(pos, pos_i, pos_j, nn, mm);
		*(line->first->begin()+i) = pos;

		pos = *(line->second->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		pos_i -= min_i;
		pos_j -= min_j;
		two2one(pos, pos_i, pos_j, nn, mm);
		*(line->second->begin()+i) = pos;
	};

	line->sort();	

/*
{
FILE * ff = fopen("c:\\qqq.m","w+");
	fprintf(ff,"hold on\n");

	// draw grid
	{
		int i;
		REAL x0, y0;
		small_grd->getCoordNode(0,0,x0,y0);
		REAL xN, yM;
		small_grd->getCoordNode(small_grd->getCountX()-1,small_grd->getCountY()-1,xN,yM);
		
		REAL stepX = small_grd->stepX/REAL(2);
		REAL stepY = small_grd->stepY/REAL(2);
		
		REAL x_0, x_1;
		REAL y_0, y_1;
		
		y_0 = y0 - stepY;
		y_1 = yM + stepY;
		for (i = 0; i < small_grd->getCountX()+1; i++) {
			x_0 = small_grd->getCoordNodeX(i)-stepX;
			x_1 = x_0;//small_grd->getCoordNodeX(i+1)+stepX;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','magenta');\n",x_0,x_1,y_0,y_1);
		}
		
		x_0 = x0 - stepX;
		x_1 = xN + stepX;
		for (i = 0; i < small_grd->getCountY()+1; i++) {
			y_0 = small_grd->getCoordNodeY(i)-stepY;
			y_1 = y_0;//small_grd->getCoordNodeY(i+1)+stepY;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','magenta');\n",x_0,x_1,y_0,y_1);
		}
		
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,yM);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,yM);
		
	}

	fflush(ff);
				
	// draw grid
	{
		int i;
		REAL x0, y0;
		grd->getCoordNode(0,0,x0,y0);
		REAL xN, yM;
		grd->getCoordNode(grd->getCountX()-1,grd->getCountY()-1,xN,yM);
		
		REAL stepX = grd->stepX/REAL(2);
		REAL stepY = grd->stepY/REAL(2);
		
		REAL x_0, x_1;
		REAL y_0, y_1;
		
		y_0 = y0 - stepY;
		y_1 = yM + stepY;
		for (i = 0; i < grd->getCountX()+1; i++) {
			x_0 = grd->getCoordNodeX(i)-stepX;
			x_1 = x_0;//grd->getCoordNodeX(i+1)+stepX;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		x_0 = x0 - stepX;
		x_1 = xN + stepX;
		for (i = 0; i < grd->getCountY()+1; i++) {
			y_0 = grd->getCoordNodeY(i)-stepY;
			y_1 = y_0;//grd->getCoordNodeY(i+1)+stepY;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,yM);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,yM);
		
	}

	fflush(ff);

					
	// draw fault line
	{
		
		int fl_size = line->first_end - line->first->begin();
		int i;
		int J1, J2;
		for (i = 0; i < fl_size; i++) {
			J1 = *(line->first->begin() + i);
			J2 = *(line->second->begin() + i);
			
			REAL x, y;
			int NN = grd->getCountX();
			
			REAL stepX2 = grd->stepX/REAL(2);
			REAL stepY2 = grd->stepY/REAL(2);
			
			int n1,m1;
			one2two(J1, n1, m1, NN, MM);
			grd->getCoordNode(n1,m1,x,y);

			int n2,m2;
			one2two(J2, n2, m2, NN, MM);
			
			//int diff = (J2-J1);
			int diff = 0;
			if (n2 > n1)
				diff = 1;
			if (n2 < n1)
				diff = -1;
			if (m2 > m1)
				diff = NN;
			if (m2 < m1)
				diff = -NN;
			
			// right line
			if (diff == 1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x+stepX2, x+stepX2, y-stepY2, y+stepY2);
			}
			
			// left line
			if (diff == -1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x-stepX2, y-stepY2, y+stepY2);
			}
			
			// up line 
			if (diff == NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y+stepY2, y+stepY2);
			}
			
			// down line
			if (diff == -NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y-stepY2, y-stepY2);
			}
			
		}
		
	}

	fflush(ff);
}
*/
	std::vector<short int> * data = new std::vector<short int>(nn*mm);

	// check for undefined elements in sub_grid!
	bool exists_undef = false;
	if (mask_undefined) {
		size_t n, m, mask_pos;
		for (j = 0; j < mm; j++) {
			for (i = 0; i < nn; i++) {
				n = i; m = j;
				two2two(n, m, grd, small_grd);
				if ( grid_bound2(n, m, NN, MM) ) {
					two2one(mask_pos, n, m, NN, MM);
					if (mask_undefined->get(mask_pos)) {
						exists_undef = true;
						break;
					}
				}
			}
		}
	}

	if (!exists_undef)
		flood_fill(grd,
			   line, 
			   data,
			   0,
			   1,
			   NULL);
	else {
		bitvec * local_mask_undefined = create_bitvec(nn*mm);
		local_mask_undefined->init_false();
		size_t n, m, mask_pos, pos;
		for (j = min_j+1; j < max_j-1; j++) {
			for (i = min_i+1; i < max_i-1; i++) {
				n = i; m = j;
				two2two(n, m, grd, small_grd);
				if ( grid_bound2(n, m, NN, MM) ) {
					two2one(mask_pos, n, m, NN, MM);
					if (mask_undefined->get(mask_pos)) {
						if (grid_bound2(i, j, nn, mm)) {
							two2one(pos, i, j, nn, mm);
							local_mask_undefined->set_true(pos);
						}
					}
				}
			}
		}
		flood_fill(grd,
			   line, 
			   data,
			   0,
			   1,
			   local_mask_undefined);
		if (local_mask_undefined)
			local_mask_undefined->release();
	}

	int val;
	for (j = 0; j < mm; j++) {
		for (i = 0; i < nn; i++) {
			pos = i + j*nn;
			val = (*data)[pos];
			if ( val == 0) {
				pos = (i + min_i) + (j + min_j)*NN;
				if ( (i + min_i >= 0) && (i + min_i < NN) &&
				     (j + min_j >= 0) && (j + min_j < MM) )
				{
					res->push_back(pos);
				}
			}
		}
	}

	delete data;

	for (i = 0; i < line->size(); i++) {
		pos = *(line->first->begin()+i);
		one2two(pos, pos_i, pos_j, nn, mm);
		pos_i += min_i;
		pos_j += min_j;
		two2one(pos, pos_i, pos_j, NN, MM);
		*(line->first->begin()+i) = pos;

		pos = *(line->second->begin()+i);
		one2two(pos, pos_i, pos_j, nn, mm);
		pos_i += min_i;
		pos_j += min_j;
		two2one(pos, pos_i, pos_j, NN, MM);
		*(line->second->begin()+i) = pos;
	};

	line->sort();
	
	grd->startX = old_startX;
	grd->endX = old_endX;
	grd->startY = old_startY;
	grd->endY = old_endY;

	std::sort(res->begin(), res->end());
	
	// Рисовка

	/*
	FILE * ff = fopen("c:\\qqq.m","w+");
	fprintf(ff,"hold on\n");
				
	// draw grid
	{
		int i;
		REAL x0, y0;
		grd->getCoordNode(0,0,x0,y0);
		REAL xN, yM;
		grd->getCoordNode(grd->getCountX()-1,grd->getCountY()-1,xN,yM);
		
		REAL stepX = grd->stepX/REAL(2);
		REAL stepY = grd->stepY/REAL(2);
		
		REAL x_0, x_1;
		REAL y_0, y_1;
		
		y_0 = y0 - stepY;
		y_1 = yM + stepY;
		for (i = 0; i < grd->getCountX()+1; i++) {
			x_0 = grd->getCoordNodeX(i)-stepX;
			x_1 = x_0;//grd->getCoordNodeX(i+1)+stepX;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		x_0 = x0 - stepX;
		x_1 = xN + stepX;
		for (i = 0; i < grd->getCountY()+1; i++) {
			y_0 = grd->getCoordNodeY(i)-stepY;
			y_1 = y_0;//grd->getCoordNodeY(i+1)+stepY;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,yM);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,yM);
		
	}

	fflush(ff);
				
	// draw fault line
	{
		
		int fl_size = line->first_end - line->first->begin();
		int i;
		int J1, J2;
		for (i = 0; i < fl_size; i++) {
			J1 = *(line->first->begin() + i);
			J2 = *(line->second->begin() + i);
			
			REAL x, y;
			int NN = grd->getCountX();
			
			REAL stepX2 = grd->stepX/REAL(2);
			REAL stepY2 = grd->stepY/REAL(2);
			
			int n1,m1;
			one2two(J1, n1, m1, NN, MM);
			grd->getCoordNode(n1,m1,x,y);

			int n2,m2;
			one2two(J2, n2, m2, NN, MM);
			
			//int diff = (J2-J1);
			int diff = 0;
			if (n2 > n1)
				diff = 1;
			if (n2 < n1)
				diff = -1;
			if (m2 > m1)
				diff = NN;
			if (m2 < m1)
				diff = -NN;
			
			// right line
			if (diff == 1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x+stepX2, x+stepX2, y-stepY2, y+stepY2);
			}
			
			// left line
			if (diff == -1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x-stepX2, y-stepY2, y+stepY2);
			}
			
			// up line 
			if (diff == NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y+stepY2, y+stepY2);
			}
			
			// down line
			if (diff == -NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y-stepY2, y-stepY2);
			}
			
		}
		
	}

	fflush(ff);

	
	for (i = 0; i < res->size(); i++) {
		
		// paint flowed area
		
		int pos = (*res)[i];
		int n,m;
		one2two(pos, n, m, NN, MM);
			
		REAL x, y;
		grd->getCoordNode(n,m,x,y);
		
		REAL stepX = grd->stepX/REAL(2);
		REAL stepY = grd->stepY/REAL(2);
		
		REAL x_, y_;
		
		y_ = y - stepY;
		x_ = x - stepX;
		
		//int j = (*data)[pos];
		int j = 1;
		
		while (j > 7)
			j-=7;
		
		if (j == 1)
			fprintf(ff,"plot(%lf, %lf,'.','color','green');\n",x,y);
		if (j == 2)
			fprintf(ff,"plot(%lf, %lf,'.','color','red');\n",x,y);
		if (j == 3)
			fprintf(ff,"plot(%lf, %lf,'.','color','blue');\n",x,y);
		if (j == 4)
			fprintf(ff,"plot(%lf, %lf,'.','color','magenta');\n",x,y);
		if (j == 5)
			fprintf(ff,"plot(%lf, %lf,'.','color','cyan');\n",x,y);
		if (j == 6)
			fprintf(ff,"plot(%lf, %lf,'.','color','black');\n",x,y);
		if (j == 7)
			fprintf(ff,"plot(%lf, %lf,'.','color','yellow');\n",x,y);
		
		
	}
		
	fclose(ff);
	*/

	if (small_grd)
		small_grd->release();

	return res;

};

bitvec * nodes_in_curv_mask(grid_line * line, d_grid * grd, bitvec * mask_undefined) {

	if (!line)
		return NULL;

	if (line->size() == 0)
		return NULL;

	bitvec * res = create_bitvec(grd->getCountX()*grd->getCountY());
	res->init_false();

	size_t min_i = UINT_MAX, min_j = UINT_MAX, max_i = 0, max_j = 0;

	size_t i, j; 
	size_t pos;
	size_t pos_i, pos_j;
	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();
	for (i = 0; i < line->size(); i++) {
		pos = *(line->first->begin()+i);
		pos_i = pos % NN;
		pos_j = (pos - pos_i)/NN;
		min_i = MIN(min_i, pos_i);
		max_i = MAX(max_i, pos_i);
		min_j = MIN(min_j, pos_j);
		max_j = MAX(max_j, pos_j);

		pos = *(line->second->begin()+i);
		pos_i = pos % NN;
		pos_j = (pos - pos_i)/NN;
		min_i = MIN(min_i, pos_i);
		max_i = MAX(max_i, pos_i);
		min_j = MIN(min_j, pos_j);
		max_j = MAX(max_j, pos_j);
	};

	min_i = MAX(min_i, 0);
	min_j = MAX(min_j, 0);
	max_i = MIN(max_i, NN-1);
	max_j = MIN(max_j, MM-1);

	// расширяем сознание
	min_i--;
	min_j--;
	max_i++;
	max_j++;

	size_t nn = max_i-min_i+1;
	size_t mm = max_j-min_j+1;

	d_grid * small_grd = create_grid(grd);

	REAL old_startX = grd->startX;
	REAL old_endX = grd->endX;
	REAL old_startY = grd->startY;
	REAL old_endY = grd->endY;

	grd->startX += grd->stepX*min_i;
	grd->startY += grd->stepY*min_j;
	grd->endX    = grd->startX + grd->stepX*(nn-1);
	grd->endY    = grd->startY + grd->stepY*(mm-1);

	nn = grd->getCountX();
	mm = grd->getCountY();

	for (i = 0; i < line->size(); i++) {
		pos = *(line->first->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		pos_i -= min_i;
		pos_j -= min_j;
		two2one(pos, pos_i, pos_j, nn, mm);
		*(line->first->begin()+i) = pos;

		pos = *(line->second->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		pos_i -= min_i;
		pos_j -= min_j;
		two2one(pos, pos_i, pos_j, nn, mm);
		*(line->second->begin()+i) = pos;
	};

	line->sort();	

	std::vector<short int> * data = new std::vector<short int>(nn*mm);

	// check for undefined elements in sub_grid!
	bool exists_undef = false;
	if (mask_undefined) {
		size_t n, m, mask_pos;
		for (j = 0; j < mm; j++) {
			for (i = 0; i < nn; i++) {
				n = i; m = j;
				two2two(n, m, grd, small_grd);
				if ( grid_bound2(n, m, NN, MM) ) {
					two2one(mask_pos, n, m, NN, MM);
					if (mask_undefined->get(mask_pos)) {
						exists_undef = true;
						break;
					}
				}
			}
		}
	}

	if (!exists_undef)
		flood_fill(grd,
			   line, 
			   data,
			   0,
			   1,
			   NULL);
	else {
		bitvec * local_mask_undefined = create_bitvec(nn*mm);
		local_mask_undefined->init_false();
		size_t n, m, mask_pos, pos;
	
		for (j = 0; j < mm; j++) {
			for (i = 0; i < nn; i++) {
				n = i; m = j;
				two2two(n, m, grd, small_grd);
				if ( grid_bound2(n, m, NN, MM) ) {
					two2one(mask_pos, n, m, NN, MM);
					if (mask_undefined->get(mask_pos)) {
						pos = i + j*nn;
						local_mask_undefined->set_true(pos);
						break;
					}
				}
			}
		}

		flood_fill(grd,
			   line, 
			   data,
			   0,
			   1,
			   local_mask_undefined);
		if (local_mask_undefined)
			local_mask_undefined->release();
	}

	int val;
	for (j = 0; j < mm; j++) {
		for (i = 0; i < nn; i++) {
			pos = i + j*nn;
			val = (*data)[pos];
			if ( val == 0) {
				pos = (i + min_i) + (j + min_j)*NN;
				if ( (i + min_i >= 0) && (i + min_i < NN) &&
				     (j + min_j >= 0) && (j + min_j < MM) )
				{
					res->set_true(pos);
				}
			}
		}
	}

	delete data;

	for (i = 0; i < line->size(); i++) {
		pos = *(line->first->begin()+i);
		one2two(pos, pos_i, pos_j, nn, mm);
		pos_i += min_i;
		pos_j += min_j;
		two2one(pos, pos_i, pos_j, NN, MM);
		*(line->first->begin()+i) = pos;

		pos = *(line->second->begin()+i);
		one2two(pos, pos_i, pos_j, nn, mm);
		pos_i += min_i;
		pos_j += min_j;
		two2one(pos, pos_i, pos_j, NN, MM);
		*(line->second->begin()+i) = pos;
	};

	line->sort();
	
	grd->startX = old_startX;
	grd->endX = old_endX;
	grd->startY = old_startY;
	grd->endY = old_endY;

	if (small_grd)
		small_grd->release();
	return res;

};

bool grid_line::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

grid_line * trace_undef_grd_line(const bitvec * mask_undefined, size_t NN) {
	size_t size = mask_undefined->size();
	size_t MM = size/NN;

	std::vector<size_t> * first = new std::vector<size_t>();
	std::vector<size_t> * second = new std::vector<size_t>();
	grid_line * res = NULL;
	
	size_t pos, pos1, pos2;
	size_t i,j;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-1; j++) {
			pos = i+j*NN;
			pos1 = i+1+j*NN;
			pos2 = i+(j+1)*NN;
			if (mask_undefined->get(pos)) {
				if (!mask_undefined->get(pos1)) {
					first->push_back(pos);
					second->push_back(pos1);
				}
				if (!mask_undefined->get(pos2)) {
					first->push_back(pos);
					second->push_back(pos2);
				}
			} else {
				if (mask_undefined->get(pos1)) {
					first->push_back(pos);
					second->push_back(pos1);
				}
				if (mask_undefined->get(pos2)) {
					first->push_back(pos);
					second->push_back(pos2);
				}
			}
			
		}
	}

	if (first->size() > 0) {
		res = create_grid_line(first, second);
		first = NULL;
		second = NULL;
	}
	
	delete first;
	delete second;
	
	return res;
};

bitvec * nodes_in_curv_mask(const d_curv * crv, d_grid * grd, bitvec * mask_undefined) {

	grid_line * grd_line = NULL;
	grd_line = curv_to_grid_line(grd_line, crv, method_grid);

	bitvec * res = nodes_in_curv_mask(grd_line, grd, mask_undefined);

	if (grd_line)
		grd_line->release();

	return res;

};

bitvec * nodes_in_area_mask(const d_area * area, d_grid * grd, bitvec * mask_undefined) {

	bitvec * res = create_bitvec(grd->getCountX()*grd->getCountY());
	res->init_false();

	int i;
	for (i = 0; i < area->size(); i++) {
		const d_curv * crv = area->get_curv(i);
		bool inside = area->get_curv_orient(i);


		grid_line * grd_line = NULL;
		grd_line = curv_to_grid_line(grd_line, crv, grd);
		if (grd_line == NULL)
			continue;

		bitvec * curv_mask = nodes_in_curv_mask(grd_line, grd, mask_undefined);

		if (grd_line)
			grd_line->release();

		if (curv_mask == NULL)
			continue;

		if (inside == true) {
			res->OR(curv_mask);
		} else {
			res->XOR(curv_mask);
		}
		
		if (curv_mask)
			curv_mask->release();
		
	}

	if (area->inverted)
		res->invert();
	
	return res;

};

}; // namespace surfit
