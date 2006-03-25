
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

#ifndef __surfit__globe_surf_internal__
#define __surfit__globe_surf_internal__

namespace surfit {

//
// CONVERTING
//

GLOBE_EXPORT
/*! \ingroup tcl_dem_internal
    \fn d_dem * _surf_to_dem(d_surf * srf);
    \brief transforms \ref surf to \ref dem
*/
d_dem * _surf_to_dem(d_surf * srf);

}; // namespace surfit;

#endif

