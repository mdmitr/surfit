
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

namespace surfit {

class vec;

SURFIT_EXPORT
void _decomp1d(REAL * X_begin, 
	       int N, // amount of elements to process
	       int distance, // distance between elements
	       REAL undef_value,
	       bool flag,
	       vec * buf); // temporary vector of size N/2

SURFIT_EXPORT
void _decomp2d(vec *& X,
	       vec *& Xa,
	       vec *& Xd,
	       vec *& Xh,
	       vec *& Xv,
	       int N, int M,
	       bool enlarge_X,
	       bool enlarge_Y,
	       REAL undef_value,
	       bool flag);


SURFIT_EXPORT		
void _recons1d(REAL * X_begin, 
	       int N, // amount of elements to process
	       int distance, // distance between elements
	       REAL undef_value,
	       bool flag,
	       vec * buf); // temporary vector of size N/2

SURFIT_EXPORT
void _recons2d(vec *& X,
	       const vec * Xa,
	       const vec * Xd,
	       const vec * Xh,
	       const vec * Xv,
	       int N, int M,
	       bool enlarge_X,
	       bool enlarge_Y,
	       REAL undef_value,
	       bool flag);

}; // namespace surfit;


#endif

