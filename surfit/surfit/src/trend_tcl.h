
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

#ifndef __surfit_trend_tcl_included__
#define __surfit_trend_tcl_included__

class trend;

namespace surfit {

//
// SAVE_LOAD
//

SURFIT_EXPORT
/*! \ingroup tcl_trend_save_load
    \fn bool trend_load(const char * filename, const char * funcname = 0);
    \brief loads \ref surfit_trend named 'funcname' from datafile
    \param filename filename
    \param funcname name for trend (optional)
*/
bool trend_load(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_trend_save_load
    \fn bool trend_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname)
    \brief loads \ref surfit_trend from Surfer grd file (ASCII format)
    \param filename filename
    \param D1 weight for D1 functional
    \param D2 weight for D2 functional
    \param trendname name for \ref surfit_trend
*/
bool trend_load_grd(const char * filename, REAL D1 = 1, REAL D2 = 0, const char * trendname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_trend_save_load
    \fn void trend_unload();
    \brief unloads \ref surfit_trend from memory
*/
void trend_unload();

SURFIT_EXPORT
/*! \ingroup tcl_trend_save_load
    \fn bool trend_save(const char * filename, const char * funcname = 0);
    \brief saves \ref surfit_trend to file named filename in active \ref rw_mode
*/
bool trend_save(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_trend_save_load
    \fn bool trend_save_grd(const char * filename);
    \brief saves trend to surfer grd file (ASCII format)
*/
bool trend_save_grd(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_trend_save_load
    \fn bool trend_save_xyz(const char * filename);
    \brief saves \ref surfit_trend to XYZ text format
*/
bool trend_save_xyz(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_trend_save_load
    \fn bool trend_save_bmp(const char * filename);
    \brief saves \ref surfit_trend to Windows-BMP file with \ref surfit_color_scale
*/
bool trend_save_bmp(const char * filename);

//
// MATH OPERATIONS
//

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn REAL trend_getValue(REAL x, REAL y);
    \brief calculates \ref surfit_trend value at point (x,y)
*/
REAL trend_getValue(REAL x, REAL y);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_resid(const char * filename)
    \brief calculates residuals between \ref surfit_task and \ref surfit_trend. 
    Saves result to text file.
*/
bool trend_resid(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_project();
    \brief recalculates trendtion on \ref surfit_grid using bilinear interpolation algorithm
*/
bool trend_project();

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn REAL trend_minz();
    \brief calculates minimum value of Z for \ref surfit_trend
*/
REAL trend_minz();

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn REAL trend_maxz();
    \brief calculates maximum value of Z for \ref surfit_trend
*/
REAL trend_maxz();

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn REAL trend_mean();
    \brief calculates mean value of Z for \ref surfit_trend
*/
REAL trend_mean();

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn REAL trend_std(REAL mean);
    \brief calculates standard deviation from mean value of Z for \ref surfit_trend
*/
REAL trend_std(REAL mean);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_plus(trend * fnc);
    \brief \ref surfit_trend = \ref surfit_trend + fnc. trendtions sizes must be equal
*/
bool trend_plus(trend * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_minus(trend * fnc);
    \brief \ref surfit_trend = \ref surfit_trend - fnc. undef_value means no operation. 
    trendtions sizes must be equal
*/
bool trend_minus(trend * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool bool trend_minus_undef(trend * fnc);
    \brief \ref surfit_trend = \ref surfit_trend - fnc. trendtions sizes must be equal.
*/
bool trend_minus_undef(trend * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_mult(trend * fnc);
    \brief \ref surfit_trend = \ref surfit_trend * fnc. trendtions sizes must be equal
*/
bool trend_mult(trend * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_div(trend * fnc);
    \brief \ref surfit_trend = \ref surfit_trend / fnc. trendtions sizes must be equal
*/
bool trend_div(trend * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_set(trend * fnc);
    \brief \ref surfit_trend = fnc. trendtions sizes must be equal
*/
bool trend_set(trend * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_plus_real(REAL val);
    \brief \ref surfit_trend = \ref surfit_trend + val
*/
bool trend_plus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_minus_real(REAL val);
    \brief \ref surfit_trend = \ref surfit_trend - val
*/
bool trend_minus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_mult_real(REAL val);
    \brief \ref surfit_trend = \ref surfit_trend * val
*/
bool trend_mult_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_div_real(REAL val);
    \brief \ref surfit_trend = \ref surfit_trend / val
*/
bool trend_div_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_trend_math
    \fn bool trend_set_real(REAL val);
    \brief \ref surfit_trend = val
*/
bool trend_set_real(REAL val);

//
// WAVELETS SECTION
//

SURFIT_EXPORT
/*! \ingroup tcl_trend_wavan
    \fn int trend_get_details_level();
    \brief returns the depth of wavelet decomposition
*/
int trend_get_details_level();

SURFIT_EXPORT
/*! \ingroup tcl_trend_wavan
    \fn bool trend_decomp();
    \brief makes one wavelet-decomposition 
*/
bool trend_decomp();

SURFIT_EXPORT
/*! \ingroup tcl_trend_wavan
    \fn bool trend_auto_decomp(REAL eps);
    \brief calls trend_decomp() until difference between calc_approx_norm() will be lower than eps
*/
bool trend_auto_decomp(REAL eps);

SURFIT_EXPORT
/*! \ingroup tcl_trend_wavan
    \fn bool trend_recons();
    \brief makes one wavelet-reconstruction
*/
bool trend_recons();

SURFIT_EXPORT
/*! \ingroup tcl_trend_wavan
    \fn bool trend_full_recons();
    \brief makes all possible wavelet-reconstruction (recontructs original trendtion)
*/
bool trend_full_recons();

//
// convers
//

SURFIT_EXPORT
/*! \ingroup tcl_trend_conv
    \fn bool trend_to_func();
    \brief makes \ref surfit_func from \ref surfit_trend 
*/
bool trend_to_func();

SURFIT_EXPORT
/*! \ingroup tcl_trend_conv
    \fn bool trend_to_funcs();
    \brief makes \ref func from \ref surfit_trend 
    and adds it to \ref surfit_funcs
*/
bool trend_to_funcs();

SURFIT_EXPORT
/*! \ingroup tcl_trend_conv
    \fn bool trend_to_trends();
    \brief moves \ref surfit_trend to \ref surfit_trends
*/
bool trend_to_trends();

//
// OTHER
//

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn bool trend_check();
    \brief checks for \ref surfit_trend existance 
*/
bool trend_check();

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn int trend_getCountX();
    \brief calculates amount of X-nodes for \ref surfit_trend
*/
int trend_getCountX();

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn int trend_getCountY();
    \brief calculates amount of Y-nodes for \ref surfit_trend
*/
int trend_getCountY();

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn REAL trend_getStepX();
    \brief returns step between X-nodes for \ref surfit_trend
*/
REAL trend_getStepX();

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn REAL trend_getStepY();
    \brief returns step between Y-nodes for \ref surfit_trend
*/
REAL trend_getStepY();

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn bool bool trend_undef(REAL new_undef_value);
    \brief sets undefined value for \ref surfit_trend
*/
bool trend_undef(REAL new_undef_value);

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn void trend_info(trend * fnc = NULL);
    \brief prints some info about trendtion. If fnc==NULL, then prints info about \ref surfit_trend
*/
void trend_info(trend * fnc = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_trend_other
    \fn bool trend_name(const char * new_name, trend * trnd = NULL);
    \brief sets name of \ref surfit_trend of trnd
*/
bool trend_name(const char * new_name, trend * trnd = NULL);

}; // namespace surfit

#endif

