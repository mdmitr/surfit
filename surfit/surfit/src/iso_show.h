
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

#ifndef __surfit_gl__iso__
#define __surfit_gl__iso__

#include <stdio.h>

namespace surfit {

class iso;

/*! \ingroup tcl_iso_gl
    \var iso_color_red
    \brief amount of red (0..255) for \ref iso drawing color
*/
extern SURFIT_EXPORT int iso_color_red;

/*! \ingroup tcl_iso_gl
    \var iso_color_green
    \brief amount of green (0..255) \ref iso points drawing color
*/
extern SURFIT_EXPORT int iso_color_green;

/*! \ingroup tcl_iso_gl
    \var iso_color_blue
    \brief amount of blue (0..255) \ref iso points drawing color
*/
extern SURFIT_EXPORT int iso_color_blue;

/*! \ingroup tcl_iso_gl
    \var iso_color_alpha
    \brief amount of alpha (0..255) \ref iso points drawing color
*/
extern SURFIT_EXPORT int iso_color_alpha;

/*! \ingroup tcl_iso_gl
    \var draw_iso
    \brief flag for isos drawing
*/
extern SURFIT_EXPORT int draw_iso;

#ifdef HAVE_GL_WORKS

SURFIT_EXPORT 
/*! \ingroup tcl_iso_gl
    \fn void iso_color(const char * color_name);
    \brief sets color for \ref iso objects
    \param color_name name of iso_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void iso_color(const char * color_name);

SURFIT_EXPORT
/*! \ingroup tcl_iso_gl
    \fn void iso_show(const char * filename = NULL, const char * isoname = NULL);
    \brief shows \ref iso from ROFF file. If no filename specified, then shows \ref surfit_iso
*/
void iso_show(const char * filename = NULL, const char * isoname = NULL);

#endif

}; // namespace surfit;

#endif
