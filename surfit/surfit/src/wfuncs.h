
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

#ifndef __surfit__wfuncs__
#define __surfit__wfuncs__

namespace surfit {

class wfunc;

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn bool wfuncs_delall();
    \brief removes all \ref wfunc's from \ref surfit_wfuncs
*/
bool wfuncs_delall();

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn bool wfuncs_del(int pos);
    \brief removes \ref wfunc from \ref surfit_wfuncs at "pos" position
*/
bool wfuncs_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn bool wfuncs_load(const char * filename, const char * wfuncname = 0)
    \brief loads \ref wfunc from ROFF file (see \ref datafile for details) and adds it to \ref surfit_wfuncs
*/
bool wfuncs_load(const char * filename, const char * wfuncname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn bool wfuncs_load_grd(const char * filename, REAL weight, const char * wfuncname = 0)
    \brief loads \ref wfunc from SURFER grd file (ASCII format) and adds it to \ref surfit_wfuncs
*/
bool wfuncs_load_grd(const char * filename, REAL weight, const char * wfuncname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn bool wfuncs_unload(const char * name);
    \brief removes first wfunc from \ref surfit_wfuncs named with "name"
*/
bool wfuncs_unload(const char * name);

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn wfunc * wfuncs_at(int pos);
    \brief returns \ref wfunc at "pos" position from \ref surfit_wfuncs
*/
wfunc * wfuncs_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn wfunc * wfuncs_first();
    \brief returns first \ref wfunc from \ref surfit_wfuncs
*/
wfunc * wfuncs_first();

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn wfunc * wfuncs_last();
    \brief returns last \ref wfunc from \ref surfit_wfuncs
*/
wfunc * wfuncs_last();

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn int wfuncs_size();
    \brief returns amount of wfunctions in \ref surfit_wfuncs
*/
int wfuncs_size();

SURFIT_EXPORT
/*! \ingroup tcl_wfuncs
    \fn int wfuncs_info();
    \brief prints information about wfunctions in \ref surfit_wfuncs
*/
int wfuncs_info();

}; // namespace surfit;

#endif

