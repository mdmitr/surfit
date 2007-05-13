
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
#include "matr_eye.h"
#include "bitvec.h"

#include <math.h>

namespace surfit {

matr_eye::matr_eye(REAL ival, size_t iN,
		   bitvec *& imask,
		   const bitvec * imask_solved,
		   const bitvec * imask_undefined) {
	val = ival;
	N = iN;
	mask = imask;
	imask = NULL;
	mask_solved = imask_solved;
	mask_undefined = imask_undefined;
};

matr_eye::~matr_eye() {
	if (mask)
		mask->release();
};

REAL matr_eye::norm() const {
	return fabs(val);
};

size_t matr_eye::rows() const {
	return N;
};

size_t matr_eye::cols() const {
	return N;
};

REAL matr_eye::element_at(size_t i, size_t j, size_t * next_j) const 
{
	size_t _next_j = UINT_MAX;
	REAL res = REAL(0);

	if (i < j) {
		_next_j = UINT_MAX;
		goto exit;
	}

	if (i > j) {
		_next_j = i;
		goto exit;
	}

	if (i == j) {
		if (mask->get(j) == true)
			res = val;
		_next_j = UINT_MAX;
		goto exit;
	}

exit:

	if (next_j) {
		*next_j = _next_j;
	}

	return res;	
};

REAL matr_eye::element_at_transposed(size_t i, size_t j, size_t * next_j) const 
{
	return element_at(i, j, next_j);	
};

REAL matr_eye::at(size_t i, size_t j, size_t * next_j) const 
{
	bool zero = mask_solved->get(i);
	if (!zero)
		zero = mask_undefined->get(i);
	if (!zero)
		zero = mask_solved->get(j);
	if (!zero)
		zero = mask_undefined->get(j);

	if (zero) {
		if ( next_j )
			*next_j = UINT_MAX;
		return REAL(0);
	}

	return element_at(i,j,next_j);
};

REAL matr_eye::at_transposed(size_t i, size_t j, size_t * next_j) const 
{
	return element_at(i,j,next_j);
};

REAL matr_eye::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) 
{
	if (mask_solved->get(J))
		return REAL(0);

	if (mask_undefined->get(J))
		return REAL(0);

	if (mask->get(J))
		return val * *(b_begin+J);

	return REAL(0);
};

REAL matr_eye::mult_transposed_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end)  
{
	return mult_line(J, b_begin, b_end);
};


}; // namespace surfit;


