
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

/*! \file grid_tcl.cpp
	implementation of "tcl" functions for grid class
*/

#include "ie.h"
#include "grid.h"
#include "grid_internal.h"
#include "grid_tcl.h"
#include "task_internal.h"
#include "wtask_internal.h"
#include "func.h"
#include "func_internal.h"
#include "fileio.h"
#include "variables_internal.h"
#include "variables.h"
#include "file_manager.h"

#include <float.h>

#include "grid_user.h"
#include "wtask_user.h"

namespace surfit {

extern grid * surfit_grid;
extern task * surfit_task;
extern func * surfit_func;

void grid_unload() {
	if (surfit_grid) {
		writelog(SURFIT_MESSAGE,"Removing surfit_grid from memory.");
		delete surfit_grid;
		surfit_grid = NULL;
	}
};

bool grid_save(const char * filename) {
	if (!_grid_check()) 
		return false;
	return _grid_save(surfit_grid, filename, get_rw_mode());
};

bool grid_check() {
	if (surfit_grid) 
		return true;
	return false;
};

int grid_getCountX() {
	if (_grid_check())
		return surfit_grid->getCountX();
	return 0;
};

int grid_getCountY() {
	if (_grid_check())
		return surfit_grid->getCountY();
	return 0;
};

REAL grid_getCoordNodeX(int i) {
    if (_grid_check()) 
        return surfit_grid->getCoordNodeX(i);
	return FLT_MAX;
};

REAL grid_getCoordNodeY(int j) {
    if (_grid_check()) 
        return surfit_grid->getCoordNodeY(j);
	return FLT_MAX;
};

REAL grid_getStepX() {
	if (_grid_check()) {
		return surfit_grid->stepX;
	}
	return 0;
};

REAL grid_getStepY() {
	if (_grid_check()) {
		return surfit_grid->stepY;
	}
	return 0;
};

bool grid_get(REAL startX, REAL endX, REAL stepX,
              REAL startY, REAL endY, REAL stepY,
              const char * name) {
	grid_unload();
	surfit_grid = _grid_get(startX, endX, stepX,
                                startY, endY, stepY,
                                name);

	grid_info();
	return (surfit_grid != NULL);
};

bool grid_get2(REAL startX, REAL endX, REAL stepX,
               REAL startY, REAL endY, REAL stepY,
               const char * name) {
	grid_unload();
	surfit_grid = _grid_get(startX, endX, stepX,
                                startY, endY, stepY,
                                name);

	grid * grd = create_last_grd();
	delete surfit_grid;
	surfit_grid = grd;

	grid_info();
	return (surfit_grid != NULL);
};

bool grid_get_for_task(int Xnodes, int Ynodes, const char * name) {
	if (!_task_check() && !_wtask_check())
		return false;
	grid_unload();
	if (surfit_task)
		surfit_grid = _grid_get_for_task(surfit_task, Xnodes, Ynodes, name);
	else 
		surfit_grid = _grid_get_for_task((task*)surfit_wtask, Xnodes, Ynodes, name);
	grid_info();
    return (surfit_grid != NULL);
};

bool grid_get_for_task_step(REAL stepX, REAL stepY, const char * name) {
	if (!_task_check())
		return false;
	grid_unload();
	surfit_grid = _grid_get_for_task_step(surfit_task, stepX, stepY, name);
	grid_info();
    return (surfit_grid != NULL);
};

bool grid_get_for_func(int Xnodes, int Ynodes, const char * name) {
	if (!_func_check())
		return false;
	grid_unload();
	surfit_grid = _grid_get_for_func(surfit_func, Xnodes, Ynodes, name);
	grid_info();
    return (surfit_grid != NULL);
};

bool grid_get_from_func(const char * name) {
	if (!_func_check())
		return false;
	grid_unload();
	surfit_grid = new grid(surfit_func->grd);
	surfit_grid->setName(name);
	grid_info();
    return (surfit_grid != NULL);
};

bool grid_get_for_func_step(REAL stepX, REAL stepY, const char * name) {
	if (!_func_check())
		return false;
	grid_unload();
	surfit_grid = _grid_get_for_func_step(surfit_func, stepX, stepY, name);
	grid_info();
    return (surfit_grid != NULL);
};

bool grid_load(const char * filename, const char * gridname) {
	grid_unload();
	surfit_grid = _grid_load(filename, gridname, get_rw_mode());
	grid_info();
	return (surfit_grid != NULL);
};

bool grid_get_from_func() {
	if (!_func_check())
		return false;
	grid * res = _grid_from_func(surfit_func);
	if (!res)
		return false;
	grid_unload();
	surfit_grid = res;
	grid_info();
	return true;
};

void grid_info() {
	if (!surfit_grid)
		return;
	writelog(SURFIT_MESSAGE,"grid: (%.2lf <-> %.2lf) / %.2lf; (%.2lf <-> %.2lf) / %.2lf.",
		surfit_grid->startX, surfit_grid->endX, surfit_grid->stepX,
		surfit_grid->startY, surfit_grid->endY, surfit_grid->stepY);
};

bool grid_auto(REAL stepX, REAL stepY, REAL percent) {
	int cnt = surfit_data_manager->data_count();		
	if (cnt == 0)
		return false;
	int i;
	REAL gminx = FLT_MAX, gmaxx = -FLT_MAX, gminy = FLT_MAX, gmaxy = -FLT_MAX;
	REAL minx, maxx, miny, maxy;
	for (i = 0; i < cnt; i++) {
		const data * dat = surfit_data_manager->data_get(i);
		if (!dat)
			continue;
		if (dat->bounds(minx, maxx, miny, maxy)) {
			gminx = MIN(gminx, minx);
			gmaxx = MAX(gmaxx, maxx);
			gminy = MIN(gminy, miny);
			gmaxy = MAX(gmaxy, maxy);
		};
	}
	if ( (gminx == FLT_MAX) || 
	     (gmaxx == -FLT_MAX) ||
	     (gminy == FLT_MAX) || 
	     (gmaxy == -FLT_MAX) )
		return false;

	REAL lenx = gmaxx-gminx;
	REAL leny = gmaxy-gminy;

	// add % of lenght
	if (percent == 0)
		percent = 2;
	gminx -= lenx/REAL(100)*REAL(percent/REAL(2));
	gmaxx += lenx/REAL(100)*REAL(percent/REAL(2));
	gminy -= leny/REAL(100)*REAL(percent/REAL(2));
	gmaxy += leny/REAL(100)*REAL(percent/REAL(2));

	REAL new_stepX, new_stepY;
	
	if (stepX == 0) 
		new_stepX = (gmaxx-gminx)/REAL(255);
	else
		new_stepX = stepX;
	
	if (stepY == 0) 
		new_stepY = (gmaxy-gminy)/REAL(255);
	else
		new_stepY = stepY;

	if ((stepY == 0) && (stepX != 0)) {
		new_stepY = new_stepX;
	}
			
	return grid_get(gminx, gmaxx, new_stepX, gminy, gmaxy, new_stepY);
};

bool grid_auto2(REAL stepX, REAL stepY, REAL percent) {
	int cnt = surfit_data_manager->data_count();		
	if (cnt == 0)
		return false;
	int i;
	REAL gminx = FLT_MAX, gmaxx = -FLT_MAX, gminy = FLT_MAX, gmaxy = -FLT_MAX;
	REAL minx, maxx, miny, maxy;
	for (i = 0; i < cnt; i++) {
		const data * dat = surfit_data_manager->data_get(i);
		if (!dat)
			continue;
		if (dat->bounds(minx, maxx, miny, maxy)) {
			gminx = MIN(gminx, minx);
			gmaxx = MAX(gmaxx, maxx);
			gminy = MIN(gminy, miny);
			gmaxy = MAX(gmaxy, maxy);
		};
	}
	if ( (gminx == FLT_MAX) || 
	     (gmaxx == -FLT_MAX) ||
	     (gminy == FLT_MAX) || 
	     (gmaxy == -FLT_MAX) )
		return false;

	REAL lenx = gmaxx-gminx;
	REAL leny = gmaxy-gminy;

	// add % of lenght
	if (percent == 0)
		percent = 2;
	gminx -= lenx/REAL(100)*REAL(percent/REAL(2));
	gmaxx += lenx/REAL(100)*REAL(percent/REAL(2));
	gminy -= leny/REAL(100)*REAL(percent/REAL(2));
	gmaxy += leny/REAL(100)*REAL(percent/REAL(2));

	REAL new_stepX, new_stepY;
	
	if (stepX == 0) 
		new_stepX = (gmaxx-gminx)/REAL(250);
	else
		new_stepX = stepX;
	
	if (stepY == 0) 
		new_stepY = (gmaxy-gminy)/REAL(250);
	else
		new_stepY = stepY;

	if ((stepY == 0) && (stepX != 0)) {
		new_stepY = new_stepX;
	}

	return grid_get2(gminx, gmaxx, new_stepX, gminy, gmaxy, new_stepY);
};


}; // namespace surfit;

