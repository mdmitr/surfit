
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
#include "f_area_surf.h"
#include "area.h"
#include "grid.h"
#include "surf.h"
#include "vec.h"
#include "matr.h"
#include "matr_eye.h"
#include "solvers.h"
#include "variables_tcl.h"
#include "bitvec.h"
#include "grid_line.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_area_surf::f_area_surf(const d_surf * isurf, const d_area * iarea, bool iinside) :
functional("f_area_surf", F_USUAL)
{
	area = iarea;
	srf = isurf;
	if (area->getName()) {
		setNameF("f_area_surf %s", area->getName());
	}
	inside = iinside;
	area_mask = NULL;
};

f_area_surf::~f_area_surf() {
	cleanup();
};

void f_area_surf::cleanup() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
};

int f_area_surf::this_get_data_count() const {
	return 2;
};

const data * f_area_surf::this_get_data(int pos) const {
	if (pos == 0)
		return area;
	if (pos == 1)
		return srf;
	return NULL;
};

bool f_area_surf::minimize() {
	if (((functionals_add->size() == 0) && ( !cond() )) ) {
		return minimize_only_area_surf();
	} else {
		
		matr * A = NULL;
		extvec * b = NULL;
		bool solvable = make_matrix_and_vector(A,b);
		
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

bool f_area_surf::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	if (srf->getName())
		writelog(LOG_MESSAGE,"area_surf (%s+%s)", area->getName(), srf->getName());
	else
		writelog(LOG_MESSAGE,"area_surf (%s)", area->getName());

	get_area_mask();
	if (area_mask == NULL)
		return false;
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	size_t i, I, J;
	size_t points = 0;
	REAL x,y,z;
	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();

	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();

	for (i = 0; i < matrix_size; i++) {

		if (area_mask->get(i) == false) 
			continue;
				
		if ( (method_mask_solved->get(i)) ) {
			mask->set_true(i);
			continue;
		}

		if ( (method_mask_undefined->get(i)) ) {
			mask->set_true(i);
			continue;
		}

		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, x, y);

		z = srf->getInterpValue(x,y);
		if (z == srf->undef_value)
			continue;
		
		(*v)(i) = z;
		points++;
		mask->set_true(i);
	
	}

	matr_eye * T = new matr_eye(1, matrix_size, mask, method_mask_solved, method_mask_undefined);
	matrix = T;

	bool solvable = (points > 0);

	solvable = wrap_sums(matrix, v) || solvable;
	
	return solvable;
};

void f_area_surf::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	if ((functionals_add->size() == 0) && ( !cond() ) && (i_am_cond == false) )
		return;	

	size_t matrix_size = method_basis_cntX * method_basis_cntY;

	get_area_mask();
	if (area_mask == NULL) {
		mark_sums(mask_solved, mask_undefined);
		return;
	}
	
	size_t i;
	
	for (i = 0; i < (size_t)matrix_size; i++) {
		if (area_mask->get(i) == false)
			continue;
		if ( (mask_solved->get(i) == false) && (mask_undefined->get(i) == false) ) {
			mask_solved->set_true(i);
		}
	}

	mark_sums(mask_solved, mask_undefined);
};

bool f_area_surf::minimize_only_area_surf() {
	
	if (srf->getName())
		writelog(LOG_MESSAGE,"area_surf (%s+%s)", area->getName(), srf->getName());
	else
		writelog(LOG_MESSAGE,"area_surf (%s)", area->getName());

	get_area_mask();
	if (area_mask == NULL)
		return false;
	
	size_t i;
	size_t I, J;
	size_t NN, MM;
	REAL x, y, z;
	NN = method_grid->getCountX();
	MM = method_grid->getCountY();
	
	for (i = 0; i < (size_t)area_mask->size(); i++) {
		if (area_mask->get(i) == false)
			continue;
		if ( (method_mask_solved->get(i) == false) && (method_mask_undefined->get(i) == false) ) 
		{
			one2two(i, I, J, NN, MM);

			method_grid->getCoordNode(I, J, x, y);

			z = srf->getInterpValue(x,y);
			if (z == srf->undef_value)
				continue;

			method_mask_solved->set_true(i);
			(*method_X)(i) = z;
		}
	}
	
	return true;
};

bool f_area_surf::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	return true;
};

void f_area_surf::get_area_mask() {

	if (area_mask == NULL) {
		area_mask = nodes_in_area_mask(area, method_grid, method_mask_undefined);
		if (inside == false) 
			area_mask->invert();
	} else {
		if (area_mask->size() != method_grid->getCountX()*method_grid->getCountY()) {
			if (area_mask)
				area_mask->release();
			area_mask = nodes_in_area_mask(area, method_grid, method_mask_undefined);
			if (inside == false) 
				area_mask->invert();
		}
	}

};

void f_area_surf::drop_private_data() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
};


}; // namespace surfit;

