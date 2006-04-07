
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

#ifndef __freeflow_pcurvs_tcl_included__
#define __freeflow_pcurvs_tcl_included__

namespace surfit {

/*! \ingroup tcl_freeflow_rules
    \fn bool flow_area(REAL value, const char * area_name_or_position = "0");

    \par Tcl syntax: 
    flow_area value "area_name_or_position"
*/
FLOW_EXPORT
bool flow_area(REAL value, const char * area_name_or_position = "0");

/*! \ingroup tcl_freeflow_rules
    \fn bool flow_curve(REAL value, const char * curve_name_or_position = "0");

    \par Tcl syntax: 
    flow_curve value "curve_name_or_position"
*/
FLOW_EXPORT
bool flow_curve(REAL value, const char * curve_name_or_position = "0");

/*! \ingroup tcl_freeflow_rules
    \fn bool flow_contour(const char * contour_name_or_position = "0");

    \par Tcl syntax: 
    flow_contour "contour_name_or_position"
*/
FLOW_EXPORT
bool flow_contour(const char * contour_name_or_position = "0");

}; // namespace surfit;

#endif

