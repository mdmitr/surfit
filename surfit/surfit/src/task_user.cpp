
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
#include "task.h"
#include "task_internal.h"
#include "tasks.h"
#include "sort_alg.h"
#include "fileio.h"
#include "grid.h"
#include "vec.h"
#include "free_elements.h"
#include "variables_tcl.h"

#include "task_user.h"
#include "grid_user.h"

#include <vector>
#include <algorithm>

namespace surfit {

////////////////////////////////////////////////
//
//  T A S K   G L O B A L   V A R I A B L E S
//
////////////////////////////////////////////////

task                    *  surfit_task     = NULL;
std::vector<task *>     * surfit_tasks     = NULL;

// arrays of points, sorted by cells
sub_tasks * sub_tsks;
std::vector<void *> * a_sub_tsks;
std::vector<task *> * tasks_garbage;

/*! \struct task_garbage
    \brief struct for deletion of \ref task pointers
*/
struct task_garbage : public binman {
	//! inits \ref surfit_task and \ref surfit_tasks
	task_garbage() {
		surfit_task = NULL;
		surfit_tasks = new std::vector<task *>;
	};
	//! removes \ref surfit_task and \ref surfit_tasks
	~task_garbage() {
		delete surfit_task;
		if (surfit_tasks) {
			release_elements(surfit_tasks->begin(), surfit_tasks->end());
			delete surfit_tasks;
		}
	};

};

task_garbage task_garb;


///////////////////////////////////////////////
//
//  T A S K   U S E F U L   F U N C T I O N S
//
///////////////////////////////////////////////

bool ptr_sub_points_less(sub_points * it1, sub_points * it2) {
	return (it1)->cell_number < (it2)->cell_number;
};

void free_scattered_points(std::vector<sub_points *> * proc_sub_tsks) {
	free_elements(proc_sub_tsks->begin(), proc_sub_tsks->end());
	delete proc_sub_tsks;
};

void prepare_scattered_points(const points * pnts, 
                              std::vector<sub_points *> *& proc_sub_tsks)
{
	if (!pnts)
		return;
	
	std::vector<unsigned int> * point_numbers = new std::vector<unsigned int>( pnts->size() );
	
	int point_counter;
	for (point_counter = 0; point_counter < pnts->size(); point_counter++) {
		*( point_numbers->begin() + point_counter ) = point_counter;
	}
	
	sub_points * sub_tsk = new sub_points(0, point_numbers);
	
	proc_sub_tsks = new std::vector<sub_points *>(1);
	(*proc_sub_tsks)[0] = sub_tsk;
};

void bind_points_to_grid(grid *& old_grid, 
			 points * pnts,
			 std::vector<sub_points *> *& old_tasks,
			 grid *& grd)
{
	std::vector<sub_points *>::iterator it;
	REAL oldx_from, oldx_to, oldy_from, oldy_to;
	REAL x_from, x_to, y_from, y_to;
	REAL x,y;
	int i,j;
	int node;

	int old_size = old_tasks->size();

	std::vector<sub_points *> * tasks = new std::vector<sub_points *>;
	tasks->reserve(old_size);

	std::vector<unsigned int> * nums = new std::vector<unsigned int>;
	int nums_size;
	
	int cnt = 0;
	for (it = old_tasks->begin(); it != old_tasks->end(); it++) {

		int total_size = 0;
		sub_points * old_sub_points = *it;
		cnt++;

		REAL ** sortx_begin = NULL;
		REAL ** sortx_end   = NULL;
		REAL ** sorty_begin = NULL;
		REAL ** sorty_end   = NULL;

		_sort_points(pnts, old_sub_points->point_numbers,
			         sortx_begin, sortx_end, sorty_begin, sorty_end);

		int old_node = old_sub_points->cell_number;
		i = old_node % old_grid->getCountX();
		j = (old_node -i)/old_grid->getCountY();

		// определ€ем границы пр€моугольника, содержащего task
		old_grid->getCoordNode(i,j,x,y);
		oldx_from = x - old_grid->stepX/REAL(2);
		oldx_to = x + old_grid->stepX/REAL(2);
		oldy_from = y - old_grid->stepY/REAL(2);
		oldy_to = y + old_grid->stepY/REAL(2);

		int prop_coeff_x = grd->getCountX()/old_grid->getCountX();
		int prop_coeff_y = grd->getCountY()/old_grid->getCountY();

		int i_from = i*prop_coeff_x;
		int i_to = i_from + prop_coeff_x-1;
		if (old_grid->stepX == grd->stepX) {
			i_from = i;
			i_to = i;
		}
		int j_from = j*prop_coeff_y;
		int j_to = j_from + prop_coeff_y-1;
		if (old_grid->stepY == grd->stepY) {
			j_from = j;
			j_to = j;
		}

		old_size = old_sub_points->point_numbers->size();
					
		x_to = grd->startX + (i_from - REAL(0.5))*grd->stepX;
		for (i = i_from; i <= i_to; i++) {
			x_from = x_to;
			x_to = x_from + grd->stepX;
			y_to = grd->startY + (j_from - REAL(0.5))*grd->stepY;
			for (j = j_from; j <= j_to; j++) {
				y_from = y_to;
				y_to = y_from + grd->stepY;
				getPointsInRect(x_from, x_to, y_from, y_to,
					sortx_begin, sortx_end,
					sorty_begin, sorty_end,
					pnts->X_begin, pnts->Y_begin,
					*nums);
				
				nums_size = nums->size();
				total_size += nums_size;
				
				if (nums_size > 0) {
					
					node = i+j*grd->getCountX();
					
					sub_points * new_sub_points = new sub_points(node, nums);
					tasks->push_back(new_sub_points);
					
					nums = new std::vector<unsigned int>;
				}
				
			}
		}
		delete *it;
		*it = NULL;

		free(sortx_begin);
		free(sorty_begin);

	}

	old_tasks = NULL;
	old_tasks = tasks;
	
	delete nums;
	
	std::sort(tasks->begin(), tasks->end(), ptr_sub_points_less);

};

void makeSolution(task * tsk,
		  std::vector<sub_points *> * tasks, 
		  bitvec * mask_solved,
		  bitvec * mask_undefined,
		  vec * X2) {
	unsigned int i;
	int num;
	sub_points * sub_task;
	REAL value;

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
		
		value = sub_task->value(tsk);
		
		(*X2)(num) = value;
		
		if (value == undef_value) {
			mask_undefined->set_true(num);
		} else {
			mask_solved->set_true(num);
		}
		
	}
	
};

void use_scattered_points(int basis_cntX, int basis_cntY,
			  REAL shiftX, REAL shiftY,
			  REAL scaleX, REAL scaleY,
			  grid * grd,
			  task * tsk,
			  grid * sub_grid,
			  std::vector<sub_points *> *& sub_tasks,
			  vec *& X,
			  bitvec * mask_solved,
			  bitvec * mask_undefined) 
{

	if (tsk) {
		
		int task_size = tsk->size();
		if (task_size > 0) {
			if (tsk->getName()) {
				writelog(SURFIT_MESSAGE,"task : (%s).", tsk->getName());
			} else {
				writelog(SURFIT_MESSAGE,"task : noname dataset");
			}
			
			bind_points_to_grid(sub_grid, tsk, sub_tasks, grd);
			
			// ѕриводим точки к геометрии с единичным шагом
			
			REAL * save_X_begin = tsk->X_begin;
			REAL * save_X_end   = tsk->X_end;
			REAL * save_Y_begin = tsk->Y_begin;
			REAL * save_Y_end   = tsk->Y_end;
			
			tsk->X_begin = (REAL*)malloc(task_size*sizeof(REAL));
			tsk->X_end = tsk->X_begin + task_size;
			memcpy(tsk->X_begin, save_X_begin, task_size*sizeof(REAL));
			
			tsk->Y_begin = (REAL*)malloc(task_size*sizeof(REAL));
			tsk->Y_end = tsk->Y_begin + task_size;
			memcpy(tsk->Y_begin, save_Y_begin, task_size*sizeof(REAL));
			
			_points_transform(tsk, shiftX, scaleX, shiftY, scaleY);
			
			makeSolution(tsk, sub_tasks, mask_solved, mask_undefined, X);
			
			//_inverse_task_transform(tsk, shiftX, scaleX, shiftY, scaleY);
			free(tsk->X_begin);
			free(tsk->Y_begin);
			tsk->X_begin = save_X_begin;
			tsk->X_end   = save_X_end;
			tsk->Y_begin = save_Y_begin;
			tsk->Y_end   = save_Y_end;
		}
	}
	
};
	

///////////////////////////////
//
//     T A S K _ U S E R 
//
///////////////////////////////

task_user::task_user() : user("task") {};

task_user::~task_user() {};

int task_user::max_priority() {
	return tasks_info();
};

void task_user::init() {
	tasks_garbage = new std::vector<task *>;
	sub_tsks = NULL;
	delete a_sub_tsks;
	a_sub_tsks = new std::vector<void *>;
};

void task_user::prepare() {
	prepare_scattered_points(surfit_task, sub_tsks);
	if (surfit_tasks->size() > 0) {
		unsigned int tasks_counter;
		for (tasks_counter = 0; tasks_counter < surfit_tasks->size(); tasks_counter++) {
			task * a_task = *(surfit_tasks->begin()+tasks_counter); // additional task
			sub_tasks * a_sub_tasks = NULL;
			prepare_scattered_points(a_task, a_sub_tasks);
			a_sub_tsks->push_back(a_sub_tasks);
		}
	}
};

void task_user::begin() {};
void task_user::stage1(int priority) {};
void task_user::stage2(int priority) {};

void task_user::stage3(int priority) {
	if (surfit_task) {
		if (surfit_task->get_priority() == priority) {
			use_scattered_points(method_basis_cntX,
					     method_basis_cntY,
				             method_shiftX,
				             method_shiftY,
				             method_scaleX,
				             method_scaleY,
				             method_grid,
					     surfit_task,
				             method_sub_grid,
				             sub_tsks,
				             method_X, 
					     method_mask_solved, 
					     method_mask_undefined);
		}
	}
	
	unsigned int tasks_counter;
	for (tasks_counter = 0; tasks_counter < a_sub_tsks->size(); tasks_counter++) {
		
		task * a_task = *(surfit_tasks->begin()+tasks_counter);
		sub_tasks * a_sub_tasks = (sub_tasks *) *(a_sub_tsks->begin() + tasks_counter);
		
		if (a_task) {
			if (a_task->get_priority() == priority) {
				use_scattered_points(method_basis_cntX,
					             method_basis_cntY,
					             method_shiftX,
					             method_shiftY,
					             method_scaleX,
					             method_scaleY,
					             method_grid,
					             a_task,
					             method_sub_grid,
					             a_sub_tasks,
					             method_X, 
						     method_mask_solved, 
						     method_mask_undefined);
				
				*(a_sub_tsks->begin() + tasks_counter) = a_sub_tasks;
			}
		}
	}
};

void task_user::stage4(int priority) {};
void task_user::stage5(int priority) {};
void task_user::finish() {};

void task_user::release() {
	// sub_tasks deletion
	if (sub_tsks) {
		free_elements(sub_tsks->begin(), sub_tsks->end());
		delete sub_tsks;
		sub_tsks = NULL;
	}
	unsigned int tasks_counter;
	for (tasks_counter = 0; tasks_counter < a_sub_tsks->size(); tasks_counter++) {
		sub_tasks * a_sub_tasks = (sub_tasks *) *(a_sub_tsks->begin() + tasks_counter);
		free_elements(a_sub_tasks->begin(), a_sub_tasks->end());
		delete a_sub_tasks;
	}
	delete a_sub_tsks;
	a_sub_tsks = NULL;

	// tasks_garbage
	std::vector<task *>::iterator it, it2;
	for (it = tasks_garbage->begin(); it != tasks_garbage->end(); it++) {
		
		it2 = std::find(surfit_tasks->begin(), surfit_tasks->end(), *it);
		if (it2 != surfit_tasks->end())
			surfit_tasks->erase(it2);
				
		delete (*it);
	}
	delete tasks_garbage;
	tasks_garbage = NULL;
};

};

