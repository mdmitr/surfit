
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
class boolvec;
class strvec;
class intvec;

//////////////////
// save and load

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_read(const char * filename, const char * cntrname, int col1=1, int col2=2, int col3=3, const char * delimiters = " \t", int skip_lines = 0, int grow_by = 250);
    
    \par Tcl syntax:
    cntr_read \ref file "filename" "cntrname" columns col1 col2 col3 "delimiters" skip_lines

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
boolvec * cntr_read(const char * filename, const char * cntrname, 
    	       int col1=1, int col2=2, int col3=3,
	       const char * delimiters=" \t", int skip_lines = 0, int grow_by=250);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_load(const char * filename, const char * cntrname = NULL);
    
    \par Tcl syntax:
    cntr_load \ref file "filename" "cntrname"

    \par Description:
    reads \ref d_cntr "countour" named 'cntrname' from surfit datafile

    \par Example:
    cntr_load "C:\\my_cntr.dat" "my_cntr"
*/
boolvec * cntr_load(const char * filename, const char * cntrname = NULL);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_write(const char * filename, const char * cntr_name = "*", const char * delimiter = "\t");
    
    \par Tcl syntax:
    cntr_write \ref file "filename" \ref str "cntr_name" "delimiter"

    \par Description:
    saves \ref d_cntr "contour" to formatted text file. 

    \par Example:
    cntr_write "C:\\my_cntr.txt" "my_cntr"
*/
boolvec * cntr_write(const char * filename, const char * cntr_name = "*", const char * delimiter = "\t");

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save(const char * filename, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_save \ref file "filename" \ref str "cntr_name"

    \par Description:
    saves \ref d_cntr "contour" to surfit datafile

    \par Example:
    cntr_save "C:\\my_cntr.dat" "my_cntr"
*/
boolvec * cntr_save(const char * filename, const char * cntr_name = "*");

///////////////
// math

/*! \ingroup tcl_cntr_math
    \fn bool cntr_plus_real(REAL value, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_plus_real value "cntr_name"

    \par Description:
    adds real value to \ref d_cntr "contour" values
*/
boolvec * cntr_plus_real(REAL value, const char * cntr_name = "*");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_minus_real(REAL value, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_minus_real value \ref str "cntr_name"

    \par Description:
    deducts real value from \ref d_cntr "contour" values
*/
boolvec * cntr_minus_real(REAL value, const char * cntr_name = "*");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_mult_real(REAL value, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_mult_real value \ref str "cntr_name"

    \par Description:
    multiplies \ref d_cntr "contour" values with real value
*/
boolvec * cntr_mult_real(REAL value, const char * cntr_name = "*");

/*! \ingroup tcl_cntr_math
    \fn bool cntr_div_real(REAL value, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_div_real value \ref str "cntr_name"

    \par Description:
    divides \ref d_cntr "contour" values with real value
*/
boolvec * cntr_div_real(REAL value, const char * cntr_name = "*");

///////////////
// convers

/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_curv(const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_to_curv \ref str "cntr_name"

    \par Description:
    makes \ref d_curv "curve" from \ref d_cntr "contour"
*/
boolvec * cntr_to_curv(const char * cntr_name = "*");

/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_pnts(REAL step, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_to_pnts \ref str "cntr_name" step

    \par Description:
    makes \ref d_points "points" from \ref d_cntr "contour" 
*/
boolvec * cntr_to_pnts(REAL step, const char * cntr_name = "*");

///////////////
// other

/*! \ingroup tcl_cntr_other
    \fn const char * cntr_getName(const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_getName \ref str "cntr_position"

    \par Description:
    returns name of \ref d_cntr "contour"
*/
strvec * cntr_getName(const char * cntr_name = "*");

/*! \ingroup tcl_cntr_other
    \fn const char * cntr_getNameAt(int pos);
    
    \par Tcl syntax:
    cntr_getNameAt position

    \par Description:
    returns name of \ref d_cntr at position "pos"
*/
const char * cntr_getNameAt(int pos);

/*! \ingroup tcl_cntr_other
    \fn int cntr_getId(const char * contour_name = "*");

    \par Tcl syntax:
    cntr_getId \ref str "contour_name"
    
    \par Description:
    returns unique contour identificator 
*/
intvec * cntr_getId(const char * contour_name = "*");

/*! \ingroup tcl_cntr_other
    \fn bool cntr_setName(const char * new_name, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_setName "new_name" \ref str "cntr_name"

    \par Description:
    sets name of \ref d_cntr "contour"
*/
boolvec * cntr_setName(const char * new_name, const char * cntr_name = "*");

/*! \ingroup tcl_cntr_other
    \fn void cntr_del(const char * cntr_name);
    
    \par Tcl syntax:
    cntr_del \ref str "cntr_name"

    \par Description:
    removes \ref d_cntr "contour" from memory
*/
void cntr_del(const char * cntr_name);

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

boolvec * cntr_smooth(const char * cntr_name = "*", size_t cnt = 1);

}; // namespace surfit;

#endif

