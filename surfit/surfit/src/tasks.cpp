
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
#include "tasks.h"
#include "task.h"
#include "task_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "free_elements.h"

#include "task_user.h"

namespace surfit {


bool tasks_load(const char * filename, const char * taskname) {
	task * tsk = _task_load(filename, taskname, get_rw_mode());
	if (!tsk)
		return false;
	surfit_tasks->push_back(tsk);
	return true;
};

bool tasks_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, const char* delimiter, int grow_by) {
	task * tsk = _task_read(filename, taskname, columns, col1, col2, col3, delimiter, grow_by);
	if (!tsk)
		return false;
	surfit_tasks->push_back(tsk);
	return true;
};

bool tasks_delall() {
	if (surfit_tasks->size() == 0) {
		//writelog(SURFIT_WARNING,"tasks_delall : empty surfit_tasks");
		return false;
	}

	free_elements(surfit_tasks->begin(), surfit_tasks->end());
	surfit_tasks->resize(0);
	return true;
};

bool tasks_del(int pos) {
	if ( ((int)surfit_tasks->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"tasks_del : wrong pos");
		return false;
	}

	surfit_tasks->erase(surfit_tasks->begin()+pos);

	return true;
};

task * tasks_at(int pos) {
	if ((int)surfit_tasks->size() <= pos) {
		writelog(SURFIT_ERROR,"tasks_at : wrong pos");
		return NULL;
	}
	return *(surfit_tasks->begin()+pos);
};

task * tasks_first() {
	if (surfit_tasks->size() == 0) {
		writelog(SURFIT_ERROR,"tasks_first : empty surfit_tasks");
		return NULL;
	}
	return *(surfit_tasks->begin());
};

task * tasks_last() {
	if (surfit_tasks->size() == 0) {
		writelog(SURFIT_ERROR,"tasks_first : empty surfit_tasks");
		return NULL;
	}
	return *(surfit_tasks->end()-1);
};

bool task_concat(task * tsk) {
	if (!_task_check())
		return false;

	if (!tsk) {
		writelog(SURFIT_ERROR,"task_concat : wrong argument");
		return false;
	}
	
	int old_cnt = surfit_task->size();
	int cnt = old_cnt + tsk->size();

	REAL * ptr;
	
	ptr = (REAL *) realloc (surfit_task->X_begin, cnt*sizeof(REAL) );
	if (ptr) {
		surfit_task->X_begin = ptr;
		surfit_task->X_end = ptr + cnt;
		ptr = surfit_task->X_begin + old_cnt;
		memcpy(ptr, tsk->X_begin, tsk->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"task_concat : not enought memory");
		return false;
	};

	ptr = (REAL *) realloc (surfit_task->Y_begin, cnt*sizeof(REAL) );
	if (ptr) {
		surfit_task->Y_begin = ptr;
		surfit_task->Y_end = ptr + cnt;
		ptr = surfit_task->Y_begin + old_cnt;
		memcpy(ptr, tsk->Y_begin, tsk->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"task_concat : not enought memory");
		return false;
	};

	ptr = (REAL *) realloc (surfit_task->Z_begin, cnt*sizeof(REAL) );
	if (ptr) {
		surfit_task->Z_begin = ptr;
		surfit_task->Z_end = ptr + cnt;
		ptr = surfit_task->Z_begin + old_cnt;
		memcpy(ptr, tsk->Z_begin, tsk->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"task_concat : not enought memory");
		return false;
	};

	return true;
};

int tasks_size() {
	return surfit_tasks->size();
};

int tasks_info() {
	int max_priority = 0;
	if (surfit_task) {
		_task_info(surfit_task);
		max_priority = MAX(max_priority, surfit_task->get_priority());
	}
	
	unsigned int tasks_counter;
	for (tasks_counter = 0; tasks_counter < surfit_tasks->size(); tasks_counter++) {
		task * a_task = *(surfit_tasks->begin()+tasks_counter);
		_task_info(a_task);
		max_priority = MAX(max_priority, a_task->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;

