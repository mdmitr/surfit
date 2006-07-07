
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

#ifndef __surfit__surf_tcl__
#define __surfit__surf_tcl__

namespace surfit {

class datafile;
class vec;
class datafile;
class d_grid;
class d_surf;

//
// saveload
//

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load(const char * filename, const char * surfname = 0);

    \par Tcl syntax:
    surf_load "filename" "surfname"
    
    \par Description:
    loads surface named "surfname" from surfit datafile. If no surfname specified, then loads first one.

    \param filename surfit datafile
    \param surfname name for surface (optional)
*/
bool surf_load(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_grd(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_grd "filename" "surfname"

    \par Description:
    loads surface from SURFER grd file (ASCII format)

    \param filename Surfer grd file (ASCII format)
    \param surfname name for surface (optional)
*/
bool surf_load_grd(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_gmt(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_gmt "filename" "surfname"

    \par Description:
    loads surface from Generic Mapping Tools grd file (CDF format)
*/
bool surf_load_gmt(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_grass(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_grass "filename" "surfname"

    \par Description:
    loads surface from GRASS ASCII file
*/
bool surf_load_grass(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_arcgis(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_arcgis "filename" "surfname"

    \par Description:
    loads surface from ArcGIS ASCII file
*/
bool surf_load_arcgis(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_jpg(const char * filename, const char * surfname = 0,
			   REAL minz = 0, REAL maxz = 0, 
			   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1)

    \par Tcl syntax:
    surf_load_jpg "filename" "surfname"

    \par Description:
    loads surface from JPEG file
*/
bool surf_load_jpg(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_bmp(const char * filename, const char * surfname = 0,
			   REAL minz = 0, REAL maxz = 0, 
			   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1)

    \par Tcl syntax:
    surf_load_bmp "filename" "surfname" 

    \par Description:
    loads surface from Windows bitmap file
*/
bool surf_load_bmp(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save "filename" "surface_name_or_position" 

    \par Description:
    saves surface to surfit datafile

    \param filename surfit datafile
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
*/
bool surf_save(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_grd(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_grd "filename" "surface_name_or_position"

    \par Description:
    saves surface to SURFER grd file (ASCII format)

    \param filename SURFER grd file (ASCII format)
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
*/
bool surf_save_grd(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_gmt(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_gmt "filename" "surface_name_or_position"

    \par Description:
    saves surface to Generic Mapping Tools grd file (CDF format)
*/
bool surf_save_gmt(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_grass(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_grass "filename" "surface_name_or_position"

    \par Description:
    saves surface to GRASS ASCII file
*/
bool surf_save_grass(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_arcgis(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_arcgis "filename" "surface_name_or_position"

    \par Description:
    saves surface to ArcGIS ASCII file
*/
bool surf_save_arcgis(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_xyz(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_xyz "filename" "surface_name_or_position"

    \par Description:
    saves surface to XYZ text format

    \param filename XYZ text file
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
*/
bool surf_save_xyz(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_jpg(const char * filename, const char * surface_name_or_position = "0", int quality = 255);

    \par Tcl syntax:
    surf_save_jpg "filename" "surface_name_or_position"

    \par Description:
    saves surface to JPEG in grayscale colours

    \param filename jpeg file
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
    \param quality jpeg quality 0..255
*/
bool surf_save_jpg(const char * filename, const char * surface_name_or_position = "0", int quality = 255);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_bmp(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_bmp "filename" "surface_name_or_position"

    \par Description:
    saves surface to Windows BitMap file in grayscale colours

    \param filename bitmap file
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
*/
bool surf_save_bmp(const char * filename, const char * surface_name_or_position = "0");

//
// MATH OPERATIONS
//

/*! \ingroup tcl_surf_math
    \fn REAL surf_getValue(REAL x, REAL y, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_getValue x y "surface_name_or_position"

    \par Description:
    calculates surface value at point (x,y)

    \param x point x-coordinate
    \param y point y-coordinate 
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
*/
REAL surf_getValue(REAL x, REAL y, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_getValueIJ(int I, int J, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_getValueIJ I J "surface_name_or_position"

    \par Description:
    returns surface value at node (I,J)

    \param I node number in X direction
    \param J node number in Y direction
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
*/
REAL surf_getValueIJ(int I, int J, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_resid(const char * filename, const char * surface_name_or_position = "0", const char * points_name_or_position = "0")

    \par Tcl syntax:
    surf_resid "filename" "surface_name_or_position" "points_name_or_position"

    \par Description:
    calculates residuals between \ref d_points "points" values and \ref d_surf "surface" values, calculated at points (x,y) coordinates.
    Saves result to text file.

    \param filename text file with residuals
    \param points_name_or_position name of \ref d_points "points" dataset, or points position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_resid(const char * filename, const char * surface_name_or_position = "0", const char * points_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_D1(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_D1 "surface_name_or_position"

    \par Description:
    calculates value of \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for surface, where f is a surface.

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_D1(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_D2(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_D2 "surface_name_or_position"

    \par Description:
    calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for surface, where f is a surface.

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_D2(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_gradient(const char * newname, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_gradient "newname" "surface_name_or_position"

    \par Description:
    calculates surface of "gradients lengths" for surface and saves result to new surface named "newname"

    \param newname name for resulting surface
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_gradient(const char * newname, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_project(const char * newname, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_project "newname" "surface_name_or_position"

    \par Description:
    recalculates surface on current \ref d_grid "grid" using bilinear interpolation algorithm

    \param newname name for resulting surface
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_project(const char * newname, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_add_noise(REAL std, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_add_noise std "surface_name_or_position"

    \par Description:
    adds normally-distributed noise with parameters N(0,std) to coeff

    \param std standart deviation
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_add_noise(REAL std, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_minz(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_minz "surface_name_or_position"

    \par Description:
    returns minimum value for surface

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_minz(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_area_minz(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
	
    \par Tcl syntax:
    surf_area_minz "area_name_or_position" "surface_name_or_position"

    \par Description:
    returns minimum value for surface in area

    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_area_minz(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_maxz(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_maxz "surface_name_or_position"
     
    \par Description:
    returns maximum value for surface

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_maxz(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_area_maxz(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
	
    \par Tcl syntax:
    surf_area_maxz "area_name_or_position" "surface_name_or_position"

    \par Description:
    returns maximum value for surface in area

    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_area_maxz(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_mean(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_mean "surface_name_or_position"

    \par Description:
    returns mean value for surface

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_mean(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_area_mean(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_area_mean "area_name_or_position" "surface_name_or_position"

    \par Description:
    returns mean value for surface in area

    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_area_mean(const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_wmean(const char * wsurface_name_or_position = "0", const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_wmean "wsurface_name_or_position" "surface_name_or_position"

    \par Description:
    returns weighted mean value for surface

    \param wsurface_name_or_position name of weighting \ref d_surf "surface" dataset, or surface position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_wmean(const char * wsurface_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_area_wmean(const char * area_name_or_position = "0", const char * wsurface_name_or_position = "0", const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_area_wmean "area_name_or_position" "wsurface_name_or_position" "surface_name_or_position"

    \par Description:
    returns weighted mean value for surface in area

    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
    \param wsurface_name_or_position name of weighting \ref d_surf "surface" dataset, or surface position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_area_wmean(const char * area_name_or_position = "0", const char * wsurface_name_or_position = "0", const char * surface_name_or_position = "0");


/*! \ingroup tcl_surf_math
    \fn REAL surf_sum(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_sum "surface_name_or_position"

    \par Description:
    returns sum of all surface cell values

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_sum(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_sum_area(const char * area_name_or_position = "0",  const char * surface_name_or_position = "0");
     
    \par Tcl syntax:
    surf_sum_area "area_name_or_position" "surface_name_or_position"

    \par Description:
    returns sum of all surface cells values in area

    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_sum_area(const char * area_name_or_position = "0",  const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn int surf_cells_in_area(const char * area_name_or_position = "0",  const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_cells_in_area "area_name_or_position" "surface_name_or_position"

    \par Description:
    returns number of cells in area

    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
int surf_cells_in_area(const char * area_name_or_position = "0",  const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn REAL surf_std(REAL mean, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_std mean "surface_name_or_position"

    \par Description:
    calculates standard deviation for surface cells values with respect to surface mean value

    \param mean surface mean value
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
REAL surf_std(REAL mean, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_plus(const char * surface1_name_or_position, const char * surface2_name_or_position);

    \par Tcl syntax:
    surf_plus "surface1_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 + surface2
*/
bool surf_plus(const char * surface1_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    bool surf_plus_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
   
    \par Tcl syntax:
    surf_plus_area "surface1_name_or_position" "area_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 + surface2
*/
bool surf_plus_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_minus(const char * surface1_name_or_position, const char * surface2_name_or_position);

    \par Tcl syntax:
    surf_minus "surface1_name_or_position" "surface2_name_or_position"
    
    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 - surface2
*/
bool surf_minus(const char * surface1_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_minus_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);

    \par Tcl syntax:
    surf_minus_area "surface1_name_or_position" "area_name_or_position" "surface2_name_or_position"
    
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 - surface2
*/
bool surf_minus_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_mult(const char * surface1_name_or_position, const char * surface2_name_or_position);

    \par Tcl syntax:
    surf_mult "surface1_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 * surface2
*/
bool surf_mult(const char * surface1_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_mult_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
    
    \par Tcl syntax:
    surf_mult_area "surface1_name_or_position" "area_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 * surface2
*/
bool surf_mult_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_div(const char * surface1_name_or_position, const char * surface2_name_or_position);
    
    \par Tcl syntax:
    surf_mult "surface1_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 / surface2
*/
bool surf_div(const char * surface1_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_div_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
    
    \par Tcl syntax:
    surf_div_area "surface1_name_or_position" "area_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 / surface2
*/
bool surf_div_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_set(const char * surface1_name_or_position, const char * surface2_name_or_position);
    
    \par Tcl syntax:
    surf_set "surface1_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface2
*/
bool surf_set(const char * surface1_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_set_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);
    
    \par Tcl syntax:
    surf_set_area "surface1_name_or_position" "area_name_or_position" "surface2_name_or_position"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface2
*/
bool surf_set_area(const char * surface1_name_or_position, const char * area_name_or_position, const char * surface2_name_or_position);

/*! \ingroup tcl_surf_math
    \fn bool surf_plus_value(REAL val, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_plus_value val "surface_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface + val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_plus_value(REAL val, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_plus_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_plus_value_area val "area_name_or_position" "surface_name_or_position"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface + val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
*/
bool surf_plus_value_area(REAL val, const char * surface_name_or_position = "0", const char * area_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_minus_value(REAL val, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_minus_value val "surface_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface - val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_minus_value(REAL val, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_minus_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_minus_value_area val "area_name_or_position" "surface_name_or_position"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface - val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
*/
bool surf_minus_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_mult_value(REAL val, const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_mult_value val "surface_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface * val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_mult_value(REAL val, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_mult_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_mult_value_area val "area_name_or_position" "surface_name_or_position"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface * val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
*/
bool surf_mult_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_div_value(REAL val, const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_div_value val "surface_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface / val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_div_value(REAL val, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_div_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_div_value_area val "area_name_or_position" "surface_name_or_position"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface / val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
*/
bool surf_div_value_area(REAL val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_set_value(REAL val, const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_set_value val "surface_name_or_position"

    \par Description:
    Performs operation with surfaces cells values:
    surface = val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_set_value(REAL val, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math
    \fn bool surf_set_value_area(const char * val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_set_value_area val "area_name_or_position" "surface_name_or_position"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = val

    \param val real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number
*/
bool surf_set_value_area(const char * val, const char * area_name_or_position = "0", const char * surface_name_or_position = "0");

//
// WAVELETS SECTION
//

/*! \ingroup tcl_surf_math_wavan
    \fn int surf_get_details_level(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_get_details_level "surface_name_or_position"

    \par Description:
    returns the depth of applied wavelet decompositions for surface

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
int surf_get_details_level(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math_wavan
    \fn bool surf_decomp(const char * surface_name_or_position = "0");

    \par Tcl syntax: 
    surf_decomp "surface_name_or_position"

    \par Description:
    makes one wavelet-decomposition for surface 

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_decomp(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math_wavan
    \fn bool surf_auto_decomp(REAL eps, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_auto_decomp eps "surface_name_or_position"

    \par Description:
    calls \ref surf_decomp until difference between original surface norm and decomposed surface norm
    will be lower than eps

    \param eps real number
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_auto_decomp(REAL eps, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math_wavan
    \fn bool surf_recons(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_recons "surface_name_or_position"

    \par Description:
    makes one wavelet-reconstruction for surface 

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_recons(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_math_wavan
    \fn bool surf_full_recons(const char * surface_name_or_position = "0");

    \par Tcl syntax: 
    surf_full_recons "surface_name_or_position"

    \par Description:
    makes all possible wavelet-reconstructions for surface (recontructs original surface)

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_full_recons(const char * surface_name_or_position = "0");

//
// CONVERTING
//

/*! \ingroup tcl_surf_conv
    \fn bool surf_to_pnts(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_to_pnts "surface_name_or_position"

    \par Description:
    transforms \ref d_surf "surface" to \ref d_points "points"

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
*/
bool surf_to_pnts(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_conv
    \fn bool surf_to_mask(REAL true_from, REAL true_to, const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_to_mask true_from true_to "surface_name_or_position"
      
    \par Description:
    makes \ref d_mask "mask" by surface. Cells values will be converted to "true" values if their
    values are in interval [true_from, true_to], else to "false" values.
*/
bool surf_to_mask(REAL true_from, REAL true_to, const char * surface_name_or_position = "0");

//
// OTHER
//

/*! \ingroup tcl_surf_other
    \fn int surf_getCountX(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_getCountX "surface_name_or_position"

    \par Description:
    returns the amount of X-nodes for surface
*/
int surf_getCountX(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn int surf_getCountY(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_getCountY "surface_name_or_position"

    \par Description:
    returns the amount of Y-nodes for surface
*/
int surf_getCountY(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn REAL surf_getStepX(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_getStepX "surface_name_or_position"
    
    \par Description:
    returns step between X-nodes for surface
*/
REAL surf_getStepX(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn REAL surf_getStepY(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_getStepY "surface_name_or_position"
    
    \par Description:
    returns step between Y-nodes for surface
*/
REAL surf_getStepY(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn bool surf_undef(REAL new_undef_value, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_undef new_undef_value "surface_name_or_position"
    
    \par Description:
    sets undefined value for surface
*/
bool surf_undef(REAL new_undef_value, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn void surf_info(const char * surface_name_or_position = "0");
     
    \par Tcl syntax:
    surf_info "surface_name_or_position"
    
    \par Description:
    prints some info about surface
*/
void surf_info(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn const char * surf_getName(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_getName "surface_name_or_position"
    
    \par Description:
    returns name of surface 
*/
const char * surf_getName(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn bool surf_setName(const char * new_name, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_setName "new_name" "surface_name_or_position"
    
    \par Description:
    sets name for surface
*/
bool surf_setName(const char * new_name, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn int surf_size();

    \par Tcl syntax:
    
    \par Description:
    returns amount of surfaces in surfaces
*/
int surf_size();

/*! \ingroup tcl_surf_other
    \fn void surfs_info();

    \par Tcl syntax:
    
    \par Description:
    prints information about surfaces in surfaces
*/
void surfs_info();

/*! \ingroup tcl_surf_other
    \fn bool surf_del(const char * surface_name_or_position = "0");
    
    \par Tcl syntax:
    surf_del "surface_name_or_position"

    \par Description:
    removes \ref d_surf "surface" from memory
*/
bool surf_del(const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_other
    \fn bool surf_delall();
 
    \par Tcl syntax:
    surf_delall

    \par Description:
    removes all \ref d_surf "surfaces" from memory
*/
bool surf_delall();

}; // namespace surfit;

#endif

