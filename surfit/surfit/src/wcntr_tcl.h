
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

#ifndef __surfit_wcntr_tcl_included__
#define __surfit_wcntr_tcl_included__

namespace surfit {

class wcntr;

//////////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_save_load
    \fn bool wcntr_read(const char * filename, const char * cntrname, REAL weight, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by);
    \brief reads \ref surfit_wcntr from formatted text file
*/
bool wcntr_read(const char * filename, const char * cntrname, REAL weight,
                int columns=3, 
		int col1=1, int col2=2, int col3=3,
		const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_save_load
    \fn bool wcntr_write(const char * filename, const char * delimiter);
    \brief saves \ref surfit_wcntr to formatted text file. 
*/
bool wcntr_write(const char * filename, const char * delimiter);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_save_load
    \fn bool wcntr_save(const char * filename, const char * cntrname = NULL);
    \brief saves \ref surfit_wcntr to ROFF file (see \ref datafile for details)
*/
bool wcntr_save(const char * filename, const char * cntrname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_save_load
    \fn bool wcntr_load(const char * filename, const char * cntrname = NULL);
    \brief loads \ref surfit_wcntr from ROFF file (see \ref datafile for details)
*/
bool wcntr_load(const char * filename, const char * cntrname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_save_load
    \fn bool wcntr_unload();
    \brief unloads \ref surfit_wcntr from memory
*/
bool wcntr_unload();

/////////////
// math

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_math
    \fn bool wcntr_plus_real(REAL value);
    \brief adds value to \ref surfit_wcntr values
*/
bool wcntr_plus_real(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_math
    \fn bool wcntr_minus_real(REAL value);
    \brief deducts value from \ref surfit_wcntr values
*/
bool wcntr_minus_real(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_math
    \fn bool wcntr_mult_real(REAL value);
    \brief multiplies \ref surfit_wcntr values with value
*/
bool wcntr_mult_real(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_math
    \fn bool wcntr_div_real(REAL value);
    \brief divides \ref surfit_wcntr values with value
*/
bool wcntr_div_real(REAL value);

/////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_conv
    \fn bool wcntr_to_cntr();
    \brief makes \ref surfit_cntr from \ref surfit_wcntr
*/
bool wcntr_to_cntr();

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_conv
    \fn bool wcntr_to_cntrs();
    \brief makes \ref cntr from \ref surfit_wcntr and adds it to \ref surfit_cntrs
*/
bool wcntr_to_cntrs();

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_conv
    \fn bool wcntr_to_curv();
    \brief makes \ref surfit_curv from \ref surfit_wcntr
*/
bool wcntr_to_curv();

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_conv
    \fn bool wcntr_to_curvs();
    \brief makes \ref curv from \ref surfit_wcntr and adds it to \ref surfit_curvs
*/
bool wcntr_to_curvs();

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_conv
    \fn bool wcntr_to_wcntrs();
    \brief moves \ref surfit_wcntr to \ref surfit_wcntrs
*/
bool wcntr_to_wcntrs();

/////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_other
    \fn bool wcntr_check();
    \brief checks for \ref surfit_wcntr existance
*/
bool wcntr_check();

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_other
    \fn bool wcntr_set(wcntr * wcontour);
    \brief sets \ref surfit_wcntr
*/
bool wcntr_set(wcntr * wcontour);

SURFIT_EXPORT
/*! \ingroup tcl_wcntr_other
    \fn bool wcntr_name(const char * new_name, wcntr * wcontour);
    \brief sets name for \ref surfit_wcntr or wcontour
*/
bool wcntr_name(const char * new_name = NULL, wcntr * wcontour = NULL);

}; // namespace surfit;

#endif

