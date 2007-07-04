
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

#include <float.h>

namespace surfit {

//////////////
// save/load

/*! \ingroup tcl_hist_save_load
    \fn bool hist_read(const char * filename, REAL minz, REAL maxz, 
		       const char * histname, int col1,  
		       const char * delimiter, int skip_lines, int grow_by);
    
    \par Tcl syntax:
    hist_read \ref file "filename" minz maxz "histname" col1 "delimiter" skip_lines grow_by

    \par Description:
    reads \ref d_hist "histogram" from formatted text file

    \param filename \ref file "name" of formatted text file
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
boolvec * hist_read(const char * filename, REAL minz, REAL maxz, const char * histname = NULL, 
		int col1 = 1, const char * delimiter = " \t", int skip_lines = 0, int grow_by = 250);

/*! \ingroup tcl_hist_save_load
    \fn bool hist_write(const char * filename, const char * hist_name = "*", bool three_columns = true);
    
    \par Tcl syntax:
    hist_write "filename" \ref str "hist_name" value

    \par Description:
    saves \ref d_hist "histogram" to formatted text file. Writes histogram interval bounds if three_columns is 1
*/
boolvec * hist_write(const char * filename, const char * hist_name = "*", bool three_columns = true);

//////////////
// other

boolvec * hist_from_surf(const char * surface_name = "*", size_t intervs = 64, REAL from = FLT_MAX, REAL to = FLT_MAX, const char * histname = NULL);

boolvec * hist_from_pnts(const char * points_name = "*", size_t intervs = 64, REAL from = FLT_MAX, REAL to = FLT_MAX, const char * histname = NULL);

strvec * hist_getName(const char * pos = "*");

/*! \ingroup tcl_hist_other
    \fn const char * hist_getNameAt(int pos);
    
    \par Tcl syntax:
    hist_getNameAt position

    \par Description:
    returns name of \ref d_hist at position "pos"
*/
const char * hist_getNameAt(int pos);

boolvec * hist_setName(const char * new_name, const char * pos = "*");

void hist_del(const char * pos = "*");

int hist_size();

void hists_info();

boolvec * surf_adj_hist(const char * surface_name = "*", const char * histogram_name = NULL);

}; // namespace surfit;

#endif

