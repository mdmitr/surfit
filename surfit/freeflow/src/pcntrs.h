
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

#ifndef __flow_pcntrs_included__
#define __flow_pcntrs_included__

namespace surfit {

class pcntr;

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn bool pcntrs_delall();
    \brief removes all elements from \ref flow_pcntrs collection
*/
bool pcntrs_delall();

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn bool pcntrs_del(int pos);
    \brief removes \ref pcntr "production contour" from \ref flow_pcntrs collection at 'pos' position
*/
bool pcntrs_del(int pos);

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn bool pcntrs_read(const char * filename, const char * cntrname, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by);
    \brief reads \ref pcntr "production contour" from formatted text file and adds it to \ref flow_pcntrs collection 
*/
bool pcntrs_read(const char * filename, const char * pcntrname,
		 int columns=250, 
		 int col1=1, int col2=2, int col3=3,
		 const char * delimiter=" ", int grow_by=250);

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn bool pcntrs_load(const char * filename, const char * pcntrname = NULL);
    \brief reads \ref pcntr "production contour" from ROFF file (see \ref datafile for details) and adds it to \ref flow_pcntrs collection 
*/
bool pcntrs_load(const char * filename, const char * pcntrname = NULL);

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn pcntr * pcntrs_at(int pos);
    \brief returns \ref pcntr at 'pos' position in \ref flow_pcntrs collection 
*/
pcntr * pcntrs_at(int pos);

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn pcntr * pcntrs_first();
    \brief returns first \ref pcntr in \ref flow_pcntrs collection 
*/
pcntr * pcntrs_first();

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn pcntr * pcntrs_last();
    \brief returns last \ref pcntr \ref flow_pcntrs collection 
*/
pcntr * pcntrs_last();

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn int pcntrs_size();
    \brief returns amount of elements in \ref flow_pcntrs collection 
*/
int pcntrs_size();

FLOW_EXPORT
/*! \ingroup tcl_pcntrs
    \fn int pcntrs_info();
    \brief prints information about all \ref pcntr "production contours" in \ref flow_pcntrs collection 
*/
int pcntrs_info();

}; // namespace surfit;

#endif

