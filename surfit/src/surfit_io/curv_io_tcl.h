
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

/*! \ingroup tcl_curv_save_load
    \fn bool curv_load_bln(const char * filename);
    
    \par Tcl syntax:
    curv_load_bln "filename"

    \par Description:
    loads \ref d_curv "curve" from BLN file

    \par Implemented in library:
    libsurfit_io
*/
bool curv_load_bln(const char * filename);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_load_shp(const char * filename, const char * curvname = NULL);
    
    \par Tcl syntax:
    curv_load_shp "filename" "curvname"

    \par Description:
    loads \ref d_curv "curve" named "curvname" from ERSI shape file

    \par Implemented in library:
    libsurfit_io
*/
bool curv_load_shp(const char * filename, const char * curvname = NULL);

/*! \ingroup tcl_curv_save_load
    \fn bool curvs_load_shp(const char * filename);
    
    \par Tcl syntax:
    curvs_load_shp "filename" "curvname"

    \par Description:
    loads all \ref d_curv "curves" from ERSI shape file

    \par Implemented in library:
    libsurfit_io
*/
bool curvs_load_shp(const char * filename);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_save_bln(const char * filename, const char * curv_name_or_position = "0", int orient=1)
    
    \par Tcl syntax:
    curv_save_bln "filename" "curv_name_or_position" orient

    \par Description:
    saves \ref d_curv "curve" to BLN file

    \param filename name for BLN file
    \param curv_name_or_position curv name, or curve position number
    \param orient This value is equal to 1 if the region is inside area and equal to 0 if the region is outside area 
    
    \par Example
    curv_save_bln "C:\\curv.bln" my_curv 1

    \par Implemented in library:
    libsurfit_io
*/
bool curv_save_bln(const char * filename, const char * curv_name_or_position = "0", int orient = 1);

/*! \ingroup tcl_curv_save_load
    \fn bool curv_save_shp(const char * filename, const char * curv_name_or_position = "0");
    
    \par Tcl syntax:
    curv_save_shp "filename" "curv_name_or_position"

    \par Description:
    saves \ref d_curv "curve" to ERSI shape file

    \par Implemented in library:
    libsurfit_io
*/
bool curv_save_shp(const char * filename, const char * curv_name_or_position = "0");

};

