
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

#ifndef __surfit_grd_line_internal_included__
#define __surfit_grd_line_internal_included__

namespace surfit {

class grid_line;
class d_curv;
class datafile;

//! writes \ref grid_line to formatted text file. 
SURFIT_EXPORT
bool _grid_line_write(const grid_line * contour, d_grid * grd, const char * filename, const char * mask);

//! writes \ref grid_line to surfit datafile (see \ref datafile for details)
SURFIT_EXPORT
bool _grid_line_save(const grid_line * contour, d_grid * grd, const char * filename);

//! prints some info about \ref grid_line
SURFIT_EXPORT
void _grid_line_info(const grid_line * contour);

//! converts \ref grid_line to \ref d_curv
SURFIT_EXPORT
d_curv * _grid_line_to_curv(const grid_line * gline, const d_grid * grd);

}; // namespace surfit;

#endif


