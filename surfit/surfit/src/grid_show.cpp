
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
#include "grid_show.h"

namespace surfit {

int grid_color_red;
int grid_color_green;
int grid_color_blue;
int grid_color_alpha;

};

#ifdef HAVE_GL_WORKS

#include "grid.h"
#include "grid_internal.h"
#include "fileio.h"
#include "draw.h"
#include "draw_object.h"
#include "colors.h"

#include <stdlib.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include "windows.h"
#endif

#include <GL/gl.h>
#include <math.h>
#include <float.h>

namespace surfit {

void grid_color(const char * color_name) {
	set_colors(color_name, 
		   grid_color_red, 
		   grid_color_green, 
		   grid_color_blue, 
		   grid_color_alpha);
};

void _grid_show(grid * grd, const char * filename, float val) {

	if (!grd)
		return;

	grid * show_grid = grd;
	bool delete_show_grid = false;

	if (show_grid->getLinesCount() <= 0) 
		return;

	int listNo = glGenLists(1);
	double minx = FLT_MAX;
	double maxx = -FLT_MAX;
	double miny = FLT_MAX;
	double maxy = -FLT_MAX;
	double minz = val;
	double maxz = val;


	glNewList(listNo,GL_COMPILE);

	glColor4f(grid_color_red/255.f,
		  grid_color_green/255.f,
		  grid_color_blue/255.f,
		  grid_color_alpha/255.f);

	glLineWidth((GLfloat)point_size);
		
        float x0, y0;
	float x1, y1;
	int lines_cnt = grd->getLinesCount();

	glBegin(GL_LINES);
	for (lines_cnt = 0; lines_cnt < show_grid->getLinesCount(); lines_cnt++) {
		
			show_grid->getLine(lines_cnt, x0, y0, x1, y1);
			glVertex3f(x0,y0,val);
			glVertex3f(x1,y1,val);
			
			minx = MIN(minx, x0);
			minx = MIN(minx, x1);
			maxx = MAX(maxx, x0);
			maxx = MAX(maxx, x1);

			miny = MIN(miny, y0);
			miny = MIN(miny, y1);
			maxy = MAX(maxy, y0);
			maxy = MAX(maxy, y1);

	}
	glEnd();

	glEndList();

	create_draw_object(grd->getName(),"grid",filename,listNo,
			   minx, maxx, miny, maxy, minz, maxz);
	
	if (delete_show_grid)
		delete show_grid;
};

void grid_show(const char * filename, const char * gridname) {
	
	grid * grd = NULL;
	
	if (filename)
		grd = _grid_load(filename, gridname, 0);
	else 
		grd = _get_surfit_grid();

	_grid_show(grd, filename);
	
	if (filename)
		delete grd;
};

}; // namespace surfit;

#endif

