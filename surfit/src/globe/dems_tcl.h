
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

class boolvec;

/*! \ingroup tcl_rules_dems
    \fn bool dem(const char * dem_name = "*");

    \par Tcl syntax:
    dem \ref str "dem_name"

    \par Description:
    Using this rule the resulting surface approximates \ref d_dem "DEM" in least squares meaning.

    \param dem_name \ref str "name" of \ref d_dem "DEM" dataset, or DEM position number

    \par Math:
    This command adds the following functional to the functional sequence:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \sum_{i,j} \left( u_{i,j} - z(x_i, y_j) \right)^2,
    \f]
    where (i,j) - indices of the cells, \f$z(x_i, y_j)\f$ - DEM value for the (i,j) cell.
*/
boolvec * dem(const char * dem_name = "*");

/*! \ingroup tcl_rules_dems
    \fn bool dem_add(REAL weight, const char * dem_name = "*");

    \par Tcl syntax:
    dem_add weight \ref str "dem_name"

    \par Description:
    This function modifies previous (modifiable) rule by adding the \ref dem rule with some weight.

    \param weight informational weight for this rule
    \param dem_name \ref str "name" of \ref d_dem "DEM" dataset, or DEM position number

    \par Math:
    This command modifies previous functional \f$ \Phi_0 \f$ by adding \f$ \Phi_1 \f$:
    \f[
    \Phi(u_{1,1},\ldots,u_{N,M}) = \Phi_0(u_{1,1},\ldots,u_{N,M}) + w\Phi_1(u_{1,1},\ldots,u_{N,M}),
    \f]
    where \f$ w \f$ - informational weight,
    \f[
    \Phi_1(u_{1,1},\ldots,u_{N,M}) = \sum_{i,j} \left( u_{i,j} - z(x_i, y_j) \right)^2,
    \f]
    where (i,j) - indices of the cells, \f$z(x_i, y_j)\f$ - DEM value for the (i,j) cell.
*/
boolvec * dem_add(REAL weight, const char * dem_name = "*");

}; // namespace surfit;

