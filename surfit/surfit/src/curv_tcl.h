
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

#ifndef __surfit_curv_tcl_included__
#define __surfit_curv_tcl_included__

namespace surfit {

class curv;

///////////////////////
// saving and loading

SURFIT_EXPORT
/*! \ingroup tcl_curv_save_load
    \fn bool curv_read(const char * filename, const char * curvname, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref curv from formatted text file
*/
bool curv_read(const char * filename, const char * curvname=NULL	, 
               int columns=2, 
	       int col1=1, int col2=2,
	       const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_curv_save_load
    \fn bool curv_write(const char * filename, const char * delimiter);
    \brief saves \ref curv to formatted text file. 
*/
bool curv_write(const char * filename, const char * delimiter);

SURFIT_EXPORT
/*! \ingroup tcl_curv_save_load
    \fn bool curv_save(const char * filename, const char * curvname = NULL);
    \brief saves \ref curv to ROFF file (see \ref datafile for details)
*/
bool curv_save(const char * filename, const char * curvname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_curv_save_load
    \fn bool curv_load(const char * filename, const char * curvname = NULL);
    \brief loads \ref curv from ROFF file (see \ref datafile for details)
*/
bool curv_load(const char * filename, const char * curvname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_curv_save_load
    \fn bool curv_unload();
    \brief unloads \ref surfit_curv from memory
*/
bool curv_unload();

//////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_iso(REAL value);
    \brief converts \ref surfit_curv to \ref surfit_iso
*/
bool curv_to_iso(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_isos(REAL value);
    \brief converts \ref surfit_curv to \ref iso and adds it to \ref surfit_isos
*/
bool curv_to_isos(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_wiso(REAL value, REAL weight);
    \brief converts \ref surfit_curv to \ref surfit_wiso
*/
bool curv_to_wiso(REAL value, REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_wisos(REAL value, REAL weight);
    \brief converts \ref surfit_curv to \ref wiso and adds it to \ref surfit_wisos
*/
bool curv_to_wisos(REAL value, REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_flt();
    \brief converts \ref surfit_curv to \ref surfit_flt
*/
bool curv_to_flt();

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_flts();
    \brief converts \ref surfit_curv to \ref flt and adds it to \ref surfit_flts
*/
bool curv_to_flts();

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_area(REAL value);
    \brief converts \ref surfit_curv to \ref surfit_area
*/
bool curv_to_area(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_areas(REAL value);
    \brief converts \ref surfit_curv to \ref area and adds it to \ref surfit_areas
*/
bool curv_to_areas(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_warea(REAL value, REAL weight);
    \brief converts \ref surfit_curv to \ref surfit_warea
*/
bool curv_to_warea(REAL value, REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_curv_conv
    \fn bool curv_to_wareas(REAL value, REAL weight);
    \brief converts \ref surfit_curv to \ref warea and adds it to \ref surfit_wareas
*/
bool curv_to_wareas(REAL value, REAL weight);

//////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_curv_other
    \fn bool curv_check();
    \brief checks for \ref surfit_curv existance
*/
bool curv_check();

SURFIT_EXPORT
/*! \ingroup tcl_curv_other
    \fn bool curv_set(curv * contour);
    \brief sets \ref surfit_curv
*/
bool curv_set(curv * contour);

SURFIT_EXPORT
/*! \ingroup tcl_curv_other
    \fn bool curv_name(const char * name, curv * crv);
    \brief sets name of \ref surfit_curv or crv
*/
bool curv_name(const char * name = NULL, curv * crv = NULL);

}; // namespace surfit;

#endif

