
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

#ifndef __surfit_flts_included__
#define __surfit_flts_included__

namespace surfit {

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn bool flts_delall();
    \brief removes all elements from \ref surfit_flts collection
*/
bool flts_delall();

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn bool flts_del(int pos);
    \brief removes \ref flt from \ref surfit_flts collection at 'pos' position
*/
bool flts_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn bool flts_read(const char * filename, const char * fltname, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads fault from formatted text file and adds it to \ref surfit_flts collection 
*/
bool flts_read(const char * filename, const char * fltname, int columns=2, 
	       int col1=1, int col2=2, const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn bool flts_load(const char * filename, const char * fltname = NULL);
    \brief reads fault from ROFF file (see \ref datafile for details) and adds it to \ref surfit_flts collection 
*/
bool flts_load(const char * filename, const char * fltname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn flt * flts_at(int pos);
    \brief returns \ref flt at 'pos' position in \ref surfit_flts collection 
*/
flt * flts_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn flt * flts_first();
    \brief returns first \ref flt in \ref surfit_isos collection 
*/
flt * flts_first();

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn flt * flts_last();
    \brief returns last \ref flt in \ref surfit_flts collection 
*/
flt * flts_last();

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn int flts_size();
    \brief returns amount of elements in \ref surfit_flts collection 
*/
int flts_size();

SURFIT_EXPORT
/*! \ingroup tcl_flts
    \fn int flts_info();
    \brief prints information about all faults in \ref surfit_flts collection 
*/
int flts_info();

}; // namespace surfit;

#endif

