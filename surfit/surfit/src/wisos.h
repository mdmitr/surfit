
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

#ifndef __surfit_wisos_included__
#define __surfit_wisos_included__

namespace surfit {

class wiso;

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn bool wisos_delall();
    \brief removes all isolines with weight from \ref surfit_wisos collection
*/
bool wisos_delall();

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn bool wisos_del(int pos);
    \brief removes isoline with weight from \ref surfit_wisos collection at 'pos' position
*/
bool wisos_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn bool wisos_read(const char * filename, const char * wisoname, REAL value, REAL weight, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads isoline with weight from formatted text file and adds it to \ref surfit_wisos collection 
*/
bool wisos_read(const char * filename, const char * wisoname, REAL value, REAL weight,
		int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn bool wisos_load(const char * filename, const char * wisoname = NULL);
    \brief reads isoline with weight from ROFF file (see \ref datafile for details) and adds it to \ref surfit_wisos collection 
*/
bool wisos_load(const char * filename, const char * wisoname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn wiso * wisos_at(int pos);
    \brief returns \ref wiso at 'pos' position in \ref surfit_wisos collection 
*/
wiso * wisos_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn wiso * wisos_first();
    \brief returns first \ref wiso in \ref surfit_wisos collection 
*/
wiso * wisos_first();

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn wiso * wisos_last();
    \brief returns last \ref wiso in \ref surfit_wisos collection 
*/
wiso * wisos_last();

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn int wisos_size();
    \brief returns amount of elements in \ref surfit_wisos collection 
*/
int wisos_size();

SURFIT_EXPORT
/*! \ingroup tcl_wisos
    \fn int wisos_info();
    \brief prints information about all elements in \ref surfit_wisos collection 
*/
int wisos_info();

}; // namespace surfit;

#endif

