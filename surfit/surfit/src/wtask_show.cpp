
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
#include "wtask_show.h"

namespace surfit {

int wtask_color_red;
int wtask_color_green;
int wtask_color_blue;
int wtask_color_alpha;

};

#ifdef HAVE_GL_WORKS

#include "draw.h"
#include "draw_object.h"
#include "colors.h"
#include "projector.h"

#include "wtask.h"
#include "wtask_internal.h"
#include "fileio.h"

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include "windows.h"
#endif

#include <GL/gl.h>

#include <math.h>

#include <float.h>

using namespace surfit;

namespace surfit {

void _wtask_show(wtask * tsk, const char * filename) {

	if (draw_wtask == 0)
		return;

	if (!tsk)
		return;

	int listNo = glGenLists(1);
	double minx = FLT_MAX;
	double maxx = -FLT_MAX; 
	double miny = FLT_MAX;
	double maxy = -FLT_MAX;
	double minz = FLT_MAX;
	double maxz = -FLT_MAX;

	if (tsk->size() == 0) {
		delete tsk;
		writelog(SURFIT_WARNING, "Empty wtask.");
		return;
	};
	
	glNewList(listNo,GL_COMPILE);
	
	glColor4f(wtask_color_red/255.f,
		      wtask_color_green/255.f,
		      wtask_color_blue/255.f,
		      wtask_color_alpha/255.f);
	
	int i;
	float x,y,z;
	glPointSize((GLfloat)point_size);
	glBegin(GL_POINTS);
	for (i = 0; i < tsk->size(); i++) {
		x = (float)(*(tsk->X_begin+i));
		y = (float)(*(tsk->Y_begin+i));

		if (show_in_area) {
			if ( (x < show_x_from) || (x > show_x_to) || (y < show_y_from) || (y > show_y_to) )
				continue;
		}

		z = (float)(*(tsk->Z_begin+i));
		glVertex3f(x,y,z);
		minx = MIN(minx, x);
		maxx = MAX(maxx, x);
		miny = MIN(miny, y);
		maxy = MAX(maxy, y);
		minz = MIN(minz, z);
		maxz = MAX(maxz, z);
	};
	
	glEnd();
	
	glEndList();
	
	create_draw_object(filename,"wtask",filename,listNo,
			   minx, maxx, miny, maxy, minz, maxz);

};

void wtask_show(const char * filename, const char * wtaskname) {
	
	wtask * tsk = NULL;
	
	if (filename)
		tsk = _wtask_load(filename, wtaskname, 0);
	else 
		tsk = _get_surfit_wtask();

	_wtask_show(tsk, filename);
	
	if (filename)
		delete tsk;
};

void wtask_color(const char * color_name) {
	set_colors(color_name, 
		   wtask_color_red, 
		   wtask_color_green, 
		   wtask_color_blue, 
		   wtask_color_alpha);
};

}; // namespace surfit;

#endif
