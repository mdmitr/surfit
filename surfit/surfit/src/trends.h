
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

#ifndef __surfit_trends_included__
#define __surfit_trends_included__

namespace surfit {

class trend;

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn bool trends_delall();
    \brief removes all \ref trend's from \ref surfit_trends
*/
bool trends_delall();

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn bool trends_del(int pos);
    \brief removes \ref trend from \ref surfit_trends at "pos" position
*/
bool trends_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn bool trends_load(const char * filename, const char * trendname = 0)
    \brief loads \ref trend from ROFF file (see \ref datafile for details) and adds it to \ref surfit_trends
*/
bool trends_load(const char * filename, const char * trendname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn bool trends_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname = 0)
    \brief loads \ref trend from SURFER grd file (ASCII format) and adds it to \ref surfit_trends
*/
bool trends_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn bool trends_unload(const char * name);
    \brief removes first trend from \ref surfit_trends named with "name"
*/
bool trends_unload(const char * name);

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn trend * trends_at(int pos);
    \brief returns \ref trend at "pos" position from \ref surfit_trends
*/
trend * trends_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn trend * trends_first();
    \brief returns first \ref trend from \ref surfit_trends
*/
trend * trends_first();

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn trend * trends_last();
    \brief returns last \ref trend from \ref surfit_trends
*/
trend * trends_last();

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn int trends_size();
    \brief returns amount of trendtions in \ref surfit_trends
*/
int trends_size();

SURFIT_EXPORT
/*! \ingroup tcl_trends
    \fn int trends_info();
    \brief prints information about trendtions in \ref surfit_trends
*/
int trends_info();

}; // namespace surfit;

#endif

