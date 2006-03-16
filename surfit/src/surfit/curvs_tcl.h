
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

#ifndef __surfit_fault_tcl_included__
#define __surfit_fault_tcl_included__

namespace surfit {

/////////////
//
// fault
//
/////////////

SURFIT_EXPORT
bool fault_add(const char * curv_name_or_position = "0");

//////////////
//
// curv
//
//////////////

/*! \ingroup tcl_rules_curvs
    \fn bool curve(REAL value, const char * curv_name_or_position = "0");

    Using this rule result surface approximates curve with constant value.

    \par Tcl syntax:
    curve value "curve_name_or_position"

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z \right)^2,
    \f] 
    where (i,j) - indexes of the cells cross with contour, 
    z - value for curve approximation.  
    
*/
SURFIT_EXPORT
bool curve(REAL value, const char * curv_name_or_position = "0");

/*! \ingroup tcl_rules_curvs
    \fn bool curve_add(REAL value, REAL weight, const char * curv_name_or_position = "0");
    
    This rule modifies previous (modifable) rule by adding \ref isoline rule with some weight. Use this rule
    if you don't know "value" exactly. Using this rule result surface approximates curve with "value" taking into
    account previous (modifable) rule.

    \par Tcl syntax:
    curve_add value weight "curv_name_or_position"

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indexes of the cells cross with contour, 
    z - value for curve approximation.  
*/
SURFIT_EXPORT
bool curve_add(REAL value, REAL weight, const char * curv_name_or_position = "0");

SURFIT_EXPORT
bool curve_leq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);

SURFIT_EXPORT
bool curve_geq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);

////////////
//
// area
//
////////////

/*! \ingroup tcl_rules_areas
    \fn bool bool area(const char * value="undef", const char * area_name_or_position = "0", int inside = 1);
    Using this rule rusult surface approximates area with constant "value" in least squares meaning.
    Usually result surface in the area looks like the constant, i.e. surface 
    "interpolates" area with the constant. Value can be set to any number or "undef"

    \par Tcl syntax:
    area value "area_name_or_position" inside

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indexes of the cells in area, z - constant value

*/
SURFIT_EXPORT
bool area(const char * value="undef", const char * area_name_or_position = "0", int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_add(REAL value, REAL weight, const char * area_name_or_position = "0", int inside = 1);
    This rule modifies previous (modifable) rule by adding \ref area rule with some weight. Use this rule
    if you don't know "value" exactly. Using this rule result surface approximates area with "value" taking into
    account previous (modifable) rule.

    \par Tcl syntax:
    area_add value weight "area_name_or_position" inside

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indexes of the cells in area, z - constant value

*/
SURFIT_EXPORT
bool area_add(REAL value, REAL weight, const char * area_name_or_position = "0", int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_leq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    This rule adds surface condition - "the result surface in area should be lower than or equal to value".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    area_leq value "area_name_or_position" mult inside

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z,
    \f]
    where (i,j) - indexes of the cells in area, z - constant value

*/
SURFIT_EXPORT
bool area_leq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_geq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    This rule adds surface condition - "the result surface in area should be greater than or equal to value".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    area_geq value "area_name_or_position" mult inside

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z,
    \f]
    where (i,j) - indexes of the cells in area, z - constant value

*/
SURFIT_EXPORT
bool area_geq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_func_leq(const char * func_pos = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    This rule adds surface condition - "the result surface in area should be lower than or equal to other surface".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    area_func_leq "func_name_or_position_or_position" "area_name_or_position" mult inside

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq f(x_{u_i},y_{u_j})
    \f]
    where (i,j) - indexes of the cells in area, \f$f(x_{u_i},y_{u_j})\f$ - \ref d_func "surface" value in the center of the cell.

*/
SURFIT_EXPORT
bool area_func_leq(const char * func_pos = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_func_geq(const char * func_pos = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    This rule adds surface condition - "the result surface in area should be greater than or equal to other surface".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    area_func_geq "func_name_or_position_or_position" "area_name_or_position" mult inside

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq f(x_{u_i},y_{u_j})
    \f]
    where (i,j) - indexes of the cells in area, \f$f(x_{u_i},y_{u_j})\f$ - \ref d_func "surface" value in the center of the cell.

*/
SURFIT_EXPORT
bool area_func_geq(const char * func_pos = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_mean(REAL mean, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    This rule adds surface condition - "the result surface mean value in area should be equal to value".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    area_mean mean_value "area_name_or_position" mult inside

    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} u_{i,j}} {Q} = m
    \f]
    where (i,j) - indexes of the cells in area, Q - number of cells in area, m - desired mean value
*/
SURFIT_EXPORT
bool area_mean(REAL mean, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_wmean(REAL mean, const char * area_name_or_position = "0", const char * func_pos = "0", REAL mult = 0.001, int inside = 1);
    This rule adds surface condition - "the result surface weighted mean value in area should be equal to value".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    area_wmean weighted_mean_value "area_name_or_position" "func_name_or_position_or_position" mult inside

    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} u_{i,j}} {Q} = m
    \f]
    where (i,j) - indexes of the cells in area, Q - number of cells in area, m - desired mean value
*/
SURFIT_EXPORT
bool area_wmean(REAL mean, const char * area_name_or_position = "0", const char * func_pos = "0", REAL mult = 0.001, int inside = 1);

//////////////
//
// contour
//
//////////////

/*! \ingroup tcl_rules_cntrs
    \fn bool contour(const char * cntr_name_or_position = "0");
    Using this rule result surface approximates contour.

    \par Tcl syntax:
    contour "cntr_name_or_position"

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z_{i,j} \right)^2,
    \f] 
    where (i,j) - indexes of the cells cross with contour, 
    \f$ z_{i,j} \f$ - contour mean value for the (i,j) cell.
*/
SURFIT_EXPORT
bool contour(const char * cntr_name_or_position = "0");

/*! \ingroup tcl_rules_cntrs
    \fn bool contour_add(REAL weight, const char * cntr_name_or_position = "0");
    This rule modifies previous (modifable) rule by adding \ref contour rule with some weight. Use this rule
    if you don't know contour values exactly. Using this rule result surface approximates contour taking into
    account previous (modifable) rule.

    \par Tcl syntax:
    contour_add weight "cntr_name_or_position"

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z_{i,j} \right)^2,
    \f]
    where (i,j) - indexes of the cells cross with contour, 
    \f$ z_{i,j} \f$ - contour mean value for the (i,j) cell.
*/
SURFIT_EXPORT
bool contour_add(REAL weight, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_rules_cntrs
    \fn bool contour_leq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

    This rule adds surface condition - "the result surface at contour should be lower than or equal to contour values".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    contour_leq "cntr_name_or_position" mult

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z_{i,j}
    \f]
    where (i,j) - indexes of the cells cross with contour, \f$z_{i,j}\f$ - contour mean value for the (i,j) cell
*/
SURFIT_EXPORT
bool contour_leq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_cntrs
    \fn bool contour_geq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

    This rule adds surface condition - "the result surface at contour should be greater than or equal to contour values".

    In case of algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \par Tcl syntax:
    contour_geq "cntr_name_or_position" mult

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z_{i,j}
    \f]
    where (i,j) - indexes of the cells cross with contour, \f$z_{i,j}\f$ - contour mean value for the (i,j) cell
*/
SURFIT_EXPORT
bool contour_geq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

}; // namespace surfit;

#endif

