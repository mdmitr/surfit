
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

#ifndef __surfit__globe_func_tcl__
#define __surfit__globe_func_tcl__

namespace surfit {

//
// CONVERTING
//

GLOBE_EXPORT
/*! \ingroup tcl_dem_conv
    \fn bool func_to_dem(const char * func_pos = "0");
    \brief transforms \ref d_func to \ref d_dem
*/
bool func_to_dem(const char * func_pos = "0");

}; // namespace surfit;

#endif

