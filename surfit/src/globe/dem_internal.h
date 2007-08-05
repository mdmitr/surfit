
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

//! \brief loads dem named 'demname' from surfit datafile (see \ref datafile for details)
GLOBE_EXPORT
d_dem * _dem_load(const char * filename, const char * demname);

//! loads \ref dem from DTM files (hdr + bin)
GLOBE_EXPORT
d_dem * _dem_load_dtm(const char * hdr_filename, const char * bin_filename = 0);

//! loads \ref dem from HGT files (Shuttle Radar Topographic Mission files)
GLOBE_EXPORT
d_dem * _dem_load_hgt(const char * hgt_filename);

//! loads \ref dem from zipped HGT files (Shuttle Radar Topographic Mission files)
GLOBE_EXPORT
d_dem * _dem_load_hgt_zip(const char * hgt_filename);

//! loads \ref dem from GTOPO30 files (The Global Land One-km Base Elevation (GLOBE) Project)
GLOBE_EXPORT
d_dem * _dem_load_globe(const char * globe_filename);

//! loads dem named 'demname' from \ref datafile 
GLOBE_EXPORT
d_dem * _dem_load_df(datafile * df, const char * demname);

//! loads dem from SURFER grd file (ASCII format)
GLOBE_EXPORT
d_dem * _dem_load_grd(const char * filename, const char * demname); 

//! unloads dem from memory
GLOBE_EXPORT
bool _dem_unload(d_dem *& srf);

//! saves dem to surfit datafile
GLOBE_EXPORT
bool _dem_save(const d_dem * srf, const char * filename);

//! saves dem to DTM files (hdr + bin)
GLOBE_EXPORT
bool _dem_save_dtm(const d_dem * srf, const char * filename);

//! writes dem tags to \ref datafile
GLOBE_EXPORT
bool _dem_save_df(const d_dem * srf, datafile * df);

//! saves dem to SURFER grd file (ASCII format)
GLOBE_EXPORT
bool _dem_save_grd(const d_dem * srf, const char * filename); 

//! saves dem to XYZ text format
GLOBE_EXPORT
bool _dem_save_xyz(const d_dem * srf, const char * filename);

//! converts \ref d_dem to \ref d_points
GLOBE_EXPORT
d_points * _dem_to_points(const d_dem * srf);

//! converts \ref dem to \ref surf
GLOBE_EXPORT
d_surf * _dem_to_surf(const d_dem * srf);

//! converts \ref dem to \ref mask
GLOBE_EXPORT
d_mask * _dem_to_mask(const d_dem * srf, short true_from, short true_to);

//! prints some info about demtion
GLOBE_EXPORT
void _dem_info(const d_dem * srf);

//! calculates residuals between values set at points in \ref task "tsk" and \ref dem "srf". Saves result to text file.
GLOBE_EXPORT
bool _dem_resid(const d_dem * srf, const d_points * tsk, const char * filename);

//! recalculates \ref dem "srf" to new \ref grid "grd" using bilinear interpolation algorithm
GLOBE_EXPORT
d_dem * _dem_project(const d_dem * srf, const d_grid * grd);

/*! \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for demtion "srf"
*/
GLOBE_EXPORT
REAL _dem_D1(const d_dem * srf);

/*! \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for demtion "srf"
*/
GLOBE_EXPORT
REAL _dem_D2(const d_dem * srf);

//! adds dem to \ref surfit_dems
GLOBE_EXPORT
void _add_globe_dems(d_dem * srf);

//! calculates "map of gradients lengths"
GLOBE_EXPORT
d_dem * _dem_gradient(const d_dem * dem);

//
// wavelets section
//

//! makes one wavelet-decomposition 
GLOBE_EXPORT
bool _dem_decomp(d_dem * srf);

//! calls _dem_decomp() while difference between calc_approx_norm() are lower than eps
GLOBE_EXPORT
bool _dem_auto_decomp(d_dem * srf, REAL eps);

//! makes one wavelet-reconstruction
GLOBE_EXPORT
bool _dem_recons(d_dem * srf);

//! makes all possible wavelet-reconstruction (recontructs original demtion)
GLOBE_EXPORT
bool _dem_full_recons(d_dem * srf);

}; // namespace surfit;

#endif

