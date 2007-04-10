
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

class boolvec;

/*! \ingroup tcl_freeflow_rules
    \fn bool flow_area(REAL value, const char * area_name = "*");

    \par Tcl syntax: 
    flow_area value \ref str "area_name"
*/
FLOW_EXPORT
boolvec * flow_area(REAL value, const char * area_name = "*");

/*! \ingroup tcl_freeflow_rules
    \fn bool flow_curve(REAL value, const char * curve_name = "*");

    \par Tcl syntax: 
    flow_curve value \ref str "curve_name"
*/
FLOW_EXPORT
boolvec * flow_curve(REAL value, const char * curve_name = "*");

/*! \ingroup tcl_freeflow_rules
    \fn bool flow_contour(const char * contour_name = "*");

    \par Tcl syntax: 
    flow_contour \ref str "contour_name"
*/
FLOW_EXPORT
boolvec * flow_contour(const char * contour_name = "*");

}; // namespace surfit;

#endif

