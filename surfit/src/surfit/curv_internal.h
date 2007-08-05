
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

#ifndef __surfit_curv_internal_included__
#define __surfit_curv_internal_included__

namespace surfit {

class d_curv;
class datafile;
class d_grid;

//! reads \ref d_curv from formatted text file
SURFIT_EXPORT
d_curv * _curv_read(const char * filename, const char * curvname,
		    int col1, int col2, int skip_lines,
		    int grow_by, const char * mask);

//! loads \ref d_curv from surfit \ref datafile
SURFIT_EXPORT
d_curv * _curv_load(const char * filename, const char * curvname);

//! reads \ref d_curv tags from \ref datafile. 
SURFIT_EXPORT
d_curv * _curv_load_df(datafile * df, const char * curvname);

//! continues to read \ref d_curv from datafile if tag is already read
SURFIT_EXPORT
bool _curv_load_df_tag_readed(datafile * df, d_curv *& crv);

//! writes \ref d_curv to formatted text file. 
SURFIT_EXPORT
bool _curv_write(const d_curv * contour, const char * filename, const char * mask);

//! writes \ref d_curv to surfit \ref datafile
SURFIT_EXPORT
bool _curv_save(const d_curv * contour, const char * filename);

//! writes \ref d_curv tags to \ref datafile. 
SURFIT_EXPORT
bool _curv_save_df(const d_curv * contour, datafile * df);

//! prints some info about \ref d_curv
SURFIT_EXPORT
void _curv_info(const d_curv * contour);

//! adds \ref d_curv to \ref surfit_curv collection
SURFIT_EXPORT
void _add_surfit_curvs(d_curv * contour);

//! bounds \ref d_curv with rect 
SURFIT_EXPORT
d_curv * _curv_intersect_grid(const d_curv * crv, const d_grid * grd);

}; // namespace surfit;

#endif

