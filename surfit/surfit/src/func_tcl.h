
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

#ifndef __surfit__func_tcl__
#define __surfit__func_tcl__

namespace surfit {

class datafile;
class vec;
class datafile;
class grid;
class task;
class func;

//
// SAVE_LOAD
//

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_load(const char * filename, const char * funcname = 0);
    \brief loads \ref surfit_func named 'funcname' from ROFF file (see \ref datafile for details)
    \param filename filename
    \param funcname name for func (optional)
*/
bool func_load(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_load_grd(const char * filename, const char * funcname = 0)
    \brief loads \ref surfit_func from SURFER grd file (ASCII format)
*/
bool func_load_grd(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn void func_unload();
    \brief unloads \ref surfit_func from memory
*/
void func_unload();

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_save(const char * filename, const char * funcname = 0);
    \brief saves \ref surfit_func to ROFF file (see \ref datafile) named filename in active \ref rw_mode
*/
bool func_save(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_save_grd(const char * filename);
    \brief saves \ref surfit_func to SURFER grd file (ASCII format)
*/
bool func_save_grd(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_save_xyz(const char * filename);
    \brief saves \ref surfit_func to XYZ text format
*/
bool func_save_xyz(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_save_bmp(const char * filename);
    \brief saves \ref surfit_func to Windows-BMP file with \ref surfit_color_scale
*/
bool func_save_bmp(const char * filename);

//
// MATH OPERATIONS
//

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_getValue(REAL x, REAL y);
    \brief calculates \ref surfit_func value at point (x,y)
*/
REAL func_getValue(REAL x, REAL y);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_resid(const char * filename)
    \brief calculates residuals between \ref surfit_task and \ref surfit_func. 
    Saves result to text file.
*/
bool func_resid(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_D1();
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for \ref surfit_func
*/
REAL func_D1();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_D2();
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for \ref surfit_func
*/
REAL func_D2();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_gradient();
    \brief calculates "map of gradients lengths" from \ref surfit_func and saves result to \ref surfit_func (!)
*/
bool func_gradient();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_project();
    \brief recalculates function on \ref surfit_grid using bilinear interpolation algorithm
*/
bool func_project();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_add_noise(REAL std);
    \brief adds normally-distributed noise with parameters N(0,std) to coeff
*/
bool func_add_noise(REAL std);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_minz();
    \brief returns minimum Z-value of \ref surfit_func
*/
REAL func_minz();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_maxz();
    \brief calculates maximum Z-value of \ref surfit_func
*/
REAL func_maxz();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_mean();
    \brief calculates mean Z-value of \ref surfit_func
*/
REAL func_mean();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_std(REAL mean);
    \brief calculates standard deviation from mean Z-value of \ref surfit_func
*/
REAL func_std(REAL mean);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_sum();
    \brief calculates sum of all \ref surfit_func cell values
*/
REAL func_sum();

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_plus(func * fnc);
    \brief \ref surfit_func = \ref surfit_func + fnc. Functions sizes must be equal
*/
bool func_plus(func * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_minus(func * fnc);
    \brief \ref surfit_func = \ref surfit_func - fnc. undef_value means no operation. 
    Functions sizes must be equal
*/
bool func_minus(func * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool bool func_minus_undef(func * fnc);
    \brief \ref surfit_func = \ref surfit_func - fnc. Functions sizes must be equal.
*/
bool func_minus_undef(func * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_mult(func * fnc);
    \brief \ref surfit_func = \ref surfit_func * fnc. Functions sizes must be equal
*/
bool func_mult(func * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_div(func * fnc);
    \brief \ref surfit_func = \ref surfit_func / fnc. Functions sizes must be equal
*/
bool func_div(func * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_set(func * fnc);
    \brief \ref surfit_func = fnc. Functions sizes must be equal
*/
bool func_set(func * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_plus_real(REAL val);
    \brief \ref surfit_func = \ref surfit_func + val
*/
bool func_plus_real(REAL val);

SURFIT_EXPORT
/* \ingroup tcl_func_math
   \fn bool func_minus_real(REAL val);
   \brief \ref surfit_func = \ref surfit_func - val
*/
bool func_minus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_mult_real(REAL val);
    \brief \ref surfit_func = \ref surfit_func * val
*/
bool func_mult_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_div_real(REAL val);
    \brief \ref surfit_func = \ref surfit_func / val
*/
bool func_div_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_set_real(REAL val);
    \brief \ref surfit_func = val
*/
bool func_set_real(REAL val);



//
// WAVELETS SECTION
//

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn int func_get_details_level();
    \brief returns the depth of wavelet decomposition of \ref surfit_func
*/
int func_get_details_level();

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_decomp();
    \brief makes one wavelet-decomposition for \ref surfit_func
*/
bool func_decomp();

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_auto_decomp(REAL eps);
    \brief calls func_decomp() until difference between calc_approx_norm() will be lower than eps
*/
bool func_auto_decomp(REAL eps);

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_recons();
    \brief makes one wavelet-reconstruction for \ref surfit_func
*/
bool func_recons();

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_full_recons();
    \brief makes all possible wavelet-reconstruction (recontructs original function)
*/
bool func_full_recons();

//
// CONVERTING
//

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_task();
    \brief transforms \ref surfit_func to \ref surfit_task
*/
bool func_to_task();

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_defarea(REAL true_from, REAL true_to);
    \brief makes \ref surfit_defarea by \ref surfit_func. Value will be true, if it lies in interval [true_from, true_to]
*/
bool func_to_defarea(REAL true_from, REAL true_to);

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_defareas(REAL true_from, REAL true_to);
    \brief makes \ref surfit_defarea by \ref surfit_func and adds it to \ref surfit_defareas. 
    Value will be true, if it lies in interval [true_from, true_to]
*/
bool func_to_defareas(REAL true_from, REAL true_to);

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_trend(REAL D1, REAL D2);
    \brief makes \ref surfit_trend from \ref surfit_func
*/
bool func_to_trend(REAL D1, REAL D2);

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_trends(REAL D1, REAL D2);
    \brief makes \ref trend from \ref surfit_func and adds it to \ref surfit_trends
*/
bool func_to_trends(REAL D1, REAL D2);

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_wfunc(REAL weight);
    \brief makes \ref surfit_wfunc from \ref surfit_func with specified informational weight
*/
bool func_to_wfunc(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_wfuncs(REAL weight);
    \brief makes \ref wfunc from \ref surfit_func with specified informational weight
    and adds it to \ref surfit_wfuncs
*/
bool func_to_wfuncs(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_funcs();
    \brief moves \ref surfit_func to \ref surfit_funcs
*/
bool func_to_funcs();



//
// OTHER
//

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn bool func_check();
    \brief checks for \ref surfit_func existance 
*/
bool func_check();

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn int func_getCountX();
    \brief returns the amount of X-nodes for \ref surfit_func
*/
int func_getCountX();

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn int func_getCountY();
    \brief returns the amount of Y-nodes for \ref surfit_func
*/
int func_getCountY();

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn REAL func_getStepX();
    \brief returns step between X-nodes for \ref surfit_func
*/
REAL func_getStepX();

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn REAL func_getStepY();
    \brief returns step between Y-nodes for \ref surfit_func
*/
REAL func_getStepY();

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn bool func_undef(REAL new_undef_value);
    \brief sets undefined value for \ref surfit_func
*/
bool func_undef(REAL new_undef_value);

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn void func_info(func * fnc = NULL);
    \brief prints some info about function. If func==NULL, then prints info about \ref surfit_func
*/
void func_info(func * fnc = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn bool func_name(const char * new_name, func * fnc = NULL);
    \brief sets name for \ref surfit_func or fnc 
*/
bool func_name(const char * new_name, func * fnc = NULL);

}; // namespace surfit;

#endif

