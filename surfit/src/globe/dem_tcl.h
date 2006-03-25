
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

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_load(const char * filename, const char * demname = 0);
    \brief loads \ref globe_dem named 'demname' from ROFF file (see \ref datafile for details)
    \param filename filename
    \param demname name for dem (optional)
*/
bool dem_load(const char * filename, const char * demname = 0);

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_grd(const char * filename, const char * demname = 0)
    \brief loads \ref globe_dem from SURFER grd file (ASCII format)
*/
bool dem_load_grd(const char * filename, const char * demname = 0);

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);
    \brief loads \ref globe_dem from DTM files (hdr + bin)
*/
bool dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename = 0);

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_hgt(const char * hgt_filename, const char * dem_name);
    \brief loads \ref globe_dem from HGT files (Shuttle Radar Topographic Mission files)
*/
bool dem_load_hgt(const char * hgt_filename, const char * dem_name = 0);

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_hgt_zip(const char * hgt_filename, const char * dem_name);
    \brief loads \ref globe_dem from zipped HGT files (Shuttle Radar Topographic Mission files)
*/
bool dem_load_hgt_zip(const char * hgt_filename, const char * dem_name = 0);

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_load_globe(const char * filename);
    \brief loads \ref globe_dem from GTOPO30 files (The Global Land One-km Base Elevation (GLOBE) Project)
*/
bool dem_load_globe(const char * filename, const char * demname = 0);

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_save(const char * filename, const char * pos = "0");
    \brief saves \ref globe_dem to ROFF file (see \ref datafile) named filename in active \ref rw_mode
*/
bool dem_save(const char * filename, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_grd(const char * filename, const char * pos = "0");
    \brief saves \ref globe_dem to SURFER grd file (ASCII format)
*/
bool dem_save_grd(const char * filename, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_xyz(const char * filename, const char * pos = "0");
    \brief saves \ref globe_dem to XYZ text format
*/
bool dem_save_xyz(const char * filename, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_save_load
    \fn bool dem_save_dtm(const char * filename, const char * pos = "0");
    \brief saves \ref globe_dem to DTM files (hdr + bin)
*/
bool dem_save_dtm(const char * filename, const char * pos = "0");

//
// MATH OPERATIONS
//

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn REAL dem_getValue(REAL x, REAL y, const char * pos = "0");
    \brief calculates \ref globe_dem value at point (x,y)
*/
REAL dem_getValue(REAL x, REAL y, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_resid(const char * filename, const char * dem_pos = "0", const char * pnts_pos = "0")
    \brief calculates residuals between \ref d_points and \ref d_dem
    Saves result to text file.
*/
bool dem_resid(const char * filename, const char * dem_pos = "0", const char * pnts_pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn REAL dem_D1(const char * pos = "0");
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for \ref globe_dem
*/
REAL dem_D1(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn REAL dem_D2(const char * pos = "0");
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for \ref globe_dem
*/
REAL dem_D2(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_gradient(const char * pos = "0");
    \brief calculates "map of gradients lengths" from \ref globe_dem and saves result to \ref globe_dem (!)
*/
bool dem_gradient(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_project(const char * pos = "0");
    \brief recalculates dem on \ref surfit_grid using bilinear interpolation algorithm
*/
bool dem_project(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn REAL dem_minz(const char * pos = "0");
    \brief returns minimum Z-value of \ref d_dem
*/
REAL dem_minz(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn REAL dem_maxz(const char * pos = "0");
    \brief calculates maximum Z-value of \ref d_dem
*/
REAL dem_maxz(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_plus(const char * pos1, const char * pos2);
    \brief dem1 = dem1 + dem2. dems sizes must be equal
*/
bool dem_plus(const char * pos1, const char * pos2);

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_minus(const char * pos1, const char * pos2);
    \brief dem1 = dem1 - dem2. undef_value means no operation. 
    dems sizes must be equal
*/
bool dem_minus(const char * pos1, const char * pos2);

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_mult(const char * pos1, const char * pos2);
    \brief dem1 = dem1 * dem2. dems sizes must be equal
*/
bool dem_mult(const char * pos1, const char * pos2);

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_div(const char * pos1, const char * pos2);
    \brief dem1 = dem1 / dem2. dems sizes must be equal
*/
bool dem_div(const char * pos1, const char * pos2);

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_set(const char * pos1, const char * pos2);
    \brief dem1 = dem2. dems sizes must be equal
*/
bool dem_set(const char * pos1, const char * pos2);

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_plus_real(REAL val, const char * pos = "0");
    \brief dem = dem + val
*/
bool dem_plus_real(REAL val, const char * pos = "0");

GLOBE_EXPORT
/* \ingroup tcl_dem_math
   \fn bool dem_minus_real(REAL val, const char * pos = "0");
   \brief dem = dem - val
*/
bool dem_minus_real(REAL val, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_mult_real(REAL val, const char * pos = "0");
    \brief dem = dem * val
*/
bool dem_mult_real(REAL val, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_div_real(REAL val, const char * pos = "0");
    \brief dem = dem / val
*/
bool dem_div_real(REAL val, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_math
    \fn bool dem_set_real(REAL val, const char * pos = "0");
    \brief dem = val
*/
bool dem_set_real(REAL val, const char * pos = "0");

//
// WAVELETS SECTION
//

GLOBE_EXPORT
/*! \ingroup tcl_dem_wavan
    \fn int dem_get_details_level(const char * pos = "0");
    \brief returns the depth of wavelet decomposition for dem
*/
int dem_get_details_level(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_wavan
    \fn bool dem_decomp(const char * pos = "0");
    \brief makes one wavelet-decomposition for dem
*/
bool dem_decomp(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_wavan
    \fn bool dem_auto_decomp(REAL eps, const char * pos = "0");
    \brief calls dem_decomp() until difference between calc_approx_norm() will be lower than eps
*/
bool dem_auto_decomp(REAL eps, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_wavan
    \fn bool dem_recons(const char * pos = "0");
    \brief makes one wavelet-reconstruction for dem
*/
bool dem_recons(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_wavan
    \fn bool dem_full_recons(const char * pos = "0");
    \brief makes all possible wavelet-reconstruction (recontructs original dem)
*/
bool dem_full_recons(const char * pos = "0");

//
// CONVERTING
//

GLOBE_EXPORT
/*! \ingroup tcl_dem_conv
    \fn bool dem_to_points(const char * pos = "0", const char * new_name = NULL);
    \brief transforms \ref d_dem to \ref d_points
*/
bool dem_to_points(const char * pos = "0", const char * new_name = NULL);

GLOBE_EXPORT
/*! \ingroup tcl_dem_conv
    \fn bool dem_to_surf(const char * pos = "0", const char * new_name = NULL);
    \brief makes \ref d_surf from \ref d_dem
*/
bool dem_to_surf(const char * pos = "0", const char * new_name = NULL);

GLOBE_EXPORT
/*! \ingroup tcl_dem_conv
    \fn bool dem_to_mask(short true_from, short true_to, const char * pos = "0");
    \brief makes \ref d_mask by \ref d_dem. Value will be true, if it lies in interval [true_from, true_to]
*/
bool dem_to_mask(short true_from, short true_to, const char * pos = "0");

//
// OTHER
//

GLOBE_EXPORT
/*! \ingroup tcl_dem_other
    \fn int dem_getCountX(const char * pos = "0");
    \brief returns the amount of X-nodes for \ref d_dem
*/
int dem_getCountX(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_other
    \fn int dem_getCountY(const char * pos = "0");
    \brief returns the amount of Y-nodes for \ref d_dem
*/
int dem_getCountY(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_other
    \fn REAL dem_getStepX(const char * pos = "0");
    \brief returns step between X-nodes for \ref d_dem
*/
REAL dem_getStepX(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_other
    \fn REAL dem_getStepY(const char * pos = "0");
    \brief returns step between Y-nodes for \ref d_dem
*/
REAL dem_getStepY(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_other
    \fn bool dem_undef(REAL new_undef_value, const char * pos = "0");
    \brief sets undefined value for \ref d_dem
*/
bool dem_undef(REAL new_undef_value, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_other
    \fn const char * dem_getName(const char * pos = "0");
    \brief returns name of \ref d_dem 
*/
const char * dem_getName(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dem_other
    \fn bool dem_setName(const char * new_name, const char * pos = "0");
    \brief sets name of \ref d_dem 
*/
bool dem_setName(const char * new_name, const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dems
    \fn bool dem_delall();
    \brief removes all \ref dem's from \ref globe_dems
*/
bool dem_delall();

GLOBE_EXPORT
/*! \ingroup tcl_dems
    \fn bool dem_del(const char * pos = "0");
    \brief removes \ref d_dem from \ref globe_dems 
*/
bool dem_del(const char * pos = "0");

GLOBE_EXPORT
/*! \ingroup tcl_dems
    \fn int dem_size();
    \brief returns amount of demtions in \ref globe_dems
*/
int dem_size();

GLOBE_EXPORT
/*! \ingroup tcl_dems
    \fn void dems_info();
    \brief prints information about dems in \ref globe_dems
*/
void dems_info();

}; // namespace surfit;

#endif

