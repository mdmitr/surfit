
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

#ifndef __surfit__ptasks__
#define __surfit__ptasks__

namespace surfit {

class ptask;

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn bool ptasks_load(const char * filename, const char * ptaskname = NULL);
    \brief reads ptask from formatted text file and adds it to \ref flow_ptasks
*/
bool ptasks_load(const char * filename, const char * ptaskname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn bool ptasks_read(const char * filename, const char * ptaskname, int columns, int col1, int col2, int col3, const char* delimiter, int grow_by);
    \brief reads ptask from formatted text file and adds it to \ref flow_ptasks 
    \param filename filename with formatted text data
    \param ptaskname name
    \param columns amount of columns
    \param col1 First column position
    \param col2 Second column position
    \param col3 Third column position
    \param delimiter delimiter (" " or "'", ...)
    \param grow_by vector growth
*/
bool ptasks_read(const char * filename, const char * ptaskname = NULL, int columns = 3, int col1 = 1, int col2 = 2, int col3 = 3, const char* delimiter = " ", int grow_by = 250);

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn bool ptasks_delall();
    \brief removes all elements from \ref flow_ptasks
*/
bool ptasks_delall();

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn bool ptasks_del(int pos = -1);
    \brief removes \ref ptask from \ref flow_ptasks at positioin 'pos'
*/
bool ptasks_del(int pos = -1);

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn ptask * ptasks_at(int pos);
    \brief returns \ref ptask, placed at position 'pos' in \ref flow_ptasks
*/
ptask * ptasks_at(int pos);

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn ptask * ptasks_first();
    \brief returns first \ref ptask in \ref flow_ptasks
*/
ptask * ptasks_first();

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn ptask * ptasks_last();
    \brief returns last \ref ptask in \ref flow_ptasks
*/
ptask * ptasks_last();

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn bool ptask_concat(ptask * ptsk);
    \brief adds scattered data-points from 'ptask' to \ref flow_ptask
*/
bool ptask_concat(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn int ptasks_size();
    \brief returns amount of elements in \ref flow_ptasks
*/
int ptasks_size();

FLOW_EXPORT
/*! \ingroup tcl_ptasks
    \fn int ptasks_info();
    \brief prints info about ptasks in \ref flow_ptasks
*/
int ptasks_info();

}; // namespace surfit;

#endif

