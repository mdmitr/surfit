
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
// other

bool hist_from_surf(const char * histname, const char * surface_name_or_positioin = "0", size_t intervs = 256);

const char * hist_getName(const char * pos = "0");

bool hist_setName(const char * new_name, const char * pos = "0");

bool hist_delall();

bool hist_del(const char * pos = "0");

int hist_size();

void hists_info();

bool surf_histeq(const char * surface_name_or_positioin = "0");


}; // namespace surfit;

#endif

