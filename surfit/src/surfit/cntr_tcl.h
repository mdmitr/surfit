
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
    reads \ref d_cntr from formatted text file
    \par Tcl syntax:
    cntr_read "filename" "cntrname" columns col1 col2 col3 "delimiters" skip_lines
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
SURFIT_EXPORT
bool cntr_read(const char * filename, const char * cntrname, 
    	       int col1=1, int col2=2, int col3=3,
	       const char * delimiters=" \t", int skip_lines = 0, int grow_by=250);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_write(const char * filename, const char * cntr_name_or_position = "0", const char * delimiter = "\t");
    saves \ref d_cntr "contour" to formatted text file. 
    \par Tcl syntax:
    cntr_write "filename" "cntr_name_or_position" "delimiter"
    \par Example:
    cntr_write "C:\\my_cntr.txt" "my_cntr"
*/
SURFIT_EXPORT
bool cntr_write(const char * filename, const char * cntr_name_or_position = "0", const char * delimiter = "\t");

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save(const char * filename, const char * cntr_name_or_position = "0");
    saves \ref d_cntr "contour" to surfit datafile
    \par Tcl syntax:
    cntr_save "filename" "cntr_name_or_position"
    \par Example:
    cntr_save "C:\\my_cntr.dat" "my_cntr"
*/
SURFIT_EXPORT
bool cntr_save(const char * filename, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_load(const char * filename, const char * cntrname = NULL);
    reads \ref d_cntr "countour" named 'cntrname' from surfit datafile
    \par Tcl syntax:
    cntr_load "filename" "cntrname"
    \par Example:
    cntr_load "C:\\my_cntr.dat" "my_cntr"
*/
SURFIT_EXPORT
bool cntr_load(const char * filename, const char * cntrname = NULL);

///////////////
// math

/*! \ingroup tcl_cntr_math
    \fn bool cntr_plus_real(REAL value, const char * cntr_name_or_position = "0");
    adds real value to \ref d_cntr "contour" values
    \par Tcl syntax:
    cntr_plus_real value "cntr_name_or_position"
*/
SURFIT_EXPORT
bool cntr_plus_real(REAL value, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_minus_real(REAL value, const char * cntr_name_or_position = "0");
    deducts real value from \ref d_cntr "contour" values
    \par Tcl syntax:
    cntr_minus_real value "cntr_name_or_position"
*/
SURFIT_EXPORT
bool cntr_minus_real(REAL value, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_mult_real(REAL value, const char * cntr_name_or_position = "0");
    multiplies \ref d_cntr "contour" values with real value
    \par Tcl syntax:
    cntr_mult_real value "cntr_name_or_position"
*/
SURFIT_EXPORT
bool cntr_mult_real(REAL value, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_div_real(REAL value, const char * cntr_name_or_position = "0");
    divides \ref d_cntr "contour" values with real value
    \par Tcl syntax:
    cntr_div_real value "cntr_name_or_position"
*/
SURFIT_EXPORT
bool cntr_div_real(REAL value, const char * cntr_name_or_position = "0");

///////////////
// convers

/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_curv(const char * cntr_name_or_position = "0");
    makes \ref d_curv "curve" from \ref d_cntr "contour"
    \par Tcl syntax:
    cntr_to_curv "cntr_name_or_position"
*/
SURFIT_EXPORT
bool cntr_to_curv(const char * cntr_name_or_position = "0");

///////////////
// other

/*! \ingroup tcl_cntr_other
    \fn const char * cntr_getName(const char * cntr_name_or_position = "0");
    returns name of \ref d_cntr "contour"
    \par Tcl syntax:
    cntr_getName cntr_position
*/
SURFIT_EXPORT
const char * cntr_getName(const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr_other
    \fn bool cntr_setName(const char * new_name, const char * cntr_name_or_position = "0");
    sets name of \ref d_cntr "contour"
    \par Tcl syntax:
    cntr_setName "new_name" "cntr_name_or_position"
*/
SURFIT_EXPORT
bool cntr_setName(const char * new_name, const char * cntr_name_or_position = "0");

/*! \ingroup tcl_cntr
    \fn bool cntr_delall();
    removes all \ref d_cntr "contours" from memory
    \par Tcl syntax:
    cntr_delall
*/
SURFIT_EXPORT
bool cntr_delall();

/*! \ingroup tcl_cntr
    \fn bool cntr_del(const char * cntr_name_or_position);
    removes \ref d_cntr "contour" from memory
    \par Tcl syntax:
    cntr_del "cntr_name_or_position"
*/
SURFIT_EXPORT
bool cntr_del(const char * cntr_name_or_position);

/*! \ingroup tcl_cntr
    \fn int cntr_size();
    returns number of \ref d_cntr "contours" in memory
    \par Tcl syntax:
    cntr_size
*/
SURFIT_EXPORT
int cntr_size();

/*! \ingroup tcl_cntr
    \fn void cntrs_info();
    prints information about all \ref d_cntr "contours" in memory
    \par Tcl syntax:
    cntrs_info
*/
SURFIT_EXPORT
void cntrs_info();

}; // namespace surfit;

#endif

