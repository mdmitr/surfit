
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

#ifndef __surfit_gl__wtask__
#define __surfit_gl__wtask__

#include <stdio.h>

namespace surfit {

class wtask;

/*! \ingroup tcl_wtask_gl
    \var wtask_color_red
    \brief amount of red (0..255) for wtasks points drawing color
*/
extern SURFIT_EXPORT int wtask_color_red;

/*! \ingroup tcl_wtask_gl
    \var wtask_color_green
    \brief amount of green (0..255) for wtasks points drawing color
*/
extern SURFIT_EXPORT int wtask_color_green;

/*! \ingroup tcl_wtask_gl
    \var wtask_color_blue
    \brief amount of blue (0..255) for wtasks points drawing color
*/
extern SURFIT_EXPORT int wtask_color_blue;

/*! \ingroup tcl_wtask_gl
    \var wtask_color_alpha
    \brief amount of alpha (0..255) for wtasks points drawing color
*/
extern SURFIT_EXPORT int wtask_color_alpha;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_wtask_gl
    \fn void wtask_color(const char * color_name);
    \brief sets color for \ref wtask objects
    \param color_name name of wtask_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void wtask_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_gl
    \fn void wtask_show(const char * filename, const char * wtaskname = NULL);
    \brief shows wtask from ROFF file. If no filename specified, then shows \ref surfit_wtask
*/
void wtask_show(const char * filename = NULL, const char * wtaskname = NULL);

SURFIT_EXPORT
void _wtask_show(surfit::wtask * tsk, const char * filename = NULL);

#endif

}; // namespace surfit;

#endif

