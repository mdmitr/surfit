
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

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_load_shp(const char * filename, const char * cntrname = NULL);
    
    \par Tcl syntax:
    cntr_load_shp "filename" "cntrname"

    \par Description:
    reads \ref d_cntr "countour" named 'cntrname' from ERSI shape file

    \par Example:
    cntr_load_shp "C:\\my_cntr.shp" "my_cntr"
*/
bool cntr_load_shp(const char * filename, const char * cntrname = NULL);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntrs_load_shp(const char * filename);
    
    \par Tcl syntax:
    cntrs_load_shp "filename" "cntrname"

    \par Description:
    reads all \ref d_cntr "countours" from ERSI shape file

    \par Example:
    cntrs_load_shp "C:\\my_cntr.shp"
*/
bool cntrs_load_shp(const char * filename);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save_shp(const char * filename, const char * cntr_name_or_position = "0");
    
    \par Tcl syntax:
    cntr_save_shp "filename" "cntr_name_or_position"

    \par Description:
    saves \ref d_cntr "contour" to ESRI shape file

    \par Example:
    cntr_save_shp "C:\\my_cntr.shp" "my_cntr"
*/
bool cntr_save_shp(const char * filename, const char * cntr_name_or_position = "0");

};

