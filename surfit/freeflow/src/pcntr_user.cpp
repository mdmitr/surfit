
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

#include "flow_ie.h"
#include "pcntrs.h"
#include "fileio.h"
#include "ptask.h"
#include "pcntr.h"
#include "grid.h"
#include "geom_alg.h"
#include "vec.h"
#include "free_elements.h"

#include "pcntr_user.h"
#include "grid_user.h"
#include "ptask_user.h"

#include <vector>
#include <algorithm>

namespace surfit {

////////////////////////////////////////////////////////////
//
//  P C N T R _ U S E R   G L O B A L   V A R I A B L E S
//
////////////////////////////////////////////////////////////

pcntr      *  flow_pcntr      = NULL;
std::vector<pcntr *>    * flow_pcntrs    = NULL;

/*! \struct pcntr_garbage
    \brief struct for deletion of pointers
*/
struct pcntr_garbage : public binman {
	pcntr_garbage() {
		flow_pcntr     = NULL;
		flow_pcntrs    = new std::vector<pcntr *>;
	};
	//! garbage sweeper
	~pcntr_garbage() {
		delete flow_pcntr;
		if (flow_pcntrs) {
			free_elements(flow_pcntrs->begin(), flow_pcntrs->end());
			delete flow_pcntrs;
		}
	};
};

pcntr_garbage pcntr_garb;


////////////////////////////////////////////////////////////
//
//  P C N T R _ U S E R   U S E F U L   F U N C T I O N S 
//
////////////////////////////////////////////////////////////

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

bool add_square_val(grid * grd, int x, int y,
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

ptask * discretize_pcntr(pcntr * pcrv, grid * grd, const char * task_name) {
	
	if (!pcrv)
		return NULL;

	// using modified brezengham algorithm
	int qq;
	REAL X2, X1, Y2, Y1, Z1, Z2;

	std::vector<pos_s> * data = new std::vector<pos_s>();
	
	for (qq = 0; qq < pcrv->size()-1; qq++) {
		X1 = *(pcrv->X_begin + qq);
		Y1 = *(pcrv->Y_begin + qq);
		Z1 = *(pcrv->Z_begin + qq);
		X2 = *(pcrv->X_begin + qq + 1);
		Y2 = *(pcrv->Y_begin + qq + 1);
		Z2 = *(pcrv->Z_begin + qq + 1);

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

	vec * points_x = new vec();
	vec * points_y = new vec();
	vec * points_z = new vec();

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
	
	ptask * res = new ptask(points_x->ref_begin(), points_x->end(),
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

///////////////////////////////////////////////////////////
//
//  P C N T R _ U S E R 
//
///////////////////////////////////////////////////////////

pcntr_user::pcntr_user() : user("pcntr") {};
pcntr_user::~pcntr_user() {};
	
int pcntr_user::max_priority() {
	return pcntrs_info();
};

void pcntr_user::init() {

	grid * last_grd = create_last_grd();

	if (flow_pcntr) {
		writelog(SURFIT_MESSAGE,"Converting pcontours to scattered data-points...");
		ptask * pcntr_task = discretize_pcntr(flow_pcntr, last_grd, flow_pcntr->getName());
		if (pcntr_task) {
			pcntr_task->set_priority(flow_pcntr->get_priority());
			flow_ptasks->push_back(pcntr_task);
			ptasks_garbage->push_back(pcntr_task);
		}
	}

	unsigned int pcntrs_counter;
	for (pcntrs_counter = 0; pcntrs_counter < flow_pcntrs->size(); pcntrs_counter++) {
		pcntr * a_pcntr = *(flow_pcntrs->begin()+pcntrs_counter);
		if (!flow_pcntr)
			writelog(SURFIT_MESSAGE,"Converting pcontours to scattered data-points...");
		ptask * pcntr_task = discretize_pcntr(a_pcntr, last_grd, a_pcntr->getName());
		if (pcntr_task) {
			pcntr_task->set_priority(a_pcntr->get_priority());
			flow_ptasks->push_back(pcntr_task);
			ptasks_garbage->push_back(pcntr_task);
		}
	};

};

void pcntr_user::prepare() {};
void pcntr_user::begin() {};
void pcntr_user::stage1(int priority) {};
void pcntr_user::stage2(int priority) {};
void pcntr_user::stage3(int priority) {};
void pcntr_user::stage4(int priority) {};
void pcntr_user::stage5(int priority) {};
void pcntr_user::finish() {};
void pcntr_user::release() {};

}; // namespace surfit;

