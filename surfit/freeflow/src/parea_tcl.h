
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

#ifndef __flow_parea_tcl_included__
#define __flow_parea_tcl_included__

#include <float.h>

namespace surfit {

class parea;

///////////////////////////
// saving and loading

FLOW_EXPORT
/*! \ingroup tcl_parea_save_load
    \fn bool parea_read(const char * filename, const char * pareaname, REAL pvalue, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref parea "production area" from formatted text file. pvalue - value of area production (for example \f$ m^3/sec \f$)
*/
bool parea_read(const char * filename, const char * pareaname, 
		REAL pvalue = FLT_MAX, int columns=2, 
		int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

FLOW_EXPORT
/*! \ingroup tcl_parea_save_load
    \fn bool parea_write(const char * filename, const char * delimiter);
    \brief saves \ref parea "production area" to formatted text file. 
*/
bool parea_write(const char * filename, const char * delimiter);

FLOW_EXPORT
/*! \ingroup tcl_parea_save_load
    \fn bool parea_save(const char * filename, const char * pareaname = NULL);
    \brief saves \ref parea "production area" to ROFF file (see \ref datafile for details)
*/
bool parea_save(const char * filename, const char * pareaname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_parea_save_load
    \fn bool parea_load(const char * filename, const char * pareaname = NULL);
    \brief loads \ref parea "production area" from ROFF file (see \ref datafile for details)
*/
bool parea_load(const char * filename, const char * pareaname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_parea_save_load
    \fn bool parea_unload();
    \brief unloads \ref flow_parea from memory
*/
bool parea_unload();

////////////////////////////
// converting

FLOW_EXPORT
/*! \ingroup tcl_parea_conv
    \fn bool parea_to_curv();
    \brief makes \ref surfit_curv from \ref flow_parea
*/
bool parea_to_curv();

FLOW_EXPORT
/*! \ingroup tcl_parea_conv
    \fn bool parea_to_curvs();
    \brief makes \ref curv from \ref flow_parea and adds it to \ref surfit_curvs
*/
bool parea_to_curvs();

FLOW_EXPORT
/*! \ingroup tcl_parea_conv
    \fn bool parea_to_pareas();
    \brief moves \ref flow_parea to \ref flow_pareas
*/
bool parea_to_pareas();

/////////////
// other

FLOW_EXPORT
/*! \ingroup tcl_parea_other
    \fn bool parea_check();
    \brief checks for \ref flow_parea existance
*/
bool parea_check();

FLOW_EXPORT
/*! \ingroup tcl_parea_other
    \fn bool parea_value(REAL value);
    \brief sets \ref parea::value "value" for \ref flow_parea 
*/
bool parea_value(REAL value);

FLOW_EXPORT
/*! \ingroup tcl_parea_other
    \fn bool parea_set(parea * par);
    \brief sets \ref flow_parea
*/
bool parea_set(parea * par);

FLOW_EXPORT
/*! \ingroup tcl_parea_other
    \fn bool parea_name(const char * new_name, parea * ar);
    \brief sets name for \ref flow_parea or \ref parea "arealine"
*/
bool parea_name(const char * new_name = NULL, parea * ar = NULL);


}; // namespace surfit;

#endif



