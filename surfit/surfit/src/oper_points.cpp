
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

#include "ie.h"

#include "oper_points.h"
#include "points.h"
#include "wtask.h"
#include "vec.h"
#include "intvec.h"
#include "bitvec.h"

#include <algorithm>

namespace surfit {

oper_points::oper_points(vec * iweights, intvec * iweights_cnt, 
			 bitvec * imask_solved,
			 bitvec * imask_undefined,
			 int iN) 
{
	N = iN; 
	weights = iweights;
	weights_cnt = iweights_cnt;
	mask_solved = imask_solved;
	mask_undefined = imask_undefined;
};
	
oper_points::~oper_points() {};

REAL oper_points::norm() const {
	return *std::max_element(weights->begin(), weights->end());
};

long oper_points::rows() const {
	return N;
};

long oper_points::cols() const {
	return N;
};

REAL oper_points::operator () (int i, int j, int * next_j) const 
{
	int _next_j = INT_MAX;
	REAL res = REAL(0);

	if (i < j) {
		_next_j = INT_MAX;
		goto exit;
	}

	if (i > j) {
		_next_j = i;
		goto exit;
	}

	if (i == j) {
		if ((*weights_cnt)(j) > 0)
			res = (*weights)(j)/REAL((*weights_cnt)(j));
		_next_j = INT_MAX;
		goto exit;
	}

exit:

	if (next_j) {
		*next_j = _next_j;
	}

	return res;	
};

REAL oper_points::at(int i, int j, int * next_j) const 
{
	return operator()(i,j,next_j);
};

REAL oper_points::mult_line(int J, const REAL * b_begin, const REAL * b_end) const 
{
	if (mask_solved->get(J))
		return REAL(0);

	if (mask_undefined->get(J))
		return REAL(0);

	if ((*weights_cnt)(J) == 0)
		return REAL(0);

	REAL weight = (*weights)(J)/REAL((*weights_cnt)(J));

	if (weight <= REAL(0))
		return REAL(0);

	return weight * *(b_begin+J);
};

REAL oper_points::mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const 
{
	return mult_line(J, b_begin, b_end);
};

}; // namespace surfit;

