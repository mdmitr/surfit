
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

#ifndef __flow_parea_internal_included__
#define __flow_parea_internal_included__

namespace surfit {

class parea;
class datafile;

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn bool _parea_check();
    \brief checks for \ref flow_parea existance
*/
bool _parea_check();

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn bool _parea_unload();
    \brief unloads \ref flow_parea from memory
*/
bool _parea_unload();

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn parea * _parea_read(const char * filename, const char * pareaname, REAL value,	int columns, int col1, int col2, int grow_by, const char * mask);
    \brief reads \ref parea from formatted text file.
*/
parea * _parea_read(const char * filename, const char * pareaname, REAL value,
		    int columns, int col1, int col2, int grow_by, const char * mask);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn bool _parea_write(parea * parealine, const char * filename, const char * mask);
    \brief writes \ref parea to formatted text file. 
*/
bool _parea_write(parea * parealine, const char * filename, const char * mask);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn bool _parea_save(parea * parealine, const char * filename, int mode);
    \brief writes \ref parea to ROFF file (see \ref datafile for details) 
*/
bool _parea_save(parea * parealine, const char * filename, int mode);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn bool _parea_save_df(parea * ar, datafile * df);
    \brief writes \ref parea tags to \ref datafile. 
*/
bool _parea_save_df(parea * ar, datafile * df);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn parea * _parea_load(const char * filename, const char * pareaname, int mode);
    \brief loads \ref parea from ROFF file (see \ref datafile for details)
*/
parea * _parea_load(const char * filename, const char * pareaname, int mode);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn parea * _parea_load_df(datafile * df, const char * pareaname);
    \brief reads \ref parea tags from \ref datafile. 
*/
parea * _parea_load_df(datafile * df, const char * pareaname);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn void _parea_info(parea * parealine);
    \brief prints some info about \ref parea "parealine"
*/
void _parea_info(parea * parealine);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn parea * _get_flow_parea();
    \brief returns pointer to \ref flow_parea
*/
parea * _get_flow_parea();

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn void _set_flow_parea(parea * parealine);
    \brief sets \ref flow_parea
*/
void _set_flow_parea(parea * parealine);

FLOW_EXPORT
/*! \ingroup internal_parea
    \fn void _add_flow_pareas(parea * parealine);
    \brief adds \ref parea "parealine" to \ref flow_pareas collection
*/
void _add_flow_pareas(parea * parealine);

}; // namespace surfit;

#endif



