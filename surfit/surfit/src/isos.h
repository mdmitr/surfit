
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

#ifndef __surfit_isos_included__
#define __surfit_isos_included__

namespace surfit {

class iso;

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn bool isos_delall();
    \brief removes all isolines from \ref surfit_isos collection
*/
bool isos_delall();

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn bool isos_del(int pos);
    \brief removes isoline from \ref surfit_isos collection at 'pos' position
*/
bool isos_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn bool isos_read(const char * filename, const char * isoname, REAL value, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads isoline from formatted text file and adds it to \ref surfit_isos collection 
*/
bool isos_read(const char * filename, const char * isoname, REAL value, 
	       int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn bool isos_load(const char * filename, const char * isoname = NULL);
    \brief reads isoline from ROFF file (see \ref datafile for details) and adds it to \ref surfit_isos collection 
*/
bool isos_load(const char * filename, const char * isoname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn iso * isos_at(int pos);
    \brief returns \ref iso at 'pos' position in \ref surfit_isos collection 
*/
iso * isos_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn iso * isos_first();
    \brief returns first \ref iso in \ref surfit_isos collection 
*/
iso * isos_first();

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn iso * isos_last();
    \brief returns last \ref iso in \ref surfit_isos collection 
*/
iso * isos_last();

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn int isos_size();
    \brief returns amount of elements in \ref surfit_isos collection 
*/
int isos_size();

SURFIT_EXPORT
/*! \ingroup tcl_isos
    \fn int isos_info();
    \brief prints information about all isolines in \ref surfit_isos collection 
*/
int isos_info();

}; // namespace surfit;

#endif

