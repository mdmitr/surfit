
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


#ifndef __surfit_gl__curv__
#define __surfit_gl__curv__

namespace surfit {

/*! \ingroup tcl_curv gl
    \var curv_color_red
    \brief amount of red (0..255) for \ref curv objects drawing
*/
extern SURFIT_EXPORT int curv_color_red;

/*! \ingroup tcl_curv_gl
    \var curv_color_green
    \brief amount of green (0..255) for \ref curv objects drawing
*/
extern SURFIT_EXPORT int curv_color_green;

/*! \ingroup tcl_curv_gl
    \var curv_color_blue
    \brief amount of blue (0..255) for \ref curv objects drawing
*/
extern SURFIT_EXPORT int curv_color_blue;

/*! \ingroup tcl_curv_gl
    \var curv_color_alpha
    \brief amount of red (0..255) for \ref curv objects drawing
*/
extern SURFIT_EXPORT int curv_color_alpha;

/*! \ingroup tcl_curv_gl
    \var draw_curv
    \brief flag for curvs drawing
*/
extern SURFIT_EXPORT int draw_curv;

#ifdef HAVE_GL_WORKS

class curv;
class cntr;

SURFIT_EXPORT 
/*! \ingroup tcl_curv_gl
    \fn void curv_color(const char * color_name);
    \brief sets color for \ref curv objects
    \param color_name name of curv_color to set

    sets color for curvlines.
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void curv_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_curv_gl
    \fn void curv_show(const char * filename = NULL, const char * curvname = NULL);
    \brief shows \ref curv from ROFF file.  If no filename specified, then shows \ref surfit_curv
*/
void curv_show(const char * filename = NULL, const char * curvname = NULL);


SURFIT_EXPORT
void _curv_show(curv * crv, const char * obj_name,
		const char * filename = NULL, REAL value = 0,
		int color_red = 255, 
		int color_green = 255,
		int color_blue = 255,
		int color_alpha = 0);

#endif

}; // namespace surfit_gl;

#endif

