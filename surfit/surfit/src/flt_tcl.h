
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

#ifndef __surfit_flt_tcl_included__
#define __surfit_flt_tcl_included__

namespace surfit {

class flt;

//////////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_flt_save_load
    \fn bool flt_read(const char * filename, const char * fltname, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref flt from formatted text file.
*/
bool flt_read(const char * filename, const char * fltname, int columns=2, 
	      int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_flt_save_load
    \fn bool flt_write(const char * filename, const char * delimiter);
    \brief saves \ref flt to formatted text file. 
*/
bool flt_write(const char * filename, const char * delimiter);

SURFIT_EXPORT
/*! \ingroup tcl_flt_save_load
    \fn bool flt_save(const char * filename, const char * fltname = NULL);
    \brief saves \ref flt to ROFF file (see \ref datafile for details)
*/
bool flt_save(const char * filename, const char * fltname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_flt_save_load
    \fn bool flt_load(const char * filename, const char * fltname = NULL);
    \brief loads \ref flt from ROFF file (see \ref datafile for details)
*/
bool flt_load(const char * filename, const char * fltname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_flt_save_load
    \fn bool flt_unload();
    \brief unloads \ref surfit_flt from memory
*/
bool flt_unload();

//////////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_flt_conv
    \fn bool flt_to_curv();
    \brief makes \ref surfit_curv from \ref surfit_flt
*/
bool flt_to_curv();

SURFIT_EXPORT
/*! \ingroup tcl_flt_conv
    \fn bool flt_to_curvs();
    \brief makes \ref curv from \ref surfit_flt and adds it to \ref surfit_curvs
*/
bool flt_to_curvs();

SURFIT_EXPORT
/*! \ingroup tcl_flt_conv
    \fn bool flt_to_grid_line();
    \brief makes \ref surfit_grid_line from \ref surfit_flt using \ref surfit_grid
*/
bool flt_to_grid_line();

SURFIT_EXPORT
/*! \ingroup tcl_flt_conv
    \fn bool flt_to_flts();
    \brief moves \ref surfit_flt to \ref surfit_flts
*/
bool flt_to_flts();

//////////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_flt_other
    \fn bool flt_check();
    \brief checks for \ref surfit_flt existance
*/
bool flt_check();

SURFIT_EXPORT
/*! \ingroup tcl_flt_other
    \fn bool flt_set(flt * fault);
    \brief sets \ref surfit_flt
*/
bool flt_set(flt * fault);

SURFIT_EXPORT
/*! \ingroup tcl_flt_other
    \fn bool flt_name(const char * new_name, flt * fault = NULL);
    \brief sets name for \ref surfit_flt or fault
*/
bool flt_name(const char * new_name = NULL, flt * fault = NULL);

}; // namespace surfit;

#endif



