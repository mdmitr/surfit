
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

#ifndef __surfit_wiso_tcl_included__
#define __surfit_wiso_tcl_included__

namespace surfit {

class wiso;

//////////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_wiso_save_load
    \fn bool wiso_read(const char * filename, const char * isoname, REAL value, REAL weight, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref wiso from formatted text file. Value - isoline level. Weight - informational weight
*/
bool wiso_read(const char * filename, const char * isoname, REAL value, REAL weight,
	       int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_save_load
    \fn bool wiso_write(const char * filename, const char * delimiter);
    \brief saves \ref wiso to formatted text file. 
*/
bool wiso_write(const char * filename, const char * delimiter);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_save_load
    \fn bool wiso_save(const char * filename, const char * isoname = NULL);
    \brief saves \ref wiso to ROFF file (see \ref datafile for details)
*/
bool wiso_save(const char * filename, const char * isoname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_save_load
    \fn bool wiso_load(const char * filename, const char * isoname = NULL);
    \brief loads \ref wiso from ROFF file (see \ref datafile for details)
*/
bool wiso_load(const char * filename, const char * isoname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_save_load
    \fn bool wiso_unload();
    \brief unloads \ref surfit_wiso from memory
*/
bool wiso_unload();

//////////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_wiso_conv
    \fn bool wiso_to_iso();
    \brief makes \ref surfit_iso from \ref surfit_wiso
*/
bool wiso_to_iso();

SURFIT_EXPORT
/*! \ingroup tcl_wiso_conv
    \fn bool wiso_to_isos();
    \brief makes \ref iso from \ref surfit_wiso and adds it to \ref surfit_isos
*/
bool wiso_to_isos();

SURFIT_EXPORT
/*! \ingroup tcl_wiso_conv
    \fn bool wiso_to_curv();
    \brief makes \ref surfit_curv from \ref surfit_wiso
*/
bool wiso_to_curv();

SURFIT_EXPORT
/*! \ingroup tcl_wiso_conv
    \fn bool wiso_to_curvs();
    \brief makes \ref curv from \ref surfit_wiso and adds it to \ref surfit_curvs
*/
bool wiso_to_curvs();

SURFIT_EXPORT
/*! \ingroup tcl_wiso_conv
    \fn bool wiso_to_wisos();
    \brief moves \ref surfit_wiso to \ref surfit_wisos
*/
bool wiso_to_wisos();

//////////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_wiso_other
    \fn bool wiso_check();
    \brief checks for \ref surfit_wiso existance
*/
bool wiso_check();

SURFIT_EXPORT
/*! \ingroup tcl_wiso_other
    \fn bool wiso_value(REAL value);
    \brief sets \ref wiso::value "value" for \ref surfit_wiso
*/
bool wiso_value(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_other
    \fn bool wiso_weight(REAL weight);
    \brief sets \ref wiso::weight "informational weight" for \ref surfit_wiso
*/
bool wiso_weight(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_other
    \fn bool wiso_set(wiso * wisoline);
    \brief sets \ref surfit_wiso
*/
bool wiso_set(wiso * wisoline);

SURFIT_EXPORT
/*! \ingroup tcl_wiso_other
    \fn bool wiso_name(const char * name, wiso * wisoline = NULL);
    \brief sets name of \ref surfit_wiso of wisoline
*/
bool wiso_name(const char * name = NULL, wiso * wisoline = NULL);

}; // namespace surfit;

#endif



