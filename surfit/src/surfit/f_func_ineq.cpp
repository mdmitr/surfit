
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
#include "f_func_ineq.h"
#include "vec.h"
#include "bitvec.h"
#include "matr_diag.h"
#include "func.h"
#include "grid.h"
#include "grid_internal.h"

#include "grid_user.h"

#include <float.h>
#include <algorithm>

namespace surfit {

f_func_ineq::f_func_ineq(const d_func * ifnc, bool ileq, REAL imult) :
functional("f_func_ineq")
{
	leq = ileq;
	fnc = ifnc;
	if (fnc->getName()) {
		setNameF("f_func_ineq %s", fnc->getName());
	}
	mult = imult;
};

f_func_ineq::~f_func_ineq() {};

int f_func_ineq::this_get_data_count() const {
	return 1;
};

const data * f_func_ineq::this_get_data(int pos) const {
	if (pos == 0)
		return fnc;
	return false;
};

bool f_func_ineq::minimize() {

	return false;

};

bool f_func_ineq::make_matrix_and_vector(matr *& matrix, vec *& v) {

	int matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_vec(matrix_size);

	if (fnc->getName()) {
		writelog(LOG_MESSAGE,"func inequality: (%s), %d x %d", fnc->getName(), fnc->getCountX(), fnc->getCountY());
	} else {
		writelog(LOG_MESSAGE,"func inequality : noname dataset, %d x %d", fnc->getCountX(), fnc->getCountY());
	}

	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();

	vec * diag = create_vec(matrix_size);

	int from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, fnc->grd,
		        from_x, to_x,
		        from_y, to_y);
	
	int points = 0;

	int fnc_sizeX = fnc->getCountX()-1;
	int fnc_sizeY = fnc->getCountY()-1;
	
	REAL value;
	REAL stepX2 = method_grid->stepX/REAL(2);
	REAL stepY2 = method_grid->stepY/REAL(2);

	int i,j,pos;
	
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

			//value = fnc->getMeanValue(x-stepX2, x+stepX2, y-stepY2, y+stepY2);
			value = fnc->getInterpValue(x, y);

			if (value == fnc->undef_value)
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

void f_func_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	int from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, fnc->grd,
		        from_x, to_x,
		        from_y, to_y);
	
	int i,j,pos;
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

			//value = fnc->getMeanValue(x-stepX2, x+stepX2, y-stepY2, y+stepY2);
			value = fnc->getInterpValue(x, y);

			if (value == fnc->undef_value)
				continue;

			mask_solved->set_true(pos);
		
			
		}

	}
	
};

bool f_func_ineq::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const vec * X) 
{

	int from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, fnc->grd,
		        from_x, to_x,
		        from_y, to_y);
	
	int i,j,pos;
	
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

