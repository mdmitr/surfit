
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

#ifndef __surfit_area_internal_included__
#define __surfit_area_internal_included__

#include "surfit_data.h"

namespace surfit {

class d_area;
class datafile;
class d_grid;

SURFIT_EXPORT
d_area * _area_read(const char * filename, const char * areaname,
		    int col1, int col2, int skip_lines,
		    int grow_by, const char * mask);

SURFIT_EXPORT
bool _area_write(const d_area * area, const char * filename, const char * mask);

SURFIT_EXPORT
d_area * _area_load(const char * filename, const char * areaname);

SURFIT_EXPORT
d_area * _area_load_df(datafile * df, const char * areaname);

SURFIT_EXPORT
bool _area_save(const d_area * area, const char * filename);

SURFIT_EXPORT
bool _area_save_df(const d_area * area, datafile * df);

SURFIT_EXPORT
void _area_info(const d_area * area);

SURFIT_EXPORT
void _add_surfit_areas(d_area * area);

SURFIT_EXPORT
d_area * _area_intersect_grid(const d_area * area, const d_grid * grd);

}; // namespace surfit;

#endif

