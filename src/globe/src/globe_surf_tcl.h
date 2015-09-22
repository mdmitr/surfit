
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

#ifndef __surfit__globe_surf_tcl__
#define __surfit__globe_surf_tcl__

namespace surfit {

class boolvec;

//
// CONVERTING
//

/*! \ingroup tcl_surf_conv
    \fn bool surf_to_dem(const char * surface_name = "*");

    \par Tcl syntax:
    surf_to_dem "surface_name"

    \par Description:
    transforms \ref d_surf "surface" to \ref d_dem "DEM".

    \par Implemented in library:
    libglobe
*/
boolvec * surf_to_dem(const char * surface_name_or_position = "0");

}; // namespace surfit;

#endif

