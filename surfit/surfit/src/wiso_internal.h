
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

#ifndef __surfit_wiso_internal_included__
#define __surfit_wiso_internal_included__

namespace surfit {

class wiso;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn bool _wiso_check();
    \brief checks for \ref surfit_wiso existance
*/
bool _wiso_check();

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn bool _wiso_unload();
    \brief unloads \ref surfit_wiso from memory
*/
bool _wiso_unload();

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn wiso * _wiso_read(const char * filename, const char * isoname, REAL value, REAL weight, int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref wiso from formatted text file. "value" - isoline level, "weight" - informational weight 
*/
wiso * _wiso_read(const char * filename, const char * isoname, REAL value, REAL weight,
		  int columns, int col1, int col2, int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn bool _wiso_write(wiso * wisoline, const char * filename, const char * mask);
    \brief writes \ref wiso to formatted text file. 
*/
bool _wiso_write(wiso * wisoline, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn bool _wiso_save(wiso * wisoline, const char * filename, int mode);
    \brief writes \ref wiso to ROFF file (see \ref datafile for details)
*/
bool _wiso_save(wiso * wisoline, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn bool _wiso_save_df(wiso * wisoline, datafile * df);
    \brief writes \ref wiso tags to \ref datafile
*/
bool _wiso_save_df(wiso * wisoline, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn wiso * _wiso_load(const char * filename, const char * wisoname, int mode);
    \brief loads \ref wiso from ROFF file (see \ref datafile for details)
*/
wiso * _wiso_load(const char * filename, const char * wisoname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn wiso * _wiso_load_df(datafile * df, const char * wisoname);
    \brief reads \ref wiso tags from \ref datafile
*/
wiso * _wiso_load_df(datafile * df, const char * wisoname);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn void _wiso_info(wiso * wisoline);
    \brief prints some info about \ref wiso
*/
void _wiso_info(wiso * wisoline);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn iso * _get_surfit_wiso();
    \brief returns \ref surfit_wiso
*/
wiso * _get_surfit_wiso();

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn void _set_surfit_wiso(wiso * wisoline);
    \brief sets \ref surfit_wiso
*/
void _set_surfit_wiso(wiso * wisoline);

SURFIT_EXPORT
/*! \ingroup internal_wiso
    \fn void _add_surfit_wisos(wiso * wisoline);
    \brief adds \ref wiso to \ref surfit_wisos collection
*/
void _add_surfit_wisos(wiso * wisoline);

}; // namespace surfit;

#endif



