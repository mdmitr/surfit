
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
#include "matr_cntrs.h"
#include "bitvec.h"
#include "free_elements.h"

#include <algorithm>
#include <assert.h>
#include <limits.h>

namespace surfit {

bool pos1_sorter(const cntr_rec & d1, const cntr_rec & d2)
{
	if (d1.pos1 == d2.pos1)
		return ((d1.pos2-d1.pos1) < (d2.pos2-d2.pos1));
	return ( d1.pos1 < d2.pos1 );
};

bool pos1_finder(const cntr_rec & d1, const cntr_rec & d2)
{
	return ( d1.pos1 < d2.pos1 );
};

struct pos2_sorter
{
	pos2_sorter(std::vector<cntr_rec> * idata): data(idata) {};
	bool operator()(size_t p1, size_t p2)
	{
		if ( (*data)[p1].pos2 == (*data)[p2].pos2 )
			return ( ((*data)[p1].pos2 - (*data)[p1].pos1) < ((*data)[p2].pos2 - (*data)[p2].pos1) );
		return ( (*data)[p1].pos2 < (*data)[p2].pos2 );
	};
	std::vector<cntr_rec> * data;
};

struct pos2_finder
{
	pos2_finder(std::vector<cntr_rec> * idata, size_t ipos) : data(idata), pos(ipos) {};
	bool operator()(size_t p1, size_t p2)
	{
		return ( (*data)[p1].pos2 < pos );
	};
	std::vector<cntr_rec> * data;
	size_t pos;
};

matr_cntrs::matr_cntrs(REAL imult, std::vector<cntr_rec> * idata, size_t iN, bitvec * imask,
		       size_t iNN, size_t iMM)
{
	mult = imult;
	NN = iNN;
	MM = iMM;
	mask = imask;
	data = idata;
	std::sort(data->begin(), data->end(), pos1_sorter);
	pos2_sorted = new std::vector<size_t>(data->size());
	size_t i;
	for (i = 0; i < data->size(); i++)
	{
		(*pos2_sorted)[i] = i;
	}
	std::sort(pos2_sorted->begin(), pos2_sorted->end(), pos2_sorter(data));
	N = iN;

	fast_data = new std::vector<fast_rec *>(N);
	
	for (i = 0; i < N; i++) {
		if (mask->get(i) == false) {
			(*fast_data)[i] = NULL;
			continue;
		}
		const cntr_rec * r1_1 = NULL, * r1_2 = NULL;
		find_pos1(i, r1_1, r1_2);
		const cntr_rec * r2_1 = NULL, * r2_2 = NULL;
		find_pos2(i, r2_1, r2_2);

		fast_rec * r = new fast_rec(i, r1_1, r1_2, r2_1, r2_2);
		(*fast_data)[i] = r;
	}

};

matr_cntrs::~matr_cntrs()
{
	delete data;
	if (mask)
		mask->release();
	delete pos2_sorted;
	free_elements(fast_data->begin(), fast_data->end());
	delete fast_data;
};

REAL matr_cntrs::element_at(size_t i, size_t j, size_t * next_j) const
{
	return at(i, j, next_j);
};
	
REAL matr_cntrs::at(size_t i, size_t j, size_t * next_j) const
{
	if (mask->get(i) == false) {
		if (next_j) {
			*next_j = UINT_MAX;	
		}
		return REAL(0);
	}

	if (j+NN < i) {
		if (next_j)
			*next_j = i-NN;
		return REAL(0);
	}

	if (j > i+NN) {
		if (next_j)
			*next_j = UINT_MAX;
		return REAL(0);
	}

	const cntr_rec * r1_1 = NULL, * r1_2 = NULL;
	//find_pos1(i, r1_1, r1_2);
	const cntr_rec * r2_1 = NULL, * r2_2 = NULL;
	//find_pos2(i, r2_1, r2_2);
	find_fast(i, r1_1, r1_2, r2_1, r2_2);

#ifdef DEBUG
	if (r1_1) {
		assert(r1_1->pos1 == i);
		assert(r1_1->pos2 == i+1);
	}
	if (r1_2) {
		assert(r1_2->pos1 == i);
		assert(r1_2->pos2 == i+NN);
	}
	if (r2_1) {
		assert(r2_1->pos2 == i);
		assert(r2_1->pos1 == i-1);
	}
	if (r2_2) {
		assert(r2_2->pos2 == i);
		assert(r2_2->pos1 == i-NN);
	}
#endif

	if (j+NN < i) {
		if (next_j)
			*next_j = i-NN;
		return REAL(0);
	}
	if (j+NN == i) {
		if (next_j)
			*next_j = i-1;
		if (r2_2)
			return mult*r2_2->sum2;
		return REAL(0);
	}
	if (j+1 < i) {
		if (next_j)
			*next_j = i-1;
		return REAL(0);
	}
	if (j+1 == i) {
		if (next_j)
			*next_j = i;
		if (r2_1)
			return mult*r2_1->sum2;
		return REAL(0);
	}
	if (j == i) {
		if (next_j)
			*next_j = i+1;
		REAL res = 0;
		if (r1_1)
			res += r1_1->sum1;
		if (r1_2)
			res += r1_2->sum1;
		if (r2_1)
			res += r2_1->sum3;
		if (r2_2)
			res += r2_2->sum3;
		return mult*res;
	}
	if (j == i+1) {
		if (next_j)
			*next_j = i+NN;
		if (r1_1)
			return mult*r1_1->sum2;
		return REAL(0);
	}
	if (j < i+NN) {
		if (next_j)
			*next_j = i+NN;
		return REAL(0);
	}
	if (j == i+NN) {
		if (next_j)
			*next_j = UINT_MAX;
		if (r1_2)
			return mult*r1_2->sum2;
		return REAL(0);
	}
	
	assert(0);
	return REAL(0);
};
	
REAL matr_cntrs::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end)
{
	if (mask->get(J) == false)
		return REAL(0);

	const cntr_rec * r1_1 = NULL, * r1_2 = NULL;
	//find_pos1(J, r1_1, r1_2);
	const cntr_rec * r2_1 = NULL, * r2_2 = NULL;
	//find_pos2(J, r2_1, r2_2);
	find_fast(J, r1_1, r1_2, r2_1, r2_2);

	REAL res = REAL(0);
	extvec::const_iterator p;

	if (r2_2) {
		p = b_begin + J - NN;
		res += *p * r2_2->sum2;
	}

	if (r2_1) {
		p = b_begin + J - 1;
		res += *p * r2_1->sum2;
	}

	p = b_begin + J;
	if (r1_1)
		res += *p * r1_1->sum1;
	if (r1_2)
		res += *p * r1_2->sum1;
	if (r2_1)
		res += *p * r2_1->sum3;
	if (r2_2)
		res += *p * r2_2->sum3;

	if (r1_1) {
		p = b_begin + J + 1;
		res += *p * r1_1->sum2;
	}

	if (r1_2) {
		p = b_begin + J + NN;
		res += *p * r1_2->sum2;
	}

	return mult*res;
};

size_t matr_cntrs::cols() const
{
	return N;
};

size_t matr_cntrs::rows() const
{
	return N;
};

REAL matr_cntrs::norm() const
{
	assert(0);
	return N;
};

void matr_cntrs::fill_vector(extvec * v)
{
	size_t i;
	for (i = 0; i < N; i++) {
		(*v)(i) = 0;
		if (mask->get(i) == false) 
			continue;
	
		const cntr_rec * r1_1 = NULL, * r1_2 = NULL;
		//find_pos1(i, r1_1, r1_2);
		const cntr_rec * r2_1 = NULL, * r2_2 = NULL;
		//find_pos2(i, r2_1, r2_2);
		find_fast(i, r1_1, r1_2, r2_1, r2_2);

		if (r1_1)
			(*v)(i) += r1_1->sum4;
		if (r1_2)
			(*v)(i) += r1_2->sum4;
		if (r2_1)
			(*v)(i) += r2_1->sum5;
		if (r2_2)
			(*v)(i) += r2_2->sum5;

		(*v)(i) *= mult;
	}
};
	
void matr_cntrs::find_pos1(size_t pos, const cntr_rec *& r1, const cntr_rec *& r2) const 
{
	cntr_rec val;
	val.pos1 = pos;
	data_it it = std::lower_bound(data->begin(), data->end(), val, pos1_finder);
	if (it == data->end())
		return;
	if ( (*it).pos1 == pos ) {
		if ( (*it).pos2-(*it).pos1 == 1)
			r1 = &(*it);
		else 
			r2 = &(*it);
	}
	it++;
	if (it != data->end()) {
		if ( (*it).pos1 == pos ) {
			if ( (*it).pos2-(*it).pos1 == 1)
				r1 = &(*it);
			else 
				r2 = &(*it);
		}
	}
	return;
};

void matr_cntrs::find_pos2(size_t pos, const cntr_rec *& r1, const cntr_rec *& r2) const 
{
	cntr_rec val;
	val.pos2 = pos;
	pos2_finder ff(data, pos);
	std::vector<size_t>::iterator it = 
	std::lower_bound(pos2_sorted->begin(), pos2_sorted->end(), UINT_MAX, ff); 
	if (it == pos2_sorted->end())
		return;
	const cntr_rec * res = &((*data)[*it]);
	if (res->pos2 == pos) {
		if (res->pos2-res->pos1 == 1)
			r1 = res;
		else
			r2 = res;
	}
	it++;
	if (it == pos2_sorted->end())
		return;
	res = &((*data)[*it]);
	if (res->pos2 == pos) {
		if (res->pos2-res->pos1 == 1)
			r1 = res;
		else
			r2 = res;
	}
	return;
};

bool matr_cntrs::find_fast(size_t pos, 
			   const cntr_rec *& r1_1, const cntr_rec *& r1_2,
			   const cntr_rec *& r2_1, const cntr_rec *& r2_2) const
{
	fast_rec * r = (*fast_data)[pos];
	assert(r != NULL);
	r1_1 = r->r1_1;
	r1_2 = r->r1_2;
	r2_1 = r->r2_1;
	r2_2 = r->r2_2;
	return true;
};

}; // namespace surfit;

