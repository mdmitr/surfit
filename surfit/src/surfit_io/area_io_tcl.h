
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

namespace surfit {

/*! \ingroup tcl_area_save_load
    \fn bool area_load_bln(const char * filename, const char * areaname = NULL);
    
    \par Tcl syntax:
    area_load_bln \ref file "filename" "area_name" 

    \par Description:
    loads \ref d_area "area" from Surfer BLN files and sets its name to "areaname".
    Loads all areas from file if no areaname specified.

    \par Example
    area_load_bln "C:\\area.bln" area_from_bln

    \par Implemented in library:
    libsurfit_io

*/
boolvec * area_load_bln(const char * filename, const char * areaname = NULL);

/*! \ingroup tcl_area_save_load
    \fn bool area_load_shp(const char * filename, const char * area_name = NULL);
    
    \par Tcl syntax:
    area_load_shp \ref file "filename" "area_name"

    \par Description:
    loads \ref d_area "area" named "area_name" from ERSI shape file. 
    Loads all areas if no area_name specified.

    \param filename ERSI shape file name
    \param area_name \ref d_area "area" name for load
    
    \par Example
    area_load_shp "C:\\area.shp" my_area

    \par Implemented in library:
    libsurfit_io
*/
boolvec * area_load_shp(const char * filename, const char * area_name = NULL);

/*! \ingroup tcl_area_save_load
    \fn bool area_save_bln(const char * filename, const char * area_name = "*");
    
    \par Tcl syntax:
    area_save_bln "filename" \ref str "area_name"

    \par Description:
    saves \ref d_area "area" to Surfer BLN file

    \param filename name for BLN file
    \param area_name area \ref str "name". If area_name = "*" then saves all areas
    
    \par Example
    area_save_bln "C:\\area.bln" my_area 

    \par Implemented in library:
    libsurfit_io
*/
boolvec * area_save_bln(const char * filename, const char * area_name = "*");

/*! \ingroup tcl_area_save_load
    \fn bool area_save_shp(const char * filename, const char * area_name = "*");
    
    \par Tcl syntax:
    area_save_shp "filename" \ref str "area_name"

    \par Description:
    saves \ref d_area "area" to ERSI shape file

    \param filename ERSI shape file name
    \param area_name \ref d_area "area" \ref str "name"
    
    \par Example
    area_save_shp "C:\\area.shp" my_area

    \par Implemented in library:
    libsurfit_io
*/
boolvec * area_save_shp(const char * filename, const char * area_name = "*");

};

