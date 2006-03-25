
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

#ifndef __surfit__dem_internal__
#define __surfit__dem_internal__

#include <vector>

namespace surfit {

class datafile;
class vec;
class datafile;
class d_grid;
class d_points;
class d_dem;
class grid_line;
class d_surf;
class d_mask;

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_load(const char * filename, const char * demname);
    \brief loads dem named 'demname' from ROFF file (see \ref datafile for details)
    \param filename data file
    \param demname name
*/
d_dem * _dem_load(const char * filename, const char * demname);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_load_dtm(const char * hdr_filename, const char * bin_filename = 0);
    \brief loads \ref dem from DTM files (hdr + bin)
*/
d_dem * _dem_load_dtm(const char * hdr_filename, const char * bin_filename = 0);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_load_hgt(const char * hgt_filename);
    \brief loads \ref dem from HGT files (Shuttle Radar Topographic Mission files)
*/
d_dem * _dem_load_hgt(const char * hgt_filename);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_load_hgt_zip(const char * hgt_filename);
    \brief loads \ref dem from zipped HGT files (Shuttle Radar Topographic Mission files)
*/
d_dem * _dem_load_hgt_zip(const char * hgt_filename);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_load_globe(const char * globe_filename);
    \brief loads \ref dem from GTOPO30 files (The Global Land One-km Base Elevation (GLOBE) Project)
*/
d_dem * _dem_load_globe(const char * globe_filename);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_load_df(datafile * df, const char * demname);
    \brief loads dem named 'demname' from \ref datafile 
*/
d_dem * _dem_load_df(datafile * df, const char * demname);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn bool _dem_load_grd(const char * filename, const char * demname)
    \brief loads dem from SURFER grd file (ASCII format)
*/
d_dem * _dem_load_grd(const char * filename, const char * demname); 

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn void _dem_unload(d_dem *& srf);
    \brief unloads dem from memory
*/
bool _dem_unload(d_dem *& srf);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn bool _dem_save(const d_dem * srf, const char * filename);
    \brief saves dem to ROFF file (see \ref datafile for details) in active \ref rw_mode
    \param srf dem class to save
    \param filename data file
*/
bool _dem_save(const d_dem * srf, const char * filename);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn bool _dem_save_dtm(const d_dem * srf, const char * filename);
    \brief saves dem to DTM files (hdr + bin)
*/
bool _dem_save_dtm(const d_dem * srf, const char * filename);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn bool _dem_save_df(const d_dem * srf, datafile * df);
    \brief writes dem tags to \ref datafile
*/
bool _dem_save_df(const d_dem * srf, datafile * df);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn bool _dem_save_grd(const d_dem * srf, const char * filename); 
    \brief saves dem to SURFER grd file (ASCII format)
*/
bool _dem_save_grd(const d_dem * srf, const char * filename); 

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn bool _dem_save_xyz(const d_dem * srf, const char * filename);
    \brief saves dem to XYZ text format
*/
bool _dem_save_xyz(const d_dem * srf, const char * filename);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_points * _dem_to_points(const d_dem * srf)
    \brief converts \ref d_dem to \ref d_points
*/
d_points * _dem_to_points(const d_dem * srf);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_surf * _dem_to_surf(const d_dem * srf);
    \brief converts \ref dem to \ref surf
*/
d_surf * _dem_to_surf(const d_dem * srf);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_defearea * _dem_to_mask(const d_dem * srf, short true_from, short true_to);
    \brief converts \ref dem to \ref mask
*/
d_mask * _dem_to_mask(const d_dem * srf, short true_from, short true_to);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn void _dem_info(const d_dem * srf);
    \brief prints some info about demtion
*/
void _dem_info(const d_dem * srf);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn bool bool _dem_resid(const d_dem * srf, const d_points * tsk, const char * filename);
    \brief calculates residuals between values set at points in \ref task "tsk" and \ref dem "srf". 
    Saves result to text file.
*/
bool _dem_resid(const d_dem * srf, const d_points * tsk, const char * filename);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_project(const d_dem * srf, const grid * grd);
    \brief recalculates \ref dem "srf" to new \ref grid "grd" using bilinear interpolation algorithm
*/
d_dem * _dem_project(const d_dem * srf, const d_grid * grd);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn REAL _dem_D1(const d_dem * srf);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for demtion "srf"
*/
REAL _dem_D1(const d_dem * srf);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn REAL _dem_D2(const d_dem * srf);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for demtion "srf"
*/
REAL _dem_D2(const d_dem * srf);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn void _add_surfit_dems(d_dem * srf);
    \brief adds srf to \ref surfit_dems
*/
void _add_globe_dems(d_dem * srf);

GLOBE_EXPORT
/*! \ingroup internal_dem
    \fn d_dem * _dem_gradient(const d_dem * dem);
    \brief calculates "map of gradients lengths"
*/
d_dem * _dem_gradient(const d_dem * dem);

//
// wavelets section
//

GLOBE_EXPORT
/*! \ingroup int_dem_wavan
    \fn bool _dem_decomp(d_dem * srf);
    \brief makes one wavelet-decomposition 
*/
bool _dem_decomp(d_dem * srf);

GLOBE_EXPORT
/*! \ingroup int_dem_wavan
    \fn bool _dem_auto_decomp(d_dem * srf, REAL eps);
    \brief calls _dem_decomp() while difference between calc_approx_norm() are lower than eps
*/
bool _dem_auto_decomp(d_dem * srf, REAL eps);

GLOBE_EXPORT
/*! \ingroup int_dem_wavan
    \fn bool _dem_recons(d_dem * srf);
    \brief makes one wavelet-reconstruction
*/
bool _dem_recons(d_dem * srf);

GLOBE_EXPORT
/*! \ingroup int_dem_wavan
    \fn bool _dem_full_recons(d_dem * srf);
    \brief makes all possible wavelet-reconstruction (recontructs original demtion)
*/
bool _dem_full_recons(d_dem * srf);


}; // namespace surfit;

#endif

