
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

#ifndef __surfit_pnts_tcl__
#define __surfit_pnts_tcl__

namespace surfit {

class vec;
class d_grid;
class d_points;
class boolvec;
class strvec;
class intvec;

////////////////////////////////////////////////
////////////////////////////////////////////////
//                points io                   //
////////////////////////////////////////////////
////////////////////////////////////////////////

///////////////
// saveload

/*! \ingroup tcl_pnts_save_load
    \par Tcl syntax:
    pnts_load \ref file "filename" "pntsname"

    \par Description:
    reads \ref d_points "points" named 'pntsname' from surfit datafile

    \par Example:
    pnts_load "C:\\my_points.dat" "my_points"
*/
boolvec * pnts_load(const char * filename, const char * pntsname = NULL);

/*! \ingroup tcl_pnts_save_load
    \par Tcl syntax:
    pnts_read \ref file "filename" "pntsname" col1 col2 col3 col4 "delimiter" skip_lines grow_by

    \par Description:
    reads \ref d_points "points" from formatted text file

    \param filename name of formatted text file
    \param pntsname name for \ref d_points "points" object
    \param col1 column with X coordinates
    \param col2 column with Y coordinates
    \param col3 colimn with Z values
    \param col4 column with names. If col4 equal to 0, then no names will be read
    \param delimiter delimiter between columns. May be " ", "\t", "," or other symbols
    \param skip_lines number of lines to skip header
    \param grow_by =250
    
    \par Examples:
    \li pnts_read "C:\\points.txt" "points" 1 2 3 0 " 	" 0 
    \li pnts_read "C:\\points_geq.txt" "points_geq" 1 2 3 3 " 	" 0 
*/
boolvec * pnts_read(const char * filename, const char * pntsname = NULL, 
	       int col1 = 1, int col2 = 2, int col3 = 3, int col4 = 0, 
	       const char * delimiter = " \t", int skip_lines = 0, int grow_by = 250);

/*! \ingroup tcl_pnts_save_load
    \par Tcl syntax:
    pnts_save "filename" \ref str "points_name"

    \par Description:
    saves \ref d_points "points" to surfit datafile

    \par Example
    pnts_save "C:\\points.dat" "my_points"
*/
boolvec * pnts_save(const char * filename, const char * points_name = "*");

/*! \ingroup tcl_pnts_save_load
    \par Tcl syntax:
    pnts_write "filename" \ref str "points_name" "delimiter" 

    \par Description:
    saves \ref d_points "points" to formatted text file
*/
boolvec * pnts_write(const char * filename, const char * points_name = "*", const char * delimiter = "\t");

//////////////
// math

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_transform shiftX scaleX shiftY scaleY \ref str "points_name"

    \par Description:
    makes geometrical transform on \ref d_points "points" (shifting and scaling). 
*/
boolvec * pnts_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_inverse_transfort shiftX scaleX shiftY scaleY \ref str "points_name"

    \par Description:
    makes inverse to \ref pnts_transform() "pnts_transform" operation
*/
boolvec * pnts_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_rotate centerX centerY angle \ref str "points_name"
     
    \par Description:
    rotates \ref d_points "points" around point with coords (centerX, centerY)
*/
boolvec * pnts_rotate(REAL centerX, REAL centerY, REAL angle, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_filter_by_mask \ref str "points_name" \ref str "mask_name"

    \par Description:
    removes all points from \ref d_points "points" dataset for which \ref d_mask is undefined
*/
boolvec * pnts_filter_by_mask(const char * points_name = "*", const char * mask_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_filter_in_area \ref str "points_name" \ref str "area_name"

    \par Description:
    removes all points from \ref d_points "points" dataset which are inside of \ref d_area
*/
boolvec * pnts_filter_in_area(const char * points_name = "*", const char * area_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_filter_out_area \ref str "points_name" \ref str "area_name"

    \par Description:
    removes all points from \ref d_points "points" dataset which are outside of \ref d_area
*/
boolvec * pnts_filter_out_area(const char * points_name = "*", const char * area_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_filter_by_surf eps \ref str "points_name" \ref str "surf_name"

    \par Description:
    removes points from \ref d_points "points" dataset, if \f$ |z - f(x,y)| > \varepsilon \f$, 
    where (x,y,z) - \ref d_points "data points", f(x,y) - \ref d_surf value at point (x,y)
*/
boolvec * pnts_filter_by_surf(REAL eps, const char * points_name = "*", const char * surf_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_update_by_surf \ref str "points_name" \ref str "surf_name"

    \par Description:
    sets points values to z = f(x,y), where (x,y,z) - \ref d_points "data points", 
    f(x,y) - \ref d_surf value at point (x,y)
*/
boolvec * pnts_update_by_surf(const char * points_name = "*", const char * surf_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_minz \ref str "points_name"

    \par Description:
    returns minimum X value of all data-points
*/
vec * pnts_minx(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_maxx \ref str "points_name"

    \par Description:
    returns maximum X value of all data-points
*/
vec * pnts_maxx(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_miny \ref str "poinst_name"

    \par Description:
    returns minimum Y value of all data-points
*/
vec * pnts_miny(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_maxy \ref str "points_name"

    \par Description:
    returns maximum Y value of all data-points
*/
vec * pnts_maxy(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_minz \ref str "points_name"

    \par Description:
    returns minimum Z value of all data-points
*/
vec * pnts_minz(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_maxz \ref str "points_name"

    \par Description:
    returns maximum Z value of all data-points
*/
vec * pnts_maxz(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_add_noise std \ref str "points_name"

    \par Description:
    adds noise distributed as N(0,std) to \ref d_points "points"
*/
boolvec * pnts_add_noise(REAL std, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_abs \ref str "points_name"

    \par Description:
    calculates absolute values for points
*/
boolvec * pnts_abs(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_mean \ref str "points_name"

    \par Description:
    calculates mean value of all data-points in \ref d_points "points"
*/
vec * pnts_mean(const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_std mean \ref str "points_name"

    \par Description:
    calculates standart deviation value from mean value (for \ref d_points "points")
*/
vec * pnts_std(REAL mean, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_plus \ref str "points_name1" \ref str "points_name2"

    \par Description:
    calculates A = A+B, where A - points at pos1, B - points at pos2
*/
boolvec * pnts_plus(const char * points_name1, const char * points_name2);

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_minus \ref str "points_name1" \ref str "points_name2"

    \par Description:
    calculates A = A-B, where A - points at pos1, B - points at pos2
*/
boolvec * pnts_minus(const char * points_name1, const char * points_name2);

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_mult \ref str "points_name1" \ref str "points_name2"

    \par Description:
    calculates A = A*B, where A - points at pos1, B - points at pos2
*/
boolvec * pnts_mult(const char * points_name1, const char * points_name2);

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_div \ref str "points_name1" \ref str "points_name2"

    \par Description:
    calculates A = A/B, where A - points at pos1, B - points at pos2
*/
boolvec * pnts_div(const char * points_name1, const char * points_name2);

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_set \ref str "points_name1" \ref str "points_name2"

    \par Description:
    calculates A = B, where A - points at pos1, B - points at pos2
*/
boolvec * pnts_set(const char * points_name1, const char * points_name2);

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_plus_real val \ref str "points_name"

    \par Description:
    calculates A = A+B, where A - this class, B - some numeric
*/
boolvec * pnts_plus_real(REAL val, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_minus_real val \ref str "points_name"

    \par Description:
    calculates A = A-B, where A - this class, B - some numeric
*/
boolvec * pnts_minus_real(REAL val, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_mult_real val \ref str "points_name"

    \par Description:
    calculates A = A*B, where A - this class, B - some numeric
*/
boolvec * pnts_mult_real(REAL val, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_div_real val \ref str "points_name"

    \par Description:
    calculates A = A/B, where A - this class, B - some numeric
*/
boolvec * pnts_div_real(REAL val, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_set_real val \ref str "points_name"

    \par Description:
    calculates A = B, where A - this class, B - some numeric
*/
boolvec * pnts_set_real(REAL val, const char * points_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_plus_surf \ref str "points_name" \ref str "surf_name"

    \par Description:
    calculates A = A+B, where A - points at points_name, B - surface values at points
*/
boolvec * pnts_plus_surf(const char * points_name = "*", const char * surf_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_minus_surf \ref str "points_name" \ref str "surf_name"

    \par Description:
    calculates A = A-B, where A - points at points_name, B - surface values at points
*/
boolvec * pnts_minus_surf(const char * points_name = "*", const char * surf_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_mult_surf \ref str "points_name" \ref str "surf_name"

    \par Description:
    calculates A = A*B, where A - points at points_name, B - surface values at points
*/
boolvec * pnts_mult_surf(const char * points_name = "*", const char * surf_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_div_surf \ref str "points_name" \ref str "surf_name"

    \par Description:
    calculates A = A/B, where A - points at points_name, B - surface values at points
*/
boolvec * pnts_div_surf(const char * points_name = "*", const char * surf_name = "*");

/*! \ingroup tcl_pnts_math
    \par Tcl syntax:
    pnts_set_surf \ref str "points_name" \ref str "surf_name"

    \par Description:
    calculates A = B, where A - points at points_name, B - surface values at points
*/
boolvec * pnts_set_surf(const char * points_name = "*", const char * surf_name = "*");

//////////////
// convert

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_to_cntrs \ref str "points_name"

    \par Description:
    converts points to contours
*/
boolvec * pnts_to_cntrs(const char * points_name = "*");

//////////////
// other

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_getCount "points_name"

    \par Description:
    returns \ref d_points "points" size (number of points)
*/
intvec * pnts_getCount(const char * points_name = "*");

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_getName \ref str "points_name"

    \par Description:
    returns name of \ref d_points "points" dataset
*/
strvec * pnts_getName(const char * points_name = "*");

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_getNameAt position

    \par Description:
    returns name of \ref d_points at position "pos"
*/
const char * pnts_getNameAt(int pos);

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_getId \ref str "points_name"
    
    \par Description:
    returns unique points identificator 
*/
intvec * pnts_getId(const char * pntsace_name = "*");

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_setName "new_name" \ref str "points_name"

    \par Description:
    sets name of \ref d_points "points" to new_name
*/
boolvec * pnts_setName(const char * new_name, const char * points_name = "*");

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_concat \ref str "points_name1" \ref str "points_name2"

    \par Description:
    adds scattered data-points from points at pos2 to points at pos1
*/
boolvec * pnts_concat(const char * points_name1, const char * points_name2);

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_size

    \par Description:
    returns number of \ref d_points "points" datasets
*/
int pnts_size();

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_info

    \par Description:
    prints info about all \ref d_points "points" datasets
*/
void pnts_info();

/*! \ingroup tcl_pnts_other
    \par Tcl syntax:
    pnts_del \ref str "points_name"

    \par Description:
    removes \ref d_points "points" from memory
    
    \param points_name points name

    \par Examples:
    \li pnts_del "my_points"
    \li pnts_del 0

*/
void pnts_del(const char * points_name = "*");

}; // namespace surfit;

#endif

