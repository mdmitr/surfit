
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

#ifndef __surfit_curv_internal_included__
#define __surfit_curv_internal_included__

namespace surfit {

class d_curv;
class datafile;
class d_grid;

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn d_curv * _curv_read(const char * filename, const char * curvname, int col1, int col2, int skip_lines, int grow_by, const char * mask);
    \brief reads \ref curv from formatted text file
*/
d_curv * _curv_read(const char * filename, const char * curvname,
		    int col1, int col2, int skip_lines,
		    int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn d_curv * _curv_load(const char * filename, const char * curvname);
    \brief loads \ref curv from surfit datafile
*/
d_curv * _curv_load(const char * filename, const char * curvname);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn d_curv * _curv_load_df(datafile * df, const char * curvname);
    \brief reads \ref curv tags from \ref datafile. 
*/
d_curv * _curv_load_df(datafile * df, const char * curvname);
bool _curv_load_df_tag_readed(datafile * df, d_curv *& crv);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_write(const d_curv * contour, const char * filename, const char * mask);
    \brief writes \ref curv to formatted text file. 
*/
bool _curv_write(const d_curv * contour, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_save(const d_curv * contour, const char * filename);
    \brief writes \ref curv to surfit datafile
*/
bool _curv_save(const d_curv * contour, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_save_df(const d_curv * contour, datafile * df);
    \brief writes \ref curv tags to \ref datafile. 
*/
bool _curv_save_df(const d_curv * contour, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn void _curv_info(const d_curv * contour);
    \brief prints some info about contour
*/
void _curv_info(const d_curv * contour);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn void _add_surfit_curvs(d_curv * contour);
    \brief adds contour to \ref surfit_curv collection
*/
void _add_surfit_curvs(d_curv * contour);

SURFIT_EXPORT
d_curv * _curv_intersect_grid(const d_curv * crv, const d_grid * grd);

}; // namespace surfit;

#endif

