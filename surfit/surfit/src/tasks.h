
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

#ifndef __surfit__tasks__
#define __surfit__tasks__

namespace surfit {

class task;

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn bool tasks_load(const char * filename, const char * taskname);
    \brief reads task from ROFF file (see \ref datafile for details) and adds it to \ref surfit_tasks
*/
bool tasks_load(const char * filename, const char * taskname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn bool tasks_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, const char* delimiter, int grow_by);
    \brief reads task from formatted text file and adds it to \ref surfit_tasks 
    \param filename filename with formatted text data
    \param taskname name
    \param columns amount of columns
    \param col1 First column position
    \param col2 Second column position
    \param col3 Third column position
    \param grow_by vector growth
    \param delimiter delimiter (" " or "," or "\t", ...)
*/
bool tasks_read(const char * filename, const char * taskname = NULL, int columns = 3, int col1 = 1, int col2 = 2, int col3 = 3, const char * delimiter = " ", int grow_by = 250);

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn bool tasks_delall();
    \brief removes all elements from \ref surfit_tasks
*/
bool tasks_delall();

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn bool tasks_del(int pos);
    \brief removes \ref task from \ref surfit_tasks at positioin 'pos'
*/
bool tasks_del(int pos = -1);

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn bool task_concat(task * tsk);
    \brief adds scattered data-points from 'tsk' to \ref surfit_task
*/
bool task_concat(task * tsk);

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn task * tasks_at(int pos);
    \brief returns \ref task at position 'pos' in \ref surfit_tasks
*/
task * tasks_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn task * tasks_first();
    \brief returns first \ref task in \ref surfit_tasks
*/
task * tasks_first();

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn task * tasks_last();
    \brief returns last \ref task in \ref surfit_tasks
*/
task * tasks_last();

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn int tasks_size();
    \brief returns amount of elements in \ref surfit_tasks
*/
int tasks_size();

SURFIT_EXPORT
/*! \ingroup tcl_tasks
    \fn int tasks_info();
    \brief prints info about all tasks in \ref surfit_tasks
*/
int tasks_info();

}; // namespace surfit;

#endif

