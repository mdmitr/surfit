
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
#include "wiso.h"
#include "wisos.h"
#include "wtask.h"
#include "grid.h"
#include "fileio.h"
#include "free_elements.h"

#include "wiso_user.h"
#include "wtask_user.h"
#include "grid_user.h"
#include "curv_user.h"

#include <algorithm>

namespace surfit {

////////////////////////////////////////////////////
//
//  W I S O   G L O B A L   V A R I A B L E S 
//
////////////////////////////////////////////////////

wiso *  surfit_wiso = NULL;
std::vector<wiso *> * surfit_wisos = NULL;

/*! \struct wiso_garbage
    \brief struct for deletion of \ref wiso pointers
*/
struct wiso_garbage : public binman {
	//! inits \ref surfit_wiso and \ref surfit_wisos
	wiso_garbage() {
		surfit_wiso = NULL;
		surfit_wisos = new std::vector<wiso *>;
	};
	//! removes \ref surfit_wiso and \ref surfit_wisos
	~wiso_garbage() {
		delete surfit_wiso;
		if (surfit_wisos) {
			free_elements(surfit_wisos->begin(), surfit_wisos->end());
			delete surfit_wisos;
		}
	};

};

wiso_garbage wiso_garb;


////////////////////////////////////////////////////
//
//  W I S O   U S E R F U L   F U N C T I O N S
//
////////////////////////////////////////////////////

wtask * discretize_curv(curv * crv, grid * grd, REAL value, REAL weight, const char * task_name) {
	task * tsk = discretize_curv(crv, grd, value, task_name);

	REAL * W_begin = (REAL *)malloc( tsk->size()*sizeof(REAL) );
	REAL * W_end = W_begin + tsk->size();

	REAL * ptr = NULL;
	for (ptr = W_begin; ptr != W_end; ptr++) 
		*ptr = weight;

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
//  W I S O _ U S E R 
//
/////////////////////////////////////

wiso_user::wiso_user() : user("wiso") {};
wiso_user::~wiso_user() {};
	
int wiso_user::max_priority() {
	return wisos_info();
};

void wiso_user::init() {
	grid * last_grd = create_last_grd();
	
	if (surfit_wiso) {
		writelog(SURFIT_MESSAGE,"Converting wisolines to scattered data-points...");
		wtask * wiso_task = discretize_curv(surfit_wiso, last_grd, surfit_wiso->value, surfit_wiso->weight, surfit_wiso->getName());
		if (wiso_task) {
			wiso_task->set_priority(surfit_wiso->get_priority());
			surfit_wtasks->push_back(wiso_task);
			wtasks_garbage->push_back(wiso_task);
		}
	}

	if (!surfit_wiso && surfit_wisos->size() > 0)
		writelog(SURFIT_MESSAGE,"Converting wisolines to scattered data-points...");
	
	unsigned int wisos_counter;
	for (wisos_counter = 0; wisos_counter < surfit_wisos->size(); wisos_counter++) {
		wiso * a_wiso = *(surfit_wisos->begin()+wisos_counter);
		wtask * wiso_task = discretize_curv(a_wiso, last_grd, a_wiso->value, a_wiso->weight, a_wiso->getName());
		if (wiso_task) {
			wiso_task->set_priority(a_wiso->get_priority());
			surfit_wtasks->push_back(wiso_task);
			wtasks_garbage->push_back(wiso_task);
		}
	};

	delete last_grd;

};

void wiso_user::prepare() {};
void wiso_user::begin() {};

void wiso_user::stage1(int priority) {};
void wiso_user::stage2(int priority) {};
void wiso_user::stage3(int priority) {};
void wiso_user::stage4(int priority) {};
void wiso_user::stage5(int priority) {};
void wiso_user::finish() {};

void wiso_user::release() {
};


}; // namespace surfit;


