
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

#ifndef __surfit_gl__geom__
#define __surfit_gl__geom__

#include <stdio.h>

namespace surfit {


/*! \ingroup tcl_grid_gl
    \var grid_color_red
    amount of red (0..255) for grid  drawing color
*/
extern SURFIT_EXPORT int grid_color_red;

/*! \ingroup tcl_grid_gl
    \var grid_color_green
    amount of green (0..255) for grid  drawing color
*/
extern SURFIT_EXPORT int grid_color_green;

/*! \ingroup tcl_grid_gl
    \var grid_color_blue
    amount of blue (0..255) for grid  drawing color
*/
extern SURFIT_EXPORT int grid_color_blue;

/*! \ingroup tcl_grid_gl
    \var grid_color_alpha
    amount of alpha (0..255) for grid  drawing color
*/
extern SURFIT_EXPORT int grid_color_alpha;

#ifdef HAVE_GL_WORKS
class grid;

/*! \ingroup tcl_grid_gl
    \fn void grid_show(const char * filename, const char * gridname = NULL);
    \brief shows grid from ROFF file. If no filename specified, then shows \ref surfit_grid
*/
void grid_show(const char * filename = NULL, const char * gridname = NULL);

void _grid_show(grid * grd, const char * filename, float val = 0.0f);

#endif

}; // namespace surfit;

#endif
