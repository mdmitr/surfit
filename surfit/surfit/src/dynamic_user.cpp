
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
#include "dynamic_user.h"
#include "dynamic.h"
#include "dynamics.h"
#include "fileio.h"
#include "free_elements.h"

namespace surfit {

////////////////////////////////////////////////////////
//
//  D Y N A M I C   G L O B A L   V A R I A B L E S 
//
////////////////////////////////////////////////////////

dynamic                 *  surfit_dynamic  = NULL;
std::vector<dynamic *>  * surfit_dynamics  = NULL;

/*! \struct dynamic_garbage
    \brief struct for deletion of \ref dynamic pointers
*/
struct dynamic_garbage : public binman {
	//! inits \ref surfit_dynamic and \ref surfit_dynamics
	dynamic_garbage() {
		surfit_dynamic   = NULL;
		surfit_dynamics  = new std::vector<dynamic *>;
	};
	//! removes \ref surfit_dynamic and \ref surfit_dynamics
	~dynamic_garbage() {
		delete surfit_dynamic;
		if (surfit_dynamics) {
			free_elements(surfit_dynamics->begin(), surfit_dynamics->end());
			delete surfit_dynamics;
		}
	};
};

dynamic_garbage dynamic_garb;

////////////////////////////////////////////////////////
//
//  D Y N A M I C   U S E F U L   F U N C T I O N S
//
////////////////////////////////////////////////////////

void load_dynamics(int current_priority) {
	if (surfit_dynamic) {
		if (surfit_dynamic->get_priority() == current_priority) {
			surfit_dynamic->load();
		}
	}
	
	unsigned int dynamic_counter;
	for (dynamic_counter = 0; dynamic_counter < surfit_dynamics->size(); dynamic_counter++) {
		dynamic * dyn_data = *(surfit_dynamics->begin()+dynamic_counter);
		if (dyn_data->get_priority() == current_priority) {
			dyn_data->load();
		}
	};
};

void unload_dynamics(int current_priority) {
	if (surfit_dynamic) {
		if (surfit_dynamic->get_priority() == current_priority) {
			surfit_dynamic->unload();
		}
	}
	
	unsigned int dynamic_counter;
	for (dynamic_counter = 0; dynamic_counter < surfit_dynamics->size(); dynamic_counter++) {
		dynamic * dyn_data = *(surfit_dynamics->begin()+dynamic_counter);
		if (dyn_data->get_priority() == current_priority) {
			dyn_data->unload();
		}
	};
};

/////////////////////////////////////////////
//
//  D Y N A M I C _ U S E R
//
/////////////////////////////////////////////

dynamic_user::dynamic_user() : user("dynamic") {};
dynamic_user::~dynamic_user() {};
	
int dynamic_user::max_priority() {
	return dynamics_info();
};

void dynamic_user::init() {};
void dynamic_user::prepare() {};
void dynamic_user::begin() {};

void dynamic_user::stage1(int priority) {
	load_dynamics(priority);
};

void dynamic_user::stage2(int priority) {};
void dynamic_user::stage3(int priority) {};
void dynamic_user::stage4(int priority) {};

void dynamic_user::stage5(int priority) {
	unload_dynamics(priority);
};

void dynamic_user::finish() {};
void dynamic_user::release() {};

}; // namespace surfit;

