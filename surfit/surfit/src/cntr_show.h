
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

#ifndef __surfit_gl__cntr__
#define __surfit_gl__cntr__

#include <stdio.h>

namespace surfit {

class cntr;

/*! \ingroup tcl_cntr_gl
    \var cntr_color_red
    \brief amount of red (0..255) for \ref cntr drawing color
*/
extern SURFIT_EXPORT int cntr_color_red;

/*! \ingroup tcl_cntr_gl
    \var cntr_color_green
    \brief amount of green (0..255) \ref cntr drawing color
*/
extern SURFIT_EXPORT int cntr_color_green;

/*! \ingroup tcl_cntr_gl
    \var cntr_color_blue
    \brief amount of blue (0..255) \ref cntr drawing color
*/
extern SURFIT_EXPORT int cntr_color_blue;

/*! \ingroup tcl_cntr_gl
    \var cntr_color_alpha
    \brief amount of alpha (0..255) \ref cntr drawing color
*/
extern SURFIT_EXPORT int cntr_color_alpha;

/*! \ingroup tcl_cntr_gl
    \var draw_cntr
    \brief flag for cntrs drawing
*/
extern SURFIT_EXPORT int draw_cntr;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_cntr_gl
    \fn void cntr_color(const char * color_name);
    \brief sets color for \ref cntr objects
    \param color_name name of cntr_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void cntr_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_gl
    \fn void void cntr_show(const char * filename = NULL, const char * cntrname = NULL);
    \brief shows \ref cntr from ROFF file.  If no filename specified, then shows \ref surfit_cntr
*/
void cntr_show(const char * filename = NULL, const char * cntrname = NULL);

SURFIT_EXPORT
void _cntr_show(cntr * crv, 
		const char * obj_name,
		const char * filename,
		int color_red, 
		int color_green,
		int color_blue,
		int color_alpha);

#endif

}; // namespace surfit;

#endif
