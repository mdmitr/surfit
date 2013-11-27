
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

#ifndef __surfit__surf_tcl__
#define __surfit__surf_tcl__

#include <float.h>

namespace surfit {

class datafile;
class vec;
class datafile;
class d_grid;
class d_surf;
class boolvec;
class intvec;
class strvec;

//
// saveload
//

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load \ref file "filename" \ref str "surfname"
    
    \par Description:
    loads surface named "surfname" from surfit datafile. If no surfname specified, then loads first one.

    \param filename surfit datafile
    \param surfname name for surface (optional)
*/
boolvec * surf_load(const char * filename, const char * surfname = NULL);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save \ref file "filename" \ref str "surface_name" 

    \par Description:
    saves surface to surfit datafile
*/
boolvec * surf_save(const char * filename, const char * surface_name = "*");

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_plot \ref file "filename" \ref str "surface_name" number_of_levels draw_isos draw_colorscale

    \par Description:
    plots surface to PostScript file
*/
boolvec * surf_plot(const char * filename = NULL, const char * surface_name = "*", size_t number_of_levels = 16, bool draw_isos = true, bool draw_labels = true);

//
// MATH OPERATIONS
//

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_getValue x y \ref str "surface_name"

    \par Description:
    calculates surface value at point (x,y)
*/
vec * surf_getValue(REAL x, REAL y, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_getValueIJ I J \ref str "surface_name"

    \par Description:
    returns surface value at node (I,J)

    \param I node number in X direction
    \param J node number in Y direction
    \param surface_name \ref str "name" of the \ref d_surf "surface" object
*/
vec * surf_getValueIJ(int I, int J, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_resid \ref file "filename" \ref str "surface_name" \ref str "points_name"

    \par Description:
    calculates residuals between \ref d_points "points" values and \ref d_surf "surface" values, calculated at points (x,y) coordinates.
    Saves result to text file.
*/
boolvec * surf_resid(const char * filename, const char * surface_name = "*", const char * points_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_D1 \ref str "surface_name"

    \par Description:
    calculates value of \f$ \int\limits_\Omega \left[ f_x^2 + f_y^2 \right] dx dy \f$ 
    for surface, where f is a surface.
*/
vec * surf_D1(const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_D2 \ref str "surface_name"

    \par Description:
    calculates value of 
    \f$ \int\limits_\Omega \left[ f_{xx}^2 + 2f_{xy}^2 + f_{yy}^2 \right] dx dy \f$ 
    for surface, where f is a surface.
*/
vec * surf_D2(const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_gradient \ref str "surface_name" "newname"

    \par Description:
    calculates surface of "gradients lengths" for surface and saves result to new surface named "newname"
*/
boolvec * surf_gradient(const char * surface_name = "*", const char * newname = NULL);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_project \ref str "surface_name" "newname"

    \par Description:
    recalculates surface on current \ref d_grid "grid" using bilinear interpolation algorithm
*/
boolvec * surf_project(const char * surface_name = "*", const char * newname = NULL);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_add_noise std \ref str "surface_name"

    \par Description:
    adds normally-distributed noise with parameters N(0,std) to coeff

    \param surface_name \ref str "name" of the \ref d_surf "surface" object
    \param std standart deviation
*/
void surf_add_noise(REAL std, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_minz \ref str "surface_name"

    \par Description:
    returns minimum value for surface
*/
vec * surf_minz(const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_area_minz \ref str "area_name" \ref str "surface_name"

    \par Description:
    returns minimum value for surface in area
*/
vec * surf_area_minz(const char * area_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_maxz \ref str "surface_name"
     
    \par Description:
    returns maximum value for surface
*/
vec * surf_maxz(const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_area_maxz \ref str "area_name" \ref str "surface_name"

    \par Description:
    returns maximum value for surface in area
*/
vec * surf_area_maxz(const char * area_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mean \ref str "surface_name"

    \par Description:
    returns mean value for surface
*/
vec * surf_mean(const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_area_mean \ref str "area_name" \ref str "surface_name"

    \par Description:
    returns mean value for surface in area
*/
vec * surf_area_mean(const char * area_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mask_mean \ref str "mask_name" \ref str "surface_name"

    \par Description:
    returns mean value for surface where mask is "true"
*/
vec * surf_mask_mean(const char * mask_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_wmean \ref str "wsurface_name" \ref str "surface_name"

    \par Description:
    returns weighted mean value for surface
*/
vec * surf_wmean(const char * wsurface_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_area_wmean \ref str "area_name" \ref str "wsurface_name" \ref str "surface_name"

    \par Description:
    returns weighted mean value for surface in area, where wsurface - weight function
*/
vec * surf_area_wmean(const char * area_name = "*", const char * wsurface_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mask_wmean \ref str "mask_name" \ref str "wsurface_name" \ref str "surface_name"

    \par Description:
    returns weighted mean value for surface where mask is "true", wsurface - weight surface
*/
vec * surf_mask_wmean(const char * mask_name = "*", const char * wsurface_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_sum \ref str "surface_name"

    \par Description:
    returns sum of all surface cell values
*/
vec * surf_sum(const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_sum_area \ref str "area_name" \ref str "surface_name"

    \par Description:
    returns sum of all surface cells values in area
*/
vec * surf_sum_area(const char * area_name = "*",  const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_cells_in_area \ref str "area_name" \ref str "surface_name"

    \par Description:
    returns number of cells in area
*/
intvec * surf_cells_in_area(const char * area_name = "*",  const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_std mean \ref str "surface_name"

    \par Description:
    calculates standard deviation for surface cells values with respect to surface mean value
*/
vec * surf_std(REAL mean, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_plus \ref str "surface1_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 + surface2
*/
boolvec * surf_plus(const char * surface1_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    bool surf_plus_area(const char * surface1_name, const char * area_name, const char * surface2_name);
   
    \par Tcl syntax:
    surf_plus_area \ref str "surface1_name" \ref str "area_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 + surface2
*/
boolvec * surf_plus_area(const char * surface1_name, const char * area_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_minus \ref str "surface1_name" \ref str "surface2_name"
    
    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 - surface2
*/
boolvec * surf_minus(const char * surface1_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_minus_area \ref str "surface1_name" \ref str "area_name" \ref str "surface2_name"
    
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 - surface2
*/
boolvec * surf_minus_area(const char * surface1_name, const char * area_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mult \ref str "surface1_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 * surface2
*/
boolvec * surf_mult(const char * surface1_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mult_area \ref str "surface1_name" \ref str "area_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 * surface2
*/
boolvec * surf_mult_area(const char * surface1_name, const char * area_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mult \ref str "surface1_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface1 / surface2
*/
boolvec * surf_div(const char * surface1_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_div_area \ref str "surface1_name" \ref str "area_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface1 / surface2
*/
boolvec * surf_div_area(const char * surface1_name, const char * area_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_set \ref str "surface1_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface1 = surface2
*/
boolvec * surf_set(const char * surface1_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_set_area \ref str "surface1_name" \ref str "area_name" \ref str "surface2_name"

    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface1 = surface2
*/
boolvec * surf_set_area(const char * surface1_name, const char * area_name, const char * surface2_name);

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_plus_value val \ref str "surface_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface + val
*/
boolvec * surf_plus_value(REAL val, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_plus_value_area val \ref str "area_name" \ref str "surface_name"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface + val
*/
boolvec * surf_plus_value_area(REAL val, const char * surface_name = "*", const char * area_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_minus_value val \ref str "surface_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface - val
*/
boolvec * surf_minus_value(REAL val, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_minus_value_area val \ref str "area_name" \ref str "surface_name"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface - val
*/
boolvec * surf_minus_value_area(REAL val, const char * area_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mult_value val \ref str "surface_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface * val
*/
boolvec * surf_mult_value(REAL val, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_mult_value_area val \ref str "area_name" \ref str "surface_name"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface * val
*/
boolvec * surf_mult_value_area(REAL val, const char * area_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_div_value val \ref str "surface_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface = surface / val
*/
boolvec * surf_div_value(REAL val, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_div_value_area val \ref str "area_name" \ref str "surface_name"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = surface / val
*/
boolvec * surf_div_value_area(REAL val, const char * area_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_set_value val \ref str "surface_name"

    \par Description:
    Performs operation with surfaces cells values:
    surface = val
*/
boolvec * surf_set_value(REAL val, const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_set_value_area val \ref str "area_name" \ref str "surface_name"
      
    \par Description:
    Performs operation with surfaces cells values for cells in area:
    surface = val
*/
boolvec * surf_set_value_area(const char * val, const char * area_name = "*", const char * surface_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_filter_by_mask \ref str "surface_name" \ref str "mask_name"

    \par Description:
    makes all cells values undefined for which \ref d_mask is false
*/
boolvec * surf_filter_by_mask(const char * surface_name = "*", const char * mask_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_filter_in_area \ref str "surface_name" \ref str "area_name"

    \par Description:
    makes all cells values undefined which are inside of \ref d_area
*/
boolvec * surf_filter_in_area(const char * surface_name = "*", const char * area_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_filter_out_area \ref str "surface_name" \ref str "area_name"

    \par Description:
    makes all cells values undefined which are outside of \ref d_area
*/
boolvec * surf_filter_out_area(const char * surface_name = "*", const char * area_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_filter_by_surf eps \ref str "surface1_name" \ref str "surface2_name"

    \par Description:
    modifies surface1 cells values. Makes cells values undefined if \f$ |f_1(x,y) - f_2(x,y)| > \varepsilon \f$, 
    where $f_1(x,y)$ - first surface, $f_2(x,y)$ - second surface
*/
boolvec * surf_filter_by_surf(REAL eps, const char * surface1_name = "*", const char * surface2_name = "*");

/*! \ingroup tcl_surf_math
    \par Tcl syntax:
    surf_swapxy \ref str "surface_name" 

    \par Description:
    swaps X and Y coordinates
*/
boolvec * surf_swapxy(const char * surface_name = "*");

//
// WAVELETS SECTION
//

/*! \ingroup tcl_surf_math_wavan
    \par Tcl syntax:
    surf_get_details_level \ref str "surface_name"

    \par Description:
    returns the depth of applied wavelet decompositions for surface
*/
intvec * surf_get_details_level(const char * surface_name = "*");

/*! \ingroup tcl_surf_math_wavan
    \par Tcl syntax: 
    surf_decomp \ref str "surface_name"

    \par Description:
    makes one wavelet-decomposition for surface 
*/
boolvec * surf_decomp(const char * surface_name = "*");

/*! \ingroup tcl_surf_math_wavan
    \par Tcl syntax:
    surf_auto_decomp eps \ref str "surface_name"

    \par Description:
    calls \ref surf_decomp() "surf_decomp" until difference between original surface norm and decomposed surface norm
    will be lower than eps
*/
boolvec * surf_auto_decomp(REAL eps, const char * surface_name = "*");

/*! \ingroup tcl_surf_math_wavan
    \par Tcl syntax:
    surf_recons \ref str "surface_name"

    \par Description:
    makes one wavelet-reconstruction for surface 
*/
boolvec * surf_recons(const char * surface_name = "*");

/*! \ingroup tcl_surf_math_wavan
    \par Tcl syntax: 
    surf_full_recons \ref str "surface_name"

    \par Description:
    makes all possible wavelet-reconstructions for surface (recontructs original surface)
*/
boolvec * surf_full_recons(const char * surface_name = "*");

//
// CONVERTING
//

/*! \ingroup tcl_surf_conv
    \par Tcl syntax:
    surf_to_pnts \ref str "surface_name"

    \par Description:
    transforms \ref d_surf "surface" to \ref d_points "points"
*/
boolvec * surf_to_pnts(const char * surface_name = "*");

/*! \ingroup tcl_surf_conv
    \par Tcl syntax:
    surf_to_mask true_from true_to \ref str "surface_name"
      
    \par Description:
    makes \ref d_mask "mask" by surface. Cells values will be converted to "true" values if their
    values are in interval [true_from, true_to], else to "false" values.
*/
boolvec * surf_to_mask(REAL true_from, REAL true_to, const char * surface_name = "*");

/*! \ingroup tcl_surf_conv
    \par Tcl syntax:
    surf_trace_cntr \ref str "surface_name" step from to 

    \par Description:
    Converts surface to contours using isoline tracing algorithm.
    \param surface_name \ref str "name" of surfaces for converting
    \param from starting value for isolines. If not set then determines automatically.
    \param step step between isolines values. If not set then determines automatically.
    \param to ending value for isolines. If not set then determines automatically.
*/
boolvec * surf_trace_cntr(const char * surface_name = "*", REAL step = FLT_MAX, REAL from = FLT_MAX, REAL to = FLT_MAX);


//
// OTHER
//

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_getCountX \ref str "surface_name"

    \par Description:
    returns the amount of X-nodes for surface
*/
intvec * surf_getCountX(const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_getCountY \ref str "surface_name"

    \par Description:
    returns the amount of Y-nodes for surface
*/
intvec * surf_getCountY(const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_getStepX \ref str "surface_name"
    
    \par Description:
    returns step between X-nodes for surface
*/
vec * surf_getStepX(const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_getStepY \ref str "surface_name"
    
    \par Description:
    returns step between Y-nodes for surface
*/
vec * surf_getStepY(const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_undef new_undef_value \ref str "surface_name"
    
    \par Description:
    sets undefined value for surface
*/
boolvec * surf_undef(REAL new_undef_value, const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_info \ref str "surface_name"
    
    \par Description:
    prints some info about surface
*/
void surf_info(const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_getName \ref str "surface_name"
    
    \par Description:
    returns name of surface 
*/
strvec * surf_getName(const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_getNameAt position

    \par Description:
    returns name of \ref d_surf at position "pos"
*/
const char * surf_getNameAt(int pos);

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_getId \ref str "surface_name"
    
    \par Description:
    returns unique surface identificator 
*/
intvec * surf_getId(const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_setName "new_name" \ref str "surface_name"
    
    \par Description:
    sets name for surface
*/
boolvec * surf_setName(const char * new_name, const char * surface_name = "*");

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_size
    
    \par Description:
    returns amount of surfaces in surfaces
*/
int surf_size();

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surfs_info
    
    \par Description:
    prints information about surfaces in surfaces
*/
void surfs_info();

/*! \ingroup tcl_surf_other
    \par Tcl syntax:
    surf_del \ref str "surface_name"

    \par Description:
    removes \ref d_surf "surface" from memory
*/
void surf_del(const char * surface_name = "*");

}; // namespace surfit;

#endif

