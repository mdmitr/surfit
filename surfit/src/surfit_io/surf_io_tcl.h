
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

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_grd(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_grd "filename" "surfname"

    \par Description:
    loads surface from SURFER grd file (ASCII format)

    \param filename Surfer grd file (ASCII format)
    \param surfname name for surface (optional)

    \par Implemented in library:
    libsurfit_io
*/
bool surf_load_grd(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_gmt(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_gmt "filename" "surfname"

    \par Description:
    loads surface from Generic Mapping Tools grd file (CDF format)

    \par Implemented in library:
    libsurfit_io
*/
bool surf_load_gmt(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_grass(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_grass "filename" "surfname"

    \par Description:
    loads surface from GRASS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
bool surf_load_grass(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_arcgis(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_arcgis "filename" "surfname"

    \par Description:
    loads surface from ArcGIS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
bool surf_load_arcgis(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_xyz(const char * filename, const char * surfname = 0)

    \par Tcl syntax:
    surf_load_xyz "filename" "surfname"

    \par Description:
    loads surface from XYZ 3-column text file

    \par Implemented in library:
    libsurfit_io
*/
bool surf_load_xyz(const char * filename, const char * surfname = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_jpg(const char * filename, const char * surfname = 0,
			   REAL minz = 0, REAL maxz = 0, 
			   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1)

    \par Tcl syntax:
    surf_load_jpg "filename" "surfname"

    \par Description:
    loads surface from JPEG file

    \par Implemented in library:
    libsurfit_io
*/
bool surf_load_jpg(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_bmp(const char * filename, const char * surfname = 0,
			   REAL minz = 0, REAL maxz = 0, 
			   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1)

    \par Tcl syntax:
    surf_load_bmp "filename" "surfname" 

    \par Description:
    loads surface from Windows bitmap file

    \par Implemented in library:
    libsurfit_io
*/
bool surf_load_bmp(const char * filename, const char * surfname = 0,
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
    \fn bool surf_save_grd(const char * filename, const char * surface_name_or_position = "0", int format);

    \par Tcl syntax:
    surf_save_grd "filename" "surface_name_or_position" format

    \par Description:
    saves surface to SURFER grd file

    \param filename SURFER grd file 
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
    \param format 0 - ascii, 1 - binary, 2 - Surfer7 binary

    \par Implemented in library:
    libsurfit_io
*/
bool surf_save_grd(const char * filename, const char * surface_name_or_position = "0", int format = 0);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_gmt(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_gmt "filename" "surface_name_or_position"

    \par Description:
    saves surface to Generic Mapping Tools grd file (CDF format)

    \par Implemented in library:
    libsurfit_io
*/
bool surf_save_gmt(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_grass(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_grass "filename" "surface_name_or_position"

    \par Description:
    saves surface to GRASS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
bool surf_save_grass(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_arcgis(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_arcgis "filename" "surface_name_or_position"

    \par Description:
    saves surface to ArcGIS ASCII file

    \par Implemented in library:
    libsurfit_io
*/
bool surf_save_arcgis(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_xyz(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_xyz "filename" "surface_name_or_position"

    \par Description:
    saves surface to XYZ text format

    \param filename XYZ text file
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.

    \par Implemented in library:
    libsurfit_io
*/
bool surf_save_xyz(const char * filename, const char * surface_name_or_position = "0");

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_jpg(const char * filename, const char * surface_name_or_position = "0", int quality = 255);

    \par Tcl syntax:
    surf_save_jpg "filename" "surface_name_or_position"

    \par Description:
    saves surface to JPEG in grayscale colours

    \param filename jpeg file
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.
    \param quality jpeg quality 0..255

    \par Implemented in library:
    libsurfit_io
*/
bool surf_save_jpg(const char * filename, const char * surface_name_or_position = "0", int quality = 255);

/*! \ingroup tcl_surf_save_load
    \fn bool surf_save_bmp(const char * filename, const char * surface_name_or_position = "0");

    \par Tcl syntax:
    surf_save_bmp "filename" "surface_name_or_position"

    \par Description:
    saves surface to Windows BitMap file in grayscale colours

    \param filename bitmap file
    \param surface_name_or_position name of \ref d_surf "surface" dataset, or surface position number.

    \par Implemented in library:
    libsurfit_io
*/
bool surf_save_bmp(const char * filename, const char * surface_name_or_position = "0");

};

