
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

#include "pnts_io_tcl.h"
#include "curv_io_tcl.h"
#include "area_io_tcl.h"
#include "cntr_io_tcl.h"
#include "surf_io_tcl.h"

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

%include "../../src/sstuff/real.h"

bool pnts_load_shp(const char * filename, const char * pntsname=NULL, const char * param = "VALUE");
bool pnts_save_shp(const char * filename, const char * points_name_or_position = "0");

bool curv_load_bln(const char * filename);
bool curv_load_shp(const char * filename, const char * curvname = NULL);
bool curvs_load_shp(const char * filename);
bool curv_save_bln(const char * filename, const char * curv_name_or_position = "0", int orient = 1);
bool curv_save_shp(const char * filename, const char * curv_name_or_position = "0");

bool area_load_bln(const char * filename, const char * areaname = NULL);
bool area_load_shp(const char * filename, const char * areaname = NULL);
bool areas_load_shp(const char * filename);
bool area_save_bln(const char * filename, const char * area_name_or_position = "0", int orient = 1);
bool area_save_shp(const char * filename, const char * area_name_or_position = "0");

bool cntr_load_shp(const char * filename, const char * cntrname = NULL);
bool cntrs_load_shp(const char * filename);
bool cntr_save_shp(const char * filename, const char * cntr_name_or_position = "0");

bool surf_load_grd(const char * filename, const char * surfname = 0);
bool surf_load_gmt(const char * filename, const char * surfname = 0);
bool surf_load_grass(const char * filename, const char * surfname = 0);
bool surf_load_arcgis(const char * filename, const char * surfname = 0);
bool surf_load_xyz(const char * filename, const char * surfname = 0);
bool surf_load_jpg(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);
bool surf_load_bmp(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);


bool surf_save_grd(const char * filename, const char * surface_name_or_position = "0");
bool surf_save_gmt(const char * filename, const char * surface_name_or_position = "0");
bool surf_save_grass(const char * filename, const char * surface_name_or_position = "0");
bool surf_save_arcgis(const char * filename, const char * surface_name_or_position = "0");
bool surf_save_xyz(const char * filename, const char * surface_name_or_position = "0");
bool surf_save_jpg(const char * filename, const char * surface_name_or_position = "0", int quality = 255);
bool surf_save_bmp(const char * filename, const char * surface_name_or_position = "0");

}; // namespace surfit


