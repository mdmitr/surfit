
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

#ifndef __surfit_wtask_tcl__
#define __surfit_wtask_tcl__

namespace surfit {

class vec;
class grid;
class wtask;

////////////////////////////////////////////////
////////////////////////////////////////////////
//                wtask io                    //
////////////////////////////////////////////////
////////////////////////////////////////////////

///////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_wtask_save_load
    \fn bool wtask_load(const char * filename, const char * taskname = NULL);
    \brief reads \ref surfit_wtask named 'taskname' from ROFF file (see \ref datafile for details)
    \param filename filename
    \param taskname name
*/
bool wtask_load(const char * filename, const char * taskname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_save_load
    \fn void wtask_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, int col4, const char* delimiter, int grow_by);
    \brief reads \ref surfit_task from formatted text file
    \param filename filename with formatted text data
    \param taskname name
    \param columns amount of columns
    \param col1 First column position
    \param col2 Second column position
    \param col3 Third column position
    \param col4 Fourth column position
    \param delimiter delimiter (" " or "," or "\t", ...)
    \param grow_by vector growth
*/
void wtask_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, int col4, const char* delimiter, int grow_by);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_save_load
    \fn void wtask_unload();
    \brief unloads \ref surfit_wtask from memory
*/
void wtask_unload();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_save_load
    \fn bool wtask_save(const char * filename, const char * taskname = NULL);
    \brief saves \ref surfit_wtask to ROFF file (see \ref datafile for details)
    \param filename filename
    \param taskname new name for wtask
*/
bool wtask_save(const char * filename, const char * taskname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_save_load
    \fn bool wtask_write(const char * filename, const char * delimiter);
    \brief saves \ref surfit_wtask to formatted text file
    \param filename filename
    \param delimiter delimiter (" " or "'", ...)
*/
bool wtask_write(const char * filename, const char * delimiter = "\t");

//////////////
// math

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn void wtask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes geometrical transform on \ref surfit_wtask (shifting and scaling)
*/
void wtask_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn void wtask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes inverse to \ref wtask_transform operation
*/
void wtask_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_filter_by_defarea();
    \brief removes all points from \ref surfit_wtask for which \ref surfit_defarea is undefined
*/
bool wtask_filter_by_defarea();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_filter_by_func(REAL eps)
    \brief removes points from \ref surfit_wtask, if \f$ |z - f(x,y)| > \varepsilon \f$, where (x,y,z) - \ref surfit_wtask data points, f(x,y) - \ref surfit_func value at point (x,y)
*/
bool wtask_filter_by_func(REAL eps);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_update_by_func();
    \brief sets points values to z = f(x,y), where (x,y,z) - \ref surfit_wtask data points, f(x,y) - \ref surfit_func value at point (x,y)
*/
bool wtask_update_by_func();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_minx();
    \brief returns minimum X value of all data-points
*/
REAL wtask_minx();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_maxx();
    \brief returns maximum X value of all data-points
*/
REAL wtask_maxx();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_miny();
    \brief returns minimum Y value of all data-points
*/
REAL wtask_miny();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_maxy();
    \brief returns maximum Y value of all data-points
*/
REAL wtask_maxy();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_minz();
    \brief returns minimum Z value of all data-points
*/
REAL wtask_minz();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_maxz();
    \brief returns maximum Z value of all data-points
*/
REAL wtask_maxz();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_add_noise(REAL std);
    \brief adds noise distributed ad N(0,std) to \ref surfit_wtask
*/
bool wtask_add_noise(REAL std);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_mean()
    \brief calculates mean value of all data-points in \ref surfit_task
*/
REAL wtask_mean();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn REAL wtask_std(REAL mean);
    \brief calculates standart deviation from mean value (for \ref surfit_task)
*/
REAL wtask_std(REAL mean);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_plus(wtask * wtsk);
    \brief calculates A = A+B, where A - this class, B - another task
*/
bool wtask_plus(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_minus(wtask * wtask);
    \brief calculates A = A-B, where A - this class, B - another wtask
*/
bool wtask_minus(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_mult(wtask * wtsk);
    \brief calculates A = A*B, where A - this class, B - another wtask
*/
bool wtask_mult(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_div(wtask * wtsk);
    \brief calculates A = A/B, where A - this class, B - another wtask
*/
bool wtask_div(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_set(wtask * wtsk);
    \brief calculates A = B, where A - this class, B - another wtask
*/
bool wtask_set(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool bool wtask_plus_real(REAL val);
    \brief calculates A = A+B, where A - this class, B - some numeric
*/
bool wtask_plus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool bool wtask_minus_real(REAL val);
    \brief calculates A = A-B, where A - this class, B - some numeric
*/
bool wtask_minus_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool bool wtask_mult_real(REAL val);
    \brief calculates A = A*B, where A - this class, B - some numeric
*/
bool wtask_mult_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool bool wtask_div_real(REAL val);
    \brief calculates A = A/B, where A - this class, B - some numeric
*/
bool wtask_div_real(REAL val);

SURFIT_EXPORT
/*! \ingroup tcl_wtask_math
    \fn bool wtask_set_real(REAL val);
    \brief calculates A = B, where A - this class, B - some numeric
*/
bool wtask_set_real(REAL val);

//////////////
// converse

SURFIT_EXPORT
/*! \ingroup tcl_wtask_conv
    \fn bool wtask_to_task();
    \brief makes \ref surfit_task from \ref surfit_task 
*/
bool wtask_to_task();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_conv
    \fn bool wtask_to_tasks();
    \brief makes \ref task from \ref surfit_wtask and
    adds it to \ref surfit_wtasks
*/
bool wtask_to_tasks();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_conv
    \fn bool wtask_to_wtasks();
    \brief moves \ref surfit_wtask to \ref surfit_wtasks
*/
bool wtask_to_wtasks();

//////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_wtask_other
    \fn bool wtask_check();
    \brief checks for \ref surfit_wtask existance
*/
bool wtask_check();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_other
    \fn int wtask_size();
    \brief returns \ref surfit_wtask size (in points)
*/
int wtask_size();

SURFIT_EXPORT
/*! \ingroup tcl_wtask_other
    \fn bool wtask_name(const char * new_name, wtask * wtsk = NULL);
    \brief sets name of \ref surfit_wtask or wtsk
*/
bool wtask_name(const char * new_name, wtask * wtsk = NULL);

}; // namespace surfit;

#endif

