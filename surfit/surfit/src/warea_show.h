
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

#ifndef __surfit_gl__warea__
#define __surfit_gl__warea__

#include <stdio.h>

namespace surfit {

class warea;

/*! \ingroup tcl_warea_gl
    \var warea_color_red
    \brief amount of red (0..255) for \ref warea drawing color
*/
extern SURFIT_EXPORT int warea_color_red;

/*! \ingroup tcl_warea_gl
    \var warea_color_green
    \brief amount of green (0..255) \ref warea drawing color
*/
extern SURFIT_EXPORT int warea_color_green;

/*! \ingroup tcl_warea_gl
    \var warea_color_blue
    \brief amount of blue (0..255) \ref warea drawing color
*/
extern SURFIT_EXPORT int warea_color_blue;

/*! \ingroup tcl_warea_gl
    \var warea_color_alpha
    \brief amount of alpha (0..255) \ref warea drawing color
*/
extern SURFIT_EXPORT int warea_color_alpha;

/*! \ingroup tcl_warea_gl
    \var draw_warea
    \brief flag for wareas drawing
*/
extern SURFIT_EXPORT int draw_warea;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_warea_gl
    \fn void warea_color(const char * color_name);
    \brief sets color for \ref warea objects
    \param color_name name of warea_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void warea_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_warea_gl
    \fn void void warea_show(const char * filename = NULL, const char * wareaname = NULL);
    \brief shows \ref warea from ROFF file.  If no filename specified, then shows \ref surfit_warea
*/
void warea_show(const char * filename = NULL, const char * wareaname = NULL);

#endif

}; // namespace surfit;

#endif
