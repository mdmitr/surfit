
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

#include "matrD1_aniso.h"
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

#define FIRST_X		(b[0])
#define SECOND_X	(b[1])
#define FIRST_Y		(b[2])
#define SECOND_Y	(b[3])
#define FIRST_XY	(FIRST_X && FIRST_Y)	
#define SECOND_XY	(FIRST_X && SECOND_Y)
#define SECOND_YX	(FIRST_Y && SECOND_X)

namespace surfit {

matrD1_aniso::matrD1_aniso(size_t iN, size_t iNN, 
			   REAL ihx, REAL ihy,
			   const bitvec * imask_solved,
			   const bitvec * imask_undefined,
			   grid_line * ifault,
			   REAL iangle, REAL iw) 
{ 
	N = iN; 
	NN = iNN;
	MM = N/NN; 
	fault = ifault;
	hx2 = ihx*ihx;
	hy2 = ihy*ihy;
	_hx2 = ihy/ihx;
	_hy2 = ihx/ihy;
	angle = iangle;
	w = iw;
	mask = NULL;
	make_mask(imask_solved, imask_undefined);

	REAL cos_a = cos(angle/REAL(180)*3.1415926);
	REAL sin_a = sin(angle/REAL(180)*3.1415926);

	wmxx = (w*w*cos_a*cos_a)/(ihx*ihx);
	wmxy = (w*w*cos_a*sin_a)/(ihx*ihy);
	wmyy = (w*w*sin_a*sin_a)/(ihy*ihy);
	mxx = (sin_a*sin_a)/(ihx*ihx);
	mxy = (cos_a*sin_a)/(ihx*ihy);
	myy = (cos_a*cos_a)/(ihy*ihy);
};

matrD1_aniso::~matrD1_aniso() {
	if (mask)
		mask->release();
	if (mask_solved_undefined)
		mask_solved_undefined->release();
};

void matrD1_aniso::make_mask(const bitvec * imask_solved, const bitvec * imask_undefined) {
	mask = create_bitvec(rows()*4);
	size_t j;
	bool first_x, second_x, first_y, second_y;
	for (j = 0; j < rows(); j++) {
		first_x = true;
		second_x = true;
		first_y = true;
		second_y = true;
		size_t n = j % NN;
		size_t m = (j - n)/NN;

		sums_points_D1(n, m, 
			NN, MM, NN, MM,
			imask_undefined,
			first_x, second_x, 
			first_y, second_y);
		
		fault_points_D1(n, m, NN, MM, fault,
				first_x, second_x, first_y, second_y);

		mask->write4(j, first_x, second_x, first_y, second_y);
	}

	mask_solved_undefined = create_bitvec(imask_solved);
	mask_solved_undefined->OR(imask_undefined);

};

REAL matrD1_aniso::matrator_serve(size_t i, size_t j, bool * b, size_t * next_j) const {

	REAL res = REAL(0);

	size_t next_j_dx = UINT_MAX;
	size_t next_j_dy = UINT_MAX;

	if ( (!FIRST_X) && (!SECOND_X) && (!FIRST_Y) && (!SECOND_Y) &&
	     (!FIRST_XY) && (!SECOND_XY) && (!SECOND_YX) ) 
	{
		if (next_j) {
			
			if (j < i-NN) {
				*next_j = i-NN;
				return REAL(0);
			}

			if (j < i-NN+1) {
				*next_j = i-NN+1;
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

			if (j < i+NN-1) {
				*next_j = i+NN-1;
				return REAL(0);
			}
			
			if (j < i+NN) {
				*next_j = i+NN;
				return REAL(0);
			}

			*next_j = UINT_MAX;
						
		}
		return REAL(0);
	}
	
	//  -(wmxx + mxx) * (u_{i+1,j} - u_{i,j}) 
	if (FIRST_X) {
		if (j < i) {
			next_j_dx = MIN(i, next_j_dx);
			goto mark_second_x;
		}

		if (j == i) {
			res += (wmxx + mxx); 
			next_j_dx = MIN(i+1, next_j_dx);
			goto mark_second_x;
		}

		if (j == i+1) {
			res += -(wmxx + mxx);
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_second_x;
		}

	}
	
mark_second_x:

	// (wmxx + mxx) * ( u_{i,j} - u_{i-1,j} ) 
	if (SECOND_X) {

		if (j < i-1) {
			next_j_dx = MIN(i-1, next_j_dx);
			goto mark_first_y;
		}

		if (j == i-1) {
			res += -(wmxx + mxx);
			next_j_dx = MIN(i, next_j_dx);
			goto mark_first_y;
		}

		if (j == i) {
			res += (wmxx + mxx);
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_first_y;
		}
		
	}

mark_first_y:

	// -(wmyy + myy) * ( u_{i,j+1} - u_{i,j} )
	if (FIRST_Y) {

		if (j < i) {
			next_j_dy = MIN(i, next_j_dy);
			goto mark_second_y;
		}

		if (j == i) {
			res += (wmyy + myy);
			next_j_dy = MIN(i+NN, next_j_dy);
			goto mark_second_y;
		}

		if (j < i+NN) {
			next_j_dy = MIN(i+NN, next_j_dy);
			goto mark_second_y;
		}

		if (j == i+NN) {
			res += -(wmyy + myy);
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto mark_second_y;
		}

	}

mark_second_y:

	// (wmyy + myy) * ( u_{i,j} - u_{i,j-1} )
	if (SECOND_Y) {

		if (j < i-NN) {
			next_j_dy = MIN(i-NN, next_j_dy);
			goto mark_first_xy;
		}

		if (j == i-NN) {
			res += -(wmyy + myy);
			next_j_dy = MIN(i, next_j_dy);
			goto mark_first_xy;
		}

		if (j < i) {
			next_j_dy = MIN(i, next_j_dy);
			goto mark_first_xy;
		}

		if (j == i) {
			res += (wmyy + myy);
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto mark_first_xy;
		}
	}

mark_first_xy:

	// (-wmxy + mxy) * ( -2 u_{i,j} + u_{i+1,j} + u_{i,j+1} )
	if (FIRST_XY) {

		if (j < i) {
			next_j_dx = MIN(i, next_j_dx);
			goto mark_second_xy;
		}

		if (j == i) {
			res += -2*(-wmxy + mxy);
			next_j_dx = MIN(i+1, next_j_dx);
			goto mark_second_xy;
		}

		if (j == i+1) {
			res += (-wmxy + mxy);
			next_j_dx = MIN(i+NN, next_j_dx);
			goto mark_second_xy;
		}

		if (j < i+NN) {
			next_j_dx = MIN(i+NN, next_j_dx);
			goto mark_second_xy;
		}

		if (j == i+NN) {
			res += (-wmxy + mxy);
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_second_xy;
		}

	}

mark_second_xy:

	// (wmxy - mxy) * ( u_{i+1,j-1} - u_{i,j-1} )
	if (SECOND_XY) {

		if (j < i-NN) {
			next_j_dy = MIN(i-NN, next_j_dy);
			goto mark_second_yx;
		}

		if (j == i-NN) {
			res += -wmxy + mxy;
			next_j_dy = MIN(i-NN+1, next_j_dy);
			goto mark_second_yx;
		}

		if (j == i-NN+1) {
			res += wmxy - mxy;
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto mark_second_yx;
		}

	}

mark_second_yx:

	// (wmxy - mxy) * ( u_{i-1,j+1} - u_{i-1,j} )
	if (SECOND_YX) {

		if (j < i-1) {
			next_j_dy = MIN(i-1, next_j_dy);
			goto exit;
		}

		if (j == i-1) {
			res += -wmxy + mxy;
			next_j_dy = MIN(i+NN-1, next_j_dy);
			goto exit;
		}

		if (j < i+NN-1) {
			next_j_dy = MIN(i+NN-1, next_j_dy);
			goto exit;
		}

		if (j == i+NN-1) {
			res += wmxy - mxy;
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto exit;
		}

	}

	goto exit;

exit:

	if (next_j) {
		*next_j = MIN(next_j_dx, next_j_dy);
	}

	return res;	
};

REAL matrD1_aniso::element_at(size_t i, size_t j, size_t * next_j) const {

	bool b[4];

	mask->get4(i, b);

	return matrator_serve(i, j, b, next_j);
	
};

REAL matrD1_aniso::element_at_transposed(size_t i, size_t j, size_t * next_j) const {
	return element_at(i, j, next_j);
};

REAL matrD1_aniso::at(size_t i, size_t j, size_t * next_j) const {

	bool zero = mask_solved_undefined->get(i);
	if (!zero)
		zero = mask_solved_undefined->get(j);

	if ( zero ) {
		if (next_j) {
			
			if (j < i-NN) {
				*next_j = i-NN;
				return REAL(0);
			}

			if (j < i-NN+1) {
				*next_j = i-NN+1;
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

			if (j < i+NN-1) {
				*next_j = i+NN-1;
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

	bool b[4];

	mask->get4(i, b);

	return matrator_serve(i, j, b, next_j);
	
};

REAL matrD1_aniso::at_transposed(size_t i, size_t j, size_t * next_j) const {
	return at(i, j, next_j);
};

REAL matrD1_aniso::mult_transposed_line(size_t J, const REAL * b_begin, const REAL * b_end) {
	return mult_line(J, b_begin, b_end);
};

REAL matrD1_aniso::mult_line(size_t J, const REAL * b_begin, const REAL * b_end) {

	if (mask_solved_undefined->get(J))
		return REAL(0);

	size_t n = J % NN;
	size_t m = (J - n)/NN;

	
	REAL res = REAL(0);
	const REAL * p;

	bool flag = false;
	bool b[4];

	mask->get4(J, b);

	// -(wmxx + mxx) * ( u_{i+1,j} - u_{i,j} ) 
	if (FIRST_X) {
		
		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * (wmxx + mxx);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -(wmxx + mxx);
			else
				assert(0);
		}

	}

	// (wmxx + mxx) * ( u_{i,j} - u_{i-1,j} )
	if (SECOND_X) {

		p = b_begin + J - 1 - 1;

		flag = incr_ptr(p,J-1,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -(wmxx + mxx);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * (wmxx + mxx);
			else 
				assert(0);
		}
		
	}

	// -(wmyy + myy) * ( u_{i,j+1} - u_{i,j} )
	if (FIRST_Y) {

		p = b_begin + J - 1;

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (wmyy + myy);
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -(wmyy + myy);
			else
				assert(0);
		}

	}

	// (wmyy + myy) * ( u_{i,j} - u_{i,j-1} )
	if (SECOND_Y) {

		p = b_begin + J - NN - 1;

		flag = incr_ptr(p,J-NN,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -(wmyy + myy);
			else
				assert(0);
		}

		flag = incr_ptr(p,J,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (wmyy + myy);
			else
				assert(0);
		}
		
	}

	// ( -wmxy + mxy ) * ( -2 u_{i,j} + u_{i+1,j} + u_{i,j+1} )
	if (FIRST_XY) {

		p = b_begin + J - 1;

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (2*(wmxy-mxy));
			else
				assert(0);
		}

		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (-wmxy + mxy);
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN-1);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (-wmxy + mxy);
			else
				assert(0);
		}

	}

	// ( wmxy - mxy ) * ( u_{i+1,j-1} - u_{i,j-1} )
	if (SECOND_XY) {

		p = b_begin + J - NN - 1;

		flag = incr_ptr(p,J-NN,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -(wmxy - mxy);
			else
				assert(0);
		}

		flag = incr_ptr(p,J-NN+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (wmxy - mxy);
			else
				assert(0);
		}

	}

	// (wmxy - mxy) * ( u_{i-1,j+1} - u_{i-1,j} )
	if (SECOND_YX) {

		p = b_begin + J - 1 - 1;

		flag = incr_ptr(p,J-1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -(wmxy - mxy);
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN-1,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (wmxy - mxy);
			else
				assert(0);
		}

	}

	return res;
	
};

REAL matrD1_aniso::norm() const {
	return REAL(2 * (2*_hx2 + 2*_hy2));
};

size_t matrD1_aniso::cols() const {
	return N;
};

size_t matrD1_aniso::rows() const {
	return N;
};

void matrD1_aniso::skip(size_t i, size_t j) {
	mask_solved_undefined->set_true(i + j*NN);
};

}; // namespace surfit;


