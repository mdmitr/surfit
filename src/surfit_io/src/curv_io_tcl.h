
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
    \par Tcl syntax:
    curv_load_bln \ref file "filename" "curv_name"

    \par Description:
    loads \ref d_curv "curve" named "curvname" from BLN file. Loads all curves
    if no curvname specified.

    \par Implemented in library:
    libsurfit_io
*/
boolvec * curv_load_bln(const char * filename, const char * curv_name = "*");

/*! \ingroup tcl_curv_save_load
    \par Tcl syntax:
    curv_load_shp \ref file "filename" "curv_name"

    \par Description:
    loads \ref d_curv "curve" named "curvname" from ERSI shape file. Loads all
    curves if no name specified

    \par Implemented in library:
    libsurfit_io
*/
boolvec * curv_load_shp(const char * filename, const char * curvname = "*");

/*! \ingroup tcl_curv_save_load
    \par Tcl syntax:
    curv_save_bln "filename" \ref str "curv_name"

    \par Description:
    saves \ref d_curv "curve" to BLN file

    \param filename name for BLN file
    \param curv_name curv \ref str "name"
    
    \par Example
    curv_save_bln "C:\\curv.bln" my_curv 

    \par Implemented in library:
    libsurfit_io
*/
boolvec * curv_save_bln(const char * filename, const char * curv_name = "*");

/*! \ingroup tcl_curv_save_load
    \par Tcl syntax:
    curv_save_shp "filename" \ref str "curv_name"

    \par Description:
    saves \ref d_curv "curve" to ERSI shape file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * curv_save_shp(const char * filename, const char * curv_name = "*");

};

