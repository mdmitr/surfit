
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

#ifdef HAVE_GL_WORKS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <windows.h>
#endif

#include "defarea_show.h"
#include "func_show.h"
#include "fileio.h"
#include "vec.h"
#include "grid.h"
#include "func.h"
#include "defarea.h"
#include "defarea_internal.h"
#include "defarea.h"
#include "defarea_internal.h"
#include "color_scale.h"
#include "draw.h"
#include "draw_object.h"
#include "projector.h"
#include "colors.h"
#include "grid_show.h"

#include <GL/gl.h>
#include <math.h>
#include <float.h>

int conrec(REAL **d,
	   int ilb,
	   int iub,
	   int jlb,
	   int jub,
	   REAL *x,
	   REAL *y,
	   int nc,
	   REAL *z,
	   REAL show_x_from, REAL show_x_to,
	   REAL show_y_from, REAL show_y_to,
	   REAL undef_value);

namespace surfit {

void _defarea_show(defarea * def, const char * filename) {
	if (!def)
		return;

	if (draw_defarea == 0)
		return;

	int listNo = glGenLists(1);
	double minx = FLT_MAX;
	double maxx = -FLT_MAX;
	double miny = FLT_MAX;
	double maxy = -FLT_MAX;
	double minz = FLT_MAX;
	double maxz = -FLT_MAX;

	int max_quads = def->getQuadsCount();

	float x0, y0;
	float x1, y1;
	float x2, y2;
	float x3, y3;

	glNewList(listNo,GL_COMPILE);
	
	glColor4f(grid_color_red/255.f,
		  grid_color_green/255.f,
		  grid_color_blue/255.f,
		  grid_color_alpha/255.f);

	glBegin(GL_QUADS);
	
	for (int q_cnt = 0; q_cnt < max_quads; q_cnt++) {
		
		if (!def->getQuad(q_cnt, 
			x0, y0,
			x1, y1,
			x2, y2,
			x3, y3))
			continue;
		
				
		glNormal3f(0,0,1);
		
		REAL z = get_projected_value((x0+x1)/REAL(2), (y1+y2)/REAL(2));
		
		if (z == FLT_MAX)
			continue;
		
		glVertex3f( (GLfloat)x0, (GLfloat)y0, GLfloat(z) );
		glVertex3f( (GLfloat)x1, (GLfloat)y1, (GLfloat)z );
		glVertex3f( (GLfloat)x2, (GLfloat)y2, GLfloat(z) );
		glVertex3f( (GLfloat)x3, (GLfloat)y3, GLfloat(z) );
		
		minx = MIN(minx, x0); 
		minx = MIN(minx, x1); 
		minx = MIN(minx, x2); 
		minx = MIN(minx, x3); 
		
		miny = MIN(miny, y0); 
		miny = MIN(miny, y1); 
		miny = MIN(miny, y2); 
		miny = MIN(miny, y3); 
		
		minz = MIN(minz, z); 
		
		maxx = MAX(maxx, x0); 
		maxx = MAX(maxx, x1); 
		maxx = MAX(maxx, x2); 
		maxx = MAX(maxx, x3); 
		
		maxy = MAX(maxy, y0); 
		maxy = MAX(maxy, y1); 
		maxy = MAX(maxy, y2); 
		maxy = MAX(maxy, y3); 
		
		maxz = MAX(maxz, z); 
		
	}
	glEnd();
	
	glEndList();
	
	create_draw_object(def->getName(),"def",filename,listNo,
		minx, maxx, miny, maxy, minz, maxz);
	
};

void defarea_show(const char * filename, const char * defareaname) {
	
	defarea * fnc = NULL;
	
	if (filename)
		fnc = _defarea_load(filename, defareaname, 0);
	else 
		fnc = _get_surfit_defarea();

	_defarea_show(fnc, filename);
	
	if (filename)
		delete fnc;
};

}; // namespace surfit;

#endif 
