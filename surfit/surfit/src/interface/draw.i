
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

%module surfit
%{
#include "draw.h"
#include "colors.h"
#include "grid_show.h"
#include "task_show.h"
#include "wtask_show.h"
#include "func_show.h"
#include "wfunc_show.h"
#include "trend_show.h"
#include "defarea_show.h"
#include "curv_show.h"
#include "iso_show.h"
#include "wiso_show.h"
#include "flt_show.h"
#include "area_show.h"
#include "warea_show.h"
#include "cntr_show.h"
#include "wcntr_show.h"
#include "file_manager.h"
%}

namespace surfit {

extern int bg_color_red;
extern int bg_color_green;
extern int bg_color_blue;
extern int bg_color_alpha;

extern int task_color_red;
extern int task_color_green;
extern int task_color_blue;
extern int task_color_alpha;

extern int wtask_color_red;
extern int wtask_color_green;
extern int wtask_color_blue;
extern int wtask_color_alpha;

extern int iso_color_red;
extern int iso_color_green;
extern int iso_color_blue;
extern int iso_color_alpha;

extern int curv_color_red;
extern int curv_color_green;
extern int curv_color_blue;
extern int curv_color_alpha;

extern int flt_color_red;
extern int flt_color_green;
extern int flt_color_blue;
extern int flt_color_alpha;

extern int warea_color_red;
extern int warea_color_green;
extern int warea_color_blue;
extern int warea_color_alpha;

extern int area_color_red;
extern int area_color_green;
extern int area_color_blue;
extern int area_color_alpha;

extern int grid_amount_x;
extern int grid_amount_y;
extern int grid_amount_z;

extern float x_shift;
extern float y_shift;
extern float scale;
extern float z_scale;

extern int axis_labels;
extern int point_size;
extern int isoline;

extern int draw_task;
extern int draw_wtask;
extern int draw_func;
extern int draw_wfunc;
extern int draw_trend;
extern int draw_iso;
extern int draw_curv;
extern int draw_wiso;
extern int draw_cntr;
extern int draw_pcntr;
extern int draw_wcntr;
extern int draw_area;
extern int draw_warea;
extern int draw_parea;
extern int draw_flt;
extern int draw_grid;
extern int draw_defarea;

extern int light;
extern int smooth;

extern int fix_axes;
extern double minx;
extern double maxx;
extern double miny;
extern double maxy;
extern double minz;
extern double maxz;

extern float show_x_from;
extern float show_x_to;
extern float show_y_from;
extern float show_y_to;
extern int  show_in_area;

%exception {
%#ifdef HAVE_GL_WORKS
        try {
                $action
        }
        catch(...) {
                return TCL_ERROR;
        }
%#else
        return TCL_ERROR;
%#endif
};

void bg_color(const char * color_name);
void task_color(const char * color_name);
void wtask_color(const char * color_name);
void flt_color(const char * color_name);
void iso_color(const char * color_name);
void wiso_color(const char * color_name);

void init(int w, int h);
void draw(int w, int h);
void draw_obj(int w, int h, const char * obj_name, const char * name = NULL);
void cleanup();

void moving(int beginx, int beginy, float x, float y, int W, int H);
void init_quat();
void get_selection_from_screen(int W, int H);

float draw_minz();
float draw_maxz();

void grid_show(const char * filename = NULL, const char * gridname = NULL);
void task_show(const char * filename = NULL, const char * taskname = NULL);
void wtask_show(const char * filename = NULL, const char * taskname = NULL);
void func_show(const char * filename = NULL, const char * funcname = NULL);
void wfunc_show(const char * filename = NULL, const char * funcname = NULL);
void trend_show(const char * filename = NULL, const char * funcname = NULL);
void defarea_show(const char * filename = NULL, const char * funcname = NULL);

void iso_show(const char * filename = NULL, const char * isoname = NULL);
void wiso_show(const char * filename = NULL, const char * isoname = NULL);
void curv_show(const char * filename = NULL, const char * curvname = NULL);
void flt_show(float value, const char * filename = NULL, const char * fltname = NULL);
void warea_show(const char * filename = NULL, const char * wareaname = NULL);
void cntr_show(const char * filename = NULL, const char * wareaname = NULL);
void wcntr_show(const char * filename = NULL, const char * wareaname = NULL);

void mem_show();
void file_show(const char * filename);

};







