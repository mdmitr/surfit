
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

#ifndef __surfit__mask_internal__
#define __surfit__mask_internal__

namespace surfit {

class d_func;
class d_grid;
class d_mask;
class boolvec;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn bool _mask_save(const d_mask * msk, const char * filename);
    \brief saves mskearea to ROFF file (see \ref datafile for details) in current \ref rw_mode
    \param msk \ref mask class to save
    \param filename data file
*/
bool _mask_save(const d_mask * msk, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn bool _mask_save_df(d_mask * msk, datafile * df);
    \brief writes mask tags to \ref datafile
*/
bool _mask_save_df(const d_mask * msk, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn d_mask * _mask_load(const char * filename, const char * mskname);
    \brief loads mask from data ROFF file (see \ref datafile for details) 
    \param filename data file
    \param mskname name
    \param mskname name for mask
*/
d_mask * _mask_load(const char * filename, const char * mskname);

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn d_mask * _mask_load_df(datafile * df, const char * maskname);
    \brief loads mask named 'maskname' from \ref datafile 
*/
d_mask * _mask_load_df(datafile * df, const char * maskname);

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn bool _mask_load_grd(const char * filename, const char * maskname)
    \brief loads mask from SURFER grd file (ASCII format)
*/
d_mask * _mask_load_grd(const char * filename, const char * maskname); 

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn d_mask * _mask_by_func(const d_func * fnc);
    \brief makes \ref mask by \ref func using unmskined values
*/
d_mask * _mask_by_func(const d_func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn bool _mask_apply_to_func(const d_mask * msk, d_func * fnc);
    \brief sets fnc coefficients to \ref unmsk_value using mask
*/
bool _mask_apply_to_func(const d_mask * msk, d_func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_mask
    \fn void _mask_info(const d_mask * msk);
    \brief prints some info about mskinition area
*/
void _mask_info(const d_mask * msk);

}; // namespace surfit

#endif



