
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

#ifndef __freeflow_gl__ptask__
#define __freeflow_gl__ptask__

#include <stdio.h>

namespace surfit {

/*! \ingroup tcl_ptask_gl
    \var ptask_color_red
    \brief amount of red (0..255) for ptasks points drawing color
*/
extern FLOW_EXPORT int ptask_color_red;

/*! \ingroup tcl_ptask_gl
    \var ptask_color_green
    \brief amount of green (0..255) for ptasks points drawing color
*/
extern FLOW_EXPORT int ptask_color_green;

/*! \ingroup tcl_ptask_gl
    \var ptask_color_blue
    \brief amount of blue (0..255) for ptasks points drawing color
*/
extern FLOW_EXPORT int ptask_color_blue;

/*! \ingroup tcl_ptask_gl
    \var ptask_color_alpha
    \brief amount of alpha (0..255) for ptasks points drawing color
*/
extern FLOW_EXPORT int ptask_color_alpha;

/*! \ingroup tcl_ptask_gl
    \var draw_ptask
    \brief flag for \ref ptask drawing
*/
extern FLOW_EXPORT int draw_ptask;


#ifdef HAVE_GL_WORKS

class ptask;

FLOW_EXPORT 
/*! \ingroup tcl_ptask_gl
    \fn void ptask_color(const char * color_name);
    \brief sets color for \ref ptask objects
    \param color_name name of ptask_color to set

    sets color for ptasklines.
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void ptask_color(const char * color_name);

FLOW_EXPORT
/*! \ingroup tcl_ptask_gl
    \fn void ptask_show(const char * filename, const char * ptaskname = NULL);
    \brief shows ptask from ROFF file. If no filename specified, then show freeflow_ptask
*/
void ptask_show(const char * filename = NULL, const char * ptaskname = NULL);

FLOW_EXPORT
void _ptask_show(ptask * tsk, const char * filename = NULL);

#endif

}; // namespace surfit;

#endif
