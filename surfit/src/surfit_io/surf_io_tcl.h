
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

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load_grd \ref file "filename" "surfname"

    \par Description:
    loads surface from SURFER grd file (ASCII format)

    \param filename Surfer grd file (ASCII format)
    \param surfname name for the surface (optional)

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_load_grd(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load_gmt \ref file "filename" "surfname"

    \par Description:
    loads surface from Generic Mapping Tools grd file (CDF format)

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_load_gmt(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load_grass \ref file "filename" "surfname"

    \par Description:
    loads surface from GRASS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_load_grass(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load_arcgis \ref file "filename" "surfname"

    \par Description:
    loads surface from ArcGIS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_load_arcgis(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load_xyz \ref file "filename" "surfname"

    \par Description:
    loads surface from XYZ 3-column text file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_load_xyz(const char * filename, const char * surfname = 0, bool force = false);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load_jpg \ref file "filename" "surfname"

    \par Description:
    loads surface from JPEG file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_load_jpg(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_load_bmp \ref file "filename" "surfname" 

    \par Description:
    loads surface from Windows bitmap file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_load_bmp(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);

//
//
//
//
//  SAVE section
//
//
//
//

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save_grd "filename" \ref str "surface_name" format

    \par Description:
    saves surface to SURFER grd file

    \param filename SURFER grd file 
    \param surface_name \ref str "name" of \ref d_surf "surface" dataset
    \param format 0 - ascii, 1 - binary, 2 - Surfer7 binary

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_save_grd(const char * filename, const char * surface_name = "*", int format = 0);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save_gmt "filename" \ref str "surface_name"

    \par Description:
    saves surface to Generic Mapping Tools grd file (CDF format)

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_save_gmt(const char * filename, const char * surface_name = "*");

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save_grass "filename" \ref str "surface_name"

    \par Description:
    saves surface to GRASS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_save_grass(const char * filename, const char * surface_name = "*");

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save_arcgis "filename" \ref str "surface_name"

    \par Description:
    saves surface to ArcGIS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_save_arcgis(const char * filename, const char * surface_name = "*");

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save_xyz "filename" \ref str "surface_name"

    \par Description:
    saves surface to XYZ text format

    \param filename XYZ text file
    \param surface_name \ref str "name" of \ref d_surf "surface" dataset

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_save_xyz(const char * filename, const char * surface_name = "*");

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save_jpg "filename" \ref str "surface_name"

    \par Description:
    saves surface to JPEG in grayscale colours

    \param filename jpeg file
    \param surface_name \ref str "name" of \ref d_surf "surface" dataset
    \param quality jpeg quality 0..255

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_save_jpg(const char * filename, const char * surface_name = "*", int quality = 255);

/*! \ingroup tcl_surf_save_load
    \par Tcl syntax:
    surf_save_bmp "filename" \ref str "surface_name"

    \par Description:
    saves surface to Windows BitMap file in grayscale colours

    \param filename bitmap file
    \param surface_name \ref str "name" of \ref d_surf "surface" dataset

    \par Implemented in library:
    libsurfit_io
*/
boolvec * surf_save_bmp(const char * filename, const char * surface_name = "*");

};

