
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
#define FIRST_Y		b[2]
#define SECOND_Y	b[3]

namespace surfit {

matrD1::matrD1(size_t iN, size_t iNN, 
	       REAL ihx, REAL ihy,
	       const bitvec * imask_solved,
	       const bitvec * imask_undefined,
	       grid_line * ifault) { 
	N = iN; 
	NN = iNN;
	MM = N/NN; 
	fault = ifault;
	hx2 = ihx*ihx;
	hy2 = ihy*ihy;
	_hx2 = ihy/ihx;
	_hy2 = ihx/ihy;
	mask = NULL;
	make_mask(imask_solved, imask_undefined);
};

matrD1::~matrD1() {
	if (mask)
		mask->release();
	if (mask_solved_undefined)
		mask_solved_undefined->release();
};

void matrD1::make_mask(const bitvec * imask_solved, const bitvec * imask_undefined) {
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

REAL matrD1::matrator_serve(size_t i, size_t j, bool * b, size_t * next_j) const {

	REAL res = REAL(0);

	size_t next_j_dx = UINT_MAX;
	size_t next_j_dy = UINT_MAX;

	
	if ( (!FIRST_X) && (!SECOND_X) &&
	     (!FIRST_Y) && (!SECOND_Y) )
	{
		if (next_j) {
			
			if (j+NN < i) {
				*next_j = i-NN;
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

			if (j < i+1) {
				*next_j = i+1;
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

	// u_{i,j} - u_{i+1,j}
	if (FIRST_X) {
		if (j < i) {
			next_j_dx = MIN(i, next_j_dx);
			goto mark_second_x;
		}

		if (j == i) {
			res += _hx2; // 1
			next_j_dx = MIN(i+1, next_j_dx);
			goto mark_second_x;
		}

		if (j == i+1) {
			res += -_hx2; // -1
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_second_x;
		}

	}
	
mark_second_x:

	// u_{i-1,j} - u_{i,j}
	if (SECOND_X) {

		if (j+1 < i) {
			next_j_dx = MIN(i-1, next_j_dx);
			goto mark_first_y;
		}

		if (j+1 == i) {
			res += -_hx2; // -1;
			next_j_dx = MIN(i, next_j_dx);
			goto mark_first_y;
		}
		
		if (i == j) {
			res += _hx2; // 1;
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_first_y;
		}
		
	}

mark_first_y:

	// u_{i,j} - u_{i,j+1}
	if (FIRST_Y) {

		if (j < i) {
			next_j_dy = MIN(i, next_j_dy);
			goto mark_second_y;
		}

		if (j == i) {
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
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto mark_second_y;
		}

	}

mark_second_y:

	// u_{i,j-1} - u_{i,j}
	if (SECOND_Y) {
		
		if (j+NN < i) {
			next_j_dy = MIN(i-NN, next_j_dy);
			goto exit;
		}

		if (j+NN == i) {
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
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto exit;
		}
										
	}

exit:

	if (next_j) {
		*next_j = MIN(next_j_dx, next_j_dy);
	}

	return res;	
};

REAL matrD1::element_at(size_t i, size_t j, size_t * next_j) const {

	bool b[4];

	mask->get4(i, b);

	return matrator_serve(i, j, b, next_j);
	
};

REAL matrD1::at(size_t i, size_t j, size_t * next_j) const {

	bool zero = mask_solved_undefined->get(i);
	if (!zero)
		zero = mask_solved_undefined->get(j);

	if ( zero ) {
		if (next_j) {
			
			if (j+NN < i) {
				*next_j = i-NN;
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

			if (j < i+1) {
				*next_j = i+1;
				return REAL(0);
			}
			
			if (j < i+NN) {
				*next_j = i+NN;
				return REAL(0);
			}

			*next_j = UINT_MAX;
			return REAL(0);
			
		}

		return REAL(0);
	}

	bool b[4];

	mask->get4(i, b);

	return matrator_serve(i, j, b, next_j);
	
};

REAL matrD1::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) {

	if (mask_solved_undefined->get(J))
		return REAL(0);

	size_t n = J % NN;
	size_t m = (J - n)/NN;

	
	REAL res = REAL(0);
	extvec::const_iterator p;

	bool flag = false;
	bool b[4];

	mask->get4(J, b);

	// u_{i,j} - u_{i+1,j}
	if (FIRST_X) {
		
		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hx2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+1,mask_solved_undefined);

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

		flag = incr_ptr(p,J-1,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hx2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved_undefined);
		
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

		flag = incr_ptr(p,J,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN);
		
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

		flag = incr_ptr(p,J-NN,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -_hy2; // (-1);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J,mask_solved_undefined,NN);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * _hy2; // 1;
			else 
				assert(0);
		}

	}

	return res;
	
};

REAL matrD1::norm() const {
	return REAL(2 * (2*_hx2 + 2*_hy2));
};

size_t matrD1::cols() const {
	return N;
};

size_t matrD1::rows() const {
	return N;
};

void sums_points_D1(size_t i, size_t j, 
		    size_t NN, size_t MM, 
		    size_t local_NN, size_t local_MM,
		    const bitvec * mask_undefined,
		    bool & first_x, bool & second_x,
		    bool & first_y, bool & second_y,
		    size_t offset_x, size_t offset_y) {

	size_t J = (i+offset_x) + (j+offset_y)*NN;

	// first_x
	if (first_x)
	if ( (i >= 0) && (i+1 < local_NN) ) { // i = 0 ... N-2
		
		if ( mask_undefined->get(J) || 
		     mask_undefined->get(J+1) )
			first_x = false;
		
	} else {
		first_x = false;
	}

	// second_x
	if (second_x)
	if ( (i > 0) && (i < local_NN) ) { // i = 1 .. N-1
		
		if ( mask_undefined->get(J-1) || 
		     mask_undefined->get(J) )
			second_x = false;
		
	} else {
		second_x = false;
	}
	
	// first_y
	if (first_y)
	if ( (j >= 0) && (j+1 < local_MM) ) {  // j = 0 ... M-2
		
		if ( mask_undefined->get(J) || 
		     mask_undefined->get(J+NN) ) 
			first_y = false;
		
	} else {
		first_y = false;
	}
	
	// second_y
	if (second_y)
	if ( (j > 0) && (j < local_MM) ) { // j = 1 ... M-1
		
		if ( mask_undefined->get(J-NN) || 
		     mask_undefined->get(J) )
			second_y = false;
		
	} else {
		second_y = false;
	}
	
	return;

};


}; // namespace surfit;


