
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
#include "flow_curv.h"
#include "flow_points.h"
#include "curv.h"
#include "grid.h"
#include "points.h"
#include "vec.h"
#include "bitvec.h"

#include "grid_user.h"

namespace surfit {

f_flow_curv::f_flow_curv(REAL ivalue, d_curv * icrv) :
functional("f_flow_curv", F_USUAL)
{
	crv = icrv;
	value = ivalue;
	if (crv->getName()) {
		setNameF("f_flow_curv %s", crv->getName());
	}
	d_pnts = NULL;
	f_points = NULL;
};

f_flow_curv::~f_flow_curv() {
	cleanup();
};

void f_flow_curv::cleanup() {
	if (d_pnts)
		d_pnts->release_private();
	delete f_points;
	d_pnts = NULL;
	f_points = NULL;
};

int f_flow_curv::this_get_data_count() const {
	return 1;
};

const data * f_flow_curv::this_get_data(int pos) const {
	if (pos == 0)
		return crv;
	return NULL;
};

void f_flow_curv::create_f_flow_points() {

	if (d_pnts == NULL) {
		d_grid * grd = create_last_grd();
		d_pnts = discretize_pcurv(crv, grd, value, crv->getName());
		if (grd)
			grd->release();
	}

	if (f_points == NULL)
		f_points = new f_flow_points(d_pnts);

	if ( cond() ) { 
		if (f_points->cond())
			f_points->cond_erase_all();
		int i;
		for (i = 0; i < (int)functionals_cond->size(); i++) {
			functional * cnd = (*functionals_cond)[i];
			f_points->cond_add(cnd);
		}
		
	}
};

bool f_flow_curv::minimize() {
	create_f_flow_points();
	return f_points->minimize();
};

bool f_flow_curv::make_matrix_and_vector(matr *& matrix, extvec *& v) {
	create_f_flow_points();
	return f_points->make_matrix_and_vector(matrix, v);
};

void f_flow_curv::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	create_f_flow_points();
	f_points->mark_solved_and_undefined(mask_solved, mask_undefined, i_am_cond);
};

bool f_flow_curv::solvable_without_cond(const bitvec * mask_solved,
				       const bitvec * mask_undefined,
				       const extvec * X)
{

	size_t i;
	for (i = 0; i < mask_solved->size(); i++) {
		if (mask_solved->get(i))
			goto sss;
	}

	return false;

sss:
	
	return true;

};



d_points * discretize_pcurv(const d_curv * crv, d_grid * grd, REAL value, const char * task_name) {
		
	if (!crv)
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

	vec * points_z = create_vec(points_x->size(), value/REAL(points_x->size()));

	d_points * res = create_points(points_x,
				       points_y,
				       points_z,
				       task_name);

	return res;

};


}; // namespace surfit;

