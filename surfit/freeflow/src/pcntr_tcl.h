
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

#ifndef __flow_pcntr_tcl_included__
#define __flow_pcntr_tcl_included__

namespace surfit {

class pcntr;

////////////////////////
// saving and loading

FLOW_EXPORT
/*! \ingroup tcl_pcntr_save_load
    \fn bool pcntr_read(const char * filename, const char * pcntrname, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by);
    \brief reads \ref pcntr "production contour" from formatted text file
*/
bool pcntr_read(const char * filename, const char * pcntrname,
               int columns = 3, 
	       int col1=1, int col2=2, int col3=3,
	       const char * delimiter=" ", int grow_by=250);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_save_load
    \fn bool pcntr_write(const char * filename, const char * delimiter);
    \brief saves \ref pcntr "production contour" to formatted text file. 
*/
bool pcntr_write(const char * filename, const char * delimiter);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_save_load
    \fn bool pcntr_save(const char * filename, const char * pcntrname = NULL);
    \brief saves \ref pcntr "production contour" to ROFF file (see \ref datafile for details)
*/
bool pcntr_save(const char * filename, const char * pcntrname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_save_load
    \fn bool pcntr_load(const char * filename, const char * pcntrname = NULL);
    \brief loads \ref pcntr "production contour" from ROFF file (see \ref datafile for details)
*/
bool pcntr_load(const char * filename, const char * pcntrname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_save_load
    \fn bool pcntr_unload();
    \brief unloads \ref flow_pcntr from memory
*/
bool pcntr_unload();

///////////////
// convers

FLOW_EXPORT
/*! \ingroup tcl_pcntr_conv
    \fn bool pcntr_to_curv();
    \brief makes \ref surfit_curv from \ref flow_pcntr 
*/
bool pcntr_to_curv();

FLOW_EXPORT
/*! \ingroup tcl_pcntr_conv
    \fn bool pcntr_to_curvs();
    \brief makes \ref curv from \ref flow_pcntr and adds it to \ref surfit_curvs
*/
bool pcntr_to_curvs();

FLOW_EXPORT
/*! \ingroup tcl_pcntr_conv
    \fn bool pcntr_to_pcntrs();
    \brief moves \ref flow_pcntr to \ref flow_pcntrs
*/
bool pcntr_to_pcntrs();

///////////////
// other

FLOW_EXPORT
/*! \ingroup tcl_pcntr_other
    \fn bool pcntr_check();
    \brief checks for \ref flow_pcntr existance
*/
bool pcntr_check();

FLOW_EXPORT
/*! \ingroup tcl_pcntr_other
    \fn bool pcntr_set(pcntr * pcontour);
    \brief sets \ref flow_pcntr
*/
bool pcntr_set(pcntr * pcontour);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_other
    \fn bool pcntr_name(const char * new_name = NULL, pcntr * contour = NULL);
    \brief sets name of \ref flow_pcntr or \ref pcntr "contour"
*/
bool pcntr_name(const char * new_name = NULL, pcntr * contour = NULL);

////////////////////
// math

FLOW_EXPORT
/*! \ingroup tcl_pcntr_math
    \fn bool pcntr_plus_real(REAL value);
    \brief adds value to \ref flow_pcntr values
*/
bool pcntr_plus_real(REAL value);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_math
    \fn bool pcntr_minus_real(REAL value);
    \brief deducts value from \ref flow_pcntr values
*/
bool pcntr_minus_real(REAL value);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_math
    \fn bool pcntr_mult_real(REAL value);
    \brief multiplies \ref flow_pcntr values with value
*/
bool pcntr_mult_real(REAL value);

FLOW_EXPORT
/*! \ingroup tcl_pcntr_math
    \fn bool pcntr_div_real(REAL value);
    \brief divides \ref flow_pcntr values with value
*/
bool pcntr_div_real(REAL value);

}; // namespace surfit;

#endif

