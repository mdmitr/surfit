
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
#include "oper.h"
#include "vec.h"

#include <float.h>
#include <limits.h>


namespace surfit {

void oper::mult(vec * b, vec * r) {
	int J;
	for (J = 0; J < rows(); J++) {
		(*r)(J) = mult_line(J, b->begin(), b->end());
	}
};

void oper::mult_transposed(vec * b, vec * r) {
	int J;
	for (J = 0; J < cols(); J++) {
		(*r)(J) = mult_transposed_line(J, b->begin(), b->end());
	}
};

oper_complex::~oper_complex() {
	delete T1;
	delete T2;
};

oper_complex::oper_complex(REAL iw1, oper *iT1, REAL iw2, oper *iT2) {
	w1 = iw1;
	T1 = iT1;
	w2 = iw2;
	T2 = iT2;
};

REAL oper_complex::operator()(int i, int j, int * next_j) const {

	REAL res = 0;
	int next_j1 = INT_MAX;
	int next_j2 = INT_MAX;
	if (T1 && w1)
		res += w1*(*T1)(i,j,&next_j1);
	if (T2 && w2)
		res += w2*(*T2)(i,j,&next_j2);
	
	if (next_j)
		*next_j = MIN(next_j1,next_j2);
	
	return res;
	
};

REAL oper_complex::at(int i, int j, int * next_j) const {

	REAL res = 0;
	int next_j1 = INT_MAX;
	int next_j2 = INT_MAX;
	if (T1 && w1)
		res += w1*T1->at(i,j,&next_j1);
	if (T2 && w2)
		res += w2*T2->at(i,j,&next_j2);
	
	if (next_j)
		*next_j = MIN(next_j1,next_j2);
	
	return res;
	
};

REAL oper_complex::mult_line(int J, const REAL * b_begin, const REAL * b_end) const {
	REAL res = 0;
	if (T1 && w1)
		res += w1*T1->mult_line(J, b_begin, b_end);
	if (T2 && w2)
		res += w2*T2->mult_line(J, b_begin, b_end);
	
	return res;
};

REAL oper_complex::mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const {
	REAL res = 0;
	if (T1 && w1)
		res += w1*T1->mult_transposed_line(J, b_begin, b_end);
	if (T2 && w2)
		res += w2*T2->mult_transposed_line(J, b_begin, b_end);
	
	return res;
};

REAL oper_complex::norm() const {
	REAL res = 0;
	if (T1 && w1)
		res += w1*T1->norm();
	if (T2 && w2)
		res += w2*T2->norm();
	
	return res;
};

long oper_complex::cols() const {
	if (T1)
		return T1->cols();
	if (T2)
		return T2->cols();
	return 0;
};

long oper_complex::rows() const {
	if (T1)
		return T1->rows();
	if (T2)
		return T2->rows();
	return 0;
};

}; // namespace surfit;

