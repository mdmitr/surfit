
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
#include "warea.h"
#include "wareas.h"
#include "grid_line.h"
#include "fileio.h"
#include "vec.h"
#include "intvec.h"
#include "free_elements.h"
#include "variables_tcl.h"
#include "bitvec.h"

#include "warea_user.h"
#include "grid_user.h"
#include "grid_line_user.h"


namespace surfit {

////////////////////////////////////////////////////
//	
//  W A R E A   G L O B A L   V A R I A B L E S
//
////////////////////////////////////////////////////

warea                   *  surfit_warea    = NULL;
std::vector<warea *>    * surfit_wareas    = NULL;

/*! \struct warea_garbage
    \brief struct for deletion of \ref warea pointers
*/
struct warea_garbage : public binman {
	//! inits \ref surfit_warea and \ref surfit_wareas
	warea_garbage() {
		surfit_warea = NULL;
		surfit_wareas = new std::vector<warea *>;
	};
	//! removes \ref surfit_warea and \ref surfit_wareas
	~warea_garbage() {
		delete surfit_warea;
		if (surfit_wareas) {
			free_elements(surfit_wareas->begin(), surfit_wareas->end());
			delete surfit_wareas;
		}
	};
};

warea_garbage warea_garb;

////////////////////////////////////////////////////
//	
//  W A R E A   U S E F U L   F U N C T I O N S 
//
////////////////////////////////////////////////////

int calcVecV_warea(modifier1 * usr, vec * V, warea * war, grid * grd, 
		   bitvec * mask_solved, bitvec * mask_undefined) {

	int points = 0;

	if (!war)
		return points;

	if (war->value == undef_value) {
		if (war->getName())
			writelog(SURFIT_MESSAGE,"skipping warea : (%s) with \"undef\" value", war->getName());
		else 
			writelog(SURFIT_MESSAGE,"skipping warea : noname with \"undef\" value");
		return points;
	}

	if (war->getName())
		writelog(SURFIT_MESSAGE,"modifying with warea : (%s), value=%lf", war->getName(), war->value);
	else 
		writelog(SURFIT_MESSAGE,"modifying with warea : noname, value=%lf", war->value);

	vec * weights = usr->get_weights();
	intvec * weights_cnt = usr->get_weights_cnt();

	if (!weights) {
		writelog(SURFIT_WARNING,"no modifier1 specified!");
		return points;
	}

	grid_line * grd_line = NULL;
	grd_line = curv_to_grid_line(grd_line, war, grd);
	std::vector<int> * res = nodes_in_area(grd_line, grd, mask_undefined);
	delete grd_line;

	if (!res)
		return points;

	unsigned int i;
	int pos;
	for (i = 0; i < res->size(); i++) {
		pos = (*res)[i];
		if ( (!mask_solved->get(pos)) && (!mask_undefined->get(pos)) ) {
			(*V)(pos) += war->value*war->weight;
			(*weights)(pos) += war->weight;
			(*weights_cnt)(pos) += 1;
			points++;
		}
	}

	delete res;
	return points;
	
};

int calcVecV_wareas(modifier1 * usr, vec * V, bitvec * mask_solved, bitvec * mask_undefined) {
	int points = 0;
	if (surfit_warea) {
		points += calcVecV_warea(usr, V, surfit_warea, method_grid, mask_solved, mask_undefined);
	}
	if (surfit_wareas) {
		std::vector<warea *>::iterator it;
		for (it = surfit_wareas->begin(); it != surfit_wareas->end(); it++) {
			points += calcVecV_warea(usr, V, *it, method_grid, mask_solved, mask_undefined);
		}
	}
	return points;
};

////////////////////////////
//
//  W A R E A _ U S E R 
//
////////////////////////////


warea_user::warea_user() : user("warea") {};
warea_user::~warea_user() {};
	
int warea_user::max_priority() {
	return wareas_info();
};

void warea_user::init() {};
void warea_user::prepare() {};
void warea_user::begin() {};
void warea_user::stage1(int priority) {};
void warea_user::stage2(int priority) {};
void warea_user::stage3(int priority) {}
void warea_user::stage4(int priority) {};
void warea_user::stage5(int priority) {};
void warea_user::finish() {};
void warea_user::release() {};

}; // namespace surfit;

