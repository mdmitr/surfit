
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
#include "iso.h"
#include "isos.h"
#include "task.h"
#include "grid.h"
#include "fileio.h"
#include "vec.h"
#include "free_elements.h"

#include "iso_user.h"
#include "task_user.h"
#include "grid_user.h"
#include "curv_user.h"

#include <algorithm>

namespace surfit {

///////////////////////////////////////////////
//
//  I S O   G L O B A L   V A R I A B L E S
//
///////////////////////////////////////////////

iso                     *  surfit_iso      = NULL;
std::vector<iso *>      * surfit_isos      = NULL;

/*! \struct iso_garbage
    \brief struct for deletion of \ref iso pointers
*/
struct iso_garbage : public binman {
	//! inits \ref surfit_iso and \ref surfit_isos
	iso_garbage() {
		surfit_iso = NULL;
		surfit_isos = new std::vector<iso *>;
	};
	//! removes \ref surfit_iso and \ref surfit_isos
	~iso_garbage() {
		delete surfit_iso;
		if (surfit_isos) {
			free_elements(surfit_isos->begin(), surfit_isos->end());
			delete surfit_isos;
		}
	};

};

iso_garbage iso_garb;


///////////////////////////////////////////////
//
//  I S O   U S E F U L   F U N C T I O N S 
//
///////////////////////////////////////////////

/////////////////////////////////////
//
//  I S O _ U S E R 
//
/////////////////////////////////////

iso_user::iso_user() : user("iso") {};
iso_user::~iso_user() {};
	
int iso_user::max_priority() {
	return isos_info();
};

void iso_user::init() {
	grid * last_grd = create_last_grd();
	
	if (surfit_iso) {
		writelog(SURFIT_MESSAGE,"Converting isolines to scattered data-points...");
		task * iso_task = discretize_curv(surfit_iso, last_grd, surfit_iso->value, surfit_iso->getName());
		if (iso_task) {
			iso_task->set_priority(surfit_iso->get_priority());
			surfit_tasks->push_back(iso_task);
			tasks_garbage->push_back(iso_task);
		}
	}

	if (!surfit_iso && surfit_isos->size() > 0)
		writelog(SURFIT_MESSAGE,"Converting isolines to scattered data-points...");
	
	unsigned int isos_counter;
	for (isos_counter = 0; isos_counter < surfit_isos->size(); isos_counter++) {
		iso * a_iso = *(surfit_isos->begin()+isos_counter);
		task * iso_task = discretize_curv(a_iso, last_grd, a_iso->value, a_iso->getName());
		if (iso_task) {
			iso_task->set_priority(a_iso->get_priority());
			surfit_tasks->push_back(iso_task);
			tasks_garbage->push_back(iso_task);
		}
	};

	delete last_grd;
};

void iso_user::prepare() {};
void iso_user::begin() {};

void iso_user::stage1(int priority) {};
void iso_user::stage2(int priority) {};
void iso_user::stage3(int priority) {};
void iso_user::stage4(int priority) {};
void iso_user::stage5(int priority) {};
void iso_user::finish() {};
void iso_user::release() {};
        
}; // namespace surfit;


