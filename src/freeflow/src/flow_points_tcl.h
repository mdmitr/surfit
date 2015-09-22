
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

#ifndef __freeflow_flow_points_tcl_included__
#define __freeflow_flow_points_tcl_included__

namespace surfit {

class boolvec;

/*! \ingroup tcl_freeflow_rules
    \fn bool flow_points(const char * points_name = "*");

    \par Tcl syntax: 
    flow_point value "points_name"
*/
FLOW_EXPORT
boolvec * flow_points(const char * points_name = "*");

}; // namespace surfit;

#endif

