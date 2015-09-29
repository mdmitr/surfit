
/*------------------------------------------------------------------------------
 *	$Id: $
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
%{
#include "hist_tcl.h"
%}

namespace surfit {

surfit::boolvec * hist(const char * hist_pos = "*", REAL penalty_factor = -1, size_t threshold = 5);

// hist
surfit::boolvec * hist_read(const char * filename, REAL minz, REAL maxz, const char * histname = NULL, 
							int col1 = 1, const char * delimiter = " \t", int skip_lines = 0, int grow_by = 250);
surfit::boolvec * hist_write(const char * filename, const char * hist_name = "*", bool three_columns = true);

surfit::boolvec * hist_from_surf(const char * surf_pos = "*", size_t intervs = 64, REAL from = FLT_MAX, REAL to = FLT_MAX, const char * histname = NULL);
surfit::boolvec * hist_from_pnts(const char * pnts_pos = "*", size_t intervs = 64, REAL from = FLT_MAX, REAL to = FLT_MAX, const char * histname = NULL);
surfit::boolvec * surf_adj_hist(const char * surf_name = "*", const char * hist_name = NULL);

surfit::strvec * hist_getName(const char * pos = "*");
const char * hist_getNameAt(int pos);
surfit::boolvec * hist_setName(const char * new_name, const char * pos = "*");
void hist_del(const char * pos = "*");
int hist_size();
void hists_info();

}; // namespace surfit

