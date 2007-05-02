
/*------------------------------------------------------------------------------
 *	$Id: f_curv.cpp 1045 2007-04-19 15:12:09Z mishadm $
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
#include "f_fault.h"
#include "curv.h"

namespace surfit {

f_fault::f_fault(const d_curv * icrv) :
functional("f_fault", F_MODIFIER)
{
	crv = icrv;
	if (crv->getName()) {
		setNameF("f_curv %s", crv->getName());
	}
};

f_fault::~f_fault()
{
};

int f_fault::this_get_data_count() const {
	return 1;
};

const data * f_fault::this_get_data(int pos) const {
	if (pos == 0)
		return crv;
	return NULL;
};

void f_fault::cleanup()
{
};

bool f_fault::minimize()
{
	return false;
};

bool f_fault::make_matrix_and_vector(matr *& matrix, extvec *& v)
{
	return false;
};

bool f_fault::solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X)
{
	return false;
};

void f_fault::mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond)
{
	return;
};

const d_curv * f_fault::get_fault() const
{
	return crv;
};

}; // namespace surfit

