
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
#include "flt.h"
#include "flts.h"
#include "flt_user.h"
#include "fileio.h"
#include "grid_line.h"
#include "grid_user.h"
#include "free_elements.h"

#include "grid_line_user.h"

namespace surfit {

///////////////////////////////////////////////
//
//  F L T  G L O B A L   V A R I A B L E S 
//
////////////////////////////////////////////////

flt                     *  surfit_flt      = NULL;
std::vector<flt *>      * surfit_flts      = NULL;
	
grid_line * fault_grd_line = NULL;

/*! \struct flt_garbage
    \brief struct for deletion of \ref flt pointers
*/
struct flt_garbage : public binman {
	//! inits \ref surfit_flt and \ref surfit_flts
	flt_garbage() {
		surfit_flt = NULL;
		surfit_flts = new std::vector<flt *>;
	};
	//! removes \ref surfit_flt and \ref surfit_flts
	~flt_garbage() {
		delete surfit_flt;
		if (surfit_flts) {
			free_elements(surfit_flts->begin(), surfit_flts->end());
			delete surfit_flts;
		}
	};

};

flt_garbage flt_garb;

///////////////////////////////////////////////
//
//  F L T  U S E F U L    F U N C T I O N S
//
////////////////////////////////////////////////

grid_line * trace_faults(int current_priority,
						 grid * grd)
{
	grid_line * flt_grd_line = NULL;
	bool converted = false;
	if (surfit_flt) {
		if (surfit_flt->get_priority() <= current_priority) {
			converted = true;
			writelog(SURFIT_MESSAGE,"Converting fault-lines to grid-fault-lines...");
			flt_grd_line = curv_to_grid_line(NULL, surfit_flt, grd);
		}
	}
	
	unsigned int faults_counter;
	for (faults_counter = 0; faults_counter < surfit_flts->size(); faults_counter++) {
		flt * a_fault = *(surfit_flts->begin()+faults_counter);
		if (a_fault->get_priority() <= current_priority) {
			if (!converted) {
				converted = true;
				writelog(SURFIT_MESSAGE,"Converting fault-lines to grid-fault-lines...");
			}
			flt_grd_line = curv_to_grid_line(flt_grd_line, a_fault, grd);
		}
		
	}
	
	if (flt_grd_line)
		flt_grd_line->compress();
	return flt_grd_line;
};


/////////////////////////////////////////
//
//  F L T  _ U S E R  
//
/////////////////////////////////////////
flt_user::flt_user() : user("flt") {};

flt_user::~flt_user() {};

int flt_user::max_priority() {
	return flts_info();
};

void flt_user::init() {
	fault_grd_line = NULL;
};

void flt_user::prepare() {};
void flt_user::begin() {};

void flt_user::stage1(int priority) {};
void flt_user::stage2(int priority) {};

void flt_user::stage3(int priority) {
	delete fault_grd_line;
	fault_grd_line = trace_faults(priority, method_grid);
	/*
	debug_print_grid_line(fault_grd_line, method_grid,
						   method_mask_solved, 
						   method_mask_undefined);
	*/

};

void flt_user::stage4(int priority) {};
void flt_user::stage5(int priority) {};

void flt_user::finish() {};

void flt_user::release() {
	delete fault_grd_line;
	fault_grd_line = NULL;
};

};

