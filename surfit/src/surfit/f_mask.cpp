
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

#include "f_mask.h"
#include "mask.h"
#include "grid.h"
#include "bitvec.h"
#include "variables_tcl.h"
#include "vec.h"
#include "matr_eye.h"

#include "grid_user.h"

namespace surfit {

f_mask::f_mask(const d_mask * idef, REAL ivalue) :
functional("f_mask", F_USUAL)
{
	msk = idef;
	value = ivalue;
	if (msk->getName())
		setNameF("f_mask %s", msk->getName());
	mask = NULL;
};

f_mask::~f_mask() {
	cleanup();
};

void f_mask::cleanup() {
	if (mask)
		mask->release();
	mask = NULL;
};

int f_mask::this_get_data_count() const {
	return 1;
};

const data * f_mask::this_get_data(int pos) const {
	if (pos == 0)
		return msk;
	return NULL;
};

bool f_mask::minimize() {

	writelog(LOG_MESSAGE,"mask : (%s), size=(%d x %d)", msk->getName(), msk->getCountX(), msk->getCountY());

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();

	size_t i, j;
	REAL x,y;
	bool mask_value;
	int N;

	size_t geom_NN = method_grid->getCountX();
	size_t geom_MM = method_grid->getCountY();

	for (j = 0; j < geom_MM; j++) {
		y = method_grid->getCoordNodeY(j);
		
		for (i = 0; i < geom_NN; i++) {
			
			N = i + j*method_grid->getCountX();
			
			// check for existance
			if (method_mask_solved->get(N))
				continue;
			if (method_mask_undefined->get(N))
				continue;
			
			x = method_grid->getCoordNodeX(i);
			mask_value = msk->getValue(x,y);
			if (value == undef_value) {
				if (mask_value) {
					method_mask_undefined->set_true(i + j*NN);
				}
			} else {
				if (mask_value) {
					method_mask_solved->set_true(i + j*NN);
					(*method_X)(i + j*NN) = value;
				}
			}
			
		}

	}

	return true;
};

bool f_mask::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	matrix = NULL;
	v = NULL;

	if (value == undef_value) {
		writelog(LOG_WARNING,"mask with \"undef_val\" can't be minimized conditionally or as a summator");
		return false;
	}
	
	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	
	if (mask)
		mask->release();
	mask = create_bitvec( NN*MM );
	mask->init_false();

	v = create_extvec( NN*MM );
	
	size_t i,j, pos;
	size_t points = 0;
	REAL x,y;

	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			pos = i + j*NN;

			if (method_mask_solved->get(pos))
				continue;

			if (method_mask_undefined->get(pos))
				continue;

			method_grid->getCoordNode(i, j, x, y);
			bool res = msk->getValue(x, y);
			if (res) {
				mask->set_true(pos);
				(*v)(pos) = value;
				points++;
			}
			
		}
	}

	if (points > 0) {
		matr_eye * T = new matr_eye(1, NN*MM, mask, method_mask_solved, method_mask_undefined);
		matrix = T;
		mask = NULL;
	} else {
		if (v)
			v->release();
		v = NULL;
	}

	return true;
};

void f_mask::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) 
{
	mark_sums(mask_solved, mask_undefined);
};

bool f_mask::solvable_without_cond(const bitvec * mask_solved,
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	return true;
};

}; // namespace surfit;

