
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

#ifndef __surfit_iso_internal_included__
#define __surfit_iso_internal_included__

namespace surfit {

class iso;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn bool _iso_check();
    \brief checks for \ref surfit_iso existance
*/
bool _iso_check();

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn bool _iso_unload();
    \brief unloads \ref surfit_iso from memory
*/
bool _iso_unload();

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn iso * _iso_read(const char * filename, const char * isoname, REAL value, int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref iso from formatted text file. "value" is isoline level
*/
iso * _iso_read(const char * filename, const char * isoname, REAL value,
		int columns, int col1, int col2, int grow_by, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn bool _iso_write(iso * isoline, const char * filename, const char * mask);
    \brief writes \ref iso to formatted text file. 
*/
bool _iso_write(iso * isoline, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn bool _iso_save(iso * isoline, const char * filename, int mode);
    \brief writes \ref iso to ROFF file (see \ref datafile for details)
*/
bool _iso_save(iso * isoline, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn bool _iso_save_df(iso * isoline, datafile * df);
    \brief writes \ref iso tags to \ref datafile 
*/
bool _iso_save_df(iso * isoline, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn iso * _iso_load(const char * filename, const char * isoname, int mode);
    \brief loads \ref iso from ROFF file (see \ref datafile for details)
*/
iso * _iso_load(const char * filename, const char * isoname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn iso * _iso_load_df(datafile * df, const char * isoname);
    \brief reads \ref iso tags from \ref datafile
*/
iso * _iso_load_df(datafile * df, const char * isoname);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn void _iso_info(iso * isoline);
    \brief prints some info about \ref iso
*/
void _iso_info(iso * isoline);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn iso * _get_surfit_iso();
    \brief returns \ref surfit_iso
*/
iso * _get_surfit_iso();

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn void _set_surfit_iso(iso * isoline);
    \brief sets \ref surfit_iso
*/
void _set_surfit_iso(iso * isoline);

SURFIT_EXPORT
/*! \ingroup internal_iso
    \fn void _add_surfit_isos(iso * isoline);
    \brief adds isoline to \ref surfit_isos collection
*/
void _add_surfit_isos(iso * isoline);

}; // namespace surfit;

#endif



