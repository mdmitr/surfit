
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
#include "cntr_show.h"

namespace surfit {

int cntr_color_red;
int cntr_color_green;
int cntr_color_blue;
int cntr_color_alpha;
int draw_cntr;

};

#ifdef HAVE_GL_WORKS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include "windows.h"
#endif

#include "draw.h"
#include "draw_object.h"
#include "cntr.h"
#include "colors.h"
#include "curv_show.h"
#include "cntr_internal.h"
#include "variables_tcl.h"

#include <GL/gl.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

namespace surfit {

void cntr_color(const char * color_name) {
	set_colors(color_name, 
		   cntr_color_red, 
		   cntr_color_green, 
		   cntr_color_blue, 
		   cntr_color_alpha);
};

void cntr_show(const char * filename, const char * cntrname) {

	if (draw_cntr == 0)
		return;
	
	cntr * crv = NULL;
	
	if (filename)
		crv = _cntr_load(filename, cntrname, 0);
	else 
		crv = _get_surfit_cntr();

	if (crv)
		_cntr_show(crv, "cntr", filename,
		           cntr_color_red,
			   cntr_color_green,
			   cntr_color_blue,
			   cntr_color_alpha);
	
	if (filename)
		delete crv;
};

void _cntr_show(cntr * crv, 
		const char * obj_name,
		const char * filename,
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
	glLineWidth((GLfloat)point_size);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < crv->size(); i++) {
		x = (float)(*(crv->X_begin+i));
		y = (float)(*(crv->Y_begin+i));
		z = (float)(*(crv->Z_begin+i));
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

}; // namespace surfit;

#endif

