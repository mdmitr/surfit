
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

#ifndef __surfit_gl_draw__
#define __surfit_gl_draw__

#include <vector>
struct Tcl_Interp;

using namespace std;

namespace surfit {

/*! \ingroup surfit_gl_variables
    \var grid_amount_x
    \brief amount of marks on X-axis
*/
extern SURFIT_EXPORT int grid_amount_x;

/*! \ingroup surfit_gl_variables
    \var grid_amount_y
    \brief amount of marks on Y-axis
*/
extern SURFIT_EXPORT int grid_amount_y;

/*! \ingroup surfit_gl_variables
    \var grid_amount_y
    \brief amount of marks on Z-axis
*/
extern SURFIT_EXPORT int grid_amount_z;

/*! \ingroup surfit_gl_variables
    \var point_size;
    \brief size of points to draw
*/
extern SURFIT_EXPORT int point_size;

/*! \ingroup surfit_gl_variables
    \var x_shift
    \brief x shift for coordinate axes moving
*/
extern SURFIT_EXPORT float x_shift;

/*! \ingroup surfit_gl_variables
    \var y_shift
    \brief y shift for coordinate axes moving
*/
extern SURFIT_EXPORT float y_shift;

/*! \ingroup surfit_gl_variables
    \var scale
    \brief scale factor
*/
extern SURFIT_EXPORT float scale;

/*! \ingroup surfit_gl_variables
    \var z_scale
    \brief additional scale factor for Z-axis
*/
extern SURFIT_EXPORT float z_scale;

/*! \ingroup surfit_gl_variables
    \var axis_labels
    \brief flag to draw axis labels
*/
extern SURFIT_EXPORT int axis_labels;

/*! \ingroup surfit_gl_variables
    \var light
    \brief flag to enable/disable lighting
*/
extern SURFIT_EXPORT int light;

/*! \ingroup surfit_gl_variables
    \var smooth
    \brief enables/disables smooth functions drawing
*/
extern SURFIT_EXPORT int smooth;

/*! \ingroup surfit_gl_variables
    \var isoline
    \brief enables/disables isolines drawing
*/
extern SURFIT_EXPORT int isoline;

/*! \ingroup surfit_gl_variables
    \var draw_wtask
    \brief flag for wtasks drawing
*/
extern SURFIT_EXPORT int draw_wtask;

/*! \ingroup surfit_gl_variables
    \var draw_func
    \brief flag for funcs drawing
*/
extern SURFIT_EXPORT int draw_func;

/*! \ingroup surfit_gl_variables
    \var draw_wfunc
    \brief flag for wfuncs drawing
*/
extern SURFIT_EXPORT int draw_wfunc;

/*! \ingroup surfit_gl_variables
    \var draw_trend
    \brief flag for trends drawing
*/
extern SURFIT_EXPORT int draw_trend;

/*! \ingroup surfit_gl_variables
    \var draw_piso
    \brief flag for pisos drawing
*/
extern SURFIT_EXPORT int draw_piso;

/*! \ingroup surfit_gl_variables
    \var draw_pcntr
    \brief flag for pcntrs drawing
*/
extern SURFIT_EXPORT int draw_pcntr;

/*! \ingroup surfit_gl_variables
    \var draw_parea
    \brief flag for pareas drawing
*/
extern SURFIT_EXPORT int draw_parea;

/*! \ingroup surfit_gl_variables
    \var draw_grid
    \brief flag for grid drawing
*/
extern SURFIT_EXPORT int draw_grid;

/*! \ingroup surfit_gl_variables
    \var draw_defarea
    \brief flag for defarea drawing
*/
extern SURFIT_EXPORT int draw_defarea;

/*! \ingroup surfit_gl_variables
    \var int use_projections
    \brief flag for projecting objects (curv, flt and others) to functions (func)
*/
extern SURFIT_EXPORT int use_projections;

/*! \ingroup surfit_gl_variables
    \var int fix_axes
    \brief flag for \ref minx, \ref maxx, \ref miny, \ref maxy, \ref minz, \ref maxz recalculating
    If fix_axes set to 1, then no recalculation will be done.
*/
extern SURFIT_EXPORT int fix_axes;

/*! \ingroup surfit_gl_variables
    \var double minx
    \brief bound for drawing
*/
extern SURFIT_EXPORT double minx;

/*! \ingroup surfit_gl_variables
    \var double maxx
    \brief bound for drawing
*/
extern SURFIT_EXPORT double maxx;

/*! \ingroup surfit_gl_variables
    \var double miny
    \brief bound for drawing
*/
extern SURFIT_EXPORT double miny;

/*! \ingroup surfit_gl_variables
    \var double maxy
    \brief bound for drawing
*/
extern SURFIT_EXPORT double maxy;

/*! \ingroup surfit_gl_variables
    \var double minz
    \brief bound for drawing
*/
extern SURFIT_EXPORT double minz;

/*! \ingroup surfit_gl_variables
    \var double maxz
    \brief bound for drawing
*/
extern SURFIT_EXPORT double maxz;

extern SURFIT_EXPORT float show_x_from;
extern SURFIT_EXPORT float show_x_to;
extern SURFIT_EXPORT float show_y_from;
extern SURFIT_EXPORT float show_y_to;
extern SURFIT_EXPORT int show_in_area;

class draw_object;

#define Y_STEP 13
#define X_STEP 8

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT
/*! \ingroup internal_gl
    \fn void init_all();
    inits all draw variables
*/
void init_draw();

SURFIT_EXPORT
void init(int w, int h);

/*! \ingroup internal_gl
    \fn void draw(int w, int h);
    draw calls openGL functions
    \param w window width
    \param h window height
*/
SURFIT_EXPORT 
void draw(int w, int h);

SURFIT_EXPORT 
void draw_obj(int w, int h, const char * obj_name, const char * name = NULL);

SURFIT_EXPORT
void cleanup();

SURFIT_EXPORT
void init_quat();

void get_selection_from_screen(int w, int h);

SURFIT_EXPORT void moving(int beginx, int beginy, float x, float y, int W, int H);

SURFIT_EXPORT 
float draw_minz();

SURFIT_EXPORT 
float draw_maxz();

#endif

}; // namespace surfit

#endif

