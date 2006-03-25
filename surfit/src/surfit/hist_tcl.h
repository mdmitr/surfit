
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

SURFIT_EXPORT
bool hist_read(const char * filename, const char * histname=NULL	, 
	       int col1=1, int col2=2, int col3 = 3,
	       const char * delimiter=" \t", int skip_lines = 0, int grow_by=250);

SURFIT_EXPORT
bool hist_write(const char * filename, const char * delimiter = "\t", const char * pos = "0");

SURFIT_EXPORT
bool hist_save(const char * filename, const char * pos = "0");

SURFIT_EXPORT
bool hist_load(const char * filename, const char * histname = NULL);

//////////////
// other

SURFIT_EXPORT
bool hist_from_surf(const char * histname, const char * surf_pos = "0", int intervs = 10);

SURFIT_EXPORT
bool hist_update_surf(const char * hist_pos = "0", const char * surf_pos = "0");

SURFIT_EXPORT
const char * hist_getName(const char * pos = "0");

SURFIT_EXPORT
bool hist_setName(const char * new_name, const char * pos = "0");

SURFIT_EXPORT
bool hist_delall();

SURFIT_EXPORT
bool hist_del(const char * pos = "0");

SURFIT_EXPORT
int hist_size();

SURFIT_EXPORT
void hists_info();


}; // namespace surfit;

#endif

