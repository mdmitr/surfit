
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

#ifndef __surfit_trend_internal_included__
#define __surfit_trend_internal_included__

class trend;

namespace surfit {

class vec;
class datafile;
class grid;
class task;
class func;
class trend;
class grid_line;

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn bool _trend_check();
    \brief checks for \ref surfit_trend existance
*/
bool _trend_check();

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn trend * _trend_load(const char * filename, const char * funcname, int mode);
    \brief loads trend with name 'funcname' from datafile in active \ref rw_mode. If no 'funcname' specified loads the first one.
    \param filename data file
    \param funcname function name
    \param mode \ref rw_mode
*/
trend * _trend_load(const char * filename, const char * funcname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn trend * _trend_load_df(datafile * df, const char * funcname);
    \brief loads trend named 'funcname' from datafile 
*/
trend * _trend_load_df(datafile * df, const char * funcname);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn void _trend_unload(trend *& fnc);
    \brief unloads trend from memory
*/
bool _trend_unload(trend *& fnc);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn bool _trend_save(trend * fnc, const char * filename, const char * funcname);
    \brief saves trend to file in active \ref rw_mode
    \param fnc func class to save
    \param filename data file
    \param funcname name for function
*/
bool _trend_save(trend * fnc, const char * filename, const char * funcname);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn bool _trend_save_df(trend * fnc, datafile * df);
    \brief writes trend tags to \ref datafile
*/
bool _trend_save_df(trend * fnc, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn bool _trend_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname)
    \brief loads trend from Surfer grd file (ASCII format)
    \param filename grd-file
    \param D1 weight number for operD1 operator
    \param D2 weight number for operD2 operator
    \param trendname name for trend function
*/
trend * _trend_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname); 

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn void _trend_info(trend * fnc);
    \brief prints some info about function
*/
void _trend_info(trend * fnc);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn trend * _trend_project(trend * wfnc, grid * grd);
    \brief recalculates \ref trend "trnd" to new \ref grid "grd" using bilinear interpolation algorithm
*/
trend * _trend_project(trend * trnd, grid * grd);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn trend * _trend_project(trend * wfnc, grid * grd, grid_line * fault_line);
    \brief recalculates \ref trend "trnd" to new grid "grd" using bilinear interpolation algorithm 
    with taking \ref grid_line "fault_line" into account as faults
*/
trend * _trend_project(trend * trnd, grid * grd, grid_line * fault_line);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn func * _trend_to_func(trend * trnd);
    \brief converts \ref trend to \ref func 
*/
func * _trend_to_func(trend * trnd);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn trend * _get_surfit_trend();
    \brief returns pointer to \ref surfit_trend
*/
trend * _get_surfit_trend();

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn void _set_surfit_trend(trend * fnc);
    \brief sets pointer \ref surfit_trend to fnc
*/
void _set_surfit_trend(trend * fnc);

SURFIT_EXPORT
/*! \ingroup internal_trend
    \fn void _add_surfit_trends(trend * fnc);
    \brief adds function fnc to collection \ref surfit_trends
*/
void _add_surfit_trends(trend * fnc);

}; // namespace surfit

#endif

