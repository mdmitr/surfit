
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit_cntr_internal_included__
#define __surfit_cntr_internal_included__

namespace surfit {

class d_cntr;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn d_cntr * _cntr_read(const char * filename, const char * cntrname, int columns, int col1, int col2, int col3, int skip_lines, int grow_by, const char * mask);
    \brief reads \ref cntr from formatted text file
*/
d_cntr * _cntr_read(const char * filename, const char * cntrname,
		  int col1, int col2, int col3, int skip_lines,
		  int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn d_cntr * _cntr_load(const char * filename, const char * cntrname);
    \brief loads \ref cntr from surfit datafile
*/
d_cntr * _cntr_load(const char * filename, const char * cntrname);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn d_cntr * _cntr_load_shp(const char * filename, const char * cntrname);
    \brief loads \ref cntr from ERSI shape file
*/
d_cntr * _cntr_load_shp(const char * filename, const char * cntrname);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn d_cntr * _cntr_load_shp(const char * filename);
    \brief loads all \ref cntr "contours" from ERSI shape file
*/
bool _cntrs_load_shp(const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_write(const d_cntr * contour, const char * filename, const char * mask);
    \brief writes \ref cntr to formatted text file. 
*/
bool _cntr_write(const d_cntr * contour, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_save(const d_cntr * contour, const char * filename);
    \brief writes \ref cntr to ROFF file (see \ref datafile for details)
*/
bool _cntr_save(const d_cntr * contour, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_save_df(const d_cntr * contour, datafile * df);
    \brief writes \ref cntr tags to \ref datafile
*/
bool _cntr_save_df(const d_cntr * contour, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_save_shp(const d_cntr * contour, const char * filename);
    \brief writes \ref cntr to ESRI shape file
*/
bool _cntr_save_shp(const d_cntr * contour, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn d_cntr * _cntr_load_df(datafile * df, const char * cntrname);
    \brief reads \ref cntr tags from \ref datafile
*/
d_cntr * _cntr_load_df(datafile * df, const char * cntrname);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn void _cntr_info(const d_cntr * contour);
    \brief prints some info about \ref cntr "contour"
*/
void _cntr_info(const d_cntr * contour);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn void _add_surfit_cntrs(d_cntr * contour);
    \brief adds contour to \ref surfit_cntr collection
*/
void _add_surfit_cntrs(d_cntr * contour);

}; // namespace surfit;

#endif

