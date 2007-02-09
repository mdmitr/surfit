
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

#ifndef __surfit_hist_internal_included__
#define __surfit_hist_internal_included__

namespace surfit {

class d_hist;
class datafile;
class d_surf;


SURFIT_EXPORT
void _hist_info(const d_hist * hst);

SURFIT_EXPORT
void _add_surfit_hists(d_hist * hst);

SURFIT_EXPORT
bool _surf_histeq(d_surf * srf);

}; // namespace surfit;

#endif

