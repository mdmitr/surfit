
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

#ifndef __surfit__funcs__
#define __surfit__funcs__

namespace surfit {

class func;

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn bool funcs_delall();
    \brief removes all \ref func's from \ref surfit_funcs
*/
bool funcs_delall();

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn bool funcs_del(int pos);
    \brief removes \ref func from \ref surfit_funcs at "pos" position
*/
bool funcs_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn bool funcs_load(const char * filename, const char * funcname = 0)
    \brief loads \ref func from ROFF file (see \ref datafile for details) and adds it to \ref surfit_funcs
*/
bool funcs_load(const char * filename, const char * funcname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn bool funcs_load_grd(const char * filename, const char * funcname = 0)
    \brief loads \ref func from SURFER grd file (ASCII format) and adds it to \ref surfit_funcs
*/
bool funcs_load_grd(const char * filename, const char * funcname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn bool funcs_unload(const char * name);
    \brief removes first func from \ref surfit_funcs named with "name"
*/
bool funcs_unload(const char * name);

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn func * funcs_at(int pos);
    \brief returns \ref func at "pos" position from \ref surfit_funcs
*/
func * funcs_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn func * funcs_first();
    \brief returns first \ref func from \ref surfit_funcs
*/
func * funcs_first();

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn func * funcs_last();
    \brief returns last \ref func from \ref surfit_funcs
*/
func * funcs_last();

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn int funcs_size();
    \brief returns amount of functions in \ref surfit_funcs
*/
int funcs_size();

SURFIT_EXPORT
/*! \ingroup tcl_funcs
    \fn int funcs_info();
    \brief prints information about functions in \ref surfit_funcs
*/
int funcs_info();

}; // namespace surfit;

#endif

