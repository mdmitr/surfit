
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

#ifndef __surfit_gl__parea__
#define __surfit_gl__parea__

#include <stdio.h>

namespace surfit {

class parea;

/*! \ingroup tcl_parea_gl
    \var parea_color_red
    \brief amount of red (0..255) for \ref parea drawing color
*/
extern FLOW_EXPORT int parea_color_red;

/*! \ingroup tcl_parea_gl
    \var parea_color_green
    \brief amount of green (0..255) \ref parea drawing color
*/
extern FLOW_EXPORT int parea_color_green;

/*! \ingroup tcl_parea_gl
    \var parea_color_blue
    \brief amount of blue (0..255) \ref parea drawing color
*/
extern FLOW_EXPORT int parea_color_blue;

/*! \ingroup tcl_parea_gl
    \var parea_color_alpha
    \brief amount of alpha (0..255) \ref parea drawing color
*/
extern FLOW_EXPORT int parea_color_alpha;

/*! \ingroup tcl_parea_gl
    \var draw_parea
    \brief flag for pareas drawing
*/
extern FLOW_EXPORT int draw_parea;

#ifdef HAVE_GL_WORKS

FLOW_EXPORT 
/*! \ingroup tcl_parea_gl
    \fn void parea_color(const char * color_name);
    \brief sets color for \ref parea objects
    \param color_name name of parea_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void parea_color(const char * color_name);

FLOW_EXPORT
/*! \ingroup tcl_parea_gl
    \fn void void parea_show(const char * filename = NULL, const char * pareaname = NULL);
    \brief shows \ref parea from ROFF file.  If no filename specified, then shows \ref surfit_parea
*/
void parea_show(const char * filename = NULL, const char * pareaname = NULL);

#endif

}; // namespace surfit;

#endif
