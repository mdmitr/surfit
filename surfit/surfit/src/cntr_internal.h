
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

#ifndef __surfit_cntr_internal_included__
#define __surfit_cntr_internal_included__

namespace surfit {

class cntr;
class wcntr;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_check();
    \brief checks for \ref surfit_cntr existance
*/
bool _cntr_check();

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_unload();
    \brief unloads \ref surfit_cntr from memory
*/
bool _cntr_unload();

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn cntr * _cntr_read(const char * filename, const char * cntrname, int columns, int col1, int col2, int col3, int grow_by, const char * mask);
    \brief reads \ref cntr from formatted text file
*/
cntr * _cntr_read(const char * filename, const char * cntrname,
		  int columns, 
		  int col1, int col2, int col3,
		  int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_write(cntr * contour, const char * filename, const char * mask);
    \brief writes \ref cntr to formatted text file. 
*/
bool _cntr_write(cntr * contour, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_save(cntr * contour, const char * filename, int mode);
    \brief writes \ref cntr to ROFF file (see \ref datafile for details)
*/
bool _cntr_save(cntr * contour, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn bool _cntr_save_df(cntr * contour, datafile * df);
    \brief writes \ref cntr tags to \ref datafile
*/
bool _cntr_save_df(cntr * contour, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn cntr * _cntr_load(const char * filename, const char * cntrname, int mode);
    \brief loads \ref cntr from ROFF file (see \ref datafile for details)
*/
cntr * _cntr_load(const char * filename, const char * cntrname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn cntr * _cntr_load_df(datafile * df, const char * cntrname);
    \brief reads \ref cntr tags from \ref datafile
*/
cntr * _cntr_load_df(datafile * df, const char * cntrname);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn void _cntr_info(cntr * contour);
    \brief prints some info about \ref cntr "contour"
*/
void _cntr_info(cntr * contour);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn cntr * _get_surfit_cntr();
    \brief returns \ref surfit_cntr
*/
cntr * _get_surfit_cntr();

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn void _set_surfit_cntr(cntr * contour);
    \brief sets \ref surfit_cntr
*/
void _set_surfit_cntr(cntr * contour);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn void _add_surfit_cntrs(cntr * contour);
    \brief adds contour to \ref surfit_cntr collection
*/
void _add_surfit_cntrs(cntr * contour);

SURFIT_EXPORT
/*! \ingroup internal_cntr
    \fn wcntr * _cntr_to_wcntr(cntr * contour, REAL weight);
    \brief converts \ref cntr to \ref wcntr with specified informational weight
*/
wcntr * _cntr_to_wcntr(cntr * contour, REAL weight);

}; // namespace surfit;

#endif

