
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

#include "f_area_surf_ineq.h"
#include "bitvec.h"
#include "vec.h"
#include "matr_diag.h"
#include "area.h"
#include "grid_line.h"
#include "grid.h"
#include "surf.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

f_area_surf_ineq::f_area_surf_ineq(const d_surf * ifnc, const d_area * iarea, bool ileq, REAL imult, bool iinside) :
functional("f_area_surf_ineq", F_CONDI)
{
	leq = ileq;
	mult = imult;
	area = iarea;
	fnc = ifnc;
	inside = iinside;
	area_mask = NULL;
};

f_area_surf_ineq::~f_area_surf_ineq() {
	cleanup();
};

void f_area_surf_ineq::cleanup() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
};

int f_area_surf_ineq::this_get_data_count() const {
	return 2;
};

const data * f_area_surf_ineq::this_get_data(int pos) const {
	if (pos == 0)
		return area;
	if (pos == 1)
		return fnc;
	return NULL;
};

bool f_area_surf_ineq::minimize() {

	return false;

};

bool f_area_surf_ineq::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	size_t points = 0;

	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	if (leq) 
		writelog(LOG_MESSAGE,"inequality for area (%s) leq surface", area->getName());
	else 
		writelog(LOG_MESSAGE,"inequality for area (%s) geq surface", area->getName());
	

	get_area_mask();
	if (area_mask == NULL)
		return false;
		
	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();

	extvec * diag = create_extvec(matrix_size);

	REAL x, y, value;

	size_t i;
	for (i = 0; i < matrix_size; i++) {

		if (area_mask->get(i) == false)
			continue;
		
		if (method_mask_solved->get(i))
			continue;
		if (method_mask_undefined->get(i))
			continue;

		size_t I, J;
		one2two(i, I, J, method_grid->getCountX(), method_grid->getCountY());
		method_grid->getCoordNode(I, J, x, y);

		//value = fnc->getMeanValue(x-stepX2, x+stepX2, y-stepY2, y+stepY2);
		value = fnc->getInterpValue(x, y);

		if (value == fnc->undef_value)
			continue;
		
		REAL x_value = (*method_X)(i);
		REAL dist = fabs(value - x_value);

		if (leq) {
			if (x_value > value) {
				mask->set_true(i);
				(*v)(i) = value*mult*(dist + 1);
				(*diag)(i) = mult*(dist + 1);
				points++;
			}
		} else {
			if (x_value < value) {
				mask->set_true(i);
				(*v)(i) = value*mult*(dist + 1);
				(*diag)(i) = mult*(dist + 1);
				points++;
			}
		}
		
	}
	
	bool solvable = true;

	if (points == 0) {
		if (v)
			v->release();
		if (diag)
			diag->release();
	} else {
		matr_diag * T = new matr_diag(diag, matrix_size, mask);
		mask = NULL;
		matrix = T;
	}

	solvable = wrap_sums(matrix, v) || solvable;
	return solvable;
};

void f_area_surf_ineq::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {

	get_area_mask();
	if (area_mask == NULL)
		return;
	
	size_t i;
	for (i = 0; i < area_mask->size(); i++) {

		if (area_mask->get(i) == false)
			continue;
		
		if (mask_solved->get(i))
			continue;
		if (mask_undefined->get(i))
			continue;

		mask_solved->set_true(i);
		
	}

};

bool f_area_surf_ineq::solvable_without_cond(const bitvec * mask_solved,
					const bitvec * mask_undefined,
					const extvec * X)
{

	get_area_mask();
	if (area_mask == NULL)
		return false;
	
	size_t i;
		
	for (i = 0; i < (size_t)area_mask->size(); i++) {

		if (area_mask->get(i) == false)
			continue;
		
		if ( (mask_solved->get(i) == false) && 
		     (mask_undefined->get(i) == false) ) 
		{
			return false;
		}
	}

	return true;

};

void f_area_surf_ineq::get_area_mask() {

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

void f_area_surf_ineq::drop_private_data() {
	if (area_mask)
		area_mask->release();
	area_mask = NULL;
};



}; // namespace surfit;

