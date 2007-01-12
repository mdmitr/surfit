
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

#ifndef __surfit_grid_line_user_included__
#define __surfit_grid_line_user_included__

namespace surfit {

class grid_line;
class d_curv;
class d_grid;
class bitvec;

/*! \ingroup surfit_data_variables
    \var surfit_grid_line
    \brief grid based line

\sa 
\li \ref tcl_grid_line "Tcl commands"

*/
extern SURFIT_EXPORT grid_line * surfit_grid_line;

SURFIT_EXPORT
grid_line * curv_to_grid_line(grid_line * grd_line, const d_curv * crv, d_grid * grd);

void draw_bitvec_matlab(FILE * ff, const d_grid * grd, const bitvec * data, const char * color="black");
void draw_grid_line_matlab(FILE * ff, const grid_line * line, const d_grid * grd, const char * color = "black", short thick = 1);
void draw_filled_grid_matlab(FILE * ff, const d_grid * grd, const std::vector<short int> * data);

}; // namespace surfit;

#endif

