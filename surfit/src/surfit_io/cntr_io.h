
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

SURFIT_IO_EXPORT
/*! \ingroup internal_cntr
    \fn d_cntr * _cntr_load_shp(const char * filename, const char * cntrname);
    \brief loads \ref cntr from ERSI shape file
*/
d_cntr * _cntr_load_shp(const char * filename, const char * cntrname);

SURFIT_IO_EXPORT
/*! \ingroup internal_cntr
    \fn d_cntr * _cntr_load_shp(const char * filename);
    \brief loads all \ref cntr "contours" from ERSI shape file
*/
bool _cntrs_load_shp(const char * filename);

SURFIT_IO_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_save_shp(const d_cntr * contour, const char * filename);
    \brief writes \ref cntr to ESRI shape file
*/
bool _cntr_save_shp(const d_cntr * contour, const char * filename);

}; // namespace surfit;

