
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

#ifndef __surfit_grid_user_included__
#define __surfit_grid_user_included__

#include "user.h"

namespace surfit {

class grid;
class vec;
class bitvec;

/*! \ingroup surfit_data_variables
    \var surfit_grid
    \brief equidistant \ref grid, used for \ref surfit_func calculation.

    This class describes equidistant rectangular grid (rectangular region comprised of evenly 
spaced rows and columns), presented with cells (intersection of a rows and columns). Each 
cell have center point, which
is grid node. To set the grid it is necessary to specify "start" and "end" points, distance between 
two neighbour nodes in OX and OY directions (stepX and stepY respectively). On the picture cell border
shown with dashed lines, nodes with small circles.
Gridding generates a Z value at each grid node by interpolating or approximating the \ref data values. 

\image html grid.jpg

\sa
\li \ref grid
\li \ref tcl_grid "Tcl commands"

*/
extern SURFIT_EXPORT grid * surfit_grid;	

extern SURFIT_EXPORT grid * method_grid;
extern SURFIT_EXPORT grid * method_sub_grid;
extern SURFIT_EXPORT grid * method_prev_grid;
extern SURFIT_EXPORT vec * method_X;
extern SURFIT_EXPORT bitvec * method_mask_solved;
extern SURFIT_EXPORT bitvec * method_mask_undefined;
extern SURFIT_EXPORT int method_basis_cntX;
extern SURFIT_EXPORT int method_basis_cntY;
extern SURFIT_EXPORT int method_phase_counter;
extern SURFIT_EXPORT REAL method_scaleX;
extern SURFIT_EXPORT REAL method_shiftX;
extern SURFIT_EXPORT REAL method_scaleY;
extern SURFIT_EXPORT REAL method_shiftY;
extern SURFIT_EXPORT REAL method_stepX;
extern SURFIT_EXPORT REAL method_stepY;
extern SURFIT_EXPORT bool doubleX;
extern SURFIT_EXPORT bool doubleY;

SURFIT_EXPORT
grid * create_last_grd();

SURFIT_EXPORT
int one2one(int pos, grid * from, grid * to);
SURFIT_EXPORT
void two2two(int & n, int & m, grid * from, grid * to);
SURFIT_EXPORT
void one2two(int pos, int & i, int & j, int NN, int MM);
SURFIT_EXPORT
void two2one(int & pos, int i, int j, int NN, int MM);
SURFIT_EXPORT
bool grid_bound(int pos, int NN, int MM);
SURFIT_EXPORT
bool grid_bound2(int n, int m, int NN, int MM);


/*! \class grid_user
    \brief implemets "Phases" for multigrid technique
*/
class SURFIT_EXPORT grid_user : public user {
public:

	//! constructor
	grid_user();

	//! destructor
	~grid_user();

	int max_priority();
	void init();
	void prepare();
	void begin();
	void stage1(int priority);
	void stage2(int priority);
	void stage3(int priority);
	void stage4(int priority);
	void stage5(int priority);
	void finish();
	void release();

};

}; // namespace surfit;

#endif

