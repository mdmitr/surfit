
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

#ifndef __flow_pisos_included__
#define __flow_pisos_included__

namespace surfit {

class piso;

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn bool pisos_delall();
    \brief removes all elements from \ref flow_pisos collection
*/
bool pisos_delall();

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn bool pisos_del(int pos);
    \brief removes \ref piso "pisoline" from \ref flow_pisos collection at 'pos' position
*/
bool pisos_del(int pos);

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn bool pisos_read(const char * filename, const char * pisoname, REAL value, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref piso from formatted text file and adds it to \ref flow_pisos collection 
*/
bool pisos_read(const char * filename, const char * pisoname, REAL value, 
		int columns=2, int col1=1, int col2=2, 
		const char * delimiter=" ", int grow_by=250);

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn bool pisos_load(const char * filename, const char * pisoname = NULL);
    \brief reads \ref piso from ROFF file (see \ref datafile for details) and adds it to \ref flow_pisos collection 
*/
bool pisos_load(const char * filename, const char * pisoname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn piso * pisos_at(int pos);
    \brief returns \ref piso at 'pos' position in \ref flow_pisos collection 
*/
piso * pisos_at(int pos);

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn piso * pisos_first();
    \brief returns first \ref piso in \ref flow_pisos collection 
*/
piso * pisos_first();

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn piso * pisos_last();
    \brief returns last \ref piso in \ref flow_pisos collection 
*/
piso * pisos_last();

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn int pisos_size();
    \brief returns amount of elements in \ref flow_pisos collection 
*/
int pisos_size();

FLOW_EXPORT
/*! \ingroup tcl_pisos
    \fn int pisos_info();
    \brief prints information about all \ref piso "pisolines" in \ref flow_pisos collection 
*/
int pisos_info();

}; // namespace surfit;

#endif

