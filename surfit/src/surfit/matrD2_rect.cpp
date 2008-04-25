
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
#include "matrD2.h"
#include "grid_line.h"
#include "bitvec.h"
#include "matrD_incr_ptr.h"

#include <assert.h>
#include <limits.h>

#ifdef DEBUG
	#ifdef XXL
		#define CHECK_PTR(p) if(true)
	#else
		#define CHECK_PTR(p) if((p >= b_begin) && (p < b_end))
	#endif
#else
	#define CHECK_PTR(p) if(true)
#endif

#define FIRST_X		b[0]
#define SECOND_X	b[1]
#define THIRD_X		b[2]
#define FIRST_XX	b[3]
#define SECOND_XX	b[4]
#define FIRST_YY	b[5]
#define SECOND_YY	b[6]
#define FIRST_Y		b[7]
#define SECOND_Y	b[8]
#define THIRD_Y		b[9]

namespace surfit {

matrD2_rect::matrD2_rect(size_t iN, size_t iNN, 
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
	rectNN = x_to - x_from + 1;
	rectMM = y_to - y_from + 1;
	hx4 = ihx*ihx*ihx*ihx;
	hy4 = ihy*ihy*ihy*ihy;
	_hx4 = (ihy*ihy)/(ihx*ihx);
	_hy4 = (ihx*ihx)/(ihy*ihy);
	_hxy4 = 1;
	make_mask(imask_solved, imask_undefined);
};

void matrD2_rect::make_mask(const bitvec * imask_solved, const bitvec * imask_undefined) {
	mask = create_bitvec(rectNN*rectMM*10);
	size_t j;
	bool first_x, second_x, third_x;
	bool first_xx, second_xx;
	bool first_yy, second_yy;
	bool first_y, second_y, third_y;

	for (j = 0; j < rectNN*rectMM; j++) {
		first_x = second_x = third_x = true;
		first_xx = second_xx = true;
		first_yy = second_yy = true;
		first_y = second_y = third_y = true;
		
		size_t n = j % rectNN;
		size_t m = (j - n)/rectNN;
		
		sums_points_D2(n, m, 
			NN, MM, rectNN, rectMM,
			imask_undefined,
			first_x, second_x, third_x,
			first_xx, second_xx,
			first_yy, second_yy,
			first_y, second_y, third_y,
			x_from, y_from);
		
		fault_points_D2(n, m, NN, MM, fault,
			first_x, second_x, third_x,
			first_xx, second_xx,
			first_yy, second_yy,
			first_y, second_y, third_y,
			x_from, y_from);

		mask->write10(j, 
			first_x, second_x, third_x,
			first_xx, second_xx,
			first_yy, second_yy,
			first_y, second_y, third_y);
	}

	mask_solved_undefined = create_bitvec(imask_solved);
	mask_solved_undefined->OR(imask_undefined);
};


REAL matrD2_rect::element_at(size_t i, size_t j, size_t * next_j) const {

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
			*next_j = UINT_MAX;//*next_j = y_from;
		return res;
	}

	if (m > y_to) {
		if (next_j)
			*next_j = UINT_MAX;
		return res;
	}

	n -= x_from;
	m -= y_from;
	size_t local_i = n + m*rectNN;

	size_t next_j_dx2  = UINT_MAX;
	size_t next_j_dxdy = UINT_MAX;
	size_t next_j_dy2  = UINT_MAX;
	
	bool b[10];

	mask->get10(local_i, b);

	return matrator_serve(i, j, b, next_j);

};

REAL matrD2_rect::at(size_t i, size_t j, size_t * next_j) const {

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
			*next_j = UINT_MAX;//*next_j = y_from;
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
			
			if (j+2*NN < i) {
				*next_j = i-2*NN;
				return REAL(0);
			}
			
			if (j+NN+1 < i) {
				*next_j = i-NN-1;
				return REAL(0);
			}
			
			if (j+NN < i) {
				*next_j = i-NN;
				return REAL(0);
			}
			
			if (j+2 < i) {
				*next_j = i-2;
				return REAL(0);
			}
			
			if (j+1 < i) {
				*next_j = i-1;
				return REAL(0);
			}
			
			if (j < i) {
				*next_j = i;
				return REAL(0);
			}
			
			if (j < i+NN-1) {
				*next_j = i+NN-1;
				return REAL(0);
			}
			
			if (j < i+NN) {
				*next_j = i+NN;
				return REAL(0);
			}
			
			if (j < i+2*NN) {
				*next_j = i+2*NN;
				return REAL(0);
			}
			
			*next_j = UINT_MAX;
			return REAL(0);
		}
	}

	n -= x_from;
	m -= y_from;

	size_t local_i = n + m*rectNN;

	size_t next_j_dx2  = UINT_MAX;
	size_t next_j_dxdy = UINT_MAX;
	size_t next_j_dy2  = UINT_MAX;

	bool b[10];
		
	mask->get10(local_i, b);

	return matrator_serve(i, j, b, next_j);

};

REAL matrD2_rect::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) {

	if (mask_solved_undefined->get(J))
		return REAL(0);

	size_t n = J % NN;
	size_t m = (J - n)/NN;

	if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
		return REAL(0);
	
	bool b[10];
	size_t local_J = n-x_from + (m-y_from)*rectNN;

	mask->get10(local_J, b);

	REAL res = REAL(0);
	extvec::const_iterator p;

	bool flag = false;

//
//  dxdx
//

	// u_{i,j} - 2 u_{i+1,j} + u_{i+2,j}
	if (FIRST_X) {

		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx4; // 1;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hx4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+2,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx4; // 1;
			else
				assert(0);
		}

	}

	// - 2 u_{i-1,j} + 4 u_{i,j} - 2 u_{i+1,j}
	if (SECOND_X) {
		
		p = b_begin + J - 1 - 1;
		
		flag = incr_ptr(p,J-1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hx4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += 4 * (*p) * _hx4; // 4;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hx4; // -2;
			else
				assert(0);
		}
		
	}

	// u_{i-2,j} - 2 u_{i-1,j} + u_{i,j}
	if (THIRD_X) {

		p = b_begin + J - 2 - 1;
		
		flag = incr_ptr(p,J-2,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx4; // 1;
			else
				assert(0);
		}

		flag = incr_ptr(p,J-1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hx4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx4; // 1;
			else
				assert(0);
		}

	}

//
//  dydy
//

	// u_{i,j} - 2 u_{i,j+1} + u_{i,j+2}
	if (FIRST_Y) {

		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy4; // 1;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+2*NN,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy4; // 1;
			else
				assert(0);
		}

	}
	
	// - 2 u_{i,j-1} + 4 u_{i,j} + - 2 u_{i,j+1}
	if (SECOND_Y) {
		
		p = b_begin + J - NN - 1;
		
		flag = incr_ptr(p,J-NN,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += 4 * (*p) * _hy4; // 4;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hy4; // -2;
			else
				assert(0);
		}

	}

	// u_{i,j-2} - 2 u_{i,j-1} + u_{i,j}
	if (THIRD_Y) {

		p = b_begin + J - 2*NN - 1;
		
		flag = incr_ptr(p,J-2*NN,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy4; // 1;
			else
				assert(0);
		}

		flag = incr_ptr(p,J-NN,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += -2 * (*p) * _hy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy4; // 1;
			else
				assert(0);
		}
		
		
	}

//
//  dxdy
//

	// 2 ( u_{i,j} - u_{i+1,j} - u_{i,j+1} + u_{i+1,j+1} )
	if (FIRST_XX) {

		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN-1);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}
		
	}

	// 2 ( - u_{i-1,j} + u_{i,j} + u_{i-1,j+1} - u_{i,j+1} )
	if (SECOND_XX) {

		p = b_begin + J - 1 - 1;
		
		flag = incr_ptr(p,J-1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN-1,mask_solved_undefined,NN-1);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}
		
	}

	// 2 ( - u_{i,j-1} + u_{i+1,j-1} + u_{i,j} - u_{i+1,j} )
	if (FIRST_YY) {

		p = b_begin + J - NN - 1;
		
		flag = incr_ptr(p,J-NN,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J-NN+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined,NN-1);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}
		
	}

	// 2 ( u_{i-1,j-1} - u_{i,j-1} - u_{i-1,j} + u_{i,j} )
	if (SECOND_YY) {

		p = b_begin + J - NN - 1 - 1;
		
		flag = incr_ptr(p,J-NN-1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J-NN,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J-1,mask_solved_undefined,NN-1);

		if (flag) {
			CHECK_PTR(p)
				res += -(*p) * _hxy4; // -2;
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += (*p) * _hxy4; // 2;
			else
				assert(0);
		}

				
	}

	return res;

};

size_t matrD2_rect::cols() const {
	return N_cols;
};

size_t matrD2_rect::rows() const {
	return N_rows;
};

REAL matrD2_rect::norm() const {
	return matrD2::norm();
};

}; // namespace surfit;

