
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

#ifndef __surfit_cntrs_included__
#define __surfit_cntrs_included__

namespace surfit {

class cntr;

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn bool cntrs_delall();
    \brief removes all contours from \ref surfit_cntrs collection
*/
bool cntrs_delall();

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn bool cntrs_del(int pos);
    \brief removes contour from \ref surfit_cntrs collection at 'pos' position
*/
bool cntrs_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn bool cntrs_read(const char * filename, const char * cntrname, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by);
    \brief reads contour from formatted text file and adds it to \ref surfit_cntr collection 
*/
bool cntrs_read(const char * filename, const char * cntrname,
		int columns=3, 
		int col1=1, int col2=2, int col3=3,
		const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn bool cntrs_load(const char * filename, const char * cntrname = NULL);
    \brief reads contour from datafile (binary format) and adds it to \ref surfit_cntrs collection 
*/
bool cntrs_load(const char * filename, const char * cntrname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn cntr * cntrs_at(int pos);
    \brief returns pointer to contour at 'pos' position in \ref surfit_cntrs collection 
*/
cntr * cntrs_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn cntr * cntrs_first();
    \brief returns pointer to first contour in \ref surfit_cntrs collection 
*/
cntr * cntrs_first();

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn cntr * cntrs_last();
    \brief returns pointer to last contour in \ref surfit_cntrs collection 
*/
cntr * cntrs_last();

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn int cntrs_size();
    \brief returns amount of elements in \ref surfit_cntrs collection 
*/
int cntrs_size();

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn int cntrs_info();
    \brief prints information about all contours in \ref surfit_cntrs collection 
*/
int cntrs_info();

SURFIT_EXPORT
/*! \ingroup tcl_cntrs
    \fn bool cntrs_to_wcntrs(REAL weight);
    \brief converts all contours from \ref surfit_cntrs to 
    contours with specified informational weight and 
    places them to \ref surfit_wcntrs
*/
bool cntrs_to_wcntrs(REAL weight);

}; // namespace surfit;

#endif

