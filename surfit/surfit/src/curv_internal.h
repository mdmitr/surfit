
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

#ifndef __surfit_curv_internal_included__
#define __surfit_curv_internal_included__

namespace surfit {

class curv;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_check();
    \brief checks for \ref surfit_curv existance
*/
bool _curv_check();

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_unload();
    \brief unloads \ref surfit_curv from memory
*/
bool _curv_unload();

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn curv * _curv_read(const char * filename, const char * curvname, int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref curv from formatted text file
*/
curv * _curv_read(const char * filename, const char * curvname,
		  int columns, 
		  int col1, int col2,
		  int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_write(curv * contour, const char * filename, const char * mask);
    \brief writes \ref curv to formatted text file. 
*/
bool _curv_write(curv * contour, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_save(curv * contour, const char * filename, int mode);
    \brief writes \ref curv to ROFF file (see \ref datafile for details)
*/
bool _curv_save(curv * contour, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn bool _curv_save_df(curv * contour, datafile * df);
    \brief writes \ref curv tags to \ref datafile. 
*/
bool _curv_save_df(curv * contour, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn curv * _curv_load(const char * filename, const char * curvname, int mode);
    \brief loads \ref curv from ROFF file (see \ref datafile for details)
*/
curv * _curv_load(const char * filename, const char * curvname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn curv * _curv_load_df(datafile * df, const char * curvname);
    \brief reads \ref curv tags from \ref datafile. 
*/
curv * _curv_load_df(datafile * df, const char * curvname);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn void _curv_info(curv * contour);
    \brief prints some info about contour
*/
void _curv_info(curv * contour);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn curv * _get_surfit_curv();
    \brief returns \ref surfit_curv
*/
curv * _get_surfit_curv();

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn void _set_surfit_curv(curv * contour);
    \brief sets \ref surfit_curv
*/
void _set_surfit_curv(curv * contour);

SURFIT_EXPORT
/*! \ingroup internal_curv
    \fn void _add_surfit_curvs(curv * contour);
    \brief adds contour to \ref surfit_curv collection
*/
void _add_surfit_curvs(curv * contour);

}; // namespace surfit;

#endif

