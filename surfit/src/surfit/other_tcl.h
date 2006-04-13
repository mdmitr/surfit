
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit_other_tcl_included__
#define __surfit_other_tcl_included__

namespace surfit {

/*! \ingroup tcl_other
    \fn init_threads(int cnt);

    \par Tcl syntax:
    init_threads cnt

    \par Description:
    sets max number of threads to execute
*/
void init_threads(int cnt);

/*! \ingroup tcl_other
    \fn int get_threads();

    \par Tcl syntax:
    get_threads

    \par Description:
    returns max number of threads to execute
*/
int get_threads();

/*! \ingroup tcl_other
    \fn char * file_info(const char * filename);

    \par Tcl syntax:
    file_info "filename"
    
    \par Description:
    prints info about surfit datafile contents
*/
char * file_info(const char * filename);

/*! \ingroup tcl_other
    \fn void file_load(const char * filename);

    \par Tcl syntax:
    file_load "filename"
     
    \par Description:
    automatically recognizes file format and loads data
*/
void file_load(const char * filename);

/*! \ingroup tcl_other
    \fn bool file_save(const char * filename);

    \par Tcl syntax:
    file_save "filename"

    \par Description:
    saves all \ref datatypes "data" to surfit datafile
*/
bool file_save(const char * filename);

/*! \ingroup tcl_other
    \fn void clear_data();

    \par Tcl syntax:
    clear_data

    \par Description:
    removes all data from memory
*/
void clear_data();

/*! \ingroup tcl_other
    \fn void mem_info();

    \par Tcl syntax:
    mem_info

    \par Description:
    prints information about \ref datatypes "data" in memory
*/
void mem_info();

};

#endif

