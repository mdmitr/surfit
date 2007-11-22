
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

class boolvec;

//////////////
//
// curv
//
//////////////

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve value \ref str "curve_name"

    \par Description:
    Using this rule the resulting surface approximates the curve with constant real number.

    \param value real number for surface approximation at curve
    \param curv_name \ref d_curv "curve" \ref str "name"

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z \right)^2,
    \f] 
    where (i,j) - indices of the cells cross with curve, 
    z - value for curve approximation.  
    
*/
boolvec * curve(REAL value, const char * curv_name = "*");

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve_add value weight \ref str "curv_name"

    \par Description:
    This rule modifies a previous (modifiable) rule by adding the \ref curve rule with 
    some weight. Use this rule if you don't know "value" exactly. 
    Using this rule the resulting surface approximates the curve with "value", taking into 
    account a previous (modifiable) rule.

    \param value real number for surface approximation at curve
    \param weight informational weight for \ref curve gridding rule
    \param curv_name \ref d_curv "curve" \ref str "name"

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
boolvec * curve_add(REAL value, REAL weight = 1, const char * curv_name = "*");

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve_leq value \ref str "curv_name" penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be lower than or equal to value".

    \param value surface should be lower than or equal to this real number
    \param curv_name \ref d_curv "curve" \ref str "name"
    \param penalty_factor parameter for \ref penalty

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z,
    \f]
    where (i,j) - indices of the cells cross with curve, z - constant value
*/
boolvec * curve_leq(REAL value, const char * curv_name = "*", REAL penalty_factor = 0);

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve_leq value \ref str "curv_name" penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be greater than or equal to value".
    
    \param value surface should be greater than or equal to this real number
    \param curv_name \ref d_curv "curve" \ref str "name"
    \param penalty_factor parameter for \ref penalty
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z,
    \f]
    where (i,j) - indices of the cells cross with curve, z - constant value
*/
boolvec * curve_geq(REAL value, const char * curv_name = "*", REAL penalty_factor = 0);

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve_surf \ref str "surf_name" \ref str "curv_name"

    \par Description:
    Using this rule the resulting surface approximates curve with other \ref d_surf "surface" values.

    \param surf_name \ref str "name" of \ref d_surf "surface". The resulting surface
    will approximate this surface at curve.
    \param curv_name \ref d_curv "curve" \ref str "name"
    
    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - f(x_i,y_j) \right)^2,
    \f] 
    where (i,j) - indices of the cells cross with curve, 
    f(x_i,y_j) - value for curve approximation, calculated as surface value at center of the (i,j) cell.
*/
boolvec * curve_surf(const char * surf_name = "*", const char * curv_name = "*");

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve_surf_add \ref str "surf_name" weight \ref str "curv_name"

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref curve_surf rule with some weight. 
    Using this rule, the resulting surface approximates curve with other surface "values" taking into 
    account a previous (modifiable) rule.
    
    \param surf_name \ref str "name" of \ref d_surf "surface". The resulting surface
    will approximate this surface at curve.
    \param weight informational weight for this rule
    \param curv_name \ref d_curv "curve" \ref str "name"

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
boolvec * curve_surf_add(const char * surf_name = "*", REAL weight = 1, const char * curv_name = "*");

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve_surf_leq \ref str "surf_name" \ref str "curv_name" penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be lower than or equal 
    to other surface values". 
    
    \param surf_name \ref str "name" of \ref d_surf "surface". The
    resulting surface should be lower than or equal to this surface values at curve.
    \param curv_name \ref d_curv "curve" \ref str "name"
    \param penalty_factor parameter for \ref penalty

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq f(x_i,y_i),
    \f]
    where (i,j) - indices of the cells cross with curve, 
    f(x_i,y_j) - value for curve approximation, calculated as surface value at center of the (i,j) cell.
*/
boolvec * curve_surf_leq(const char * surf_name = "*", const char * curv_name = "*", REAL penalty_factor = 0);

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    curve_surf_geq \ref str "surf_name" \ref str "curv_name" penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface at curve should be greater 
    than or equal to other surface values".
    
    \param surf_name \ref str "name" of \ref d_surf "surface". The
    resulting surface should be greater than or equal to this surface values at curve.
    \param curv_name \ref d_curv "curve" \ref str "name"
    \param penalty_factor parameter for \ref penalty

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq f(x_i,y_i),
    \f]
    where (i,j) - indices of the cells cross with curve, 
    f(x_i,y_j) - value for curve approximation, calculated as surface value at center of the (i,j) cell.
*/
boolvec * curve_surf_geq(const char * surf_name = "*", const char * curv_name = "*", REAL penalty_factor = 0);

/*! \ingroup tcl_rules_curvs
    \par Tcl syntax:
    fault \ref str "curv_name"

    \par Description:
    This rule modifies special gridding rules by adding "fault" condition. 
    This modification leads to special behavior of the resulting surface: 
    the parts of resulting surface between fault curve are independent of each other.
    This rule is very useful in pressure field reconstruction, or structural surfaces modeling.
    
    \param curv_name \ref d_curv "curve" \ref str "name"

    \par Gridding rules, modifiable with this rule:
    \li \ref completer
    \li \ref trend
    \li \ref lcm_simple

*/
boolvec * fault(const char * curv_name = "*");

////////////
//
// area
//
////////////

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area value \ref str "area_name" inside

    \par Description:
    Using this rule the resulting surface approximates area with constant "value" in least squares meaning.
    Value can be set to any real number or "undef".

    \param value real number for surface approximation in area
    \param area_name \ref str "name" of \ref d_area "area" dataset
    \param inside if inside is equal to 1, then surface will be approximated inside area, else outside

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indices of the cells in area, z - constant value

*/
boolvec * area(const char * value="undef", const char * area_name = "*", int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_add value weight \ref str "area_name" inside

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref area rule with some weight. Use this rule
    if you don't know "value" exactly. Using this rule the resulting surface approximates area with "value" 
    taking into account a previous (modifiable) rule.

    \param value real number for surface approximation in area
    \param weight informational weight for this rule
    \param area_name \ref str "name" of \ref d_area "area" dataset
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
boolvec * area_add(REAL value, REAL weight, const char * area_name = "*", int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_leq value \ref str "area_name" penalty_factor inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be lower than or equal to value".
    
    \param value resulting surface values should be lower than or equal to this real number
    \param area_name \ref str "name" of \ref d_area "area" dataset
    \param penalty_factor parameter for \ref penalty
    \param inside if inside is equal to 1, then surface values should be lower than or equal to value 
    inside area, else outside
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z,
    \f]
    where (i,j) - indices of the cells in area, z - constant value

*/
boolvec * area_leq(REAL value, const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_geq value \ref str "area_name" penalty_factor inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be greater than or equal to value".
    
    \param value resulting surface values should be greater than or equal to this real number
    \param area_name \ref str "name" of \ref d_area "area" dataset
    \param penalty_factor parameter for \ref penalty
    \param inside if inside is equal to 1, then surface values should be greater than or equal to value 
    inside area, else outside

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z,
    \f]
    where (i,j) - indices of the cells in area, z - constant value

*/
boolvec * area_geq(REAL value, const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_surf \ref str "surf_name" mult inside

    \par Description:
    Using this rule the resulting surface approximates area in least squares meaning with values 
    taken from the other surface.

    \param surf_name \ref str "name" of \ref d_surf "surface". Resulting surface
    will approximate this surface values inside (or outside) area.
    \param area_name name of \ref d_area "area" dataset
    \param inside if inside is equal to 1, then surface will be approximated inside area, else outside

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{p=1}^P \left( u_{i,j} - z(x_i, y_j) \right)^2,
    \f]
    where (i,j) - indices of the cells in area, \f$z(x_i, y_j)\f$ - surface value for the (i,j) cell.

*/
boolvec * area_surf(const char * surf_name = "*", const char * area_name = "*", int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_surf_add \ref str "surf_name" weight \ref str "area_name" inside

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref area_surf rule with some weight. 
    Using this rule the resulting surface approximates area with other surface "values" taking into
    account a previous (modifiable) rule.

    \param surf_name \ref str "name" of \ref d_surf "surface". Resulting surface
    will approximate this surface values inside (or outside) area.
    \param weight informational weight for this rule
    \param area_name \ref str "name" of \ref d_area "area" dataset
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
boolvec * area_surf_add(const char * surf_name = "*", REAL weight = 1, const char * area_name = "*", int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_surf_leq \ref str "surf_name" \ref str "area_name" penalty_factor inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be lower than or equal to other surface".
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq f(x_{u_i},y_{u_j})
    \f]
    where (i,j) - indices of the cells in area, \f$f(x_{u_i},y_{u_j})\f$ - \ref d_surf "surface" value in the center of the cell.

*/
boolvec * area_surf_leq(const char * surf_name = "*", const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_surf_geq \ref str "surf_name" \ref str "area_name" penalty_factor inside

    \par Description:
    This rule adds the surface condition - "the resulting surface in area should be greater than or equal to other surface".
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq f(x_{u_i},y_{u_j})
    \f]
    where (i,j) - indices of the cells in area, \f$f(x_{u_i},y_{u_j})\f$ - \ref d_surf "surface" value in the center of the cell.

*/
boolvec * area_surf_geq(const char * surf_name = "*", const char * area_name = "*", REAL penalty_factor = 0, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_mean mean_value \ref str "area_name" penalty_factor inside

    \par Description:
    This rule adds the surface condition - "the resulting surface mean value in area should be 
    equal to real number". 
    
    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} u_{i,j}} {Q} = m
    \f]
    where (i,j) - indices of the cells in area, Q - number of cells in area, m - desired mean value
*/
boolvec * area_mean(REAL mean, const char * area_name = "*", REAL penalty_factor = -2, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_wmean weighted_mean_value \ref str "area_name" \ref str "surf_name" penalty_factor inside

    \par Description:
    This rule adds the surface condition - "the resulting surface weighted mean value in 
    area should be equal to real number". 

    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} z(x_i,y_j) u_{i,j}} {z(x_i,y_j)} = m
    \f]
    where (i,j) - indices of the cells in area, \f$z(x_i,y_j)\f$ - weighted surface value for the (i,j) cell,
    m - desired weighted mean value
*/
boolvec * area_wmean(REAL mean, const char * area_name = "*", const char * surf_name = "*", REAL penalty_factor = -2, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_completer \ref str "area_name" D1 D2 alpha w inside

    \par Description
    This rule implements \ref completer rule inside or outside \ref d_area "area"

    \param area_name \ref d_area "area" \ref str "name"
    \param D1 weight coefficient for rule that the resulting surface should tend to constant surface
    \param D2 weight coefficient for rule that the resulting surface should tend to plane surface
    \param alpha anisotropy angle (degrees)
    \param w anisotropy factor
    \param inside if inside is equal to 1, then area_completer will work inside area, else outside
*/
boolvec * area_completer(const char * area_name = "*", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_completer_add weight \ref str "area_name" D1 D2 alpha w inside

    \par Description
    This rule adds rule \ref area_completer with informational "weight" to the previous rule.

    \param weight weight coefficient. This gridding rule will be added with this weight coefficient to previous gridding rule.
    \param area_name \ref d_area "area" \ref str "name"
    \param D1 weight coefficient for rule that the resulting surface should tend to constant surface
    \param D2 weight coefficient for rule that the resulting surface should tend to plane surface
    \param alpha anisotropy angle (degrees)
    \param w anisotropy factor
    \param inside if inside is equal to 1, then area_completer will work inside area, else outside
*/
boolvec * area_completer_add(REAL weight = 1, const char * area_name = "*", REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1, int inside = 1);

/*! \ingroup tcl_rules_areas
    \par Tcl syntax:
    area_hist \ref str "area_name" \ref str "histogram_name" penalty_factor inside

    \par Description
    This rule adds the following condition: histogram of the resulting surface should be equal
    to the desired histogram inside (or outside) the area. 
    
    \param area_name \ref str "name" of the area for histogram fitting
    \param histogram_name \ref str "name" of the desired histogram
    \param penalty_factor parameter for \ref penalty
    \param inside if inside is equal to 1, then area_hist will work inside area, else outside
*/
boolvec * area_hist(const char * area_name = "*", const char * histogram_name = "*", REAL penalty_factor = -1, int inside = 1);

//////////////
//
// contour
//
//////////////

/*! \ingroup tcl_rules_cntrs
    \par Tcl syntax:
    contour \ref str "cntr_name"

    \par Description:
    Using this rule the resulting surface approximates contour values.

    \param cntr_name \ref d_cntr "contour" \ref str "name"

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_i \sum_j \left( u_{i,j} - z_{i,j} \right)^2,
    \f] 
    where (i,j) - indices of the cells cross with contour, 
    \f$ z_{i,j} \f$ - contour mean value for the (i,j) cell.
*/
boolvec * contour(const char * cntr_name = "*");

/*! \ingroup tcl_rules_cntrs
    \par Tcl syntax:
    contour_add weight \ref str "cntr_name"

    \par Description:
    This rule modifies a previous (modifiable) rule by adding the \ref contour rule with some weight. 
    Use this rule if you don't know contour values exactly. Using this rule the resulting surface 
    approximates contour taking into account a previous (modifiable) rule.

    \param weight informational weight for this rule
    \param cntr_name \ref d_cntr "contour" \ref str "name"

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
boolvec * contour_add(REAL weight = 50, const char * cntr_name = "*");

/*! \ingroup tcl_rules_cntrs
    \par Tcl syntax:
    smooth_contour \ref str "cntr_name" penalty_factor

    \par Description:
    This rule tells surfit that resulting surface should approximate contour Z-values.
    The result of approximation is that resulting surface should be very similar to given contours.
    The main difference with \ref contour gridding rule is that resulting surface is
    more smooth near contours. 

    \param cntr_name \ref d_cntr "contour" \ref str "name"
    \param penalty_factor parameter for \ref penalty

    \par Math:

	Problem: we need to approximate contours (or isolines with different values) by adjusting 
cell values. 
Let consider Figure 1: solid straight lines show cells borders, dot lines connect
cells centers (black squares), thick black curves shows contours projection to the XoY plane. 
Red points on the figure are intersections of curves and dot lines. 

    \image html matr_sect.gif

Consider the case then the contours cross one of the dot lines, i.e. contours lay between
two cells centers (see Figure 2). 
On the figure \f$\overline{p}_0\f$ and \f$\overline{p}_1\f$ are cells centers coordinates (X or Y), 
\f$u_0\f$ and \f$u_1\f$ are adjustable values for those cells. Red circles are points where contours cross
vertical plane (this plane comes through points \f$p_0\f$ and \f$p_1\f$). 
\f$p_i\f$ - are points coordinates (X or Y), \f$z_i\f$ - Z coordinates.

    \image html matr_sect2.gif

We are trying to approximate points \f$(p_i,z_i)\f$ with straight line. To do
this we are going to find a minimum of the following functional:

\f[
\Phi = \sum\limits_{i=1}^N \left( f(p_i) - z_i \right)^2
\rightarrow \min, 
\f]
where
\f[
 f(p) = u_0 + (u_1-u_0)
\frac{p-\overline{p}_0}{\overline{p}_1-\overline{p}_0}.
\f]

To solve our problem we should write this functional for each pair of 
neighbour cells, if at least one of contours lays between them.

For more details see f_cntr_smooth.tex

*/
boolvec * smooth_contour(const char * cntr_name = "*", REAL penalty_factor = 0);


boolvec * smooth_contour_add(REAL weight = 50, const char * cntr_name = "*");

/*! \ingroup tcl_rules_cntrs
    \par Tcl syntax:
    contour_leq \ref str "cntr_name" penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface at contour should be lower than 
    or equal to the contour values". 

    \param cntr_name \ref d_cntr "contour" \ref str "name"
    \param penalty_factor parameter for \ref penalty

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z_{i,j}
    \f]
    where (i,j) - indices of the cells cross with contour, \f$z_{i,j}\f$ - contour mean value for the (i,j) cell
*/
boolvec * contour_leq(const char * cntr_name = "*", REAL penalty_factor = 0);

/*! \ingroup tcl_rules_cntrs
    \par Tcl syntax:
    contour_geq \ref str "cntr_name" penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface at contour should be greater than 
    or equal to contour values". 

    \param cntr_name \ref d_cntr "contour" \ref str "name"
    \param penalty_factor parameter for \ref penalty

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z_{i,j}
    \f]
    where (i,j) - indices of the cells cross with contour, \f$z_{i,j}\f$ - contour mean value for the (i,j) cell
*/
boolvec * contour_geq(const char * cntr_name = "*", REAL penalty_factor = 0);

}; // namespace surfit;

#endif

