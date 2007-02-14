
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

#ifndef __surfit_hist_tcl_included__
#define __surfit_hist_tcl_included__

namespace surfit {

//////////////
// save/load

/*! \ingroup tcl_hist_save_load
    \fn bool hist_read(const char * filename, REAL minz, REAL maxz, 
		       const char * histname, int col1,  
		       const char * delimiter, int skip_lines, int grow_by);
    
    \par Tcl syntax:
    hist_read "filename" minz maxz "histname" col1 "delimiter" skip_lines grow_by

    \par Description:
    reads \ref d_hist "histogram" from formatted text file

    \param filename name of formatted text file
    \param histname name for \ref d_hist "histogram" object
    \param minz minimum value for X axis
    \param maxz maximum value for X axis
    \param col1 column with histogram values
    \param delimiter delimiter between columns. May be " ", "\t", "," or other symbols
    \param skip_lines number of lines to skip header
    \param grow_by =250
    
    \par Examples:
    \li hist_read "C:\\hist.txt" "my_hist" 0 256 
*/
bool hist_read(const char * filename, REAL minz, REAL maxz, const char * histname = NULL, 
	       int col1 = 1, const char * delimiter = " \t", int skip_lines = 0, int grow_by = 250);

/*! \ingroup tcl_hist_save_load
    \fn bool hist_write(const char * filename, const char * hist_name_or_position = "0");
    
    \par Tcl syntax:
    hist_write "filename" "hist_name_or_position" 

    \par Description:
    saves \ref d_hist "histogram" to formatted text file
*/
bool hist_write(const char * filename, const char * hist_name_or_position = "0");

//////////////
// other

bool hist_from_surf(const char * surface_name_or_positioin = "0", size_t intervs = 64, const char * histname = NULL);

const char * hist_getName(const char * pos = "0");

bool hist_setName(const char * new_name, const char * pos = "0");

bool hist_delall();

bool hist_del(const char * pos = "0");

int hist_size();

void hists_info();

bool surf_histeq(const char * surface_name_or_positioin = "0", const char * histogram_name_or_position = "0");


}; // namespace surfit;

#endif

