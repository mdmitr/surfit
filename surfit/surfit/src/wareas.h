
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

#ifndef __surfit_wareas_included__
#define __surfit_wareas_included__

namespace surfit {

class warea;

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn bool wareas_delall();
    \brief removes all wareas from \ref surfit_wareas collection
*/
bool wareas_delall();

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn bool wareas_del(int pos);
    \brief removes \ref warea from \ref surfit_wareas collection at 'pos' position
*/
bool wareas_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn bool wareas_read(const char * filename, const char * wareaname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);
    \brief reads \ref warea from formatted text file and adds it to \ref surfit_wareas collection 
*/
bool wareas_read(const char * filename, const char * wareaname, REAL value, REAL weight, 
		 int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn bool wareas_load(const char * filename, const char * wareaname = NULL);
    \brief reads \ref warea from ROFF file (see \ref datafile for details) and adds it to \ref surfit_wareas collection 
*/
bool wareas_load(const char * filename, const char * wareaname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn warea * wareas_at(int pos);
    \brief returns \ref warea at 'pos' position in \ref surfit_wareas collection 
*/
warea * wareas_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn warea * wareas_first();
    \brief returns first \ref warea in \ref surfit_wareas collection 
*/
warea * wareas_first();

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn warea * wareas_last();
    \brief returns last \ref warea in \ref surfit_wareas collection 
*/
warea * wareas_last();

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn int wareas_size();
    \brief returns amount of elements in \ref surfit_wareas collection 
*/
int wareas_size();

SURFIT_EXPORT
/*! \ingroup tcl_wareas
    \fn int wareas_info();
    \brief prints information about all wareas in \ref surfit_wareas collection 
*/
int wareas_info();

}; // namespace surfit;

#endif

