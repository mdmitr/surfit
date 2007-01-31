
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
#include "f_surf_ineq.h"
#include "vec.h"
#include "bitvec.h"
#include "matr_diag.h"
#include "surf.h"
#include "grid.h"
#include "grid_internal.h"

#include "grid_user.h"

#include <float.h>
#include <algorithm>

namespace surfit {

f_surf_ineq::f_surf_ineq(const d_surf * isrf, bool ileq, REAL imult) :
functional("f_surf_ineq", F_CONDI)
{
	leq = ileq;
	srf = isrf;
	if (srf->getName()) {
		setNameF("f_surf_ineq %s", srf->getName());
	}
	mult = imult;
};

f_surf_ineq::~f_surf_ineq() {};

int f_surf_ineq::this_get_data_count() const {
	return 1;
};

const data * f_surf_ineq::this_get_data(int pos) const {
	if (pos == 0)
		return srf;
	return false;
};

bool f_surf_ineq::minimize() {

	return false;

};

bool f_surf_ineq::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	if (srf->getName()) {
		writelog(LOG_MESSAGE,"surf inequality: (%s), %d x %d", srf->getName(), srf->getCountX(), srf->getCountY());
	} else {
		writelog(LOG_MESSAGE,"surf inequality : noname dataset, %d x %d", srf->getCountX(), srf->getCountY());
	}

	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();

	extvec * diag = create_extvec(matrix_size);

	size_t from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, srf->grd,
		        from_x, to_x,
		        from_y, to_y);
	
	size_t points = 0;

	size_t srf_sizeX = srf->getCountX()-1;
	size_t srf_sizeY = srf->getCountY()-1;
	
	REAL value;
	REAL stepX2 = method_grid->stepX/REAL(2);
	REAL stepY2 = method_grid->stepY/REAL(2);

	size_t i,j,pos;
	
	for (j = from_y; j <= to_y; j++) {

		for (i = from_x; i <= to_x; i++) {

			pos = i + j * method_grid->getCountX();
			
			// check for existance
			if (method_mask_solved->get(pos))
				continue;
			if (method_mask_undefined->get(pos))
				continue;
			
			REAL x, y;
			method_grid->getCoordNode(i, j, x, y);

			//value = srf->getMeanValue(x-stepX2, x+stepX2, y-stepY2, y+stepY2);
			value = srf->getInterpValue(x, y);

			if (value == srf->undef_value)
				continue;

			REAL x_value = (*method_X)(pos);
			REAL dist = fabs(value - x_value);
			if (leq) {
				if (x_value > value) {
					mask->set_true(pos);
					(*v)(pos) = value*mult*(dist + 1);
					(*diag)(pos) = mult*(dist + 1);
					points++;
				}
			} else {
				if (x_value < value) {
					mask->set_true(pos);
					(*v)(pos) = value*mult*(dist + 1);
					(*diag)(pos) = mult*(dist + 1);
					points++;
				}
			}	
			
		}

	}
		
		
	matr_diag * T = new matr_diag(diag, matrix_size, mask);
	matrix = T;

	if (points == 0) {
		delete T;
		T = NULL;
		matrix = NULL;
		if (v)
			v->release();
		v = NULL;
	}

	bool solvable = true;

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;
};

void f_surf_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	size_t from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, srf->grd,
		        from_x, to_x,
		        from_y, to_y);
	
	size_t i,j,pos;
	REAL value;
	
	for (j = from_y; j <= to_y; j++) {

		for (i = from_x; i <= to_x; i++) {

			pos = i + j * method_grid->getCountX();

			if (mask_solved->get(pos))
				continue;

			if (mask_undefined->get(pos))
				continue;
			
			REAL x, y;
			method_grid->getCoordNode(i, j, x, y);

			//value = srf->getMeanValue(x-stepX2, x+stepX2, y-stepY2, y+stepY2);
			value = srf->getInterpValue(x, y);

			if (value == srf->undef_value)
				continue;

			mask_solved->set_true(pos);
		
			
		}

	}
	
};

bool f_surf_ineq::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const extvec * X) 
{

	size_t from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, srf->grd,
		        from_x, to_x,
		        from_y, to_y);
	
	size_t i,j,pos;
	
	for (j = from_y; j <= to_y; j++) {

		for (i = from_x; i <= to_x; i++) {

			pos = i + j * method_grid->getCountX();
			
			// check for existance
			if (method_mask_solved->get(pos))
				continue;
			if (method_mask_undefined->get(pos))
				continue;
			
			return false;
			
		}

	}
		
	return true;

};


}; // namespace surfit;

