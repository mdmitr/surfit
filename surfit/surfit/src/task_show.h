
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

#ifndef __surfit_gl__task__
#define __surfit_gl__task__

#include <stdio.h>

namespace surfit {

class task;

/*! \ingroup tcl_task_gl
    \var task_color_red
    \brief amount of red (0..255) for tasks points drawing color
*/
extern SURFIT_EXPORT int task_color_red;

/*! \ingroup tcl_task_gl
    \var task_color_green
    \brief amount of green (0..255) for tasks points drawing color
*/
extern SURFIT_EXPORT int task_color_green;

/*! \ingroup tcl_task_gl
    \var task_color_blue
    \brief amount of blue (0..255) for tasks points drawing color
*/
extern SURFIT_EXPORT int task_color_blue;

/*! \ingroup tcl_task_gl
    \var task_color_alpha
    \brief amount of alpha (0..255) for tasks points drawing color
*/
extern SURFIT_EXPORT int task_color_alpha;

/*! \ingroup tcl_task_gl
    \var draw_task
    \brief enables/disables \ref task drawing
*/
extern SURFIT_EXPORT int draw_task;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_task_gl
    \fn void task_color(const char * color_name);
    \brief sets color for \ref task objects
    \param color_name name of task_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void task_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_task_gl
    \fn void task_show(const char * filename = NULL, const char * taskname = NULL);
    \brief shows task from ROFF file. If no filename specified, then shows \ref surfit_task
*/
void task_show(const char * filename = NULL, const char * taskname = NULL);

SURFIT_EXPORT
void _task_show(surfit::task * tsk, const char * filename = NULL);

#endif

}; // namespace surfit;

#endif
