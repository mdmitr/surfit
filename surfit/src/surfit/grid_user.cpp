
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

#include "surfit_ie.h"

#include "fileio.h"

#include "grid.h"
#include "bitvec.h"
#include "vec.h"
#include "surf.h"
#include "surf_tcl.h"
#include "variables_tcl.h"
#include "grid_tcl.h"
#include "variables.h"

#include "grid_user.h"

namespace surfit {

////////////////////////////////////////////////
//
//  G R I D   G L O B A L   V A R I A B L E S
//
////////////////////////////////////////////////

d_grid         *  surfit_grid         = NULL;

/*! \struct grid_garbage
    \brief struct for deletion of \ref grid pointers
*/
struct grid_garbage : public binman {
	//! inits \ref surfit_grid
	grid_garbage() {
		surfit_grid = NULL;
	};
	//! removes \ref surfit_grid
	~grid_garbage() {
		if (surfit_grid)
			surfit_grid->release();
	};
};

grid_garbage gird_garb;

d_grid * method_grid;
d_grid * method_sub_grid;
d_grid * method_prev_grid;
vec * method_X;
bool method_ok;
bitvec * method_mask_solved;
bitvec * method_mask_undefined;
int basis_cnt = 8;
int method_basis_cntX;
int method_basis_cntY;
int method_phase_counter;
REAL method_scaleX;
REAL method_shiftX;
REAL method_scaleY;
REAL method_shiftY;
REAL method_stepX;
REAL method_stepY;
bool doubleX;
bool doubleY;

/////////////////////////////////////////////////
//
//   G R I D   U S E F U L   F U N C T I O N S
//
/////////////////////////////////////////////////

int one2one(int pos, d_grid * from, d_grid * to) {
	int n, m;
	one2two(pos, n, m, from->getCountX(), from->getCountY());
	REAL x, y;
	from->getCoordNode(n, m, x, y);
	n = to->get_i(x);
	m = to->get_j(y);
	two2one(pos, n, m, to->getCountX(), to->getCountY());
	to->getCoordNode(n,m, x, y);
	return pos;
};

void two2two(int & n, int & m, d_grid * from, d_grid * to) {
	REAL x, y;
	from->getCoordNode(n, m, x, y);
	n = to->get_i(x);
	m = to->get_j(y);
};

void one2two(int pos, int & i, int & j, int NN, int MM) {
	if (pos >= 0 && pos < NN*MM) {
		i = pos % NN;
		j = (pos - i)/NN;
		return;
	}

	pos = -pos;
	NN += 2;
	MM += 2;
	i = pos % NN;
	j = (pos - i)/NN;
	i -= 1;
	j -= 1;

};

void two2one(int & pos, int i, int j, int NN, int MM) {
	
	if ((i >= 0) && (i < NN) && (j >= 0) && (j < MM)) {
		pos = i + j*NN;
		return;
	}

	if ((i < -1) || (i > NN+1) || (j < -1) || (j > MM+1)) {
		pos = INT_MAX;
		return;
	}
	
	NN += 2;
	MM += 2;
	i += 1;
	j += 1;
	pos = i + j*NN;
	pos = -pos;
		
};

bool grid_bound(int pos, int NN, int MM) {
	int n, m;
	one2two(pos, n, m, NN, MM);
	return ( (n >= 0) && (n < NN) && (m >= 0) && (m < MM) );
};

bool grid_bound2(int n, int m, int NN, int MM) {
	return ( (n >= 0) && (n < NN) && (m >= 0) && (m < MM) );
};

void project_vector(vec * A, int NN, int MM,
		    bool doubleX, bool doubleY) {

	if (!doubleX && !doubleY)
		return;

	if (doubleY) {
		int size = A->size();
		A->resize(size*2);
		vec::iterator A_it = A->begin() + size - 1;
		vec::iterator new_A_it = A->begin() + size*2 - 1;
		vec::iterator temp_it;
		vec::iterator A_beg = A->begin();
		while ( new_A_it != A->begin() - 1 ) {
			int i;
			temp_it = A_it;
			for ( i = 0; i < NN; i++) {
				*new_A_it = *A_it;
				new_A_it--;
				A_it--;
			}
			A_it = temp_it;
			for ( i = 0; i < NN; i++) {
				*new_A_it = *A_it;
				new_A_it--;
				A_it--;
			}
		}
	}

	if (doubleX) {
		NN *= 2;
		int size = A->size();
		A->resize(size*2);
		vec::iterator A_it = A->begin() + size - 1;
		vec::iterator new_A_it = A->begin() + size*2 - 1;
		vec::iterator A_beg = A->begin();
		while ( new_A_it != A->begin() - 1 ) {
			*new_A_it = *A_it;
			new_A_it--;
			*new_A_it = *A_it;
			new_A_it--;
			A_it--;
		}
		
	}
	 	
};

d_grid * create_calc_grd(int basis_cntX, int basis_cntY) {

	REAL grid_lengthX = surfit_grid->endX+surfit_grid->stepX - surfit_grid->startX;
	int grid_nodesX = surfit_grid->getCountX();
	REAL grid_lengthY = surfit_grid->endY+surfit_grid->stepY - surfit_grid->startY;
	int grid_nodesY = surfit_grid->getCountY();

	REAL grd_startX = surfit_grid->startX-surfit_grid->stepX/REAL(2);
	REAL grd_endX = surfit_grid->endX+surfit_grid->stepX/REAL(2);
	REAL grd_startY = surfit_grid->startY-surfit_grid->stepY/REAL(2);
	REAL grd_endY = surfit_grid->endY+surfit_grid->stepY/REAL(2);
	REAL grd_stepX = (grd_endX-grd_startX)/REAL(basis_cntX);
	REAL grd_stepY = (grd_endY-grd_startY)/REAL(basis_cntY);

	d_grid * grd = create_grid(grd_startX+grd_stepX/REAL(2), 
			           grd_endX-grd_stepX/REAL(2), 
			           grd_stepX, 
			           grd_startY+grd_stepY/REAL(2), 
			           grd_endY-grd_stepY/REAL(2), 
			           grd_stepY, 
			           NULL);
	return grd;

};

d_grid * create_last_grd() {

	REAL grid_lengthX = surfit_grid->endX+surfit_grid->stepX - surfit_grid->startX;
	int grid_nodesX = surfit_grid->getCountX();
	REAL grid_lengthY = surfit_grid->endY+surfit_grid->stepY - surfit_grid->startY;
	int grid_nodesY = surfit_grid->getCountY();

	double log2 = log(double(2));
	int last_basis_cntX = (int)ceil(log((REAL)grid_nodesX)/log2);
	int last_basis_cntY = (int)ceil(log((REAL)grid_nodesY)/log2);
	last_basis_cntX = (int)pow(2, last_basis_cntX);
	last_basis_cntY = (int)pow(2, last_basis_cntY);

	REAL grd_startX = surfit_grid->startX-surfit_grid->stepX/REAL(2);
	REAL grd_endX = surfit_grid->endX+surfit_grid->stepX/REAL(2);
	REAL grd_startY = surfit_grid->startY-surfit_grid->stepY/REAL(2);
	REAL grd_endY = surfit_grid->endY+surfit_grid->stepY/REAL(2);

	REAL grd_stepX = (grd_endX-grd_startX)/REAL(last_basis_cntX);
	REAL grd_stepY = (grd_endY-grd_startY)/REAL(last_basis_cntY);

	d_grid * last_grd = create_grid(grd_startX+grd_stepX/REAL(2), 
		                        grd_endX-grd_stepX/REAL(2), 
				        grd_stepX, 
				        grd_startY+grd_stepY/REAL(2), 
				        grd_endY-grd_stepY/REAL(2), 
				        grd_stepY, 
				        NULL);

	return last_grd;
};

////////////////////////////////
//
// functions for grid sequence
//
////////////////////////////////
void grid_init() {
	method_grid = NULL;
	method_sub_grid = NULL;
	method_prev_grid = NULL;
	method_X = NULL;
	method_mask_solved = NULL;
	method_mask_undefined = NULL;
	doubleX = false;
	doubleY = false;
};

void grid_prepare()
{
	method_basis_cntX = basis_cnt;
	method_basis_cntY = basis_cnt;
	method_phase_counter = 0;
	method_scaleX = 1;
	method_shiftX = 0;
	method_scaleY = 1;
	method_shiftY = 0;
	method_stepX = 0;
	method_stepY = 0;
	method_ok = false;

	if (surfit_grid == NULL) {
		grid();
	}

	if (surfit_grid == NULL) {
		return;
	}

	REAL startx, starty, endx, endy;
	surfit_grid->getCoordNode(0,0,startx,starty);
	startx -= surfit_grid->stepX/REAL(2);
	starty -= surfit_grid->stepY/REAL(2);
	surfit_grid->getCoordNode(surfit_grid->getCountX()-1,
		                  surfit_grid->getCountY()-1,
				  endx,endy);
	endx += surfit_grid->stepX/REAL(2);
	endy += surfit_grid->stepY/REAL(2);
	
	method_sub_grid = create_grid((startx+endx)/REAL(2), (startx+endx)/REAL(2), (endx-startx),
				      (starty+endy)/REAL(2), (starty+endy)/REAL(2), (endy-starty));
};

void grid_begin() {
	
	method_phase_counter++;

	writelog(LOG_MESSAGE,"");
	writelog(LOG_MESSAGE,"*************");
	if (map_name)
		writelog(LOG_MESSAGE,"* Phase %d, grid size = %d x %d (%s)",
		         method_phase_counter, method_basis_cntX, method_basis_cntY, map_name);
	else
		writelog(LOG_MESSAGE,"* Phase %d, grid size = %d x %d",
		         method_phase_counter, method_basis_cntX, method_basis_cntY);
	
	writelog(LOG_MESSAGE,"*************");

	// Создаем геометрию, с которой будем считать
	if (method_grid)
		method_grid->release();
	method_grid = create_calc_grd(method_basis_cntX, method_basis_cntY);
	
	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();
	int matrix_size = NN*MM;
	
	if (!method_X) 
		method_X = create_vec(matrix_size);

	if (method_mask_solved)
		method_mask_solved->release();
	method_mask_solved = create_bitvec(matrix_size);
	method_mask_solved->init_false();
	if (method_mask_undefined)
		method_mask_undefined->release();
	method_mask_undefined = create_bitvec(matrix_size);
	method_mask_undefined->init_false();

	method_scaleX = REAL(1)/method_grid->stepX;
	method_shiftX = method_grid->startX;
	method_scaleY = REAL(1)/method_grid->stepY;
	method_shiftY = method_grid->startY;
	method_stepX = method_grid->stepX;
	method_stepY = method_grid->stepY;
	REAL div = method_stepX/method_stepY;
	if (div > 1) {
		method_stepX = 1;
		method_stepY = REAL(1)/div;
	} else {
		method_stepX = div;
		method_stepY = 1;
	}

};

void grid_finish() {

	if (method_sub_grid)
		method_sub_grid->release();
	method_sub_grid = create_grid(method_grid);

	if (method_prev_grid)
		method_prev_grid->release();
	method_prev_grid = create_grid(method_grid);
	
	doubleX = false;
	doubleY = false;
	
	if (method_grid->getCountX() < surfit_grid->getCountX()) {
		method_basis_cntX *= 2;
		doubleX = true;
	}
	
	if (method_grid->getCountY() < surfit_grid->getCountY()) {
		method_basis_cntY *= 2;
		doubleY = true;
	}
	
	// updating sigma's coeff
	project_vector(method_X, 
		method_grid->getCountX(), method_grid->getCountY(),
		doubleX, doubleY);
	
	if (
		(method_grid->getCountX() >= surfit_grid->getCountX()) &&
		(method_grid->getCountY() >= surfit_grid->getCountY())
		)
		method_ok = true;

	if (method_ok) {
		int i;
		for (i = 0; i < method_mask_undefined->size(); i++) {
			if (method_mask_undefined->get(i))
				(*method_X)(i) = undef_value;
		}
		
	}

};

void grid_release() {

	int i;
	for (i = 0; i < method_X->size(); i++) {
		if (method_mask_solved->get(i) == false)
			(*method_X)(i) = undef_value;
	}

	if (method_mask_solved)
		method_mask_solved->release();
	method_mask_solved = NULL;
	if (method_mask_undefined)
		method_mask_undefined->release();
	method_mask_undefined = NULL;
	if (method_sub_grid)
		method_sub_grid->release();
	method_sub_grid = NULL;

	if (method_prev_grid)
		method_prev_grid->release();
	
	d_surf * res_surf = create_surf(method_X, create_grid(method_grid), map_name);
	if (method_grid)
		method_grid->release();
	method_grid = NULL;
	method_X = NULL;

	res_surf->undef_value = surfit::undef_value;
	res_surf->setName(map_name);
	
	surfit_surfs->push_back(res_surf);	
	//surf_project();

};

}; // namespace surfit;

