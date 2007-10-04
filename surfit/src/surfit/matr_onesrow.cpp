
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
#include "matr_onesrow.h"
#include "bitvec.h"
#include "vec.h"
#include "vec_alg.h"

#ifdef HAVE_THREADS
#include "ptypes/pasync.h"
USING_PTYPES
#endif

namespace surfit {

#ifdef HAVE_THREADS
mutex matr_onesrow_mutex;
#endif

matr_onesrow::matr_onesrow(REAL ival, size_t iN,
			   bitvec *& imask) 
{
	val = ival;
	N = iN;
	
	mask = imask;
	imask = NULL;

	prev_b_begin = NULL;
	prev_val = 0;

};

matr_onesrow::~matr_onesrow() 
{
	if (mask)
		mask->release();
	if (prev_b_begin)
		delete prev_b_begin;
	prev_b_begin = NULL;
};

REAL matr_onesrow::norm() const {
	return fabs(val);
};

size_t matr_onesrow::rows() const {
	return N;
};

size_t matr_onesrow::cols() const {
	return N;
};

REAL matr_onesrow::element_at(size_t i, size_t j, size_t * next_j) const 
{
	size_t _next_j = UINT_MAX;
	REAL res = REAL(0);

	if ( mask->get(i) == false )
		res = val;

	if (next_j) {
		*next_j = j+1;
	}

	return res;
};

REAL matr_onesrow::at(size_t i, size_t j, size_t * next_j) const 
{
	bool zero = mask->get(j);
	
	if (zero) {
		if ( next_j )
			*next_j = UINT_MAX;
		return REAL(0);
	}

	return element_at(i,j,next_j);
};

REAL matr_onesrow::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end)
{
	if (mask->get(J))
		return REAL(0);

#ifdef HAVE_THREADS
	matr_onesrow_mutex.enter();
#endif
	if (prev_b_begin) {
		if (*prev_b_begin == b_begin) {
			REAL res = prev_val;
#ifdef HAVE_THREADS
			matr_onesrow_mutex.leave();
#endif
			return res;
		}
	}
#ifdef HAVE_THREADS
	matr_onesrow_mutex.leave();
#endif
		
	size_t i;
	REAL res = REAL(0);
	for (i = 0; i < N; i++) {
		if (mask->get(i))
			continue;
		res += val * *(b_begin+i);
	}

	prev_val = res;
#ifdef HAVE_THREADS
	matr_onesrow_mutex.enter();
#endif
	if (prev_b_begin)
		delete prev_b_begin;
	prev_b_begin = new extvec::const_iterator(b_begin);

#ifdef HAVE_THREADS
	matr_onesrow_mutex.leave();
#endif
		
	return res;
};

REAL matr_onesrow::mult_transposed_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) 
{
	return mult_line(J, b_begin, b_end);
};

void matr_onesrow::call_after_mult() {
	if (prev_b_begin)
		delete prev_b_begin;
	prev_b_begin = NULL;
};

//
//
// matr_row
//
//

matr_row::matr_row(size_t iN,
		   bitvec * imask,
		   extvec * ivalues) {
	values = ivalues;
	N = iN;
	
	mask = imask;

	prev_b_begin = NULL;
	prev_val = 0;

};

matr_row::~matr_row() {
	if (mask)
		mask->release();
	if (values)
		values->release();
	if (prev_b_begin)
		delete prev_b_begin;
	prev_b_begin = NULL;
};

REAL matr_row::norm() const {
	return norm2(values, 0);
};

size_t matr_row::rows() const {
	return N;
};

size_t matr_row::cols() const {
	return N;
};

REAL matr_row::element_at(size_t i, size_t j, size_t * next_j) const 
{
	size_t _next_j = UINT_MAX;
	REAL res = REAL(0);

	if ( !mask->get(i) )
		res = (*values)(i)*(*values)(j);

	if (next_j) {
		size_t q;
		for (q = j; q < N; q++) {
			*next_j = q;
			if (mask->get(q))
				break;
		}
	}

	return res;
	
};

REAL matr_row::at(size_t i, size_t j, size_t * next_j) const 
{
	bool zero = mask->get(j);
	
	if (zero) {
		if ( next_j )
			*next_j = UINT_MAX;
		return REAL(0);
	}

	return element_at(i,j,next_j);
};

#ifdef HAVE_THREADS
mutex matr_row_alloc_prev_b_begin;
#endif
REAL matr_row::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end)
{
	if (mask->get(J))
		return REAL(0);

#ifdef HAVE_THREADS
	matr_row_alloc_prev_b_begin.enter();
#endif
	if (prev_b_begin) {
		if (*prev_b_begin == b_begin) {
#ifdef HAVE_THREADS
			matr_row_alloc_prev_b_begin.leave();
#endif
			return prev_val*(*values)(J);
		}
	}
#ifdef HAVE_THREADS
	matr_row_alloc_prev_b_begin.leave();
#endif
	
	size_t i;
	REAL res = REAL(0);
	for (i = 0; i < N; i++) {
		if (mask->get(i))
			continue;
		res += (*values)(i) * *(b_begin+i);
	}

	prev_val = res;

#ifdef HAVE_THREADS
	matr_row_alloc_prev_b_begin.enter();
#endif
	if (prev_b_begin)
		delete prev_b_begin;
	prev_b_begin = new extvec::const_iterator(b_begin);
#ifdef HAVE_THREADS
	matr_row_alloc_prev_b_begin.leave();
#endif
		
	return res*(*values)(J);
};

REAL matr_row::mult_transposed_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) 
{
	return mult_line(J, b_begin, b_end);
};

void matr_row::call_after_mult() {
	if (prev_b_begin)
		delete prev_b_begin;
	prev_b_begin = NULL;
};

}; // namespace surfit

