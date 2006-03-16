
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

class d_hist;
class datafile;

SURFIT_EXPORT
d_hist * _hist_read(const char * filename, const char * histname,
		    int col1, int col2, int col3, int skip_lines,
		    int grow_by, const char * mask);

SURFIT_EXPORT
bool _hist_write(const d_hist * hst, const char * filename, const char * mask);

SURFIT_EXPORT
bool _hist_save(const d_hist * hst, const char * filename);

SURFIT_EXPORT
bool _hist_save_df(const d_hist * hst, datafile * df);

SURFIT_EXPORT
d_hist * _hist_load(const char * filename, const char * histname);

SURFIT_EXPORT
d_hist * _hist_load_df(datafile * df, const char * histname);

SURFIT_EXPORT
void _hist_info(const d_hist * hst);

SURFIT_EXPORT
void _add_surfit_hists(d_hist * hst);


}; // namespace surfit;

#endif

