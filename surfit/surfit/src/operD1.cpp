
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
#include "grid_line.h"
#include "bitvec.h"
#include "bitvec_alg.h"

#include <float.h>
#include <assert.h>

#ifdef _DEBUG
#define CHECK_PTR(p) if((p >= b_begin) && (p < b_end))
#else
#define CHECK_PTR(p) if(true)
#endif

namespace surfit {

operD1::operD1(int iN, int iNN, 
	       REAL ihx, REAL ihy,
	       bitvec * imask_solved,
	       bitvec * imask_undefined,
	       grid_line * ifault) { 
	N = iN; 
	NN = iNN;
	MM = N/NN; 
	mask_solved = imask_solved;
	mask_undefined = imask_undefined;
	fault = ifault;
	hx2 = ihx*ihx;
	hy2 = ihy*ihy;
	_hx2 = ihy/ihx;
	_hy2 = ihx/ihy;
	mask = NULL;
	make_mask();
};

operD1::~operD1() {
	delete mask;
};

void operD1::make_mask() {
	mask = new bitvec(rows()*4);
	int j;
	bool first_x, second_x, first_y, second_y;
	for (j = 0; j < rows(); j++) {
		first_x = true;
		second_x = true;
		first_y = true;
		second_y = true;
		int n = j % NN;
		int m = (j - n)/NN;

		sums_points_D1(n, m, 
			NN, MM, NN, MM,
			mask_undefined,
			first_x, second_x, 
			first_y, second_y);
		
		fault_points_D1(n, m, NN, MM, fault,
				first_x, second_x, first_y, second_y);

		mask->write4(j, first_x, second_x, first_y, second_y);
	}

};

REAL operD1::operator_serve(int i, int j, bool first_x, bool second_x, bool first_y, bool second_y, int * next_j) const {

	REAL res = REAL(0);

	int next_j_dx = INT_MAX;
	int next_j_dy = INT_MAX;

	
	if ( (!first_x) && (!second_x) &&
		 (!first_y) && (!second_y) )
	{
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
	

	// u_{i,j} - u_{i+1,j}
	if (first_x) {
		if (j < i) {
			next_j_dx = MIN(i, next_j_dx);
			goto mark_second_x;
		}

		if (i == j) {
			res += _hx2; // 1
			next_j_dx = MIN(i+1, next_j_dx);
			goto mark_second_x;
		}

		if (j == i+1) {
			res += -_hx2; // -1
			next_j_dx = MIN(INT_MAX, next_j_dx);
			goto mark_second_x;
		}

	}
	
mark_second_x:

	// u_{i-1,j} - u_{i,j}
	if (second_x) {

		if (j < i-1) {
			next_j_dx = MIN(i-1, next_j_dx);
			goto mark_first_y;
		}

		if (j == i-1) {
			res += -_hx2; // -1;
			next_j_dx = MIN(i, next_j_dx);
			goto mark_first_y;
		}
		
		if (i == j) {
			res += _hx2; // 1;
			next_j_dx = MIN(INT_MAX, next_j_dx);
			goto mark_first_y;
		}
		
	}

mark_first_y:

	// u_{i,j} - u_{i,j+1}
	if (first_y) {

		if (j < i) {
			next_j_dy = MIN(i, next_j_dy);
			goto mark_second_y;
		}

		if (i == j) {
			res += _hy2; // 1;
			next_j_dy = MIN(i+NN, next_j_dy);
			goto mark_second_y;
		}
		
		if (j < i+NN) {
			next_j_dy = MIN(i+NN, next_j_dy);
			goto mark_second_y;
		}

		if (j == i+NN) {
			res += -_hy2; // -1;
			next_j_dy = MIN(INT_MAX, next_j_dy);
			goto mark_second_y;
		}

	}

mark_second_y:

	// u_{i,j-1} - u_{i,j}
	if (second_y) {
		
		if (j < i-NN) {
			next_j_dy = MIN(i-NN, next_j_dy);
			goto exit;
		}

		if (j == i-NN) {
			res += -_hy2; // -1;
			next_j_dy = MIN(i, next_j_dy);
			goto exit;
		}

		if (j < i) {
			next_j_dy = MIN(i, next_j_dy);
			goto exit;
		}

		if (i == j) {
			res += _hy2; // 1;
			next_j_dy = MIN(INT_MAX, next_j_dy);
			goto exit;
		}
										
	}

exit:

	if (next_j) {
		*next_j = MIN(next_j_dx, next_j_dy);
	}

	return res;	
};

REAL operD1::operator()(int i, int j, int * next_j) const {

	bool first_x = true, second_x = true, first_y = true, second_y = true;

	mask->get4(i, first_x, second_x, first_y, second_y);

	return operator_serve(i, j, first_x, second_x, first_y, second_y, next_j);
	
};

REAL operD1::at(int i, int j, int * next_j) const {

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

	bool first_x = true, second_x = true, first_y = true, second_y = true;

	mask->get4(i, first_x, second_x, first_y, second_y);

	return operator_serve(i, j, first_x, second_x, first_y, second_y, next_j);
	
};

REAL operD1::mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const {
	return mult_line(J, b_begin, b_end);
};

REAL operD1::mult_line(int J, const REAL * b_begin, const REAL * b_end) const {

	int n = J % NN;
	int m = (J - n)/NN;

	if (mask_solved->get(J))
		return REAL(0);

	if (mask_undefined->get(J))
		return REAL(0);
	
	REAL res = REAL(0);
	const REAL * p;

	bool flag = false;
	bool first_x = true, second_x = true, first_y = true, second_y = true;

	mask->get4(J, first_x, second_x, first_y, second_y);

	// u_{i,j} - u_{i+1,j}
	if (first_x) {
		
		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved,mask_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+1,mask_solved,mask_undefined);

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

		flag = incr_ptr(p,J-1,mask_solved,mask_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hx2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved,mask_undefined);
		
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

		flag = incr_ptr(p,J,mask_solved,mask_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+NN,mask_solved,mask_undefined,NN);
		
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

		flag = incr_ptr(p,J-NN,mask_solved,mask_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hy2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved,mask_undefined,NN);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else 
				assert(0);
		}

	}

	return res;
	
};

REAL operD1::norm() const {
	return REAL(2 * (2*_hx2 + 2*_hy2));
};

long operD1::cols() const {
	return N;
};

long operD1::rows() const {
	return N;
};

}; // namespace surfit;


