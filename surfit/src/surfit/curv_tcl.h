
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

#ifndef __surfit_curv_tcl_included__
#define __surfit_curv_tcl_included__

namespace surfit {

class boolvec;
class strvec;
class intvec;

///////////////////////
// saving and loading

/*! \ingroup tcl_curv_save_load
    \fn bool curv_read(const char * filename, const char * curvname, int col1, int col2, const char * delimiter, int skip_lines, int grow_by);
    
    \par Tcl syntax:
    curv_read \ref file "filename" "curvname" 1st_column 2nd_column "delimiters" number_of_lines_to_skip

    \par Description:
    loads \ref d_curv "curve" from formatted text file

    \param filename name of formatted text file
    \param curvname name for \ref d_curv "curv" dataset
    \param col1 column with X coordinates
    \param col2 column with Y coordinates
    \param skip_lines number of lines to skip header
    \param delimiter delimiters between columns. May be " ", "\t", "," or other symbols
    \param grow_by =250
    
    \par Example
    curv_read "C:\\curv.txt" my_curv
    curv_read "C:\\curv2.txt" my_curv2 2 3 "\t"
*/
boolvec * curv_read(const char * filename, const char * curvname=NULL	, 
    		    int col1=1, int col2=2, 
		    const char * delimiter=" \t", int skip_lines = 0, int grow_by=250);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_load(const char * filename, const char * curvname = NULL);
    
    \par Tcl syntax:
    curv_load \ref file "filename" "curvname"

    \par Description:
    loads \ref d_curv "curve" from surfit datafile
*/
boolvec * curv_load(const char * filename, const char * curvname = NULL);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_write(const char * filename, const char * curv_name = "*", const char * delimiter = "\t");
    
    \par Tcl syntax:
    curv_write "filename" \ref str "curv_name" "delimiter"

    \par Description:
    saves \ref d_curv "curve" to formatted text file.
*/
boolvec * curv_write(const char * filename, const char * curv_name = "*", const char * delimiter = "\t");

/*! \ingroup tcl_curv_save_load
    \fn bool curv_save(const char * filename, const char * curv_name = "*");
    
    \par Tcl syntax:
    curv_save "filename" \ref str "curv_name"

    \par Description:
    saves \ref d_curv "curve" to surfit datafile
*/
boolvec * curv_save(const char * filename, const char * curv_name = "*");

//////////////
// other

/*! \ingroup tcl_curv_other
    \fn const char * curv_getName(const char * curv_position = "*");
    
    \par Tcl syntax:
    curv_getName position_number

    \par Description:
    returns name of \ref d_curv "curve"
*/
strvec * curv_getName(const char * curv_name = "*");

/*! \ingroup tcl_surf_other
    \fn int curv_getId(const char * curve_name = "*");

    \par Tcl syntax:
    curv_getId \ref str "curve_name"
    
    \par Description:
    returns unique curve identificator 
*/
surfit::intvec * curv_getId(const char * curv_name = "*");

/*! \ingroup tcl_curv_other
    \fn bool curv_setName(const char * new_name, const char * curv_name = "*");
    
    \par Tcl syntax:
    curv_setName "new_name" \ref str "curv_name"

    \par Description:
    sets name of \ref d_curv "curve"
*/
boolvec * curv_setName(const char * new_name, const char * curv_name = "*");

/*! \ingroup tcl_curv_other
    \fn void curv_del(const char * curv_name = "*");
    
    \par Tcl syntax:
    curv_del "curv_name

    \par Description:
    removes \ref d_curv "curve" at 'curv_name' position from memory

    \par Example:
    curv_del "my_curve"
*/
void curv_del(const char * curv_name = "*");

/*! \ingroup tcl_curv_other
    \fn int curv_size();
    
    \par Tcl syntax:
    curv_size

    \par Description:
    returns number of curvs in memory
*/
int curv_size();

/*! \ingroup tcl_curv_other
    \fn void curvs_info();
    
    \par Tcl syntax:
    curvs_info

    \par Description:
    prints information about all \ref d_curv "curves" in memory
*/
void curvs_info();

}; // namespace surfit;

#endif

