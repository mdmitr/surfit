
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


#include "flow_ie.h"
#include "ptask.h"
#include "ptask_internal.h"
#include "ptask_tcl.h"
#include "func.h"
#include "func_internal.h"
#include "defarea.h"
#include "defarea_internal.h"
#include "fileio.h"
#include "variables_internal.h"
#include "rnd.h"
#include "task_tcl.h"

#include "func_user.h"
#include "defarea_user.h"
#include "ptask_user.h"
#include "task_user.h"

#include <math.h>

namespace surfit {

bool ptask_load(const char * filename, const char * ptaskname) {
	ptask_unload();
	flow_ptask = _ptask_load(filename, ptaskname, get_rw_mode());
	return (flow_ptask != NULL);
};

bool ptask_add_noise(REAL std) {
	if (!ptask_check()) 
		return false;

	REAL * ptr;
	for (ptr = flow_ptask->Z_begin; ptr != flow_ptask->Z_end; ptr++) {
		*ptr += norm_rand(std);
	}

	return true;
};

REAL ptask_mean() {
	if (!ptask_check())
		return false;
	return flow_ptask->mean();
}

REAL ptask_std(REAL mean) {
	if (!ptask_check())
		return false;
	return flow_ptask->std(mean);
}


bool ptask_save(const char * filename, const char * ptaskname) {
	if (!ptask_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving ptask to file %s", filename);

	if (ptaskname)
		flow_ptask->setName(ptaskname);

	return _ptask_save(flow_ptask, filename, get_rw_mode());
};

void ptask_unload() {
	delete flow_ptask;
	flow_ptask = NULL;
};

bool ptask_check() {
	if (flow_ptask)
		return true;
	return false;
};

int ptask_size() {
	if (ptask_check())
		return flow_ptask->size();
	return 0;
};

void ptask_read(const char * filename, const char * ptaskname, 
		int columns, 
		int col1, int col2, int col3, 
		const char * delimiter, int grow_by) {
	ptask_unload();
	flow_ptask = _ptask_read(filename, ptaskname, columns, col1, col2, col3, delimiter, grow_by);
};

bool ptask_write(const char * filename, const char * delimiter) {
	if (!ptask_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "\n" );
	return _ptask_write(flow_ptask, filename, buf);
};

bool ptask_filter_by_func(REAL eps) {

	if (!_func_check())
		return false;

	if (!ptask_check())
		return false;

	int old_size = flow_ptask->size();

	REAL * old_X_ptr = flow_ptask->X_begin;
	REAL * old_Y_ptr = flow_ptask->Y_begin;
	REAL * old_Z_ptr = flow_ptask->Z_begin;

	REAL * new_X_ptr = flow_ptask->X_begin;
	REAL * new_Y_ptr = flow_ptask->Y_begin;
	REAL * new_Z_ptr = flow_ptask->Z_begin;

	REAL z_value;

	for (;old_X_ptr != flow_ptask->X_end; old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
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

	int new_size = new_X_ptr - flow_ptask->X_begin;

	flow_ptask->X_begin = (REAL*)realloc(flow_ptask->X_begin, new_size*sizeof(REAL));
	flow_ptask->Y_begin = (REAL*)realloc(flow_ptask->Y_begin, new_size*sizeof(REAL));
	flow_ptask->Z_begin = (REAL*)realloc(flow_ptask->Z_begin, new_size*sizeof(REAL));

	flow_ptask->X_end = flow_ptask->X_begin + new_size;
	flow_ptask->Y_end = flow_ptask->Y_begin + new_size;
	flow_ptask->Z_end = flow_ptask->Z_begin + new_size;

	return true;

};

bool ptask_filter_by_defarea() {
	if (!ptask_check())
		return false;
	if (!_defarea_check())
		return false;

	int cnt = flow_ptask->size();
	
	REAL * new_X_begin = (REAL *)malloc( sizeof(REAL)*cnt );
	REAL * new_Y_begin = (REAL *)malloc( sizeof(REAL)*cnt );
	REAL * new_Z_begin = (REAL *)malloc( sizeof(REAL)*cnt );

	int i,j;
	REAL x,y;
	bool val;
	j = 0;

	for (i = 0; i < cnt; i++) {
		x = *(flow_ptask->X_begin + i);
		y = *(flow_ptask->Y_begin + i);
		val = surfit_defarea->getValue(x,y);
		if (val) {
			*(new_X_begin + j) = x;
			*(new_Y_begin + j) = y;
			*(new_Z_begin + j) = *(flow_ptask->Z_begin + i);
			j++;
		}
	}

	new_X_begin = (REAL *)realloc(new_X_begin, sizeof(REAL)*j);
	new_Y_begin = (REAL *)realloc(new_Y_begin, sizeof(REAL)*j);
	new_Z_begin = (REAL *)realloc(new_Z_begin, sizeof(REAL)*j);

	free(flow_ptask->X_begin);
	free(flow_ptask->Y_begin);
	free(flow_ptask->Z_begin);

	flow_ptask->X_begin = new_X_begin;
	flow_ptask->X_end = new_X_begin + j;

	flow_ptask->Y_begin = new_Y_begin;
	flow_ptask->Y_end = new_Y_begin + j;

	flow_ptask->Z_begin = new_Z_begin;
	flow_ptask->Z_end = new_Z_begin + j;

	return true;
};

bool ptask_plus(ptask * ptsk) {
	if (!ptask_check())
		return false;
	return flow_ptask->plus(ptsk);
};

bool ptask_minus(ptask * ptsk) {
	if (!ptask_check())
		return false;
	return flow_ptask->minus(ptsk);
};

bool ptask_mult(ptask * ptsk) {
	if (!ptask_check())
		return false;
	return flow_ptask->mult(ptsk);
};

bool ptask_div(ptask * ptsk) {
	if (!ptask_check())
		return false;
	return flow_ptask->div(ptsk);
};

bool ptask_set(ptask * ptsk) {
	if (!ptask_check())
		return false;
	return flow_ptask->set(ptsk);
};

bool ptask_plus_real(REAL val) {
	if (!ptask_check())
		return false;
	writelog(SURFIT_MESSAGE,"Increasing ptask Z-values at %lf", val);
	flow_ptask->plus(val);
	return true;
};

bool ptask_minus_real(REAL val) {
	if (!ptask_check())
		return false;
	writelog(SURFIT_MESSAGE,"Decreasing ptask Z-values at %lf", val);
	flow_ptask->minus(val);
	return true;
};

bool ptask_mult_real(REAL val) {
	if (!ptask_check())
		return false;
	writelog(SURFIT_MESSAGE,"Multiplying ptask Z-values at %lf", val);
	flow_ptask->mult(val);
	return true;
};

bool ptask_div_real(REAL val) {
	if (!ptask_check())
		return false;
	writelog(SURFIT_MESSAGE,"Dividing ptask Z-values at %lf", val);
	flow_ptask->div(val);
	return true;
};

bool ptask_set_real(REAL val) {
	if (!ptask_check())
		return false;
	flow_ptask->set(val);
	return true;
};

bool ptask_update_by_func() {
	if (!ptask_check())
		return false;
	if (!_func_check())
		return false;
	int i;
	REAL x, y, z;
	for (i = 0; i < flow_ptask->size(); i++) {
		x = *(flow_ptask->X_begin + i);
		y = *(flow_ptask->Y_begin + i);
		z = surfit_func->getValue(x,y);
		*(flow_ptask->Z_begin + i) = z;
	}
	return true;
};

REAL ptask_minx() {
	if (!ptask_check())
		return false;
	return flow_ptask->minx();
};

REAL ptask_maxx() {
	if (!ptask_check())
		return false;
	return flow_ptask->maxx();
};

REAL ptask_miny() {
	if (!ptask_check())
		return false;
	return flow_ptask->miny();
};

REAL ptask_maxy() {
	if (!ptask_check())
		return false;
	return flow_ptask->maxy();
};

REAL ptask_minz() {
	if (!ptask_check())
		return false;
	return flow_ptask->minz();
};

REAL ptask_maxz() {
	if (!ptask_check())
		return false;
	return flow_ptask->maxz();
};

bool ptask_name(const char * new_name) {
	if (!ptask_check())
		return false;
	if (new_name)
		flow_ptask->setName(new_name);
	if (flow_ptask->getName())
		writelog(SURFIT_MESSAGE,"flow_ptask name is \"%s\"",flow_ptask->getName());
	else
		writelog(SURFIT_MESSAGE,"flow_ptask have no name");
	return true;
};

void ptask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_ptask_transform(flow_ptask, shiftX, scaleX, shiftY, scaleY);
};

void ptask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_inverse_ptask_transform(flow_ptask, shiftX, scaleX, shiftY, scaleY);
};

bool ptask_to_task() {
	if (!ptask_check())
		return false;
	task_unload();
	surfit_task = flow_ptask;
	flow_ptask = NULL;
	return true;
};

bool ptask_to_tasks() {
	if (!ptask_check())
		return false;
	surfit_tasks->push_back(flow_ptask);
	flow_ptask = NULL;
	return true;
};

bool task_to_ptask() {
	if (!task_check())
		return false;
	ptask_unload();
	flow_ptask = new ptask(surfit_task);
	task_unload();
	return true;
};

bool task_to_ptasks() {
	if (!task_check())
		return false;
	ptask * pt = new ptask(surfit_task);
	task_unload();
	flow_ptasks->push_back(pt);
	return true;
};

bool ptask_to_ptasks() {
	if (!ptask_check())
		return false;
	flow_ptasks->push_back(flow_ptask);
	flow_ptask = NULL;
	return true;
};


}; // namespace surfit;

