
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

#ifndef __surfit_iso_tcl_included__
#define __surfit_iso_tcl_included__

namespace surfit {

class iso;

//////////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_iso_save_load
    \fn bool iso_read(const char * filename, const char * isoname, REAL value, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref iso from formatted text file. Value - isoline level.
*/
bool iso_read(const char * filename, const char * isoname, REAL value, 
	      int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_iso_save_load
    \fn bool iso_write(const char * filename, const char * delimiter);
    \brief saves \ref iso to formatted text file. 
*/
bool iso_write(const char * filename, const char * delimiter);

SURFIT_EXPORT
/*! \ingroup tcl_iso_save_load
    \fn bool iso_save(const char * filename, const char * isoname = NULL);
    \brief saves \ref iso to ROFF file (see \ref datafile for details)
*/
bool iso_save(const char * filename, const char * isoname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_iso_save_load
    \fn bool iso_load(const char * filename, const char * isoname = NULL);
    \brief loads \ref iso from ROFF file (see \ref datafile for details)
*/
bool iso_load(const char * filename, const char * isoname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_iso_save_load
    \fn bool iso_unload();
    \brief unloads \ref surfit_iso from memory
*/
bool iso_unload();

/////////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_iso_conv
    \fn bool iso_to_wiso(REAL weight);
    \brief makes \ref surfit_wiso from \ref surfit_iso with specified informational weight
*/
bool iso_to_wiso(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_iso_conv
    \fn bool iso_to_wisos(REAL weight);
    \brief makes \ref wiso from \ref surfit_iso with specified informational weight and adds it to \ref surfit_wisos
*/
bool iso_to_wisos(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_iso_conv
    \fn bool iso_to_curv();
    \brief makes \ref surfit_curv from \ref surfit_iso
*/
bool iso_to_curv();

SURFIT_EXPORT
/*! \ingroup tcl_iso_conv
    \fn bool iso_to_curvs();
    \brief makes \ref curv from \ref surfit_iso and adds it to \ref surfit_curvs
*/
bool iso_to_curvs();

SURFIT_EXPORT
/*! \ingroup tcl_iso_conv
    \fn bool iso_to_isos();
    \brief moves \ref surfit_iso to \ref surfit_isos
*/
bool iso_to_isos();

/////////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_iso_other
    \fn bool iso_check();
    \brief checks for \ref surfit_iso existance
*/
bool iso_check();

SURFIT_EXPORT
/*! \ingroup tcl_iso_other
    \fn bool iso_value(REAL value);
    \brief sets \ref iso::value for \ref surfit_iso
*/
bool iso_value(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_iso_other
    \fn bool iso_set(iso * isoline);
    \brief sets \ref surfit_iso
*/
bool iso_set(iso * isoline);

SURFIT_EXPORT
/*! \ingroup tcl_iso_other
    \fn bool iso_name(const char * new_name, iso * isoline = NULL);
    \brief sets name of \ref surfit_iso or isoline
*/
bool iso_name(const char * new_name = NULL, iso * isoline = NULL);

}; // namespace surfit;

#endif



