
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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "vec.h"
#include "vec_alg.h"
#include "strvec.h"
#include "sort_alg.h"

#include "points.h"
#include "variables_tcl.h"
#include "free_elements.h"

#include <algorithm>

namespace surfit {

d_points * create_points_default() {
	return new d_points();
};

d_points * create_points(vec *& iX, vec *& iY, vec *& iZ, 
                         const char * ipoints_name) 
{
	return new d_points(iX, iY, iZ,
			    ipoints_name);
};

d_points * create_points(vec *& iX, vec *& iY, vec *& iZ,
			 strvec *& inames,
			 const char * ipoints_name)
{
	return new d_points(iX, iY, iZ, inames, ipoints_name);
};

d_points::d_points() : data("pnts") {
	X = NULL;
	Y = NULL;
	Z = NULL;
	names = NULL;
};

d_points::d_points(vec *& iX, vec *& iY, vec *& iZ, 
                   const char * ipoints_name) : data("pnts") {
	X = iX;
	iX = NULL;
	Y = iY;
	iY = NULL;
	Z = iZ;
	iZ = NULL;
	setName(ipoints_name);
	names = NULL;
};

d_points::d_points(vec *& iX, vec *& iY, vec *& iZ,
		   strvec *& inames,
                   const char * ipoints_name) : data("pnts")
{
	X = iX;
	iX = NULL;
	Y = iY;
	iY = NULL;
	Z = iZ;
	iZ = NULL;
	setName(ipoints_name);
	names = inames;
};

d_points::~d_points() {
	if (X)
		X->release();
	if (Y)
		Y->release();
	if (Z)
		Z->release();
	if (names)
		names->release();
};

int d_points::size() const {
	if (Z)
		return Z->size();
	return 0;
};

REAL d_points::minx() const {
	if (X)
		return *std::min_element(X->begin(), X->end());
	return FLT_MAX;
};

REAL d_points::maxx() const {
	if (X)
		return *std::max_element(X->begin(), X->end());
	return -FLT_MAX;
};

REAL d_points::miny() const {
	if (Y)
		return *std::min_element(Y->begin(), Y->end());
	return FLT_MAX;
};

REAL d_points::maxy() const {
	if (Y)
		return *std::max_element(Y->begin(), Y->end());
	return -FLT_MAX;
};

REAL d_points::minz() const {
	if (Z)
		return *std::min_element(Z->begin(), Z->end());
	return FLT_MAX;
};

REAL d_points::maxz() const {
	if (Z)
		return *std::max_element(Z->begin(), Z->end());
	return -FLT_MAX;
};

bool d_points::plus(const d_points * pnts) {
	if (!pnts)
		return false;
	if (pnts->size() != size())
		return false;
	if (size() == 0)
		return true;
	int i;
	REAL * ptr1 = Z->begin();
	REAL * ptr2 = pnts->Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr1 + i) += *(ptr2 + i);
	return true;
};

bool d_points::minus(const d_points * pnts) {
	if (!pnts)
		return false;
	if (pnts->size() != size())
		return false;
	if (size() == 0)
		return true;
	int i;
	REAL * ptr1 = Z->begin();
	REAL * ptr2 = pnts->Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr1 + i) -= *(ptr2 + i);
	return true;
};

bool d_points::mult(const d_points * pnts) {
	if (!pnts)
		return false;
	if (pnts->size() != size())
		return false;
	if (size() == 0)
		return true;
	int i;
	REAL * ptr1 = Z->begin();
	REAL * ptr2 = pnts->Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr1 + i) *= *(ptr2 + i);
	return true;
};

bool d_points::div(const d_points * pnts) {
	if (!pnts)
		return false;
	if (pnts->size() != size())
		return false;
	if (size() == 0)
		return true;
	int i;
	REAL * ptr1 = Z->begin();
	REAL * ptr2 = pnts->Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr1 + i) /= *(ptr2 + i);
	return true;
};

bool d_points::set(const d_points * pnts) {
	if (!pnts)
		return false;
	if (pnts->size() != size())
		return false;
	if (size() == 0)
		return true;
	int i;
	REAL * ptr1 = Z->begin();
	REAL * ptr2 = pnts->Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr1 + i) = *(ptr2 + i);
	return true;
};

void d_points::plus(REAL val) {
	int i;
	REAL * ptr = Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr + i) += val;
};

void d_points::minus(REAL val) {
	int i;
	REAL * ptr = Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr + i) -= val;
};

void d_points::mult(REAL val) {
	int i;
	REAL * ptr = Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr + i) *= val;
};

void d_points::div(REAL val) {
	int i;
	REAL * ptr = Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr + i) /= val;
};

void d_points::set(REAL val) {
	int i;
	REAL * ptr = Z->begin();
	for (i = 0; i < size(); i++)
		*(ptr + i) = val;
};


REAL d_points::mean() const {
	if (Z)
		return mean_value(Z->begin(), Z->end(), undef_value);
	return FLT_MAX;
};

REAL d_points::std(REAL mean) const {
	if (Z)
		return std_value(mean, Z->begin(), Z->end(), undef_value);
	return FLT_MAX;
};

bool d_points::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	if (X && Y) {
		minmax_value(X->begin(), X->end(), minx, maxx);
		minmax_value(Y->begin(), Y->end(), miny, maxy);
		return true;
	}
	return false;
};

bool d_points::getMinMaxZ(REAL & minz, REAL & maxz) const {
	if (Z) {
		minmax_value(Z->begin(), Z->end(), minz, maxz);
		return true;
	}
	return false;
};

void d_points::remove_with_value(REAL val) {
	int i,j;
	REAL z;
	int N = size();
	for (i = 0, j = 0; i < N; i++) {
		z = (*Z)(i);
		if (z != val) {
			(*Z)(j) = z;
			(*X)(j) = (*X)(i);
			(*Y)(j) = (*Y)(i);
			j++;
			continue;
		}
		
	}

	X->resize(j);
	Y->resize(j);
	Z->resize(j);

};

sub_points::sub_points(int icell_number, 
		       std::vector<size_t> * ipoint_numbers)
{
	cell_number = icell_number;
	point_numbers = ipoint_numbers;
};

sub_points::~sub_points() {
	delete point_numbers;
};

void sub_points::release() {
	delete this;
};

REAL sub_points::value(const d_points * pnts) const {
	std::vector<size_t>::const_iterator ptr;
	
	REAL value = REAL(0);
	REAL temp_value;
	int cnt = 0;
	REAL * z_ptr = pnts->Z->begin();
	for (ptr = point_numbers->begin(); ptr != point_numbers->end(); ptr++) {
		temp_value = *(z_ptr + *ptr);
		if (temp_value == undef_value)
			return undef_value;
		value += temp_value;
		cnt++;
	}
	value /= REAL(cnt);
	return value;
};

REAL sub_points::sum_value(const d_points * pnts) const {
	std::vector<size_t>::const_iterator ptr;
	
	REAL value = REAL(0);
	REAL temp_value;
	REAL * z_ptr = pnts->Z->begin();
	for (ptr = point_numbers->begin(); ptr != point_numbers->end(); ptr++) {
		temp_value = *(z_ptr + *ptr);
		if (temp_value == undef_value)
			return undef_value;
		value += temp_value;
	}
	return value;
};

void sub_points::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy, const d_points * pnts) const
{
	minx = FLT_MAX;
	maxx = -FLT_MAX;
	miny = FLT_MAX;
	maxy = -FLT_MAX;

	REAL x, y;

	std::vector<size_t>::const_iterator ptr;
	for (ptr = point_numbers->begin(); ptr != point_numbers->end(); ptr++) {
		x = (*(pnts->X))(*ptr);
		y = (*(pnts->Y))(*ptr);
		minx = MIN(x, minx);
		maxx = MAX(x, maxx);
		miny = MIN(y, miny);
		maxy = MAX(y, maxy);
	}

};

void _sort_points(const d_points * pnts, 
		  std::vector<size_t> * nums,
		  REAL **& sortx_begin, 
		  REAL **& sortx_end, 
		  REAL **& sorty_begin, 
		  REAL **& sorty_end) {


	if (pnts->X == NULL)
		return;

	if (pnts->Y == NULL)
		return;

	int ppnts_size = nums->size();
	REAL ** ptr;
	
	sortx_begin = (REAL**) malloc( sizeof(REAL*) * ppnts_size );
	sortx_end = sortx_begin + ppnts_size;
	int cnt;
    
	REAL * x_ptr = pnts->X->begin();
	for (cnt = 0; cnt < ppnts_size; cnt++) {
		ptr = sortx_begin + cnt;
		*ptr = ( x_ptr + *(nums->begin()+cnt) );
	}
	
	std::sort(sortx_begin, sortx_end, ptr_vector_less);
	
	sorty_begin = (REAL**) malloc( sizeof(REAL*) * ppnts_size );
	sorty_end = sorty_begin + ppnts_size;
	
	REAL * y_ptr = pnts->Y->begin();
	for (cnt = 0; cnt < ppnts_size; cnt++) {
		ptr = sorty_begin + cnt;
		*ptr = ( y_ptr + *(nums->begin()+cnt) );
	}
	
	std::sort(sorty_begin, sorty_end, ptr_vector_less);

};

void _points_transform(vec * X, vec * Y, 
		       REAL shiftX, REAL scaleX, 
		       REAL shiftY, REAL scaleY) {
	REAL * ptr_X;
	REAL * ptr_Y;
	for (ptr_X = X->begin(); ptr_X != X->end(); ptr_X++) 
        *ptr_X = ( *ptr_X - shiftX ) * scaleX; 
	
	for (ptr_Y = Y->begin(); ptr_Y != Y->end(); ptr_Y++) 
		*ptr_Y = ( *ptr_Y - shiftY ) * scaleY;
};

void _inverse_points_transform(d_points * pnts, 
			       REAL shiftX, REAL scaleX, 
			       REAL shiftY, REAL scaleY) {

	if (pnts->X == NULL)
		return;

	if (pnts->Y == NULL)
		return;

	REAL * ptr_X;
	REAL * ptr_Y;
	for (ptr_X = pnts->X->begin(); ptr_X != pnts->X->end(); ptr_X++) 
	        *ptr_X = *ptr_X/scaleX + shiftX;
	
	for (ptr_Y = pnts->Y->begin(); ptr_Y != pnts->Y->end(); ptr_Y++) 
        	*ptr_Y = *ptr_Y/scaleY + shiftY;
};


std::vector<d_points *>     * surfit_pnts = NULL;

/*! \struct pnts_garbage
    \brief struct for deletion of \ref d_points pointers
*/
struct pnts_garbage : public binman {
	//! inits \ref surfit_pnts
	pnts_garbage() {
		surfit_pnts = new std::vector<d_points *>;
	};
	//! removes \ref surfit_task and \ref surfit_tasks
	~pnts_garbage() {
		if (surfit_pnts) {
			release_elements(surfit_pnts->begin(), surfit_pnts->end());
			delete surfit_pnts;
			surfit_pnts = NULL;
		}
	};

};

pnts_garbage pnts_garb;


}; // namespace surfit;

