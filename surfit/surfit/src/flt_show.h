
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

#ifndef __surfit_gl__flt__
#define __surfit_gl__flt__

#include <stdio.h>

namespace surfit {

class flt;

/*! \ingroup tcl_flt_gl
    \var flt_color_red
    \brief amount of red (0..255) for \ref flt drawing color
*/
extern SURFIT_EXPORT int flt_color_red;

/*! \ingroup tcl_flt_gl
    \var flt_color_green
    \brief amount of green (0..255) \ref flt drawing color
*/
extern SURFIT_EXPORT int flt_color_green;

/*! \ingroup tcl_flt_gl
    \var flt_color_blue
    \brief amount of blue (0..255) \ref flt drawing color
*/
extern SURFIT_EXPORT int flt_color_blue;

/*! \ingroup tcl_flt_gl
    \var flt_color_alpha
    \brief amount of alpha (0..255) \ref flt drawing color
*/
extern SURFIT_EXPORT int flt_color_alpha;

/*! \ingroup tcl_flt_gl
    \var draw_flt
    \brief flag for flts drawing
*/
extern SURFIT_EXPORT int draw_flt;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_flt_gl
    \fn void flt_color(const char * color_name);
    \brief sets color for \ref flt objects
    \param color_name name of flt_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void flt_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_flt_gl
    \fn void flt_show(REAL value = 0, const char * filename = NULL, const char * fltname = NULL);
    \brief shows \ref flt from ROFF file.  If no filename specified, then shows surfit_flt
*/
void flt_show(REAL value = 0, const char * filename = NULL, const char * fltname = NULL);

#endif

}; // namespace surfit;

#endif
