
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

#ifndef __surfit_gl__wcntr__
#define __surfit_gl__wcntr__

#include <stdio.h>

namespace surfit {

class wcntr;

/*! \ingroup tcl_wcntr_gl
    \var wcntr_color_red
    \brief amount of red (0..255) for \ref wcntr drawing color
*/
extern SURFIT_EXPORT int wcntr_color_red;

/*! \ingroup tcl_wcntr_gl
    \var wcntr_color_green
    \brief amount of green (0..255) \ref wcntr drawing color
*/
extern SURFIT_EXPORT int wcntr_color_green;

/*! \ingroup tcl_wcntr_gl
    \var wcntr_color_blue
    \brief amount of blue (0..255) \ref wcntr drawing color
*/
extern SURFIT_EXPORT int wcntr_color_blue;

/*! \ingroup tcl_wcntr_gl
    \var wcntr_color_alpha
    \brief amount of alpha (0..255) \ref wcntr drawing color
*/
extern SURFIT_EXPORT int wcntr_color_alpha;

/*! \ingroup tcl_wcntr_gl
    \var draw_wcntr
    \brief flag for wcntrs drawing
*/
extern SURFIT_EXPORT int draw_wcntr;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_wcntr_gl
    \fn void wcntr_color(const char * color_name);
    \brief sets color for \ref wcntr objects
    \param color_name name of wcntr_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void wcntr_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_gl
    \fn void void wcntr_show(const char * filename = NULL, const char * wcntrname = NULL);
    \brief shows \ref wcntr from ROFF file.  If no filename specified, then shows \ref surfit_wcntr
*/
void wcntr_show(const char * filename = NULL, const char * wcntrname = NULL);

#endif

}; // namespace surfit;

#endif
