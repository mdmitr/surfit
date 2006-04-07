
/*------------------------------------------------------------------------------
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

/* File : freeflow.i */

%module freeflow
%{
#include "real.h"
#include "flow_ie.h"
#include "variables.h"
#include "variables_tcl.h"
#include "flow_variables.h"
#include <float.h>

#include "flow_points_tcl.h"
#include "flow_curvs_tcl.h"
%}

%init 
%{
surfit::freeflow_init_variables(interp);
%}

namespace surfit {

%exception {
        try {
		if (surfit::stop_execution == 0) {
                $action
		}
        }
        catch(...) {
                return TCL_ERROR;
        }
};

%typemap(out) char * {
   Tcl_SetObjResult(interp,Tcl_NewStringObj($1,-1));
   free($1);
};

%typemap(out) const char * {
   Tcl_SetObjResult(interp,Tcl_NewStringObj($1,-1));
};

%include "../../src/sstuff/real.h"

bool flow_points(const char * points_name_or_position = "0");
bool flow_area(REAL value, const char * area_name_or_position = "0");
bool flow_curve(REAL value, const char * curve_name_or_position = "0");
bool flow_contour(const char * contour_name_or_position = "0");


}; // namespace surfit;

%include "interface/lcm.i"

