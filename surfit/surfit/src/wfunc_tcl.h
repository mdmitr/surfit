
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

#ifndef __surfit__wfunc_tcl__
#define __surfit__wfunc_tcl__

namespace surfit {

class datafile;
class vec;
class datafile;
class grid;
class task;
class wfunc;

//
// save_load
//

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_save_load
    \fn bool wfunc_load(const char * filename, const char * wfuncname = 0);
    \brief loads \ref surfit_wfunc named 'wfuncname' from datafile
    \param filename filename
    \param wfuncname name for wfunc (optional)
*/   
bool wfunc_load(const char * filename, const char * wfuncname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_save_load
    \fn bool wfunc_load_grd(const char * filename, REAL weight, const char * wfuncname)
    \brief loads \ref surfit_wfunc from SURFER grd file (ASCII format)
*/
bool wfunc_load_grd(const char * filename, REAL weight, const char * wfuncname);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_save_load
    \fn void wfunc_unload();
    \brief unloads \ref surfit_wfunc from memory
*/
void wfunc_unload();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_save_load
    \fn bool wfunc_save(const char * filename, const char * wfuncname = 0);
    \brief saves \ref surfit_wfunc to file named filename in active \ref rw_mode
*/
bool wfunc_save(const char * filename, const char * wfuncname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_save_load
    \fn bool wfunc_save_grd(const char * filename);
    \brief saves \ref surfit_wfunc to SURFER grd file (ASCII format)
*/
bool wfunc_save_grd(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_save_load
    \fn bool wfunc_save_xyz(const char * filename);
    \brief saves \ref surfit_wfunc to XYZ text format
*/
bool wfunc_save_xyz(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_save_load
    \fn bool wfunc_save_bmp(const char * filename);
    \brief saves \ref surfit_wfunc to Windows-BMP file with \ref surfit_color_scale
*/
bool wfunc_save_bmp(const char * filename);

//
// MATH
//

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn REAL wfunc_getValue(REAL x, REAL y);
    \brief calculates wfunction value at point (x,y)
*/
REAL wfunc_getValue(REAL x, REAL y);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_add_noise(REAL std);
    \brief adds normally-distributed noise with parameters N(0,std) to coeff
*/
bool wfunc_add_noise(REAL std);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn REAL wfunc_minz();
    \brief calculates minimum value of Z for \ref surfit_wfunc
*/
REAL wfunc_minz();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn REAL wfunc_maxz();
    \brief calculates maximum value of Z for \ref surfit_wfunc
*/
REAL wfunc_maxz();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn REAL wfunc_mean();
    \brief calculates mean value of Z for \ref surfit_wfunc
*/
REAL wfunc_mean();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn REAL wfunc_std(REAL mean);
    \brief calculates standard deviation from mean value of Z for \ref surfit_wfunc
*/
REAL wfunc_std(REAL mean);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_plus(wfunc * fnc);
    \brief \ref surfit_wfunc = \ref surfit_wfunc + fnc. wfunctions sizes must be equal
*/
bool wfunc_plus(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_minus(wfunc * fnc);
    \brief \ref surfit_wfunc = \ref surfit_wfunc - fnc. wfunctions sizes must be equal
*/
bool wfunc_minus(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_mult(wfunc * fnc);
    \brief \ref surfit_wfunc = \ref surfit_wfunc * fnc. wfunctions sizes must be equal
*/
bool wfunc_mult(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_div(wfunc * fnc);
    \brief \ref surfit_wfunc = \ref surfit_wfunc / fnc. wfunctions sizes must be equal
*/
bool wfunc_div(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_set(wfunc * fnc);
    \brief \ref surfit_wfunc = fnc. wfunctions sizes must be equal
*/
bool wfunc_set(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_plus_real(REAL val);
    \brief \ref surfit_wfunc = \ref surfit_wfunc + val
*/
bool wfunc_plus_real(REAL val);

SURFIT_EXPORT
/* \ingroup tcl_wfunc_math
   \fn bool wfunc_minus_real(REAL val);
   \brief \ref surfit_wfunc = \ref surfit_wfunc - val
*/
bool wfunc_minus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_mult_real(REAL val);
    \brief \ref surfit_wfunc = \ref surfit_wfunc * val
*/
bool wfunc_mult_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_div_real(REAL val);
    \brief \ref surfit_wfunc = \ref surfit_wfunc / val
*/
bool wfunc_div_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_math
    \fn bool wfunc_set_real(REAL val);
    \brief \ref surfit_wfunc = val
*/
bool wfunc_set_real(REAL val);

//
// wavelets section
//

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn int wfunc_get_details_level();
    \brief returns the depth of wavelet decomposition of \ref surfit_wfunc
*/
int wfunc_get_details_level();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_wavan
    \fn bool wfunc_decomp();
    \brief makes one wavelet-decomposition 
*/
bool wfunc_decomp();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_wavan
    \fn bool wfunc_auto_decomp(REAL eps);
    \brief calls wfunc_decomp() while difference between calc_approx_norm() are lower than eps
*/
bool wfunc_auto_decomp(REAL eps);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_wavan
    \fn bool wfunc_recons();
    \brief makes one wavelet-reconstruction
*/
bool wfunc_recons();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_wavan
    \fn bool wfunc_full_recons();
    \brief makes all possible wavelet-reconstruction (recontructs original wfunction)
*/
bool wfunc_full_recons();

//
// convers
//

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_conv
    \fn bool wfunc_to_wtask();
    \brief transforms \ref surfit_wfunc to \ref surfit_wtask
*/
bool wfunc_to_wtask();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_conv
    \fn bool wfunc_to_func();
    \brief makes \ref surfit_func from \ref surfit_wfunc 
*/
bool wfunc_to_func();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_conv
    \fn bool wfunc_to_funcs();
    \brief makes \ref func from \ref surfit_wfunc 
    and adds to \ref surfit_funcs
*/
bool wfunc_to_funcs();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_conv
    \fn bool wfunc_to_wfuncs();
    \brief moves \ref surfit_wfunc to \ref surfit_wfuncs
*/
bool wfunc_to_wfuncs();

//
// other
//

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn bool wfunc_check();
    \brief checks for \ref surfit_wfunc existance 
*/
bool wfunc_check();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn int wfunc_getCountX();
    \brief returns the amount of X-nodes for \ref surfit_wfunc
*/
int wfunc_getCountX();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn int wfunc_getCountY();
    \brief returns the amount of Y-nodes for \ref surfit_wfunc
*/
int wfunc_getCountY();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn REAL wfunc_getStepX();
    \brief returns step between X-nodes for \ref surfit_wfunc
*/
REAL wfunc_getStepX();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn REAL wfunc_getStepY();
    \brief returns step between Y-nodes for \ref surfit_wfunc
*/
REAL wfunc_getStepY();

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn bool bool wfunc_undef(REAL new_undef_value);
    \brief sets undefined value for \ref surfit_wfunc
*/
bool wfunc_undef(REAL new_undef_value);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn void wfunc_info(wfunc * fnc = NULL);
    \brief prints some info about wfunction. If wfunc==NULL, then prints info about \ref surfit_wfunc
*/
void wfunc_info(wfunc * fnc = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wfunc_other
    \fn bool wfunc_name(const char * new_name, wfunc * wfnc = NULL);
    \brief sets name of \ref surfit_wfunc or wfnc
*/
bool wfunc_name(const char * new_name, wfunc * wfnc = NULL);



}; // namespace surfit;

#endif

