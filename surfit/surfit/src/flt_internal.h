
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

#ifndef __surfit_flt_internal_included__
#define __surfit_flt_internal_included__

namespace surfit {

class flt;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn bool _flt_check();
    \brief checks for \ref surfit_flt existance
*/
bool _flt_check();

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn bool _flt_unload();
    \brief unloads \ref surfit_flt from memory
*/
bool _flt_unload();

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn flt * _flt_read(const char * filename, const char * fltname, int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref flt from formatted text file.
*/
flt * _flt_read(const char * filename, const char * fltname, int columns, 
		int col1, int col2, int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn bool _flt_write(flt * fault, const char * filename, const char * mask);
    \brief writes \ref flt to formatted text file. 
*/
bool _flt_write(flt * fault, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn bool _flt_save(flt * fault, const char * filename, int mode);
    \brief writes \ref flt to ROFF file (see \ref datafile for details)
*/
bool _flt_save(flt * fault, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn bool _flt_save_df(flt * fault, datafile * df);
    \brief writes \ref flt tags to \ref datafile. 
*/
bool _flt_save_df(flt * fault, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn flt * _flt_load(const char * filename, const char * fltname, int mode);
    \brief loads \ref flt from ROFF file (see \ref datafile for details)
*/
flt * _flt_load(const char * filename, const char * fltname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn flt * _flt_load_df(datafile * df, const char * fltname);
    \brief reads \ref flt tags from \ref datafile. 
*/
flt * _flt_load_df(datafile * df, const char * fltname);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn void _flt_info(flt * fault);
    \brief prints some info about \ref flt "fault line"
*/
void _flt_info(flt * fault);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn flt * _get_surfit_flt();
    \brief returns pointer to \ref surfit_flt
*/
flt * _get_surfit_flt();

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn void _set_surfit_flt(flt * fault);
    \brief sets \ref surfit_flt
*/
void _set_surfit_flt(flt * fault);

SURFIT_EXPORT
/*! \ingroup internal_flt
    \fn void _add_surfit_flts(flt * fault);
    \brief adds fault line to \ref surfit_flts collection
*/
void _add_surfit_flts(flt * fault);

}; // namespace surfit;

#endif



