
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
#include "flow_ie.h"
#include "real.h"
#include "boolvec.h"
#include "vec.h"
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

%typemap(out) surfit::vec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			double val = (double)(*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewDoubleObj(val));
		}
		($1)->release();
	}
}

%typemap(out) surfit::intvec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			int val = (int)(*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewIntObj(val));
		}
		($1)->release();
	}
}

%typemap(out) surfit::boolvec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			bool val = (bool)(*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewBooleanObj(val));
		}
		($1)->release();
	}
}

%typemap(out) surfit::strvec * {
	Tcl_Obj * res_obj = Tcl_NewListObj(0,0);
	Tcl_SetObjResult(interp, res_obj);
	if ($1) {
		size_t i;
		for (i = 0; i < ($1)->size(); i++)
		{
			char * val = (*($1))(i);
			Tcl_ListObjAppendElement(interp, res_obj, Tcl_NewStringObj(val,-1));
		}
		($1)->release();
	}
}

%include "../../src/sstuff/real.h"

surfit::boolvec * flow_points(const char * points_name = "*");
surfit::boolvec * flow_area(REAL value, const char * area_name = "*");
surfit::boolvec * flow_curve(REAL value, const char * curve_name = "*");
surfit::boolvec * flow_contour(const char * contour_name = "*");

}; // namespace surfit;

%include "interface/lcm.i"

