
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
#include "curv.h"
#include "curv_user.h"
#include "free_elements.h"
#include "vec.h"
#include "task.h"
#include "grid.h"
#include "user.h"

namespace surfit {

curv                    *  surfit_curv     = NULL;
std::vector<curv *>     * surfit_curvs     = NULL;

/*! \struct curv_garbage
    \brief struct for deletion of \ref curv pointers
*/
struct curv_garbage : public binman {
	//! inits \ref surfit_curv and \ref surfit_curvs
	curv_garbage() {
		surfit_curv = NULL;
		surfit_curvs = new std::vector<curv *>;
	}
	//! removes \ref surfit_curv and \ref surfit_curvs
	~curv_garbage() {
		delete surfit_curv;
		if (surfit_curvs) {
			free_elements(surfit_curvs->begin(), surfit_curvs->end());
			delete surfit_curvs;
		}
	}

};

curv_garbage curv_garb;


task * discretize_curv(curv * crv, grid * grd, REAL value, const char * task_name) {
		
	if (!crv)
		return NULL;

	// using modified brezengham algorithm
	int qq;
	REAL X2, X1, Y2, Y1;

	vec * points_x = new vec();
	vec * points_y = new vec();
		
	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = *(crv->X_begin + qq);
		X2 = *(crv->X_begin + qq + 1);
		Y1 = *(crv->Y_begin + qq);
		Y2 = *(crv->Y_begin + qq + 1);
		
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

	vec * points_z = new vec(points_x->size(), value);

	task * res = new task(points_x->ref_begin(), points_x->end(),
		                      points_y->ref_begin(), points_y->end(),
							  points_z->ref_begin(), points_z->end(),
							  task_name);

	points_x->drop_data();
	delete points_x;
	points_y->drop_data();
	delete points_y;
	points_z->drop_data();
	delete points_z;
		
	return res;

};

}; // namespace surfit;

