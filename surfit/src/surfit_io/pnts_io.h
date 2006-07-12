
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

class d_points;

SURFIT_IO_EXPORT
/*! \ingroup internal
    \fn d_points * _pnts_load_shp(const char * filename, const char * pntsname);
    \brief reads \ref d_points from ESRI shape file
*/
d_points * _pnts_load_shp(const char * filename, const char * pntsname, const char * param = "VALUE");

SURFIT_IO_EXPORT
/*! \ingroup internal
    \fn bool _pnts_save_shp(const d_points * pnts, const char * filename);
    \brief saves \ref d_points to ESRI shapefile format
    \param filename filename
    \param pnts pointer to \ref d_points
*/
bool _pnts_save_shp(const d_points * pnts, const char * filename);

}; // namespace surfit;

