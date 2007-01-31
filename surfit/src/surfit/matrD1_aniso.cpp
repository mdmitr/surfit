
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

#ifdef DEBUG
	#ifdef XXL
		#define CHECK_PTR(p) if(true)
	#else
		#define CHECK_PTR(p) if((p >= b_begin) && (p < b_end))
	#endif
#else
	#define CHECK_PTR(p) if(true)
#endif

#define FIRST_X		(b[0])
#define SECOND_X	(b[1])
#define FIRST_Y		(b[2])
#define SECOND_Y	(b[3])
#define FIRST_XY	(b[4])	
#define FIRST_YX	(b[5])
#define SECOND_XY	(b[6])
#define SECOND_YX	(b[7])

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
	
	mask = create_bitvec(rows()*8);
	size_t j;
	bool first_x, second_x, first_y, second_y;
	bool first_xy, first_yx, second_xy, second_yx;
	
	for (j = 0; j < rows(); j++) {

		first_x = true;
		second_x = true;
		first_y = true;
		second_y = true;
		first_xy = true;
		first_yx = true;
		second_xy = true;
		second_yx = true;
		size_t n = j % NN;
		size_t m = (j - n)/NN;

		sums_points_D1_aniso(n, m, 
				     NN, MM, NN, MM,
				     imask_undefined,
				     first_x, second_x, 
				     first_y, second_y,
				     first_xy, first_yx,
				     second_xy, second_yx);
		
		fault_points_D1_aniso(n, m, NN, MM, fault,
				      first_x, second_x, first_y, second_y,
				      first_xy, first_yx, second_xy, second_yx);

		mask->write8(j, first_x, second_x, first_y, second_y,
			        first_xy, first_yx, second_xy, second_yx);
	}

	mask_solved_undefined = create_bitvec(imask_solved);
	mask_solved_undefined->OR(imask_undefined);

};

REAL matrD1_aniso::matrator_serve(size_t i, size_t j, bool * b, size_t * next_j) const {

	REAL res = REAL(0);

	size_t next_j_dx = UINT_MAX;
	size_t next_j_dy = UINT_MAX;

	if ( (!FIRST_X) && (!SECOND_X) && (!FIRST_Y) && (!SECOND_Y) &&
	     (!FIRST_XY) && (!FIRST_YX) && (!SECOND_XY) && (!SECOND_YX) ) 
	{
		if (next_j) {
			
			if (j+NN < i) {
				*next_j = i-NN;
				return REAL(0);
			}

			if (j+NN-1 < i) {
				*next_j = i-NN+1;
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
	
	// ( - wmxx - mxx ) * (u_{i+1,j} - u_{i,j}) 
	if (FIRST_X) {
		if (j < i) {
			next_j_dx = MIN(i, next_j_dx);
			goto mark_second_x;
		}

		if (j == i) {
			res += -( - wmxx - mxx ); 
			next_j_dx = MIN(i+1, next_j_dx);
			goto mark_second_x;
		}

		if (j == i+1) {
			res += ( - wmxx - mxx );
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_second_x;
		}

	}
	
mark_second_x:

	// ( wmxx + mxx ) * ( u_{i,j} - u_{i-1,j} ) 
	if (SECOND_X) {

		if (j+1 < i) {
			next_j_dx = MIN(i-1, next_j_dx);
			goto mark_first_y;
		}

		if (j+1 == i) {
			res += -( wmxx + mxx );
			next_j_dx = MIN(i, next_j_dx);
			goto mark_first_y;
		}

		if (j == i) {
			res += ( wmxx + mxx );
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_first_y;
		}
		
	}

mark_first_y:

	// ( - wmyy - myy ) * ( u_{i,j+1} - u_{i,j} )
	if (FIRST_Y) {

		if (j < i) {
			next_j_dy = MIN(i, next_j_dy);
			goto mark_second_y;
		}

		if (j == i) {
			res += -( - wmyy - myy );
			next_j_dy = MIN(i+NN, next_j_dy);
			goto mark_second_y;
		}

		if (j < i+NN) {
			next_j_dy = MIN(i+NN, next_j_dy);
			goto mark_second_y;
		}

		if (j == i+NN) {
			res += ( - wmyy - myy );
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto mark_second_y;
		}

	}

mark_second_y:

	// ( wmyy + myy ) * ( u_{i,j} - u_{i,j-1} )
	if (SECOND_Y) {

		if (j+NN < i) {
			next_j_dy = MIN(i-NN, next_j_dy);
			goto mark_first_xy;
		}

		if (j+NN == i) {
			res += -( wmyy + myy );
			next_j_dy = MIN(i, next_j_dy);
			goto mark_first_xy;
		}

		if (j < i) {
			next_j_dy = MIN(i, next_j_dy);
			goto mark_first_xy;
		}

		if (j == i) {
			res += ( wmyy + myy );
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto mark_first_xy;
		}
	}

mark_first_xy:

	// ( - wmxy + mxy ) * ( u_{i+1,j} - u_{i,j} )
	if (FIRST_XY) {

		if (j < i) {
			next_j_dx = MIN(i, next_j_dx);
			goto mark_first_yx;
		}

		if (j == i) {
			res += -( - wmxy + mxy );
			next_j_dx = MIN(i+1, next_j_dx);
			goto mark_first_yx;
		}

		if (j == i+1) {
			res += ( - wmxy + mxy );
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_first_yx;
		}

	}

mark_first_yx:

	// ( - wmxy + mxy) * ( u_{i,j+1} - u_{i,j} )
	if (FIRST_YX) {

		if (j < i) {
			next_j_dx = MIN(i, next_j_dx);
			goto mark_second_xy;
		}

		if (j == i) {
			res += -( - wmxy + mxy);
			next_j_dx = MIN(i+NN, next_j_dx);
			goto mark_second_xy;
		}
		
		if (j < i+NN) {
			next_j_dx = MIN(i+NN, next_j_dx);
			goto mark_second_xy;
		}

		if (j == i+NN) {
			res += ( - wmxy + mxy);
			next_j_dx = MIN(UINT_MAX, next_j_dx);
			goto mark_second_xy;
		}

	}

mark_second_xy:

	// ( wmxy - mxy ) * ( u_{i+1,j-1} - u_{i,j-1} )
	if (SECOND_XY) {

		if (j+NN < i) {
			next_j_dy = MIN(i-NN, next_j_dy);
			goto mark_second_yx;
		}

		if (j+NN == i) {
			res += -( wmxy - mxy );
			next_j_dy = MIN(i-NN+1, next_j_dy);
			goto mark_second_yx;
		}

		if (j+NN-1 == i) {
			res += ( wmxy - mxy );
			next_j_dy = MIN(UINT_MAX, next_j_dy);
			goto mark_second_yx;
		}

	}

mark_second_yx:

	// ( wmxy - mxy ) * ( u_{i-1,j+1} - u_{i-1,j} )
	if (SECOND_YX) {

		if (j+1 < i) {
			next_j_dy = MIN(i-1, next_j_dy);
			goto exit;
		}

		if (j+1 == i) {
			res += -( wmxy - mxy );
			next_j_dy = MIN(i+NN-1, next_j_dy);
			goto exit;
		}

		if (j < i+NN-1) {
			next_j_dy = MIN(i+NN-1, next_j_dy);
			goto exit;
		}

		if (j == i+NN-1) {
			res += ( wmxy - mxy );
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

	bool b[8];

	mask->get8(i, b);

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
			
			if (j+NN < i) {
				*next_j = i-NN;
				return REAL(0);
			}

			if (j+NN-1 < i) {
				*next_j = i-NN+1;
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

	bool b[8];

	mask->get8(i, b);

	return matrator_serve(i, j, b, next_j);
	
};

REAL matrD1_aniso::at_transposed(size_t i, size_t j, size_t * next_j) const {
	return at(i, j, next_j);
};

REAL matrD1_aniso::mult_transposed_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) {
	return mult_line(J, b_begin, b_end);
};

REAL matrD1_aniso::mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end) {

	if (mask_solved_undefined->get(J))
		return REAL(0);

	size_t n = J % NN;
	size_t m = (J - n)/NN;

	
	REAL res = REAL(0);
	extvec::const_iterator p;

	bool flag = false;
	bool b[8];

	mask->get8(J, b);

	// (- wmxx - mxx) * ( u_{i+1,j} - u_{i,j} ) 
	if (FIRST_X) {
		
		p = b_begin + J - 1;
		
		flag = incr_ptr(p,J,mask_solved_undefined);
		
		if (flag) {
			CHECK_PTR(p)
				res += *p * -(- wmxx - mxx);
			else
				assert(0);
		}
		
		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * (- wmxx - mxx);
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

	// ( - wmyy - myy ) * ( u_{i,j+1} - u_{i,j} )
	if (FIRST_Y) {

		p = b_begin + J - 1;

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -( - wmyy - myy );
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * ( - wmyy - myy );
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

	// ( - wmxy + mxy ) * ( u_{i+1,j} - u_{i,j} )
	if (FIRST_XY) {

		p = b_begin + J - 1;

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -( - wmxy + mxy );
			else
				assert(0);
		}

		flag = incr_ptr(p,J+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * ( - wmxy + mxy);
			else
				assert(0);
		}

	}

	// ( - wmxy + mxy ) * ( u_{i,j+1} - u_{i,j}  )
	if (FIRST_YX) {

		p = b_begin + J - 1;

		flag = incr_ptr(p,J,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -( - wmxy + mxy );
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * ( - wmxy + mxy );
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
				res += *p * -( wmxy - mxy );
			else
				assert(0);
		}

		flag = incr_ptr(p,J-NN+1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * ( wmxy - mxy );
			else
				assert(0);
		}

	}

	// ( wmxy - mxy ) * ( u_{i-1,j+1} - u_{i-1,j} )
	if (SECOND_YX) {

		p = b_begin + J - 1 - 1;

		flag = incr_ptr(p,J-1,mask_solved_undefined);

		if (flag) {
			CHECK_PTR(p)
				res += *p * -( wmxy - mxy );
			else
				assert(0);
		}

		flag = incr_ptr(p,J+NN-1,mask_solved_undefined,NN);

		if (flag) {
			CHECK_PTR(p)
				res += *p * ( wmxy - mxy );
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


