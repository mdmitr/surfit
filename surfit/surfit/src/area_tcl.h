
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

#ifndef __surfit_area_tcl_included__
#define __surfit_area_tcl_included__

#include "variables_tcl.h"

namespace surfit {

class area;

//////////////////
// save and load

SURFIT_EXPORT
/*! \ingroup tcl_area_save_load
    \fn bool area_read(const char * filename, const char * areaname, REAL value, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref area from formatted text file. Value - value of points in area
*/
bool area_read(const char * filename, const char * areaname, REAL value = undef_value, 
               int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_area_save_load
    \fn bool area_write(const char * filename, const char * delimiter);
    \brief saves \ref area to formatted text file. 
*/
bool area_write(const char * filename, const char * delimiter=" ");

SURFIT_EXPORT
/*! \ingroup tcl_area_save_load
    \fn bool area_save(const char * filename, const char * areaname = NULL);
    \brief saves \ref area to datafile (binary format). 
*/
bool area_save(const char * filename, const char * areaname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_area_save_load
    \fn bool area_load(const char * filename, const char * areaname = NULL);
    \brief loads \ref area from datafile (binary format). 
*/
bool area_load(const char * filename, const char * areaname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_area_save_load
    \fn bool area_unload();
    \brief unloads \ref surfit_area from memory
*/
bool area_unload();

/////////////
// convers

SURFIT_EXPORT
/*! \ingroup tcl_area_conv
    \fn bool area_to_curv();
    \brief makes \ref surfit_curv from \ref surfit_area
*/
bool area_to_curv();

SURFIT_EXPORT
/*! \ingroup tcl_area_conv
    \fn bool area_to_curvs();
    \brief makes \ref curv from \ref surfit_area and adds it to \ref surfit_curvs
*/
bool area_to_curvs();

SURFIT_EXPORT
/*! \ingroup tcl_area_conv
    \fn bool area_to_areas();
    \brief moves \ref surfit_area to \ref surfit_areas
*/
bool area_to_areas();

/////////////
// other

SURFIT_EXPORT
/*! \ingroup tcl_area_other
    \fn bool area_check();
    \brief checks for \ref surfit_area existance
*/
bool area_check();

SURFIT_EXPORT
/*! \ingroup tcl_area_other
    \fn bool area_value(REAL value);
    \brief sets \ref area::value "value" for \ref surfit_area 
*/
bool area_value(REAL value);

SURFIT_EXPORT
/*! \ingroup tcl_area_other
    \fn bool area_value_undef();
    \brief sets \ref area::value "value" for \ref surfit_area to undefined
*/
bool area_value_undef();

SURFIT_EXPORT
/*! \ingroup tcl_area_other
    \fn bool area_set(area * arealine);
    \brief sets \ref surfit_area
*/
bool area_set(area * arealine);

SURFIT_EXPORT
/*! \ingroup tcl_area_other
    \fn bool area_name(const char * new_name, area * ar = NULL);
    \brief sets name for \ref surfit_area or arealine
*/
bool area_name(const char * new_name = NULL, area * arealine = NULL);

}; // namespace surfit;

#endif



