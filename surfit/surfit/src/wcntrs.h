
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

#ifndef __surfit_wcntrs_included__
#define __surfit_wcntrs_included__

namespace surfit {

class wcntr;

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn bool wcntrs_delall();
    \brief removes all \ref wcntr "wcntrs" from \ref surfit_wcntrs collection
*/
bool wcntrs_delall();

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn bool wcntrs_del(int pos);
    \brief removes \ref wcntr from \ref surfit_wcntrs collection at 'pos' position
*/
bool wcntrs_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn bool wcntrs_read(const char * filename, const char * cntrname, REAL weight, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by);
    \brief reads \ref wcntr from formatted text file and adds it to \ref surfit_wcntr collection 
*/
bool wcntrs_read(const char * filename, const char * cntrname, REAL weight,
		 int columns=3, 
		 int col1=1, int col2=2, int col3=3,
		 const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn bool wcntrs_load(const char * filename, const char * cntrname = NULL);
    \brief reads \ref wcntr from ROFF file (see \ref datafile for details) and adds it to \ref surfit_wcntrs collection 
*/
bool wcntrs_load(const char * filename, const char * cntrname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn wcntr * wcntrs_at(int pos);
    \brief returns \ref wcntr at 'pos' position in \ref surfit_wcntrs collection 
*/
wcntr * wcntrs_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn wcntr * wcntrs_first();
    \brief returns first \ref wcntr in \ref surfit_wcntrs collection 
*/
wcntr * wcntrs_first();

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn wcntr * wcntrs_last();
    \brief returns last \ref wcntr in \ref surfit_wcntrs collection 
*/
wcntr * wcntrs_last();

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn int wcntrs_size();
    \brief returns amount of elements in \ref surfit_wcntrs collection 
*/
int wcntrs_size();

SURFIT_EXPORT
/*! \ingroup tcl_wcntrs
    \fn int wcntrs_info();
    \brief prints information about all \ref wcntr "wcntrs" in \ref surfit_wcntrs collection 
*/
int wcntrs_info();

}; // namespace surfit;

#endif

