
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

#ifndef __surfit_gl__pcntr__
#define __surfit_gl__pcntr__

#include <stdio.h>

namespace surfit {

class pcntr;

/*! \ingroup tcl_pcntr_gl
    \var pcntr_color_red
    \brief amount of red (0..255) for \ref pcntr drawing color
*/
extern FLOW_EXPORT int pcntr_color_red;

/*! \ingroup tcl_pcntr_gl
    \var pcntr_color_green
    \brief amount of green (0..255) \ref pcntr drawing color
*/
extern FLOW_EXPORT int pcntr_color_green;

/*! \ingroup tcl_pcntr_gl
    \var pcntr_color_blue
    \brief amount of blue (0..255) \ref pcntr drawing color
*/
extern FLOW_EXPORT int pcntr_color_blue;

/*! \ingroup tcl_pcntr_gl
    \var pcntr_color_alpha
    \brief amount of alpha (0..255) \ref pcntr drawing color
*/
extern FLOW_EXPORT int pcntr_color_alpha;

/*! \ingroup tcl_pcntr_gl
    \var draw_pcntr
    \brief flag for pcntrs drawing
*/
extern FLOW_EXPORT int draw_pcntr;

#ifdef HAVE_GL_WORKS

FLOW_EXPORT 
/*! \ingroup tcl_pcntr_gl
    \fn void pcntr_color(const char * color_name);
    \brief sets color for \ref pcntr objects
    \param color_name name of pcntr_color to set

    sets color for points
    Available colors are :
    white, cyan, magenta, yellow, lblue, blue, green, red, gray, black.
*/
void pcntr_color(const char * color_name);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_gl
    \fn void void pcntr_show(const char * filename = NULL, const char * pcntrname = NULL);
    \brief shows \ref pcntr from ROFF file.  If no filename specified, then shows \ref surfit_pcntr
*/
void pcntr_show(const char * filename = NULL, const char * pcntrname = NULL);

#endif

}; // namespace surfit;

#endif
