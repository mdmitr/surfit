
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
#include "matrD1.h"
#include "bitvec_alg.h"
#include "grid_line.h"

#include <float.h>
#include <assert.h>

#ifdef _DEBUG
#define CHECK_PTR(p) if((p >= b_begin) && (p < b_end))
#else
#define CHECK_PTR(p) if(true)
#endif

#define FIRST_X		b[0]
#define SECOND_X	b[1]
#define FIRST_Y		b[2]
#define SECOND_Y	b[3]

namespace surfit {

matrD1_rect::matrD1_rect(size_t iN, size_t iNN, 
			 REAL ihx, REAL ihy,
		         size_t ix_from, size_t ix_to, size_t iy_from, size_t iy_to, 
			 const bitvec * imask_solved,
			 const bitvec * imask_undefined,
			 grid_line * ifault) : matr_rect(ix_from, ix_to, iy_from, iy_to, iNN)
{
	N = iN; 
	NN = iNN;
	MM = N/NN; 
	fault = ifault;
	N_cols = N;
	N_rows = N;
	matrNN = x_to - x_from + 1;
	matrMM = y_to - y_from + 1;
	hx2 = ihx*ihx;
	hy2 = ihy*ihy;
	_hx2 = REAL(1)/hx2;
	_hy2 = REAL(1)/hx2;
	make_mask(imask_solved, imask_undefined);
};

void matrD1_rect::make_mask(const bitvec * imask_solved, const bitvec * imask_undefined) {
	mask = create_bitvec(matrMM*matrNN*4);
	size_t j;
	bool first_x, second_x, first_y, second_y;
	for (j = 0; j < matrMM*matrNN; j++) {
		first_x = true;
		second_x = true;
		first_y = true;
		second_y = true;
		size_t n = j % matrNN;
		size_t m = (j - n)/matrNN;
	
		sums_points_D1(n, m, 
			NN, MM, matrNN, matrMM,
			imask_undefined,
			first_x, second_x, 
			first_y, second_y,
			x_from, y_from);
		
		fault_points_D1(n, m, NN, MM, fault,
			first_x, second_x, first_y, second_y,
			x_from, y_from);

		mask->write4(j, first_x, second_x, first_y, second_y);
	}

	mask_solved_undefined = create_bitvec(imask_solved);
	mask_solved_undefined->OR(imask_undefined);

};

REAL matrD1_rect::element_at(size_t i, size_t j, size_t * next_j) const {


	REAL res = REAL(0);
	size_t n = i % NN;
	size_t m = (i-n)/NN;

	if ((n < x_from) || (n > x_to))  {
		if (next_j)
			*next_j = UINT_MAX;
		return res;
	}

	if (m < y_from) {
		if (next_j)
			*next_j = y_from;
		return res;
	}

	if (m > y_to) {
		if (next_j)
			*next_j = UINT_MAX;
		return res;
	}

	n -= x_from;
	m -= y_from;
	size_t local_i = n + m*matrNN;
	bool b[4];

	mask->get4(local_i, b);

	return matrator_serve(i, j, b, next_j);
	
};

REAL matrD1_rect::element_at_transposed(size_t i, size_t j, size_t * next_j) const {
	return element_at(i, j, next_j);
};

REAL matrD1_rect::at(size_t i, size_t j, size_t * next_j) const {

	REAL res = REAL(0);
	size_t n = i % NN;
	size_t m = (i-n)/NN;

	if ((n < x_from) || (n > x_to))  {
		if (next_j)
			*next_j = UINT_MAX;
		return res;
	}

	if (m < y_from) {
		if (next_j)
			*next_j = y_from;
		return res;
	}

	if (m > y_to) {
		if (next_j)
			*next_j = UINT_MAX;
		return res;
	}

	bool zero = mask_solved_undefined->get(i);
	if (!zero)
		zero = mask_solved_undefined->get(j);

	if ( zero ) {
		if (next_j) {
			
			if (j < i-NN) {
				*next_j = i-NN;
				return REAL(0);
			}
			
			if (j < i-1) {
				*next_j = i-1;
				return REAL(0);
			}
			
			if (j < i) {
				*next_j = i;
				return REAL(0);
			}
			
			if (j < i+NN) {
				*next_j = i+NN;
				return REAL(0);
			}

			*next_j = UINT_MAX;
			return REAL(0);
			
		}
	}

	n -= x_from;
	m -= y_from;
	size_t local_i = n + m*matrNN;
	bool b[4];

	mask->get4(local_i, b);

	return matrator_serve(i, j, b, next_j);
	
};

REAL matrD1_rect::at_transposed(size_t i, size_t j, size_t * next_j) const {
	return at(i, j, next_j);
};

REAL matrD1_rect::mult_transposed_line(size_t J, const REAL * b_begin, const REAL * b_end) {
	return mult_line(J, b_begin, b_end);
};

REAL matrD1_rect::mult_line(size_t J, const REAL * b_begin, const REAL * b_end) {
		
	if (mask_solved_undefined->get(J))
		return REAL(0);

	size_t n = J % NN;
	size_t m = (J - n)/NN;

	if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
		return REAL(0);
	
	size_t local_J = n-x_from + (m-y_from)*matrNN;
	bool b[4];
	mask->get4(local_J, b);

	REAL res = REAL(0);
	const REAL * p;

	bool flag = false;
	
	// u_{i,j} - u_{i+1,j}
	if (FIRST_X) {
		
		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+1,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,1);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hx2; // (-1);
			else
				assert(0);
		}

	}

	// u_{i-1,j} - u_{i,j}
	if (SECOND_X) {

		p = b_begin + J - 1 - 1;

		flag = incr_ptr(p,J-1,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hx2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx2; // 1;
			else 
				assert(0);
		}
		
	}

	// u_{i,j} - u_{i,j+1}
	if (FIRST_Y) {

		p = b_begin + J - 1;

		flag = incr_ptr(p,J,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+NN,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,NN);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hy2; // (-1);
			else
				assert(0);
		}
		
	}

	// u_{i,j-1} - u_{i,j}
	if (SECOND_Y) {
		
		p = b_begin + J - NN - 1;

		flag = incr_ptr(p,J-NN,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hy2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved_undefined,x_from,x_to,y_from,y_to,NN,NN);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else 
				assert(0);
		}
								
	}
	
	return res;

};

size_t matrD1_rect::cols() const {
	return N_cols;
};

size_t matrD1_rect::rows() const {
	return N_rows;
};

REAL matrD1_rect::norm() const {
	return matrD1::norm();
};

}; // namespace surfit;


