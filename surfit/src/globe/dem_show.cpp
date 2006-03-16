
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "globe_ie.h"

#include "fileio.h"
#include "datafile.h"

#ifdef HAVE_GL_WORKS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <windows.h>
#endif

#include "dem_show.h"
#include "shortvec.h"
#include "grid.h"
#include "dem.h"
#include "dem_internal.h"
#include "color_scale.h"
#include "draw.h"
#include "draw_object.h"
#include "sort_alg.h"
#include "globe_variables.h"

#include <GL/gl.h>
#include <math.h>
#include <float.h>

namespace surfit {

int draw_dem = 1;

void _dem_show(d_dem * fnc, int surf_draw, const char * filename) {

	if (!fnc)
		return;

	if ((draw_dem == 0) && (draw_isolines == 0))
		return;
	
	int listNo = glGenLists(1);
	double minx = FLT_MAX;
	double maxx = -FLT_MAX;
	double miny = FLT_MAX;
	double maxy = -FLT_MAX;
	double minz = FLT_MAX;
	double maxz = -FLT_MAX;

	d_dem * show_dem = fnc;
	
	if (draw_dem) {
		
		fnc->show_smooth = (smooth != 0);
		
		if (show_dem->getTrianglesCount() == 0) 
			return;
		
		glNewList(listNo,GL_COMPILE);
		REAL x0, y0;
		REAL x1, y1;
		REAL x2, y2;
		short z0, z1, z2;
		int tri_cnt;
		
		int r,g,b;
		
		//*/
		
		int max_triangles;
		if (show_in_area)
			max_triangles = show_dem->getTrianglesCount(show_x_from, show_x_to, show_y_from, show_y_to);
		else
			max_triangles = show_dem->getTrianglesCount();
		
		glBegin(GL_TRIANGLES);
		
		for (tri_cnt = 0; tri_cnt < max_triangles; tri_cnt++) {
			
			if (show_in_area) {
				show_dem->getTriangle(tri_cnt, 
					x0, y0, z0,
					x1, y1, z1,
					x2, y2, z2,
					show_x_from, show_x_to,
					show_y_from, show_y_to);
			} else {
				show_dem->getTriangle(tri_cnt, 
					x0, y0, z0,
					x1, y1, z1,
					x2, y2, z2);
			}
			
			if (show_in_area) {
				if ( (z0 < show_z_from) || (z0 > show_z_to) ||
				     (z1 < show_z_from) || (z1 > show_z_to) ||
				     (z2 < show_z_from) || (z2 > show_z_to) )
				     continue;
			}
			
			if ((z0 == show_dem->undef_value) || 
			    (z1 == show_dem->undef_value) || 
			    (z2 == show_dem->undef_value))
				continue;
			
			float nx = float( (y1-y0)*(z2-z0) - (z1-z0)*(y2-y0) );
			float ny = float( (z1-z0)*(x2-x0) - (x1-x0)*(z2-z0) );
			float nz = float( (x1-x0)*(y2-y0) - (y1-y0)*(x2-x0) );
			glNormal3f(nx,ny,nz);
			
			if (globe_color_scale) {
				globe_color_scale->get_value(z0,r,g,b);
				glColor4f(r/255.f,
					  g/255.f,
					  b/255.f,
					  0 );
			}
			glVertex3f( (GLfloat)x0, (GLfloat)y0, GLfloat(z0) );
			
			
			if (globe_color_scale) {
				globe_color_scale->get_value(z1,r,g,b);
				glColor4f(r/255.f,
					  g/255.f,
					  b/255.f,
					  0 );
			}
			glVertex3f( (GLfloat)x1, (GLfloat)y1, (GLfloat)z1 );
			
			if (globe_color_scale) {
				globe_color_scale->get_value(z2,r,g,b);
				glColor4f(r/255.f,
					  g/255.f,
					  b/255.f,
					  0 );
			}
			glVertex3f( (GLfloat)x2, (GLfloat)y2, GLfloat(z2) );
			
			minx = MIN(minx, x0); 
			minx = MIN(minx, x1); 
			minx = MIN(minx, x2); 
			
			miny = MIN(miny, y0); 
			miny = MIN(miny, y1); 
			miny = MIN(miny, y2); 
			
			minz = MIN(minz, z0); 
			minz = MIN(minz, z1); 
			minz = MIN(minz, z2); 
			
			maxx = MAX(maxx, x0); 
			maxx = MAX(maxx, x1); 
			maxx = MAX(maxx, x2); 
			
			maxy = MAX(maxy, y0); 
			maxy = MAX(maxy, y1); 
			maxy = MAX(maxy, y2); 
			
			maxz = MAX(maxz, z0); 
			maxz = MAX(maxz, z1); 
			maxz = MAX(maxz, z2); 
			
		}
		glEnd();
		
		glEndList();
		
		create_draw_object(show_dem->getName(),"dem",filename,listNo,
			minx, maxx, miny, maxy, minz, maxz);
		
	}

};

void dem_show(const char * filename, const char * demname) {
	
	d_dem * fnc = NULL;
	
	if (filename)
		fnc = _dem_load(filename, demname, 0);
	else 
		fnc = NULL;

	_dem_show(fnc, draw_dem, filename);
	
	if (filename)
		if (fnc)
			fnc->release();
};

}; // namespace surfit;

#endif 
