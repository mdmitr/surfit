
/*------------------------------------------------------------------------------
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky 
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
/* File : surfit_io.i */

%module surfit_io
%{
#include "surfit_io_ie.h"
#include "surfit_io.h"
#include "surfit_io_variables.h"
#include "boolvec.h"

#include "pnts_io_tcl.h"
#include "curv_io_tcl.h"
#include "area_io_tcl.h"
#include "cntr_io_tcl.h"
#include "surf_io_tcl.h"
#include "mask_io_tcl.h"

#include "variables_tcl.h"
%}

%init 
%{
surfit::surfit_io_init_variables(interp);
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

surfit::boolvec * pnts_load_shp(const char * filename, const char * pntsname=NULL, const char * param = "VALUE");
surfit::boolvec * pnts_save_shp(const char * filename, const char * points_name = "*");

surfit::boolvec * curv_load_bln(const char * filename, const char * curvname = NULL);
surfit::boolvec * curv_load_shp(const char * filename, const char * curvname = NULL);
surfit::boolvec * curv_save_bln(const char * filename, const char * curv_name = "*");
surfit::boolvec * curv_save_shp(const char * filename, const char * curv_name = "*");

surfit::boolvec * area_load_bln(const char * filename, const char * areaname = NULL);
surfit::boolvec * area_load_shp(const char * filename, const char * areaname = NULL);
surfit::boolvec * area_save_bln(const char * filename, const char * area_name = "*");
surfit::boolvec * area_save_shp(const char * filename, const char * area_name = "*");

surfit::boolvec * cntr_load_bln(const char * filename, const char * cntrname = NULL);
surfit::boolvec * cntr_load_shp(const char * filename, const char * cntrname = NULL, const char * zfield = NULL);
surfit::boolvec * cntr_save_shp(const char * filename, const char * cntr_name = "*");
surfit::boolvec * cntr_save_bln(const char * filename, const char * cntr_name = "*");

surfit::boolvec * surf_load_grd(const char * filename, const char * surfname = 0);
surfit::boolvec * surf_load_gmt(const char * filename, const char * surfname = 0);
surfit::boolvec * surf_load_grass(const char * filename, const char * surfname = 0);
surfit::boolvec * surf_load_arcgis(const char * filename, const char * surfname = 0);
surfit::boolvec * surf_load_xyz(const char * filename, const char * surfname = 0, bool force = false);
surfit::boolvec * surf_load_jpg(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);
surfit::boolvec * surf_load_bmp(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);

surfit::boolvec * surf_save_grd(const char * filename, const char * surface_name = "*", int format = 0);
surfit::boolvec * surf_save_gmt(const char * filename, const char * surface_name = "*");
surfit::boolvec * surf_save_grass(const char * filename, const char * surface_name = "*");
surfit::boolvec * surf_save_arcgis(const char * filename, const char * surface_name = "*");
surfit::boolvec * surf_save_xyz(const char * filename, const char * surface_name = "*");
surfit::boolvec * surf_save_jpg(const char * filename, const char * surface_name = "*", int quality = 255);
surfit::boolvec * surf_save_bmp(const char * filename, const char * surface_name = "*");

surfit::boolvec * mask_save_grd(const char * filename, const char * mask_name = "*");
surfit::boolvec * mask_save_xyz(const char * filename, const char * mask_name = "*");

}; // namespace surfit


