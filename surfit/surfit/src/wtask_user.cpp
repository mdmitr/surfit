
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
#include "real.h"

#include "wtask_internal.h"
#include "wtasks.h"
#include "wtask.h"
#include "fileio.h"
#include "grid_user.h"
#include "task_internal.h"
#include "vec.h"
#include "intvec.h"
#include "bitvec.h"
#include "variables_tcl.h"
#include "free_elements.h"

#include "wtask_user.h"
#include "task_user.h"

#include <algorithm>

namespace surfit {

////////////////////////////////////////////////////
//
//  W T A S K   G L O B A L   V A R I A B L E S
//
////////////////////////////////////////////////////

wtask                   *  surfit_wtask    = NULL;
std::vector<wtask *>    * surfit_wtasks    = NULL;

sub_tasks * sub_wtsks;
wtask * wtsk;
std::vector<wtask *> * wtasks_garbage;

/*! \struct wtask_garbage
    \brief struct for deletion of \ref wtask pointers
*/
struct wtask_garbage : public binman {
	//! inits \ref surfit_wtask and \ref surfit_wtasks
	wtask_garbage() {
		surfit_wtask = NULL;
		surfit_wtasks = new std::vector<wtask *>;
	};
	//! removes \ref surfit_wtask and \ref surfit_wtasks
	~wtask_garbage() {
		delete surfit_wtask;
		if (surfit_wtasks) {
			free_elements(surfit_wtasks->begin(), surfit_wtasks->end());
			delete surfit_wtasks;
		}
	};

};

wtask_garbage wtask_garb;


//////////////////////////////////////////////////
//
//  W T A S K   U S E F U L   F U N C T I O N S
//
//////////////////////////////////////////////////

int calcVecV_points(modifier1 * usr, vec * V, wtask * wtsk, std::vector<sub_points *> * sub_wtsks,
		    bitvec * mask_solved, bitvec * mask_undefined) {
	
	int points = 0;

	if (!wtsk)
		return points;

	if (wtsk->getName())
		writelog(SURFIT_MESSAGE,"modifying with wtask : (%s), %d points", wtsk->getName(), wtsk->size());
	else 
		writelog(SURFIT_MESSAGE,"modifying with wtask : noname, %d points", wtsk->size());

	vec * weights = usr->get_weights();
	intvec * weights_cnt = usr->get_weights_cnt();

	if (!weights) {
		writelog(SURFIT_WARNING,"no modifier1 specified!");
		return points;
	}

	REAL val, weight;
	unsigned int i;
	for (i = 0; i < sub_wtsks->size(); i++) {
		sub_points * sub_pnts = *(sub_wtsks->begin()+i);
		if ( (!mask_solved->get(sub_pnts->cell_number)) && 
		     (!mask_undefined->get(sub_pnts->cell_number)) ) 
		{
			(*weights)(sub_pnts->cell_number) += sub_pnts->weight(wtsk);
			(*weights_cnt)(sub_pnts->cell_number) += 1;
			val = sub_pnts->value(wtsk);
			weight = sub_pnts->weight(wtsk);
			(*V)(sub_pnts->cell_number) += val*weight;
			points++;
		}
	}

	return points;
	
};

void makeSolution_w(wtask * wtsk,
		    std::vector<sub_points *> * tasks, 
		    bitvec * mask_solved,
		    bitvec * mask_undefined,
		    vec * X2) {

	unsigned int i;
	int num;
	sub_points * sub_task;
	REAL value, weight;

	int solved_add_size = 0;
	int undefined_add_size = 0;

	unsigned int tasks_size = tasks->size();
	
	for (i = 0; i < tasks->size(); i++) {
		sub_task = (*tasks)[i];
		num = sub_task->cell_number;

		// check for existance
		if (mask_solved->get(num))
			continue;
		if (mask_undefined->get(num))
			continue;
		
		value = sub_task->value(wtsk);
		weight = sub_task->weight(wtsk);
		
		if (value == undef_value) {
			mask_undefined->set_true(num);
		} else {
			if (weight < 0) {
				(*X2)(num) = value;
				mask_solved->set_true(num);
			}
		}
		
	}
	
};

void scattered_points2d_w() 
{

	if (wtsk) {
		
		int task_size = wtsk->size();
		if (task_size > 0) {
			if (wtsk->getName()) {
				writelog(SURFIT_MESSAGE,"wtask : (%s).", wtsk->getName());
			} else {
				writelog(SURFIT_MESSAGE,"wtask : noname dataset");
			}
			
			bind_points_to_grid(method_sub_grid, wtsk, sub_wtsks, method_grid);
			
			// ѕриводим точки к геометрии с единичным шагом
			
			REAL * save_X_begin = wtsk->X_begin;
			REAL * save_X_end   = wtsk->X_end;
			REAL * save_Y_begin = wtsk->Y_begin;
			REAL * save_Y_end   = wtsk->Y_end;
			
			wtsk->X_begin = (REAL*)malloc(task_size*sizeof(REAL));
			wtsk->X_end = wtsk->X_begin + task_size;
			memcpy(wtsk->X_begin, save_X_begin, task_size*sizeof(REAL));
			
			wtsk->Y_begin = (REAL*)malloc(task_size*sizeof(REAL));
			wtsk->Y_end = wtsk->Y_begin + task_size;
			memcpy(wtsk->Y_begin, save_Y_begin, task_size*sizeof(REAL));
			
			_points_transform(wtsk, method_shiftX, method_scaleX, method_shiftY, method_scaleY);
			
			makeSolution_w(wtsk, sub_wtsks, method_mask_solved, method_mask_undefined, method_X);
			
			free(wtsk->X_begin);
			free(wtsk->Y_begin);
			wtsk->X_begin = save_X_begin;
			wtsk->X_end   = save_X_end;
			wtsk->Y_begin = save_Y_begin;
			wtsk->Y_end   = save_Y_end;
			
		}
	}

};

///////////////////////////////////////
//
//  W T A S K _ U S E R 
//
///////////////////////////////////////

wtask_user::wtask_user() : user("wtask") {};

wtask_user::~wtask_user() {};

int wtask_user::max_priority() {
	return wtasks_info();
};

void wtask_user::init() {
	sub_wtsks = NULL;
	wtasks_garbage = new std::vector<wtask *>;
};

void wtask_user::prepare() {
	wtsk = _collect_all_wtasks();
	prepare_scattered_points(wtsk, sub_wtsks);
};

void wtask_user::begin() {};
void wtask_user::stage1(int priority) {};
void wtask_user::stage2(int priority) {};

void wtask_user::stage3(int priority) {
	if (wtsk) {
		if (wtsk->get_priority() == priority) {

			scattered_points2d_w();
			
		}
	}
};

void wtask_user::stage4(int priority) {};
void wtask_user::stage5(int priority) {};
void wtask_user::finish() {};

void wtask_user::release() {
	
	// wtasks_garbage
	std::vector<wtask *>::iterator it, it2;
	for (it = wtasks_garbage->begin(); it != wtasks_garbage->end(); it++) {
		
		it2 = std::find(surfit_wtasks->begin(), surfit_wtasks->end(), *it);
		if (it2 != surfit_wtasks->end())
			surfit_wtasks->erase(it2);
				
		delete *it;
	}
	delete wtasks_garbage;
	wtasks_garbage = NULL;
};

}; // namespace surfit;

