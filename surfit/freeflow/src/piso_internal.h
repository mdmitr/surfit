
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

#ifndef __flow_piso_internal_included__
#define __flow_piso_internal_included__

namespace surfit {

class piso;
class datafile;

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn bool _piso_check();
    \brief checks for \ref flow_piso existance
*/
bool _piso_check();

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn bool _piso_unload();
    \brief unloads \ref flow_piso from memory
*/
bool _piso_unload();

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn piso * _piso_read(const char * filename, const char * pisoname, REAL value, int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref piso from formatted text file. Value - pisoline level.
*/
piso * _piso_read(const char * filename, const char * pisoname, REAL value,
		  int columns, int col1, int col2, int grow_by, const char * mask);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn bool _piso_write(piso * pisoline, const char * filename, const char * mask);
    \brief writes \ref piso to formatted text file. 
*/
bool _piso_write(piso * pisoline, const char * filename, const char * mask);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn bool _piso_save(piso * pisoline, const char * filename, int mode);
    \brief writes \ref piso to ROFF file (see \ref datafile for details)
*/
bool _piso_save(piso * pisoline, const char * filename, int mode);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn bool _piso_save_df(piso * pisoline, datafile * df);
    \brief writes \ref piso tags to \ref datafile. 
*/
bool _piso_save_df(piso * pisoline, datafile * df);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn piso * _piso_load(const char * filename, const char * pisoname, int mode);
    \brief loads \ref piso from ROFF file (see \ref datafile for details)
*/
piso * _piso_load(const char * filename, const char * pisoname, int mode);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn piso * _piso_load_df(datafile * df, const char * pisoname);
    \brief reads \ref piso tags from \ref datafile. 
*/
piso * _piso_load_df(datafile * df, const char * pisoname);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn void _piso_info(piso * pisoline);
    \brief prints some info about \ref piso "pisoline"
*/
void _piso_info(piso * pisoline);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn piso * _get_flow_piso();
    \brief returns \ref flow_piso
*/
piso * _get_flow_piso();

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn void _set_flow_piso(piso * pisoline);
    \brief sets \ref flow_piso
*/
void _set_flow_piso(piso * pisoline);

FLOW_EXPORT
/*! \ingroup internal_piso
    \fn void _add_flow_pisos(piso * pisoline);
    \brief adds \ref piso "pisoline" to \ref flow_pisos collection
*/
void _add_flow_pisos(piso * pisoline);

}; // namespace surfit;

#endif



