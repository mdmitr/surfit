
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

#ifndef __surfit_gl__piso__
#define __surfit_gl__piso__

#include <stdio.h>

namespace surfit {

class piso;

/*! \ingroup tcl_piso_gl
    \var piso_color_red
    \brief amount of red (0..255) for \ref piso drawing color
*/
extern FLOW_EXPORT int piso_color_red;

/*! \ingroup tcl_piso_gl
    \var piso_color_green
    \brief amount of green (0..255) \ref piso drawing color
*/
extern FLOW_EXPORT int piso_color_green;

/*! \ingroup tcl_piso_gl
    \var piso_color_blue
    \brief amount of blue (0..255) \ref piso drawing color
*/
extern FLOW_EXPORT int piso_color_blue;

/*! \ingroup tcl_piso_gl
    \var piso_color_alpha
    \brief amount of alpha (0..255) \ref piso drawing color
*/
extern FLOW_EXPORT int piso_color_alpha;

/*! \ingroup tcl_piso_gl
    \var draw_piso
    \brief flag for pisos drawing
*/
extern FLOW_EXPORT int draw_piso;

#ifdef HAVE_GL_WORKS

FLOW_EXPORT 
/*! \ingroup tcl_piso_gl
    \fn void piso_color(const char * color_name);
    \brief sets color for \ref piso objects
    \param color_name name of piso_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void piso_color(const char * color_name);

FLOW_EXPORT
/*! \ingroup tcl_piso_gl
    \fn void void piso_show(const char * filename = NULL, const char * pisoname = NULL);
    \brief shows \ref piso from ROFF file.  If no filename specified, then shows \ref surfit_piso
*/
void piso_show(const char * filename = NULL, const char * pisoname = NULL);

#endif

}; // namespace surfit;

#endif
