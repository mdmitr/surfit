
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
    loads \ref d_curv "curve" from formatted text file
    \par Tcl syntax:
    curv_read "filename" "curvname" 1st_column 2nd_column "delimiters" number_of_lines_to_skip
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
SURFIT_EXPORT
bool curv_read(const char * filename, const char * curvname=NULL	, 
    	       int col1=1, int col2=2, 
	       const char * delimiter=" ", int skip_lines = 0, int grow_by=250);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_read_bln(const char * filename);
    loads \ref d_curv "curve" from BLN file
    \par Tcl syntax:
    curv_read_bln "filename"
*/
SURFIT_EXPORT
bool curv_read_bln(const char * filename);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_write(const char * filename, const char * curv_name_or_position = "0", const char * delimiter = "\t");
    saves \ref d_curv "curve" to formatted text file.
    \par Tcl syntax:
    curv_write "filename" "delimiter"
*/
SURFIT_EXPORT
bool curv_write(const char * filename, const char * curv_name_or_position = "0", const char * delimiter = "\t");

/*! \ingroup tcl_curv_save_load
    \fn bool curv_write_bln(const char * filename, const char * curv_name_or_position = "0", int orient=1)
    saves \ref d_curv "curve" to BLN file
    \par Tcl syntax:
    curv_write_bln "filename" "curv_name_or_position" orient
    \param filename name for BLN file
    \param curv_name_or_position curv name or position number
    \param orient This value is equal to 1 if the region is inside area and equal to 0 if the region is outside area 
    \par Example
    curv_write_bln "C:\\curv.bln" my_curv 1
*/
SURFIT_EXPORT
bool curv_write_bln(const char * filename, const char * curv_name_or_position = "0", int orient = 1);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_save(const char * filename, const char * curv_name_or_position = "0");
    saves \ref d_curv "curve" to surfit datafile
    \par Tcl syntax:
    curv_save "filename" "curv_name_or_position"
*/
SURFIT_EXPORT
bool curv_save(const char * filename, const char * curv_name_or_position = "0");

/*! \ingroup tcl_curv_save_load
    \fn bool curv_load(const char * filename, const char * curvname = NULL);
    loads \ref d_curv "curve" from surfit datafile
    \par Tcl syntax:
    curv_load "filename" "curvname"
*/
SURFIT_EXPORT
bool curv_load(const char * filename, const char * curvname = NULL);

//////////////
// other

/*! \ingroup tcl_curv_other
    \fn const char * curv_getName(const char * curv_position = "0");
    returns name of \ref d_curv "curve"
    \par Tcl syntax:
    curv_getName position_number
*/
SURFIT_EXPORT
const char * curv_getName(const char * curv_name_or_position = "0");

/*! \ingroup tcl_curv_other
    \fn bool curv_setName(const char * new_name, const char * curv_name_or_position = "0");
    sets name of \ref d_curv "curve"
    \par Tcl syntax:
    curv_setName "new_name" "curv_name_or_position"
    
*/
SURFIT_EXPORT
bool curv_setName(const char * new_name, const char * curv_name_or_position = "0");

/*! \ingroup tcl_curv
    \fn bool curv_delall();
    removes all curves from memory
    \par Tcl syntax:
    curv_delall
*/
SURFIT_EXPORT
bool curv_delall();

/*! \ingroup tcl_curv
    \fn bool curv_del(const char * curv_name_or_position = "0");
    removes \ref d_curv "curve" at 'curv_name_or_position' position from memory
    \par Tcl syntax:
    curv_del "curv_name_or_position
    \par Example:
    curv_del "my_curve"
*/
SURFIT_EXPORT
bool curv_del(const char * curv_name_or_position = "0");

/*! \ingroup tcl_curv
    \fn int curv_size();
    returns number of curvs in memory
    \par Tcl syntax:
    curv_size
*/
SURFIT_EXPORT
int curv_size();

/*! \ingroup tcl_curv
    \fn void curvs_info();
    prints information about all \ref d_curv "curves" in memory
    \par Tcl syntax:
    curvs_info
*/
SURFIT_EXPORT
void curvs_info();

}; // namespace surfit;

#endif
