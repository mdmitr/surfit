
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
#include "wtask.h"
#include "wtask_internal.h"
#include "wtask_tcl.h"
#include "task_tcl.h"
#include "task_internal.h"
#include "func.h"
#include "func_internal.h"
#include "defarea.h"
#include "defarea_internal.h"
#include "fileio.h"
#include "rnd.h"
#include "variables_internal.h"

#include "wtask_user.h"
#include "task_user.h"
#include "func_user.h"
#include "defarea_user.h"

namespace surfit {

bool wtask_load(const char * filename, const char * taskname) {
	wtask_unload();
	surfit_wtask = _wtask_load(filename, taskname, get_rw_mode());
	return (surfit_wtask != NULL);
};

bool wtask_add_noise(REAL std) {
	if (!_wtask_check()) 
		return false;

	REAL * ptr;
	for (ptr = surfit_wtask->Z_begin; ptr != surfit_wtask->Z_end; ptr++) {
		*ptr += norm_rand(std);
	}

	return true;
};

REAL wtask_mean() {
	if (!_wtask_check())
		return false;
	return surfit_wtask->mean();
};

REAL wtask_std(REAL mean) {
	if (!_wtask_check())
		return false;
	return surfit_wtask->std(mean);
};

bool wtask_save(const char * filename, const char * taskname) {
	if (!_wtask_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving wtask to file %s", filename);

	if (taskname)
		surfit_wtask->setName(taskname);

	return _wtask_save(surfit_wtask, filename, get_rw_mode());
};

void wtask_unload() {
	delete surfit_wtask;
	surfit_wtask = NULL;
};

bool wtask_check() {
	if (surfit_wtask)
		return true;
	return false;
};

int wtask_size() {
	if (_wtask_check())
		return surfit_wtask->size();
	return 0;
};

void wtask_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, int col4, const char * delimiter, int grow_by) {
	wtask_unload();
	surfit_wtask = _wtask_read(filename, taskname, columns, col1, col2, col3, col4, delimiter, grow_by);
};

bool wtask_write(const char * filename, const char * delimiter) {
	if (!_wtask_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
    strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "\n" );
	return _wtask_write(surfit_wtask, filename, buf);
};

bool wtask_filter_by_func(REAL eps) {

	if (!_func_check())
		return false;

	if (!_wtask_check())
		return false;

	int old_size = surfit_wtask->size();

	REAL * old_X_ptr = surfit_wtask->X_begin;
	REAL * old_Y_ptr = surfit_wtask->Y_begin;
	REAL * old_Z_ptr = surfit_wtask->Z_begin;
	REAL * old_W_ptr = surfit_wtask->W_begin;

	REAL * new_X_ptr = surfit_wtask->X_begin;
	REAL * new_Y_ptr = surfit_wtask->Y_begin;
	REAL * new_Z_ptr = surfit_wtask->Z_begin;
	REAL * new_W_ptr = surfit_wtask->W_begin;

	REAL z_value;

	for (;old_X_ptr != surfit_wtask->X_end; old_X_ptr++, old_Y_ptr++, old_Z_ptr++, old_W_ptr++) {
		z_value = surfit_func->getValue(*old_X_ptr, *old_Y_ptr);
		if ( fabs(z_value - *old_Z_ptr) < eps ) {
			*new_X_ptr = *old_X_ptr;
			*new_Y_ptr = *old_Y_ptr;
			*new_Z_ptr = *old_Z_ptr;
			*new_W_ptr = *old_W_ptr;
			new_X_ptr++;
			new_Y_ptr++;
			new_Z_ptr++;
			new_W_ptr++;
		}
	}

	int new_size = new_X_ptr - surfit_wtask->X_begin;

	surfit_wtask->X_begin = (REAL*)realloc(surfit_wtask->X_begin, new_size*sizeof(REAL));
	surfit_wtask->Y_begin = (REAL*)realloc(surfit_wtask->Y_begin, new_size*sizeof(REAL));
	surfit_wtask->Z_begin = (REAL*)realloc(surfit_wtask->Z_begin, new_size*sizeof(REAL));
	surfit_wtask->W_begin = (REAL*)realloc(surfit_wtask->W_begin, new_size*sizeof(REAL));

	surfit_wtask->X_end = surfit_wtask->X_begin + new_size;
	surfit_wtask->Y_end = surfit_wtask->Y_begin + new_size;
	surfit_wtask->Z_end = surfit_wtask->Z_begin + new_size;
	surfit_wtask->W_end = surfit_wtask->Z_begin + new_size;

	return true;

};

bool wtask_filter_by_defarea() {
	if (!_wtask_check())
		return false;
	if (!_defarea_check())
		return false;

	int cnt = surfit_wtask->size();
	
	REAL * new_X_begin = (REAL *)malloc( sizeof(REAL)*cnt );
	REAL * new_Y_begin = (REAL *)malloc( sizeof(REAL)*cnt );
	REAL * new_Z_begin = (REAL *)malloc( sizeof(REAL)*cnt );
	REAL * new_W_begin = (REAL *)malloc( sizeof(REAL)*cnt );

	int i,j;
	REAL x,y;
	bool val;
	j = 0;

	for (i = 0; i < cnt; i++) {
		x = *(surfit_wtask->X_begin + i);
		y = *(surfit_wtask->Y_begin + i);
		val = surfit_defarea->getValue(x,y);
		if (val) {
			*(new_X_begin + j) = x;
			*(new_Y_begin + j) = y;
			*(new_Z_begin + j) = *(surfit_wtask->Z_begin + i);
			*(new_W_begin + j) = *(surfit_wtask->W_begin + i);
			j++;
		}
	}

	new_X_begin = (REAL *)realloc(new_X_begin, sizeof(REAL)*j);
	new_Y_begin = (REAL *)realloc(new_Y_begin, sizeof(REAL)*j);
	new_Z_begin = (REAL *)realloc(new_Z_begin, sizeof(REAL)*j);
	new_W_begin = (REAL *)realloc(new_W_begin, sizeof(REAL)*j);

	free(surfit_wtask->X_begin);
	free(surfit_wtask->Y_begin);
	free(surfit_wtask->Z_begin);
	free(surfit_wtask->W_begin);

	surfit_wtask->X_begin = new_X_begin;
	surfit_wtask->X_end = new_X_begin + j;

	surfit_wtask->Y_begin = new_Y_begin;
	surfit_wtask->Y_end = new_Y_begin + j;

	surfit_wtask->Z_begin = new_Z_begin;
	surfit_wtask->Z_end = new_Z_begin + j;

	surfit_wtask->W_begin = new_W_begin;
	surfit_wtask->W_end = new_W_begin + j;

	return true;
};

bool wtask_update_by_func() {
	if (!_wtask_check())
		return false;
	if (!_func_check())
		return false;
	int i;
	REAL x, y, z;
	for (i = 0; i < surfit_wtask->size(); i++) {
		x = *(surfit_wtask->X_begin + i);
		y = *(surfit_wtask->Y_begin + i);
		z = surfit_func->getValue(x,y);
		*(surfit_wtask->Z_begin + i) = z;
	}
	return true;
};

REAL wtask_minx() {
	if (!_wtask_check())
		return false;
	return surfit_wtask->minx();
};

REAL wtask_maxx() {
	if (!_wtask_check())
		return false;
	return surfit_wtask->maxx();
};

REAL wtask_miny() {
	if (!_wtask_check())
		return false;
	return surfit_wtask->miny();
};

REAL wtask_maxy() {
	if (!_wtask_check())
		return false;
	return surfit_wtask->maxy();
};

REAL wtask_minz() {
	if (!_wtask_check())
		return false;
	return surfit_wtask->minz();
};

REAL wtask_maxz() {
	if (!_wtask_check())
		return false;
	return surfit_wtask->maxz();
};

bool wtask_name(const char * new_name, wtask * wtsk) {
	if (wtsk) {
		wtsk->setName(new_name);
		return true;
	}
	if (!_wtask_check())
		return false;
	if (!new_name) {
		if (surfit_wtask->getName())
			writelog(SURFIT_MESSAGE,"surfit_wtask name is \"%s\"",surfit_wtask->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_wtask have no name");
		return true;
	}
	surfit_wtask->setName(new_name);
	return true;
};

bool wtask_plus(wtask * wtsk) {
	if (!_wtask_check())
		return false;
	return surfit_wtask->plus(wtsk);
};

bool wtask_minus(wtask * wtsk) {
	if (!_wtask_check())
		return false;
	return surfit_wtask->minus(wtsk);
};

bool wtask_mult(wtask * wtsk) {
	if (!_wtask_check())
		return false;
	return surfit_wtask->mult(wtsk);
};

bool wtask_div(wtask * wtsk) {
	if (!_wtask_check())
		return false;
	return surfit_wtask->div(wtsk);
};

bool wtask_set(wtask * wtsk) {
	if (!_wtask_check())
		return false;
	return surfit_wtask->set(wtsk);
};

bool wtask_plus_real(REAL val) {
	if (!_wtask_check())
		return false;
	surfit_wtask->plus(val);
	return true;
};

bool wtask_minus_real(REAL val) {
	if (!_wtask_check())
		return false;
	surfit_wtask->minus(val);
	return true;
};

bool wtask_mult_real(REAL val) {
	if (!_wtask_check())
		return false;
	writelog(SURFIT_MESSAGE,"Multiplying wtask Z-values at %lf", val);
	surfit_wtask->mult(val);
	return true;
};

bool wtask_div_real(REAL val) {
	if (!_wtask_check())
		return false;
	surfit_wtask->div(val);
	return true;
};

bool wtask_set_real(REAL val) {
	if (!_wtask_check())
		return false;
	surfit_wtask->set(val);
	return true;
};

void wtask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_points_transform(surfit_wtask, shiftX, scaleX, shiftY, scaleY);
};

void wtask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_inverse_points_transform(surfit_wtask, shiftX, scaleX, shiftY, scaleY);
};

bool wtask_to_task() {
	if (!_wtask_check())
		return false;
	task_unload();
	surfit_task = surfit_wtask;
	surfit_wtask = NULL;
	return true;
};

bool wtask_to_tasks() {
	if (!_wtask_check())
		return false;
	surfit_tasks->push_back(surfit_wtask);
	surfit_wtask = NULL;
	return true;
};

bool wtask_to_wtasks() {
	if (!_wtask_check())
		return false;
	surfit_wtasks->push_back(surfit_wtask);
	surfit_wtask = NULL;
	return true;
};

}; // namespace surfit;

