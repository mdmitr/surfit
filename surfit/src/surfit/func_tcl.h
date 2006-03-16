
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

#ifndef __surfit__func_tcl__
#define __surfit__func_tcl__

namespace surfit {

class datafile;
class vec;
class datafile;
class d_grid;
class d_func;

//
// saveload
//

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_del(const char * pos = "0");
    \brief removes \ref func named 'pos' from memory
*/
bool func_del(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_delall();
    \brief removes all \ref func's from memory
*/
bool func_delall();

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_load(const char * filename, const char * funcname = 0);
    \brief loads function named 'funcname' from ROFF file (see \ref datafile for details)
    \param filename filename
    \param funcname name for func (optional)
*/
bool func_load(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_load_grd(const char * filename, const char * funcname = 0)
    \brief loads function from SURFER grd file (ASCII format)
*/
bool func_load_grd(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_save(const char * filename, const char * pos = "0");
    \brief saves function to ROFF file (see \ref datafile) named filename in active \ref rw_mode
*/
bool func_save(const char * filename, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_save_grd(const char * filename, const char * pos = "0");
    \brief saves function to SURFER grd file (ASCII format)
*/
bool func_save_grd(const char * filename, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_save_load
    \fn bool func_save_xyz(const char * filename, const char * pos = "0");
    \brief saves function to XYZ text format
*/
bool func_save_xyz(const char * filename, const char * pos = "0");

//
// MATH OPERATIONS
//

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_getValue(REAL x, REAL y, const char * pos = "0");
    \brief calculates function value at point (x,y)
*/
REAL func_getValue(REAL x, REAL y, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_getValueIJ(int I, int J, const char * pos = "0");
    \brief returns function value at node (I,J)
*/
REAL func_getValueIJ(int I, int J, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_resid(const char * filename, const char * func_pos = "0", const char * pnts_pos = "0")
    \brief calculates residuals between \ref points and \ref func. 
    Saves result to text file.
*/
bool func_resid(const char * filename, const char * func_pos = "0", const char * pnts_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_D1(const char * pos = "0");
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for function
*/
REAL func_D1(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_D2(const char * pos = "0");
    \brief calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for function
*/
REAL func_D2(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_gradient(const char * newname, const char * pos = "0");
    \brief calculates "map of gradients lengths" from function and saves result to function (!)
*/
bool func_gradient(const char * newname, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_project(const char * newname, const char * pos = "0");
    \brief recalculates function on \ref surfit_grid using bilinear interpolation algorithm
*/
bool func_project(const char * newname, const char * pos = "0");

SURFIT_EXPORT
bool func_project_with_faults(const char * newname, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_add_noise(REAL std, const char * pos = "0");
    \brief adds normally-distributed noise with parameters N(0,std) to coeff
*/
bool func_add_noise(REAL std, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_minz(const char * pos = "0");
    \brief returns minimum Z-value of function
*/
REAL func_minz(const char * pos = "0");

SURFIT_EXPORT
REAL func_area_minz(const char * area_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
REAL func_region_minz(const char * region_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_maxz(const char * pos = "0");
    \brief calculates maximum Z-value of function
*/
REAL func_maxz(const char * pos = "0");

SURFIT_EXPORT
REAL func_area_maxz(const char * area_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
REAL func_region_maxz(const char * region_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_mean(const char * pos = "0");
    \brief calculates mean Z-value of function
*/
REAL func_mean(const char * pos = "0");

SURFIT_EXPORT
REAL func_area_mean(const char * curv_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
REAL func_region_mean(const char * region_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
REAL func_wmean(const char * wfunc_pos = "0", const char * pos = "0");

SURFIT_EXPORT
REAL func_area_wmean(const char * curv_pos = "0", const char * wfunc_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
REAL func_region_wmean(const char * region_pos = "0", const char * wfunc_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
REAL func_sum_area(const char * curv_pos = "0",  const char * func_pos = "0");

SURFIT_EXPORT
int func_cells_in_area(const char * curv_pos = "0",  const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_std(REAL mean, const char * pos = "0");
    \brief calculates standard deviation from mean Z-value of function
*/
REAL func_std(REAL mean, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn REAL func_sum(const char * pos = "0");
    \brief calculates sum of all function cell values
*/
REAL func_sum(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_plus(const char * pos1, const char * pos2);
    \brief function = function + fnc. Functions sizes must be equal
*/
bool func_plus(const char * pos1, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_plus(const char * pos1, const char * area_pos, const char * pos2);
    \brief function = function + fnc. Functions sizes must be equal
*/
bool func_plus_area(const char * pos1, const char * area_pos, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_minus(const char * pos1, const char * pos2);
    \brief function = function - fnc. undef_value means no operation. 
    Functions sizes must be equal
*/
bool func_minus(const char * pos1, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_minus_area(const char * pos1, const char * area_pos, const char * pos2);
    \brief function = function - fnc. undef_value means no operation. 
    Functions sizes must be equal
*/
bool func_minus_area(const char * pos1, const char * area_pos, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool bool func_minus_undef(const char * pos1, const char * pos2);
    \brief function = function - fnc. Functions sizes must be equal.
*/
bool func_minus_undef(const char * pos1, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool bool func_minus_undef_area(const char * pos1, const char * area_pos, const char * pos2);
    \brief function = function - fnc. Functions sizes must be equal.
*/
bool func_minus_undef_area(const char * pos1, const char * area_pos, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_mult(const char * pos1, const char * pos2);
    \brief function = function * fnc. Functions sizes must be equal
*/
bool func_mult(const char * pos1, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_mult_area(const char * pos1, const char * area_pos, const char * pos2);
    \brief function = function * fnc. Functions sizes must be equal
*/
bool func_mult_area(const char * pos1, const char * area_pos, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_div(const char * pos1, const char * pos2);
    \brief function = function / fnc. Functions sizes must be equal
*/
bool func_div(const char * pos1, const char * pos2);

SURFIT_EXPORT
bool func_div_undef(const char * pos1, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_div_area(const char * pos1, const char * area_pos, const char * pos2);
    \brief function = function / fnc. Functions sizes must be equal
*/
bool func_div_area(const char * pos1, const char * area_pos, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_set(const char * pos1, const char * pos2);
    \brief function = fnc. Functions sizes must be equal
*/
bool func_set(const char * pos1, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_set_area(const char * pos1, const char * area_pos, const char * pos2);
    \brief function = fnc. Functions sizes must be equal
*/
bool func_set_area(const char * pos1, const char * area_pos, const char * pos2);

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_plus_value(REAL val, const char * pos = "0");
    \brief function = function + val
*/
bool func_plus_value(REAL val, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_plus_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
    \brief function = function + val in \ref area
*/
bool func_plus_value_area(REAL val, const char * pos = "0", const char * area_pos = "0");

SURFIT_EXPORT
/* \ingroup tcl_func_math
   \fn bool func_minus_value(REAL val, const char * pos = "0");
   \brief function = function - val
*/
bool func_minus_value(REAL val, const char * pos = "0");

SURFIT_EXPORT
/* \ingroup tcl_func_math
   \fn bool func_minus_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
   \brief function = function - val in \ref area
*/
bool func_minus_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_mult_value(REAL val, const char * pos = "0");
    \brief function = function * val
*/
bool func_mult_value(REAL val, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_mult_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
    \brief function = function * val in \ref area
*/
bool func_mult_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_div_value(REAL val, const char * pos = "0");
    \brief function = function / val
*/
bool func_div_value(REAL val, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_div_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");
    \brief function = function / val
*/
bool func_div_value_area(REAL val, const char * area_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_set_value(REAL val, const char * pos = "0");
    \brief function = val
*/
bool func_set_value(REAL val, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_math
    \fn bool func_set_value_area(const char * Value, const char * area_pos = "0", const char * func_pos = "0");
    \brief function = val in \ref area. Value can be "undef"
*/
bool func_set_value_area(const char * Value, const char * area_pos = "0", const char * func_pos = "0");

//
// WAVELETS SECTION
//

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn int func_get_details_level(const char * pos = "0");
    \brief returns the depth of wavelet decomposition of function
*/
int func_get_details_level(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_decomp(const char * pos = "0");
    \brief makes one wavelet-decomposition for function if pos == -1 or for 
    \ref func from functions if pos >= 0
*/
bool func_decomp(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_auto_decomp(REAL eps, const char * pos = "0");
    \brief calls func_decomp() until difference between calc_approx_norm() will be lower than eps
*/
bool func_auto_decomp(REAL eps, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_recons(const char * pos = "0");
    \brief makes one wavelet-reconstruction for function if pos == -1 or for 
    \ref func from functions if pos >= 0
*/
bool func_recons(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_wavan
    \fn bool func_full_recons(const char * pos = "0");
    \brief makes all possible wavelet-reconstruction (recontructs original function)
*/
bool func_full_recons(const char * pos = "0");

//
// CONVERTING
//

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_pnts(const char * func_pos = "0");
    \brief transforms \ref func_pos to \ref points
*/
bool func_to_pnts(const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_conv
    \fn bool func_to_mask(REAL true_from, REAL true_to, const char * pos = "0");
    \brief makes \ref surfit_mask by function. Value will be true, if it lies in interval [true_from, true_to]
*/
bool func_to_mask(REAL true_from, REAL true_to, const char * pos = "0");

//
// OTHER
//

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn int func_getCountX(const char * pos = "0");
    \brief returns the amount of X-nodes for function
*/
int func_getCountX(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn int func_getCountY(const char * pos = "0");
    \brief returns the amount of Y-nodes for function
*/
int func_getCountY(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn REAL func_getStepX(const char * pos = "0");
    \brief returns step between X-nodes for function
*/
REAL func_getStepX(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn REAL func_getStepY(const char * pos = "0");
    \brief returns step between Y-nodes for function
*/
REAL func_getStepY(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn bool func_undef(REAL new_undef_value, const char * pos = "0");
    \brief sets undefined value for function
*/
bool func_undef(REAL new_undef_value, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn void func_info(const char * pos = "0");
    \brief prints some info about function. If func==NULL, then prints info about function
*/
void func_info(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn const char * func_getName(const char * pos = "0");
    \brief returns name for function or \ref func in functions at 'pos' position
*/
const char * func_getName(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_func_other
    \fn bool func_setName(const char * new_name, const char * pos = "0");
    \brief sets name for function or \ref func in functions at 'pos' position
*/
bool func_setName(const char * new_name, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn int func_size();
    \brief returns amount of functions in functions
*/
int func_size();

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn void funcs_info();
    \brief prints information about functions in functions
*/
void funcs_info();

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn void surfit_func_add(d_func * fnc);
    \brief adds \ref d_func into functions
*/
void surfit_func_add(d_func * fnc);

}; // namespace surfit;

#endif

