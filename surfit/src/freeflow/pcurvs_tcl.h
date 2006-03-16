
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

FLOW_EXPORT
bool prod_area(REAL value, const char * pos = "-1");

FLOW_EXPORT
bool prod_isoline(REAL value, const char * pos = "-1");

FLOW_EXPORT
bool prod_contour(const char * pos = "-1");

}; // namespace surfit;

#endif

