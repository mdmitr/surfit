
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
#include "areas.h"
#include "task.h"
#include "grid.h"
#include "grid_line.h"
#include "vec.h"
#include "curv.h"
#include "area.h"
#include "fileio.h"
#include "bitvec.h"
#include "free_elements.h"
#include "variables_tcl.h"

#include "area_user.h"
#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

/////////////////////////////////////////////////
//
//  A R E A   G L O B A L   V A R I A B L E S
//
/////////////////////////////////////////////////

area                    *  surfit_area     = NULL;
std::vector<area *>     * surfit_areas     = NULL;

grid_line * area_grd_line = NULL;

/*! \struct area_garbage
    \brief struct for deletion of \ref area pointers
*/
struct area_garbage : public binman {
	//! inits \ref surfit_area and \ref surfit_areas
	area_garbage() {
		surfit_area = NULL;
		surfit_areas = new std::vector<area *>;
	};
	//! removes \ref surfit_area and \ref surfit_areas
	~area_garbage() {
		delete surfit_area;
		if (surfit_areas) {
			free_elements(surfit_areas->begin(), surfit_areas->end());
			delete surfit_areas;
		}
	};

};

area_garbage area_garb;

/////////////////////////////////////////////////
//
//  A R E A   U S E F U L   F U N C T I O N S
//
/////////////////////////////////////////////////

void use_area(area * a_area,
	      grid * grd,
	      vec * X,
	      bitvec * mask_solved,
	      bitvec * mask_undefined)
{
	if (a_area->getName()) {
		if (a_area->value != undef_value)
			writelog(SURFIT_MESSAGE,"area (%s), value = %lf", a_area->getName(), a_area->value);
		else 
			writelog(SURFIT_MESSAGE,"area (%s), value = \"undef\"", a_area->getName());
	} else {
		if (a_area->value != undef_value)
			writelog(SURFIT_MESSAGE,"area noname, value = %lf", a_area->value);
		else 
			writelog(SURFIT_MESSAGE,"area noname, value = \"undef\"");
	}

	grid_line * grd_line = NULL;
	grd_line = curv_to_grid_line(grd_line, a_area, grd);
	std::vector<int> * res = NULL;

	if (a_area->value == undef_value) 
		res = nodes_in_area(grd_line, grd, mask_undefined);
	else
		res = nodes_in_area(grd_line, grd, mask_undefined);
	
	unsigned int i;
	int pos;
	
	if (!res) {
		delete grd_line;
		return;
	}
		
	
	if (a_area->value == undef_value) {
		for (i = 0; i < res->size(); i++) {
			pos = *(res->begin()+i);
			if (!mask_solved->get(pos))
				mask_undefined->set_true(pos);
		}
	} else {
		for (i = 0; i < res->size(); i++) {
			pos = *(res->begin()+i);
			if ( !mask_solved->get(pos) || !mask_undefined->get(pos) ) {
				mask_solved->set_true(pos);
				(*X)(pos) = a_area->value;
			}
		}
	}
	delete grd_line;
	delete res;
};

grid_line * trace_area_grd_line(grid * grd) 
{
	grid_line * grd_line = NULL;
	if (surfit_area) 
	{
		if (surfit_area->value == undef_value) {
			grd_line = curv_to_grid_line(grd_line, surfit_area, grd);
		}
	}
	
	unsigned int areas_counter;
	for (areas_counter = 0; areas_counter < surfit_areas->size(); areas_counter++) {
		area * a_area = *(surfit_areas->begin()+areas_counter);
		if (a_area->value == undef_value) {
			grd_line = curv_to_grid_line(grd_line, a_area, grd);
		}
	};
	return grd_line;
};

/////////////////////////////////////////
//
//  A R E A _ U S E R
//
/////////////////////////////////////////

area_user::area_user() : user("area") {};
area_user::~area_user() {};
	
int area_user::max_priority() {
	return areas_info();
};

void area_user::init() {
	area_grd_line = NULL;
};

void area_user::prepare() {};
void area_user::begin() {};
void area_user::stage1(int priority) {};
void area_user::stage2(int priority) {};

void area_user::stage3(int priority) {

	if (surfit_area) 
	{
		use_area(surfit_area, 
			     method_grid,
			     method_X,
				 method_mask_solved, 
				 method_mask_undefined);
	}
	
	unsigned int areas_counter;
	for (areas_counter = 0; areas_counter < surfit_areas->size(); areas_counter++) {
		area * a_area = *(surfit_areas->begin()+areas_counter);
		use_area(a_area,
			     method_grid,
				 method_X,
				 method_mask_solved,
				 method_mask_undefined);
	}

	delete area_grd_line;
	area_grd_line = trace_area_grd_line(method_grid);

};

void area_user::stage4(int priority) {};
void area_user::stage5(int priority) {};
void area_user::finish() {};

void area_user::release() {
	delete area_grd_line;
	area_grd_line = NULL;
};

}; // namespace surfit;

