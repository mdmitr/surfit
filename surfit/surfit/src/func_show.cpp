
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

#include "func_show.h"
#include "fileio.h"
#include "vec.h"
#include "grid.h"
#include "func.h"
#include "func_internal.h"
#include "color_scale.h"
#include "draw.h"
#include "draw_object.h"

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

double stepFunc(double StartX, double EndX, int amount);

void _func_show(func * fnc, int surf_draw, const char * filename) {

	if (!fnc)
		return;

	if ((surf_draw == 0) && (isoline == 0))
		return;
	
	int listNo = glGenLists(1);
	double minx = FLT_MAX;
	double maxx = -FLT_MAX;
	double miny = FLT_MAX;
	double maxy = -FLT_MAX;
	double minz = FLT_MAX;
	double maxz = -FLT_MAX;

	func * show_func = fnc;
	
	color_scale * cs = get_surfit_color_scale();        
	
	///*
	if (cs) {
		if (cs->is_default()) {
			REAL minz, maxz, step;
			show_func->getMinMaxZ(minz, maxz);
			step = stepFunc(minz, maxz, 10);
			minz = floor(minz/step)*step;
			maxz = floor(maxz/step)*step;
			cs->set(minz, maxz, step, DEFAULT_COLORS);
		}
	}


	if (surf_draw) {
		
		fnc->show_smooth = (smooth != 0);
		
		if (show_func->getTrianglesCount() == 0) 
			return;
		
		glNewList(listNo,GL_COMPILE);
		REAL x0, y0, z0;
		REAL x1, y1, z1;
		REAL x2, y2, z2;
		int tri_cnt;
		
		int r,g,b;
		
		//*/
		
		int max_triangles;
		if (show_in_area)
			max_triangles = show_func->getTrianglesCount(show_x_from, show_x_to, show_y_from, show_y_to);
		else
			max_triangles = show_func->getTrianglesCount();
		
		glBegin(GL_TRIANGLES);
		
		for (tri_cnt = 0; tri_cnt < max_triangles; tri_cnt++) {
			
			if (show_in_area) {
				show_func->getTriangle(tri_cnt, 
					x0, y0, z0,
					x1, y1, z1,
					x2, y2, z2,
					show_x_from, show_x_to,
					show_y_from, show_y_to);
			} else {
				show_func->getTriangle(tri_cnt, 
					x0, y0, z0,
					x1, y1, z1,
					x2, y2, z2);
			}
			
			if ((z0 == show_func->undef_value) || (z1 == show_func->undef_value) || (z2 == show_func->undef_value))
				continue;
			
			float nx = float( (y1-y0)*(z2-z0) - (z1-z0)*(y2-y0) );
			float ny = float( (z1-z0)*(x2-x0) - (x1-x0)*(z2-z0) );
			float nz = float( (x1-x0)*(y2-y0) - (y1-y0)*(x2-x0) );
			glNormal3f(nx,ny,nz);
			
			if (cs) {
				cs->get_value(z0,r,g,b);
				glColor4f(	r/255.f,
					g/255.f,
					b/255.f,
					0 );
			}
			glVertex3f( (GLfloat)x0, (GLfloat)y0, GLfloat(z0) );
			
			
			if (cs) {
				cs->get_value(z1,r,g,b);
				glColor4f(	r/255.f,
					g/255.f,
					b/255.f,
					0 );
			}
			glVertex3f( (GLfloat)x1, (GLfloat)y1, (GLfloat)z1 );
			
			if (cs) {
				cs->get_value(z2,r,g,b);
				glColor4f(	r/255.f,
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
		
		create_draw_object(show_func->getName(),"func",filename,listNo,
			minx, maxx, miny, maxy, minz, maxz);
		
	}

	if (isoline != 0 && (cs != NULL)) {

		listNo = glGenLists(1);
		glNewList(listNo,GL_COMPILE);

		glColor3f(0,0,0);
		
		// Ўкала
		REAL * z = (REAL*)malloc(cs->size()*sizeof(REAL));
		REAL * pz = z;
		int p;
		for (p = 0; p < cs->size()-1; p++) {
			*pz = cs->get_value(p);
			pz++;
		}
		minz = *z;
		maxz = *(z+cs->size()-2);
		
		REAL point_X, point_Y;
		
		// ќсь X
		REAL * X = (REAL*)malloc(show_func->getCountX()*sizeof(REAL));
		REAL * pX = X;
		for (p = 0; p < show_func->getCountX(); p++) {
			show_func->getCoordNode(p, 0, point_X, point_Y);
			*pX = point_X;
			pX++;
		}
		minx = *X;
		maxx = *(X+show_func->getCountX()-1);
		
		// ќсь Y
		REAL * Y = (REAL*)malloc(show_func->getCountY()*sizeof(REAL));
		REAL * pY = Y;
		for (p = 0; p < show_func->getCountY(); p++) {
			show_func->getCoordNode(0, p, point_X, point_Y);
			*pY = point_Y;// + show_func->geom->stepY/show_func->geom_scaleY;
			pY++;
		}
		miny = *Y;
		maxy = *(Y+show_func->getCountY()-1);
		
		REAL ** d = (REAL**)malloc(show_func->getCountY()*sizeof(REAL*));
		REAL ** pd = d;
		for (p = 0; p < show_func->getCountY(); p++) {
			*pd = (show_func->coeff->begin() + p*show_func->getCountX());
			pd++;
		}
		
		glLineWidth( (GLfloat)point_size );
		glBegin(GL_LINES);
		if (show_in_area) {
			int iso = conrec(d, 
			                 0, show_func->getCountY()-1,
			                 0, show_func->getCountX()-1, 
			                 Y, X, 
			                 cs->size()-1,
			                 z,
			                 show_x_from-show_func->grd->stepX, show_x_to-show_func->grd->stepX,
			                 show_y_from-show_func->grd->stepY, show_y_to-show_func->grd->stepY,
					 show_func->undef_value);
		} else {
			int iso = conrec(d, 
			                 0, show_func->getCountY()-1,
			                 0, show_func->getCountX()-1, 
			                 Y, X, 
			                 cs->size()-1,
			                 z,
			                 -FLT_MAX, FLT_MAX,
			                 -FLT_MAX, FLT_MAX,
					 show_func->undef_value);
		}
		glEnd();

		glEndList();

		create_draw_object(show_func->getName(),"isolines",filename,listNo,
		                   minx, maxx, miny, maxy, minz, maxz);
		
		free(z);
		free(X);
		free(Y);
		free(d);

	}
		
};

void func_show(const char * filename, const char * funcname) {
	
	func * fnc = NULL;
	
	if (filename)
		fnc = _func_load(filename, funcname, 0);
	else 
		fnc = _get_surfit_func();

	_func_show(fnc, draw_func, filename);
	
	if (filename)
		delete fnc;
};

}; // namespace surfit;

#endif 
