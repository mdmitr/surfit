
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

#ifndef __surfit_areas_included__
#define __surfit_areas_included__

#include "variables_tcl.h"

namespace surfit {

class area;

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn bool areas_delall();
    \brief removes all areas from \ref surfit_areas collection
*/
bool areas_delall();

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn bool areas_del(int pos);
    \brief removes \ref area from \ref surfit_areas collection at 'pos' position
*/
bool areas_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn bool areas_read(const char * filename, const char * areaname, REAL value, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref area from formatted text file and adds it to \ref surfit_areas collection 
*/
bool areas_read(const char * filename, const char * areaname, REAL value=undef_value, 
		int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn bool areas_load(const char * filename, const char * areaname = NULL);
    \brief reads \ref area from ROFF file (see \ref datafile for details) and adds it to \ref surfit_areas collection 
*/
bool areas_load(const char * filename, const char * areaname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn area * areas_at(int pos);
    \brief returns \ref area at 'pos' position in \ref surfit_areas collection 
*/
area * areas_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn area * areas_first();
    \brief returns first \ref area in \ref surfit_areas collection 
*/
area * areas_first();

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn area * areas_last();
    \brief returns last \ref area in \ref surfit_areas collection 
*/
area * areas_last();

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn int areas_size();
    \brief returns amount of elements in \ref surfit_areas collection 
*/
int areas_size();

SURFIT_EXPORT
/*! \ingroup tcl_areas
    \fn int areas_info();
    \brief prints information about all areas in \ref surfit_areas collection 
*/
int areas_info();

}; // namespace surfit;

#endif

