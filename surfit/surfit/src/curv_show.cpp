
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
#include "curv_show.h"

namespace surfit {

int curv_color_red;
int curv_color_green;
int curv_color_blue;
int curv_color_alpha;
int draw_curv;

}; // namespace surfit;


#ifdef HAVE_GL_WORKS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include "windows.h"
#endif

#include "fileio.h"
#include "vec.h"
#include "curv.h"
#include "curv.h"
#include "curv_internal.h"
#include "variables_tcl.h"

#include "draw.h"
#include "draw_object.h"
#include "colors.h"
#include "projector.h"

#include <GL/gl.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

namespace surfit {

void curv_color(const char * color_name) {
	set_colors(color_name, 
		   curv_color_red, 
		   curv_color_green, 
		   curv_color_blue, 
		   curv_color_alpha);
};

void _curv_show(curv * crv, 
		const char * obj_name,
		const char * filename, 
		REAL value,
		int color_red, 
		int color_green,
		int color_blue,
		int color_alpha) {

	if (!crv)
		return;

	int listNo = glGenLists(1);
	double minx = FLT_MAX;
	double maxx = -FLT_MAX; 
	double miny = FLT_MAX;
	double maxy = -FLT_MAX;
	double minz = FLT_MAX;
	double maxz = -FLT_MAX;
	
	glNewList(listNo,GL_COMPILE);
	
	glColor4f(color_red/255.f,
		  color_green/255.f,
		  color_blue/255.f,
		  color_alpha/255.f);

	int i;
	float x,y,z;
	float prev_z = (float)value;
	if (value == FLT_MAX)
		prev_z = 0;
	glLineWidth((GLfloat)point_size);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < crv->size(); i++) {
		x = (float)(*(crv->X_begin+i));
		y = (float)(*(crv->Y_begin+i));
		if (use_projections && value == FLT_MAX) {
			z = (float)get_projected_value(x,y);
			if (z == FLT_MAX)
				z = prev_z;
			else
				prev_z = z;
		} else {
			z = (float)(value);
		}
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
	
	create_draw_object(filename,obj_name,filename,listNo,
			   minx, maxx, miny, maxy, minz, maxz);

};

void curv_show(const char * filename, const char * curvname) {

	if (draw_curv == 0)
		return;
	
	curv * crv = NULL;
	
	if (filename)
		crv = _curv_load(filename, curvname, 0);
	else 
		crv = _get_surfit_curv();

	if (crv)
		_curv_show(crv, "curv", filename, FLT_MAX,
		           curv_color_red,
			   curv_color_green,
			   curv_color_blue,
			   curv_color_alpha);
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif 


