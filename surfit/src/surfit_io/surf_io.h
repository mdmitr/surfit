
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

//! loads surface from SURFER grd file (ASCII format)
SURFIT_IO_EXPORT
d_surf * _surf_load_grd(const char * filename, const char * surfname); 

//! loads surface from SURFER grd file (BINARY format)
SURFIT_IO_EXPORT
d_surf * _surf_load_grd_bin(const char * filename, const char * surfname); 

//! loads surface from SURFER grd file (Surfer7 BINARY format)
SURFIT_IO_EXPORT
d_surf * _surf_load_grd_bin7(const char * filename, const char * surfname); 

//! loads surface from Generic Mapping Tools grd file (CDF format)
SURFIT_IO_EXPORT
d_surf * _surf_load_gmt(const char * filename, const char * surfname); 

//! loads surface from GRASS ASCII file
SURFIT_IO_EXPORT
d_surf * _surf_load_grass(const char * filename, const char * surfname); 

//! loads surface from ArcGIS ASCII file
SURFIT_IO_EXPORT
d_surf * _surf_load_arcgis(const char * filename, const char * surfname); 

//! loads surface from XYZ 3 column text file
SURFIT_IO_EXPORT
d_surf * _surf_load_xyz(const char * filename, const char * surfname, bool force = false); 

//! loads surface from JPEG file
SURFIT_IO_EXPORT
d_surf * _surf_load_jpg(const char * filename, const char * surfname, 
			REAL minz = 0, REAL maxz = 0, 
			REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1); 

//! loads surface from BMP file
SURFIT_IO_EXPORT
d_surf * _surf_load_bmp(const char * filename, const char * surfname, 
			REAL minz = 0, REAL maxz = 0, 
			REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1); 

//! saves surface to SURFER grd file (ASCII format)
SURFIT_IO_EXPORT
bool _surf_save_grd(const d_surf * srf, const char * filename); 

//! saves surface to SURFER grd file (BINARY format)
SURFIT_IO_EXPORT
bool _surf_save_grd_bin(const d_surf * srf, const char * filename); 

//! saves surface to SURFER grd file (Surfer7 BINARY format)
SURFIT_IO_EXPORT
bool _surf_save_grd_bin7(const d_surf * srf, const char * filename); 

//! saves surface to Generic Mapping Tools grd file (CDF format)
SURFIT_IO_EXPORT
bool _surf_save_gmt(const d_surf * srf, const char * filename); 

//! saves surface to GRASS ASCII file 
SURFIT_IO_EXPORT
bool _surf_save_grass(const d_surf * srf, const char * filename); 

//! saves surface to ArcGIS ASCII file 
SURFIT_IO_EXPORT
bool _surf_save_arcgis(const d_surf * srf, const char * filename); 

//! saves surface to XYZ text format
SURFIT_IO_EXPORT
bool _surf_save_xyz(const d_surf * srf, const char * filename);

//! saves surface to JPEG format
SURFIT_IO_EXPORT
bool _surf_save_jpg(const d_surf * srf, const char * filename, int quality = 255);

//! saves surface to Windows Bitmap format
SURFIT_IO_EXPORT
bool _surf_save_bmp(const d_surf * srf, const char * filename);

}; // namespace surfit;

