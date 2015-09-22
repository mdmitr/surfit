
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

class boolvec;

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_load_shp(const char * filename, const char * pntsname = "*", const char * param = "VALUE");
    
    \par Tcl syntax:
    pnts_load_shp \ref file "filename" "pntsname" "param"

    \par Description:
    reads \ref d_points "points" from ESRI shape file and names them "pntsname"

    \par Example:
    pnts_load_shp "C:\\my_points.shp" "my_points" "VALUE"

    \par Implemented in library:
    libsurfit_io
*/
boolvec * pnts_load_shp(const char * filename, const char * pntsname = "*", const char * param = "VALUE");

/*! \ingroup tcl_pnts_save_load
    \fn bool pnts_save_shp(const char * filename, const char * points_name = "*");
    
    \par Tcl syntax:
    pnts_save_shp "filename" \ref str "points_name"

    \par Description:
    saves \ref d_points "points" to ESRI shapefile format

    \par Example
    pnts_save_shp "C:\\points.shp" "my_points"

    \par Implemented in library:
    libsurfit_io
*/
boolvec * pnts_save_shp(const char * filename, const char * points_name = "*");


};

