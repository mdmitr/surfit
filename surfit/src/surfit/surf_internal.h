
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

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn d_surf * _surf_load(const char * filename, const char * surfname);
    \brief loads surf named 'surfname' from ROFF file (see \ref datafile for details)
    \param filename data file
    \param surfname name
*/
d_surf * _surf_load(const char * filename, const char * surfname);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn d_surf * _surf_load_df(datafile * df, const char * surfname);
    \brief loads surf named 'surfname' from \ref datafile 
*/
d_surf * _surf_load_df(datafile * df, const char * surfname);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_grd(const char * filename, const char * surfname)
    \brief loads surf from SURFER grd file (ASCII format)
*/
d_surf * _surf_load_grd(const char * filename, const char * surfname); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_gmt(const char * filename, const char * surfname)
    \brief loads surf from Generic Mapping Tools grd file (CDF format)
*/
d_surf * _surf_load_gmt(const char * filename, const char * surfname); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_grass(const char * filename, const char * surfname)
    \brief loads surf from GRASS ASCII file
*/
d_surf * _surf_load_grass(const char * filename, const char * surfname); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_arcgis(const char * filename, const char * surfname)
    \brief loads surf from ArcGIS ASCII file
*/
d_surf * _surf_load_arcgis(const char * filename, const char * surfname); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_jpg(const char * filename, const char * surfname, REAL minz = 0, REAL maxz = 0)
    \brief loads surf from JPEG file
*/
d_surf * _surf_load_jpg(const char * filename, const char * surfname, 
			REAL minz = 0, REAL maxz = 0, 
			REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save(const d_surf * srf, const char * filename);
    \brief saves surf to ROFF file (see \ref datafile for details) in active \ref rw_mode
    \param srf surf class to save
    \param filename data file
*/
bool _surf_save(const d_surf * srf, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_df(const d_surf * srf, datafile * df);
    \brief writes surf tags to \ref datafile
*/
bool _surf_save_df(const d_surf * srf, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_grd(const d_surf * srf, const char * filename); 
    \brief saves surf to SURFER grd file (ASCII format)
*/
bool _surf_save_grd(const d_surf * srf, const char * filename); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_gmt(const d_surf * srf, const char * filename); 
    \brief saves surf to Generic Mapping Tools grd file (CDF format)
*/
bool _surf_save_gmt(const d_surf * srf, const char * filename); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_grass(const d_surf * srf, const char * filename); 
    \brief saves surf to GRASS ASCII file 
*/
bool _surf_save_grass(const d_surf * srf, const char * filename); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_arcgis(const d_surf * srf, const char * filename); 
    \brief saves surf to ArcGIS ASCII file 
*/
bool _surf_save_arcgis(const d_surf * srf, const char * filename); 

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_xyz(const d_surf * srf, const char * filename);
    \brief saves surf to XYZ text format
*/
bool _surf_save_xyz(const d_surf * srf, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_jpg(const d_surf * srf, const char * filename, int quality);
    \brief saves surf to JPEG format
*/
bool _surf_save_jpg(const d_surf * srf, const char * filename, int quality = 255);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn d_points * _surf_to_pnts(const d_surf * srf)
    \brief converts \ref surf to \ref d_points
*/
d_points * _surf_to_pnts(const d_surf * srf);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_add_noise(d_surf * srf, REAL std);
    \brief adds normally-distributed noise with parameters N(0,std) to \ref surf::coeff
*/
bool _surf_add_noise(d_surf * srf, REAL std);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn void _surf_info(const d_surf * srf);
    \brief prints some info about surface
*/
void _surf_info(const d_surf * srf);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_resid(const d_surf * srf, const d_points * pnts, const char * filename);
    \brief calculates residuals between values set at points in \ref d_points and \ref surf "srf". 
    Saves result to text file.
*/
bool _surf_resid(const d_surf * srf, const d_points * pnts, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn d_surf * _surf_project(const d_surf * srf, grid * grd);
    \brief recalculates \ref surf "srf" to new \ref grid "grd" using bilinear interpolation algorithm
*/
d_surf * _surf_project(const d_surf * srf, d_grid * grd);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn REAL _surf_D1(const d_surf * srf);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for surface "srf"
*/
REAL _surf_D1(const d_surf * srf);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn REAL _surf_D2(const d_surf * srf);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for surface "srf"
*/
REAL _surf_D2(const d_surf * srf);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn void _add_surfit_surfs(d_surf * srf);
    \brief adds srf to \ref surfit_surfs
*/
void _add_surfit_surfs(d_surf * srf);

SURFIT_EXPORT
/*! \ingroup internal_surf
    \fn d_surf * _surf_gradient(const d_surf * srf);
    \brief calculates "map of gradients lengths"
*/
d_surf * _surf_gradient(const d_surf * srf);

//
// wavelets section
//

SURFIT_EXPORT
/*! \ingroup int_surf_wavan
    \fn bool _surf_decomp(d_surf * srf);
    \brief makes one wavelet-decomposition 
*/
bool _surf_decomp(d_surf * srf);

SURFIT_EXPORT
/*! \ingroup int_surf_wavan
    \fn bool _surf_auto_decomp(d_surf * srf, REAL eps);
    \brief calls _surf_decomp() while difference between calc_approx_norm() are lower than eps
*/
bool _surf_auto_decomp(d_surf * srf, REAL eps);

SURFIT_EXPORT
/*! \ingroup int_surf_wavan
    \fn bool _surf_recons(d_surf * srf);
    \brief makes one wavelet-reconstruction
*/
bool _surf_recons(d_surf * srf);

SURFIT_EXPORT
/*! \ingroup int_surf_wavan
    \fn bool _surf_full_recons(d_surf * srf);
    \brief makes all possible wavelet-reconstruction (recontructs original surface)
*/
bool _surf_full_recons(d_surf * srf);

SURFIT_EXPORT
d_grid * adopt_surf_grid(const d_surf * srf, d_grid * grd,
		         size_t & from_x, size_t & to_x,
		         size_t & from_y, size_t & to_y);

SURFIT_EXPORT
REAL _surf_mean_area(const d_surf * srf, const d_area * area);

SURFIT_EXPORT
REAL _surf_wmean_area(const d_surf * srf, const d_surf * wsrf, const d_area * area);

SURFIT_EXPORT
REAL _surf_sum_area(const d_surf * srf, const d_area * crv);

SURFIT_EXPORT
int _surf_cells_in_area(const d_surf * srf, const d_area * crv);

SURFIT_EXPORT
void _surfit_surf_add(d_surf * srf);

}; // namespace surfit;

#endif

