
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

#ifndef __surfit_cntr_tcl_included__
#define __surfit_cntr_tcl_included__

namespace surfit {

class cntr;

//////////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_read(const char * filename, const char * cntrname, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by);
    \brief reads \ref cntr from formatted text file
*/
bool cntr_read(const char * filename, const char * cntrname, 
               int columns=3, 
	       int col1=1, int col2=2, int col3=3,
	       const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_write(const char * filename, const char * delimiter);
    \brief saves \ref cntr to formatted text file. 
*/
bool cntr_write(const char * filename, const char * delimiter);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_save(const char * filename, const char * cntrname = NULL);
    \brief saves \ref cntr to ROFF file (see \ref datafile for details)
*/
bool cntr_save(const char * filename, const char * cntrname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_load(const char * filename, const char * cntrname = NULL);
    \brief loads \ref cntr from ROFF file (see \ref datafile for details)
*/
bool cntr_load(const char * filename, const char * cntrname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_save_load
    \fn bool cntr_unload();
    \brief unloads \ref surfit_cntr from memory
*/
bool cntr_unload();

///////////////
// math

SURFIT_EXPORT
/*! \ingroup tcl_cntr_math
    \fn bool cntr_plus_real(REAL value);
    \brief adds value to \ref surfit_cntr values
*/
bool cntr_plus_real(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_math
    \fn bool cntr_minus_real(REAL value);
    \brief deducts value from \ref surfit_cntr values
*/
bool cntr_minus_real(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_math
    \fn bool cntr_mult_real(REAL value);
    \brief multiplies \ref surfit_cntr values with value
*/
bool cntr_mult_real(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_math
    \fn bool cntr_div_real(REAL value);
    \brief divides \ref surfit_cntr values with value
*/
bool cntr_div_real(REAL value);

///////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_wcntr(REAL weight);
    \brief makes \ref surfit_cntr from \ref surfit_wcntr with specified informational weight
*/
bool cntr_to_wcntr(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_wcntrs(REAL weight);
    \brief makes \ref cntr from \ref surfit_wcntr with specified informational weight and adds it to \ref surfit_wcntrs
*/
bool cntr_to_wcntrs(REAL weight);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_curv();
    \brief makes \ref surfit_curv from \ref surfit_cntr 
*/
bool cntr_to_curv();

SURFIT_EXPORT
/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_curvs();
    \brief makes \ref curv from \ref surfit_cntr and adds it to \ref surfit_curvs
*/
bool cntr_to_curvs();

SURFIT_EXPORT
/*! \ingroup tcl_cntr_conv
    \fn bool cntr_to_cntrs();
    \brief moves \ref surfit_cntr to \ref surfit_cntrs
*/
bool cntr_to_cntrs();

///////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_cntr_other
    \fn bool cntr_check();
    \brief checks for \ref surfit_cntr existance
*/
bool cntr_check();

SURFIT_EXPORT
/*! \ingroup tcl_cntr_other
    \fn bool cntr_set(cntr * contour);
    \brief sets \ref surfit_cntr
*/
bool cntr_set(cntr * contour);

SURFIT_EXPORT
/*! \ingroup tcl_cntr_other
    \fn bool cntr_name(const char * new_name, cntr * contour = NULL);
    \brief sets name of \ref surfit_cntr or contour
*/
bool cntr_name(const char * new_name = NULL, cntr * contour = NULL);

}; // namespace surfit;

#endif

