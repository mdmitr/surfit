
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
#include "wcntrs.h"
#include "fileio.h"
#include "wcntr.h"
#include "wtask.h"
#include "grid.h"
#include "free_elements.h"

#include "grid_user.h"
#include "wtask_user.h"
#include "wcntr_user.h"

namespace surfit {

/////////////////////////////////////////////////
//
//  W C N T R  G L O B A L   V A R I A B L E S
//
//////////////////////////////////////////////////

wcntr                   *  surfit_wcntr    = NULL;
std::vector<wcntr *>    * surfit_wcntrs    = NULL;

/*! \struct wcntr_garbage
    \brief struct for deletion of \ref wcntr pointers
*/
struct wcntr_garbage : public binman {
	//! inits \ref surfit_wcntr and \ref surfit_wcntrs
	wcntr_garbage() {
		surfit_wcntr = NULL;
		surfit_wcntrs = new std::vector<wcntr *>;
	};
	//! removes \ref surfit_wcntr and \ref surfit_wcntrs
	~wcntr_garbage() {
		delete surfit_wcntr;
		if (surfit_wcntrs) {
			free_elements(surfit_wcntrs->begin(), surfit_wcntrs->end());
			delete surfit_wcntrs;
		}
	};
};

wcntr_garbage wcntr_garb;

/////////////////////////////////////////////////
//
//  W C N T R  U S E F U L   F U N C T I O N S
//
//////////////////////////////////////////////////

task * discretize_cntr(cntr * crv, grid * grd, const char * task_name);
wtask * discretize_wcntr(wcntr * crv, grid * grd, const char * task_name) {
	task * tsk = discretize_cntr(crv, grd, task_name);

	REAL * W_begin = (REAL *)malloc( tsk->size()*sizeof(REAL) );
	REAL * W_end = W_begin + tsk->size();

	REAL * ptr = NULL;
	for (ptr = W_begin; ptr != W_end; ptr++) 
		*ptr = crv->weight;

	wtask * wtsk = new wtask(tsk->X_begin, tsk->X_end,
		                     tsk->Y_begin, tsk->Y_end,
							 tsk->Z_begin, tsk->Z_end,
							 W_begin, W_end,
							 task_name);

	tsk->X_begin = NULL;
	tsk->Y_begin = NULL;
	tsk->Z_begin = NULL;

	delete tsk;
	return wtsk;
};

/////////////////////////////////////
//
//  W C N T R _ U S E R 
//
/////////////////////////////////////

wcntr_user::wcntr_user() : user("wcntr") {};
wcntr_user::~wcntr_user() {};
	
int wcntr_user::max_priority() 
{
	return wcntrs_info();
};

void wcntr_user::init() {
	grid * last_grd = create_last_grd();
	
	if (surfit_wcntr) {
		writelog(SURFIT_MESSAGE,"Converting wcontours to scattered data-points...");
		wtask * wcntr_task = discretize_wcntr(surfit_wcntr, last_grd, surfit_wcntr->getName());
		if (wcntr_task) {
			wcntr_task->set_priority(surfit_wcntr->get_priority());
			surfit_wtasks->push_back(wcntr_task);
			wtasks_garbage->push_back(wcntr_task);
		}
	}

	if (!surfit_wcntr && surfit_wcntrs->size() > 0)
		writelog(SURFIT_MESSAGE,"Converting wcontours to scattered data-points...");
	
	unsigned int wcntrs_counter;
	for (wcntrs_counter = 0; wcntrs_counter < surfit_wcntrs->size(); wcntrs_counter++) {
		wcntr * a_wcntr = *(surfit_wcntrs->begin()+wcntrs_counter);
		wtask * wcntr_task = discretize_wcntr(a_wcntr, last_grd, a_wcntr->getName());
		if (wcntr_task) {
			wcntr_task->set_priority(a_wcntr->get_priority());
			surfit_wtasks->push_back(wcntr_task);
			wtasks_garbage->push_back(wcntr_task);
		}
	};

	delete last_grd;
};

void wcntr_user::prepare() {};
void wcntr_user::begin() {};
void wcntr_user::stage1(int priority) {};
void wcntr_user::stage2(int priority) {};
void wcntr_user::stage3(int priority) {};
void wcntr_user::stage4(int priority) {};
void wcntr_user::stage5(int priority) {};
void wcntr_user::finish() {};
void wcntr_user::release() {};

}; // namespace surfit;

