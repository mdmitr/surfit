
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

#ifndef __surfit_task_tcl__
#define __surfit_task_tcl__

namespace surfit {

class vec;
class grid;
class task;

////////////////////////////////////////////////
////////////////////////////////////////////////
//                task io                   //
////////////////////////////////////////////////
////////////////////////////////////////////////

///////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_task_save_load
    \fn bool task_load(const char * filename, const char * taskname = NULL);
    \brief reads \ref surfit_task named 'taskname' from datafile
    \param filename filename
    \param taskname name
*/
bool task_load(const char * filename, const char * taskname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_task_save_load
    \fn void task_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, const char* delimiter, int grow_by);
    \brief reads \ref surfit_task from formatted text file
    \param filename filename with formatted text data
    \param taskname name
    \param columns amount of columns
    \param col1 First column position
    \param col2 Second column position
    \param col3 Third column position
    \param delimiter delimiter (" " or "," or "\t", ...)
    \param grow_by vector growth
*/
void task_read(const char * filename, const char * taskname = NULL, int columns = 3, int col1 = 1, int col2 = 2, int col3 = 3, const char * delimiter = " ", int grow_by = 250);

SURFIT_EXPORT
/*! \ingroup tcl_task_save_load
    \fn void task_unload();
    \brief unloads \ref surfit_task from memory
*/
void task_unload();

SURFIT_EXPORT
/*! \ingroup tcl_task_save_load
    \fn bool task_save(const char * filename, const char * taskname = NULL);
    \brief saves \ref surfit_task to ROFF file (see \ref datafile for details)
    \param filename filename
    \param taskname new name for task
*/
bool task_save(const char * filename, const char * taskname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_task_save_load
    \fn bool task_write(const char * filename, const char * delimiter);
    \brief saves \ref surfit_task to formatted text file
    \param filename filename
    \param delimiter delimiter (" " or "'", ...)
*/
bool task_write(const char * filename, const char * delimiter = "\t");

//////////////
// math

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn void task_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes geometrical transform on \ref surfit_task (shifting and scaling)
*/
void task_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn void task_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes inverse to \ref task_transform operation
*/
void task_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_filter_by_defarea();
    \brief removes all points from \ref surfit_task for which \ref surfit_defarea is undefined
*/
bool task_filter_by_defarea();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_filter_by_func(REAL eps)
    \brief removes points from \ref surfit_task, if \f$ |z - f(x,y)| > \varepsilon \f$, where (x,y,z) - \ref surfit_task data points, f(x,y) - \ref surfit_func value at point (x,y)
*/
bool task_filter_by_func(REAL eps);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_update_by_func();
    \brief set points values to z = f(x,y), where (x,y,z) - \ref surfit_task data points, f(x,y) - \ref surfit_func value at point (x,y)
*/
bool task_update_by_func();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_minx();
    \brief returns minimum X value of all data-points
*/
REAL task_minx();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_maxx();
    \brief returns maximum X value of all data-points
*/
REAL task_maxx();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_miny();
    \brief returns minimum Y value of all data-points
*/
REAL task_miny();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_maxy();
    \brief returns maximum Y value of all data-points
*/
REAL task_maxy();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_minz();
    \brief returns minimum Z value of all data-points
*/
REAL task_minz();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_maxz();
    \brief returns maximum Z value of all data-points
*/
REAL task_maxz();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_add_noise(REAL std);
    \brief adds noise distributed as N(0,std) to \ref surfit_task
*/
bool task_add_noise(REAL std);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_mean()
    \brief calculates mean value of all data-points in \ref surfit_task
*/
REAL task_mean();

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn REAL task_std(REAL mean);
    \brief calculates standart deviation value from mean value (for \ref surfit_task)
*/
REAL task_std(REAL mean);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_plus(task * tak);
    \brief calculates A = A+B, where A - this class, B - another task
*/
bool task_plus(task * tsk);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_minus(task * tsk);
    \brief calculates A = A-B, where A - this class, B - another task
*/
bool task_minus(task * tsk);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_mult(task * tsk);
    \brief calculates A = A*B, where A - this class, B - another task
*/
bool task_mult(task * tsk);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_div(task * tsk);
    \brief calculates A = A/B, where A - this class, B - another task
*/
bool task_div(task * tsk);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_set(task * tsk);
    \brief calculates A = B, where A - this class, B - another task
*/
bool task_set(task * tsk);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_plus_real(REAL val);
    \brief calculates A = A+B, where A - this class, B - some numeric
*/
bool task_plus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_minus_real(REAL val);
    \brief calculates A = A-B, where A - this class, B - some numeric
*/
bool task_minus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_mult_real(REAL val);
    \brief calculates A = A*B, where A - this class, B - some numeric
*/
bool task_mult_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_div_real(REAL val);
    \brief calculates A = A/B, where A - this class, B - some numeric
*/
bool task_div_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_task_math
    \fn bool task_set_real(REAL val);
    \brief calculates A = B, where A - this class, B - some numeric
*/
bool task_set_real(REAL val);

//////////////
// converse

SURFIT_EXPORT
/*! \ingroup tcl_task_conv
    \fn bool task_to_wtask(REAL weight);
    \brief makes \ref surfit_wtask from \ref surfit_task with specified informational weight
*/
bool task_to_wtask(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_task_conv
    \fn bool task_to_wtasks(REAL weight);
    \brief makes \ref wtask from \ref surfit_task with specified informational weight and
    adds it to \ref surfit_wtasks
*/
bool task_to_wtasks(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_task_conv
    \fn bool task_to_tasks();
    \brief moves \ref surfit_task to \ref surfit_tasks
*/
bool task_to_tasks();

//////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_task_other
    \fn bool task_check();
    \brief checks for \ref surfit_task existance
*/
bool task_check();

SURFIT_EXPORT
/*! \ingroup tcl_task_other
    \fn int task_size();
    \brief returns \ref surfit_task size (amount of points)
*/
int task_size();

SURFIT_EXPORT
/*! \ingroup tcl_task_other
    \fn bool task_name(const char * new_name, task * tsk = NULL);
    \brief sets name of \ref surfit_task or specified task "tsk"
*/
bool task_name(const char * new_name, task * tsk = NULL);


}; // namespace surfit;

#endif

