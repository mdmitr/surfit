
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

#ifndef __surfit_mrf_included__
#define __surfit_mrf_included__

#include "vec.h"

namespace surfit {

//! applies wavelet decompositon for vector
SURFIT_EXPORT
void _decomp1d(extvec::iterator X_begin, 
	       size_t N, // amount of elements to process
	       int distance, // distance between elements
	       REAL undef_value,
	       bool flag,
	       extvec * buf); // temporary vector of size N/2

//! applies wavelet decompositon as matrix
SURFIT_EXPORT
void _decomp2d(extvec *& X,
	       extvec *& Xa,
	       extvec *& Xd,
	       extvec *& Xh,
	       extvec *& Xv,
	       size_t N, size_t M,
	       bool enlarge_X,
	       bool enlarge_Y,
	       REAL undef_value,
	       bool flag);

//! applies wavelet reconstruction for vector
SURFIT_EXPORT		
void _recons1d(extvec::iterator X_begin, 
	       size_t N, // amount of elements to process
	       int distance, // distance between elements
	       REAL undef_value,
	       bool flag,
	       extvec * buf); // temporary vector of size N/2

//! applies wavelet reconstruction for matrix
SURFIT_EXPORT
void _recons2d(extvec *& X,
	       const extvec * Xa,
	       const extvec * Xd,
	       const extvec * Xh,
	       const extvec * Xv,
	       size_t N, size_t M,
	       bool enlarge_X,
	       bool enlarge_Y,
	       REAL undef_value,
	       bool flag);

}; // namespace surfit;


#endif

