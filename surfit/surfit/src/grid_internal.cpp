
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

/*! \file grid_internal.cpp
    implementation of "internal" functions for grid class
*/

#include "ie.h"
#include <math.h>
#include "grid.h"
#include "grid_internal.h"
#include "task.h"
#include "task_internal.h"
#include "func.h"
#include "fileio.h"
#include "datafile.h"
#include "vec_alg.h"
#include "grid_user.h"
#include <algorithm>

namespace surfit {

bool _grid_check() {
	if (surfit_grid) 
		return true;
	return false;
};

bool _grid_save_df(grid * grd, datafile * df) {
	bool res = true;
	bool op;

	op = grd->writeTags(df);				res = (op && res);
    		
	return res;
};

bool _grid_save(grid * grd, const char * filename, int mode) {
	if (!grd) {
		writelog(SURFIT_WARNING, "NULL pointer to grid.");
		return false;
	};
	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _grid_save_df(grd, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

grid * _grid_get(REAL startX, REAL endX, REAL stepX,
                 REAL startY, REAL endY, REAL stepY,
                 const char * name) {
	
    return new grid(startX, endX, stepX,
                    startY, endY, stepY,
                    name);

};

grid * _grid_get_for_task(task *task, int Xnodes, int Ynodes, const char * name) {

	if (task->size() == 0) {
		writelog(SURFIT_WARNING,"grid_get_for_task : empty task");
		return NULL;
	}

	REAL minx = *std::min_element(task->X_begin, task->X_end);
	REAL maxx = *std::max_element(task->X_begin, task->X_end);

	REAL len_x = maxx-minx;
	if (len_x == REAL(0))
		len_x = REAL(1);

	REAL miny = *std::min_element(task->Y_begin, task->Y_end);
	REAL maxy = *std::max_element(task->Y_begin, task->Y_end);
    
	REAL len_y = maxy-miny;
	if (len_y == REAL(0))
		len_y = REAL(1);

	grid * res = new grid(minx, maxx, (maxx-minx)/(Xnodes - 1),
                              miny, maxy, (maxy-miny)/(Ynodes - 1),
                              name);

	return res;
};

grid * _grid_get_for_task_step(task *task, REAL stepX, REAL stepY, const char * name) {

	if (task->size() == 0) {
		writelog(SURFIT_WARNING,"grid_get_for_task_step : empty task");
		return NULL;
	}

	REAL minx = *std::min_element(task->X_begin, task->X_end);
	REAL maxx = *std::max_element(task->X_begin, task->X_end);

	REAL len_x = maxx-minx;
	if (len_x == REAL(0))
		len_x = REAL(1);

	REAL miny = *std::min_element(task->Y_begin, task->Y_end);
	REAL maxy = *std::max_element(task->Y_begin, task->Y_end);
    
	REAL len_y = maxy-miny;
	if (len_y == REAL(0))
		len_y = REAL(1);

	grid * res = new grid(minx, maxx, stepX,
                              miny, maxy, stepY,
                              name);

	return res;
};

grid * _grid_get_for_func(func * fnc, int Xnodes, int Ynodes, const char * name) {
	
	REAL minx = fnc->getMinX();
	REAL maxx = fnc->getMaxX();
	REAL miny = fnc->getMinY();
	REAL maxy = fnc->getMaxY();

	REAL len_x = maxx-minx;
	if (len_x == REAL(0))
		len_x = REAL(1);

	REAL len_y = maxy-miny;
	if (len_y == REAL(0))
		len_y = REAL(1);

	grid * res = new grid(minx, maxx, (maxx-minx)/(Xnodes - 1),
                              miny, maxy, (maxy-miny)/(Ynodes - 1),
                              name);

	return res;
};

grid * _grid_get_for_func_step(func * fnc, REAL stepX, REAL stepY, const char * name) {

	REAL minx = fnc->getMinX();
	REAL maxx = fnc->getMaxX();
	REAL miny = fnc->getMinY();
	REAL maxy = fnc->getMaxY();

	REAL len_x = maxx-minx;
	if (len_x == REAL(0))
		len_x = REAL(1);

	REAL len_y = maxy-miny;
	if (len_y == REAL(0))
		len_y = REAL(1);

	grid * res = new grid(minx, maxx, stepX,
                              miny, maxy, stepY,
                              name);

	return res;

};

grid * _grid_get_for_task_and_geom(const grid * grd, const task * tsk) {
	if (tsk == NULL)
		return NULL;
	if (grd == NULL)
		return NULL;

	int countX = grd->getCountX();
	int countY = grd->getCountY();

	REAL grd_startX, grd_endX;
	REAL grd_startY, grd_endY;

	grd->getCoordNode(0,0, grd_startX, grd_startY);
	grd->getCoordNode(countX-1, countY-1, grd_endX, grd_endY);

	REAL task_startX, task_endX;
	REAL task_startY, task_endY;

	minmax_value(tsk->X_begin, tsk->X_end, task_startX, task_endX);
	minmax_value(tsk->Y_begin, tsk->Y_end, task_startY, task_endY);

	int newgrd_X_from, newgrd_X_to;
	int newgrd_Y_from, newgrd_Y_to;
	int temp_int;

	if (task_startX < grd_startX)
		newgrd_X_from = 0;
	else
		grd->getCoordPoint(task_startX, grd_startY, newgrd_X_from, temp_int);

	if (task_endX > grd_endX)
		newgrd_X_to = countX;
	else
		grd->getCoordPoint(task_endX, grd_endY, newgrd_X_to, temp_int);

	
	if (task_startY < grd_startY)
		newgrd_Y_from = 0;
	else
		grd->getCoordPoint(grd_startX, task_startY, temp_int, newgrd_Y_from);

	if (task_endY > grd_endY)
		newgrd_Y_to = countY;
	else
		grd->getCoordPoint(grd_endX, task_endY, temp_int, newgrd_Y_to);

	REAL g_startX, g_endX, g_stepX;
	REAL g_startY, g_endY, g_stepY;
	grd->getCoordNode(newgrd_X_from, newgrd_Y_from, g_startX, g_startY);
	grd->getCoordNode(newgrd_X_to, newgrd_Y_to, g_endX, g_endY);
	g_stepX = grd->stepX;
	g_stepY = grd->stepY;

	return new grid(g_startX, g_endX, g_stepX, g_startY, g_endY, g_stepY);

};

bool _grid_load_df_tag_readed(datafile * df, grid *& geom) {

	REAL startX = 0;
	REAL endX = 0;
	REAL stepX = 0;
	REAL startY = 0;
	REAL endY = 0;
	REAL stepY = 0;
	
	REAL angle = 0;
	REAL pi = REAL(3.1415926535);
	REAL cos_val;
	REAL sin_val;
	REAL len;

	char * name = NULL;

	grid * res = NULL;

	if (!df->readWord()) goto exit;
	
	while ( !df->isWord("endtag" ) ) {

        if ( df->isWord("char") ) {
            // read char name
            if (!df->readWord()) goto exit;
            if ( df->isWord("name") ) {
                if ( !df->readWord() ) goto exit;

                name = (char *)malloc(strlen(df->getWord()) + 1);
                strcpy(name, df->getWord());
                goto cont;
            }
        }

	if ( df->isWord( REAL_NAME ) ) {
		
		if (!df->readWord()) goto exit;
	
		if ( df->isWord("startX") ) {
				if ( !df->readReal(startX) ) goto exit;
				goto cont;
			}
			if ( df->isWord("endX") ) {
				if ( !df->readReal(endX) ) goto exit;
				goto cont;
			}
			if ( df->isWord("stepX") ) {
				if ( !df->readReal(stepX) ) goto exit;
				goto cont;
			}
		if ( df->isWord("startY") ) {
				if ( !df->readReal(startY) ) goto exit;
				goto cont;
			}
			if ( df->isWord("endY") ) {
				if ( !df->readReal(endY) ) goto exit;
				goto cont;
			}
			if ( df->isWord("stepY") ) {
				if ( !df->readReal(stepY) ) goto exit;
				goto cont;
			}
			if ( df->isWord("angle") ) {
				if ( !df->readReal(angle) ) goto exit;
				goto cont;
			}
			if (!df->skipReal(false)) goto exit;
			goto cont;
		}
		
		if ( !df->skip(false) ) goto exit;
		goto cont;
cont:
		if ( !df->readWord() ) goto exit;
		continue;
	}


	angle = angle/REAL(180)*pi;
	len = sqrt((endX-startX)*(endX-startX) + (endY-startY)*(endY-startY));
	angle = angle + acos((endX-startX)/len);
	cos_val = cos(angle);
	sin_val = sin(angle);

	endX = startX + len*cos_val;
	endY = startY + len*sin_val;

	res = new grid(startX, endX, stepX,
                     startY, endY, stepY,
                     name);

	geom = res;

	return true;

exit:
    free(name);
    return false;
};

grid * _grid_load_df(datafile * df, const char * grid_name) {
	
	grid * grd = NULL;
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("grid")) {
			
			df->skipTagName();
						
			if (!_grid_load_df_tag_readed(df, grd)) {
				delete grd;
				return NULL;
			};

		if (!grd) {
			return NULL;
		}

		if (!grid_name) {
			return grd;
		}

		if (!grd->getName()) {
		if (!grid_name)
			return grd;
		if (strlen(grid_name) == 0)
			return grd;

                delete grd;
		grd = NULL;
                continue;
            };

            if ( strcmp(grid_name,grd->getName()) == 0 ) {
                return grd;
            }

            delete grd;
            grd = NULL;
            

        } else {
         	if (!grid_name)
			writelog(SURFIT_ERROR, "grid_load : this file have no grid");
		else
			writelog(SURFIT_ERROR, "grid_load : this file have no grid with name %s", grid_name);
		delete grd;
		return NULL;
        }

			
	};

	delete grd;
	return NULL;
};

grid * _grid_load(const char * filename, const char * gridname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	if (!df->condition()) {
		delete df;
		return NULL;
	}

	grid * grd = _grid_load_df(df, gridname);
		
	delete df;
	return grd;

};

grid * _grid_from_func(func * fnc) {
	if (!fnc)
		return NULL;
	grid * res = new grid(fnc->grd);
	return res;
};

void _set_surfit_grid(grid * grd) {
	delete surfit_grid;
	surfit_grid = grd;
};

grid * _get_surfit_grid() {
	return surfit_grid;
};

}; // namespace surfit;

