
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

class d_area;

SURFIT_IO_EXPORT
d_area * _area_load_bln(const char * filename, const char * areaname);

SURFIT_IO_EXPORT
d_area * _area_load_shp(const char * filename, const char * areaname);

SURFIT_IO_EXPORT
bool _areas_load_shp(const char * filename);

SURFIT_IO_EXPORT
bool _area_save_bln(const d_area * area, const char * filename);

SURFIT_IO_EXPORT
bool _area_save_shp(const d_area * area, const char * filename);


}; // namespace surfit;

