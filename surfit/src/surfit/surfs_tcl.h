
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

namespace surfit {

/*! \ingroup tcl_rules_surfs
    \fn bool surface(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surface "surface_name_or_position"

    \par Description:
    Using this rule the resulting surface approximates other surface in least squares meaning.

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{i,j} \left( u_{i,j} - z(x_i, y_j) \right)^2,
    \f]
    where (i,j) - indexes of the cells, \f$z(x_i, y_j)\f$ - surface value for the (i,j) cell.
*/
SURFIT_EXPORT
bool surface(const char * surface_name_or_position = "0");

/*! \ingroup tcl_rules_surfs
    \fn bool surface_add(REAL weight, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surface_add weight "surface_name_or_position"

    \par Description:
    This rule modifies previous (modifiable) rule by adding the \ref surface rule with some weight.

    \param weight informational weight for this rule
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_{i,j} \left( u_{i,j} - z(x_i, y_j) \right)^2,
    \f]
    where (i,j) - indexes of the cells, \f$z(x_i, y_j)\f$ - surface value for the (i,j) cell.
*/
SURFIT_EXPORT
bool surface_add(REAL weight, const char * surface_name_or_position = "0");

/*! \ingroup tcl_rules_surfs
    \fn bool surface_leq(const char * surface_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    surface_leq "surface_name_or_position" mult

    \par Description:
    This rule adds the surface condition - "the surface should be lower than equal to other surface".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
    \param mult multiplier parameter for \ref penalty algorithm

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z(x_i, y_j) \quad i=1,\ldots,N, \quad j=1,\ldots,M
    \f]
    where (i,j) - indexes of the cells, \f$z(x_i, y_j)\f$ - surface value for the (i,j) cell.
*/
SURFIT_EXPORT
bool surface_leq(const char * surface_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_surfs
    \fn bool surface_geq(const char * surface_name_or_position = "0", REAL mult = 0.001);

    \par Tcl syntax:
    surface_geq "surface_name_or_position" mult

    \par Description:
    This rule adds the surface condition - "the surface should be greater than equal to other surface".
    In case of the \ref penalty algorithm bad convergence or unexpected (wrong) result, you should carefully review
    your conditions and if they are correct, try to change "mult" parameter

    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number
    \param mult multiplier parameter for \ref penalty algorithm

    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z(x_i, y_j) \quad i=1,\ldots,N, \quad j=1,\ldots,M
    \f]
    where (i,j) - indexes of the cells, \f$z(x_i, y_j)\f$ - surface value for the (i,j) cell.
*/
SURFIT_EXPORT
bool surface_geq(const char * surface_name_or_position = "0", REAL mult = 0.001);

/*! \ingroup tcl_rules_surfs
    \fn bool trend(REAL D1 = 1, REAL D2 = 2, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    trend D1 D2 "surface_name_or_position"

    \par Description:
    This rule determines resulting surface behaviour in regions out low information density. This rule
    tells, that in these regions resulting surface should be similar to other surface 
    (which is called trend). 
    
    \param D1 informational weight for rule that sounds "resulting surface should have the same gradients as trend surface"
    \param D2 informational weight for rule that sounds "resulting surface should have the same curvature as trend surface"
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number. This is a trend surface.

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[ 
\Phi(u_{1,1},\ldots,u_{N,M}) = 
 \mathbf{D_1} \frac{h_y}{h_x} \left[ 
 \left( \left( u_{i+1,j}-u_{i,j} \right) - \left( t(x_{i+1,},y_j)-t(x_i,y_j) \right) \right)^2 + 
 \left( (u_{i,j} - u_{i-1,j})-(t(x_i,y_j) - t(x_{i-1},y_j)) \right)^2
 \right] + 
\f]
\f[
 \mathbf{D_1} \frac{h_x}{h_y} \left[ 
 \left( \left( u_{i,j+1}-u_{i,j} \right) - \left( t(x_i,y_{j+1})-t(x_i,y_j) \right) \right)^2 + 
 \left( \left( u_{i,j-1} - u_{i,j} \right) -  \left( t(x_i,y_{j-1}) - t(x_i,y_j) \right) \right)^2
 \right] +
\f]
\f[ 
 +  \mathbf{D_2} \frac{h_y^2}{h_x^2}
 \left[
 \left( (u_{i+2,j} - 2u_{i+1,j} + u_{i,j}) - (t(x_{i+2},y_j) - 2t(x_{i+1},y_j) + t(x_i,y_j)) \right)^2  + \right.
\f]
\f[
 \left( (u_{i+1,j} - 2u_{i,j} + u_{i-1,j}) - (t(x_{i+1},y_j) - 2t(x_i,y_j) + t(x_{i-1},y_j)) \right)^2  +
\f]
\f[
 \left.
 \left( (u_{i,j} - 2u_{i-1,j} + u_{i-2,j}) - (t(x_i,y_j) - 2t(x_{i-1},y_j) + t(x_{i-2},y_j)) \right)^2 
 \right] +
\f]
\f[ 
 +  2 \mathbf{D_2} \left(
 \left[
 \left( (u_{i+1,j+1} - u_{i,j+1} - u_{i+1,j} + u_{i,j}) - (t(x_{i+1},y_{j+1}) - t(x_i,y_{j+1}) - t(x_{i+1},y_j) + t(x_i,y_j) ) \right)
 \right] + \right.
\f]
\f[
 \left.
 \left[
 \left( (u_{i,j+1} - u_{i-1,j+1} - u_{i,j} + u_{i-1,j}) - (t(x_i,y_{j+1}) - t(x_{i-1},y_{j+1}) - t(x_i,y_j) + t(x_{i-1},y_j)) \right)
 \right] \right) +
\f]
\f[ 
 +  \mathbf{D_2} \frac{h_x^2}{h_y^2}
 \left[
 \left( (u_{i,j+2} - 2u_{i,j+1} + u_{i,j}) - (t(x_i,y_{j+2}) - 2t(x_i,y_{j+1}) + t(x_i,y_j)) \right)^2  +
 \right.
\f]
\f[
 \left( (u_{i,j+1} - 2u_{i,j} + u_{i,j-1}) - (t(x_i,y_{j+1}) - 2t(x_i,y_j) + t(x_i,y_{j-1})) \right)^2  +
\f]
\f[
 \left.
 \left( (u_{i,j} - 2u_{i,j-1} + u_{i,j-2}) - (t(x_i,y_j) - 2t(x_i,y_{j-1}) + t(x_i,y_{j-2})) \right)^2 
 \right] +
\f]
\f[ 
 +  2 \mathbf{D_2} \left(
 \left[
 \left( (u_{i+1,j+1} - u_{i+1,j} - u_{i,j+1} + u_{i,j}) - (t(x_{i+1},y_{j+1}) - t(x_{i+1},y_j) - t(x_i,y_{j+1}) + t(x_i,y_j)) \right)
 \right] +
 \right.
\f]
\f[
 \left.
 \left[
 \left( (u_{i+1,j} - u_{i+1,j-1} - u_{i,j} + u_{i,j-1}) - (t(x_{i+1},y_j) - t(x_{i+1},y_{j-1}) - t(x_i,y_j) + t(x_i,y_{j-1})) \right)
 \right] \right) = \min.
\f]

*/
SURFIT_EXPORT
bool trend(REAL D1 = 1, REAL D2 = 2, const char * surface_name_or_position = "0");

/*! \ingroup tcl_rules_surfs
    bool trend_add(REAL weight, REAL D1 = 1, REAL D2 = 2, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    trend_add weight D1 D2 "surface_name_or_position"

    \par Description:
    This rule modifies previous (modifiable) rule by adding the \ref trend rule with some weight.

    \param weight informational weight for this rule
    \param D1 informational weight for rule that sounds "resulting surface should have the same gradients as trend surface"
    \param D2 informational weight for rule that sounds "resulting surface should have the same curvature as trend surface"
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number. This is a trend surface.
*/	
SURFIT_EXPORT
bool trend_add(REAL weight, REAL D1 = 1, REAL D2 = 0, const char * surface_name_or_position = "0");

/*! \ingroup tcl_rules_surfs
    \fn bool mask(const char * val, const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask val "surface_name_or_position"

    \par Description:
    Using this rule the resulting surface approximates cells where mask is true with constant real number

    \param val real number for cells approximation
    \param mask_name_or_position name of \ref d_mask "mask" dataset, or mask position number

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{i,j} \left( u_{i,j} - z \right)^2,
    \f]
    where (i,j) - indexes of the cells where mask is true, z - constant real number.

*/
SURFIT_EXPORT
bool mask(const char * val, const char * mask_name_or_position = "0");
	
}; // namespace surfit;

