
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

#ifndef __surfit_warea_internal_included__
#define __surfit_warea_internal_included__

namespace surfit {

class warea;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn bool _warea_check();
    \brief checks for \ref surfit_warea existance
*/
bool _warea_check();

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn bool _warea_unload();
    \brief unloads \ref surfit_warea from memory
*/
bool _warea_unload();

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn warea * _warea_read(const char * filename, const char * wareaname, REAL value, REAL weight, int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref warea from formatted text file.
*/
warea * _warea_read(const char * filename, const char * wareaname, REAL value, REAL weight,
		    int columns, int col1, int col2, int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn bool _warea_write(warea * warealine, const char * filename, const char * mask);
    \brief writes \ref warea to formatted text file. 
*/
bool _warea_write(warea * warealine, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn bool _warea_save(warea * warealine, const char * filename, int mode);
    \brief writes \ref warea to ROFF file (see \ref datafile for details) 
*/
bool _warea_save(warea * warealine, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn bool _warea_save_df(warea * ar, datafile * df);
    \brief writes \ref warea tags to \ref datafile
*/
bool _warea_save_df(warea * ar, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn warea * _warea_load(const char * filename, const char * wareaname, int mode);
    \brief loads \ref warea from ROFF file (see \ref datafile for details) 
*/
warea * _warea_load(const char * filename, const char * wareaname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn warea * _warea_load_df(datafile * df, const char * wareaname);
    \brief reads \ref warea tags from \ref datafile
*/
warea * _warea_load_df(datafile * df, const char * wareaname);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn void _warea_info(warea * warealine);
    \brief prints some info about \ref warea
*/
void _warea_info(warea * warealine);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn warea * _get_surfit_warea();
    \brief returns pointer to \ref surfit_warea
*/
warea * _get_surfit_warea();

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn void _set_surfit_warea(warea * warealine);
    \brief sets \ref surfit_warea
*/
void _set_surfit_warea(warea * warealine);

SURFIT_EXPORT
/*! \ingroup internal_warea
    \fn void _add_surfit_wareas(warea * warealine);
    \brief adds warealine to \ref surfit_wareas collection
*/
void _add_surfit_wareas(warea * warealine);

}; // namespace surfit;

#endif



