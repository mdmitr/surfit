
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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


#ifndef __surfit_gl__dem__
#define __surfit_gl__dem__

namespace surfit {

class d_dem;

/*! \ingroup tcl_dem_gl
    \var draw_dem
    \brief flag for dems drawing
*/
extern GLOBE_EXPORT int draw_dem;

#ifdef HAVE_GL_WORKS

GLOBE_EXPORT
/*! \ingroup tcl_dem_gl
    \fn void dem_show(const char * filename, const char * demname = NULL);
    \brief shows dem from ROFF file. If no filename specified, then shows \ref surfit_dem
*/
void dem_show(const char * filename = NULL, const char * demname = NULL);

GLOBE_EXPORT
void _dem_show(d_dem * fnc, int surf_draw, const char * filename = NULL);

#endif

}; // namespace surfit;

#endif

