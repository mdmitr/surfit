
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
#include "cntr.h"
#include "vec_alg.h"
#include "free_elements.h"
#include "grid.h"
#include "geom_alg.h"
#include "vec.h"
#include "points.h"

#include <algorithm>

namespace surfit {

d_cntr * create_cntr(vec * iX, vec * iY, vec * iZ,
	             const char * cntr_name)
{
	return new d_cntr(iX, iY, iZ, cntr_name);
};

d_cntr * create_cntr(d_curv * crv, REAL z_value,
	             const char * cntr_name)
{
	return new d_cntr(crv, z_value, cntr_name);
};


d_cntr::d_cntr(vec * iX, vec * iY, vec * iZ,
	   const char * cntr_name) : 
d_curv(iX, iY, cntr_name)
{
	setType("cntr");
	Z = iZ;
};

d_cntr::d_cntr(d_curv * crv, REAL z_value,
	   const char * cntr_name) : 
d_curv(create_vec(*(crv->X)), create_vec(*(crv->Y)), cntr_name)
{
	setType("cntr");
	Z = create_vec(size(), z_value);
};

d_cntr::~d_cntr() {
	if (Z)
		Z->release();
};

REAL d_cntr::minz() const {
	if (Z)
		return *std::min_element(Z->begin(), Z->end());
	return FLT_MAX;
};

REAL d_cntr::maxz() const {
	if (Z)
		return *std::max_element(Z->begin(), Z->end());
	return -FLT_MAX;
};

bool d_cntr::getMinMaxZ(REAL & minz, REAL & maxz) const {
	if (Z) {
		minmax_value(Z->begin(), Z->end(), minz, maxz);
		return true;
	}
	return false;
};

void d_cntr::plus(REAL value) {
	if (Z == NULL)
		return;
	vec::iterator ptr;
	for (ptr = Z->begin(); ptr != Z->end(); ptr++) 
		*ptr += value;
}; 
	
void d_cntr::minus(REAL value) {
	if (Z == NULL)
		return;
	vec::iterator ptr;
	for (ptr = Z->begin(); ptr != Z->end(); ptr++) 
		*ptr -= value;
};

void d_cntr::mult(REAL value) {
	if (Z == NULL)
		return;
	vec::iterator ptr;
	for (ptr = Z->begin(); ptr != Z->end(); ptr++) 
		*ptr *= value;
};

void d_cntr::div(REAL value) {
	if (Z == NULL)
		return;
	vec::iterator ptr;
	for (ptr = Z->begin(); ptr != Z->end(); ptr++) 
		*ptr /= value;
};

void d_cntr::normalize(REAL eps)
{
	if (size() < 1)
		return;

	vec * newX = create_vec();
	newX->reserve(size());
	vec * newY = create_vec();
	newY->reserve(size());
	vec * newZ = create_vec();
	newZ->reserve(size());

	newX->push_back( (*X)(0) );
	newY->push_back( (*Y)(0) );
	newZ->push_back( (*Z)(0) );

	REAL prev_x = (*X)(0);
	REAL prev_y = (*Y)(0);
	REAL prev_z = (*Z)(0);

	size_t i;
	for (i = 1; i < size(); i++) {
		REAL x1 = (*X)(i);
		REAL y1 = (*Y)(i);
		REAL z1 = (*Z)(i);

		REAL dist = (x1-prev_x)*(x1-prev_x) + (y1-prev_y)*(y1-prev_y) + (z1-prev_z)*(z1-prev_z);
		if (dist < eps)
			continue;

		newX->push_back(x1);
		newY->push_back(y1);
		newZ->push_back(z1);
		prev_x = x1;
		prev_y = y1;
		prev_z = z1;
	}

	X->release();
	Y->release();
	Z->release();
	X = newX;
	Y = newY;
	Z = newZ;
};










void cntrs_container::push_back(d_cntr * elem)
{
	data->push_back(elem);
};

cntrs_container * surfit_cntrs = NULL;

/*! \struct cntr_garbage
    \brief struct for deletion of \ref cntr pointers
*/
struct cntr_garbage : public binman {
	//! inits \ref surfit_cntr and \ref surfit_cntrs
	cntr_garbage() {
		surfit_cntrs = new cntrs_container();
	};
	//! removes \ref surfit_cntr and \ref surfit_cntrs
	~cntr_garbage() {
		if (surfit_cntrs) {
			release_elements(surfit_cntrs->begin(), surfit_cntrs->end());
			delete surfit_cntrs;
			surfit_cntrs = NULL;
		}
	};
};

cntr_garbage cntr_garb;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct pos_z_w {
	size_t pos;
	REAL z;
	REAL w;
};
#endif

inline
bool ptr_pos_z_w_less(const pos_z_w & it1, const pos_z_w & it2) 
{
	return it1.pos < it2.pos;
};

bool add_mean_val(d_grid * grd, size_t x, size_t y,
		  REAL X1, REAL Y1, REAL Z1,
		  REAL X2, REAL Y2, REAL Z2,
		  std::vector<pos_z_w> * data) {

	REAL rx1, rx2;
	REAL ry1, ry2;
	size_t NN = grd->getCountX();

	REAL lx1 = X1, lx2 = X2, ly1 = Y1, ly2 = Y2;
	
	grd->getCoordNode(x, y, rx1, ry1);
	rx1 -= grd->stepX/REAL(2);
	ry1 -= grd->stepY/REAL(2);
	rx2 = rx1 + grd->stepX;
	ry2 = ry1 + grd->stepY;

	if (!get_line_in_rect(rx1, ry1, rx2, ry2,
		                  lx1, ly1, lx2, ly2))
		return false;


	REAL lz1, lz2;

	REAL dz = Z2-Z1;

	REAL max_dist = sqrt((X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1));
	if (max_dist == 0)
		return false;

	REAL dist1 = sqrt((X1-lx1)*(X1-lx1) + (Y1-ly1)*(Y1-ly1));
	lz1 = Z1 + dz*dist1/max_dist;

	REAL dist2 = sqrt((X1-lx2)*(X1-lx2) + (Y1-ly2)*(Y1-ly2));
	lz2 = Z1 + dz*dist2/max_dist;

	REAL dist = sqrt( (lx1-lx2)*(lx1-lx2) + (ly1-ly2)*(ly1-ly2) );

	pos_z_w elem;
	elem.pos =  x + NN*y;
	elem.z = (lz1+lz2)/REAL(2);
	elem.w =  dist;

	data->push_back(elem);

	return true;
};

d_points * discretize_cntr(const d_cntr * crv, d_grid * grd, const char * pnts_name) {
	
	if (!crv)
		return NULL;

	if (crv->size() == 0)
		return NULL;

	// using modified brezengham algorithm
	size_t qq;
	REAL X2, X1, Y2, Y1, Z1, Z2;

	std::vector<pos_z_w> * data = new std::vector<pos_z_w>();
	
	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = (*(crv->X))(qq);
		Y1 = (*(crv->Y))(qq);
		Z1 = (*(crv->Z))(qq);
		X2 = (*(crv->X))(qq + 1);
		Y2 = (*(crv->Y))(qq + 1);
		Z2 = (*(crv->Z))(qq + 1);

		int x1 = grd->get_i(X1);
		int x2 = grd->get_i(X2);
		int y1 = grd->get_j(Y1);
		int y2 = grd->get_j(Y2);
			
		int dx, dy, i1, i2, i, kx, ky;
		int d;      // "отклонение" 
		int x, y;
		int flag;
			
		dy = y2 - y1;
		dx = x2 - x1;
		REAL DY = Y2-Y1;
		REAL DX = X2-X1;

		if (dx == 0 && dy == 0) // only one point
		{
			add_mean_val(grd, x1, y1, 
				     X1, Y1, Z1, 
				     X2, Y2, Z2,
				     data);
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
			
			add_mean_val(grd, x, y, 
				     X1, Y1, Z1, 
				     X2, Y2, Z2,
				     data);
			
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
						x -= kx;
						y += ky;
						add_mean_val(grd, x, y, 
							         X1, Y1, Z1, 
							         X2, Y2, Z2,
							         data);
						x += kx;
					} else {
						add_mean_val(grd, x, y, 
				                     X1, Y1, Z1, 
						             X2, Y2, Z2,
				                     data);
						y += ky; // прирост высоты 
					}
					
				} else {
					
					if (fabs( DX*(Y_0-Y1) + DY*(X1-X_1) ) - fabs( DX*(Y_1-Y1) + DY*(X1-X_0)) < 0) {
						
						y -= ky;
						x += kx;
						
						add_mean_val(grd, x, y, 
				                     X1, Y1, Z1, 
						             X2, Y2, Z2,
				                     data);

						y += ky;
						
					} else {
						
						add_mean_val(grd, x, y, 
				                     X1, Y1, Z1, 
						             X2, Y2, Z2,
				                     data);

						x += kx;
					}
				}
				
				d += i2;
			}
		}
		
		add_mean_val(grd, x, y, 
			     X1, Y1, Z1, 
			     X2, Y2, Z2,
			     data); // последняя точка 
		
	}

	if (data->size() == 0)
	{
		delete data;
		return NULL;
	}

	std::sort(data->begin(), data->end(), ptr_pos_z_w_less);

	vec * points_x = create_vec();
	vec * points_y = create_vec();
	vec * points_z = create_vec();

	points_x->reserve(data->size());
	points_y->reserve(data->size());
	points_z->reserve(data->size());

	size_t prev_pos = UINT_MAX;
	pos_z_w elem;
	REAL total_weight = 0;
	REAL sum_val = 0;
	size_t NN = grd->getCountX();
	
	for (qq = 0; qq < data->size(); qq++) {
		elem = (*data)[qq];
		if (prev_pos == elem.pos) {
			sum_val += elem.w*elem.z;
			total_weight += elem.w;
		} else {
			// write
			if (prev_pos != UINT_MAX) {
				size_t pos_x = prev_pos % NN;
				size_t pos_y = (prev_pos - pos_x)/NN;
				REAL x, y, z;
				grd->getCoordNode(pos_x, pos_y, x, y);
				z = sum_val / total_weight;
				points_x->push_back(x);
				points_y->push_back(y);
				points_z->push_back(z);
			}
			//
			sum_val = elem.w*elem.z;
			total_weight = elem.w;
		}
		prev_pos = elem.pos;
	};

	size_t pos_x = prev_pos % NN;
	size_t pos_y = (prev_pos - pos_x)/NN;
	REAL x, y, z;
	grd->getCoordNode(pos_x, pos_y, x, y);
	z = sum_val / total_weight;
	points_x->push_back(x);
	points_y->push_back(y);
	points_z->push_back(z);

	points_x->resize(points_x->size());
	points_y->resize(points_y->size());
	points_z->resize(points_z->size());

	delete data;
	
	d_points * pnts = create_points(points_x, points_y, points_z,
			                pnts_name);
	
	return pnts;
};

d_points * discretize_cntr8(const d_cntr * crv, d_grid * grd, const char * pnts_name) 
{
	if (grd == NULL)
		return NULL;

	if (!crv)
		return NULL;

	if (crv->size() == 0)
		return NULL;

	// using modified brezengham algorithm
	size_t qq;
	REAL X2, X1, Y2, Y1, Z1, Z2;

	std::vector<pos_z_w> * data = new std::vector<pos_z_w>();
	
	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = (*(crv->X))(qq);
		Y1 = (*(crv->Y))(qq);
		Z1 = (*(crv->Z))(qq);
		X2 = (*(crv->X))(qq + 1);
		Y2 = (*(crv->Y))(qq + 1);
		Z2 = (*(crv->Z))(qq + 1);

		int x1 = grd->get_i(X1);
		int x2 = grd->get_i(X2);
		int y1 = grd->get_j(Y1);
		int y2 = grd->get_j(Y2);
			
		int dx, dy, i1, i2, i, kx, ky;
		int d;      // "отклонение" 
		int x, y;
		int flag;
			
		dy = y2 - y1;
		dx = x2 - x1;
		REAL DY = Y2-Y1;
		REAL DX = X2-X1;

		if (dx == 0 && dy == 0) // only one point
		{
			add_mean_val(grd, x1, y1, 
				     X1, Y1, Z1, 
				     X2, Y2, Z2,
				     data);
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
			
			add_mean_val(grd, x, y, 
				     X1, Y1, Z1, 
				     X2, Y2, Z2,
				     data);
			
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
						x -= kx;
						y += ky;
						/*
						add_mean_val(grd, x, y, 
							         X1, Y1, Z1, 
							         X2, Y2, Z2,
							         data);
						*/
						x += kx;
					} else {
						/*add_mean_val(grd, x, y, 
				                     X1, Y1, Z1, 
						             X2, Y2, Z2,
				                     data);*/
						y += ky; // прирост высоты 
					}
					
				} else {
					
					if (fabs( DX*(Y_0-Y1) + DY*(X1-X_1) ) - fabs( DX*(Y_1-Y1) + DY*(X1-X_0)) < 0) {
						
						y -= ky;
						x += kx;
						
						/*add_mean_val(grd, x, y, 
							X1, Y1, Z1, 
							X2, Y2, Z2,
							data);*/

						y += ky;
						
					} else {
						
						/*add_mean_val(grd, x, y, 
							X1, Y1, Z1, 
							X2, Y2, Z2,
							data);*/

						x += kx;
					}
				}
				
				d += i2;
			}
		}
		
		add_mean_val(grd, x, y, 
			     X1, Y1, Z1, 
			     X2, Y2, Z2,
			     data); // последняя точка 
		
	}

	if (data->size() == 0)
	{
		delete data;
		return NULL;
	}

	std::sort(data->begin(), data->end(), ptr_pos_z_w_less);

	vec * points_x = create_vec();
	vec * points_y = create_vec();
	vec * points_z = create_vec();

	points_x->reserve(data->size());
	points_y->reserve(data->size());
	points_z->reserve(data->size());

	size_t prev_pos = UINT_MAX;
	pos_z_w elem;
	REAL total_weight = 0;
	REAL sum_val = 0;
	size_t NN = grd->getCountX();
	
	for (qq = 0; qq < data->size(); qq++) {
		elem = (*data)[qq];
		if (prev_pos == elem.pos) {
			sum_val += elem.w*elem.z;
			total_weight += elem.w;
		} else {
			// write
			if (prev_pos != UINT_MAX) {
				size_t pos_x = prev_pos % NN;
				size_t pos_y = (prev_pos - pos_x)/NN;
				REAL x, y, z;
				grd->getCoordNode(pos_x, pos_y, x, y);
				z = sum_val / total_weight;
				points_x->push_back(x);
				points_y->push_back(y);
				points_z->push_back(z);
			}
			//
			sum_val = elem.w*elem.z;
			total_weight = elem.w;
		}
		prev_pos = elem.pos;
	};

	size_t pos_x = prev_pos % NN;
	size_t pos_y = (prev_pos - pos_x)/NN;
	REAL x, y, z;
	grd->getCoordNode(pos_x, pos_y, x, y);
	z = sum_val / total_weight;
	points_x->push_back(x);
	points_y->push_back(y);
	points_z->push_back(z);

	points_x->resize(points_x->size());
	points_y->resize(points_y->size());
	points_z->resize(points_z->size());

	delete data;
	
	d_points * pnts = create_points(points_x, points_y, points_z,
			                pnts_name);
	
	return pnts;
};

d_points * discretize_cntr(const d_cntr * crv, REAL step, const char * pnts_name) 
{
	if (!crv)
		return NULL;

	if (crv->size() == 0)
		return NULL;

	if (step == 0)
		return NULL;

	step = fabs(step);

	REAL len = crv->length_xy();

	vec * points_x = create_vec();
	vec * points_y = create_vec();
	vec * points_z = create_vec();

	points_x->reserve( (size_t)(len/step/4.) );
	points_y->reserve( (size_t)(len/step/4.) );
	points_z->reserve( (size_t)(len/step/4.) );

	size_t qq;
	REAL X2, X1, Y2, Y1, Z1, Z2;

	len = 0;
	REAL nlen=0;

	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = (*(crv->X))(qq);
		Y1 = (*(crv->Y))(qq);
		Z1 = (*(crv->Z))(qq);
		X2 = (*(crv->X))(qq + 1);
		Y2 = (*(crv->Y))(qq + 1);
		Z2 = (*(crv->Z))(qq + 1);

		REAL ri = sqrt( (X1-X2)*(X1-X2) + (Y1-Y2)*(Y1-Y2)  );
		if( fabs(ri) < 1E-12 ) continue;
		
		while( nlen <= len + ri )
		{
			REAL lambda = (nlen - len)/ri;
			REAL x = X1+lambda*(X2-X1);
			REAL y = Y1+lambda*(Y2-Y1);
			REAL z = Z1+lambda*(Z2-Z1);
			points_x->push_back(x);
			points_y->push_back(y);
			points_z->push_back(z);
			nlen += step;
		}

		len += ri;

	}

	if (points_x->size() == 0)
	{
		points_x->release();
		points_y->release();
		points_z->release();
		return NULL;
	}

	d_points * pnts = create_points(points_x, points_y, points_z,
			                pnts_name);
	return pnts;
};

}; // namespace surfit;

