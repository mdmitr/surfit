
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

#ifndef __surfit__wtasks__
#define __surfit__wtasks__

namespace surfit {

class wtask;

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn bool wtasks_load(const char * filename, const char * taskname = NULL);
    \brief reads \ref wtask from ROFF file (see \ref datafile for details) and adds it to \ref surfit_wtasks
*/
bool wtasks_load(const char * filename, const char * taskname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn bool wtasks_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, int col4, const char* delimiter, int grow_by);
    \brief reads \ref wtask from formatted text file and addsit to \ref surfit_wtasks 
    \param filename filename with formatted text data
    \param taskname name
    \param columns amount of columns
    \param col1 First column position
    \param col2 Second column position
    \param col3 Third column position
    \param col4 Fourth column position
    \param delimiter delimiter (" " or "'", ...)
    \param grow_by vector growth
*/
bool wtasks_read(const char * filename, const char * taskname = NULL, int columns = 4, int col1 = 1, int col2 = 2, int col3 = 3, int col4 = 4, const char* delimiter = " ", int grow_by = 250);

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn bool wtasks_delall();
    \brief removes all elements from \ref surfit_wtasks
*/
bool wtasks_delall();

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn bool wtasks_del(int pos = -1);
    \brief removes wtask from \ref surfit_wtasks at positioin 'pos'
*/
bool wtasks_del(int pos = -1);

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn bool wtask_concat(wtask * wtsk);
    \brief adds scattered data-points from 'wtsk' to \ref surfit_wtask
*/
bool wtask_concat(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn wtask * wtasks_at(int pos);
    \brief returns \ref wtask at position 'pos' in \ref surfit_wtasks
*/
wtask * wtasks_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn wtask * wtasks_first();
    \brief returns first \ref wtask in \ref surfit_wtasks
*/
wtask * wtasks_first();

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn wtask * wtasks_last();
    \brief returns last \ref wtask in \ref surfit_wtasks
*/
wtask * wtasks_last();

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn int wtasks_size();
    \brief returns amount of elements in \ref surfit_wtasks
*/
int wtasks_size();

SURFIT_EXPORT
/*! \ingroup tcl_wtasks
    \fn int wtasks_info();
    \brief prints info about wtasks in \ref surfit_wtasks
*/
int wtasks_info();

}; // namespace surfit;

#endif

