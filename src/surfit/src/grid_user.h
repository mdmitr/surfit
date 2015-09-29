
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

#ifndef __surfit_grid_user_included__
#define __surfit_grid_user_included__

#include "vec.h"
#include <vector>
#include "grid.h"
#include <assert.h>

namespace surfit {

class bitvec;

/*! \var surfit_grid
    \brief equidistant \ref d_grid

    This class describes equidistant rectangular grid (rectangular region comprised of evenly 
spaced rows and columns), presented with cells (intersection of a rows and columns). Each 
cell have center point, which
is grid node. To set the grid it is necessary to specify "start" and "end" points, distance between 
two neighbour nodes in OX and OY directions (stepX and stepY respectively). On the picture cell border
shown with dashed lines, nodes with small circles.
Gridding generates a Z value at each grid node by interpolating or approximating the \ref data values. 

\sa
\li \ref d_grid
*/
extern SURFIT_EXPORT d_grid * surfit_grid;	

//! current \ref d_grid using for gridding calculations
extern SURFIT_EXPORT d_grid * method_grid;

//! previous \ref d_grid used for gridding calculations
extern SURFIT_EXPORT d_grid * method_prev_grid;

//! the solution vector
extern SURFIT_EXPORT extvec * method_X;

//! this vector have true values for the cells that already solved
extern SURFIT_EXPORT bitvec * method_mask_solved;

//! this vector have true values for the cells that are marked as undefined
extern SURFIT_EXPORT bitvec * method_mask_undefined;

//! grid size in OX direction for the current phase
extern SURFIT_EXPORT size_t method_basis_cntX;

//! grid size in OY direction for the current phase
extern SURFIT_EXPORT size_t method_basis_cntY;

//! number of the current phase
extern SURFIT_EXPORT size_t method_phase_counter;

//! number of cells in each direction for initial (small) grid
extern SURFIT_EXPORT size_t basis_cnt;

//! constructs grid to the latest calculation phase
SURFIT_EXPORT
d_grid * create_last_grd();

//! converts cell number from one grid to another
SURFIT_EXPORT
size_t one2one(size_t pos, const d_grid * from, const d_grid * to);

//! converts pair (i,j) from one grid to another
SURFIT_EXPORT
void two2two(size_t & n, size_t & m, const d_grid * from, const d_grid * to);

//! converts cell number into pair (i,j)
SURFIT_EXPORT
bool one2two(size_t pos, size_t & i, size_t & j, size_t NN, size_t MM);

//! converts pair (i,j) into one number
inline
size_t two2one(size_t i, size_t j, size_t NN, size_t MM)
{
	if ((i >= 0) && (i < NN) && (j >= 0) && (j < MM)) {
		return i + j*NN;
	}

	if ((i < -1) || (i > NN+1) || (j < -1) || (j > MM+1)) {
		return UINT_MAX;
	}
	
	assert(0);
	return UINT_MAX;
};

//! converts triple (i,j,k) into one number
inline
size_t three2one(size_t i, size_t j, size_t k, size_t NN, size_t MM, size_t KK)
{
	size_t pos = UINT_MAX;
	if ((i >= 0) && (i < NN) && (j >= 0) && (j < MM) && (k >= 0) && (k < KK))
	{
		pos = i + j*NN + k*NN*MM;
		return pos;
	}

	assert(0);
	return pos;
};

//! returns true if cell with pos-number is inside grid with NNxMM cells
SURFIT_EXPORT
bool grid_bound(size_t pos, size_t NN, size_t MM);

//! returns true if cell with pair (n,m) is inside grid with NNxMM cells
SURFIT_EXPORT
bool grid_bound2(size_t n, size_t m, size_t NN, size_t MM);

//! initializes some global variables
//SURFIT_EXPORT 
//void grid_init();

//! like grid_init
SURFIT_EXPORT 
void grid_prepare();

//! calculates grid for the first calculation phase
SURFIT_EXPORT 
void grid_begin();

//! performs some operations after the latest phase
SURFIT_EXPORT 
void grid_finish(bool & method_ok);

//! releases some global variables
SURFIT_EXPORT 
void grid_release();

//! debug drawing function
void draw_grid_matlab(FILE * ff, const d_grid * grd, const char * color = "cyan");

}; // namespace surfit;

#endif

