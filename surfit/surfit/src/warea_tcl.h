
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

#ifndef __surfit_warea_tcl_included__
#define __surfit_warea_tcl_included__

namespace surfit {

class warea;

//////////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_warea_save_load
    \fn bool warea_read(const char * filename, const char * wareaname, REAL value, REAL weight, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref warea from formatted text file. Value - value of points in warea, Weight - informational weight
*/
bool warea_read(const char * filename, const char * wareaname, REAL value, REAL weight,
		int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_warea_save_load
    \fn bool warea_write(const char * filename, const char * delimiter);
    \brief saves \ref warea to formatted text file. 
*/
bool warea_write(const char * filename, const char * delimiter);

SURFIT_EXPORT
/*! \ingroup tcl_warea_save_load
    \fn bool warea_save(const char * filename, const char * wareaname = NULL);
    \brief saves \ref warea to ROFF file (see \ref datafile for details)
*/
bool warea_save(const char * filename, const char * wareaname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_warea_save_load
    \fn bool warea_load(const char * filename, const char * wareaname = NULL);
    \brief loads \ref warea from ROFF file (see \ref datafile for details)
*/
bool warea_load(const char * filename, const char * wareaname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_warea_save_load
    \fn bool warea_unload();
    \brief unloads \ref surfit_warea from memory
*/
bool warea_unload();

//////////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_warea_conv
    \fn bool warea_to_area();
    \brief makes \ref surfit_area from \ref surfit_warea
*/
bool warea_to_area();

SURFIT_EXPORT
/*! \ingroup tcl_warea_conv
    \fn bool warea_to_areas();
    \brief makes \ref area from \ref surfit_warea and adds it to \ref surfit_areas
*/
bool warea_to_areas();

SURFIT_EXPORT
/*! \ingroup tcl_warea_conv
    \fn bool warea_to_curv();
    \brief makes \ref surfit_curv from \ref surfit_warea
*/
bool warea_to_curv();

SURFIT_EXPORT
/*! \ingroup tcl_warea_conv
    \fn bool warea_to_curvs();
    \brief makes \ref curv from \ref surfit_warea and adds it to \ref surfit_curvs
*/
bool warea_to_curvs();

SURFIT_EXPORT
/*! \ingroup tcl_warea_conv
    \fn bool warea_to_wareas();
    \brief moves \ref surfit_warea to \ref surfit_wareas
*/
bool warea_to_wareas();

//////////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_warea_other
    \fn bool warea_check();
    \brief checks for \ref surfit_warea existance
*/
bool warea_check();

SURFIT_EXPORT
/*! \ingroup tcl_warea_other
    \fn bool warea_value(REAL value);
    \brief sets \ref warea::value "value" for \ref surfit_warea
*/
bool warea_value(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_warea_other
    \fn bool warea_weight(REAL weight);
    \brief sets \ref warea::weight "weight" for \ref surfit_warea
*/
bool warea_weight(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_warea_save_load
    \fn bool warea_set(warea * warealine);
    \brief sets \ref surfit_warea
*/
bool warea_set(warea * warealine);

SURFIT_EXPORT
/*! \ingroup tcl_warea_save_load
    \fn bool warea_name(const char * new_name, warea * warealine = NULL);
    \brief sets name for \ref surfit_warea or warealine
*/
bool warea_name(const char * new_name = NULL, warea * warealine = NULL);

}; // namespace surfit;

#endif



