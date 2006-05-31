
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

#ifndef __surfit_cntr_tcl_included__
#define __surfit_cntr_tcl_included__

namespace surfit {

class cntr;

//////////////////
// save and load

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_read(const char * filename, const char * cntrname, int col1=1, int col2=2, int col3=3, const char * delimiters = " \t", int skip_lines = 0, int grow_by = 250);
    
    \par Tcl syntax:
    cntr_read "filename" "cntrname" columns col1 col2 col3 "delimiters" skip_lines

    \par Description:
    reads \ref d_cntr from formatted text file

    \param filename name of formatted text file
    \param cntrname name for \ref d_cntr "contour" object
    \param col1 column with X coordinates
    \param col2 column with Y coordinates
    \param col3 colimn with Z values
    \param delimiters delimiter between columns. May be " ", "\t", "," or other symbols
    \param skip_lines number of lines to skip header
    \param grow_by =250
    
    \par Example:
    cntr_read "C:\\my_cntr.txt" "my_cntr"
*/
bool cntr_read(const char * filename, const char * cntrname, 
    	       int col1=1, int col2=2, int col3=3,
	       const char * delimiters=" \t", int skip_lines = 0, int grow_by=250);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_load(const char * filename, const char * cntrname = NULL);
    
    \par Tcl syntax:
    cntr_load "filename" "cntrname"

    \par Description:
    reads \ref d_cntr "countour" named 'cntrname' from surfit datafile

    \par Example:
    cntr_load "C:\\my_cntr.dat" "my_cntr"
*/
bool cntr_load(const char * filename, const char * cntrname = NULL);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_load_shp(const char * filename, const char * cntrname = NULL);
    
    \par Tcl syntax:
    cntr_load_shp "filename" "cntrname"

    \par Description:
    reads \ref d_cntr "countour" named 'cntrname' from ERSI shape file

    \par Example:
    cntr_load_shp "C:\\my_cntr.shp" "my_cntr"
*/
bool cntr_load_shp(const char * filename, const char * cntrname = NULL);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntrs_load_shp(const char * filename);
    
    \par Tcl syntax:
    cntrs_load_shp "filename" "cntrname"

    \par Description:
    reads all \ref d_cntr "countours" from ERSI shape file

    \par Example:
    cntrs_load_shp "C:\\my_cntr.shp"
*/
bool cntrs_load_shp(const char * filename);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_write(const char * filename, const char * cntr_name_or_position = "0", const char * delimiter = "\t");
    
    \par Tcl syntax:
    cntr_write "filename" "cntr_name_or_position" "delimiter"

    \par Description:
    saves \ref d_cntr "contour" to formatted text file. 

    \par Example:
    cntr_write "C:\\my_cntr.txt" "my_cntr"
*/
bool cntr_write(const char * filename, const char * cntr_name_or_position = "0", const char * delimiter = "\t");

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save(const char * filename, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_save "filename" "cntr_name_or_position"

    \par Description:
    saves \ref d_cntr "contour" to surfit datafile

    \par Example:
    cntr_save "C:\\my_cntr.dat" "my_cntr"
*/
bool cntr_save(const char * filename, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save_shp(const char * filename, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_save_shp "filename" "cntr_name_or_position"

    \par Description:
    saves \ref d_cntr "contour" to ESRI shape file

    \par Example:
    cntr_save_shp "C:\\my_cntr.shp" "my_cntr"
*/
bool cntr_save_shp(const char * filename, const char * cntr_name_or_position = "0");

///////////////
// math

/*! \ingroup tcl_cntr_math
    \fn bool cntr_plus_real(REAL value, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_plus_real value "cntr_name_or_position"

    \par Description:
    adds real value to \ref d_cntr "contour" values
*/
bool cntr_plus_real(REAL value, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_minus_real(REAL value, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_minus_real value "cntr_name_or_position"

    \par Description:
    deducts real value from \ref d_cntr "contour" values
*/
bool cntr_minus_real(REAL value, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_mult_real(REAL value, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_mult_real value "cntr_name_or_position"

    \par Description:
    multiplies \ref d_cntr "contour" values with real value
*/
bool cntr_mult_real(REAL value, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_div_real(REAL value, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_div_real value "cntr_name_or_position"

    \par Description:
    divides \ref d_cntr "contour" values with real value
*/
bool cntr_div_real(REAL value, const char * cntr_name_or_position = "0");

///////////////
// convers

/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_curv(const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_to_curv "cntr_name_or_position"

    \par Description:
    makes \ref d_curv "curve" from \ref d_cntr "contour"
*/
bool cntr_to_curv(const char * cntr_name_or_position = "0");

///////////////
// other

/*! \ingroup tcl_cntr_other
    \fn const char * cntr_getName(const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_getName cntr_position

    \par Description:
    returns name of \ref d_cntr "contour"
*/
const char * cntr_getName(const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_other
    \fn bool cntr_setName(const char * new_name, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_setName "new_name" "cntr_name_or_position"

    \par Description:
    sets name of \ref d_cntr "contour"
*/
bool cntr_setName(const char * new_name, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_other
    \fn bool cntr_delall();
    
    \par Tcl syntax:
    cntr_delall

    \par Description:
    removes all \ref d_cntr "contours" from memory
*/
bool cntr_delall();

/*! \ingroup tcl_cntr_other
    \fn bool cntr_del(const char * cntr_name_or_position);
    
    \par Tcl syntax:
    cntr_del "cntr_name_or_position"

    \par Description:
    removes \ref d_cntr "contour" from memory
*/
bool cntr_del(const char * cntr_name_or_position);

/*! \ingroup tcl_cntr_other
    \fn int cntr_size();
    
    \par Tcl syntax:
    cntr_size

    \par Description:
    returns number of \ref d_cntr "contours" in memory
*/
int cntr_size();

/*! \ingroup tcl_cntr_other
    \fn void cntrs_info();
    
    \par Tcl syntax:
    cntrs_info

    \par Description:
    prints information about all \ref d_cntr "contours" in memory
*/
void cntrs_info();

}; // namespace surfit;

#endif

