
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

#ifndef __flow_pcntr_internal_included__
#define __flow_pcntr_internal_included__

namespace surfit {

class pcntr;
class datafile;

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn bool _pcntr_check();
    \brief checks for \ref flow_pcntr existance
*/
bool _pcntr_check();

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn bool _pcntr_unload();
    \brief unloads \ref flow_pcntr from memory
*/
bool _pcntr_unload();

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn pcntr * _pcntr_read(const char * filename, const char * pcntrname, int columns, int col1, int col2, int col3, int grow_by, const char * mask);
    \brief reads \ref pcntr from formatted text file
*/
pcntr * _pcntr_read(const char * filename, const char * pcntrname,
		    int columns, 
		    int col1, int col2, int col3,
		    int grow_by, const char * mask);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn bool _pcntr_write(pcntr * contour, const char * filename, const char * mask);
    \brief writes \ref pcntr to formatted text file. 
*/
bool _pcntr_write(pcntr * contour, const char * filename, const char * mask);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn bool _pcntr_save(pcntr * contour, const char * filename, int mode);
    \brief writes \ref pcntr to ROFF file (see \ref datafile for details)
*/
bool _pcntr_save(pcntr * contour, const char * filename, int mode);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn bool _pcntr_save_df(pcntr * contour, datafile * df);
    \brief writes \ref pcntr tags to \ref datafile. 
*/
bool _pcntr_save_df(pcntr * contour, datafile * df);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn pcntr * _pcntr_load(const char * filename, const char * pcntrname, int mode);
    \brief loads \ref pcntr from ROFF file (see \ref datafile for detials)
*/
pcntr * _pcntr_load(const char * filename, const char * pcntrname, int mode);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn pcntr * _pcntr_load_df(datafile * df, const char * pcntrname);
    \brief reads \ref pcntr tags from \ref datafile. 
*/
pcntr * _pcntr_load_df(datafile * df, const char * pcntrname);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn void _pcntr_info(pcntr * contour);
    \brief prints some info about \ref pcntr "contour"
*/
void _pcntr_info(pcntr * contour);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn pcntr * _get_flow_pcntr();
    \brief returns \ref flow_pcntr
*/
pcntr * _get_flow_pcntr();

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn void _set_flow_pcntr(pcntr * contour);
    \brief sets \ref flow_pcntr
*/
void _set_flow_pcntr(pcntr * contour);

FLOW_EXPORT
/*! \ingroup internal_pcntr
    \fn void _add_flow_pcntrs(pcntr * contour);
    \brief adds \ref pcntr "contour" to \ref flow_pcntr collection
*/
void _add_flow_pcntrs(pcntr * contour);

}; // namespace surfit;

#endif

