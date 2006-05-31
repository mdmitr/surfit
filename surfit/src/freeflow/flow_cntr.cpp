
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

#include "flow_ie.h"
#include "flow_cntr.h"
#include "cntr.h"
#include "flow_points.h"
#include "points.h"
#include "free_elements.h"
#include "grid.h"
#include "geom_alg.h"
#include "vec.h"
#include "bitvec.h"

#include "grid_user.h"

#include <algorithm>

namespace surfit {

f_flow_cntr::f_flow_cntr(d_cntr * icontour) :
functional("f_flow_cntr", F_USUAL)
{
	contour = icontour;
	if (contour->getName()) {
		setNameF("f_flow_cntr %s", contour->getName());
	}
	d_pnts = NULL;
	f_points = NULL;
};

f_flow_cntr::~f_flow_cntr() {
	cleanup();
};

void f_flow_cntr::cleanup() {
	if (d_pnts)
		d_pnts->release_private();
	delete f_points;
	d_pnts = NULL;
	f_points = NULL;
};

int f_flow_cntr::this_get_data_count() const {
	return 1;
};

const data * f_flow_cntr::this_get_data(int pos) const {
	if (pos == 0)
		return contour;
	return NULL;
};

void f_flow_cntr::create_f_flow_points() {

	if (d_pnts == NULL) {
		d_grid * grd = create_last_grd();
		d_pnts = discretize_pcntr(contour, grd, contour->getName());
		if (grd)
			grd->release();
	}

	if (f_points == NULL)
		f_points = new f_flow_points(d_pnts);

	if ( cond() ) { 
		if ( f_points->cond() )
			f_points->cond_erase_all();
		int i;
		for (i = 0; i < (int)functionals_cond->size(); i++) {
			functional * cnd = (*functionals_cond)[i];
			f_points->cond_add(cnd);
		}
		
	}
};

bool f_flow_cntr::minimize() {
	create_f_flow_points();
	return f_points->minimize();
};

bool f_flow_cntr::make_matrix_and_vector(matr *& matrix, vec *& v) {
	create_f_flow_points();
	return f_points->make_matrix_and_vector(matrix, v);
};

void f_flow_cntr::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	create_f_flow_points();
	f_points->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
};

bool f_flow_cntr::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const vec * X)
{

	int i;
	for (i = 0; i < mask_solved->size(); i++) {
		if (mask_solved->get(i))
			goto sss;
	}

	return false;

sss:
	
	return true;

};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct pos_s {
	int pos;
	REAL s; // square
};
#endif


inline
bool ptr_pos_s_less(const pos_s & it1, const pos_s & it2) 
{
	return it1.pos < it2.pos;
};

bool add_square_val(d_grid * grd, int x, int y,
                    REAL X1, REAL Y1, REAL Z1,
                    REAL X2, REAL Y2, REAL Z2,
                    std::vector<pos_s> * data) {

	REAL rx1, rx2;
	REAL ry1, ry2;
	int NN = grd->getCountX();

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

	REAL dist1 = sqrt((X1-lx1)*(X1-lx1) + (Y1-ly1)*(Y1-ly1));
	lz1 = Z1 + dz*dist1/max_dist;

	REAL dist2 = sqrt((X1-lx2)*(X1-lx2) + (Y1-ly2)*(Y1-ly2));
	lz2 = Z1 + dz*dist2/max_dist;

	REAL dist = sqrt( (lx1-lx2)*(lx1-lx2) + (ly1-ly2)*(ly1-ly2) );

	pos_s elem;
	elem.pos =  x + NN*y;
	elem.s = (lz2+lz1)*dist/REAL(2);
	
	data->push_back(elem);

	return true;
};

d_points * discretize_pcntr(const d_cntr * pcrv, d_grid * grd, const char * task_name) {
	
	if (!pcrv)
		return NULL;

	// using modified brezengham algorithm
	int qq;
	REAL X2, X1, Y2, Y1, Z1, Z2;

	std::vector<pos_s> * data = new std::vector<pos_s>();
	
	for (qq = 0; qq < pcrv->size()-1; qq++) {
		X1 = (*(pcrv->X))(qq);
		Y1 = (*(pcrv->Y))(qq);
		Z1 = (*(pcrv->Z))(qq);
		X2 = (*(pcrv->X))(qq + 1);
		Y2 = (*(pcrv->Y))(qq + 1);
		Z2 = (*(pcrv->Z))(qq + 1);

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
			add_square_val(grd, x1, y1, 
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
			
			add_square_val(grd, x, y, 
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
						bool change = true;
						x -= kx;
						y += ky;
						add_square_val(grd, x, y, 
							       X1, Y1, Z1, 
							       X2, Y2, Z2,
							       data);
						x += kx;
					} else {
						add_square_val(grd, x, y, 
				                       	       X1, Y1, Z1, 
						               X2, Y2, Z2,
				                       	       data);
						y += ky; // прирост высоты 
					}
					
				} else {
					
					if (fabs( DX*(Y_0-Y1) + DY*(X1-X_1) ) - fabs( DX*(Y_1-Y1) + DY*(X1-X_0)) < 0) {
						
						y -= ky;
						x += kx;
						
						add_square_val(grd, x, y, 
				                               X1, Y1, Z1, 
						               X2, Y2, Z2,
				                               data);

						y += ky;
						
					} else {
						
						add_square_val(grd, x, y, 
				                               X1, Y1, Z1, 
						               X2, Y2, Z2,
				                               data);

						x += kx;
					}
				}
				
				d += i2;
			}
		}
		
		add_square_val(grd, x, y, 
			       X1, Y1, Z1, 
			       X2, Y2, Z2,
			       data); // последняя точка 
		
	}


	std::sort(data->begin(), data->end(), ptr_pos_s_less);

	vec * points_x = create_vec();
	vec * points_y = create_vec();
	vec * points_z = create_vec();

	points_x->reserve(data->size());
	points_y->reserve(data->size());
	points_z->reserve(data->size());

	int prev_pos = INT_MAX;
	pos_s elem;
	REAL total_weight = 0;
	REAL sum_val = 0;
	int NN = grd->getCountX();
	
	for (qq = 0; qq < (int)data->size(); qq++) {
		elem = (*data)[qq];
		if (prev_pos == elem.pos) {
			sum_val += elem.s;
		} else {
			// write
			if (prev_pos != INT_MAX) {
				int pos_x = prev_pos % NN;
				int pos_y = (prev_pos - pos_x)/NN;
				REAL x, y, z;
				grd->getCoordNode(pos_x, pos_y, x, y);
				z = sum_val;
				points_x->push_back(x);
				points_y->push_back(y);
				points_z->push_back(z);
			}
			//
			sum_val = elem.s;
		}
		prev_pos = elem.pos;
	};

	int pos_x = prev_pos % NN;
	int pos_y = (prev_pos - pos_x)/NN;
	REAL x, y, z;
	grd->getCoordNode(pos_x, pos_y, x, y);
	z = sum_val;
	points_x->push_back(x);
	points_y->push_back(y);
	points_z->push_back(z);

	points_x->resize(points_x->size());
	points_y->resize(points_y->size());
	points_z->resize(points_z->size());

	delete data;
	
	d_points * res = create_points(points_x, points_y, points_z,
			               task_name);

	return res;
};


}; // namespace surfit;

