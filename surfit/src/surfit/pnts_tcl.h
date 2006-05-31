
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

////////////////////////////////////////////////
////////////////////////////////////////////////
//                points io                   //
////////////////////////////////////////////////
////////////////////////////////////////////////

///////////////
// saveload

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_load(const char * filename, const char * pntsname = NULL);
    
    \par Tcl syntax:
    pnts_load "filename" "pntsname"

    \par Description:
    reads \ref d_points "points" named 'pntsname' from surfit datafile

    \par Example:
    pnts_load "C:\\my_points.dat" "my_points"
*/
bool pnts_load(const char * filename, const char * pntsname = NULL);

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_read(const char * filename, const char * pntsname, int col1, int col2, int col3, int col4, 
	       const char * delimiter, int skip_lines, int grow_by);
    
    \par Tcl syntax:
    pnts_read "filename" "pntsname" col1 col2 col3 col4 "delimiter" skip_lines grow_by

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
bool pnts_read(const char * filename, const char * pntsname = NULL, 
	       int col1 = 1, int col2 = 2, int col3 = 3, int col4 = 0, 
	       const char * delimiter = " \t", int skip_lines = 0, int grow_by = 250);

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_load_shp(const char * filename, const char * pntsname = NULL, const char * param = "VALUE");
    
    \par Tcl syntax:
    pnts_load_shp "filename" "pntsname" "param"

    \par Description:
    reads \ref d_points "points" from ESRI shape file and names them "pntsname"

    \par Example:
    pnts_load_shp "C:\\my_points.shp" "my_points" "VALUE"
*/
bool pnts_load_shp(const char * filename, const char * pntsname = NULL, const char * param = "VALUE");

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_save(const char * filename, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_save "filename" "points_name_or_position"

    \par Description:
    saves \ref d_points "points" to surfit datafile

    \par Example
    pnts_save "C:\\points.dat" "my_points"
*/
bool pnts_save(const char * filename, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_write(const char * filename, const char * points_name_or_position = "0", const char * delimiter = "\t");
    
    \par Tcl syntax:
    pnts_write "filename" "delimiter" "points_name_or_position"

    \par Description:
    saves \ref d_points "points" to formatted text file
*/
bool pnts_write(const char * filename, const char * points_name_or_position = "0", const char * delimiter = "\t");

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_save_shp(const char * filename, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_save_shp "filename" "points_name_or_position"

    \par Description:
    saves \ref d_points "points" to ESRI shapefile format

    \par Example
    pnts_save_shp "C:\\points.shp" "my_points"
*/
bool pnts_save_shp(const char * filename, const char * points_name_or_position = "0");

//////////////
// math

/*! \ingroup tcl_pnts_math
    \fn bool pnts_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_transform shiftX scaleX shiftY scaleY "points_name_or_position"

    \par Description:
    makes geometrical transform on \ref d_points "points" (shifting and scaling). 
*/
bool pnts_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_inverse_transfort shiftX scaleX shiftY scaleY "points_name_or_position"

    \par Description:
    makes inverse to \ref pnts_transform operation
*/
bool pnts_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_rotate(REAL centerX, REAL centerY, REAL angle, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_rotate centerX centerY angle "points_name_or_position"
     
    \par Description:
    rotates \ref d_points "points" around point with coords (centerX, centerY)
*/
bool pnts_rotate(REAL centerX, REAL centerY, REAL angle, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_filter_by_mask(const char * points_name_or_position = "0", const char * mask_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_filter_by_mask "points_name_or_position" "mask_name_or_position"

    \par Description:
    removes all points from \ref d_points "points" dataset for which \ref d_mask is undefined
*/
bool pnts_filter_by_mask(const char * points_name_or_position = "0", const char * mask_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_filter_in_area(const char * points_name_or_position = "0", const char * area_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_filter_in_area "points_name_or_position" "area_name_or_position"

    \par Description:
    removes all points from \ref d_points "points" dataset which are inside of \ref d_area
*/
bool pnts_filter_in_area(const char * points_name_or_position = "0", const char * area_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_filter_out_area(const char * points_name_or_position = "0", const char * area_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_filter_out_area "points_name_or_position" "area_name_or_position"

    \par Description:
    removes all points from \ref d_points "points" dataset which are outside of \ref d_area
*/
bool pnts_filter_out_area(const char * points_name_or_position = "0", const char * area_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_filter_by_surf(REAL eps, const char * points_name_or_position = "0", const char * surf_name_or_position = "0")
    
    \par Tcl syntax:
    pnts_filter_by_surf eps "points_name_or_position" "surf_name_or_position"

    \par Description:
    removes points from \ref d_points "points" dataset, if \f$ |z - f(x,y)| > \varepsilon \f$, 
    where (x,y,z) - \ref d_points "data points", f(x,y) - \ref d_surf value at point (x,y)
*/
bool pnts_filter_by_surf(REAL eps, const char * points_name_or_position = "0", const char * surf_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_update_by_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_update_by_surf "points_name_or_position" "surf_name_or_position"

    \par Description:
    sets points values to z = f(x,y), where (x,y,z) - \ref d_points "data points", 
    f(x,y) - \ref d_surf value at point (x,y)
*/
bool pnts_update_by_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_minx(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_minz "points_name_or_position"

    \par Description:
    returns minimum X value of all data-points
*/
REAL pnts_minx(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_maxx(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_maxx "points_name_or_position"

    \par Description:
    returns maximum X value of all data-points
*/
REAL pnts_maxx(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_miny(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_miny "poinst_name_or_position"

    \par Description:
    returns minimum Y value of all data-points
*/
REAL pnts_miny(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_maxy(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_maxy "points_name_or_position"

    \par Description:
    returns maximum Y value of all data-points
*/
REAL pnts_maxy(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_minz(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_minz "points_name_or_position"

    \par Description:
    returns minimum Z value of all data-points
*/
REAL pnts_minz(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_maxz(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_maxz "points_name_or_position"

    \par Description:
    returns maximum Z value of all data-points
*/
REAL pnts_maxz(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_add_noise(REAL std, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_add_noise std "points_name_or_position"

    \par Description:
    adds noise distributed as N(0,std) to \ref d_points "points"
*/
bool pnts_add_noise(REAL std, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_mean(const char * points_name_or_position = "0")
    
    \par Tcl syntax:
    pnts_mean "points_name_or_position"

    \par Description:
    calculates mean value of all data-points in \ref d_points "points"
*/
REAL pnts_mean(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn REAL pnts_std(REAL mean, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_std mean "points_name_or_position"

    \par Description:
    calculates standart deviation value from mean value (for \ref d_points "points")
*/
REAL pnts_std(REAL mean, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_plus(const char * points_name_or_position1, const char * points_name_or_position2);
    
    \par Tcl syntax:
    pnts_plus "points_name_or_position1" "points_name_or_position2"

    \par Description:
    calculates A = A+B, where A - points at pos1, B - points at pos2
*/
bool pnts_plus(const char * points_name_or_position1, const char * points_name_or_position2);

/*! \ingroup tcl_pnts_math
    \fn bool pnts_minus(const char * points_name_or_position1, const char * points_name_or_position2);
    
    \par Tcl syntax:
    pnts_minus "points_name_or_position1" "points_name_or_position2"

    \par Description:
    calculates A = A-B, where A - points at pos1, B - points at pos2
*/
bool pnts_minus(const char * points_name_or_position1, const char * points_name_or_position2);

/*! \ingroup tcl_pnts_math
    \fn bool pnts_mult(const char * points_name_or_position1, const char * points_name_or_position2);
    
    \par Tcl syntax:
    pnts_mult "points_name_or_position1" "points_name_or_position2"

    \par Description:
    calculates A = A*B, where A - points at pos1, B - points at pos2
*/
bool pnts_mult(const char * points_name_or_position1, const char * points_name_or_position2);

/*! \ingroup tcl_pnts_math
    \fn bool pnts_div(const char * points_name_or_position1, const char * points_name_or_position2);
    
    \par Tcl syntax:
    pnts_div "points_name_or_position1" "points_name_or_position2"

    \par Description:
    calculates A = A/B, where A - points at pos1, B - points at pos2
*/
bool pnts_div(const char * points_name_or_position1, const char * points_name_or_position2);

/*! \ingroup tcl_pnts_math
    \fn bool pnts_set(const char * points_name_or_position1, const char * points_name_or_position2);
    
    \par Tcl syntax:
    pnts_set "points_name_or_position1" "points_name_or_position2"

    \par Description:
    calculates A = B, where A - points at pos1, B - points at pos2
*/
bool pnts_set(const char * points_name_or_position1, const char * points_name_or_position2);

/*! \ingroup tcl_pnts_math
    \fn bool pnts_plus_real(REAL val, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_plus_real val "points_name_or_position"

    \par Description:
    calculates A = A+B, where A - this class, B - some numeric
*/
bool pnts_plus_real(REAL val, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_minus_real(REAL val, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_minus_real val "points_name_or_position"

    \par Description:
    calculates A = A-B, where A - this class, B - some numeric
*/
bool pnts_minus_real(REAL val, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_mult_real(REAL val, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_mult_real val "points_name_or_position"

    \par Description:
    calculates A = A*B, where A - this class, B - some numeric
*/
bool pnts_mult_real(REAL val, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_div_real(REAL val, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_div_real val "points_name_or_position"

    \par Description:
    calculates A = A/B, where A - this class, B - some numeric
*/
bool pnts_div_real(REAL val, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_set_real(REAL val, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_set_real val "points_name_or_position"

    \par Description:
    calculates A = B, where A - this class, B - some numeric
*/
bool pnts_set_real(REAL val, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_plus_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_plus_surf "points_name_or_position" "surf_name_or_position"

    \par Description:
    calculates A = A+B, where A - points at points_name_or_position, B - surface values at points
*/
bool pnts_plus_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_minus_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_minus_surf "points_name_or_position" "surf_name_or_position"

    \par Description:
    calculates A = A-B, where A - points at points_name_or_position, B - surface values at points
*/
bool pnts_minus_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_mult_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_mult_surf "points_name_or_position" "surf_name_or_position"

    \par Description:
    calculates A = A*B, where A - points at points_name_or_position, B - surface values at points
*/
bool pnts_mult_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_div_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_div_surf "points_name_or_position" "surf_name_or_position"

    \par Description:
    calculates A = A/B, where A - points at points_name_or_position, B - surface values at points
*/
bool pnts_div_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");

/*! \ingroup tcl_pnts_math
    \fn bool pnts_set_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_set_surf "points_name_or_position" "surf_name_or_position"

    \par Description:
    calculates A = B, where A - points at points_name_or_position, B - surface values at points
*/
bool pnts_set_surf(const char * points_name_or_position = "0", const char * surf_name_or_position = "0");

//////////////
// other

/*! \ingroup tcl_pnts_other
    \fn int pnts_getCount(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_getCount "points_name_or_position"

    \par Description:
    returns \ref d_points "points" size (number of points)
*/
int pnts_getCount(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_other
    \fn const char * pnts_getName(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_getName "points_name_or_position"

    \par Description:
    returns name of \ref d_points "points" dataset
*/
const char * pnts_getName(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_other
    \fn bool pnts_setName(const char * new_name, const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_setName "new_name" "points_name_or_position"

    \par Description:
    sets name of \ref d_points "points" to new_name
*/
bool pnts_setName(const char * new_name, const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_other
    \fn bool pnts_concat(const char * points_name_or_position1, const char * points_name_or_position2);
    
    \par Tcl syntax:
    pnts_concat "points_name_or_position1" "points_name_or_position2"

    \par Description:
    adds scattered data-points from points at pos2 to points at pos1
*/
bool pnts_concat(const char * points_name_or_position1, const char * points_name_or_position2);

/*! \ingroup tcl_pnts_other
    \fn int pnts_size();
    
    \par Tcl syntax:
    pnts_size

    \par Description:
    returns number of \ref d_points "points" datasets
*/
int pnts_size();

/*! \ingroup tcl_pnts_other
    \fn void pnts_info();
    
    \par Tcl syntax:
    pnts_info

    \par Description:
    prints info about all \ref d_points "points" datasets
*/
void pnts_info();

/*! \ingroup tcl_pnts_other
    \fn bool pnts_del(const char * points_name_or_position = "0");
    
    \par Tcl syntax:
    pnts_del "points_name_or_position"

    \par Description:
    removes \ref d_points "points" from memory
    
    \param points_name_or_position points name, or points position number

    \par Examples:
    \li pnts_del "my_points"
    \li pnts_del 0

*/
bool pnts_del(const char * points_name_or_position = "0");

/*! \ingroup tcl_pnts_other
    \fn bool pnts_delall();
    
    \par Tcl syntax:
    pnts_delall

    \par Description:
    removes all points objects from memory
*/
bool pnts_delall();

}; // namespace surfit;

#endif

