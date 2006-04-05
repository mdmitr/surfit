
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

%include "../../src/sstuff/real.h"

////////////////////////////////
// Digital elevation model
////////////////////////////////

bool dem(const char * demname_or_position = "0");
bool dem_add(REAL weight, const char * demname_or_position = "0");


//saveload
bool dem_load(const char * filename, const char * demname = 0);
bool dem_load_grd(const char * filename, const char * demname = 0);
bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);
bool dem_load_hgt(const char * hgt_filename, const char * name = 0);
bool dem_load_hgt_zip(const char * hgt_filename, const char * name = 0);
bool dem_load_globe(const char * filename, const char * name = 0);
bool dem_save(const char * filename, const char * dem_name_or_position = "0");
bool dem_save_grd(const char * filename, const char * dem_name_or_position = "0");
bool dem_save_xyz(const char * filename, const char * dem_name_or_position = "0");
bool dem_save_dtm(const char * filename, const char * dem_name_or_position = "0");
// MATH OPERATIONS
REAL dem_getValue(REAL x, REAL y, const char * dem_name_or_position = "0");
bool dem_resid(const char * filename, const char * dem_name_or_position = "0", const char * points_name_or_position = "0");
REAL dem_D1(const char * dem_name_or_position = "0");
REAL dem_D2(const char * dem_name_or_position = "0");
bool dem_gradient(const char * newname, const char * dem_name_or_position = "0");
bool dem_project(const char * newname, const char * dem_name_or_position = "0");
REAL dem_minz(const char * dem_name_or_position = "0");
REAL dem_maxz(const char * dem_name_or_position = "0");
bool dem_plus(const char * dem1_name_or_position, const char * dem2_name_or_position);
bool dem_minus(const char * dem1_name_or_position, const char * dem2_name_or_position);
bool dem_mult(const char * dem1_name_or_position, const char * dem2_name_or_position);
bool dem_div(const char * dem1_name_or_position, const char * dem2_name_or_position);
bool dem_set(const char * dem1_name_or_position, const char * dem2_name_or_position);
bool dem_plus_real(REAL val, const char * dem_name_or_position = "0");
bool dem_minus_real(REAL val, const char * dem_name_or_position = "0");
bool dem_mult_real(REAL val, const char * dem_name_or_position = "0");
bool dem_div_real(REAL val, const char * dem_name_or_position = "0");
bool dem_set_real(REAL val, const char * dem_name_or_position = "0");
// WAVELETS SECTION
int dem_get_details_level(const char * dem_name_or_position = "0");
bool dem_decomp(const char * dem_name_or_position = "0");
bool dem_auto_decomp(REAL eps, const char * dem_name_or_position = "0");
bool dem_recons(const char * dem_name_or_position = "0");
bool dem_full_recons(const char * dem_name_or_position = "0");
// CONVERTING
bool dem_to_pnts(const char * dem_name_or_position = "0");
bool dem_to_surf(const char * dem_name_or_position = "0");
bool dem_to_mask(short true_from, short true_to, const char * dem_name_or_position = "0");
bool surf_to_dem(const char * surface_name_or_position = "0");
// OTHER
int dem_getCountX(const char * dem_name_or_position = "0");
int dem_getCountY(const char * dem_name_or_position = "0");
REAL dem_getStepX(const char * dem_name_or_position = "0");
REAL dem_getStepY(const char * dem_name_or_position = "0");
bool dem_undef(REAL new_undef_value, const char * dem_name_or_position = "0");
const char * dem_getName(const char * dem_name_or_position = "0");
bool dem_setName(const char * new_name, const char * dem_name_or_position = "0");
bool dem_delall();
bool dem_del(const char * dem_name_or_position = "0");
int dem_size();
void dems_info();


}; // namespace surfit


