
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
#include "operD1.h"
#include "bitvec_alg.h"
#include "grid_line.h"

#include <float.h>
#include <assert.h>

#ifdef _DEBUG
#define CHECK_PTR(p) if((p >= b_begin) && (p < b_end))
#else
#define CHECK_PTR(p) if(true)
#endif

namespace surfit {

operD1_rect::operD1_rect(int iN, int iNN, 
			 REAL ihx, REAL ihy,
		         int ix_from, int ix_to, int iy_from, int iy_to,
			 bitvec * imask_solved,
			 bitvec * imask_undefined,
			 grid_line * ifault) 
{
	N = iN; 
	NN = iNN;
	MM = N/NN; 
	mask_solved = imask_solved;
	mask_undefined = imask_undefined;
	fault = ifault;
	N_cols = N;
	N_rows = N;
	x_from = ix_from; x_to = ix_to;
	matrNN = x_to - x_from + 1;
	y_from = iy_from; y_to = iy_to;
	matrMM = y_to - y_from + 1;
	hx2 = ihx*ihx;
	hy2 = ihy*ihy;
	_hx2 = REAL(1)/hx2;
	_hy2 = REAL(1)/hx2;
	make_mask();
};

void operD1_rect::make_mask() {
	mask = new bitvec(matrMM*matrNN*4);
	int j;
	bool first_x, second_x, first_y, second_y;
	for (j = 0; j < matrMM*matrNN; j++) {
		first_x = true;
		second_x = true;
		first_y = true;
		second_y = true;
		int n = j % matrNN;
		int m = (j - n)/matrNN;
	
		sums_points_D1(n, m, 
			NN, MM, matrNN, matrMM,
			mask_undefined,
			first_x, second_x, 
			first_y, second_y,
			x_from, y_from);
		
		fault_points_D1(n, m, NN, MM, fault,
			first_x, second_x, first_y, second_y,
			x_from, y_from);

		mask->write4(j, first_x, second_x, first_y, second_y);
	}

};

REAL operD1_rect::operator()(int i, int j, int * next_j) const {


	REAL res = REAL(0);
	int n = i % NN;
	int m = (i-n)/NN;

	if ((n < x_from) || (n > x_to))  {
		if (next_j)
			*next_j = INT_MAX;
		return res;
	}

	if (m < y_from) {
		if (next_j)
			*next_j = y_from;
		return res;
	}

	if (m > y_to) {
		if (next_j)
			*next_j = INT_MAX;
		return res;
	}

	n -= x_from;
	m -= y_from;
	int local_i = n + m*matrNN;
	bool first_x = true, second_x = true, first_y = true, second_y = true;

	mask->get4(local_i, first_x, second_x, first_y, second_y);

	return operator_serve(i, j, first_x, second_x, first_y, second_y, next_j);
	
};

REAL operD1_rect::at(int i, int j, int * next_j) const {

	REAL res = REAL(0);
	int n = i % NN;
	int m = (i-n)/NN;

	if ((n < x_from) || (n > x_to))  {
		if (next_j)
			*next_j = INT_MAX;
		return res;
	}

	if (m < y_from) {
		if (next_j)
			*next_j = y_from;
		return res;
	}

	if (m > y_to) {
		if (next_j)
			*next_j = INT_MAX;
		return res;
	}

	bool zero = mask_solved->get(i);
	if (!zero)
		zero = mask_solved->get(j);

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

			*next_j = INT_MAX;
			return REAL(0);
			
		}
	}

	n -= x_from;
	m -= y_from;
	int local_i = n + m*matrNN;
	bool first_x = true, second_x = true, first_y = true, second_y = true;

	mask->get4(local_i, first_x, second_x, first_y, second_y);

	return operator_serve(i, j, first_x, second_x, first_y, second_y, next_j);
	
};

REAL operD1_rect::mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const {
	return mult_line(J, b_begin, b_end);
};

REAL operD1_rect::mult_line(int J, const REAL * b_begin, const REAL * b_end) const {
		
	int n = J % NN;
	int m = (J - n)/NN;

	if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
		return REAL(0);

	if (mask_solved->get(J))
		return REAL(0);

	if (mask_undefined->get(J))
		return REAL(0);

	int local_J = n-x_from + (m-y_from)*matrNN;
	bool first_x = true, second_x = true, first_y = true, second_y = true;
	mask->get4(local_J, first_x, second_x, first_y, second_y);

	REAL res = REAL(0);
	const REAL * p;

	bool flag = false;
	
	// u_{i,j} - u_{i+1,j}
	if (first_x) {
		
		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+1,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,1);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hx2; // (-1);
			else
				assert(0);
		}

	}

	// u_{i-1,j} - u_{i,j}
	if (second_x) {

		p = b_begin + J - 1 - 1;

		flag = incr_ptr(p,J-1,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hx2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx2; // 1;
			else 
				assert(0);
		}
		
	}

	// u_{i,j} - u_{i,j+1}
	if (first_y) {

		p = b_begin + J - 1;

		flag = incr_ptr(p,J,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+NN,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,NN);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hy2; // (-1);
			else
				assert(0);
		}
		
	}

	// u_{i,j-1} - u_{i,j}
	if (second_y) {
		
		p = b_begin + J - NN - 1;

		flag = incr_ptr(p,J-NN,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,1);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hy2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved,mask_undefined,x_from,x_to,y_from,y_to,NN,NN);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else 
				assert(0);
		}
								
	}
	
	return res;

};

long operD1_rect::cols() const {
	return N_cols;
};

long operD1_rect::rows() const {
	return N_rows;
};

}; // namespace surfit;


