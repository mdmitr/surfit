
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit_grid_line_user_included__
#define __surfit_grid_line_user_included__

namespace surfit {

class grid_line;
class curv;
class grid;
class bitvec;

/*! \ingroup surfit_data_variables
    \var surfit_grid_line
    \brief grid based line

\sa 
\li \ref tcl_grid_line "Tcl commands"

*/
extern SURFIT_EXPORT grid_line * surfit_grid_line;

SURFIT_EXPORT
grid_line * curv_to_grid_line(grid_line * grd_line, const curv * crv, grid * grd);

SURFIT_EXPORT
void debug_print_grid_line(const char * filename,
			   grid_line * grd_line, grid * grd,
			   bitvec * mask_solved, 
			   bitvec * mask_undefined,
			   curv * crv = NULL);

}; // namespace surfit;

#endif

