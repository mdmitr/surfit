
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
#ifndef __surfit_bitvec_alg__
#define __surfit_bitvec_alg__

#include "bitvec.h"

namespace surfit {

inline
bool incr_ptr(const REAL *& p, size_t i, 
              const bitvec * mask_solved,
	      const bitvec * mask_undefined,
	      size_t incr = 1) 
{
	p += incr;
	
	if (mask_solved->get(i))
		return false;

	if (mask_undefined->get(i))
		return false;
	
	return true;
};

inline
bool incr_ptr(const REAL *& p, size_t i, 
              const bitvec * mask_solved_undefined,
	      size_t incr = 1) 
{
	p += incr;
	
	if (mask_solved_undefined->get(i))
		return false;
	
	return true;
};

inline
bool incr_ptr(const REAL *& p, size_t i, 
              const bitvec * mask_solved,
	      const bitvec * mask_undefined,
	      size_t x_from, size_t x_to, size_t y_from, size_t y_to, size_t NN,
	      size_t incr = 1)
{
	p += incr;
	
	size_t n = i % NN;
	size_t m = (i - n)/NN;
	
	if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
		return false;
	
	if (mask_solved->get(i))
		return false;

	if (mask_undefined->get(i))
		return false;
	
	return true;
};

inline
bool incr_ptr(const REAL *& p, size_t i, 
              const bitvec * mask_solved_undefined,
	      size_t x_from, size_t x_to, size_t y_from, size_t y_to, size_t NN,
	      size_t incr = 1)
{
	p += incr;
	
	size_t n = i % NN;
	size_t m = (i - n)/NN;
	
	if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
		return false;
	
	if (mask_solved_undefined->get(i))
		return false;

	return true;
};

inline
bool incr_ptr(const REAL *& p, size_t i, 
              const bitvec * mask_solved,
	      const bitvec * mask_undefined,
	      size_t from, size_t to,
	      size_t incr = 1)
{
	p += incr;
	
	if ( (i < from) || (i > to) )
		return false;
	
	if (mask_solved->get(i))
		return false;

	if (mask_undefined->get(i))
		return false;
	
	return true;
};

inline
void sums_points_D1(size_t i, size_t j, 
		    size_t NN, size_t MM, 
		    size_t local_NN, size_t local_MM,
		    const bitvec * mask_undefined,
		    bool & first_x, bool & second_x,
		    bool & first_y, bool & second_y,
		    size_t offset_x = 0, size_t offset_y = 0) {

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

inline
void sums_points_D1_(size_t i, size_t j, 
		     size_t NN, size_t MM, 
		     size_t local_NN, size_t local_MM,
		     const bitvec * mask_solved,
		     bool & first_x, bool & second_x,
		     bool & first_y, bool & second_y,
		     int offset_x = 0, int offset_y = 0) {

	size_t J = (i+offset_x) + (j+offset_y)*NN;

	// first_x
	if (first_x)
	if ( (i >= 0) && (i+1 < local_NN) ) { // i = 0 ... N-2
		
		if ( !mask_solved->get(J) || 
			 !mask_solved->get(J+1) )
			first_x = false;
		
	} else {
		first_x = false;
	}

	// second_x
	if (second_x)
	if ( (i > 0) && (i < local_NN) ) { // i = 1 .. N-1
		
		if ( !mask_solved->get(J-1) || 
			 !mask_solved->get(J) )
		    second_x = false;
		
	} else {
		second_x = false;
	}
	
	// first_y
	if (first_y)
	if ( (j >= 0) && (j+1 < local_MM) ) { // j = 0 ... M-2
		
		if ( !mask_solved->get(J) || 
			 !mask_solved->get(J+NN) ) 
		    first_y = false;
		
	} else {
		first_y = false;
	}
	
	// second_y
	if (second_y)
	if ( (j > 0) && (j < local_MM) ) { // j = 1 ... M-1
		
		if ( !mask_solved->get(J-NN) || 
			 !mask_solved->get(J) )
			second_y = false;
		
	} else {
		second_y = false;
	}
	
	return;

};

inline
void sums_points_D2(size_t i, size_t j, 
		    size_t NN, size_t MM,
		    size_t local_NN, size_t local_MM,
		    const bitvec * mask_undefined,
		    bool & first_x,  bool & second_x, bool & third_x,
		    bool & first_xx, bool & second_xx,
		    bool & first_yy, bool & second_yy,
		    bool & first_y,  bool & second_y, bool & third_y,
		    size_t offset_x = 0, size_t offset_y = 0) {

	size_t J = (i+offset_x) + (j+offset_y)*NN;

	// first_x
	if ( (i >= 0) && (i+2 < local_NN) ) { // i = 0 ... N-3
		
		if ( mask_undefined->get(J)   || 
			 mask_undefined->get(J+1) ||
			 mask_undefined->get(J+2) )
			first_x = false;
		
	} else {
		first_x = false;
	}

	// second_x
	if ( (i > 0) && (i+1 < local_NN) ) { // i = 1 ... N-2
		
		if ( mask_undefined->get(J-1) || 
			 mask_undefined->get(J)   || 
			 mask_undefined->get(J+1) )
		    second_x = false;
		
	} else {
		second_x = false;
	}

	// third_x
	if ( (i > 1) && (i < local_NN) ) { // i = 2 ... N-1
		
		if ( mask_undefined->get(J-2) || 
			 mask_undefined->get(J-1) || 
			 mask_undefined->get(J) )
		    third_x = false;
		
	} else {
		third_x = false;
	}
	
	// first_y
	if ( (j >= 0) && (j+2 < local_MM) ) { // j = 0 ... M-3
		
		if ( mask_undefined->get(J)    || 
			 mask_undefined->get(J+NN) ||
			 mask_undefined->get(J+2*NN) )
			first_y = false;
		
	} else {
		first_y = false;
	}

	// second_y
	if ( (j > 0) && (j+1 < local_MM) ) { // j = 1 ... M-2
		
		if ( mask_undefined->get(J-NN) || 
			 mask_undefined->get(J)    || 
			 mask_undefined->get(J+NN) )
		    second_y = false;
		
	} else {
		second_y = false;
	}

	// third_y
	if ( (j > 1) && (j < local_MM) ) { // j = 2 ... M-1
		
		if ( mask_undefined->get(J-2*NN) || 
			 mask_undefined->get(J-NN)   || 
			 mask_undefined->get(J) )
		    third_y = false;
		
	} else {
		third_y = false;
	}

	// first_xx
	if (
		( (i >= 0) && (i+1 < local_NN) ) &&  // i = 0 ... N-2
		( (j >= 0) && (j+1 < local_MM) )     // j = 0 ... M-2
	   )
	{
		if ( 
			 mask_undefined->get(J)      || 
			 mask_undefined->get(J+1)    ||
			 mask_undefined->get(J+NN)   ||
			 mask_undefined->get(J+NN+1) 
		   )
			first_xx = false;
	} else {
		first_xx = false;
	}

	// second_xx
	if (
		( (i > 0) && (i < local_NN) )    &&  // i = 1 ... N-1
		( (j >= 0) && (j+1 < local_MM) )     // j = 0 ... M-2
	   )
	{
		if ( 
			 mask_undefined->get(J-1)      || 
			 mask_undefined->get(J)        ||
			 mask_undefined->get(J+NN-1)   ||
			 mask_undefined->get(J+NN) 
		   )
			second_xx = false;
	} else {
		second_xx = false;
	}

	// first_yy
	if (
		( (i >= 0) && (i+1 < local_NN) ) &&  // i = 0 ... N-2
		( (j > 0) && (j < local_MM) )        // j = 1 ... M-1
	   )
	{
		if ( 
			 mask_undefined->get(J-NN)      || 
			 mask_undefined->get(J-NN+1)    ||
			 mask_undefined->get(J)         ||
			 mask_undefined->get(J+1) 
		   )
			first_yy = false;
	} else {
		first_yy = false;
	}

	// second_yy
	if (
		( (i > 0) && (i < local_NN) )    &&  // i = 1 ... N-1
		( (j > 0) && (j < local_MM) )        // j = 1 ... M-1
	   )
	{
		if ( 
			 mask_undefined->get(J-NN-1)      || 
			 mask_undefined->get(J-NN)        ||
			 mask_undefined->get(J-1)         ||
			 mask_undefined->get(J) 
		   )
			second_yy = false;
	} else {
		second_yy = false;
	}
	
	return;

};

}; // namespace surfit;

#endif

