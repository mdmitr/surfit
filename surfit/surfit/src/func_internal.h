
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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
class grid;
class task;
class func;
class wfunc;
class grid_line;

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_check();
    \brief checks for \ref surfit_func existance
*/
bool _func_check();

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn func * _func_load(const char * filename, const char * funcname, int mode);
    \brief loads func named 'funcname' from ROFF file (see \ref datafile for details) in active \ref rw_mode
    \param filename data file
    \param funcname name
    \param mode \ref rw_mode
*/
func * _func_load(const char * filename, const char * funcname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn func * _func_load_df(datafile * df, const char * funcname);
    \brief loads func named 'funcname' from \ref datafile 
*/
func * _func_load_df(datafile * df, const char * funcname);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_load_grd(const char * filename, const char * funcname)
    \brief loads func from SURFER grd file (ASCII format)
*/
func * _func_load_grd(const char * filename, const char * funcname); 

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn void _func_unload(func *& fnc);
    \brief unloads func from memory
*/
bool _func_unload(func *& fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save(func * fnc, const char * filename, const char * funcname);
    \brief saves func to ROFF file (see \ref datafile for details) in active \ref rw_mode
    \param fnc func class to save
    \param filename data file
    \param funcname name for function
*/
bool _func_save(func * fnc, const char * filename, const char * funcname);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save_df(func * fnc, datafile * df);
    \brief writes func tags to \ref datafile
*/
bool _func_save_df(func * fnc, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save_grd(func * fnc, const char * filename); 
    \brief saves func to SURFER grd file (ASCII format)
*/
bool _func_save_grd(func * fnc, const char * filename); 

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save_xyz(func * fnc, const char * filename);
    \brief saves func to XYZ text format
*/
bool _func_save_xyz(func * fnc, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_save_bmp(func * fnc, const char * filename);
    \brief saves func to Windows-BMP file with \ref surfit_color_scale
*/
bool _func_save_bmp(func * fnc, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn task * _func_to_task(const func * fnc)
    \brief converts \ref func to \ref task
*/
task * _func_to_task(const func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool _func_add_noise(func * fnc, REAL std);
    \brief adds normally-distributed noise with parameters N(0,std) to \ref func::coeff
*/
bool _func_add_noise(func * fnc, REAL std);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn void _func_info(func * fnc);
    \brief prints some info about function
*/
void _func_info(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn bool bool _func_resid(func * fnc, task * tsk, const char * filename);
    \brief calculates residuals between values set at points in \ref task "tsk" and \ref func "fnc". 
    Saves result to text file.
*/
bool _func_resid(func * fnc, task * tsk, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn func * _func_project(func * fnc, grid * grd);
    \brief recalculates \ref func "fnc" to new \ref grid "grd" using bilinear interpolation algorithm
*/
func * _func_project(func * fnc, grid * grd);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn func * _func_project(func * fnc, grid * grd, grid_line * fault_line);
    \brief recalculates \ref func "fnc" to new grid "grd" using bilinear interpolation algorithm 
    with taking \ref grid_line "fault_line" into account as faults
*/
func * _func_project(func * fnc, grid * grd, grid_line * fault_line);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn REAL _func_D1(func * fnc);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for function "fnc"
*/
REAL _func_D1(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn REAL _func_D2(func * fnc);
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for function "fnc"
*/
REAL _func_D2(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn func * _get_surfit_func();
    \brief returns pointer to \ref surfit_func
*/
func * _get_surfit_func();

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn void _set_surfit_func(func * fnc);
    \brief sets pointer \ref surfit_func to fnc
*/
void _set_surfit_func(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn void _add_surfit_funcs(func * fnc);
    \brief adds fnc to \ref surfit_funcs
*/
void _add_surfit_funcs(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn func * _func_gradient(func * fnc);
    \brief calculates "map of gradients lengths"
*/
func * _func_gradient(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_func
    \fn wfunc * _func_to_wfunc(func * fnc, REAL weight)
    \brief converts \ref func to \ref wfunc with specified informational weight
*/
wfunc * _func_to_wfunc(func * fnc, REAL weight);


//
// wavelets section
//

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_decomp(func * fnc);
    \brief makes one wavelet-decomposition 
*/
bool _func_decomp(func * fnc);

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_auto_decomp(func * fnc, REAL eps);
    \brief calls _func_decomp() while difference between calc_approx_norm() are lower than eps
*/
bool _func_auto_decomp(func * fnc, REAL eps);

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_recons(func * fnc);
    \brief makes one wavelet-reconstruction
*/
bool _func_recons(func * fnc);

SURFIT_EXPORT
/*! \ingroup int_func_wavan
    \fn bool _func_full_recons(func * fnc);
    \brief makes all possible wavelet-reconstruction (recontructs original function)
*/
bool _func_full_recons(func * fnc);


}; // namespace surfit;

#endif

