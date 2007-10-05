
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

class d_cntr;

//! loads contour from surfer BLN file
SURFIT_IO_EXPORT
d_cntr * _cntr_load_bln(FILE * file, int & orient);

//! loads contours from ERSI shape file
SURFIT_IO_EXPORT
bool _cntr_load_shp(const char * filename, const char * cntrname, const char * zfield = NULL);

//! saves contour to Surfer-BLN file
SURFIT_IO_EXPORT
bool _cntr_save_bln(const d_cntr * crv, FILE * file, int orient);

//! writes contour to ESRI shape file
SURFIT_IO_EXPORT
bool _cntr_save_shp(const d_cntr * contour, const char * filename);

}; // namespace surfit;

