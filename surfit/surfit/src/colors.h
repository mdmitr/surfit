
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

#ifndef __surfit_colors_included__
#define __surfit_colors_included__

namespace surfit {

// background color;

/*! \ingroup surfit_gl_variables
    \var bg_color_red
    \brief amount of red (0..255) in background color
*/
extern SURFIT_EXPORT int bg_color_red;

/*! \ingroup surfit_gl_variables
    \var bg_color_green
    \brief amount of green (0..255) in background color
*/
extern SURFIT_EXPORT int bg_color_green;

/*! \ingroup surfit_gl_variables
    \var bg_color_blue
    \brief amount of blue (0..255) in background color
*/
extern SURFIT_EXPORT int bg_color_blue;

/*! \ingroup surfit_gl_variables
    \var bg_color_alpha
    \brief amount of alpha (0..255) in background color
*/
extern SURFIT_EXPORT int bg_color_alpha;

///////////////////////////////////////

///////////////////////////////////////

///////////////////////////////////////

///////////////////////////////////////

///////////////////////////////////////

///////////////////////////////////////

///////////////////////////////////////

///////////////////////////////////////

///////////////////////////////////////


#ifdef HAVE_GL_WORKS

///////////////////////////////////////

SURFIT_EXPORT int get_bg_color_red();
SURFIT_EXPORT int get_bg_color_green();
SURFIT_EXPORT int get_bg_color_blue();
SURFIT_EXPORT int get_bg_color_alpha();

SURFIT_EXPORT 
/*! \ingroup tcl_gl
    \fn void bg_color(const char * color_name);
    \brief sets background color
    \param color_name name of color to set

    sets background color
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void bg_color(const char * color_name);

SURFIT_EXPORT 
/*! \ingroup tcl_gl
    \fn void grid_color(const char * color_name);
    \brief set color for countours
    \param color_name name of grid_color to set

    sets color for contours.
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void grid_color(const char * color_name);

SURFIT_EXPORT
bool set_colors(const char * color_name, 
		int & color_red, 
		int & color_green, 
		int & color_blue, 
		int & color_alpha);


#endif

}; // namespace surfit_gl

#endif


