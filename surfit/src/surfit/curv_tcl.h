
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

///////////////////////
// saving and loading

/*! \ingroup tcl_curv_save_load
    \fn bool curv_read(const char * filename, const char * curvname, int col1, int col2, const char * delimiter, int skip_lines, int grow_by);
    
    \par Tcl syntax:
    curv_read "filename" "curvname" 1st_column 2nd_column "delimiters" number_of_lines_to_skip

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
bool curv_read(const char * filename, const char * curvname=NULL	, 
    	       int col1=1, int col2=2, 
	       const char * delimiter=" \t", int skip_lines = 0, int grow_by=250);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_read_bln(const char * filename);
    
    \par Tcl syntax:
    curv_read_bln "filename"

    \par Description:
    loads \ref d_curv "curve" from BLN file
*/
bool curv_read_bln(const char * filename);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_write(const char * filename, const char * curv_name_or_position = "0", const char * delimiter = "\t");
    
    \par Tcl syntax:
    curv_write "filename" "delimiter"

    \par Description:
    saves \ref d_curv "curve" to formatted text file.
*/
bool curv_write(const char * filename, const char * curv_name_or_position = "0", const char * delimiter = "\t");

/*! \ingroup tcl_curv_save_load
    \fn bool curv_write_bln(const char * filename, const char * curv_name_or_position = "0", int orient=1)
    
    \par Tcl syntax:
    curv_write_bln "filename" "curv_name_or_position" orient

    \par Description:
    saves \ref d_curv "curve" to BLN file

    \param filename name for BLN file
    \param curv_name_or_position curv name, or curve position number
    \param orient This value is equal to 1 if the region is inside area and equal to 0 if the region is outside area 
    
    \par Example
    curv_write_bln "C:\\curv.bln" my_curv 1
*/
bool curv_write_bln(const char * filename, const char * curv_name_or_position = "0", int orient = 1);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_save(const char * filename, const char * curv_name_or_position = "0");
    
    \par Tcl syntax:
    curv_save "filename" "curv_name_or_position"

    \par Description:
    saves \ref d_curv "curve" to surfit datafile
*/
bool curv_save(const char * filename, const char * curv_name_or_position = "0");

/*! \ingroup tcl_curv_save_load
    \fn bool curv_load(const char * filename, const char * curvname = NULL);
    
    \par Tcl syntax:
    curv_load "filename" "curvname"

    \par Description:
    loads \ref d_curv "curve" from surfit datafile
*/
bool curv_load(const char * filename, const char * curvname = NULL);

//////////////
// other

/*! \ingroup tcl_curv_other
    \fn const char * curv_getName(const char * curv_position = "0");
    
    \par Tcl syntax:
    curv_getName position_number

    \par Description:
    returns name of \ref d_curv "curve"
*/
const char * curv_getName(const char * curv_name_or_position = "0");

/*! \ingroup tcl_curv_other
    \fn bool curv_setName(const char * new_name, const char * curv_name_or_position = "0");
    
    \par Tcl syntax:
    curv_setName "new_name" "curv_name_or_position"

    \par Description:
    sets name of \ref d_curv "curve"
*/
bool curv_setName(const char * new_name, const char * curv_name_or_position = "0");

/*! \ingroup tcl_curv_other
    \fn bool curv_delall();
    
    \par Tcl syntax:
    curv_delall

    \par Description:
    removes all curves from memory
*/
bool curv_delall();

/*! \ingroup tcl_curv_other
    \fn bool curv_del(const char * curv_name_or_position = "0");
    
    \par Tcl syntax:
    curv_del "curv_name_or_position

    \par Description:
    removes \ref d_curv "curve" at 'curv_name_or_position' position from memory

    \par Example:
    curv_del "my_curve"
*/
bool curv_del(const char * curv_name_or_position = "0");

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

