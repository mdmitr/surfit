
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

#ifndef __flow_pareas_included__
#define __flow_pareas_included__

namespace surfit {

class parea;

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn bool pareas_delall();
    \brief removes all \ref parea "production areas" from \ref flow_pareas collection
*/
bool pareas_delall();

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn bool pareas_del(int pos);
    \brief removes \ref parea "production area" from \ref flow_pareas collection at 'pos' position
*/
bool pareas_del(int pos);

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn bool pareas_read(const char * filename, const char * pareaname, REAL value, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref parea "production area" from formatted text file and adds it to \ref flow_pareas collection 
*/
bool pareas_read(const char * filename, const char * pareaname, REAL value, 
		 int columns=2, int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn bool pareas_load(const char * filename, const char * pareaname = NULL);
    \brief reads \ref parea "production area" from ROFF file (see \ref datafile for details) and adds it to \ref flow_pareas collection 
*/
bool pareas_load(const char * filename, const char * pareaname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn area * pareas_at(int pos);
    \brief returns \ref parea "production area" at 'pos' position in \ref flow_pareas collection 
*/
parea * pareas_at(int pos);

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn area * pareas_first();
    \brief returns first \ref parea "production area" in \ref flow_pareas collection 
*/
parea * pareas_first();

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn area * pareas_last();
    \brief returns last \ref parea "produciton area" in \ref flow_pareas collection 
*/
parea * pareas_last();

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn int pareas_size();
    \brief returns amount of elements in \ref flow_pareas collection 
*/
int pareas_size();

FLOW_EXPORT
/*! \ingroup tcl_pareas
    \fn int pareas_info();
    \brief prints information about all \ref parea "production areas" in \ref surfit_areas collection 
*/
int pareas_info();

}; // namespace surfit;

#endif

