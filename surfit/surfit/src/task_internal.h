
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

#ifndef __surfit__task_internal__
#define __surfit__task_internal__

#include <vector>

namespace surfit {

class vec;
class grid;
class datafile;
class task;
class wtask;

////////////////////////////////////////////////
////////////////////////////////////////////////
//                task io                   //
////////////////////////////////////////////////
////////////////////////////////////////////////

///////////////
// load

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn task * _task_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, const char * mask, int grow_by);
    \brief reads task from formatted text file
    \return pointer to task class
    \param filename filename
    \param taskname taskname
    \param columns columns in text file
    \param col1 column number in text file for X coordinates
    \param col2 column number in text file for Y coordinates
    \param col3 column number in text file for Z coordinates
    \param mask mask for scanf
    \param grow_by vector's grow factor
*/
task * _task_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, const char * mask, int grow_by);

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn task * _task_load(const char * filename, const char * taskname, int mode);
    \brief reads task from ROFF file (see \ref datafile for details)
    \return pointer to task class
    \param filename filename
    \param taskname name
    \param mode rw_mode (0 = bin, 1 = asc)
*/
task * _task_load(const char * filename, const char * taskname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn task * _task_load_df(datafile * df, const char * taskname);
    \brief reads task from \ref datafile
*/
task * _task_load_df(datafile * df, const char * taskname);

//////////////
// save

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn bool _task_write(task * tsk, const char * filename, const char * mask);
    \brief saves task to formatted text file
    \param tsk pointer to task
    \param filename filename
    \param mask mask for printf
*/
bool _task_write(task * tsk, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn bool _task_save(task * tsk, const char * filename, int mode);
    \brief saves task to ROFF file (see \ref datafile for details)
    \param filename filename
    \param tsk pointer to task
    \param mode rw_mode (0 = bin, 1 = asc)
*/
bool _task_save(task * tsk, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn bool _task_save(task * tsk, const char * filename, int mode);
    \brief saves task to \ref datafile
*/
bool _task_save_df(task * tsk, datafile * df);

//////////////
// stuff

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn bool _task_check();
    \brief for internal \ref surfit_task checking
*/
bool _task_check();

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn void _task_info(task * tsk);
    \brief prints some info about tsk
*/
void _task_info(task * tsk);

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn task * _get_surfit_task();
    \brief returns \ref surfit_task
*/
task * _get_surfit_task();

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn void _set_surfit_task(task * tsk);
    \brief sets \ref surfit_task
*/
void _set_surfit_task(task * tsk);

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn void _add_surfit_tasks(task * tsk);
    \brief adds tsk to \ref surfit_tasks
*/
void _add_surfit_tasks(task * tsk);

SURFIT_EXPORT
/*! \ingroup internal_task
    \fn wtask * _task_to_wtask(task * tsk, REAL weight);
    \brief makes \ref wtask from \ref task with specified informational weight
*/
wtask * _task_to_wtask(task * tsk, REAL weight);

}; // namespace surfit;

#endif

