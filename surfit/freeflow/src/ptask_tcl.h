
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

#ifndef __flow_ptask_tcl__
#define __flow_ptask_tcl__

namespace surfit {

class vec;
class grid;
class ptask;

/////////////////////
// saving and loading

FLOW_EXPORT
/*! \ingroup tcl_ptask_save_load
    \fn bool ptask_load(const char * filename, const char * ptaskname);
    \brief reads \ref flow_ptask named 'ptaskname' from ROFF file (see \ref datafile for details)
    \param filename filename
    \param ptaskname name
*/
bool ptask_load(const char * filename, const char * ptaskname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_ptask_save_load
    \fn void ptask_read(const char * filename, const char * ptaskname, int columns, int col1, int col2, int col3, const char* delimiter, int grow_by);
    \brief reads \ref flow_ptask from formatted text file
    \param filename filename with formatted text data
    \param ptaskname name
    \param columns amount of columns
    \param col1 First column position
    \param col2 Second column position
    \param col3 Third column position
    \param delimiter delimiter (" " or "'", ...)
    \param grow_by vector growth
*/
void ptask_read(const char * filename, const char * ptaskname = NULL, int columns = 3, int col1 = 1, int col2 = 2, int col3 = 3, const char* delimiter = " ", int grow_by = 250);

FLOW_EXPORT
/*! \ingroup tcl_ptask_save_load
    \fn void ptask_unload();
    \brief unloads \ref flow_ptask from memory
*/
void ptask_unload();

FLOW_EXPORT
/*! \ingroup tcl_ptask_save_load
    \fn bool ptask_save(const char * filename, const char * ptaskname = NULL);
    \brief saves \ref flow_ptask to ROFF file (see \ref datafile for details)
    \param filename filename
    \param ptaskname new name for ptask
*/
bool ptask_save(const char * filename, const char * ptaskname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_ptask_save_load
    \fn bool ptask_write(const char * filename, const char * delimiter);
    \brief saves \ref flow_ptask to formatted text file
    \param filename filename
    \param delimiter delimiter (" " or "'", ...)
*/
bool ptask_write(const char * filename, const char * delimiter = "\t");

//////////////
// math

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn void ptask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes geometrical transform on \ref flow_ptask (shifting and scaling)
*/
void ptask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn void ptask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes inverse to \ref ptask_transform operation
*/
void ptask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_filter_by_defarea();
    \brief removes points from \ref flow_ptask, if \ref surfit_defarea returns false for their coords
*/
bool ptask_filter_by_defarea();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_filter_by_func(REAL eps);
    \brief removes points from \ref flow_ptask, if |z - f(x,y)|>eps, where (x,y,z) - \ref flow_ptask data points, f(x,y) - \ref surfit_func value at point (x,y)
*/
bool ptask_filter_by_func(REAL eps);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_update_by_func();
    \brief sets points values to z = f(x,y), where (x,y,z) - \ref flow_ptask data points, f(x,y) - \ref surfit_func value at point (x,y)
*/
bool ptask_update_by_func();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_minx();
    \brief returns minimum X value of all data-points
*/
REAL ptask_minx();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_maxx();
    \brief returns maximum X value of all data-points
*/
REAL ptask_maxx();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_miny();
    \brief returns minimum Y value of all data-points
*/
REAL ptask_miny();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_maxy();
    \brief returns maximum Y value of all data-points
*/
REAL ptask_maxy();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_minz();
    \brief returns minimum Z value of all data-points
*/
REAL ptask_minz();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_maxz();
    \brief returns maximum Z value of all data-points
*/
REAL ptask_maxz();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_add_noise(REAL std);
    \brief adds noise distributed as N(0,std) to \ref flow_ptask
*/
bool ptask_add_noise(REAL std);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_mean()
    \brief calculates mean value of all data-points in \ref flow_ptask
*/
REAL ptask_mean();

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn REAL ptask_std(REAL mean);
    \brief calculates standart deviation from mean value of \ref flow_ptask
*/
REAL ptask_std(REAL mean);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_plus(ptask * ptsk);
    \brief calculates A = A+B, where A - this class, B - another ptask
*/
bool ptask_plus(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_minus(ptask * ptsk);
    \brief calculates A = A-B, where A - this class, B - another ptask
*/
bool ptask_minus(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_mult(ptask * ptsk);
    \brief calculates A = A*B, where A - this class, B - another ptask
*/
bool ptask_mult(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_div(ptask * ptsk);
    \brief calculates A = A/B, where A - this class, B - another ptask
*/
bool ptask_div(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_set(ptask * ptsk);
    \brief calculates A = B, where A - this class, B - another ptask
*/
bool ptask_set(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_plus_real(REAL val);
    \brief calculates A = A+B, where A - this class, B - some numeric
*/
bool ptask_plus_real(REAL val);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_minus_real(REAL val);
    \brief calculates A = A-B, where A - this class, B - some numeric
*/
bool ptask_minus_real(REAL val);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_mult_real(REAL val);
    \brief calculates A = A*B, where A - this class, B - some numeric
*/
bool ptask_mult_real(REAL val);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool bool ptask_div_real(REAL val);
    \brief calculates A = A/B, where A - this class, B - some numeric
*/
bool ptask_div_real(REAL val);

FLOW_EXPORT
/*! \ingroup tcl_ptask_math
    \fn bool ptask_set_real(REAL val);
    \brief calculates A = B, where A - this class, B - some numeric
*/
bool ptask_set_real(REAL val);

/////////////////
// converting

FLOW_EXPORT
/*! \ingroup tcl_ptask_conv
    \fn bool ptask_to_task();
    \brief makes \ref surfit_task from \ref flow_ptask
*/
bool ptask_to_task();

FLOW_EXPORT
/*! \ingroup tcl_ptask_conv
    \fn bool ptask_to_tasks();
    \brief makes \ref surfit_task from \ref flow_ptask and adds it to \ref surfit_tasks
*/
bool ptask_to_tasks();

FLOW_EXPORT
/*! \ingroup tcl_ptask_conv
    \fn bool task_to_ptask();
    \brief makes \ref flow_ptask from \ref surfit_task
*/
bool task_to_ptask();

FLOW_EXPORT
/*! \ingroup tcl_ptask_conv
    \fn bool task_to_ptasks();
    \brief makes \ref flow_ptask from \ref surfit_task and adds it to \ref flow_ptasks
*/
bool task_to_ptasks();

FLOW_EXPORT
/*! \ingroup tcl_ptask_conv
    \fn bool ptask_to_ptasks();
    \brief moves \ref flow_ptask to \ref flow_ptasks
*/
bool ptask_to_ptasks();

//////////////////
// other

FLOW_EXPORT
/*! \ingroup tcl_ptask_other
    \fn bool ptask_check();
    \brief checks for \ref flow_ptask existance
*/
bool ptask_check();

FLOW_EXPORT
/*! \ingroup tcl_ptask_other
    \fn int ptask_size();
    \brief returns \ref flow_ptask size (in points)
*/
int ptask_size();

FLOW_EXPORT
/*! \ingroup tcl_ptask_other
    \fn bool ptask_name(const char * new_name = NULL);
    \brief prints \ref flow_ptask name. If new_name variable specified - sets \ref flow_ptask name to new_name
*/
bool ptask_name(const char * new_name = NULL);


}; // namespace surfit;

#endif

