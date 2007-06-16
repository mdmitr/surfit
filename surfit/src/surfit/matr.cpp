
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
#include "matr.h"
#include "vec.h"
#include "bitvec.h"
#include "free_elements.h"
#include "variables_tcl.h"
#include "threads.h"

#include <float.h>
#include <limits.h>

namespace surfit {

//////////////////
//
// matr
//
//////////////////

#ifdef HAVE_THREADS
struct matr_mult_job : public job 
{
	matr_mult_job()
	{
		m = NULL;
		b = NULL;
		r = NULL;
		J_from = 0;
		J_to = 0;
	};
	void set(matr * im, const extvec * ib, extvec * ir, size_t iJ_from, size_t iJ_to)
	{
		m = im;
		b = ib;
		r = ir;
		J_from = iJ_from;
		J_to = iJ_to;
	};
	virtual void do_job() 
	{
		size_t J;
		for (J = J_from; J < J_to; J++) {
			(*r)(J) = m->mult_line(J, b->const_begin(), b->const_end());
		}
	};

	matr * m;
	const extvec * b;
	extvec * r;
	size_t J_from, J_to;
};

matr_mult_job matr_mult_jobs[MAX_CPU];
#endif

void matr::mult(const extvec * b, extvec * r) {
#ifdef HAVE_THREADS
	if (sstuff_get_threads() == 1) {
#endif
		size_t J;
		for (J = 0; J < rows(); J++) {
			(*r)(J) = mult_line(J, b->const_begin(), b->const_end());
		}
		call_after_mult();
#ifdef HAVE_THREADS
	} else {
		size_t i;
		size_t rws = rows();
		size_t step = rws/(sstuff_get_threads());
		size_t ost = rws % (sstuff_get_threads());
		size_t J_from = 0;
		size_t J_to = 0;
		for (i = 0; i < sstuff_get_threads(); i++) {
			J_to = J_from + step;
			if (i == 0)
				J_to += ost;

			matr_mult_job & f = matr_mult_jobs[i];
			f.set(this, b, r, J_from, J_to);
			set_job(&f, i);
			J_from = J_to;
		}
		
		do_jobs();
		call_after_mult();

	};
#endif
};

void matr::call_after_mult() { };

//////////////////
//
// matr_rect     
// 
//////////////////

#ifdef HAVE_THREADS
struct matr_rect_mult_job : public job 
{
	matr_rect_mult_job()
	{
		m = NULL;
		b = NULL;
		r = NULL;
		J_from = 0;
		J_to = 0;
	};
	void set(matr_rect * im, const extvec * ib, extvec * ir, size_t iJ_from, size_t iJ_to)
	{
		m = im;
		b = ib;
		r = ir;
		J_from = iJ_from;
		J_to = iJ_to;
	};
	virtual void do_job() 
	{
		size_t J;
		size_t i, j;
		for (j = J_from; j < J_to; j++) {
			for (i = m->x_from; i <= (size_t)m->x_to; i++) {
				J = i + j*m->n_grid_cols;
				(*r)(J) = m->mult_line(J, b->const_begin(), b->const_end());
			}
		}
	};

	matr_rect * m;
	const extvec * b;
	extvec * r;
	size_t J_from, J_to;
};

matr_rect_mult_job matr_rect_mult_jobs[MAX_CPU];
#endif


matr_rect::matr_rect(size_t ix_from, size_t ix_to, size_t iy_from, size_t iy_to, size_t in_grid_cols) {
	x_from = ix_from;
	x_to = ix_to;
	y_from = iy_from;
	y_to = iy_to;
	n_grid_cols = in_grid_cols;
};

void matr_rect::mult(const extvec * b, extvec * r) {
	size_t J;
	size_t i, j;
	for (i = 0; i < b->size(); i++)
		(*r)(i) = 0;

#ifdef HAVE_THREADS
	if (sstuff_get_threads() == 1) {
#endif
		for (j = y_from; j <= y_to; j++) {
			for (i = x_from; i <= x_to; i++) {
				J = i + j*n_grid_cols;
				(*r)(J) = mult_line(J, b->const_begin(), b->const_end());
			}
		}
		call_after_mult();

#ifdef HAVE_THREADS
	} else {
		size_t i;
		size_t rws = y_to-y_from+1;
		size_t step = rws/(sstuff_get_threads());
		size_t ost = rws % (sstuff_get_threads());
		size_t J_from = y_from;
		size_t J_to = 0;
		for (i = 0; i < sstuff_get_threads(); i++) {
			J_to = J_from + step;
			if (i == 0)
				J_to += ost;

			matr_rect_mult_job & f = matr_rect_mult_jobs[i];
			f.set(this, b, r, J_from, J_to);
			set_job(&f, i);
			J_from = J_to;
		}
		
		do_jobs();
		call_after_mult();
	}
#endif
};

//////////////////
//
// matr_sum
//
//////////////////

matr_sum::matr_sum(REAL iw1, matr *iT1, REAL iw2, matr *iT2) 
{
	w1 = iw1;
	T1 = iT1;
	cT1 = NULL;
	w2 = iw2;
	T2 = iT2;
	cT2 = NULL;
};

matr_sum::~matr_sum() 
{
	delete T1;
	delete T2;
};

void matr_sum::set_const() 
{
	cT1 = T1;
	cT2 = T2;
	T1 = NULL;
	T2 = NULL;
};

REAL matr_sum::element_at(size_t i, size_t j, size_t * next_j) const 
{
	REAL res = 0;
	size_t next_j1 = UINT_MAX;
	size_t next_j2 = UINT_MAX;
	if (T1 && w1)
		res += w1 * T1->element_at(i,j,&next_j1);
	if (cT1 && w1)
		res += w1 * cT1->element_at(i,j,&next_j1);
	if (T2 && w2)
		res += w2 * T2->element_at(i,j,&next_j2);
	if (cT2 && w2)
		res += w2 * cT2->element_at(i,j,&next_j2);
	
	if (next_j)
		*next_j = MIN(next_j1,next_j2);
	
	return res;
	
};

REAL matr_sum::at(size_t i, size_t j, size_t * next_j) const 
{
	REAL res = 0;
	size_t next_j1 = UINT_MAX;
	size_t next_j2 = UINT_MAX;
	if (T1 && w1)
		res += w1 * T1->at(i,j,&next_j1);
	if (cT1 && w1)
		res += w1 * cT1->at(i,j,&next_j1);
	if (T2 && w2)
		res += w2 * T2->at(i,j,&next_j2);
	if (cT2 && w2)
		res += w2 * cT2->at(i,j,&next_j2);
	
	if (next_j)
		*next_j = MIN(next_j1,next_j2);
	
	return res;
	
};

REAL matr_sum::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) 
{
	REAL res = 0;
	if (T1 && w1)
		res += w1*T1->mult_line(J, b_begin, b_end);
	if (cT1 && w1)
		res += w1*cT1->mult_line(J, b_begin, b_end);
	if (T2 && w2)
		res += w2*T2->mult_line(J, b_begin, b_end);
	if (cT2 && w2)
		res += w2*cT2->mult_line(J, b_begin, b_end);
	
	return res;
};

void matr_sum::call_after_mult() 
{
	if (T1)
		T1->call_after_mult();
	if (cT1)
		cT1->call_after_mult();
	if (T2)
		T2->call_after_mult();
	if (cT2)
		cT2->call_after_mult();
};

REAL matr_sum::norm() const 
{
	REAL res = 0;
	if (T1 && w1)
		res += w1*T1->norm();
	if (cT1 && w1)
		res += w1*cT1->norm();
	if (T2 && w2)
		res += w2*T2->norm();
	if (cT2 && w2)
		res += w2*cT2->norm();
	
	return res;
};

size_t matr_sum::cols() const 
{
	if (T1)
		return T1->cols();
	if (cT1)
		return cT1->cols();
	if (T2)
		return T2->cols();
	if (cT2)
		return cT2->cols();
	return 0;
};

size_t matr_sum::rows() const 
{
	if (T1)
		return T1->rows();
	if (cT1)
		return cT1->rows();
	if (T2)
		return T2->rows();
	if (cT2)
		return cT2->rows();
	return 0;
};

//////////////////
//
// matr_sums
//
//////////////////

matr_sums::matr_sums(std::vector<REAL> * iweights, std::vector<matr *> * imatrices) 
{
	weights = iweights;
	matrices = imatrices;
};

matr_sums::~matr_sums() 
{
	delete weights;
	free_elements(matrices->begin(), matrices->end());
	delete matrices;
};

REAL matr_sums::element_at(size_t i, size_t j, size_t * next_j) const 
{
	REAL res = 0;
	size_t next_j1 = UINT_MAX;
	size_t next_j2 = UINT_MAX;
	size_t q;
	for (q = 0; q < matrices->size(); q++) {
		matr * T = (*matrices)[q];
		REAL w = (*weights)[q];
		res += w * T->element_at(i,j,&next_j2);
		next_j1 = MIN(next_j1, next_j2);
	}
	
	if (next_j)
		*next_j = next_j1;
	
	return res;
};

REAL matr_sums::at(size_t i, size_t j, size_t * next_j) const 
{
	REAL res = 0;
	size_t next_j1 = UINT_MAX;
	size_t next_j2 = UINT_MAX;
	size_t q;
	for (q = 0; q < matrices->size(); q++) {
		matr * T = (*matrices)[q];
		if (T == NULL) 
			continue;
		REAL w = (*weights)[q];
		res += w * T->at(i,j,&next_j2);
		next_j1 = MIN(next_j1, next_j2);
	}
	
	if (next_j)
		*next_j = next_j1;
	
	return res;
};

REAL matr_sums::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) 
{
	REAL res = 0;
	size_t q;
	for (q = 0; q < matrices->size(); q++) {
		matr * T = (*matrices)[q];
		if (!T)
			continue;
		REAL w = (*weights)[q];
		res += w * T->mult_line(J, b_begin, b_end);
	}
	return res;
};

void matr_sums::call_after_mult() 
{
	size_t q;
	for (q = 0; q < matrices->size(); q++) {
		matr * T = (*matrices)[q];
		if (T)
			T->call_after_mult();
	}
};

REAL matr_sums::norm() const 
{
	REAL res = 0;
	size_t q;
	for (q = 0; q < matrices->size(); q++) {
		matr * T = (*matrices)[q];
		if (T == NULL)
			continue;
		REAL w = (*weights)[q];
		res += w * T->norm();
	}
	return res;
};

size_t matr_sums::cols() const 
{
	matr * T = (*matrices)[0];
	return T->cols();
};

size_t matr_sums::rows() const 
{
	matr * T = (*matrices)[0];
	return T->rows();
};

//////////////////
//
// matr_mask
//
//////////////////

matr_mask::matr_mask(const bitvec * imask, matr * imatrix) 
{
	mask = imask;
	matrix = imatrix;	
};

matr_mask::~matr_mask() 
{
	// delete mask;
	delete matrix;	
};

REAL matr_mask::element_at(size_t i, size_t j, size_t * next_j) const 
{
	if (mask)
	if (mask->get(i) == false) {
		if (next_j)
			*next_j = UINT_MAX;
		return REAL(0);
	}

	if (mask)
	if (mask->get(j) == false) {
		if (next_j)
			*next_j = UINT_MAX;
		return REAL(0);
	}

	return matrix->element_at(i,j,next_j);
	
};

REAL matr_mask::at(size_t i, size_t j, size_t * next_j) const 
{
	if (mask)
	if (mask->get(i) == false) {
		if (next_j)
			*next_j = UINT_MAX;
		return REAL(0);
	}

	if (mask)
	if (mask->get(j) == false) {
		if (next_j)
			*next_j = UINT_MAX;
		return REAL(0);
	}

	return matrix->at(i,j,next_j);
	
};

REAL matr_mask::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) 
{
	if (mask)
	if (mask->get(J) == false) 
		return REAL(0);
	
	return matrix->mult_line(J, b_begin, b_end);
	
};

void matr_mask::call_after_mult() {
	
	matrix->call_after_mult();

};

REAL matr_mask::norm() const 
{
	return matrix->norm();
};

size_t matr_mask::cols() const 
{
	return matrix->cols();
};

size_t matr_mask::rows() const {

	return matrix->rows();
	
};

//////////////////
//
// matr_rect_sum
//
//////////////////

matr_rect_sum::matr_rect_sum(size_t ix_from, size_t ix_to, size_t iy_from, size_t iy_to, size_t in_grid_cols,
			     REAL iw1, matr_rect *iT1, REAL iw2, matr_rect *iT2) 
			     : matr_rect(ix_from, ix_to, iy_from, iy_to, in_grid_cols) 
{
	w1 = iw1;
	T1 = iT1;
	cT1 = NULL;
	w2 = iw2;
	T2 = iT2;
	cT2 = NULL;
};

matr_rect_sum::~matr_rect_sum() 
{
	delete T1;
	delete T2;
};

void matr_rect_sum::set_const() {
	cT1 = T1;
	cT2 = T2;
	T1 = NULL;
	T2 = NULL;
};

REAL matr_rect_sum::element_at(size_t i, size_t j, size_t * next_j) const 
{
	REAL res = 0;
	size_t next_j1 = UINT_MAX;
	size_t next_j2 = UINT_MAX;
	if (T1 && w1)
		res += w1 * T1->element_at(i,j,&next_j1);
	if (cT1 && w1)
		res += w1 * cT1->element_at(i,j,&next_j1);
	if (T2 && w2)
		res += w2 * T2->element_at(i,j,&next_j2);
	if (cT2 && w2)
		res += w2 * cT2->element_at(i,j,&next_j2);
	
	if (next_j)
		*next_j = MIN(next_j1,next_j2);
	
	return res;
	
};

REAL matr_rect_sum::at(size_t i, size_t j, size_t * next_j) const 
{
	REAL res = 0;
	size_t next_j1 = UINT_MAX;
	size_t next_j2 = UINT_MAX;
	if (T1 && w1)
		res += w1 * T1->at(i,j,&next_j1);
	if (cT1 && w1)
		res += w1 * cT1->at(i,j,&next_j1);
	if (T2 && w2)
		res += w2 * T2->at(i,j,&next_j2);
	if (cT2 && w2)
		res += w2 * cT2->at(i,j,&next_j2);
	
	if (next_j)
		*next_j = MIN(next_j1,next_j2);
	
	return res;
	
};

REAL matr_rect_sum::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) 
{
	REAL res = 0;
	if (T1 && w1)
		res += w1*T1->mult_line(J, b_begin, b_end);
	if (cT1 && w1)
		res += w1*cT1->mult_line(J, b_begin, b_end);
	if (T2 && w2)
		res += w2*T2->mult_line(J, b_begin, b_end);
	if (cT2 && w2)
		res += w2*cT2->mult_line(J, b_begin, b_end);
	
	return res;
};

void matr_rect_sum::call_after_mult() 
{
	if (T1)
		T1->call_after_mult();
	if (cT1)
		cT1->call_after_mult();
	if (T2)
		T2->call_after_mult();
	if (cT2)
		cT2->call_after_mult();
};

REAL matr_rect_sum::norm() const 
{
	REAL res = 0;
	if (T1 && w1)
		res += w1*T1->norm();
	if (cT1 && w1)
		res += w1*cT1->norm();
	if (T2 && w2)
		res += w2*T2->norm();
	if (cT2 && w2)
		res += w2*cT2->norm();
	
	return res;
};

size_t matr_rect_sum::cols() const 
{
	if (T1)
		return T1->cols();
	if (cT1)
		return cT1->cols();
	if (T2)
		return T2->cols();
	if (cT2)
		return cT2->cols();
	return 0;
};

size_t matr_rect_sum::rows() const 
{
	if (T1)
		return T1->rows();
	if (cT1)
		return cT1->rows();
	if (T2)
		return T2->rows();
	if (cT2)
		return cT2->rows();
	return 0;
};


}; // namespace surfit;

