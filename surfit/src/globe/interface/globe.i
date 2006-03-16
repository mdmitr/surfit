
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
#include "globe_func_tcl.h"
#include "variables_tcl.h"

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

//%include "../../surfit/src/real.h"

////////////////////////////////
// Digital elevation model
////////////////////////////////

bool dem(const char * pos = "-1");
bool dem_add(REAL weight, const char * pos = "-1");


//saveload
bool dem_load(const char * filename, const char * demname = 0);
bool dem_load_grd(const char * filename, const char * demname = 0);
bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);
bool dem_load_hgt(const char * hgt_filename, const char * name = 0);
bool dem_load_hgt_zip(const char * hgt_filename, const char * name = 0);
bool dem_load_globe(const char * filename, const char * name = 0);
bool dem_save(const char * filename, const char * pos = "0");
bool dem_save_grd(const char * filename, const char * pos = "0");
bool dem_save_xyz(const char * filename, const char * pos = "0");
bool dem_save_dtm(const char * filename, const char * pos = "0");
// MATH OPERATIONS
REAL dem_getValue(REAL x, REAL y, const char * pos = "0");
bool dem_resid(const char * filename, const char * dem_pos = "0", const char * pnts_pos = "0");
REAL dem_D1(const char * pos = "0");
REAL dem_D2(const char * pos = "0");
bool dem_gradient(const char * pos = "0");
bool dem_project(const char * pos = "0");
REAL dem_minz(const char * pos = "0");
REAL dem_maxz(const char * pos = "0");
bool dem_plus(const char * pos1, const char * pos2);
bool dem_minus(const char * pos1, const char * pos2);
bool dem_minus_undef(const char * pos1, const char * pos2);
bool dem_mult(const char * pos1, const char * pos2);
bool dem_div(const char * pos1, const char * pos2);
bool dem_set(const char * pos1, const char * pos2);
bool dem_plus_real(REAL val, const char * pos = "0");
bool dem_minus_real(REAL val, const char * pos = "0");
bool dem_mult_real(REAL val, const char * pos = "0");
bool dem_div_real(REAL val, const char * pos = "0");
bool dem_set_real(REAL val, const char * pos = "0");
// WAVELETS SECTION
int dem_get_details_level(const char * pos = "0");
bool dem_decomp(const char * pos = "0");
bool dem_auto_decomp(REAL eps, const char * pos = "0");
bool dem_recons(const char * pos = "0");
bool dem_full_recons(const char * pos = "0");
// CONVERTING
bool dem_to_points(const char * pos = "0", const char * new_name = NULL);
bool dem_to_func(const char * pos = "0", const char * new_name = NULL);
bool dem_to_mask(short true_from, short true_to, const char * pos = "0");
bool func_to_dem(const char * func_pos = "0");
// OTHER
int dem_getCountX(const char * pos = "0");
int dem_getCountY(const char * pos = "0");
REAL dem_getStepX(const char * pos = "0");
REAL dem_getStepY(const char * pos = "0");
bool dem_undef(REAL new_undef_value, const char * pos = "0");
const char * dem_getName(const char * pos = "0");
bool dem_setName(const char * new_name, const char * pos = "0");
bool dem_delall();
bool dem_del(const char * pos = "0");
int dem_size();
void dems_info();


}; // namespace surfit

//%include "interface/globe_draw.i"

