
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
    cntr_load_shp \ref file "filename" "cntrname"

    \par Description:
    reads \ref d_cntr "countour" named 'cntrname' from ERSI shape file. Loads
    all contours if no "cntrname" specified.

    \par Example:
    cntr_load_shp "C:\\my_cntr.shp" "my_cntr"

    \par Implemented in library:
    libsurfit_io
*/
boolvec * cntr_load_shp(const char * filename, const char * cntrname = NULL, const char * zfield = NULL);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_load_bln(const char * filename, const char * cntrname = NULL, const char * zfield);
    
    \par Tcl syntax:
    cntr_load_bln \ref file "filename" "cntrname" "fieldtouseforzvalue"

    \par Description:
    loads \ref d_cntr "contour" named "cntrname" from BLN file. Loads
    all contours if no "cntrname" specified.

    \par Implemented in library:
    libsurfit_io
*/
boolvec * cntr_load_bln(const char * filename, const char * cntrname = NULL);

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save_shp(const char * filename, const char * cntr_name = "*");
    
    \par Tcl syntax:
    cntr_save_shp "filename" \ref str "cntr_name" 

    \par Description:
    saves \ref d_cntr "contour" to ESRI shape file

    \par Example:
    cntr_save_shp "C:\\my_cntr.shp" "my_cntr"

    \par Implemented in library:
    libsurfit_io
*/
boolvec * cntr_save_shp(const char * filename, const char * cntr_name = "*");

/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save_bln(const char * filename, const char * cntr_name = "*")
    
    \par Tcl syntax:
    cntr_save_bln "filename" \ref str "cntr_name" 

    \par Description:
    saves \ref d_cntr "cntre" to BLN file

    \param filename name for BLN file
    \param cntr_name \ref d_contour "contour" \ref str "name"
    
    \par Example
    cntr_save_bln "C:\\cntr.bln" my_cntr 

    \par Implemented in library:
    libsurfit_io
*/
boolvec * cntr_save_bln(const char * filename, const char * cntr_name = "*");

};

