
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
#include <math.h>
#include "task.h"
#include "task_internal.h"
#include "task_tcl.h"
#include "func.h"
#include "func_internal.h"
#include "defarea.h"
#include "defarea_internal.h"
#include "fileio.h"
#include "rnd.h"
#include "variables_internal.h"

#include "task_user.h"
#include "func_user.h"
#include "defarea_user.h"
#include "wtask_user.h"

namespace surfit {

bool task_load(const char * filename, const char * taskname) {
	task_unload();
	surfit_task = _task_load(filename, taskname, get_rw_mode());
	return (surfit_task != NULL);
};

bool task_add_noise(REAL std) {
	if (!_task_check()) 
		return false;

	REAL * ptr;
	for (ptr = surfit_task->Z_begin; ptr != surfit_task->Z_end; ptr++) {
		*ptr += norm_rand(std);
	}

	return true;
};

REAL task_mean() {
	if (!_task_check())
		return false;
	return surfit_task->mean();
}

REAL task_std(REAL mean) {
	if (!_task_check())
		return false;
	return surfit_task->std(mean);
}


bool task_save(const char * filename, const char * taskname) {
	if (!_task_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving task to file %s", filename);

	if (taskname)
		surfit_task->setName(taskname);

	return _task_save(surfit_task, filename, get_rw_mode());
};

void task_unload() {
	//if (surfit_task)
	//	surfit_task->release();
	delete surfit_task;
	surfit_task = NULL;
};

bool task_check() {
	if (surfit_task)
		return true;
	return false;
};

int task_size() {
	if (_task_check())
		return surfit_task->size();
	return 0;
};

void task_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by) {
	task_unload();
	surfit_task = _task_read(filename, taskname, columns, col1, col2, col3, delimiter, grow_by);
};

bool task_write(const char * filename, const char * delimiter) {
	if (!_task_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "\n" );
	return _task_write(surfit_task, filename, buf);
};

bool task_filter_by_func(REAL eps) {

	if (!_func_check())
		return false;

	if (!_task_check())
		return false;

	int old_size = surfit_task->size();

	REAL * old_X_ptr = surfit_task->X_begin;
	REAL * old_Y_ptr = surfit_task->Y_begin;
	REAL * old_Z_ptr = surfit_task->Z_begin;

	REAL * new_X_ptr = surfit_task->X_begin;
	REAL * new_Y_ptr = surfit_task->Y_begin;
	REAL * new_Z_ptr = surfit_task->Z_begin;

	REAL z_value;

	for (;old_X_ptr != surfit_task->X_end; old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
		z_value = surfit_func->getValue(*old_X_ptr, *old_Y_ptr);
		if ( fabs(z_value - *old_Z_ptr) < eps ) {
			*new_X_ptr = *old_X_ptr;
			*new_Y_ptr = *old_Y_ptr;
			*new_Z_ptr = *old_Z_ptr;
			new_X_ptr++;
			new_Y_ptr++;
			new_Z_ptr++;
		}
	}

	int new_size = new_X_ptr - surfit_task->X_begin;

	surfit_task->X_begin = (REAL*)realloc(surfit_task->X_begin, new_size*sizeof(REAL));
	surfit_task->Y_begin = (REAL*)realloc(surfit_task->Y_begin, new_size*sizeof(REAL));
	surfit_task->Z_begin = (REAL*)realloc(surfit_task->Z_begin, new_size*sizeof(REAL));

	surfit_task->X_end = surfit_task->X_begin + new_size;
	surfit_task->Y_end = surfit_task->Y_begin + new_size;
	surfit_task->Z_end = surfit_task->Z_begin + new_size;

	return true;

};

bool task_filter_by_defarea() {
	if (!_task_check())
		return false;
	if (!_defarea_check())
		return false;

	int cnt = surfit_task->size();
	
	REAL * new_X_begin = (REAL *)malloc( sizeof(REAL)*cnt );
	REAL * new_Y_begin = (REAL *)malloc( sizeof(REAL)*cnt );
	REAL * new_Z_begin = (REAL *)malloc( sizeof(REAL)*cnt );

	int i,j;
	REAL x,y;
	bool val;
	j = 0;

	for (i = 0; i < cnt; i++) {
		x = *(surfit_task->X_begin + i);
		y = *(surfit_task->Y_begin + i);
		val = surfit_defarea->getValue(x,y);
		if (val) {
			*(new_X_begin + j) = x;
			*(new_Y_begin + j) = y;
			*(new_Z_begin + j) = *(surfit_task->Z_begin + i);
			j++;
		}
	}

	new_X_begin = (REAL *)realloc(new_X_begin, sizeof(REAL)*j);
	new_Y_begin = (REAL *)realloc(new_Y_begin, sizeof(REAL)*j);
	new_Z_begin = (REAL *)realloc(new_Z_begin, sizeof(REAL)*j);

	free(surfit_task->X_begin);
	free(surfit_task->Y_begin);
	free(surfit_task->Z_begin);

	surfit_task->X_begin = new_X_begin;
	surfit_task->X_end = new_X_begin + j;

	surfit_task->Y_begin = new_Y_begin;
	surfit_task->Y_end = new_Y_begin + j;

	surfit_task->Z_begin = new_Z_begin;
	surfit_task->Z_end = new_Z_begin + j;

	return true;
};

bool task_plus(task * tsk) {
	if (!_task_check())
		return false;
	return surfit_task->plus(tsk);
};

bool task_minus(task * tsk) {
	if (!_task_check())
		return false;
	return surfit_task->minus(tsk);
};

bool task_mult(task * tsk) {
	if (!_task_check())
		return false;
	return surfit_task->mult(tsk);
};

bool task_div(task * tsk) {
	if (!_task_check())
		return false;
	return surfit_task->div(tsk);
};

bool task_set(task * tsk) {
	if (!_task_check())
		return false;
	return surfit_task->set(tsk);
};

bool task_plus_real(REAL val) {
	if (!_task_check())
		return false;
	surfit_task->plus(val);
	return true;
};

bool task_minus_real(REAL val) {
	if (!_task_check())
		return false;
	surfit_task->minus(val);
	return true;
};

bool task_mult_real(REAL val) {
	if (!_task_check())
		return false;
	writelog(SURFIT_MESSAGE,"Multiplying task Z-values at %lf", val);
	surfit_task->mult(val);
	return true;
};

bool task_div_real(REAL val) {
	if (!_task_check())
		return false;
	surfit_task->div(val);
	return true;
};

bool task_set_real(REAL val) {
	if (!_task_check())
		return false;
	surfit_task->set(val);
	return true;
};

bool task_update_by_func() {
	if (!_task_check())
		return false;
	if (!_func_check())
		return false;
	int i;
	REAL x, y, z;
	for (i = 0; i < surfit_task->size(); i++) {
		x = *(surfit_task->X_begin + i);
		y = *(surfit_task->Y_begin + i);
		z = surfit_func->getValue(x,y);
		*(surfit_task->Z_begin + i) = z;
	}
	return true;
};

REAL task_minx() {
	if (!_task_check())
		return false;
	return surfit_task->minx();
};

REAL task_maxx() {
	if (!_task_check())
		return false;
	return surfit_task->maxx();
};

REAL task_miny() {
	if (!_task_check())
		return false;
	return surfit_task->miny();
};

REAL task_maxy() {
	if (!_task_check())
		return false;
	return surfit_task->maxy();
};

REAL task_minz() {
	if (!_task_check())
		return false;
	return surfit_task->minz();
};

REAL task_maxz() {
	if (!_task_check())
		return false;
	return surfit_task->maxz();
};

bool task_name(const char * new_name, task * tsk) {
	if (tsk) {
		tsk->setName(new_name);
		return true;
	}
	if (!_task_check())
		return false;
	if (!new_name) {
		if (surfit_task->getName())
			writelog(SURFIT_MESSAGE,"surfit_task name is \"%s\"",surfit_task->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_task have no name");
		return true;
	}
	surfit_task->setName(new_name);
	return true;
};

void task_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_points_transform(surfit_task, shiftX, scaleX, shiftY, scaleY);
};

void task_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_inverse_points_transform(surfit_task, shiftX, scaleX, shiftY, scaleY);
};

bool task_to_wtask(REAL weight) {
	if (!_task_check())
		return false;
	surfit_wtask = _task_to_wtask(surfit_task, weight);
	if (surfit_wtask) {
		task_unload();
		return true;
	}
	return false;
};

bool task_to_wtasks(REAL weight) {
	if (!_task_check())
		return false;
	wtask * wtsk = _task_to_wtask(surfit_task, weight);
	if (wtsk) {
		task_unload();
		surfit_wtasks->push_back(wtsk);
		return true;
	}
	return false;
};

bool task_to_tasks() {
	if (!_task_check())
		return false;
	surfit_tasks->push_back(surfit_task);
	surfit_task = NULL;
	return true;
};

}; // namespace surfit;

