
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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "points.h"
#include "vec_alg.h"
#include "variables_tcl.h"
#include "wtask.h"
#include "sort_alg.h"
#include <algorithm>

namespace surfit {

points::points() {
	X_begin = NULL;
	Y_begin = NULL;
	Z_begin = NULL;
	X_end = NULL;
	Y_end = NULL;
	Z_end = NULL;
};

points::points(REAL *& iX_begin, REAL * iX_end, 
               REAL *& iY_begin, REAL * iY_end, 
               REAL *& iZ_begin, REAL * iZ_end,
               const char * ipoints_name) {
	X_begin = iX_begin;
	iX_begin = NULL;
	Y_begin = iY_begin;
	iY_begin = NULL;
	Z_begin = iZ_begin;
	iZ_begin = NULL;
	X_end = iX_end;
	iX_end = NULL;
	Y_end = iY_end;
	iY_end = NULL;
	Z_end = iZ_end;
	iZ_end = NULL;
};

points::~points() {
	free(X_begin);
	free(Y_begin);
	free(Z_begin);
};

int points::size() const {
	if ((!Z_begin) || (!Z_end)) return 0;
	return Z_end-Z_begin;
};

REAL points::minx() const {
	return *std::min_element(X_begin, X_end);
};

REAL points::maxx() const {
	return *std::max_element(X_begin, X_end);
};

REAL points::miny() const {
	return *std::min_element(Y_begin, Y_end);
};

REAL points::maxy() const {
	return *std::max_element(Y_begin, Y_end);
};

REAL points::minz() const {
	return *std::min_element(Z_begin, Z_end);
};

REAL points::maxz() const {
	return *std::max_element(Z_begin, Z_end);
};

bool points::plus(const points * points) {
	if (!points)
		return false;
	if (points->size() != size())
		return false;
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) += *(points->Z_begin + i);
	return true;
};

bool points::minus(const points * points) {
	if (!points)
		return false;
	if (points->size() != size())
		return false;
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) -= *(points->Z_begin + i);
	return true;
};

bool points::mult(const points * points) {
	if (!points)
		return false;
	if (points->size() != size())
		return false;
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) *= *(points->Z_begin + i);
	return true;
};

bool points::div(const points * points) {
	if (!points)
		return false;
	if (points->size() != size())
		return false;
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) /= *(points->Z_begin + i);
	return true;
};

bool points::set(const points * points) {
	if (!points)
		return false;
	if (points->size() != size())
		return false;
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) = *(points->Z_begin + i);
	return true;
};

void points::plus(REAL val) {
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) += val;
};

void points::minus(REAL val) {
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) -= val;
};

void points::mult(REAL val) {
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) *= val;
};

void points::div(REAL val) {
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) /= val;
};

void points::set(REAL val) {
	int i;
	for (i = 0; i < size(); i++)
		*(Z_begin + i) = val;
};


REAL points::mean() const {
	return mean_value(Z_begin, Z_end, undef_value);
};

REAL points::std(REAL mean) const {
	return std_value(mean, Z_begin, Z_end, undef_value);
};

sub_points::sub_points(int icell_number, 
		       std::vector<unsigned int> * ipoint_numbers)
{
	cell_number = icell_number;
	point_numbers = ipoint_numbers;
};

sub_points::~sub_points() {
	delete point_numbers;
};

REAL sub_points::value(const points * pnts) const {
	std::vector<unsigned int>::const_iterator ptr;
	
	REAL value = REAL(0);
	REAL temp_value;
	int cnt = 0;
	for (ptr = point_numbers->begin(); ptr != point_numbers->end(); ptr++) {
		temp_value = *(pnts->Z_begin + *ptr);
		if (temp_value == undef_value)
			return undef_value;
		value += temp_value;
		cnt++;
	}
	value /= REAL(cnt);
	return value;
};

REAL sub_points::sum_value(const points * pnts) const {
	std::vector<unsigned int>::const_iterator ptr;
	
	REAL value = REAL(0);
	REAL temp_value;
	for (ptr = point_numbers->begin(); ptr != point_numbers->end(); ptr++) {
		temp_value = *(pnts->Z_begin + *ptr);
		if (temp_value == undef_value)
			return undef_value;
		value += temp_value;
	}
	return value;
};

REAL sub_points::value(const wtask * wtsk) const {
	std::vector<unsigned int>::const_iterator ptr;

	REAL value = REAL(0);
	REAL total_weight = REAL(0);
	REAL weight;
	REAL temp_value;

	REAL abs_value = REAL(0);
	int abs_cnt = 0;

	for (ptr = point_numbers->begin(); ptr != point_numbers->end(); ptr++) {
		temp_value = *(wtsk->Z_begin + *ptr);
		weight = *(wtsk->W_begin + *ptr);

		if (temp_value == undef_value)
			return undef_value;

		if (weight < 0) {
			abs_value += temp_value;
			abs_cnt++;
		} else {
			value += temp_value * weight;
			total_weight += weight;
		}

	}

	if (abs_cnt > 0) 
		return abs_value/REAL(abs_cnt);
	
	if (total_weight != 0)
		return value / total_weight;
	return 0;

};

REAL sub_points::weight(const wtask * wtsk) const {
	std::vector<unsigned int>::const_iterator ptr;

	REAL total_weight = REAL(0);
	REAL weight;
	int cnt = 0;
	
	for (ptr = point_numbers->begin(); ptr != point_numbers->end(); ptr++) {
		weight = *(wtsk->W_begin + *ptr);

		if (weight < 0) {
			return -1;
		} else {
			cnt++;
			total_weight += weight;
		}
	}

	return total_weight / REAL(cnt);
};

void _sort_points(points * pnts, 
		  std::vector<unsigned int> * nums,
		  REAL **& sortx_begin, 
		  REAL **& sortx_end, 
		  REAL **& sorty_begin, 
		  REAL **& sorty_end) {

	int ptask_size = nums->size();
	REAL ** ptr;
	
	sortx_begin = (REAL**) malloc( sizeof(REAL*) * ptask_size );
	sortx_end = sortx_begin + ptask_size;
	int cnt;
    
	for (cnt = 0; cnt < ptask_size; cnt++) {
		ptr = sortx_begin + cnt;
		*ptr = ( pnts->X_begin + *(nums->begin()+cnt) );
	}
	
	std::sort(sortx_begin, sortx_end, ptr_vector_less);
	
	sorty_begin = (REAL**) malloc( sizeof(REAL*) * ptask_size );
	sorty_end = sorty_begin + ptask_size;
	
	for (cnt = 0; cnt < ptask_size; cnt++) {
		ptr = sorty_begin + cnt;
		*ptr = ( pnts->Y_begin + *(nums->begin()+cnt) );
	}
	
	std::sort(sorty_begin, sorty_end, ptr_vector_less);

};

void _points_transform(points * pnts, 
		       REAL shiftX, REAL scaleX, 
		       REAL shiftY, REAL scaleY) {
	REAL * ptr_X;
	REAL * ptr_Y;
	for (ptr_X = pnts->X_begin; ptr_X != pnts->X_end; ptr_X++) 
        *ptr_X = ( *ptr_X - shiftX ) * scaleX; 
	
	for (ptr_Y = pnts->Y_begin; ptr_Y != pnts->Y_end; ptr_Y++) 
		*ptr_Y = ( *ptr_Y - shiftY ) * scaleY;
};

void _inverse_points_transform(points * pnts, 
			       REAL shiftX, REAL scaleX, 
			       REAL shiftY, REAL scaleY) {

	REAL * ptr_X;
	REAL * ptr_Y;
	for (ptr_X = pnts->X_begin; ptr_X != pnts->X_end; ptr_X++) 
	        *ptr_X = *ptr_X/scaleX + shiftX;
	
	for (ptr_Y = pnts->Y_begin; ptr_Y != pnts->Y_end; ptr_Y++) 
        	*ptr_Y = *ptr_Y/scaleY + shiftY;
};

}; // namespace surfit;

