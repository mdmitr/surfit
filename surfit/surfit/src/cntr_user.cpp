
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
#include "cntrs.h"
#include "fileio.h"
#include "cntr.h"
#include "task.h"
#include "grid.h"
#include "geom_alg.h"
#include "vec.h"
#include "free_elements.h"

#include "grid_user.h"
#include "task_user.h"
#include "cntr_user.h"

#include <algorithm>

namespace surfit {

////////////////////////////////////////////////
//
//  C N T R   G L O B A L  V A R I A B L E S
//
////////////////////////////////////////////////

cntr                    *  surfit_cntr     = NULL;
std::vector<cntr *>     * surfit_cntrs     = NULL;

/*! \struct cntr_garbage
    \brief struct for deletion of \ref cntr pointers
*/
struct cntr_garbage : public binman {
	//! inits \ref surfit_cntr and \ref surfit_cntrs
	cntr_garbage() {
		surfit_cntr = NULL;
		surfit_cntrs = new std::vector<cntr *>;
	};
	//! removes \ref surfit_cntr and \ref surfit_cntrs
	~cntr_garbage() {
		delete surfit_cntr;
		if (surfit_cntrs) {
			free_elements(surfit_cntrs->begin(), surfit_cntrs->end());
			delete surfit_cntrs;
		}
	};
};

cntr_garbage cntr_garb;


////////////////////////////////////////////////
//
//  C N T R   U S E F U L   F U N C T I O N S
//
////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct pos_z_w {
	int pos;
	REAL z;
	REAL w;
};
#endif

inline
bool ptr_pos_z_w_less(const pos_z_w & it1, const pos_z_w & it2) 
{
	return it1.pos < it2.pos;
};

bool add_mean_val(grid * grd, int x, int y,
		  REAL X1, REAL Y1, REAL Z1,
		  REAL X2, REAL Y2, REAL Z2,
		  std::vector<pos_z_w> * data) {

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

	pos_z_w elem;
	elem.pos =  x + NN*y;
	elem.z = (lz1+lz2)/REAL(2);
	elem.w =  dist;

	data->push_back(elem);

	return true;
};

task * discretize_cntr(cntr * crv, grid * grd, const char * task_name) {
	
	if (!crv)
		return NULL;

	// using modified brezengham algorithm
	int qq;
	REAL X2, X1, Y2, Y1, Z1, Z2;

	std::vector<pos_z_w> * data = new std::vector<pos_z_w>();
	
	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = *(crv->X_begin + qq);
		Y1 = *(crv->Y_begin + qq);
		Z1 = *(crv->Z_begin + qq);
		X2 = *(crv->X_begin + qq + 1);
		Y2 = *(crv->Y_begin + qq + 1);
		Z2 = *(crv->Z_begin + qq + 1);

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
						bool change = true;
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

	std::sort(data->begin(), data->end(), ptr_pos_z_w_less);

	vec * points_x = new vec();
	vec * points_y = new vec();
	vec * points_z = new vec();

	points_x->reserve(data->size());
	points_y->reserve(data->size());
	points_z->reserve(data->size());

	int prev_pos = INT_MAX;
	pos_z_w elem;
	REAL total_weight = 0;
	REAL sum_val = 0;
	int NN = grd->getCountX();
	
	for (qq = 0; qq < (int)data->size(); qq++) {
		elem = (*data)[qq];
		if (prev_pos == elem.pos) {
			sum_val += elem.w*elem.z;
			total_weight += elem.w;
		} else {
			// write
			if (prev_pos != INT_MAX) {
				int pos_x = prev_pos % NN;
				int pos_y = (prev_pos - pos_x)/NN;
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

	int pos_x = prev_pos % NN;
	int pos_y = (prev_pos - pos_x)/NN;
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

/////////////////////////////////////
//
//  C N T R _ U S E R 
//
/////////////////////////////////////

cntr_user::cntr_user() : user("cntr") {};
cntr_user::~cntr_user() {};
	
int cntr_user::max_priority() 
{
	return cntrs_info();
};

void cntr_user::init() {
	grid * last_grd = create_last_grd();
	
	if (surfit_cntr) {
		writelog(SURFIT_MESSAGE,"Converting contours to scattered data-points...");
		task * cntr_task = discretize_cntr(surfit_cntr, last_grd, surfit_cntr->getName());
		if (cntr_task) {
			cntr_task->set_priority(surfit_cntr->get_priority());
			surfit_tasks->push_back(cntr_task);
			tasks_garbage->push_back(cntr_task);
		}
	}

	if (!surfit_cntr && surfit_cntrs->size() > 0)
		writelog(SURFIT_MESSAGE,"Converting contours to scattered data-points...");
	
	unsigned int cntrs_counter;
	for (cntrs_counter = 0; cntrs_counter < surfit_cntrs->size(); cntrs_counter++) {
		cntr * a_cntr = *(surfit_cntrs->begin()+cntrs_counter);
		task * cntr_task = discretize_cntr(a_cntr, last_grd, a_cntr->getName());
		if (cntr_task) {
			cntr_task->set_priority(a_cntr->get_priority());
			surfit_tasks->push_back(cntr_task);
			tasks_garbage->push_back(cntr_task);
		}
	};

	delete last_grd;
};

void cntr_user::prepare() {};
void cntr_user::begin() {};
void cntr_user::stage1(int priority) {};
void cntr_user::stage2(int priority) {};
void cntr_user::stage3(int priority) {};
void cntr_user::stage4(int priority) {};
void cntr_user::stage5(int priority) {};
void cntr_user::finish() {};
void cntr_user::release() {};

}; // namespace surfit;

