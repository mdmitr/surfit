
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

struct search_cells {
	
	search_cells(const sizetvec * iV, const size_t isearch_val)
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
	const sizetvec * V;
	size_t search_val;
};

grid_line * create_grid_line(size_t iNN, size_t iMM, sizetvec * ifirst, sizetvec * isecond) {
	return new grid_line(iNN, iMM, ifirst, isecond);
};

grid_line::grid_line(size_t iNN, size_t iMM, sizetvec * ifirst, sizetvec * isecond) : data("grid_line") {

	NN = iNN;
	MM = iMM;
	first = ifirst;
	second = isecond;
	sorted_first = NULL;
	sorted_second = NULL;
	sort();
	
};

grid_line::~grid_line() {
	if (first)
		first->release();
	if (second)
		second->release();
	if (sorted_first)
		sorted_first->release();
	if (sorted_second)
		sorted_second->release();
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
	size_t size = first->size();;

	if (sorted_first)
		sorted_first->release();
	if (sorted_second)
		sorted_second->release();
	
	sorted_first = create_sizetvec(size);
	
	size_t pos;
	for (pos = 0; pos < size; pos++)
		(*sorted_first)(pos) = pos;
	
	nums_less_compare nums_less_first(first);
	std::sort(sorted_first->begin(), sorted_first->end(), nums_less_first);

	sorted_second = create_sizetvec(size);
	for (pos = 0; pos < size; pos++)
		(*sorted_second)(pos) = pos;

	nums_less_compare nums_less_second(second);
	std::sort(sorted_second->begin(), sorted_second->end(), nums_less_second);
};

void grid_line::add(sizetvec *& ifirst, sizetvec *& isecond) 
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
	if (ifirst)
		ifirst->release();
	ifirst = NULL;
	
	second->resize(old_size+add_size);
	std::copy(isecond->begin(), isecond->begin() + add_size, second->begin() + old_size);
	//memcpy(second->begin() + old_size, isecond->begin(), add_size*sizeof(int));
	if (isecond)
		isecond->release();
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

grid_line::cell_finder grid_line::get_cell_finder(size_t ipos) const
{
	return cell_finder(ipos, this);
};

grid_line::cell_finder::cell_finder(size_t ipos, const grid_line * grd_line) 
{
	NN = grd_line->NN;
	MM = grd_line->MM;
	size_t pos_i, pos_j;
	one2two(ipos, pos_i, pos_j, NN-2, MM-2);
	pos_i++;
	pos_j++;
	pos = two2one(pos_i, pos_j, NN, MM);

	sorted_first = grd_line->sorted_first;
	sorted_second = grd_line->sorted_second;
	last_first = sorted_first->const_begin();
	last_second = sorted_second->const_begin();
	
	first = grd_line->first;
	second = grd_line->second;
};

bool grid_line::cell_finder::find_next(size_t & near_cell) {


	if (last_first != sorted_first->const_end()) {

		search_cells search_pos(first, pos);
		ptr = std::lower_bound(last_first, 
				       sorted_first->const_end(), 
				       UINT_MAX,
				       search_pos);

		if (ptr != sorted_first->const_end()) {
			last_first = ptr+1;
			if ( (*first)(*ptr) == pos ) {
				near_cell = (*second)(*ptr); 
				size_t pos_i, pos_j;
				one2two(near_cell, pos_i, pos_j, NN, MM);
				pos_i--;
				pos_j--;
				near_cell = two2one(pos_i, pos_j, NN-2, MM-2);
				return true;
			} else {
				last_first = sorted_first->const_end();
			}
		} else
			last_first = sorted_first->const_end();

	}

	if ( (last_first == sorted_first->const_end()) && (last_second != sorted_second->const_end()) ) {
		
		search_cells search_pos(second, pos);
		ptr = std::lower_bound(last_second, 
				       sorted_second->const_end(), 
				       UINT_MAX,
				       search_pos);

		if (ptr != sorted_second->const_end()) {
			last_second = ptr+1;
			if ( (*second)(*ptr) == pos ) {
				near_cell = (*first)(*ptr);
				size_t pos_i, pos_j;
				one2two(near_cell, pos_i, pos_j, NN, MM);
				pos_i--;
				pos_j--;
				near_cell = two2one(pos_i, pos_j, NN-2, MM-2);
				return true;
			} else {
				last_second = sorted_second->const_end();
			}
		} else
			last_second = sorted_second->const_end();

	}

	return false;

};

bool grid_line::check_for_node(size_t pos) const {

	size_t pos_i, pos_j;
	one2two(pos, pos_i, pos_j, NN-2, MM-2);
	pos_i++;
	pos_j++;
	pos = two2one(pos_i, pos_j, NN, MM);
	assert(pos != UINT_MAX);

	search_cells search_pos1(first, pos);

	sizetvec::const_iterator ptr;
	ptr = std::lower_bound(sorted_first->const_begin(), 
			       sorted_first->const_end(), 
			       UINT_MAX,
			       search_pos1);
	
	if (ptr != sorted_first->const_end())
		if ((*first)(*ptr) == pos)
			return true;
		
	search_cells search_pos2(second, pos);

	ptr = std::lower_bound(sorted_second->const_begin(), 
			       sorted_second->const_end(), 
	                       UINT_MAX,
			       search_pos2);
		
	if (ptr != sorted_second->const_end())
		if ((*second)(*ptr) == pos)
			return true;
			
	return false;
			
};

bool grid_line::check_for_pair(size_t pos1, size_t pos2) const {

	size_t pos_i, pos_j;
	one2two(pos1, pos_i, pos_j, NN-2, MM-2);
	pos_i++;
	pos_j++;
	pos1 = two2one(pos_i, pos_j, NN, MM);
	assert(pos1 != UINT_MAX);

	one2two(pos2, pos_i, pos_j, NN-2, MM-2);
	pos_i++;
	pos_j++;
	pos2 = two2one(pos_i, pos_j, NN, MM);
	assert(pos2 != UINT_MAX);

	if (pos1 > pos2) {
		size_t temp = pos2;
		pos2 = pos1;
		pos1 = temp;
	}

	sizetvec::const_iterator ptr;

	sizetvec::const_iterator ptr_from = sorted_first->const_begin();
	
first_again_pos1:
	
	search_cells search_pos11(first, pos1);

	ptr = std::lower_bound(ptr_from, 
			       sorted_first->const_end(), 
	                       UINT_MAX,
			       search_pos11);

	if (ptr != sorted_first->const_end()) {
		if ((*first)(*ptr) == pos1) {
			if ( pos2 == (*second)(*ptr) )
				return true;
			ptr_from = ptr+1;
			goto first_again_pos1;
		}
	}

	ptr_from = ptr; //sort_by_first_begin;

first_again_pos2:
	

	if (ptr_from != sorted_first->const_end()) {

		search_cells search_pos12(first, pos2);

		ptr = std::lower_bound(ptr_from, 
				       sorted_first->const_end(), 
	                               UINT_MAX,
				       search_pos12);
		
		if (ptr != sorted_first->const_end()) {
			if ( (*first)(*ptr) == pos2) {
				if ( pos1 == (*second)(*ptr) )
					return true;
				ptr_from = ptr+1;
				goto first_again_pos2;
			}
		}
	}

	ptr_from = sorted_second->const_begin();

second_again_pos1:

	search_cells search_pos21(second, pos1);

	ptr = std::lower_bound(ptr_from, 
			       sorted_second->const_end(), 
	                       UINT_MAX,
			       search_pos21);

	if (ptr != sorted_second->const_end()) {
		if ( (*second)(*ptr) == pos1) {
			if ( pos2 == (*first)(*ptr) )
				return true;
			ptr_from = ptr+1;
			goto second_again_pos1;
		}
	}

	ptr_from = ptr;//sort_by_second_begin;

second_again_pos2:

	if (ptr_from != sorted_second->const_end()) {

		search_cells search_pos22(second, pos2);

		ptr = std::lower_bound(ptr_from, 
				       sorted_second->const_end(), 
				       UINT_MAX,
				       search_pos22);
		
		if ( ptr != sorted_second->const_end()) {
			if ( (*second)(*ptr) == pos2) {
				if ( pos1 == (*first)(*ptr) )
					return true;
				ptr_from = ptr+1;
				goto second_again_pos2;
			}
		}
	}

	return false;

};


void fault_points_D1(size_t n, size_t m, 
		     size_t NN, size_t MM, 
		     const grid_line * fault,
		     bool & first_x, bool & second_x, 
		     bool & first_y, bool & second_y,
		     size_t offset_x, size_t offset_y) 
{
	if (!fault)
		return;

	size_t J = (n+offset_x) + (m+offset_y)*NN;
	size_t J2;
	size_t diff;
		
	grid_line::cell_finder cf = fault->get_cell_finder(J);

	while (cf.find_next(J2)) {
		
		if (J2 == UINT_MAX)
			continue;
		diff = abs(int(J - J2));
		
		// vertical
		if (diff == 1) {
			if (J2 > J)
				first_x = false;
			else
				second_x = false;
		}
		
		// horizontal
		if (diff == NN) {
			if (J2 > J)
				first_y = false;
			else
				second_y = false;
		}

		if ( (!first_x) && (!second_x) && (!first_y) && (!second_y) )
			break;

	}

	return;

};

void fault_points_D1_aniso(size_t n, size_t m, 
			   size_t NN, size_t MM, 
			   const grid_line * fault,
			   bool & first_x, bool & second_x, 
			   bool & first_y, bool & second_y,
			   bool & first_xy, bool & first_yx,
			   bool & second_xy, bool & second_yx,
			   size_t offset_x, size_t offset_y) 
{
	if (!fault)
		return;

	size_t J = (n+offset_x) + (m+offset_y)*NN;
	size_t J2;
	size_t diff;
	size_t pos2find;

	// J - NN
	if ( ( second_xy ) && (J >= NN) ) {
		pos2find = J-NN; 
		grid_line::cell_finder cf = fault->get_cell_finder(pos2find);
		
		while (cf.find_next(J2)) {
			if (J2 == UINT_MAX)
				continue;
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

			if (!second_xy)
				break;

		}

	}

	// J - 1
	if ( ( second_yx ) && ( J >= 1 ) ) {
		pos2find = J-1; 
	
		grid_line::cell_finder cf = fault->get_cell_finder(pos2find);
		while (cf.find_next(J2)) {
			if (J2 == UINT_MAX)
				continue;
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
		
			if (!second_yx)
				break;
		}

	}

	// J
	if ( first_y || second_y || first_x || second_x || first_xy || first_yx || second_xy || second_yx ) {
		pos2find = J; 

		grid_line::cell_finder cf = fault->get_cell_finder(pos2find);
		while (cf.find_next(J2)) {
			if (J2 == UINT_MAX)
				continue;
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

			if ( !first_y && !second_y && !first_x && !second_x && !first_xy && !first_yx && !second_xy && !second_yx) 
				break;

		}

	}

	return;

};

void fault_points_D2(size_t n, size_t m, size_t NN, size_t MM, 
		     const grid_line * fault,
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
	size_t pos2find;

	// J-NN
	if ( ( second_y || third_y || first_yy || second_yy ) && ( J >= NN ) ) {
		pos2find = J-NN;
		grid_line::cell_finder cf_J__NN = fault->get_cell_finder(pos2find);
		while (cf_J__NN.find_next(J2)) {
			if (J2 == UINT_MAX)
				continue;
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
			
			if ( !second_y && !third_y && !first_yy && !second_yy )
				break;
			
		}
	}

	// J-1
	if ( ( second_x || third_x || first_xx || second_xx || second_yy ) && (J >= 1) ) {
		pos2find = J-1;
		grid_line::cell_finder cf_J__1 = fault->get_cell_finder(pos2find);
		while (cf_J__1.find_next(J2)) {
			if (J2 == UINT_MAX)
				continue;
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
			
			if ( !second_x && !third_x && !first_xx && !second_xx && !second_yy )
				break;
		}
	}

	// J+1
	if ( ( first_x || second_x || first_xx || first_yy ) && ( J+1 < NN*MM ) ) {
		pos2find = J+1;
		grid_line::cell_finder cf_J_1 = fault->get_cell_finder(pos2find);
		while (cf_J_1.find_next(J2)) {
			if (J2 == UINT_MAX)
				continue;
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

			if ( !first_x && !second_x && !first_xx && !first_yy ) 
				break;
	
		}
	}

	// J+NN
	if ( ( first_y || second_y || first_xx || second_xx ) && ( J+NN < NN*MM ) ) {
		pos2find = J+NN;
		grid_line::cell_finder cf_J_NN = fault->get_cell_finder(pos2find);
		while (cf_J_NN.find_next(J2)) {
			if (J2 == UINT_MAX)
				continue;
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

			if ( !first_y && !second_y && !first_xx && !second_xx )
				break;

		}
	}

	return;

};

void grid_line::get_minmax(size_t & min_i, size_t & max_i, 
			   size_t & min_j, size_t & max_j) const 
{
	min_i = UINT_MAX;
	max_i = 0;
	min_j = UINT_MAX;
	max_j = 0;
	size_t i, pos, pos_i, pos_j;
	
	for (i = 0; i < size(); i++) {
		pos = *(first->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		min_i = MIN(min_i, pos_i);
		max_i = MAX(max_i, pos_i);
		min_j = MIN(min_j, pos_j);
		max_j = MAX(max_j, pos_j);
		
		pos = *(second->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		min_i = MIN(min_i, pos_i);
		max_i = MAX(max_i, pos_i);
		min_j = MIN(min_j, pos_j);
		max_j = MAX(max_j, pos_j);
	}
	
};

void grid_line::resize(size_t move_i, size_t move_j, size_t newNN, size_t newMM, 
		       bool minus_i, bool minus_j) {

	size_t i, pos, pos_i, pos_j;

	for (i = 0; i < size(); i++) {
		pos = *(first->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		
		if (minus_i)
			pos_i -= move_i;
		else
			pos_i += move_i;
		if (minus_j)
			pos_j -= move_j;
		else 
			pos_j += move_j;
		
		pos = two2one(pos_i, pos_j, newNN, newMM);
		*(first->begin()+i) = pos;
		
		pos = *(second->begin()+i);
		one2two(pos, pos_i, pos_j, NN, MM);
		
		if (minus_i)
			pos_i -= move_i;
		else
			pos_i += move_i;
		if (minus_j)
			pos_j -= move_j;
		else 
			pos_j += move_j;

		pos = two2one(pos_i, pos_j, newNN, newMM);
		*(second->begin()+i) = pos;
	}

	NN = newNN;
	MM = newMM;
};

size_t grid_line::get_first_cell(size_t pos) const
{
	return (*first)(pos);
};

size_t grid_line::get_second_cell(size_t pos) const
{
	return (*second)(pos);
};

void flood_fill(d_grid * grd,
		const grid_line * line, 
		shortvec * data,
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
	 
	sizetvec * flood_points = create_sizetvec();
	size_t push_pos, push_pos2;
	flood_points->push_back(fill_pos);
	
	size_t max_points = 1;
	size_t i;
	for (i = 0; i < max_points; i++) {

		bool flood;

		size_t pos = (*flood_points)(i);

		if (pos == UINT_MAX)
			continue;

		if ( (*data)(pos) != 0 )
			continue;

		one2two(pos, fill_i, fill_j, NN, MM);
		
		// find left edge
		size_t left_i = fill_i;
		size_t left_j = fill_j;
				
		while (true) {
			
			if ((left_i >= 0) && (left_i < max_i) && (left_j >= 0) && (left_j < max_j)) {
				push_pos = two2one(left_i, left_j, NN, MM);
				if ( (*data)(push_pos) == 0 )
					(*data)(push_pos) = fill_val;
			}
			else
				break;
			
			left_i--;

			push_pos = two2one(left_i, left_j, NN, MM);
			push_pos2 = two2one(left_i + 1, left_j, NN, MM);

			bool bound = ((left_i >= 0) && (left_i < max_i) && (left_j >= 0) && (left_j < max_j));
			if (!bound)
				break;
			
			flood = true;
			
			if (line)
				flood = !line->check_for_pair(push_pos, push_pos2);// check_flood(left_i, left_j, left_i+1, left_j);

			if (mask_undefined && flood) {
				flood = flood && !mask_undefined->get(push_pos);
			}
			
			if (flood)
				flood = flood && ( (*data)(push_pos) == 0 );
			
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
			push_pos = two2one(right_i, right_j, NN, MM);
			push_pos2 = two2one(right_i - 1, right_j, NN, MM);
			
			flood = true;
			bool bound = ((right_i >= 0) && (right_i < max_i) && (right_j >= 0) && (right_j < max_j));
			if (!bound)
				break;
			
			if (line)
				flood = !line->check_for_pair(push_pos, push_pos2);//check_flood(right_i, right_j, right_i-1, right_j);
			
			if (mask_undefined && flood) {
				flood = flood && !mask_undefined->get(push_pos);
			}
							
			if (flood)
			    	flood = flood && ( (*data)(push_pos) == 0 );
			
			if (!flood)
				break;

			if ( (*data)(push_pos) == 0 )
				(*data)(push_pos) = fill_val;
			
			else
				break;

		};
		right_i--;
		
		// start the loop upwards and downwards
		size_t i_pos;
		for (i_pos = left_i; i_pos <= right_i; i_pos++) {

			// upwards
			push_pos = two2one(i_pos, fill_j+1, NN, MM);
			push_pos2 = two2one(i_pos, fill_j, NN, MM);
			if (( push_pos >= 0 ) && (push_pos < grid_size)) {
				if ( (*data)(push_pos) == 0 ) {
					
					flood = true;
					
					if (line)
						flood = !line->check_for_pair(push_pos2, push_pos);
					
					if (mask_undefined && flood && (push_pos > 0)) {
						flood = flood && !mask_undefined->get(push_pos);
					}
						
					if (flood && (fill_j+1 < MM))
						flood = flood && ( (*data)(push_pos) == 0 );
					
					if (flood && (fill_j+1 < MM))
						flood_points->push_back(push_pos);
				}
			}
			
			// downwards
			push_pos = two2one(i_pos, fill_j-1, NN, MM);
			push_pos2 = two2one(i_pos, fill_j, NN, MM);
			if (( push_pos >= 0 ) && (push_pos < grid_size)) {
				if ( (*data)(push_pos) == 0 ) {
					
					flood = true;
					
					if (line)
						flood = !line->check_for_pair(push_pos2, push_pos);
					
					if (mask_undefined && flood && (push_pos > 0)) {
						flood = flood && !mask_undefined->get(push_pos);
					}

					if (flood && (fill_j-1 >= 0))
						flood = flood && ( (*data)(push_pos) == 0 );
					
					if (flood && (fill_j-1 >= 0))
						flood_points->push_back(push_pos);
				}
			}

		}

		max_points = flood_points->size();
				
	}

	if (flood_points)
		flood_points->release();
	
	/*
#ifdef DEBUG
	FILE * ff = fopen("c:\\ffill.m","w");
	fprintf(ff,"hold on\n");
	
	draw_grid_matlab(ff,grd);
	draw_grid_line_matlab(ff, line, grd);
	draw_filled_grid_matlab(ff, grd, data);
	
	fclose(ff);
#endif
	//*/
		
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

	sizetvec * flood_points = create_sizetvec();
	flood_points->push_back(fill_i + NN * fill_j);

	size_t max_points = 1;
	size_t i;
	for (i = 0; i < max_points; i++) {
		
		bool flood;

		size_t pos = (*flood_points)(i);

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
			flood = line->check_for_pair(left_i + left_j*NN, left_i + left_j*NN + 1);// check_flood(left_i, left_j, left_i+1, left_j);
			if (flood)
				break;
		};
		left_i++;

		size_t right_i = fill_i, right_j = fill_j;
		
		// find right edge
		while (true) {
			
			right_i++;
			flood = line->check_for_pair(right_i + right_j*NN, right_i + right_j*NN - 1);//check_flood(right_i, right_j, right_i-1, right_j);
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
					flood = line->check_for_pair(i_pos + fill_j*NN, new_pos);
					if (!flood)
						flood_points->push_back(new_pos);
				}
			}
			
			// downwards
			new_pos = i_pos-NN + fill_j*NN;
			if (( new_pos >= 0 ) && (new_pos < grid_size)) {
				if ( (*data)(new_pos) == false ) {
					flood = line->check_for_pair(i_pos + fill_j*NN, new_pos);
					if (!flood)
						flood_points->push_back(new_pos);
				}
			}

		}

		max_points = flood_points->size();
				
	}

	if (flood_points)
		flood_points->release();
		
	return;
};

shortvec::const_iterator 
find_first(shortvec::const_iterator it1, 
	   shortvec::const_iterator it2,
	   short int val) {

	while (it1 != it2) {
		if (*it1 == val)
			return it1;
		it1++;
	}

	return it2;

};

void fill_all_areas(shortvec *& flood_areas, 
		    d_grid * grd, 
		    grid_line * line, 
		    int & flood_areas_cnt,
		    const bitvec * mask_undefined)
{
	
	size_t pos ;

	size_t max_pos = grd->getCountX()*grd->getCountY();

	if (!flood_areas)
		flood_areas = create_shortvec( max_pos );

	short int color = 1;

	if (!line && !mask_undefined)
	{
		size_t i;
		for (i = 0; i < flood_areas->size(); i++) {
			(*flood_areas)(i) = color;
			flood_areas_cnt = 1;
		}
		return;
	}

	if (mask_undefined) {
		for (pos = 0; pos < max_pos; pos++) {
			if (mask_undefined->get(pos))
				(*flood_areas)(pos) = -1;
		}
	}

	shortvec::const_iterator it;
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
#ifdef DEBUG
	FILE * ff = fopen("c:\\qqq.m","w+");
	fprintf(ff,"hold on\n");
	
	draw_grid_matlab(ff,grd);
	draw_grid_line_matlab(ff, line, grd);
	draw_filled_grid(ff, grd, flood_areas);
	
	fclose(ff);
#endif
	*/

	return;

};

bitvec * nodes_in_curv_mask(grid_line * line, const d_grid * grd, const bitvec * mask_undefined) {

	if (!line)
		return NULL;

	if (line->size() == 0)
		return NULL;

	
	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();

	bitvec * res = create_bitvec(NN*MM);
	res->init_false();

	size_t min_i = UINT_MAX, min_j = UINT_MAX, max_i = 0, max_j = 0;
	
	size_t i, j; 
	size_t pos;

	// in terms of the extended grid
	line->get_minmax(min_i, max_i, min_j, max_j);

	// for some cases
	if (min_i > 0)
		min_i--;
	max_i++;
	if (min_j > 0)
		min_j--;
	max_j++;

	min_i = MAX(min_i, 0);
	min_j = MAX(min_j, 0);
	max_i = MIN(max_i, NN+2);
	max_j = MIN(max_j, MM+2);

	size_t nn = max_i-min_i+1;
	size_t mm = max_j-min_j+1;

	d_grid * small_grd = create_grid(grd); // small and not extended

	small_grd->startX = grd->startX + min_i*grd->stepX - grd->stepX;
	small_grd->startY = grd->startY + min_j*grd->stepY - grd->stepY;
	small_grd->endX = small_grd->startX + (nn-1)*grd->stepX;
	small_grd->endY = small_grd->startY + (mm-1)*grd->stepY;

	assert(nn == small_grd->getCountX());
	assert(mm == small_grd->getCountY());

/*
#ifdef DEBUG
	FILE * ff = fopen("c:\\qqq.m","w+");
	fprintf(ff,"hold on\n");
	
	draw_grid_matlab(ff,grd,"magenta");
	draw_grid_line_matlab(ff, line, grd, "red", 3);
#endif
//*/

	line->resize( min_i>1?min_i-1:1-min_i, 
		      min_j>1?min_j-1:1-min_j, 
		      nn+2, mm+2, 
		      min_i>1, min_j>1);
	line->sort();	

/*
#ifdef DEBUG
	draw_grid_matlab(ff,small_grd);
	draw_grid_line_matlab(ff, line, small_grd);
#endif
//*/

	shortvec * data = create_shortvec(nn*mm);

	// check for undefined elements in small_grd
	bool exists_undef = false;
	if (mask_undefined) {
		size_t n, m, mask_pos;
		for (j = 0; j < mm; j++) {
			for (i = 0; i < nn; i++) {
				n = i; m = j;
				two2two(n, m, grd, small_grd);
				if ( grid_bound2(n, m, NN, MM) ) {
					mask_pos = two2one(n, m, NN, MM);
					if (mask_undefined->get(mask_pos)) {
						exists_undef = true;
						break;
					}
				}
			}
		}
	}

	if (!exists_undef) {
		flood_fill(small_grd,
			   line, 
			   data,
			   0,
			   1,
			   NULL);
	} else {
		bitvec * local_mask_undefined = create_bitvec(nn*mm);
		local_mask_undefined->init_false();
		size_t n, m, mask_pos, pos;
	
		for (j = 0; j < mm; j++) {
			for (i = 0; i < nn; i++) {
				n = i; m = j;
				two2two(n, m, small_grd, grd);
				if ( grid_bound2(n, m, NN, MM) ) {
					mask_pos = two2one(n, m, NN, MM);
					if (mask_undefined->get(mask_pos)) {
						pos = i + j*nn;
						local_mask_undefined->set_true(pos);
						break;
					}
				}
			}
		}

		flood_fill(small_grd,
			   line, 
			   data,
			   0,
			   1,
			   local_mask_undefined);
		if (local_mask_undefined)
			local_mask_undefined->release();
	}

	int val;
	size_t pos_i, pos_j;
	for (j = 0; j < mm; j++) {
		for (i = 0; i < nn; i++) {
			pos = i + j*nn;
			val = (*data)(pos);
			if ( val == 0) {
				pos_i = i + ( min_i>1?min_i-1:-1 );
				pos_j = j + ( min_j>1?min_j-1:-1 );
				pos = two2one(pos_i, pos_j, NN, MM);
				if (pos != UINT_MAX)
					res->set_true(pos);
			}
		}
	}

	if (data)
		data->release();
	
	line->resize( min_i>1?min_i-1:1-min_i, 
		      min_j>1?min_j-1:1-min_j, 
		      NN+2, MM+2, 
		      min_i<1, min_j<1);

/*
#ifdef DEBUG

	draw_grid_line_matlab(ff, line, grd, "blue", 3);
	fclose(ff);

#endif
//*/

	line->sort();
	
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

	sizetvec * first = create_sizetvec();
	sizetvec * second = create_sizetvec();
	grid_line * res = NULL;
	
	size_t pos, pos1, pos2;
	size_t gl_pos, gl_pos1, gl_pos2;
	size_t i,j;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-1; j++) {
			pos = i+j*NN;
			pos1 = i+1+j*NN;
			pos2 = i+(j+1)*NN;

			gl_pos = two2one(i+1, j+1, NN+2, MM+2);
			gl_pos1 = two2one(i+2, j+1, NN+2, MM+2);
			gl_pos2 = two2one(i+1, j+2, NN+2, MM+2);

			if (mask_undefined->get(pos)) {
				if (!mask_undefined->get(pos1)) {
					first->push_back(gl_pos);
					second->push_back(gl_pos1);
				}
				if (!mask_undefined->get(pos2)) {
					first->push_back(gl_pos);
					second->push_back(gl_pos2);
				}
			} else {
				if (mask_undefined->get(pos1)) {
					first->push_back(gl_pos);
					second->push_back(gl_pos1);
				}
				if (mask_undefined->get(pos2)) {
					first->push_back(gl_pos);
					second->push_back(gl_pos2);
				}
			}
			
		}
	}

	if (first->size() > 0) {
		res = create_grid_line(NN+2, MM+2, first, second);
		first = NULL;
		second = NULL;
	}
	
	if (first)
		first->release();
	if (second)
		second->release();
	
	return res;
};

bitvec * nodes_in_curv_mask(const d_curv * crv, d_grid * grd, const bitvec * mask_undefined) {

	grid_line * grd_line = NULL;
	grd_line = curv_to_grid_line(grd_line, crv, method_grid);

	bitvec * res = nodes_in_curv_mask(grd_line, grd, mask_undefined);

	if (grd_line)
		grd_line->release();

	return res;

};

bitvec * nodes_in_area_mask(const d_area * area, d_grid * grd, const bitvec * mask_undefined) {

	bitvec * res = create_bitvec(grd->getCountX()*grd->getCountY());
	res->init_false();

/*
#ifdef DEBUG
	FILE * ff = fopen("c:\\mask.m","w+");
	fprintf(ff,"hold on\n");
#endif
//*/

	int i;
	for (i = 0; i < area->size(); i++) {
		const d_curv * crv = area->get_curv(i);
		bool inside = area->get_curv_orient(i);

		grid_line * grd_line = NULL;
		grd_line = curv_to_grid_line(grd_line, crv, grd);

/*
#ifdef DEBUG
		draw_grid_line_matlab(ff, grd_line, grd, "blue",3);
#endif
//*/

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


/*
#ifdef DEBUG
	draw_area_matlab(ff, area);
	draw_grid_matlab(ff,grd);
	draw_bitvec_matlab(ff, grd, res);
	
	fclose(ff);
#endif
//*/
	return res;

};

}; // namespace surfit
