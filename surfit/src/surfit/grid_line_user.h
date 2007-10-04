
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
class shortvec;
class sizetvec;

/*! \ingroup surfit_data_variables
    \var surfit_grid_line
    \brief grid based line
*/
extern SURFIT_EXPORT grid_line * surfit_grid_line;

//! adds section 
SURFIT_EXPORT
void add_sect(sizetvec * nns, 
	      REAL X1, REAL Y1, REAL X2, REAL Y2,
	      d_grid * grd2);

//! converts \ref d_curv
SURFIT_EXPORT
sizetvec * curv_to_nns(const d_curv * crv, d_grid * grd);

//! converts \ref d_curv into \ref grid_line using \ref d_grid
SURFIT_EXPORT
grid_line * curv_to_grid_line(grid_line * grd_line, const d_curv * crv, d_grid * grd);

//! debug drawing function
void draw_bitvec_matlab(FILE * ff, const d_grid * grd, const bitvec * data, const char * color="black");
//! debug drawing function
void draw_grid_line_matlab(FILE * ff, const grid_line * line, const d_grid * grd, const char * color = "black", short thick = 1);
//! debug drawing function
void draw_filled_grid_matlab(FILE * ff, const d_grid * grd, const shortvec * data);

}; // namespace surfit;

#endif

