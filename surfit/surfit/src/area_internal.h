
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit_area_internal_included__
#define __surfit_area_internal_included__

namespace surfit {

class area;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn bool _area_check();
    \brief checks for \ref surfit_area existance
*/
bool _area_check();

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn bool _area_unload();
    \brief unloads \ref surfit_area from memory
*/
bool _area_unload();

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn area * _area_read(const char * filename, const char * areaname, REAL value, int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref area from formatted text file.
*/
area * _area_read(const char * filename, const char * areaname, REAL value,
                  int columns, int col1, int col2, int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn bool _area_write(area * arealine, const char * filename, const char * mask);
    \brief writes \ref area to formatted text file. 
*/
bool _area_write(area * arealine, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn bool _area_save(area * arealine, const char * filename, int mode);
    \brief writes \ref area to ROFF file (see \ref datafile for details)
*/
bool _area_save(area * arealine, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn bool _area_save_df(area * ar, datafile * df);
    \brief writes \ref area tags to \ref datafile
*/
bool _area_save_df(area * ar, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn area * _area_load(const char * filename, const char * areaname, int mode);
    \brief loads \ref area from ROFF file (see \ref datafile for details) 
*/
area * _area_load(const char * filename, const char * areaname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn area * _area_load_df(datafile * df, const char * areaname);
    \brief reads \ref area tags from \ref datafile
*/
area * _area_load_df(datafile * df, const char * areaname);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn void _area_info(area * arealine);
    \brief prints some info about area
*/
void _area_info(area * arealine);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn area * _get_surfit_area();
    \brief returns pointer to \ref surfit_area
*/
area * _get_surfit_area();

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn void _set_surfit_area(area * arealine);
    \brief sets \ref surfit_area
*/
void _set_surfit_area(area * arealine);

SURFIT_EXPORT
/*! \ingroup internal_area
    \fn void _add_surfit_areas(area * arealine);
    \brief adds arealine to \ref surfit_areas collection
*/
void _add_surfit_areas(area * arealine);

}; // namespace surfit;

#endif



