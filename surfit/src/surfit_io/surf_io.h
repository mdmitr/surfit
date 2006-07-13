
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

class d_surf;

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_grd(const char * filename, const char * surfname)
    \brief loads surf from SURFER grd file (ASCII format)
*/
d_surf * _surf_load_grd(const char * filename, const char * surfname); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_gmt(const char * filename, const char * surfname)
    \brief loads surf from Generic Mapping Tools grd file (CDF format)
*/
d_surf * _surf_load_gmt(const char * filename, const char * surfname); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_grass(const char * filename, const char * surfname)
    \brief loads surf from GRASS ASCII file
*/
d_surf * _surf_load_grass(const char * filename, const char * surfname); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_arcgis(const char * filename, const char * surfname)
    \brief loads surf from ArcGIS ASCII file
*/
d_surf * _surf_load_arcgis(const char * filename, const char * surfname); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_xyz(const char * filename, const char * surfname)
    \brief loads surf from XYZ 3 column text file
*/
d_surf * _surf_load_xyz(const char * filename, const char * surfname); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_jpg(const char * filename, const char * surfname, REAL minz = 0, REAL maxz = 0)
    \brief loads surf from JPEG file
*/
d_surf * _surf_load_jpg(const char * filename, const char * surfname, 
			REAL minz = 0, REAL maxz = 0, 
			REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_load_bmp(const char * filename, const char * surfname, REAL minz = 0, REAL maxz = 0)
    \brief loads surf from JPEG file
*/
d_surf * _surf_load_bmp(const char * filename, const char * surfname, 
			REAL minz = 0, REAL maxz = 0, 
			REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1); 


SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_grd(const d_surf * srf, const char * filename); 
    \brief saves surf to SURFER grd file (ASCII format)
*/
bool _surf_save_grd(const d_surf * srf, const char * filename); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_gmt(const d_surf * srf, const char * filename); 
    \brief saves surf to Generic Mapping Tools grd file (CDF format)
*/
bool _surf_save_gmt(const d_surf * srf, const char * filename); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_grass(const d_surf * srf, const char * filename); 
    \brief saves surf to GRASS ASCII file 
*/
bool _surf_save_grass(const d_surf * srf, const char * filename); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_arcgis(const d_surf * srf, const char * filename); 
    \brief saves surf to ArcGIS ASCII file 
*/
bool _surf_save_arcgis(const d_surf * srf, const char * filename); 

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_xyz(const d_surf * srf, const char * filename);
    \brief saves surf to XYZ text format
*/
bool _surf_save_xyz(const d_surf * srf, const char * filename);

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_jpg(const d_surf * srf, const char * filename, int quality);
    \brief saves surf to JPEG format
*/
bool _surf_save_jpg(const d_surf * srf, const char * filename, int quality = 255);

SURFIT_IO_EXPORT
/*! \ingroup internal_surf
    \fn bool _surf_save_bmp(const d_surf * srf, const char * filename);
    \brief saves surf to Windows Bitmap format
*/
bool _surf_save_bmp(const d_surf * srf, const char * filename);

}; // namespace surfit;

