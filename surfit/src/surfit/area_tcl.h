
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

#ifndef __surfit_area_tcl_included__
#define __surfit_area_tcl_included__

namespace surfit {

///////////////////////
// saving and loading

/*! \ingroup tcl_area_save_load
    \fn bool area_read(const char * filename, const char * areaname=NULL	, 
	       int col1=1, int col2=2,
	       const char * delimiters=" ", int skip_lines = 0, int grow_by=250);
    reads \ref d_area "area" from formatted text file and sets its name to "areaname"
    \par Tcl syntax:
    area_read "filename" "area_name" first_column_position second_column_position "delimiters" skip_lines
    \param filename name of formatted text file
    \param areaname name for \ref d_area "area" dataset
    \param col1 column with X coordinates
    \param col2 column with Y coordinates
    \param skip_lines number of lines to skip header
    \param delimiters delimiters between columns. May be " ", "\t", "," or other symbols
    \param grow_by =250
    \par Example
    area_read "C:\\area.txt" my_area
    area_read "C:\\area2.txt" my_area2 2 3 "\t"
*/
SURFIT_EXPORT
bool area_read(const char * filename, const char * areaname=NULL	, 
	       int col1=1, int col2=2,
	       const char * delimiter=" ", int skip_lines = 0, int grow_by=250);

/*! \ingroup tcl_area_save_load
    \fn bool area_read_bln(const char * filename, const char * areaname = NULL);
    reads \ref d_area "area" from Surfer BLN files and sets its name to "areaname"
    \par Tcl syntax:
    area_read_read "filename" "area_name" 
    \par Example
    area_read_bln "C:\\area.bln" area_from_bln
*/
SURFIT_EXPORT
bool area_read_bln(const char * filename, const char * areaname = NULL);

/*! \ingroup tcl_area_save_load
    \fn bool area_write(const char * filename, const char * area_name_or_position, const char * delimiter);
    writes \ref d_area "area" to formatted text file
    \par Tcl syntax:
    area_write "filename" "area_name_or_position" "delimiter"
    \param filename text file filename
    \param area_name_or_position area name or position number
    \param delimiter delimiter between columns. May be " ", "\t", "," or other symbols
    \par Example
    area_write "C:\\area.txt" my_area
*/
SURFIT_EXPORT
bool area_write(const char * filename, const char * area_name_or_position = "0", const char * delimiter = "\t");

/*! \ingroup tcl_area_save_load
    \fn bool area_write_bln(const char * filename, const char * area_name_or_position = "0", int orient = 1);
    writes \ref d_area "area" to Surfer BLN file
    \par Tcl syntax:
    area_write_bln "filename" "area_name_or_position" orient
    \param filename name for BLN file
    \param area_name_or_position area name or position number
    \param orient This value is equal to 1 if the region is inside area and equal to 0 if the region is outside area 
    \par Example
    area_write_bln "C:\\area.bln" my_area 1
*/
SURFIT_EXPORT
bool area_write_bln(const char * filename, const char * area_name_or_position = "0", int flag = 1);

/*! \ingroup tcl_area_save_load
    \fn bool area_save(const char * filename, const char * area_name_or_position = "0");
    saves \ref d_area "area" to surfit datafile
    \par Tcl syntax:
    area_save "filename" "area_name_or_position"
    \param filename Surfer BLN file
    \param area_name_or_position \ref d_area "area" name or position number
    \par Example
    area_save "C:\\area.dat" my_area
*/
SURFIT_EXPORT
bool area_save(const char * filename, const char * area_name_or_position = "0");

/*! \ingroup tcl_area_save_load
    \fn bool area_load(const char * filename, const char * area_name = NULL);
    loads \ref d_area "area" from surfit datafile. if no areaname specified, then loads the first area in the file.
    \par Tcl syntax:
    area_load "filename" "area_name"
    \param filename surfit datafile filename
    \param area_name \ref d_area "area" name for load
    \par Example
    area_load "C:\\area.dat" my_area
*/
SURFIT_EXPORT
bool area_load(const char * filename, const char * area_name = NULL);

//////////////
// other

/*! \ingroup tcl_area_other
    \fn const char * area_getName(const char * area_name_or_position = "0");
    returns name of \ref area 

    \par Tcl syntax:
    area_getName "area_name_or_position"
*/
SURFIT_EXPORT
const char * area_getName(const char * area_name_or_position = "0");

/*! \ingroup tcl_area_other
    \fn bool area_setName(const char * new_name, const char * area_name_or_position = "0");
    sets name of \ref area 

    \par Tcl syntax:
    area_setName new_name "area_name_or_position"
*/
SURFIT_EXPORT
bool area_setName(const char * new_name, const char * area_name_or_position = "0");

/*! \ingroup tcl_area
    \fn bool area_delall();
    removes all areas from memory

    \par Tcl syntax:
    area_delall
*/
SURFIT_EXPORT
bool area_delall();

/*! \ingroup tcl_area
    \fn bool area_del(const char * area_name_or_position = "0");
    removes \ref area from at 'area_name_or_position' position
    
    \par Tcl syntax:
    area_del "area_name_or_position"

*/
SURFIT_EXPORT
bool area_del(const char * area_name_or_position = "0");

/*! \ingroup tcl_area
    \fn int area_size();
    returns number of areas in memory 

    \par Tcl syntax:
    area_size
*/
SURFIT_EXPORT
int area_size();

SURFIT_EXPORT
bool area_invert(const char * area_name_or_position = "0");

/*! \ingroup tcl_area
    \fn void areas_info();
    prints information about all areas  

    \par Tcl syntax:
    areas_info
*/
SURFIT_EXPORT
void areas_info();

}; // namespace surfit;

#endif

