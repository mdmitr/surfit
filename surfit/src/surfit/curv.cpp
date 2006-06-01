
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

#include "vec.h"

#include "curv.h"
#include "points.h"
#include "free_elements.h"
#include "grid.h"

#include <math.h>
#include <algorithm>
#include <float.h>

namespace surfit {

d_curv * create_curv(vec * iX, vec * iY,
		     const char * curv_name) 
{
	return new d_curv(iX, iY, curv_name);
};

d_curv * create_curv(const d_curv * src) 
{

	size_t size = src->size();
	vec * X = create_vec(*(src->X));
	vec * Y = create_vec(*(src->Y));
	
	return new d_curv(X, Y, src->getName());
};

d_curv::d_curv(vec * iX, vec * iY, const char * curv_name) : data("curv") 
{
	X = iX;
	Y = iY;
	setName(curv_name);
};

d_curv::~d_curv() {
	if (X)
		X->release();
	if (Y)
		Y->release();
};

bool d_curv::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	if (X && Y) {
		minx = *std::min_element(X->begin(), X->end());
		maxx = *std::max_element(X->begin(), X->end());
		miny = *std::min_element(Y->begin(), Y->end());
		maxy = *std::max_element(Y->begin(), Y->end());
		return true;
	}
	return false;
};

size_t d_curv::size() const {
	if (X)
		return X->size();
	return 0;
};

bool d_curv::is_closed() const {
	size_t s = size();
	if (s <= 1)
		return false;
	bool x_equals = ( (*X)(0) == (*X)(s - 1));
	bool y_equals = ( (*Y)(0) == (*Y)(s - 1));
	return (x_equals && y_equals);
};

void d_curv::close() {
	if (is_closed()) 
		return;

	size_t old_size = size();
	if (old_size == 0)
		return;

	X->resize(old_size+1);
	Y->resize(old_size+1);

	(*X)(old_size) = (*X)(0);
	(*Y)(old_size) = (*Y)(0);

};

REAL d_curv::minx() const {
	if (X)
		return *std::min_element(X->begin(), X->end());
	return FLT_MAX;
};

REAL d_curv::maxx() const {
	if (X)
		return *std::max_element(X->begin(), X->end());
	return -FLT_MAX;
};

REAL d_curv::miny() const {
	if (Y)
		return *std::min_element(Y->begin(), Y->end());
	return FLT_MAX;
};

REAL d_curv::maxy() const {
	if (Y)
		return *std::max_element(Y->begin(), Y->end());
	return -FLT_MAX;
};

REAL d_curv::length_xy() const {
	REAL len = REAL(0);
	if (size() == 0)
		return len;
	
	const REAL * x_ptr = X->begin();
	const REAL * y_ptr = Y->begin();

	if (size() == 0)
		return len;

	while (x_ptr != X->end()-1) {
		len += sqrt( (*x_ptr - *(x_ptr+1))*(*x_ptr - *(x_ptr+1)) + (*y_ptr - *(y_ptr+1))*(*y_ptr - *(y_ptr+1)) );
		x_ptr++;
		y_ptr++;
	}
	return len;
};

bool d_curv::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

bool d_curv::in_region(REAL x, REAL y) const {
	size_t N = size();
	if (N == 0)
		return false;
	
	REAL x0 = (*X)(0);
	REAL x1 = (*X)(N-1);
	if (x0 != x1)
		return false;
	
	REAL y0 = (*Y)(0);
	REAL y1 = (*Y)(N-1);
	if (y0 != y1)
		return false;

	REAL * X_begin = X->begin();
	REAL * Y_begin = Y->begin();

	size_t i;
	int test=0;
	REAL x2,y2;

	for ( i=0; i< N-1; i++ ) {
		if( ( *(Y_begin+i) <= y) || ( *(Y_begin+i+1) <= y ) ) {
			if( !( ((*(X_begin+i) < x)&&(*(X_begin+i+1)<x)) || ((*(X_begin+i)>x)&&(*(X_begin+i+1)>x)) ) ) {
				if( (*(X_begin+i)!=x) && (*(X_begin+i+1) != x) )
				{
					if( (*(Y_begin+i)>y)||(*(Y_begin+i+1)>y) )
					{
						x1=x-*(X_begin+i);
						x2=*(X_begin+i+1)-x;
						y1=y-*(Y_begin+i);
						y2=*(Y_begin+i+1)-y;

						if( *(Y_begin+i)<=y )
						{
							if( fabs(y1*x2)-fabs(y2*x1)>0 ) test++;
						}
						else  if( fabs(y2*x1)-fabs(y1*x2)>0) test++;
					}
					else test++;
				}
				else
				{
					if(( *(X_begin+i)>x ) && (*(X_begin+i+1) != x) )
					{
						if( *(Y_begin+i+1)<=y )  test++;
					}
					else
					{
						if ( ( *(X_begin+i+1)>x) /*&& (p[i].x != x)*/)
						{
							if( *(Y_begin+i)<=y ) test++;
						}
						else
						{ 
							if( *(X_begin+i)==x && *(X_begin+i+1)==x ) {
								if( (*(Y_begin+i)>y)||(*(Y_begin+i+1)>y) )
									return true;
							}
						}
						if ( (*(X_begin+i+1) == x) || (*(X_begin+i) == x) ) {
							if( (*(Y_begin+i)==y) && (*(Y_begin+i+1)==y) )
									return true;
						}
					}
				}
			}
		}
	}
	
	return (test%2) == 1;
};












std::vector<d_curv *>     * surfit_curvs     = NULL;

/*! \struct curv_garbage
    \brief struct for deletion of \ref curv pointers
*/
struct curv_garbage : public binman {
	//! inits \ref surfit_curv and \ref surfit_curvs
	curv_garbage() {
		surfit_curvs = new std::vector<d_curv *>;
	}
	//! removes \ref surfit_curv and \ref surfit_curvs
	~curv_garbage() {
		if (surfit_curvs) {
			release_elements(surfit_curvs->begin(), surfit_curvs->end());
			delete surfit_curvs;
			surfit_curvs = NULL;
		}
	}

};

curv_garbage curv_garb;

d_points * discretize_curv(const d_curv * crv, d_grid * grd, REAL value, const char * pnts_name) {
		
	if (!crv)
		return NULL;

	if (crv->size() == 0)
		return NULL;

	// using modified brezengham algorithm
	size_t qq;
	REAL X2, X1, Y2, Y1;

	vec * points_x = create_vec();
	vec * points_y = create_vec();
		
	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = (*(crv->X))(qq);
		X2 = (*(crv->X))(qq + 1);
		Y1 = (*(crv->Y))(qq);
		Y2 = (*(crv->Y))(qq + 1);
		
		size_t x1 = grd->get_i(X1);
		size_t x2 = grd->get_i(X2);
		size_t y1 = grd->get_j(Y1);
		size_t y2 = grd->get_j(Y2);
			
		int dx, dy, i1, i2, i, kx, ky;
		int d;      // "отклонение" 
		size_t x, y;
		int flag;
			
		dy = y2 - y1;
		dx = x2 - x1;
		REAL DY = Y2-Y1;
		REAL DX = X2-X1;

		REAL p_x, p_y;
		
		if (dx == 0 && dy == 0) {// only one point
			grd->getCoordNode(x1, y1, p_x, p_y);
			points_x->push_back(p_x);
			points_y->push_back(p_y);
			continue; 
		}
		
		kx = 1; // шаг по x
		ky = 1; // шаг по y
			
		// Выбор тактовой оси
		if ( dx < 0 ) { 
			dx = -dx; 
			kx = -1;       // Y
		} else {
			if(dx == 0)
				kx = 0;    // X 
		}
			
		if (dy < 0) { 
			dy = -dy; 
			ky = -1; 
		}
		
		if (dx < dy) { 
			flag = 0; 
			d = dx; 
			dx = dy; 
			dy = d; 
		}
		else         
			flag = 1;
		
		i1 = dy + dy; d = i1 - dx; i2 = d - dx;
		x = x1; y = y1;
						
		for ( i = 0; i < dx; i++ ) {
			
			grd->getCoordNode(x,y,p_x,p_y);
			points_x->push_back(p_x);
			points_y->push_back(p_y);
			
			if (flag) 
				x += kx; // шаг по такт. оси   
			else     
				y += ky;
			
			if( d < 0 ) {// горизонтальный шаг   
				d += i1;
			} else {       // диагональный шаг        
				
				int x_0;
				int x_1;
				int y_0;
				int y_1;
				
				if (flag) {
					x_0 = x-kx;
					x_1 = x;
					y_0 = y;
					y_1 = y+ky;
				} else {
					y_0 = y-ky;
					y_1 = y;
					x_0 = x;
					x_1 = x+kx;
				}
				REAL X_0 = grd->getCoordNodeX(x_0);
				REAL X_1 = grd->getCoordNodeX(x_1);
				REAL Y_0 = grd->getCoordNodeY(y_0);
				REAL Y_1 = grd->getCoordNodeY(y_1);
				
				if (flag) {
					
					if (fabs( DY*(X_0-X1) + DX*(Y1-Y_1) ) - fabs( DY*(X_1-X1) + DX*(Y1-Y_0)) < 0) {
						bool change = true;
						x -= kx;
						y += ky;
						grd->getCoordNode(x,y,p_x,p_y);
						points_x->push_back(p_x);
						points_y->push_back(p_y);
						x += kx;
					} else {
						grd->getCoordNode(x,y,p_x,p_y);
						points_x->push_back(p_x);
						points_y->push_back(p_y);
						y += ky; // прирост высоты 
					}
					
				} else {
					
					if (fabs( DX*(Y_0-Y1) + DY*(X1-X_1) ) - fabs( DX*(Y_1-Y1) + DY*(X1-X_0)) < 0) {
						
						y -= ky;
						x += kx;
						
						grd->getCoordNode(x,y,p_x,p_y);
						points_x->push_back(p_x);
						points_y->push_back(p_y);
						y += ky;
						
					} else {
						
						grd->getCoordNode(x,y,p_x,p_y);
						points_x->push_back(p_x);
						points_y->push_back(p_y);
						x += kx;
					}
				}
				
				d += i2;
			}
		}
		
		grd->getCoordNode(x,y,p_x,p_y);
		points_x->push_back(p_x);
		points_y->push_back(p_y); // последняя точка 
		
	}

	vec * points_z = create_vec(points_x->size(), value);

	d_points * res = create_points(points_x, points_y, points_z, pnts_name);
		
	return res;

};

}; // namespace surfit;

