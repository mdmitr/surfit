
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

#ifndef __flow_piso_tcl_included__
#define __flow_piso_tcl_included__

namespace surfit {

class piso;

///////////////////////
// saving and loading

FLOW_EXPORT
/*! \ingroup tcl_piso_save_load
    \fn bool piso_read(const char * filename, const char * pisoname, REAL value, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref flow_piso from formatted text file.
*/
bool piso_read(const char * filename, const char * pisoname, REAL value, 
	       int columns=2, int col1=1, int col2=2, 
	       const char * delimiter=" ", int grow_by=250);

FLOW_EXPORT
/*! \ingroup tcl_piso_save_load
    \fn bool piso_write(const char * filename, const char * delimiter);
    \brief saves \ref flow_piso to formatted text file. 
*/
bool piso_write(const char * filename, const char * delimiter);

FLOW_EXPORT
/*! \ingroup tcl_piso_save_load
    \fn bool piso_save(const char * filename, const char * pisoname = NULL);
    \brief saves \ref flow_piso to ROFF file (see \ref datafile for details)
*/
bool piso_save(const char * filename, const char * pisoname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_piso_save_load
    \fn bool piso_load(const char * filename, const char * pisoname = NULL);
    \brief loads \ref flow_piso from ROFF file (see \ref datafile for details)
*/
bool piso_load(const char * filename, const char * pisoname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_piso_save_load
    \fn bool piso_unload();
    \brief unloads \ref flow_piso from memory
*/
bool piso_unload();

/////////////////
// convers

FLOW_EXPORT
/*! \ingroup tcl_piso_conv
    \fn bool piso_to_curv();
    \brief makes \ref surfit_curv from \ref flow_piso
*/
bool piso_to_curv();

FLOW_EXPORT
/*! \ingroup tcl_piso_conv
    \fn bool piso_to_curvs();
    \brief makes \ref curv from \ref flow_piso and adds it to \ref surfit_curvs
*/
bool piso_to_curvs();

FLOW_EXPORT
/*! \ingroup tcl_piso_conv
    \fn bool piso_to_pisos();
    \brief moves \ref flow_piso to \ref flow_pisos
*/
bool piso_to_pisos();

/////////////////
// other

FLOW_EXPORT
/*! \ingroup tcl_piso_other
    \fn bool piso_check();
    \brief checks for \ref flow_piso existance
*/
bool piso_check();

FLOW_EXPORT
/*! \ingroup tcl_piso_other
    \fn bool piso_value(REAL value);
    \brief sets \ref piso::value for \ref flow_piso
*/
bool piso_value(REAL value);

FLOW_EXPORT
/*! \ingroup tcl_piso_other
    \fn bool piso_set(piso * pisoline);
    \brief sets \ref flow_piso
*/
bool piso_set(piso * pisoline);

FLOW_EXPORT
/*! \ingroup tcl_piso_other
    \fn bool piso_name(const char * new_name = NULL, piso * pisoline = NULL);
    \brief sets name of \ref flow_piso or \ref piso "pisoline"
*/
bool piso_name(const char * new_name = NULL, piso * pisoline = NULL);

}; // namespace surfit;

#endif



