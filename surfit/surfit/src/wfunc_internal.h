
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

#ifndef __surfit__wfunc_internal__
#define __surfit__wfunc_internal__

#include <vector>

namespace surfit {

class datafile;
class vec;
class datafile;
class grid;
class wfunc;
class wtask;
class grid_line;

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn bool _wfunc_check();
    \brief checks for \ref surfit_wfunc existance
*/
bool _wfunc_check();

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn bool _wfunc_save(wfunc * fnc, const char * filename, const char * wfuncname);
    \brief saves \ref wfunc to ROFF file (see \ref datafile for details) in active \ref rw_mode
    \param fnc wfunc class to save
    \param filename data file
    \param wfuncname name for wfunction
*/
bool _wfunc_save(wfunc * fnc, const char * filename, const char * wfuncname);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn bool _wfunc_save_df(wfunc * fnc, datafile * df);
    \brief writes wfunc tags to \ref datafile
*/
bool _wfunc_save_df(wfunc * fnc, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn wfunc * _wfunc_load(const char * filename, const char * wfuncname, int mode);
    \brief loads \ref wfunc named 'wfuncname' from ROFF file (see \ref datafile for details) in active \ref rw_mode
    \param filename data file
    \param wfuncname name
    \param mode \ref rw_mode
*/
wfunc * _wfunc_load(const char * filename, const char * wfuncname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn wfunc * _wfunc_load_df(datafile * df, const char * wfuncname);
    \brief loads wfunc named 'wfuncname' from \ref datafile 
*/
wfunc * _wfunc_load_df(datafile * df, const char * wfuncname);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn bool _wfunc_load_grd(const char * filename, REAL weight, const char * wfuncname)
    \brief loads wfunc from Surfer grd file (ASCII format)
*/
wfunc * _wfunc_load_grd(const char * filename, REAL weight, const char * wfuncname); 

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn void _wfunc_unload(wfunc *& fnc);
    \brief unloads \ref wfunc from memory
*/
bool _wfunc_unload(wfunc *& fnc);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn wtask * _wfunc_to_wtask(wfunc * fnc);
    \brief converts \ref wfunc to \ref wtask
*/
wtask * _wfunc_to_wtask(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn void _wfunc_info(wfunc * fnc);
    \brief prints some info about \ref wfunc
*/
void _wfunc_info(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn wfunc * _wfunc_project(wfunc * wfnc, grid * grd);
    \brief recalculates \ref wfunc "wfnc" to new \ref grid "grd" using bilinear interpolation algorithm
*/
wfunc * _wfunc_project(wfunc * wfnc, grid * grd);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn wfunc * _wfunc_project(wfunc * wfnc, grid * grd, grid_line * fault_line);
    \brief recalculates \ref wfunc "wfnc" to new grid "grd" using bilinear interpolation algorithm 
    with taking \ref grid_line "fault_line" into account as faults
*/
wfunc * _wfunc_project(wfunc * wfnc, grid * grd, grid_line * fault_line);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn func * _wfunc_to_func(wfunc * wfnc);
    \brief converts \ref wfunc to \ref func 
*/
func * _wfunc_to_func(wfunc * wfnc);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn wfunc * _get_surfit_wfunc();
    \brief returns pointer to \ref surfit_wfunc
*/
wfunc * _get_surfit_wfunc();

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn void _set_surfit_wfunc(wfunc * fnc);
    \brief sets pointer of \ref surfit_wfunc to fnc
*/
void _set_surfit_wfunc(wfunc * fnc);

SURFIT_EXPORT
/*! \ingroup internal_wfunc
    \fn void _add_surfit_wfuncs(wfunc * fnc);
    \brief adds fnc to \ref surfit_wfuncs
*/
void _add_surfit_wfuncs(wfunc * fnc);

}; // namespace surfit;

#endif

