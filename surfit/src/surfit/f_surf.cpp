
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
#include "f_surf.h"
#include "surf.h"
#include "solvers.h"
#include "variables_tcl.h"
#include "matr.h"
#include "vec.h"
#include "bitvec.h"
#include "grid.h"
#include "matr_eye.h"
#include "grid_internal.h"

#include "grid_user.h"

namespace surfit {

f_surf::f_surf(const d_surf * isrf, REAL imult, const char * iname) :
functional("f_surf", F_USUAL)
{
	srf = isrf;
	if (iname == NULL) {
		if (srf->getName()) {
			setNameF( srf->getName());
		}
	} else
		setNameF("f_surf %s", iname);
	mask = NULL;
	name = NULL;
	if (iname)
		name = strdup(iname);
	need_complete = true;
	mult = imult;
};

f_surf::~f_surf() {
	cleanup();
};

void f_surf::cleanup() {
	if (mask)
		mask->release();
	mask = NULL;
	free(name);
};

int f_surf::this_get_data_count() const {
	return 1;
};

const data * f_surf::this_get_data(int pos) const {
	if (pos == 0)
		return srf;
	return false;
};

bool f_surf::minimize() 
{
	if ((functionals_add->size() == 0) && ( !cond() )) {
		return minimize_only_surf();
	} else {

		matr * A = NULL;
		extvec * b = NULL;
		bool solvable = make_matrix_and_vector(A,b, method_mask_solved, method_mask_undefined);
		if (solvable == false)
			return false;
		
		size_t matrix_size = method_basis_cntX*method_basis_cntY;
		
		if ( !cond() ) {
			if (solvable == false) {
				delete A;
				if (b)
					b->release();
				return false;
			}
			
			method_X->resize(b->size());
			solve(A,b,method_X);
			method_X->resize(matrix_size);
			
			delete A;
			if (b)
				b->release();
			
			return true;
		} else {
			return solve_with_penalties(this, A, b, method_X);
		}
		return false;
		
	}
	return false;
};

bool f_surf::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) {

	if (name == NULL)
		writelog(LOG_MESSAGE,"surf : (%s), size=(%d x %d)", srf->getName(), srf->getCountX(), srf->getCountY());
	else
		writelog(LOG_MESSAGE,"%s, size=(%d x %d)", name, srf->getCountX(), srf->getCountY());

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();

	v = create_extvec(NN*MM);
	
	if (mask)
		mask->release();
	mask = create_bitvec(NN*MM);
	mask->init_false();
	int points = 0;

	size_t from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, srf->grd,
		        from_x, to_x,
		        from_y, to_y);

	size_t i, j, pos;
	
	REAL value;
	REAL stepX2 = method_grid->stepX/REAL(2);
	REAL stepY2 = method_grid->stepY/REAL(2);

	for (j = from_y; j <= to_y; j++) {
		for (i = from_x; i <= to_x; i++) {
			
			pos = i + j * method_grid->getCountX();

			// check for existance
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

			(*v)(pos) = value*mult;
			mask->set_true(pos);
			points++;
			
		}
	}

	bitvec * mask_copy = create_bitvec(mask);
	matr_eye * T = new matr_eye(mult, NN*MM, mask, mask_solved, mask_undefined);
	mask = mask_copy;
	matrix = T;

	bool solvable = (points > 0);

	solvable = wrap_sums(matrix, v, mask_solved, mask_undefined) || solvable;

	return solvable;
};
	
void f_surf::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	if ((functionals_add->size() == 0) && ( !cond() ) && (i_am_cond == false))
		return;

	size_t i;
	if (mask) {
		for (i = 0; i < mask->size(); i++) {
			if (mask->get(i))
				mask_solved->set_true(i);
		}
	}

	mark_sums(mask_solved, mask_undefined);

	if (need_complete)
	{
		set_undefined(mask_solved, mask_undefined);
	}
};

bool f_surf::minimize_only_surf() 
{
	if (name == NULL)
		writelog(LOG_MESSAGE,"surf : (%s), size=(%d x %d)", srf->getName(), srf->getCountX(), srf->getCountY());
	else
		writelog(LOG_MESSAGE,"%s, size=(%d x %d)", name, srf->getCountX(), srf->getCountY());

	size_t from_x, from_y, to_x, to_y;
	_grid_intersect1(method_grid, srf->grd,
		        from_x, to_x,
		        from_y, to_y);

	size_t i, j, pos;
	
	REAL value;
	REAL stepX2 = method_grid->stepX/REAL(2);
	REAL stepY2 = method_grid->stepY/REAL(2);

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

			(*method_X)(pos) = value;
			method_mask_solved->set_true(pos);
			
		}
	}

	if (need_complete) {
		set_undefined(method_mask_solved, method_mask_undefined);
	}
	
	return true;
};

bool f_surf::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	return true;
};

const d_surf * f_surf::get_surf() const
{
	return srf;
};

}; // namespace surfit;

