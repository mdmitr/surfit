
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

#ifndef __surfit_gl__wiso__
#define __surfit_gl__wiso__

#include <stdio.h>

namespace surfit {

class wiso;

/*! \ingroup tcl_wiso_gl
    \var wiso_color_red
    \brief amount of red (0..255) for \ref wiso drawing color
*/
extern SURFIT_EXPORT int wiso_color_red;

/*! \ingroup tcl_wiso_gl
    \var wiso_color_green
    \brief amount of green (0..255) \ref wiso points drawing color
*/
extern SURFIT_EXPORT int wiso_color_green;

/*! \ingroup tcl_wiso_gl
    \var wiso_color_blue
    \brief amount of blue (0..255) \ref wiso points drawing color
*/
extern SURFIT_EXPORT int wiso_color_blue;

/*! \ingroup tcl_wiso_gl
    \var wiso_color_alpha
    \brief amount of alpha (0..255) \ref wiso points drawing color
*/
extern SURFIT_EXPORT int wiso_color_alpha;

/*! \ingroup tcl_wiso_gl
    \var draw_wiso
    \brief flag for wisos drawing
*/
extern SURFIT_EXPORT int draw_wiso;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_wiso_gl
    \fn void wiso_color(const char * color_name);
    \brief sets color for \ref wiso objects
    \param color_name name of wiso_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void wiso_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_gl
    \fn void wiso_show(const char * filename = NULL, const char * wisoname = NULL);
    \brief shows \ref wiso from ROFF file. If no filename specified, then shows \ref surfit_wiso
*/
void wiso_show(const char * filename = NULL, const char * wisoname = NULL);

#endif

}; // namespace surfit;

#endif
