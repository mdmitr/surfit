
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
#include "flow.h"
#include "variables.h"
#include "variables_tcl.h"
#include "flow_variables.h"
#include <float.h>

#include "prod_points_tcl.h"
#include "pcurvs_tcl.h"
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

//%include "../../surfit/src/real.h"

bool prod_points(const char * pos = "-1");
bool prod_area(REAL value, const char * pos = "-1");
bool prod_isoline(REAL value, const char * pos = "-1");
bool prod_contour(const char * pos = "-1");


}; // namespace surfit;

%include "interface/lcm.i"
%include "interface/flow_draw.i"

