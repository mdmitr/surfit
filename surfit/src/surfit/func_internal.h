
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

#ifndef __surfit__func_internal__
#define __surfit__func_internal__

#include <vector>

namespace surfit {

class datafile;
class vec;
class datafile;
class d_grid;
class d_points;
class d_func;
class d_curv;
class grid_line;
class d_area;

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn d_func * _func_load(const char * filename, const char * funcname);
    \brief loads func named 'funcname' from ROFF file (see \ref datafile for details)
    \param filename data file
    \param funcname name
*/
d_func * _func_load(const char * filename, const char * funcname);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn d_func * _func_load_df(datafile * df, const char * funcname);
    \brief loads func named 'funcname' from \ref datafile 
*/
d_func * _func_load_df(datafile * df, const char * funcname);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_load_grd(const char * filename, const char * funcname)
    \brief loads func from SURFER grd file (ASCII format)
*/
d_func * _func_load_grd(const char * filename, const char * funcname); 

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save(const d_func * fnc, const char * filename);
    \brief saves func to ROFF file (see \ref datafile for details) in active \ref rw_mode
    \param fnc func class to save
    \param filename data file
*/
bool _func_save(const d_func * fnc, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save_df(const d_func * fnc, datafile * df);
    \brief writes func tags to \ref datafile
*/
bool _func_save_df(const d_func * fnc, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save_grd(const d_func * fnc, const char * filename); 
    \brief saves func to SURFER grd file (ASCII format)
*/
bool _func_save_grd(const d_func * fnc, const char * filename); 

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save_xyz(const d_func * fnc, const char * filename);
    \brief saves func to XYZ text format
*/
bool _func_save_xyz(const d_func * fnc, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn d_points * _func_to_pnts(const d_func * fnc)
    \brief converts \ref func to \ref d_points
*/
d_points * _func_to_pnts(const d_func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_add_noise(d_func * fnc, REAL std);
    \brief adds normally-distributed noise with parameters N(0,std) to \ref func::coeff
*/
bool _func_add_noise(d_func * fnc, REAL std);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn void _func_info(const d_func * fnc);
    \brief prints some info about function
*/
void _func_info(const d_func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_resid(const d_func * fnc, const d_points * pnts, const char * filename);
    \brief calculates residuals between values set at points in \ref d_points and \ref func "fnc". 
    Saves result to text file.
*/
bool _func_resid(const d_func * fnc, const d_points * pnts, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn d_func * _func_project(const d_func * fnc, grid * grd);
    \brief recalculates \ref func "fnc" to new \ref grid "grd" using bilinear interpolation algorithm
*/
d_func * _func_project(const d_func * fnc, d_grid * grd);

SURFIT_EXPORT
d_func * _func_project_with_faults(const d_func * fnc, d_grid * grd);

//SURFIT_EXPORT
/*! \ingroup internal_func
    \fn d_func * _func_project(d_func * fnc, grid * grd, grid_line * fault_line);
    \brief recalculates \ref func "fnc" to new grid "grd" using bilinear interpolation algorithm 
    with taking \ref grid_line "fault_line" into account as faults
*/
//d_func * _func_project(d_func * fnc, grid * grd, grid_line * fault_line);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn REAL _func_D1(const d_func * fnc);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for function "fnc"
*/
REAL _func_D1(const d_func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn REAL _func_D2(const d_func * fnc);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for function "fnc"
*/
REAL _func_D2(const d_func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn void _add_surfit_funcs(d_func * fnc);
    \brief adds fnc to \ref surfit_funcs
*/
void _add_surfit_funcs(d_func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn d_func * _func_gradient(const d_func * fnc);
    \brief calculates "map of gradients lengths"
*/
d_func * _func_gradient(const d_func * fnc);

//
// wavelets section
//

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_decomp(d_func * fnc);
    \brief makes one wavelet-decomposition 
*/
bool _func_decomp(d_func * fnc);

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_auto_decomp(d_func * fnc, REAL eps);
    \brief calls _func_decomp() while difference between calc_approx_norm() are lower than eps
*/
bool _func_auto_decomp(d_func * fnc, REAL eps);

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_recons(d_func * fnc);
    \brief makes one wavelet-reconstruction
*/
bool _func_recons(d_func * fnc);

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_full_recons(d_func * fnc);
    \brief makes all possible wavelet-reconstruction (recontructs original function)
*/
bool _func_full_recons(d_func * fnc);

SURFIT_EXPORT
d_grid * adopt_func_grid(const d_func * fnc, d_grid * grd,
		         int & from_x, int & to_x,
		         int & from_y, int & to_y);

SURFIT_EXPORT
REAL _func_mean_area(const d_func * fnc, const d_area * area);

SURFIT_EXPORT
REAL _func_wmean_area(const d_func * fnc, const d_func * wfnc, const d_area * area);

SURFIT_EXPORT
REAL _func_sum_area(const d_func * fnc, const d_area * crv);

SURFIT_EXPORT
int _func_cells_in_area(const d_func * fnc, const d_area * crv);

}; // namespace surfit;

#endif

