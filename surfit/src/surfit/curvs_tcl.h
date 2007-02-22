
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

#ifndef __surfit_curvs_tcl_included__
#define __surfit_curvs_tcl_included__

namespace surfit {

//////////////
//
// curv
//
//////////////

/*! \ingroup tcl_rules_curvs
    \fn bool curve(REAL value, const char * curv_name_or_position = "0");

    \par Tcl syntax:
    curve value "curve_name_or_position"

    \par Description:
    Using this rule the resulting surface approximates the curve with constant real number.

    \param value real number for surface approximation at curve
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z \right)^2,
    \f] 
    where (i,j) - indices of the cells cross with curve, 
    z - value for curve approximation.  
    
*/
bool curve(REAL value, const char * curv_name_or_position = "0");

/*! \ingroup tcl_rules_curvs
    \fn bool curve_add(REAL value, REAL weight = 1, const char * curv_name_or_position = "0");
    
    \par Tcl syntax:
    curve_add value weight "curv_name_or_position"

    \par Description:
    This rule modifies a previous (modifiable) rule by adding the \ref curve rule with 
    some weight. Use this rule if you don't know "value" exactly. 
    Using this rule the resulting surface approximates the curve with "value", taking into 
    account a previous (modifiable) rule.

    \param value real number for surface approximation at curve
    \param weight informational weight for this rule
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indices of the cells cross with curve, 
    z - value for curve approximation.  
*/
bool curve_add(REAL value, REAL weight = 1, const char * curv_name_or_position = "0");

/*! \ingroup tcl_rules_curvs
    \fn bool curve_leq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    curve_leq value "curv_name_or_position"

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be lower than or equal to value".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter.

    \param value surface should be lower than or equal to this real number
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number
    \param mult multiplier parameter for \ref penalty algorithm

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z,
    \f]
    where (i,j) - indices of the cells cross with curve, z - constant value
*/
bool curve_leq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_curvs
    \fn bool curve_geq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    curve_leq value "curv_name_or_position"

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be greater than or equal to value".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter.
    
    \param value surface should be greater than or equal to this real number
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number
    \param mult multiplier parameter for \ref penalty algorithm
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z,
    \f]
    where (i,j) - indices of the cells cross with curve, z - constant value
*/
bool curve_geq(REAL value, const char * curv_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_curvs
    \fn bool curve_surf(const char * surf_name_or_position = "0", const char * curv_name_or_position = "0");

    \par Tcl syntax:
    curve_surf "surf_name_or_position" "curv_name_or_position"

    \par Description:
    Using this rule the resulting surface approximates curve with other \ref d_surf "surface" values.

    \param surf_name_or_position name of \ref d_surf "surface", or surface position number. The resulting surface
    will approximate this surface at curve.
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number
    
    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - f(x_i,y_j) \right)^2,
    \f] 
    where (i,j) - indices of the cells cross with curve, 
    f(x_i,y_j) - value for curve approximation, calculated as surface value at center of the (i,j) cell.
*/
bool curve_surf(const char * surf_name_or_position = "0", const char * curv_name_or_position = "0");

/*! \ingroup tcl_rules_curvs
    \fn bool curve_surf_add(const char * surf_name_or_position = "0", REAL weight = 1, const char * curv_name_or_position = "0");
    
    \par Tcl syntax:
    curve_surf_add "surf_name_or_position" weight "curv_name_or_position"

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref curve_surf rule with some weight. 
    Using this rule, the resulting surface approximates curve with other surface "values" taking into 
    account a previous (modifiable) rule.
    
    \param surf_name_or_position name of \ref d_surf "surface", or surface position number. The resulting surface
    will approximate this surface at curve.
    \param weight informational weight for this rule
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - f(x_i,y_j) \right)^2,
    \f]
    where (i,j) - indices of the cells cross with curve, 
    f(x_i,y_j) - value for curve approximation, calculated as surface value at center of the (i,j) cell.
*/
bool curve_surf_add(const char * surf_name_or_position = "0", REAL weight = 1, const char * curv_name_or_position = "0");

/*! \ingroup tcl_rules_curvs
    \fn bool curve_surf_leq(const char * surf_name_or_position = "0", const char * curv_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    curve_surf_leq "surf_name_or_position" "curv_name_or_position"

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be lower than or equal 
    to other surface values". 
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should 
    carefully review your conditions and if they are correct, try to change "mult" parameter.

    \param surf_name_or_position name of \ref d_surf "surface", or surface position number. The
    resulting surface should be lower than or equal to this surface values at curve.
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number
    \param mult multiplier parameter for \ref penalty algorithm

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq f(x_i,y_i),
    \f]
    where (i,j) - indices of the cells cross with curve, 
    f(x_i,y_j) - value for curve approximation, calculated as surface value at center of the (i,j) cell.
*/
bool curve_surf_leq(const char * surf_name_or_position = "0", const char * curv_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_curvs
    \fn bool curve_surf_geq(const char * surf_name_or_position = "0", const char * curv_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    curve_surf_geq "surf_name_or_position" "curv_name_or_position"

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be greater 
    than or equal to other surface values".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you 
    should carefully review your conditions and if they are correct, try to change "mult" parameter.

    \param surf_name_or_position name of \ref d_surf "surface", or surface position number. The
    resulting surface should be greater than or equal to this surface values at curve.
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number
    \param mult multiplier parameter for \ref penalty algorithm

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq f(x_i,y_i),
    \f]
    where (i,j) - indices of the cells cross with curve, 
    f(x_i,y_j) - value for curve approximation, calculated as surface value at center of the (i,j) cell.
*/
bool curve_surf_geq(const char * surf_name_or_position = "0", const char * curv_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_curvs
    \fn bool fault(const char * curv_name_or_position = "0");

    \par Tcl syntax:
    fault "curv_name_or_position"

    \par Description:
    This rule modifies special gridding rules by adding "fault" condition. 
    This modification leads to special behavior of the resulting surface: 
    the parts of resulting surface between fault curve are independent of each other.
    This rule is very useful in pressure field reconstruction, or structural surfaces modeling.
    
    \param curv_name_or_position \ref d_curv "curve" name, or curve position number

    \par Gridding rules, modifiable with this rule:
    \li \ref completer
    \li \ref trend
    \li \ref lcm_simple

*/
bool fault(const char * curv_name_or_position = "0");

////////////
//
// area
//
////////////

/*! \ingroup tcl_rules_areas
    \fn bool bool area(const char * value="undef", const char * area_name_or_position = "0", int inside = 1);
    
    \par Tcl syntax:
    area value "area_name_or_position" inside

    \par Description:
    Using this rule the resulting surface approximates area with constant "value" in least squares meaning.
    Value can be set to any real number or "undef".

    \param value real number for surface approximation in area
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number.
    \param inside if inside is equal to 1, then surface will be approximated inside area, else outside

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indices of the cells in area, z - constant value

*/
bool area(const char * value="undef", const char * area_name_or_position = "0", int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_add(REAL value, REAL weight, const char * area_name_or_position = "0", int inside = 1);
    
    \par Tcl syntax:
    area_add value weight "area_name_or_position" inside

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref area rule with some weight. Use this rule
    if you don't know "value" exactly. Using this rule the resulting surface approximates area with "value" 
    taking into account a previous (modifiable) rule.

    \param value real number for surface approximation in area
    \param weight informational weight for this rule
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number.
    \param inside if inside is equal to 1, then surface will be approximated inside area, else outside

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indices of the cells in area, z - constant value

*/
bool area_add(REAL value, REAL weight, const char * area_name_or_position = "0", int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_leq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    
    \par Tcl syntax:
    area_leq value "area_name_or_position" mult inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be lower than or equal to value".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter.

    \param value resulting surface values should be lower than or equal to this real number
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number.
    \param mult multiplier parameter for \ref penalty algorithm
    \param inside if inside is equal to 1, then surface values should be lower than or equal to value 
    inside area, else outside
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z,
    \f]
    where (i,j) - indices of the cells in area, z - constant value

*/
bool area_leq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_geq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    
    \par Tcl syntax:
    area_geq value "area_name_or_position" mult inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be greater than or equal to value".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter.

    \param value resulting surface values should be greater than or equal to this real number
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number.
    \param mult multiplier parameter for \ref penalty algorithm
    \param inside if inside is equal to 1, then surface values should be greater than or equal to value 
    inside area, else outside

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z,
    \f]
    where (i,j) - indices of the cells in area, z - constant value

*/
bool area_geq(REAL value, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_surf(const char * surf_name_or_position = "0", const char * area_name_or_position = "0", int inside = 1);

    \par Tcl syntax:
    area_surf "surf_name_or_position" mult inside

    \par Description:
    Using this rule the resulting surface approximates area in least squares meaning with values 
    taken from the other surface.

    \param surf_name_or_position name of \ref d_surf "surface", or surface position number. Resulting surface
    will approximate this surface values inside (or outside) area.
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number.
    \param inside if inside is equal to 1, then surface will be approximated inside area, else outside

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z(x_i, y_j) \right)^2,
    \f]
    where (i,j) - indices of the cells in area, \f$z(x_i, y_j)\f$ - surface value for the (i,j) cell.

*/
bool area_surf(const char * surf_name_or_position = "0", const char * area_name_or_position = "0", int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_surf_add(const char * surf_name_or_position = "0", REAL weight = 1, const char * area_name_or_position = "0", int inside = 1);

    \par Tcl syntax:
    area_surf_add "surf_name_or_position" weight "area_name_or_position" inside

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref area_surf rule with some weight. 
    Using this rule the resulting surface approximates area with other surface "values" taking into
    account a previous (modifiable) rule.

    \param surf_name_or_position name of \ref d_surf "surface", or surface position number. Resulting surface
    will approximate this surface values inside (or outside) area.
    \param weight informational weight for this rule
    \param area_name_or_position name of \ref d_area "area" dataset, or area position number.
    \param inside if inside is equal to 1, then surface will be approximated inside area, else outside

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z(x_i, y_j) \right)^2,
    \f]
    where (i,j) - indices of the cells in area, \f$z(x_i, y_j)\f$ - surface value for the (i,j) cell.

*/
bool area_surf_add(const char * surf_name_or_position = "0", REAL weight = 1, const char * area_name_or_position = "0", int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_surf_leq(const char * surf_name_or_position = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    
    \par Tcl syntax:
    area_surf_leq "surf_name_or_position_or_position" "area_name_or_position" mult inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be lower than or equal to other surface".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter.

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq f(x_{u_i},y_{u_j})
    \f]
    where (i,j) - indices of the cells in area, \f$f(x_{u_i},y_{u_j})\f$ - \ref d_surf "surface" value in the center of the cell.

*/
bool area_surf_leq(const char * surf_name_or_position = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_surf_geq(const char * surf_name_or_position = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    
    \par Tcl syntax:
    area_surf_geq "surf_name_or_position_or_position" "area_name_or_position" mult inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be greater than or equal to other surface".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter.

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq f(x_{u_i},y_{u_j})
    \f]
    where (i,j) - indices of the cells in area, \f$f(x_{u_i},y_{u_j})\f$ - \ref d_surf "surface" value in the center of the cell.

*/
bool area_surf_geq(const char * surf_name_or_position = "0", const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_mean(REAL mean, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    
    \par Tcl syntax:
    area_mean mean_value "area_name_or_position" mult inside

    \par Description:
    This rule adds the surface condition - "the resulting surface mean value in area should be 
    equal to real number". In case of the \ref penalty algorithm bad convergence or unexpected 
    (wrong) result, you should carefully review your conditions and if they are correct, try 
    to change "mult" parameter.

    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} u_{i,j}} {Q} = m
    \f]
    where (i,j) - indices of the cells in area, Q - number of cells in area, m - desired mean value
*/
bool area_mean(REAL mean, const char * area_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_wmean(REAL mean, const char * area_name_or_position = "0", const char * surf_name_or_position = "0", REAL mult = 0.001, int inside = 1);
    
    \par Tcl syntax:
    area_wmean weighted_mean_value "area_name_or_position" "surf_name_or_position_or_position" mult inside

    \par Description:
    This rule adds the surface condition - "the resulting surface weighted mean value in 
    area should be equal to real number". In case of the \ref penalty algorithm bad 
    convergence or unexpected (wrong) result, you should carefully review your conditions 
    and if they are correct, try to change "mult" parameter.

    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} z(x_i,y_j) u_{i,j}} {z(x_i,y_j)} = m
    \f]
    where (i,j) - indices of the cells in area, \f$z(x_i,y_j)\f$ - weighted surface value for the (i,j) cell,
    m - desired weighted mean value
*/
bool area_wmean(REAL mean, const char * area_name_or_position = "0", const char * surf_name_or_position = "0", REAL mult = 0.001, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_completer(const char * area_name_or_position = "0", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);

    \par Tcl syntax:
    area_completer "area_name_or_position" D1 D2 alpha w inside

    \par Description
    This rule implements \ref completer rule inside or outside \ref d_area "area"

    \param D1 weight coefficient for rule that the resulting surface should tend to constant surface
    \param D2 weight coefficient for rule that the resulting surface should tend to plane surface
    \param alpha anisotropy angle (degrees)
    \param w anisotropy factor
*/
bool area_completer(const char * area_name_or_position = "0", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);

/*! \ingroup tcl_rules_areas
    \fn bool area_completer_add(REAL weight = 1, const char * area_name_or_position = "0", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);

    \par Tcl syntax:
    area_completer_add weight "area_name_or_position" D1 D2 alpha w inside

    \par Description
    This rule adds rule \ref area_completer with informational "weight" to the previous rule.

    \param D1 weight coefficient for rule that the resulting surface should tend to constant surface
    \param D2 weight coefficient for rule that the resulting surface should tend to plane surface
    \param alpha anisotropy angle (degrees)
    \param w anisotropy factor
*/
bool area_completer_add(REAL weight = 1, const char * area_name_or_position = "0", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);

bool area_hist(const char * area_name_or_position = "0", const char * histogram_name_or_position = "0", REAL mult = 0.001, int inside = 1);

//////////////
//
// contour
//
//////////////

/*! \ingroup tcl_rules_cntrs
    \fn bool contour(const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    contour \ref regexp "cntr_name_or_position"

    \par Description:
    Using this rule the resulting surface approximates contour values.

    \param cntr_name_or_position \ref d_cntr "contour" name, or contour position number.

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z_{i,j} \right)^2,
    \f] 
    where (i,j) - indices of the cells cross with contour, 
    \f$ z_{i,j} \f$ - contour mean value for the (i,j) cell.
*/
bool contour(const char * cntr_name_or_position = "0");

/*! \ingroup tcl_rules_cntrs
    \fn bool contour_add(REAL weight, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    contour_add weight \ref regexp "cntr_name_or_position"

    \par Description:
    This rule modifies a previous (modifiable) rule by adding the \ref contour rule with some weight. 
    Use this rule if you don't know contour values exactly. Using this rule the resulting surface 
    approximates contour taking into account a previous (modifiable) rule.

    \param weight informational weight for this rule
    \param cntr_name_or_position \ref d_cntr "contour" name, or contour position number.

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z_{i,j} \right)^2,
    \f]
    where (i,j) - indices of the cells cross with contour, 
    \f$ z_{i,j} \f$ - contour mean value for the (i,j) cell.
*/
bool contour_add(REAL weight, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_rules_cntrs
    \fn bool contour_leq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    contour_leq "cntr_name_or_position" mult

    \par Description:
    This rule adds the surface condition - "the resulting surface at contour should be lower than 
    or equal to the contour values". In case of the \ref penalty algorithm bad convergence or 
    unexpected (wrong) result, you should carefully review your conditions and if they are 
    correct, try to change "mult" parameter.

    \param cntr_name_or_position \ref d_cntr "contour" name, or contour position number.
    \param mult multiplier parameter for \ref penalty algorithm

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z_{i,j}
    \f]
    where (i,j) - indices of the cells cross with contour, \f$z_{i,j}\f$ - contour mean value for the (i,j) cell
*/
bool contour_leq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_cntrs
    \fn bool contour_geq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    contour_geq "cntr_name_or_position" mult

    \par Description:
    This rule adds the surface condition - "the resulting surface at contour should be greater than 
    or equal to contour values". In case of the \ref penalty algorithm bad convergence or unexpected 
    (wrong) result, you should carefully review your conditions and if they are correct, try to 
    change "mult" parameter.

    \param cntr_name_or_position \ref d_cntr "contour" name, or contour position number.
    \param mult multiplier parameter for \ref penalty algorithm

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z_{i,j}
    \f]
    where (i,j) - indices of the cells cross with contour, \f$z_{i,j}\f$ - contour mean value for the (i,j) cell
*/
bool contour_geq(const char * cntr_name_or_position = "0", REAL mult = 0.001);

}; // namespace surfit;

#endif

