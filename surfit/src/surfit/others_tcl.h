
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

#ifndef __surfit_f_completer_tcl_included__
#define __surfit_f_completer_tcl_included__

namespace surfit {

class boolvec;

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    completer D1 D2

    \par Description:
    This rule describes the resulting surface behavior in the areas of low data density. This rule applies to whole resulting surface.
    Here is simple example of "completer" D1 and D2 variables influence:
    \image html surface_and_points.jpg "completer 0 1"
    \image html surface_and_points2.jpg "completer 1 5"
    \image html surface_and_points3.jpg "completer 1 0"

    \param D1 weight coefficient for rule that the resulting surface should tend to constant surface
    \param D2 weight coefficient for rule that the resulting surface should tend to plane surface
    \param alpha anisotropy angle (degrees)
    \param w anisotropy factor
  
    \par Math:
    This command adds the following functional to the functional sequence:
    \f[ 
    \Phi(u_{1,1},\ldots,u_{N,M}) = D_1 \Phi_1(u_{1,1},\ldots,u_{N,M}) + D_2 \Phi_2(u_{1,1},\ldots,u_{N,M}),
    \f]
    where
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \left[ 
    \sum\limits_{j=0}^{M-1} \sum\limits_{i=0}^{N-2}   
    \left( \frac{ u_{i+1,j} - u_{i,j} } { h_x } \right)^2 
    + 
    \sum\limits_{i=0}^{N-1} \sum\limits_{j=0}^{M-2}   
    \left( \frac{ u_{i,j+1} - u_{i,j} } { h_y } \right)^2 
    \right]
    \f]
    \f[
    \Phi_2 = \left[
    \sum\limits_{j=0}^{M-1} \sum\limits_{i=0}^{N-3} 
    \left( \frac{ u_{i+2,j} - 2u_{i+1,j} + u_{i,j} } {h_x^2} \right)^2
    + \right.
    \f]
    \f[
    2\sum\limits_{j=0}^{M-2} \sum\limits_{i=0}^{N-2} 
    \left( \frac{ (u_{i+1,j+1} - u_{i,j+1}) - (u_{i+1,j} - u_{i,j}) } { h_x h_y }  \right)^2
    + 
    \f]
    \f[
    \left.
    \sum\limits_{i=0}^{N-1} \sum\limits_{j=0}^{M-3} 
    \left( \frac{ u_{i,j+2} - 2u_{i,j+1} + u_{i,j} } { h_y^2 } \right)^2
    \right].
    \f]

*/
bool completer(REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    completer_add weight D1 D2

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref completer rule with some weight.
    This rule applies to whole resulting surface.

    \param weight informational weight for this rule
    \param D1 weight coefficient for rule that the resulting surface should tend to constant surface
    \param D2 weight coefficient for rule that the resulting surface should tend to plane surface
    \param alpha anisotropy angle (degrees)
    \param w anisotropy factor

*/
bool completer_add(REAL weight = 1, REAL D1 = 1, REAL D2 = 2, REAL alpha = 0, REAL w = 1);

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    value val

    \par Descrpition:
    Using this rule the resulting surface approximates constant value. 
    This rule applies to whole resulting surface.

    \param val real number for surface approximation. Also you may set val to "undef" 
    string to fill surface with \ref undef_value values.

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{i,j} \left( u_{i,j} - z \right)^2,
    \f]
*/
bool value(const char * val = "undef");

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    value_add weight val

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref value rule with some weight.
    This rule applies to whole resulting surface.

    \param weight informational weight for this rule
    \param val real number for surface approximation

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_{i,j} \left( u_{i,j} - z \right)^2,
    \f]
*/
bool value_add(REAL weight = 1, REAL val = 0);

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    mean value penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface mean value should be 
    equal to real number". 

    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} u_{i,j}} {Q} = m
    \f]
    where (i,j) - indices of the cells, Q - total number of cells, m - desired mean value
*/
bool mean(REAL value, REAL penalty_factor = -2);

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    wmean value "surface_name" penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface weighted mean value 
    should be equal to real number". 

    \par Math:
    This command adds the condition:
    \f[
    \frac {\sum\limits_{i,j} z(x_i,y_j) u_{i,j}} {z(x_i,y_j)} = m
    \f]
    where (i,j) - indices of the cells, \f$z(x_i,y_j)\f$ - weighted surface value for the (i,j) cell,
    m - desired weighted mean value
*/
boolvec * wmean(REAL value, const char * surface_name = "*", REAL penalty_factor = -2);

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    leq value penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface should be lower than or equal to value".
    
    \param value resulting surface values should be lower than or equal to this real number
    \param penalty_factor parameter for \ref penalty algorithm
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \leq z,
    \f]
    where (i,j) - indices of the cells, z - constant value
*/
bool leq(REAL value, REAL penalty_factor = 0);

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    geq value penalty_factor

    \par Description:
    This rule adds the surface condition - "the resulting surface should be greater than or equal to value".
    
    \param value resulting surface values should be lower than or equal to this real number
    \param penalty_factor parameter for \ref penalty algorithm
    
    \par Math:
    This command adds the condition:
    \f[
    u_{i,j} \geq z,
    \f]
    where (i,j) - indices of the cells, z - constant value
*/
bool geq(REAL value, REAL penalty_factor = 0);

/*! \ingroup tcl_rules_other
    \par Tcl syntax:
    hist "histogram_name" penalty_factor threshold

    \par Description:
    This rule adds the surface condition - "the resulting surface histogram should be equal to given histogram".
    
    \param histogram_name desired \ref d_hist "histogram"
    \param penalty_factor parameter for \ref penalty 
    \param treshold another parameter for changing if something going wrong :)
    
    \par Math:
    This command adds the condition:
    \f[
	u_{i,j} = histeq( u_{i,j} ),
    \f]
    where histeq is the histogram equalization algorithm described in the book
    R. Gonzalez and R. Woods Digital Image Processing, Addison-Wesley Publishing Company, 1992, Chap. 4.
    
*/
boolvec * hist(const char * histogram_name = "*", REAL penalty_factor = -1, size_t treshold = 5);

bool triangulate();

}; // namespace surfit;

#endif

