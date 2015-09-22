
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
/* File : globe.i */

%module globe
%{
#include "globe_ie.h"
#include "globe.h"
#include "globe_variables.h"
#include "dem_tcl.h"
#include "globe_surf_tcl.h"
#include "variables_tcl.h"
#include "boolvec.h"
#include "strvec.h"
#include "intvec.h"

#include "dems_tcl.h"
%}

%init 
%{
surfit::globe_init_variables(interp);
%}

namespace surfit {

class dem; 

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

////////////////////////////////
// Digital elevation model
////////////////////////////////

surfit::boolvec * dem(const char * demname = "*");
surfit::boolvec * dem_add(REAL weight, const char * demname = "*");
//
//saveload
surfit::boolvec * dem_load(const char * filename, const char * demname = 0);
surfit::boolvec * dem_load_grd(const char * filename, const char * demname = 0);
surfit::boolvec * dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);
surfit::boolvec * dem_load_hgt(const char * hgt_filename, const char * name = 0);
surfit::boolvec * dem_load_hgt_zip(const char * hgt_filename, const char * name = 0);
surfit::boolvec * dem_load_globe(const char * filename, const char * name = 0);
surfit::boolvec * dem_save(const char * filename, const char * dem_name = "*");
surfit::boolvec * dem_save_grd(const char * filename, const char * dem_name = "*");
surfit::boolvec * dem_save_xyz(const char * filename, const char * dem_name = "*");
surfit::boolvec * dem_save_dtm(const char * filename, const char * dem_name = "*");
//
// math operations
surfit::vec * dem_getValue(REAL x, REAL y, const char * dem_name = "*");
surfit::vec * dem_D1(const char * dem_name = "*");
surfit::vec * dem_D2(const char * dem_name = "*");
surfit::vec * dem_minz(const char * dem_name = "*");
surfit::vec * dem_maxz(const char * dem_name = "*");
surfit::boolvec * dem_resid(const char * filename, const char * dem_name = "*", const char * points_name = "*");
surfit::boolvec * dem_gradient(const char * newname, const char * dem_name = "*");
surfit::boolvec * dem_project(const char * newname, const char * dem_name = "*");
surfit::boolvec * dem_plus(const char * dem1_name, const char * dem2_name);
surfit::boolvec * dem_minus(const char * dem1_name, const char * dem2_name);
surfit::boolvec * dem_mult(const char * dem1_name, const char * dem2_name);
surfit::boolvec * dem_div(const char * dem1_name, const char * dem2_name);
surfit::boolvec * dem_set(const char * dem1_name, const char * dem2_name);
surfit::boolvec * dem_plus_real(REAL val, const char * dem_name = "*");
surfit::boolvec * dem_minus_real(REAL val, const char * dem_name = "*");
surfit::boolvec * dem_mult_real(REAL val, const char * dem_name = "*");
surfit::boolvec * dem_div_real(REAL val, const char * dem_name = "*");
surfit::boolvec * dem_set_real(REAL val, const char * dem_name = "*");
//
// wavelets section
surfit::intvec * dem_get_details_level(const char * dem_name = "*");
surfit::boolvec * dem_decomp(const char * dem_name = "*");
surfit::boolvec * dem_auto_decomp(REAL eps, const char * dem_name = "*");
surfit::boolvec * dem_recons(const char * dem_name = "*");
surfit::boolvec * dem_full_recons(const char * dem_name = "*");
//
// converting
surfit::boolvec * dem_to_pnts(const char * dem_name = "*");
surfit::boolvec * dem_to_surf(const char * dem_name = "*");
surfit::boolvec * dem_to_mask(short true_from, short true_to, const char * dem_name = "*");
surfit::boolvec * surf_to_dem(const char * surface_name = "*");
//
// other
surfit::intvec * dem_getCountX(const char * dem_name = "*");
surfit::intvec * dem_getCountY(const char * dem_name = "*");
surfit::vec * dem_getStepX(const char * dem_name = "*");
surfit::vec * dem_getStepY(const char * dem_name = "*");
surfit::boolvec * dem_undef(REAL new_undef_value, const char * dem_name = "*");
surfit::strvec * dem_getName(const char * dem_name = "*");
const char * dem_getNameAt(int pos);
surfit::intvec * dem_getId(const char * dem_name = "*");
surfit::boolvec * dem_setName(const char * new_name, const char * dem_name = "*");
void dem_del(const char * dem_name = "*");
int dem_size();
void dems_info();

}; // namespace surfit


