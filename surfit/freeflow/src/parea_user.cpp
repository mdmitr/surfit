
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
#include "pareas.h"
#include "ptask.h"
#include "grid.h"
#include "parea.h"
#include "grid_line.h"
#include "vec.h"
#include "fileio.h"
#include "free_elements.h"

#include "parea_user.h"
#include "grid_user.h"
#include "ptask_user.h"
#include "grid_line_user.h"

namespace surfit {

/////////////////////////////////////////////////
//
//  P A R E A   G L O B A L  V A R I A B L E S
//
/////////////////////////////////////////////////

parea      *  flow_parea      = NULL;
std::vector<parea *>    * flow_pareas    = NULL;

/*! \struct parea_garbage
    \brief struct for deletion of pointers
*/
struct parea_garbage : public binman {
	parea_garbage() {
		flow_parea     = NULL;
		flow_pareas    = new std::vector<parea *>;
	};
	//! garbage sweeper
	~parea_garbage() {
		delete flow_parea;
		if (flow_pareas) {
			free_elements(flow_pareas->begin(), flow_pareas->end());
			delete flow_pareas;
		}
	};
};

parea_garbage parea_garb;

/////////////////////////////////////////////////
//
//  P A R E A   U S E F U L   F U N C T I O N S
//
/////////////////////////////////////////////////

ptask * discretize_parea(parea * par, grid * grd, const char * name) {

	if (par->getName())
		writelog(SURFIT_MESSAGE, "converting parea (%s) to ptask...", par->getName());
	else 
		writelog(SURFIT_MESSAGE, "converting parea noname to ptask...");
	
	grid_line * gline = NULL;
	std::vector<int> * parea_points = NULL;
	vec * points_x = NULL;
	vec * points_y = NULL;
	vec * points_z = NULL;
	int size = 0;
	REAL x,y,z;
	int NN = grd->getCountX();
	int pos;
	int n, m;
	ptask * res = NULL;

	gline = curv_to_grid_line(gline, par, grd);
	if (!gline)
		goto exit;

	parea_points = nodes_in_area(gline, grd, NULL);
	if (!parea_points)
		goto exit;

	delete gline;
	gline = NULL;

	size = parea_points->size();
	if (size == 0)
		goto exit;

	int i;
	points_x = new vec(size);
	points_y = new vec(size);
	points_z = new vec(size);
	z = par->value/REAL(size);
	for (i = 0; i < size; i++) {
		pos = *(parea_points->begin()+i);
		n = pos % NN;
		m = (pos - n)/NN;
		grd->getCoordNode(n, m, x, y);
		(*points_x)(i) = x;
		(*points_y)(i) = y;
		(*points_z)(i) = z;
	};

	res = new ptask(points_x->ref_begin(), points_x->end(),
	                points_y->ref_begin(), points_y->end(),
	                points_z->ref_begin(), points_z->end(),
			name);

	points_x->drop_data();
	delete points_x;
	points_y->drop_data();
	delete points_y;
	points_z->drop_data();
	delete points_z;
	
	return res;

exit:

	delete gline;
	delete parea_points;
	delete points_x;
	delete points_y;
	delete points_z;
	return NULL;

};

/////////////////////////////////////////
//
//  P A R E A _ U S E R
//
/////////////////////////////////////////

parea_user::parea_user() : user("parea") {};
parea_user::~parea_user() {};
	
int parea_user::max_priority() {
	return pareas_info();
};

void parea_user::init() {

	grid * last_grd = create_last_grd();

	if (flow_parea) {
		ptask * parea_task = discretize_parea(flow_parea, last_grd, flow_parea->getName());
		if (parea_task) {
			parea_task->set_priority(flow_parea->get_priority());
			flow_ptasks->push_back(parea_task);
			if (ptasks_garbage)
				ptasks_garbage->push_back(parea_task);
		}
	}

	unsigned int areas_counter;
	for (areas_counter = 0; areas_counter < flow_pareas->size(); areas_counter++) {
		parea * a_parea = *(flow_pareas->begin()+areas_counter);
		ptask * parea_task = discretize_parea(a_parea, last_grd, a_parea->getName());
		if (parea_task) {
			parea_task->set_priority(a_parea->get_priority());
			flow_ptasks->push_back(parea_task);
			if (ptasks_garbage)
				ptasks_garbage->push_back(parea_task);
		}
	}

	delete last_grd;
};

void parea_user::prepare() {};
void parea_user::begin() {};
void parea_user::stage1(int priority) {};
void parea_user::stage2(int priority) {};
void parea_user::stage3(int priority) {};
void parea_user::stage4(int priority) {};
void parea_user::stage5(int priority) {};
void parea_user::finish() {};

void parea_user::release() {};

}; // namespace surfit;

