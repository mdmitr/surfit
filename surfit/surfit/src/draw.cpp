
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
#include "draw.h"
#include "draw_object.h"
#include "trackball.h"
#include "colors.h"

#include "file_manager.h"
#include "variables.h"

#include "fileio.h"
#include "func.h"
#include "funcs.h"
#include "trend.h"
#include "trends.h"
#include "sort_alg.h"

#include "func_user.h"
#include "trend_user.h"

#include "task_show.h"
#include "wtask_show.h"
#include "iso_show.h"
#include "wiso_show.h"
#include "flt_show.h"
#include "area_show.h"
#include "warea_show.h"
#include "wcntr_show.h"
#include "cntr_show.h"
#include "curv_show.h"

#include <math.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

#define SURFIT_GL_CMD_LINES 70
#define PI 3.1415926535

namespace surfit {

int grid_amount_x = 5;
int grid_amount_y;
int grid_amount_z;

int point_size;

float x_shift;
float y_shift;
float scale;
float z_scale;

int axis_labels;
int use_projections;

int light;
int smooth;
int fix_axes;
int isoline;

int draw_wtask;
int draw_func;
int draw_wfunc;
int draw_trend;
int draw_piso;
int draw_pcntr;
int draw_parea;
int draw_grid;
int draw_defarea;

double minx;
double maxx;
double miny;
double maxy;
double minz;
double maxz;

float show_x_from;
float show_x_to;
float show_y_from;
float show_y_to;
int show_in_area;

double step_x, step_y, step_z;
double len_x, len_y, len_z;
double Len_X, Len_Y, Len_Z;

float curquat[4];
float lastquat[4];

float l_curquat[4];
float l_lastquat[4];

}; // namespace surfit;

#ifdef HAVE_GL_WORKS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <windows.h>
#endif

#ifdef HAVE_FLTKLIB
#include <FL/gl.h>
#include <FL/fl_draw.H>
#else
#include <GL/gl.h>
#endif

namespace surfit { 

vector<draw_object*> draw_vector;

struct gl_init{
	gl_init() {
		init_draw();
	}
};

gl_init gl_initializer;

void init_quat() {
	curquat[0] = 0;
	curquat[1] = 0;
	curquat[2] = 1;
	curquat[3] = 0;
	l_curquat[0] = 0;
	l_curquat[1] = 0;
	l_curquat[2] = 1;
	l_curquat[3] = 0;
};

void init_draw() {

	draw_vector.resize(0);
	bg_color_red = 0;
	bg_color_green = 0;
	bg_color_blue = 0;
	bg_color_alpha = 0;
		
	grid_amount_x = 5;
	grid_amount_y = 5;
	grid_amount_z = 5;

	x_shift = 0;
	y_shift = 0;
	scale = 0.75;
	scale = 1;
	z_scale = 0.5;

	axis_labels = 0;
	use_projections = 1;

	light = 1;
	smooth = 1;
	isoline = 1;

	draw_task = 1;
	draw_wtask = 1;
	draw_func = 1;
	draw_wfunc = 1;
	draw_trend = 1;
	draw_iso = 1;
	draw_piso = 1;
	draw_wiso = 1;
	draw_cntr = 1;
	draw_pcntr = 1;
	draw_wcntr = 1;
	draw_area = 1;
	draw_warea = 1;
	draw_parea = 1;
	draw_flt = 1;
	draw_curv = 1;
	draw_grid = 1;
	draw_defarea = 1;

	point_size = 5;

	fix_axes = 0;

	minx = FLT_MAX;
	maxx = -FLT_MAX; 
	miny = FLT_MAX;
	maxy = -FLT_MAX;
	minz = FLT_MAX;
	maxz = -FLT_MAX;

	show_x_from  = -FLT_MAX;
	show_x_to    = FLT_MAX;
	show_y_from  = -FLT_MAX;
	show_y_to    = FLT_MAX;
	show_in_area = 0; // false
	
	step_x = FLT_MAX;
	step_y = FLT_MAX;
	step_z = FLT_MAX;
	len_x = FLT_MAX;
	len_y = FLT_MAX;
	len_z = FLT_MAX;
	Len_X = FLT_MAX;
	Len_Y = FLT_MAX;
	Len_Z = FLT_MAX;

	task_color("green");
	wtask_color("red");
//	ptask_color("blue");
	flt_color("white");
	curv_color("yellow");
	iso_color("blue");
	wiso_color("lblue");
	area_color("green");
	warea_color("green");
	cntr_color("red");
	wcntr_color("red");
	grid_color("cyan");

	init_quat();
	
};

void gl_print(const char * str) {
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
};

void add_draw_vector(draw_object * obj) {
	draw_vector.push_back(obj);
};

void moving(int beginx, int beginy, float x, float y, int W, int H) {

	trackball(lastquat,
		  (2.0f * beginx - W) / W,
		  (H - 2.0f * beginy) / H,
		  (2.0f * x - W) / W,
		  (H - 2.0f * y) / H);
    
	add_quats(lastquat, curquat, curquat);

	beginx += (int)x;
	beginy += (int)y;
	x = -x;
	y = -y;
	trackball(l_lastquat,
		  (2.0f * beginx - W) / W,
		  (H - 2.0f * beginy) / H,
		  (2.0f * x - W) / W,
		  (H - 2.0f * y) / H);
    
	add_quats(l_lastquat, l_curquat, l_curquat);

};

void scale_axes(double & MinX, double & MaxX,
		double & MinY, double & MaxY,
		double & MinZ, double & MaxZ,
		double & x_step, double & y_step, double & z_step,
		double & len_x, double & len_y, double & len_z,
		double & Len_X, double & Len_Y, double & Len_Z)
{

	double perc = 1./10.;

	double minx = MinX, maxx = MaxX;
	double miny = MinY, maxy = MaxY;
	double minz = MinZ, maxz = MaxZ;
	
	if ( (minx == FLT_MAX) && (maxx == -FLT_MAX) ) {
		minx = -1;
		maxx = 1;
	}
	if (minx == maxx) {
		minx -= 1;
		maxx += 1;
	}

	if ( (miny == FLT_MAX) && (maxy == -FLT_MAX) ) {
		miny = -1;
		maxy = 1;
	}
	if (miny == maxy) {
		miny -= 1;
		maxy += 1;
	}

	if ( (minz == FLT_MAX) && (maxz == -FLT_MAX) ) {
		minz = -1;
		maxz = 1;
	}
	if (minz == maxz) {
		minz -= 1;
		maxz += 1;
	}

	double temp;
	
	x_step = stepFunc(minx, maxx, grid_amount_x);
	temp = minx / x_step;
	minx = (floor(temp) * x_step);
	temp = maxx / x_step;
	maxx = (ceil(temp) * x_step);

	y_step = stepFunc(miny, maxy, grid_amount_y);
	temp = miny / y_step;
	miny = (floor(temp) * y_step);
	temp = maxy / y_step;
	maxy = (ceil(temp) * y_step);

	z_step = stepFunc(minz, maxz, grid_amount_z);
	temp = minz / z_step;
	minz = (floor(temp) * z_step);
	temp = maxz / z_step;
	maxz = (ceil(temp) * z_step);

	Len_X = x_step * (int)((maxx - minx)/x_step);
	len_x = Len_X*perc;
	minx -= len_x;
	maxx += len_x;

	Len_Y = y_step * (int)((maxy - miny)/y_step);
	len_y = Len_Y*perc;
	miny -= len_y;
	maxy += len_y;

	Len_Z = z_step * (int)((maxz - minz)/z_step);
	len_z = Len_Z*perc;
	minz -= len_z;
	maxz += len_z;

	MinX = minx;
	MaxX = maxx;
	MinY = miny;
	MaxY = maxy;
	MinZ = minz;
	MaxZ = maxz;

};

void init(int w, int h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,w,h);
	
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,  0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat amb[] = {float(0.35), float(0.35), float(0.35),1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
	GLdouble diff[] = {0.35,0.35,0.35,1};
	GLdouble spec[] = {0.35,0.35,0.35,1};
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,  1);
	glMatrixMode(GL_MODELVIEW);
};

void draw_axes(double minx, double maxx,
	       double miny, double maxy,
	       double minz, double maxz,
	       double x_step, double y_step, double z_step,
	       double len_x, double len_y, double len_z,
	       double Len_X, double Len_Y, double Len_Z,
	       int w, int h)
{

	
	glColor3f((255-get_bg_color_red())/255.f,
		  (255-get_bg_color_green())/255.f,
		  (255-get_bg_color_blue())/255.f);

	glLineWidth(2);

	int XYZ_fontsize = MAX(8,MIN((int)(10*scale/5),30));
	int axis_fontsize = MAX(8,MIN((int)(6*scale/5),20));

	// marks
	int i;
	GLfloat r_x, r_y, r_z;

	GLfloat x_down = GLfloat(minx+len_x - len_x/13.);
	GLfloat x_up   = GLfloat(minx+len_x + len_x/13.);
	GLfloat y_down = GLfloat(miny+len_y - len_y/7.);
	GLfloat y_up   = GLfloat(miny+len_y + len_y/7.);
	GLfloat z_down = GLfloat(minz+len_z - len_z/7.);
	GLfloat z_up   = GLfloat(minz+len_z + len_z/7.);
	double x_cc, y_cc, z_cc;

	if (light == 1)
		glDisable(GL_LIGHTING);


	// X-axis
	r_y = GLfloat(miny+len_y/2.);
	r_z = GLfloat(minz+len_z/2.);
	
	glBegin(GL_LINES);
	glVertex3f( GLfloat(minx+len_x/2.f), GLfloat(miny+len_y), GLfloat(minz+len_z) );
	glVertex3f( GLfloat(maxx-len_x/2.f), GLfloat(miny+len_y), GLfloat(minz+len_z) );
	glEnd();

	glBegin(GL_LINES);
	for (i = 0; i < (maxx-minx)/x_step; i++) {
		x_cc = minx+len_x + x_step*i;
		if ( (x_cc >= minx+len_x/2.) & (x_cc <= maxx-len_x/2.) ) {
			glVertex3f( GLfloat(x_cc), GLfloat(y_down), GLfloat(minz+len_z) );
			glVertex3f( GLfloat(x_cc), GLfloat(y_up),  GLfloat(minz+len_z) );
		}
	};
	glEnd();

	int max_lines = SURFIT_GL_CMD_LINES;
	int font_size = MAX(h,w)/max_lines;
	
#ifdef HAVE_FLTKLIB
	gl_font(fl_font_,font_size);
	font_size = MIN(gl_height(),24);
	gl_font(fl_font_,font_size);
#endif

	char bb[81];
	

	if (axis_labels) {
		x_cc = minx+len_x;
		for (i = 0; i < (maxx-minx)/x_step; i++) {
			x_cc += x_step;
			if ((fabs(minx) > 10e-14) && (fabs(x_cc) < 10e-5))
				x_cc = double(0);
			if ( (x_cc >= minx+len_x/2.) & (x_cc <= maxx-len_x/2.) ) {
				glRasterPos3d(x_cc, r_y, r_z);
				sprintf(bb,"%g",x_cc);
				gl_print(bb);
			}
		};
	}

	r_x = GLfloat(minx+Len_X+len_x*2);
	
	glRasterPos3d(r_x, r_y, r_z);
	gl_print("X");

	// Y-axis

	r_x = GLfloat(minx/*+len_x/2.*/);
	r_z = GLfloat(minz+len_z/2.);
	
	glBegin(GL_LINES);
	glVertex3f( GLfloat(minx+len_x), GLfloat(miny+len_y/2.f), GLfloat(minz+len_z) );
	glVertex3f( GLfloat(minx+len_x), GLfloat(maxy-len_y/2.f), GLfloat(minz+len_z) );
	glEnd();

	glBegin(GL_LINES);
	for (i = 0; i < (maxy-miny)/y_step; i++) {
		y_cc = miny+len_y + y_step*i;
		if ((y_cc >= miny+len_y/2.) && (y_cc <= maxy-len_y/2.)) {
			glVertex3f( GLfloat(x_down), GLfloat(y_cc), GLfloat(minz+len_z) );
			glVertex3f( GLfloat(x_up), GLfloat(y_cc), GLfloat(minz+len_z) );
		}
	};
	glEnd();

	if (axis_labels) {
		for (i = 0; i < (maxy-miny)/y_step; i++) {
			y_cc = miny+len_y + y_step*i;
			if ((fabs(miny) > 10e-14) && (fabs(y_cc) < 10e-5))
				y_cc = double(0);
			if ((y_cc >= miny+len_y/2.) && (y_cc <= maxy-len_y/2.)) {
				glRasterPos3d(r_x, y_cc, r_z);
				sprintf(bb,"%g",y_cc);
				gl_print(bb);
			}
		};
	}

	r_y = GLfloat(miny+Len_Y+len_y*2);
	
	glRasterPos3d(r_x, r_y, r_z);
	gl_print("Y");

	// Z-axis

	r_x = GLfloat(minx+len_x/2.);
	r_y = GLfloat(miny+len_y/2.);
	r_z = GLfloat(minz+Len_Z+len_z*2);
	
	glBegin(GL_LINES);
	glVertex3f( GLfloat(minx+len_x), GLfloat(miny+len_y), GLfloat(minz+len_z/2.f) );
	glVertex3f( GLfloat(minx+len_x), GLfloat(miny+len_y), GLfloat(maxz-len_z/2.f) );
	glEnd();

	glBegin(GL_LINES);
	for (i = 0; i < (maxz-minz)/z_step; i++) {
		z_cc = minz+len_z + z_step*i;
		if ((z_cc >= minz+len_z/2.) && (z_cc <= maxz-len_z/2.)) {
			glVertex3f( GLfloat(minx+len_x), GLfloat(y_down), GLfloat(z_cc) );
			glVertex3f( GLfloat(minx+len_x), GLfloat(y_up), GLfloat(z_cc) );
		}
	};
	glEnd();

	if (axis_labels) {
		for (i = 0; i < (maxz-minz)/z_step; i++) {
			z_cc = minz+len_z + z_step*i;
			if ((fabs(minz) > 10e-14) && (fabs(z_cc) < 10e-5))
				z_cc = double(0);
			if ((z_cc >= minz+len_z/2.) && (z_cc <= maxz-len_z/2.)) {
				glRasterPos3d(r_x, r_y, z_cc);
				sprintf(bb,"%g",z_cc);
				gl_print(bb);
			}
		};
	}

	glRasterPos3d(r_x, r_y, r_z);
	gl_print("Z");


	if (light == 1)
		glEnable(GL_LIGHTING);
};

void get_selection_from_screen(int w, int h) {
	
	minx = FLT_MAX;
	maxx = -FLT_MAX; 
	miny = FLT_MAX;
	maxy = -FLT_MAX;

	vector<draw_object*>::const_iterator it;
	
	for (it = draw_vector.begin(); it != draw_vector.end(); ++it) {
		minx = GLfloat(MIN((*it)->minx, minx));
		maxx = GLfloat(MAX((*it)->maxx, maxx));
		miny = GLfloat(MIN((*it)->miny, miny));
		maxy = GLfloat(MAX((*it)->maxy, maxy));
	};
	
	if (show_in_area) {
		minx = MAX(show_x_from, minx);
		maxx = MIN(show_x_to, maxx);
		miny = MAX(show_y_from, miny);
		maxy = MIN(show_y_to, maxy);
	}

	scale_axes(minx,maxx,miny,maxy,minz,maxz,
		   step_x, step_y, step_z,
		   len_x,len_y,len_z,Len_X,Len_Y,Len_Z);

	double c_x = (maxx+minx)/2.;
	double c_y = (maxy+miny)/2.;

	double Maxx = maxx;
	double Minx = minx;
	double Miny = miny;
	double Maxy = maxy;
	double X_shift = x_shift;
	double Scale = scale;

	double len_x = maxx-minx;
	double len_y = maxy-miny;
	double len = MAX(len_x,len_y);

	double aa = len/scale;
	
	double scale_x = 2./len_x;
	double scale_y = 2./len_y;

	c_x -= x_shift/double(w)/scale_x/scale;
	c_y -= y_shift/double(h)/scale_y/scale;

	x_shift = 0;
	y_shift = 0;

	show_x_from = float(c_x - aa/2.);
	show_x_to = float(c_x + aa/2.);
	show_y_from = float(c_y - aa/2.);
	show_y_to = float(c_y + aa/2.);

	scale /= scale;

};

void get_minmax()
{
	vector<draw_object*>::const_iterator it;
	if (fix_axes) {

	} else {
		
		if (!surfit_data_manager)
			return;
				

		minx = FLT_MAX;
		maxx = -FLT_MAX; 
		miny = FLT_MAX;
		maxy = -FLT_MAX;
		minz = FLT_MAX;
		maxz = -FLT_MAX;
		
		for (it = draw_vector.begin(); it != draw_vector.end(); ++it) {

			bool res = surfit_data_manager->check_for_drawing((*it)->getType());
			if (!res)
				continue;
			
			minx = MIN( (*it)->minx, minx );
			maxx = MAX( (*it)->maxx, maxx );
			miny = MIN( (*it)->miny, miny );
			maxy = MAX( (*it)->maxy, maxy );
			minz = MIN( (*it)->minz, minz );
			maxz = MAX( (*it)->maxz, maxz );
		}

		if (show_in_area) {
			minx = MAX(show_x_from, minx);
			maxx = MIN(show_x_to, maxx);
			miny = MAX(show_y_from, miny);
			maxy = MIN(show_y_to, maxy);
		}

	}
};

float draw_minz() {
	get_minmax();
	return float(minz);
};

float draw_maxz() {
	get_minmax();
	return float(maxz);
};

void draw(int w, int h) {

	glClearColor(bg_color_red/255.f, bg_color_green/255.f, bg_color_blue/255.f, bg_color_alpha/255.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (light == 1)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	get_minmax();

	double c_x = (maxx+minx)/2.;
	double c_y = (maxy+miny)/2.;
	double c_z = (maxz+minz)/2.;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(c_x-1,c_x+1,c_y-1,c_y+1,c_z-100,c_z+100);

	if (!fix_axes) {
		scale_axes(minx,maxx,miny,maxy,minz,maxz,
			   step_x, step_y, step_z,
			   len_x,len_y,len_z,Len_X,Len_Y,Len_Z);
	}




	// Устанавливаем свет
	float px = 1;
	float py = 1;
	float pz = 1;//c_z + 100;
	float pos[4] = {px,py,pz,0};
	float dir[3] = {-px,-py,-pz};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	double scale_x = 2./(maxx-minx);
	double scale_y = 2./(maxy-miny);
	double scale_xy = MIN(scale_x,scale_y);
	scale_x = scale_xy;
	scale_y = scale_xy;
	double scale_z = 2./(maxz-minz);
			
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glScalef(1,1,-1);

	glTranslatef( GLfloat(x_shift/double(w)), GLfloat(y_shift/double(h)), 0);

	// Смещаем центр вращения
	glTranslated(c_x,c_y,c_z);
	glScalef(-1,-1,1);
	
	GLfloat m[4][4];
	build_rotmatrix(m, curquat);
	glMultMatrixf(&m[0][0]);
	
	glScaled(scale*scale_x, scale*scale_y, -scale*scale_z*z_scale);	
	glTranslated(-c_x,-c_y,-c_z);
	
	draw_axes(minx,maxx,miny,maxy,minz,maxz,
		  step_x, step_y, step_z,
		  len_x, len_y, len_z, Len_X, Len_Y, Len_Z, 
		  w, h);

	vector<draw_object*>::const_iterator it;
		
	for (it = draw_vector.begin(); it != draw_vector.end(); ++it) {

		bool res = surfit_data_manager->check_for_drawing((*it)->getType());
		if (!res)
			continue;		

		(*it)->callList();
			
	};
	
	glPopMatrix();
	
};

void draw_obj(int w, int h, const char * Obj_name, const char * name) 
{
	glClearColor(bg_color_red/255.f, bg_color_green/255.f, bg_color_blue/255.f, bg_color_alpha/255.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (light == 1)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	vector<draw_object*>::const_iterator it;

	if (fix_axes) {

	} else {
		
		minx = FLT_MAX;
		maxx = -FLT_MAX; 
		miny = FLT_MAX;
		maxy = -FLT_MAX;
		minz = FLT_MAX;
		maxz = -FLT_MAX;
		
		for (it = draw_vector.begin(); it != draw_vector.end(); ++it) {
			if ( strcmp(Obj_name,(*it)->getType()) == 0 ) {
				const char * obj_name = (*it)->getName();
				if ( 
					(name == NULL) || 
					( (name == NULL) && (obj_name == NULL) ) ||
					( (obj_name != NULL) && (strcmp(name,(*it)->getName())==0) ) 
				   ) 
				{
					minx = GLfloat(MIN((*it)->minx, minx));
					maxx = GLfloat(MAX((*it)->maxx, maxx));
					miny = GLfloat(MIN((*it)->miny, miny));
					maxy = GLfloat(MAX((*it)->maxy, maxy));
					minz = GLfloat(MIN((*it)->minz, minz));
					maxz = GLfloat(MAX((*it)->maxz, maxz));
				}
			}
		};

		if (show_in_area) {
			minx = MAX(show_x_from, minx);
			maxx = MIN(show_x_to, maxx);
			miny = MAX(show_y_from, miny);
			maxy = MIN(show_y_from, maxy);
		}

		scale_axes(minx,maxx,miny,maxy,minz,maxz,
		       step_x, step_y, step_z,
		       len_x,len_y,len_z,Len_X,Len_Y,Len_Z);

	}


	double c_x = (maxx+minx)/2.;
	double c_y = (maxy+miny)/2.;
	double c_z = (maxz+minz)/2.;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(c_x-1,c_x+1,c_y-1,c_y+1,c_z-10,c_z+10);
	
	double scale_x = 2./(maxx-minx);
	double scale_y = 2./(maxy-miny);
	double scale_z = 2./(maxz-minz);
	double scale_xy = MIN(scale_x,scale_y);
	scale_x = scale_xy;
	scale_y = scale_xy;
			
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glScalef(1,1,-1);

	glTranslatef( GLfloat(x_shift/double(w)), GLfloat(y_shift/double(h)), 0);

	// Смещаем центр вращения
	glTranslated(c_x,c_y,c_z);
	glScalef(-1,-1,1);
		
	GLfloat m[4][4];
	build_rotmatrix(m, curquat);
	glMultMatrixf(&m[0][0]);
	
	glScaled(scale*scale_x, scale*scale_y, -scale*scale_z);	
	glTranslated(-c_x,-c_y,-c_z);

	draw_axes(minx,maxx,miny,maxy,minz,maxz,
		      step_x, step_y, step_z,
			  len_x, len_y, len_z, Len_X, Len_Y, Len_Z,
			  w, h);


	for (it = draw_vector.begin(); it != draw_vector.end(); ++it) {
		if ( strcmp(Obj_name,(*it)->getType()) == 0 ) {
			const char * obj_name = (*it)->getName();
			if ( 
				(name == NULL) || 
				( (name == NULL) && (obj_name == NULL) ) ||
				( (obj_name != NULL) && (strcmp(name,(*it)->getName())==0) ) 
			   ) 
			{
				(*it)->callList();
			}
		}
	};

	glPopMatrix();

};

void cleanup() {
	vector<draw_object*>::iterator it = draw_vector.begin();
	while( it != draw_vector.end() ) {
		delete *it;
		it++;
	}
	draw_vector.resize(0);
};

}; // namespace surfit;

#endif






