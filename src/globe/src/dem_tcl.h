
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
class boolvec;
class strvec;
class intvec;

//
// SAVE_LOAD
//

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load(const char * filename, const char * demname = 0);

    \par Tcl syntax:
    dem_load \ref file "filename" "demname"

    \par Description:
    loads \ref d_dem "DEM" named 'demname' from surfit datafile. If no demname specified,
    then loads the first one.
    
    \param filename surfit datafile
    \param demname name of DEM (optional)
*/
boolvec * dem_load(const char * filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_grd(const char * filename, const char * demname = 0);

    \par Tcl syntax:
    dem_load_grd \ref file "filename" "demname"

    \par Description:
    loads \ref d_dem "DEM" from SURFER grd file (ASCII format)

    \param filename Surfer GRD-ASCII file
    \param demname name of DEM (optional)
*/
boolvec * dem_load_grd(const char * filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);

    \par Tcl syntax:
    dem_load_dmt \ref file "hdr_filename" "demname" "bin_filename"

    \par Description:
    loads \ref d_dem "DEM" from DTM files (hdr + bin)
*/
boolvec * dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_hgt(const char * hgt_filename, const char * demname);
    
    \par Tcl syntax:
    dem_load_hgt \ref file "hgt_filename" "demname"

    \par Description:
    loads \ref d_dem "DEM" from HGT files (Shuttle Radar Topographic Mission files)
*/
boolvec * dem_load_hgt(const char * hgt_filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_hgt_zip(const char * hgt_filename, const char * demname);

    \par Tcl syntax:
    dem_load_hgt_zip \ref file "hgt_filename" "demname"

    \par Description:
    loads \ref d_dem "DEM" from zipped HGT files (Shuttle Radar Topographic Mission files)
*/
boolvec * dem_load_hgt_zip(const char * hgt_filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_globe(const char * filename, const char * demname = 0);
     
    \par Tcl syntax:
    dem_load_globe \ref file "filename"

    \par Description:
    loads \ref d_dem "DEM" from GTOPO30 files (The Global Land One-km Base Elevation (GLOBE) Project)
*/
boolvec * dem_load_globe(const char * filename, const char * demname = 0);

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save(const char * filename, const char * dem_name = "*");

    \par Tcl syntax:
    dem_save "filename" \ref str "dem_name"

    \par Description:
    saves \ref d_dem "DEM" to surfit datafile
*/
boolvec * dem_save(const char * filename, const char * dem_name = "*");

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_grd(const char * filename, const char * dem_name = "*");

    \par Tcl syntax:
    dem_save_grd "filename" \ref str "dem_name"

    \par Description:
    saves \ref d_dem "DEM" to SURFER grd file (ASCII format)
*/
boolvec * dem_save_grd(const char * filename, const char * dem_name = "*");

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_xyz(const char * filename, const char * dem_name = "*");

    \par Tcl syntax:
    dem_save_xyz "filename" \ref str "dem_name"

    \par Description:
    saves \ref d_dem "DEM" to XYZ text format
*/
boolvec * dem_save_xyz(const char * filename, const char * dem_name = "*");

/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_dtm(const char * filename, const char * dem_name = "*");

    \par Tcl syntax:
    dem_save_dtm "filename" \ref str "dem_name"

    \par Description:
    saves \ref d_dem "DEM" to DTM files (hdr + bin)
*/
boolvec * dem_save_dtm(const char * filename, const char * dem_name = "*");

//
// MATH OPERATIONS
//

/*! \ingroup tcl_dem_math
    \fn REAL dem_getValue(REAL x, REAL y, const char * dem_name = "*");

    \par Tcl syntax:
    dem_getValue x y \ref str "dem_name"

    \par Description:
    calculates \ref d_dem "DEM" value at (x,y) point
*/
vec * dem_getValue(REAL x, REAL y, const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_resid(const char * filename, const char * dem_name = "*", const char * points_name = "*")

    \par Tcl syntax:
    dem_resid "filename" \ref str "dem_name" \ref str "points_name"

    \par Description:
    calculates residuals between \ref d_points "points" and \ref d_dem "DEM"
    Saves result to text file.
*/
boolvec * dem_resid(const char * filename, const char * dem_name = "*", const char * points_name = "*");

/*! \ingroup tcl_dem_math
    \fn REAL dem_D1(const char * dem_name = "*");

    \par Tcl syntax:
    dem_D1 \ref str "dem_name"

    \par Description:
    calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for \ref d_dem "DEM"
*/
vec * dem_D1(const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn REAL dem_D2(const char * dem_name = "*");

    \par Tcl syntax:
    dem_D2 \ref str "dem_name"

    \par Description:
    calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for \ref d_dem "DEM"
*/
vec * dem_D2(const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_gradient(const char * newname, const char * dem_name = "*");

    \par Tcl syntax:
    dem_gradient "newname" \ref str "dem_name"

    \par Description:
    calculates "DEM of gradients lengths" from \ref d_dem "DEM"
*/
boolvec * dem_gradient(const char * newname, const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_project(const char * newname, const char * dem_name = "*");

    \par Tcl syntax:
    dem_project "newname" \ref str "dem_name"

    \par Description:
    recalculates d_dem "DEM" on \ref d_grid using bilinear interpolation algorithm
*/
boolvec * dem_project(const char * newname, const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn REAL dem_minz(const char * dem_name = "*");

    \par Tcl syntax:
    dem_minz \ref str "dem_name"

    \par Description:
    calculates minimum Z-value for \ref d_dem "DEM"
*/
vec * dem_minz(const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn REAL dem_maxz(const char * dem_name = "*");

    \par Tcl syntax:
    dem_maxz \ref str "dem_name"

    \par Description:
    calculates maximum Z-value for \ref d_dem "DEM"
*/
vec * dem_maxz(const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_plus(const char * dem1_name, const char * dem2_name);

    \par Tcl syntax:
    dem_plus \ref str "dem1_name" \ref str "dem2_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 + dem2
*/
boolvec * dem_plus(const char * dem1_name, const char * dem2_name);

/*! \ingroup tcl_dem_math
    \fn bool dem_minus(const char * dem1_name, const char * dem2_name);

    \par Tcl syntax:
    dem_minus \ref str "dem1_name" \ref str "dem2_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 - dem2
*/
boolvec * dem_minus(const char * dem1_name, const char * dem2_name);

/*! \ingroup tcl_dem_math
    \fn bool dem_mult(const char * dem1_name, const char * dem2_name);

    \par Tcl syntax:
    dem_mult \ref str "dem1_name" \ref str "dem2_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 * dem2
*/
boolvec * dem_mult(const char * dem1_name, const char * dem2_name);

/*! \ingroup tcl_dem_math
    \fn bool dem_div(const char * dem1_name, const char * dem2_name);

    \par Tcl syntax:
    dem_div \ref str "dem1_name" \ref str "dem2_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem1 / dem2
*/
boolvec * dem_div(const char * dem1_name, const char * dem2_name);

/*! \ingroup tcl_dem_math
    \fn bool dem_set(const char * dem1_name, const char * dem2_name);

    \par Tcl syntax:
    dem_set \ref str "dem1_name" \ref str "dem2_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem1 = dem2
*/
boolvec * dem_set(const char * dem1_name, const char * dem2_name);

/*! \ingroup tcl_dem_math
    \fn bool dem_plus_real(REAL val, const char * dem_name = "*");

    \par Tcl syntax:
    dem_plus_real val \ref str "dem_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem + val
*/
boolvec * dem_plus_real(REAL val, const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_minus_real(REAL val, const char * dem_name = "*");

    \par Tcl syntax:
    dem_minus_real val \ref str "dem_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem - val
*/
boolvec * dem_minus_real(REAL val, const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_mult_real(REAL val, const char * dem_name = "*");

    \par Tcl syntax:
    dem_mult_real val \ref str "dem_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem * val
*/
boolvec * dem_mult_real(REAL val, const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_div_real(REAL val, const char * dem_name = "*");

    \par Tcl syntax:
    dem_div_real val \ref str "dem_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem = dem / val
*/
boolvec * dem_div_real(REAL val, const char * dem_name = "*");

/*! \ingroup tcl_dem_math
    \fn bool dem_set_real(REAL val, const char * dem_name = "*");

    \par Tcl syntax:
    dem_set_real val \ref str "dem_name"

    \par Description:
    Performs operation with DEMs cells values:
    dem = val
*/
boolvec * dem_set_real(REAL val, const char * dem_name = "*");

//
// WAVELETS SECTION
//

/*! \ingroup tcl_dem_math_wavan
    \fn int dem_get_details_level(const char * dem_name = "*");

    \par Tcl syntax:
    dem_get_details_level \ref str "dem_name"

    \par Description:
    returns the depth of wavelet decomposition for dem
*/
intvec * dem_get_details_level(const char * dem_name = "*");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_decomp(const char * dem_name = "*");

    \par Tcl syntax:
    dem_decomp \ref str "dem_name"

    \par Description:
    makes one wavelet-decomposition for dem
*/
boolvec * dem_decomp(const char * dem_name = "*");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_auto_decomp(REAL eps, const char * dem_name = "*");

    \par Tcl syntax:
    dem_auto_decomp eps \ref str "dem_name"

    \par Description:
    calls \ref dem_decomp() "dem_decomp" until difference between original DEM norm and decomposed DEM norm
    will be lower than eps
*/
boolvec * dem_auto_decomp(REAL eps, const char * dem_name = "*");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_recons(const char * dem_name = "*");

    \par Tcl syntax:
    dem_recons \ref str "dem_name"

    \par Description:
    makes one wavelet-reconstruction for dem
*/
boolvec * dem_recons(const char * dem_name = "*");

/*! \ingroup tcl_dem_math_wavan
    \fn bool dem_full_recons(const char * dem_name = "*");

    \par Tcl syntax:
    dem_full_recons \ref str "dem_name"

    \par Description:
    makes all possible wavelet-reconstruction (recontructs original dem)
*/
boolvec * dem_full_recons(const char * dem_name = "*");

//
// CONVERTING
//

/*! \ingroup tcl_dem_conv
    \fn bool dem_to_pnts(const char * dem_name = "*");

    \par Tcl syntax:
    dem_to_pnts \ref str "dem_name" "new_name"

    \par Description:
    transforms \ref d_dem "DEM" to \ref d_points "points"
*/
boolvec * dem_to_pnts(const char * dem_name = "*");

/*! \ingroup tcl_dem_conv
    \fn bool dem_to_surf(const char * dem_name = "*");

    \par Tcl syntax:
    dem_to_surf \ref str "dem_name"

    \par Description:
    makes \ref d_surf "surface" from \ref d_dem "DEM"
*/
boolvec * dem_to_surf(const char * dem_name = "*");

/*! \ingroup tcl_dem_conv
    \fn bool dem_to_mask(short true_from, short true_to, const char * dem_name = "*");

    \par Tcl syntax:
    dem_to_mask true_from true_to \ref str "dem_name"

    \par Description:
    makes \ref d_mask "mask" by \ref d_dem "DEM". Value will be true, if it lies in interval [true_from, true_to]
*/
boolvec * dem_to_mask(short true_from, short true_to, const char * dem_name = "*");

//
// OTHER
//

/*! \ingroup tcl_dem_other
    \fn int dem_getCountX(const char * dem_name = "*");

    \par Tcl syntax:
    dem_getCountX \ref str "dem_name"

    \par Description:
    returns the number of X-nodes for \ref d_dem "DEM"
*/
intvec * dem_getCountX(const char * dem_name = "*");

/*! \ingroup tcl_dem_other
    \fn int dem_getCountY(const char * dem_name = "*");

    \par Tcl syntax:
    dem_getCountY \ref str "dem_name"

    \par Description:
    returns the number of Y-nodes for \ref d_dem "DEM"
*/
intvec * dem_getCountY(const char * dem_name = "*");

/*! \ingroup tcl_dem_other
    \fn REAL dem_getStepX(const char * dem_name = "*");

    \par Tcl syntax:
    dem_getStepX \ref str "dem_name"

    \par Description:
    returns step between X-nodes for \ref d_dem "DEM"
*/
vec * dem_getStepX(const char * dem_name = "*");

/*! \ingroup tcl_dem_other
    \fn REAL dem_getStepY(const char * dem_name = "*");

    \par Tcl syntax:
    dem_getStepY \ref str "dem_name"

    \par Description:
    returns step between Y-nodes for \ref d_dem "DEM"
*/
vec * dem_getStepY(const char * dem_name = "*");

/*! \ingroup tcl_dem_other
    \fn bool dem_undef(REAL new_undef_value, const char * dem_name = "*");

    \par Tcl syntax:
    dem_undef new_undef_value \ref str "dem_name"

    \par Description:
    sets new undefined value for \ref d_dem "DEM"
*/
boolvec * dem_undef(REAL new_undef_value, const char * dem_name = "*");

/*! \ingroup tcl_dem_other
    \fn const char * dem_getName(const char * dem_name = "*");

    \par Tcl syntax:
    dem_getName \ref str "dem_name"

    \par Description:
    returns name of \ref d_dem 
*/
strvec * dem_getName(const char * dem_name = "*");

/*! \ingroup tcl_dem_other
    \fn const char * dem_getNameAt(int pos);
    
    \par Tcl syntax:
    dem_getNameAt position

    \par Description:
    returns name of \ref d_dem at position "pos"
*/
const char * dem_getNameAt(int pos);

/*! \ingroup tcl_dem_other
    \fn const char * dem_getId(const char * dem_name = "*");

    \par Tcl syntax:
    dem_getId \ref str "dem_name"

    \par Description:
    returns unique \ref d_dem "dem" identificator
*/
intvec * dem_getId(const char * dem_name = "*");

/*! \ingroup tcl_dem_other
    \fn bool dem_setName(const char * new_name, const char * dem_name = "*");

    \par Tcl syntax:
    dem_setName "new_name" \ref str "dem_name"

    \par Description:
    sets name of \ref d_dem "DEM"
*/
boolvec * dem_setName(const char * new_name, const char * dem_name = "*");

/*! \ingroup tcl_dems
    \fn void dem_del(const char * dem_name = "*");

    \par Tcl syntax:
    dem_del \ref str "dem_name"

    \par Description:
    removes \ref d_dem "DEM" from memory
*/
void dem_del(const char * dem_name = "*");

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

