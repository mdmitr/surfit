
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

#ifndef __surfit_wcntr_internal_included__
#define __surfit_wcntr_internal_included__

namespace surfit {

class wcntr;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn bool _wcntr_check();
    \brief checks for \ref surfit_wcntr existance
*/
bool _wcntr_check();

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn bool _wcntr_unload();
    \brief unloads \ref surfit_wcntr from memory
*/
bool _wcntr_unload();

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn wcntr * _wcntr_read(const char * filename, const char * cntrname, REAL weight, int columns, int col1, int col2, int col3, int grow_by, const char * mask);
    \brief reads \ref wcntr from formatted text file
*/
wcntr * _wcntr_read(const char * filename, const char * cntrname, REAL weight,
		    int columns, 
		    int col1, int col2, int col3,
		    int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn bool _wcntr_save(wcntr * wcnt, const char * filename, int mode);
    \brief writes \ref wcntr to ROFF file (see \ref datafile for details)
*/
bool _wcntr_save(wcntr * wcnt, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn bool _wcntr_save_df(wcntr * wcontour, datafile * df);
    \brief writes \ref wcntr tags to \ref datafile
*/
bool _wcntr_save_df(wcntr * wcontour, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn wcntr * _wcntr_load(const char * filename, const char * cntrname, int mode);
    \brief loads \ref wcntr from ROFF file (see \ref datafile for details) 
*/
wcntr * _wcntr_load(const char * filename, const char * cntrname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn wcntr * _wcntr_load_df(datafile * df, const char * cntrname);
    \brief reads \ref wcntr tags from \ref datafile
*/
wcntr * _wcntr_load_df(datafile * df, const char * cntrname);

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn void _wcntr_info(wcntr * wcontour);
    \brief prints some info about \ref wcntr "contour with weight"
*/
void _wcntr_info(wcntr * wcontour);

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn wcntr * _get_surfit_wcntr();
    \brief returns \ref surfit_wcntr
*/
wcntr * _get_surfit_wcntr();

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn void _set_surfit_wcntr(wcntr * wcontour);
    \brief sets \ref surfit_wcntr
*/
void _set_surfit_wcntr(wcntr * wcontour);

SURFIT_EXPORT
/*! \ingroup internal_wcntr
    \fn void _add_surfit_wcntrs(wcntr * wcontour);
    \brief adds wcontour to \ref surfit_wcntr collection
*/
void _add_surfit_wcntrs(wcntr * wcontour);

}; // namespace surfit;

#endif

