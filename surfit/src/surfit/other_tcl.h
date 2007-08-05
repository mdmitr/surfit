
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
    \par Tcl syntax:
    init_threads cnt

    \par Description:
    sets max number of threads to execute
*/
void init_threads(int cnt);

/*! \ingroup tcl_other
    \par Tcl syntax:
    get_threads

    \par Description:
    returns max number of threads to execute
*/
int get_threads();

/*! \ingroup tcl_other
    \par Tcl syntax:
    file_info "filename"
    
    \par Description:
    prints info about surfit datafile contents
*/
char * file_info(const char * filename);

/*! \ingroup tcl_other
    \par Tcl syntax:
    file_load "filename"
     
    \par Description:
    automatically recognizes file format and loads data
*/
void file_load(const char * filename);

/*! \ingroup tcl_other
    \par Tcl syntax:
    file_save "filename"

    \par Description:
    saves all \ref datatypes "data" to surfit datafile
*/
bool file_save(const char * filename);

/*! \ingroup tcl_other
    \par Tcl syntax:
    clear_data

    \par Description:
    removes all data from memory
*/
void clear_data();

/*! \ingroup tcl_other
    \par Tcl syntax:
    mem_info

    \par Description:
    prints information about \ref datatypes "data" in memory
*/
void mem_info();

/*! \ingroup tcl_other
    \par Tcl syntax:
    datafile_mode

    \par Description
    return current datafile mode. This mode tells how to use surfit datafiles for
    saving various data in surfit native format. Two modes allowed : \ref datafile_new
    and \ref datafile_append
*/
const char * datafile_mode();

/*! \ingroup tcl_other
    \par Tcl syntax:
    datafile_new

    \par Description
    Sets \ref datafile_mode to "new" mode. This means that each time you saving
    your data into datafile, the datafile first will be cleaned up and then data will be saved.
*/
const char * datafile_new();

/*! \ingroup tcl_other
    \par Tcl syntax:
    datafile_append

    \par Description
    Sets \ref datafile_mode to "append" mode. This means that each time you saving
    your data into datafile, data will be added to the end of datafile.
*/
const char * datafile_append();

};

#endif

