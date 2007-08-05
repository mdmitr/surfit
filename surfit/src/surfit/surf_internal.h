
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

#ifndef __surfit__surf_internal__
#define __surfit__surf_internal__

#include <vector>
#include <float.h>

namespace surfit {

class datafile;
class vec;
class datafile;
class d_grid;
class d_points;
class d_surf;
class d_curv;
class grid_line;
class d_area;
class d_mask;
class d_cntr;


//! loads \ref d_surf named 'surfname' from surfit \ref datafile
SURFIT_EXPORT
d_surf * _surf_load(const char * filename, const char * surfname);

//! loads \ref d_surf named 'surfname' from surfit \ref datafile 
SURFIT_EXPORT
d_surf * _surf_load_df(datafile * df, const char * surfname);

//! saves \ref d_surf to surfit \ref datafile 
SURFIT_EXPORT
bool _surf_save(const d_surf * srf, const char * filename);

//! plots \ref d_surf to PostScript file
SURFIT_EXPORT
bool _surf_plot(const d_surf * srf, const char * filename, size_t number_of_levels = 16, bool draw_isos = true, bool draw_colorscale = true);

//! writes \ref d_surf tags to \ref datafile
SURFIT_EXPORT
bool _surf_save_df(const d_surf * srf, datafile * df);

//! converts \ref d_surf to \ref d_points
SURFIT_EXPORT
d_points * _surf_to_pnts(const d_surf * srf);

//! adds normally-distributed noise with parameters N(0,std) to \ref d_surf::coeff
SURFIT_EXPORT
bool _surf_add_noise(d_surf * srf, REAL std);

//! prints some info about \ref d_surf
SURFIT_EXPORT
void _surf_info(const d_surf * srf);

//! calculates residuals between values set at points in \ref d_points and \ref d_surf 
SURFIT_EXPORT
bool _surf_resid(const d_surf * srf, const d_points * pnts, const char * filename);

//! recalculates \ref d_surf to new \ref d_grid using bilinear interpolation algorithm
SURFIT_EXPORT
d_surf * _surf_project(const d_surf * srf, d_grid * grd);

//! calculates value of \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ for \ref d_surf
SURFIT_EXPORT
REAL _surf_D1(const d_surf * srf);

//! calculates value of \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ for \ref d_surf
SURFIT_EXPORT
REAL _surf_D2(const d_surf * srf);

//! adds \ref d_surf to \ref surfit_surfs
SURFIT_EXPORT
void _add_surfit_surfs(d_surf * srf);

//! calculates "map of gradients lengths"
SURFIT_EXPORT
d_surf * _surf_gradient(const d_surf * srf);

//
// wavelets section
//

//! makes one wavelet-decomposition 
SURFIT_EXPORT
bool _surf_decomp(d_surf * srf);

//! calls _surf_decomp() while difference between calc_approx_norm() are lower than eps
SURFIT_EXPORT
bool _surf_auto_decomp(d_surf * srf, REAL eps);

//! makes one wavelet-reconstruction
SURFIT_EXPORT
bool _surf_recons(d_surf * srf);

//! makes all possible wavelet-reconstruction (recontructs original surface)
SURFIT_EXPORT
bool _surf_full_recons(d_surf * srf);

//! calculates \ref d_surf mean value inside \ref d_area
SURFIT_EXPORT
REAL _surf_mean_area(const d_surf * srf, const d_area * area);

//! calculates \ref d_surf mean value where \ref d_mask is true
SURFIT_EXPORT
REAL _surf_mean_mask(const d_surf * srf, const d_mask * mask);

//! calculates \ref d_surf weighted mean value inside \ref d_area
SURFIT_EXPORT
REAL _surf_wmean_area(const d_surf * srf, const d_surf * wsrf, const d_area * area);

//! calculates \ref d_surf weighted mean value where \ref d_mask is true
SURFIT_EXPORT
REAL _surf_wmean_mask(const d_surf * srf, const d_surf * wsrf, const d_mask * mask);

//! calculates sum of all cells, which are inside \ref d_area
SURFIT_EXPORT
REAL _surf_sum_area(const d_surf * srf, const d_area * area);

//! calculates number of cells inside \ref d_area
SURFIT_EXPORT
int _surf_cells_in_area(const d_surf * srf, const d_area * crv);

//! adds \ref d_surf to \ref surfit_surfs
SURFIT_EXPORT
void _surfit_surf_add(d_surf * srf);

//! calculates \ref d_surf from \ref d_points using triangulation algorithm
SURFIT_EXPORT
d_surf * triangulate_points(const d_points * pnts, const d_grid * grd);

//! traces contours from \ref d_surf
SURFIT_EXPORT
std::vector<d_cntr *> * _surf_trace_cntrs(const d_surf * surf, REAL from = FLT_MAX, REAL to = FLT_MAX, REAL step = FLT_MAX, bool closed = false);

}; // namespace surfit;

#endif

