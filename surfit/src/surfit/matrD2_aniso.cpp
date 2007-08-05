
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
#include "matrD2_aniso.h"
#include "grid_line.h"
#include "bitvec.h"
#include "matrD_incr_ptr.h"

#include <float.h>
#include <assert.h>

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

matrD2_aniso::matrD2_aniso(size_t iN, size_t iNN, 
			   REAL ihx, REAL ihy,
			   const bitvec * imask_solved, 
			   const bitvec * imask_undefined,
			   grid_line * ifault,
			   REAL iangle, REAL iw) { 
	N = iN; 
	NN = iNN;
	MM = N/NN; 
	fault = ifault;
	hx4 = ihx*ihx*ihx*ihx;
	hy4 = ihy*ihy*ihy*ihy;
	_hx4 = (ihy*ihy)/(ihx*ihx);
	_hy4 = (ihx*ihx)/(ihy*ihy);
	_hxy4 = 1;

	angle = iangle;
	w = iw;

	make_mask(imask_solved, imask_undefined);
};

matrD2_aniso::~matrD2_aniso() {
	if (mask)
		mask->release();
	if (mask_solved_undefined)
		mask_solved_undefined->release();
};

void matrD2_aniso::make_mask(const bitvec * imask_solved, const bitvec * imask_undefined) {
	mask = create_bitvec(rows()*10);
	size_t j;
	bool first_x, second_x, third_x;
	bool first_xx, second_xx;
	bool first_yy, second_yy;
	bool first_y, second_y, third_y;

	for (j = 0; j < rows(); j++) {
		first_x = second_x = third_x = true;
		first_xx = second_xx = true;
		first_yy = second_yy = true;
		first_y = second_y = third_y = true;
		
		size_t n = j % NN;
		size_t m = (j - n)/NN;
		
		sums_points_D2(n, m, 
			NN, MM, NN, MM,
			imask_undefined,
			first_x, second_x, third_x,
			first_xx, second_xx,
			first_yy, second_yy,
			first_y, second_y, third_y);
		
		fault_points_D2(n, m, NN, MM, fault,
			first_x, second_x, third_x,
			first_xx, second_xx,
			first_yy, second_yy,
			first_y, second_y, third_y);

		mask->write10(j, 
			first_x, second_x, third_x,
			first_xx, second_xx,
			first_yy, second_yy,
			first_y, second_y, third_y);
	}

	mask_solved_undefined = create_bitvec(imask_solved);
	mask_solved_undefined->OR(imask_undefined);
};

REAL matrD2_aniso::matrator_serve(size_t i, size_t j,
				  bool * b,
				  size_t * next_j) const {

	size_t next_j_dx2  = UINT_MAX;
	size_t next_j_dxdy = UINT_MAX;
	size_t next_j_dy2  = UINT_MAX;

	REAL res = REAL(0);

	if ( (!FIRST_X) && (!SECOND_X) && (!THIRD_X) &&
	     (!FIRST_Y) && (!SECOND_Y) && (!THIRD_Y) &&
	     (!FIRST_XX) && (!SECOND_XX) && 
	     (!FIRST_YY) && (!SECOND_YY) )
	{
		if (next_j) {

			if (j < i-2*NN) {
				*next_j = i-2*NN;
				return REAL(0);
			}
			if (j < i-NN-1) {
				*next_j = i-NN-1;
				return REAL(0);
			}
			if (j < i-NN) {
				*next_j = i-NN;
				return REAL(0);
			}
			if (j < i-NN+1) {
				*next_j = i-NN+1;
				return REAL(0);
			}
			if (j < i-2) {
				*next_j = i-2;
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
			if (j < i+1) {
				*next_j = i+1;
				return REAL(0);
			}
			if (j < i+2) {
				*next_j = i+2;
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
			if (j < i+NN+1) {
				*next_j = i+NN+1;
				return REAL(0);
			}
			if (j < i+2*NN) {
				*next_j = i+2*NN;
				return REAL(0);
			}
			*next_j = UINT_MAX;
			
		}
		return REAL(0);
	}
	
	// u_{i,j} - 2 u_{i+1,j} + u_{i+2,j}
	if (FIRST_X) {
		if (j < i) {
			next_j_dx2 = MIN(i, next_j_dx2);
			goto mark_second_x;
		}

		if (j == i) {
			res += _hx4; // 1;
			next_j_dx2 = MIN(i+1, next_j_dx2);
			goto mark_second_x;
		}	

		if (j == i+1) {
			res += -2 * _hx4; // -2;
			next_j_dx2 = MIN(i+2, next_j_dx2);
			goto mark_second_x;
		}

		if (j == i+2) {
			res += _hx4; // 1;
			next_j_dx2 = MIN(UINT_MAX, next_j_dx2);
			goto mark_second_x;
		}

		next_j_dx2 = MIN(UINT_MAX, next_j_dx2);
	}

mark_second_x:
	
	// - 2 u_{i-1,j} + 4 u_{i,j} - 2 u_{i+1,j}
	if (SECOND_X) {
		
		if (j < i-1) {
			next_j_dx2 = MIN(i-1, next_j_dx2);
			goto mark_third_x;
		}

		if (j == i-1) {
			res += -2 * _hx4; // -2;
			next_j_dx2 = MIN(i, next_j_dx2);
			goto mark_third_x;
		}

		if (j == i) {
			res += 4 * _hx4; // 4;
			next_j_dx2 = MIN(i+1, next_j_dx2);
			goto mark_third_x;
		}

		if (j == i+1) {
			res += -2 * _hx4; // -2;
			next_j_dx2 = MIN(UINT_MAX, next_j_dx2);
			goto mark_third_x;
		}
		
		next_j_dx2 = MIN(UINT_MAX, next_j_dx2);
		
	}

mark_third_x:

	// u_{i-2,j} - 2 u_{i-1,j} + u_{i,j}
	if (THIRD_X) {
		
		if (j < i-2) {
			next_j_dx2 = MIN(i-2, next_j_dx2);
			goto mark_first_y;
		}

		if (j == i-2) {
			res += _hx4; // 1;
			next_j_dx2 = MIN(i-1, next_j_dx2);
			goto mark_first_y;
		}

		if (j == i-1) {
			res += -2 * _hx4; // -2;
			next_j_dx2 = MIN(i, next_j_dx2);
			goto mark_first_y;
		}

		if (j == i) {
			res += _hx4; // 1;
			next_j_dx2 = MIN(UINT_MAX, next_j_dx2);
			goto mark_first_y;
		}
		
		next_j_dx2 = MIN(UINT_MAX, next_j_dx2);
		
	}

mark_first_y:

	// u_{i,j} - 2 u_{i,j+1} + u_{i,j+2}
	if (FIRST_Y) {
		
		if (j < i) {
			next_j_dy2 = MIN(i, next_j_dy2);
			goto mark_second_y;
		}

		if (j == i) {
			res += _hy4; // 1;
			next_j_dy2 = MIN(i+NN, next_j_dy2);
			goto mark_second_y;
		}

		if (j < i+NN) {
			next_j_dy2 = MIN(i+NN, next_j_dy2);
			goto mark_second_y;
		}

		if (j == i+NN) {
			res += -2 * _hy4; // -2;
			next_j_dy2 = MIN(i+2*NN, next_j_dy2);
			goto mark_second_y;
		}
		
		if (j < i+2*NN) {
			next_j_dy2 = MIN(i+2*NN, next_j_dy2);
			goto mark_second_y;
		}

		if (j == i+2*NN) {
			res += _hy4; // 1;
			next_j_dy2 = MIN(UINT_MAX, next_j_dy2);
			goto mark_second_y;
		}

		next_j_dy2 = MIN(UINT_MAX, next_j_dy2);
			
	}

mark_second_y:

	// - 2 u_{i,j-1} + 4 u_{i,j} - 2 u_{i,j+1}
	if (SECOND_Y) {
	
		if (j < i-NN) {
			next_j_dy2 = MIN(i-NN, next_j_dy2);
			goto mark_third_y;
		}

		if (j == i-NN) {
			res += -2 * _hy4; // -2;
			next_j_dy2 = MIN(i, next_j_dy2);
			goto mark_third_y;
		}

		if (j < i) {
			next_j_dy2 = MIN(i, next_j_dy2);
			goto mark_third_y;
		}

		if (j == i) {
			res += 4 * _hy4; // 4 ;
			next_j_dy2 = MIN(i+NN, next_j_dy2);
			goto mark_third_y;
		}

		if (j < i+NN) {
			next_j_dy2 = MIN(i+NN, next_j_dy2);
			goto mark_third_y;
		}

		if (j == i+NN) {
			res += -2 * _hy4; // -2;
			next_j_dy2 = MIN(UINT_MAX, next_j_dy2);
			goto mark_third_y;
		}

		next_j_dy2 = MIN(UINT_MAX, next_j_dy2);

	}

mark_third_y:

	// u_{i,j-2} - 2 u_{i,j-1} + u_{i,j}
	if (THIRD_Y) {
	
		if (j < i-2*NN) {
			next_j_dy2 = MIN(i-2*NN, next_j_dy2);
			goto mark_first_xx;
		}

		if (j == i-2*NN) {
			res += _hy4; // 1;
			next_j_dy2 = MIN(i-NN, next_j_dy2);
			goto mark_first_xx;
		}

		if (j < i-NN) {
			next_j_dy2 = MIN(i-NN, next_j_dy2);
			goto mark_first_xx;
		}

		if (j == i-NN) {
			res += -2 * _hy4; // -2;
			next_j_dy2 = MIN(i, next_j_dy2);
			goto mark_first_xx;
		}
		
		if (j < i) {
			next_j_dy2 = MIN(i, next_j_dy2);
			goto mark_first_xx;
		}

		if (j == i) {
			res += _hy4; // 1;
			next_j_dy2 = MIN(UINT_MAX, next_j_dy2);
			goto mark_first_xx;
		}
		
		next_j_dy2 = MIN(UINT_MAX, next_j_dy2);
		
	}

mark_first_xx:

	// 2 ( u_{i,j} - u_{i+1,j} - u_{i,j+1} + u_{i+1,j+1} )
	if (FIRST_XX) {

		if (j < i) {
			next_j_dxdy = MIN(i, next_j_dxdy);
			goto mark_second_xx;
		}

		if (j == i) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(i+1, next_j_dxdy);
			goto mark_second_xx;
		}

		if (j == i+1) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(i+NN, next_j_dxdy);
			goto mark_second_xx;
		}
		
		if (j < i+NN) {
			next_j_dxdy = MIN(i+NN, next_j_dxdy);
			goto mark_second_xx;
		}
		
		if (j == i+NN) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(i+NN+1, next_j_dxdy);
			goto mark_second_xx;
		}

		if (j == i+NN+1) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
			goto mark_second_xx;
		}
		
		next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
		
	}

mark_second_xx:

	// 2 ( - u_{i-1,j} + u_{i,j} + u_{i-1,j+1} - u_{i,j+1} )
	if (SECOND_XX) {

		if (j < i-1) {
			next_j_dxdy = MIN(i-1, next_j_dxdy);
			goto mark_first_yy;
		}

		if (j == i-1) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(i, next_j_dxdy);
			goto mark_first_yy;
		}
		
		if (j == i) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(i+NN-1, next_j_dxdy);
			goto mark_first_yy;
		}
		
		if (j < i+NN-1) {
			next_j_dxdy = MIN(i+NN-1, next_j_dxdy);
			goto mark_first_yy;
		}
		
		if (j == i+NN-1) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(i+NN, next_j_dxdy);
			goto mark_first_yy;
		}
		
		if (j == i+NN) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
			goto mark_first_yy;
		}

		next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
				
	}

mark_first_yy:

	// 2 ( - u_{i,j-1} + u_{i+1,j-1} + u_{i,j} - u_{i+1,j} )
	if (FIRST_YY) {

		if (j < i-NN) {
			next_j_dxdy = MIN(i-NN, next_j_dxdy);
			goto mark_second_yy;
		}

		if (j == i-NN) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(i-NN+1, next_j_dxdy);
			goto mark_second_yy;
		}

		if (j == i-NN+1) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(i, next_j_dxdy);
			goto mark_second_yy;
		}
		
		if (j < i) {
			next_j_dxdy = MIN(i, next_j_dxdy);
			goto mark_second_yy;
		}
		
		if (j == i) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(i+1, next_j_dxdy);
			goto mark_second_yy;
		}

		if (j == i+1) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
			goto mark_second_yy;
		}

		next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
				
	}

mark_second_yy:

	// 2 ( u_{i-1,j-1} - u_{i,j-1} - u_{i-1,j} + u_{i,j} )
	if (SECOND_YY) {

		if (j < i-NN-1) {
			next_j_dxdy = MIN(i-NN-1, next_j_dxdy);
			goto exit;
		}

		if (j == i-NN-1) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(i-NN, next_j_dxdy);
			goto exit;
		}
		
		if (j == i-NN) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(i-1, next_j_dxdy);
			goto exit;
		}
		
		if (j < i-1) {
			next_j_dxdy = MIN(i-1, next_j_dxdy);
			goto exit;
		}

		if (j == i-1) {
			res += -_hxy4; // -2;
			next_j_dxdy = MIN(i, next_j_dxdy);
			goto exit;
		}

		if (j == i) {
			res += _hxy4; // 2;
			next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
			goto exit;
		}
		
		next_j_dxdy = MIN(UINT_MAX, next_j_dxdy);
				
	}

exit:

	if (next_j) 
	{
		*next_j = MIN(next_j_dx2, next_j_dy2);
		*next_j = MIN(*next_j, next_j_dxdy);
	}

	return res;

};
	
REAL matrD2_aniso::element_at(size_t i, size_t j, size_t * next_j) const {

		
	bool b[10];

	mask->get10(i, b);
	
	return matrator_serve(i,j, b,
			      next_j);
                            	

};

REAL matrD2_aniso::element_at_transposed(size_t i, size_t j, size_t * next_j) const {
	return element_at(i, j, next_j);
};

REAL matrD2_aniso::at(size_t i, size_t j, size_t * next_j) const {

	bool zero = mask_solved_undefined->get(i);
	if (!zero)
		zero = mask_solved_undefined->get(j);
	
	if ( zero ) {
		if (next_j) {
			
			if (j < i-2*NN) {
				*next_j = i-2*NN;
				return REAL(0);
			}
			
			if (j < i-NN-1) {
				*next_j = i-NN-1;
				return REAL(0);
			}
			
			if (j < i-NN) {
				*next_j = i-NN;
				return REAL(0);
			}

			if (j < i-NN+1) {
				*next_j = i-NN+1;
				return REAL(0);
			}
			
			if (j < i-2) {
				*next_j = i-2;
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

			if (j < i+1) {
				*next_j = i+1;
				return REAL(0);
			}

			if (j < i+2) {
				*next_j = i+2;
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

			if (j < i+NN+1) {
				*next_j = i+NN+1;
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

	bool b[10];

	mask->get10(i, b);

	return matrator_serve(i, j, b, next_j);

};

REAL matrD2_aniso::at_transposed(size_t i, size_t j, size_t * next_j) const {
	return at(i, j, next_j);
};

REAL matrD2_aniso::mult_transposed_line(size_t J, const REAL * b_begin, const REAL * b_end) {
	return mult_line(J, b_begin, b_end);
};

REAL matrD2_aniso::mult_line(size_t J, const REAL * b_begin, const REAL * b_end) {

	if (mask_solved_undefined->get(J))
		return REAL(0);

	REAL res = REAL(0);
	const REAL * p;
	bool b[10];
	
	bool flag = false;
	
	mask->get10(J, b);
	
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
	
	// - 2 u_{i,j-1} + 4 u_{i,j} - 2 u_{i,j+1}
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

		flag = incr_ptr(p,J+NN+1,mask_solved_undefined,1);

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

REAL matrD2_aniso::norm() const {
	return 16*REAL(_hx4 + _hy4 + _hxy4);
};

size_t matrD2_aniso::cols() const {
	return N;
};

size_t matrD2_aniso::rows() const {
	return N;
};

void matrD2_aniso::skip(size_t i, size_t j) {
	mask_solved_undefined->set_true(i + j*NN);
};

}; // namespace surfit;

