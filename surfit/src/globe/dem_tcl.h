
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

#ifndef __surfit__dem_tcl__
#define __surfit__dem_tcl__

namespace surfit {

class datafile;
class vec;
class datafile;
class d_grid;
class dem;

//
// SAVE_LOAD
//

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load(const char * filename, const char * demname = 0);

    \par Tcl syntax:
    dem_load "filename" "demname"

    \par Description:
    loads \ref d_dem "DEM" named 'demname' from surfit datafile. If no demname specified,
    then loads the first one.
    
    \param filename surfit datafile
    \param demname name of DEM (optional)
*/
bool dem_load(const char * filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_grd(const char * filename, const char * demname = 0);

    \par Tcl syntax:
    dem_load_grd "filename" "demname"

    \par Description:
    loads \ref d_dem "DEM" from SURFER grd file (ASCII format)

    \param filename Surfer GRD-ASCII file
    \param demname name of DEM (optional)
*/
bool dem_load_grd(const char * filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);

    \par Tcl syntax:
    dem_load_dmt "hdr_filename" "demname" "bin_filename"

    \par Description:
    loads \ref d_dem "DEM" from DTM files (hdr + bin)
*/
bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_hgt(const char * hgt_filename, const char * demname);
    
    \par Tcl syntax:
    dem_load_hgt "hgt_filename" "demname"

    \par Description:
    loads \ref d_dem "DEM" from HGT files (Shuttle Radar Topographic Mission files)
*/
bool dem_load_hgt(const char * hgt_filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_hgt_zip(const char * hgt_filename, const char * demname);

    \par Tcl syntax:
    dem_load_hgt_zip(const char * hgt_filename, const char * demname);

    \par Description:
    loads \ref d_dem "DEM" from zipped HGT files (Shuttle Radar Topographic Mission files)
*/
bool dem_load_hgt_zip(const char * hgt_filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_globe(const char * filename, const char * demname = 0);
     
    \par Tcl syntax:
    dem_load_globe "filename"

    \par Description:
    loads \ref d_dem "DEM" from GTOPO30 files (The Global Land One-km Base Elevation (GLOBE) Project)
*/
bool dem_load_globe(const char * filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save(const char * filename, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_save "filename" "dem_name_or_position"

    \par Description:
    saves \ref d_dem "DEM" to surfit datafile
*/
bool dem_save(const char * filename, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_grd(const char * filename, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_save_grd "filename" "dem_name_or_position"

    \par Description:
    saves \ref d_dem "DEM" to SURFER grd file (ASCII format)
*/
bool dem_save_grd(const char * filename, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_xyz(const char * filename, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_save_xyz "filename" "dem_name_or_position"

    \par Description:
    saves \ref d_dem "DEM" to XYZ text format
*/
bool dem_save_xyz(const char * filename, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_dtm(const char * filename, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_save_dtm "filename" "dem_name_or_position"

    \par Description:
    saves \ref d_dem "DEM" to DTM files (hdr + bin)
*/
bool dem_save_dtm(const char * filename, const char * dem_name_or_position = "0");

//
// MATH OPERATIONS
//

/*! \ingroup tcl_dem_math
    \fn REAL dem_getValue(REAL x, REAL y, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_getValue x y "dem_name_or_position"

    \par Description:
    calculates \ref d_dem "DEM" value at (x,y) point
*/
REAL dem_getValue(REAL x, REAL y, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_resid(const char * filename, const char * dem_name_or_position = "0", const char * points_name_or_position = "0")

    \par Tcl syntax:
    dem_resid "filename" "dem_name_or_position" "points_name_or_position"

    \par Description:
    calculates residuals between \ref d_points "points" and \ref d_dem "DEM"
    Saves result to text file.
*/
bool dem_resid(const char * filename, const char * dem_name_or_position = "0", const char * points_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn REAL dem_D1(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_D1 "dem_name_or_position"

    \par Description:
    calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for \ref d_dem "DEM"
*/
REAL dem_D1(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn REAL dem_D2(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_D2 "dem_name_or_position"

    \par Description:
    calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for \ref d_dem "DEM"
*/
REAL dem_D2(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_gradient(const char * newname, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_gradient "newname" "dem_name_or_position"

    \par Description:
    calculates "DEM of gradients lengths" from \ref d_dem "DEM"
*/
bool dem_gradient(const char * newname, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_project(const char * newname, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_project "newname" "dem_name_or_position"

    \par Description:
    recalculates d_dem "DEM" on \ref d_grid using bilinear interpolation algorithm
*/
bool dem_project(const char * newname, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn REAL dem_minz(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_minz "dem_name_or_position"

    \par Description:
    calculates minimum Z-value for \ref d_dem "DEM"
*/
REAL dem_minz(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn REAL dem_maxz(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_maxz "dem_name_or_position"

    \par Description:
    calculates maximum Z-value for \ref d_dem "DEM"
*/
REAL dem_maxz(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_plus(const char * dem1_name_or_position, const char * dem2_name_or_position);

    \par Tcl syntax:
    dem_plus "dem1_name_or_position" "dem2_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 + dem2
*/
bool dem_plus(const char * dem1_name_or_position, const char * dem2_name_or_position);

/*! \ingroup tcl_dem_math
    \fn bool dem_minus(const char * dem1_name_or_position, const char * dem2_name_or_position);

    \par Tcl syntax:
    dem_minus "dem1_name_or_position" "dem2_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 - dem2
*/
bool dem_minus(const char * dem1_name_or_position, const char * dem2_name_or_position);

/*! \ingroup tcl_dem_math
    \fn bool dem_mult(const char * dem1_name_or_position, const char * dem2_name_or_position);

    \par Tcl syntax:
    dem_mult "dem1_name_or_position" "dem2_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 * dem2
*/
bool dem_mult(const char * dem1_name_or_position, const char * dem2_name_or_position);

/*! \ingroup tcl_dem_math
    \fn bool dem_div(const char * dem1_name_or_position, const char * dem2_name_or_position);

    \par Tcl syntax:
    dem_div "dem1_name_or_position" "dem2_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 / dem2
*/
bool dem_div(const char * dem1_name_or_position, const char * dem2_name_or_position);

/*! \ingroup tcl_dem_math
    \fn bool dem_set(const char * dem1_name_or_position, const char * dem2_name_or_position);

    \par Tcl syntax:
    dem_set "dem1_name_or_position" "dem2_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem2
*/
bool dem_set(const char * dem1_name_or_position, const char * dem2_name_or_position);

/*! \ingroup tcl_dem_math
    \fn bool dem_plus_real(REAL val, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_plus_real val "dem_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem + val
*/
bool dem_plus_real(REAL val, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_minus_real(REAL val, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_minus_real val "dem_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem - val
*/
bool dem_minus_real(REAL val, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_mult_real(REAL val, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_mult_real val "dem_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem * val
*/
bool dem_mult_real(REAL val, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_div_real(REAL val, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_div_real val "dem_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem / val
*/
bool dem_div_real(REAL val, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math
    \fn bool dem_set_real(REAL val, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_set_real val "dem_name_or_position"

    \par Description:
    Performs operation with DEMs cells values:
    dem = val
*/
bool dem_set_real(REAL val, const char * dem_name_or_position = "0");

//
// WAVELETS SECTION
//

/*! \ingroup tcl_dem_math_wavan
    \fn int dem_get_details_level(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_get_details_level "dem_name_or_position"

    \par Description:
    returns the depth of wavelet decomposition for dem
*/
int dem_get_details_level(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_decomp(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_decomp \ref regexp "dem_name_or_position"

    \par Description:
    makes one wavelet-decomposition for dem
*/
bool dem_decomp(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_auto_decomp(REAL eps, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_auto_decomp eps "dem_name_or_position"

    \par Description:
    calls \ref dem_decomp until difference between original DEM norm and decomposed DEM norm
    will be lower than eps
*/
bool dem_auto_decomp(REAL eps, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_recons(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_recons \ref regexp "dem_name_or_position"

    \par Description:
    makes one wavelet-reconstruction for dem
*/
bool dem_recons(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_full_recons(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_full_recons "dem_name_or_position"

    \par Description:
    makes all possible wavelet-reconstruction (recontructs original dem)
*/
bool dem_full_recons(const char * dem_name_or_position = "0");

//
// CONVERTING
//

/*! \ingroup tcl_dem_conv
    \fn bool dem_to_pnts(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_to_pnts "dem_name_or_position" "new_name"

    \par Description:
    transforms \ref d_dem "DEM" to \ref d_points "points"
*/
bool dem_to_pnts(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_conv
    \fn bool dem_to_surf(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_to_surf "dem_name_or_position"

    \par Description:
    makes \ref d_surf "surface" from \ref d_dem "DEM"
*/
bool dem_to_surf(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_conv
    \fn bool dem_to_mask(short true_from, short true_to, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_to_mask true_from true_to "dem_name_or_position"

    \par Description:
    makes \ref d_mask "mask" by \ref d_dem "DEM". Value will be true, if it lies in interval [true_from, true_to]
*/
bool dem_to_mask(short true_from, short true_to, const char * dem_name_or_position = "0");

//
// OTHER
//

/*! \ingroup tcl_dem_other
    \fn int dem_getCountX(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_getCountX "dem_name_or_position"

    \par Description:
    returns the number of X-nodes for \ref d_dem "DEM"
*/
int dem_getCountX(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_other
    \fn int dem_getCountY(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_getCountY "dem_name_or_position"

    \par Description:
    returns the number of Y-nodes for \ref d_dem "DEM"
*/
int dem_getCountY(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_other
    \fn REAL dem_getStepX(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_getStepX "dem_name_or_position"

    \par Description:
    returns step between X-nodes for \ref d_dem "DEM"
*/
REAL dem_getStepX(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_other
    \fn REAL dem_getStepY(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_getStepY "dem_name_or_position"

    \par Description:
    returns step between Y-nodes for \ref d_dem "DEM"
*/
REAL dem_getStepY(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_other
    \fn bool dem_undef(REAL new_undef_value, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_undef new_undef_value "dem_name_or_position"

    \par Description:
    sets new undefined value for \ref d_dem "DEM"
*/
bool dem_undef(REAL new_undef_value, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_other
    \fn const char * dem_getName(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_getName "dem_name_or_position"

    \par Description:
    returns name of \ref d_dem 
*/
const char * dem_getName(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dem_other
    \fn bool dem_setName(const char * new_name, const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_setName "new_name" "dem_name_or_position"

    \par Description:
    sets name of \ref d_dem "DEM"
*/
bool dem_setName(const char * new_name, const char * dem_name_or_position = "0");

/*! \ingroup tcl_dems
    \fn bool dem_delall();

    \par Tcl syntax:
    dem_delall

    \par Description:
    removes all \ref d_dem "DEMs" from memory
*/
bool dem_delall();

/*! \ingroup tcl_dems
    \fn bool dem_del(const char * dem_name_or_position = "0");

    \par Tcl syntax:
    dem_del "dem_name_or_position"

    \par Description:
    removes \ref d_dem "DEM" from memory
*/
bool dem_del(const char * dem_name_or_position = "0");

/*! \ingroup tcl_dems
    \fn int dem_size();

    \par Tcl syntax:
    dem_size

    \par Description:
    \returns number of \ref d_dem "DEMs" in memory
*/
int dem_size();

/*! \ingroup tcl_dems
    \fn void dems_info();

    \par Tcl syntax:
    dems_info

    \par Description:
    prints information about \ref d_dem "DEMs" in memory
*/
void dems_info();

}; // namespace surfit;

#endif

