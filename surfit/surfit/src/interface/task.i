
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
%{
#include "task_tcl.h"
#include "tasks.h"
#include "wtask_tcl.h"
#include "wtasks.h"
#include "dynamic_tcl.h"
#include "dynamics.h"
%}

namespace surfit {

class task;
class wtask;
class dynamic;

//
// task
//

//save load
bool task_load(const char *filename, const char *taskname=NULL);
void task_read(const char *filename, const char *taskname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
void task_unload();
bool task_save(const char *filename, const char *taskname=NULL);
bool task_write(const char *filename, const char *delimiter="\t");
//math
void task_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
void task_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
bool task_filter_by_defarea();
bool task_filter_by_func(REAL eps);
bool task_update_by_func();
REAL task_minx();
REAL task_maxx();
REAL task_miny();
REAL task_maxy();
REAL task_minz();
REAL task_maxz();
bool task_add_noise(REAL std);
REAL task_mean();
REAL task_std(REAL mean);
bool task_plus(task *tsk);
bool task_minus(task *tsk);
bool task_mult(task *tsk);
bool task_div(task *tsk);
bool task_set(task *tsk);
bool task_plus_real(REAL val);
bool task_minus_real(REAL val);
bool task_mult_real(REAL val);
bool task_div_real(REAL val);
bool task_set_real(REAL val);
//convers
bool task_to_wtask(REAL weight);
bool task_to_wtasks(REAL weight);
bool task_to_tasks();
//other
bool task_check();
int task_size();
bool task_name(const char *new_name=NULL, task *tsk=NULL);
//operations with task collections
bool tasks_load(const char *filename, const char *taskname=NULL);
bool tasks_read(const char *filename, const char *taskname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=" ", int grow_by=250);
bool tasks_delall();
bool tasks_del(int pos);
bool task_concat(task *tsk);
task * tasks_at(int pos);
task * tasks_first();
task * tasks_last();
int tasks_size();
int tasks_info();
 	
//
// wtask
//

//save load
bool wtask_load(const char *filename, const char *taskname=NULL);
void wtask_read(const char *filename, const char *taskname=NULL, int columns=4, int col1=1, int col2=2, int col3=3, int col4=4, const char *delimiter=" ", int grow_by=250);
void wtask_unload();
bool wtask_save(const char *filename, const char *taskname=NULL);
bool wtask_write(const char *filename, const char *delimiter="\t");
//math
void wtask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
void wtask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
bool wtask_filter_by_defarea();
bool wtask_filter_by_func(REAL eps);
bool wtask_update_by_func();
REAL wtask_minx();
REAL wtask_maxx();
REAL wtask_miny();
REAL wtask_maxy();
REAL wtask_minz();
REAL wtask_maxz();
bool wtask_add_noise(REAL std);
REAL wtask_mean();
REAL wtask_std(REAL mean);
bool wtask_plus(wtask *wtsk);
bool wtask_minus(wtask *wtsk);
bool wtask_mult(wtask *wtsk);
bool wtask_div(wtask *wtsk);
bool wtask_set(wtask *wtsk);
bool wtask_plus_real(REAL val);
bool wtask_minus_real(REAL val);
bool wtask_mult_real(REAL val);
bool wtask_div_real(REAL val);
bool wtask_set_real(REAL val);
//convers
bool wtask_to_task();
bool wtask_to_tasks();
bool wtask_to_wtasks();
//other
bool wtask_check();
int wtask_size();
bool wtask_name(const char *new_name=NULL, wtask *wtsk=NULL);
//operations with wtask collections
bool wtasks_load(const char *filename, const char *taskname=NULL);
bool wtasks_read(const char *filename, const char *taskname=NULL, int columns=4, int col1=1, int col2=2, int col3=3, int col4=4, const char *delimiter=" ", int grow_by=250);
bool wtasks_delall();
bool wtasks_del(int pos);
bool wtask_concat(wtask *wtsk);
wtask * wtasks_at(int pos);
wtask * wtasks_first();
wtask * wtasks_last();
int wtasks_size();
int wtasks_info();

//
// dynamic
//

bool dynamic_unload();
bool dynamic_load(const char * load_proc_name, const char * unload_proc_name);

bool dynamics_load(const char * iload_proc_name, const char * iunload_proc_name);
bool dynamics_delall();
int dynamics_info();
bool dynamic_name(const char * new_name, dynamic * dynam = NULL);

}; // namespace surfit;