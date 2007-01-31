
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

#include "fileio.h"
#include "vec.h"

#include <memory.h>
#include "mrf.h"

#include <string.h>
#include <limits.h>

namespace surfit {

void _decomp1d(extvec::iterator X_begin, 
	       size_t N, 
	       int distance, 
	       REAL undef_value,
	       bool flag,
	       extvec * buf)
{
	size_t i;
	size_t pos = 0;

	REAL s1, s2;
	REAL a, d;
	for (i = 0; i < N; i+= 2) {
		s1 = *(X_begin + i*distance);
		s2 = *(X_begin + (i+1)*distance);

		if ((s1 != undef_value) && (s2 != undef_value))
		{
			a = (s1 + s2)/REAL(2);
			d = (s1 - s2)/REAL(2);
		} else {
			if ( flag ) {
				if ( s1 == undef_value )
					d = undef_value;
				else
					d = s1;
				if ( s2 == undef_value )
					a = undef_value;
				else  
					a = s2;
			} else {
				if ( s1 == undef_value ) 
					a = undef_value;
				 else 
					a = s1;
				if ( s2 == undef_value )
					d = undef_value;
				else
					d = s2;
			}
		}
	
		*(X_begin + pos*distance) = a;
		(*buf)(pos) = d;

		pos++;
	}

	size_t buf_size = N/2;
	for (i = 0; i < buf_size; i++) 
		*(X_begin + buf_size*distance + i*distance) = (*buf)(i);
	
};

void _decomp2d(extvec *& X,
	       extvec *& Xa, extvec *& Xd, extvec *& Xh, extvec *& Xv,
	       size_t N, size_t M, bool enlarge_cols, bool enlarge_rows,
	       REAL undef_value,
	       bool flag)
{

	size_t newN = N;
	size_t newM = M;

	if (enlarge_cols)
		newN++;
	if (enlarge_rows)
		newM++;

	size_t i, j;

	if (enlarge_cols) {
		X->resize(newN*M);
		for (j = M-1; ; j--) {

#ifdef XXL
			size_t q;
			size_t pos = j*N + N - 1;
			for (q = 0; q < N; q++)  {
				*(X->begin()+pos+j) = *(X->const_begin()+pos);
				pos--;
			}
#else
			memmove(X->begin() + j*N + j, X->begin() + j*N, N*sizeof(REAL));
#endif
			(*X)(j*N + j + N) = (*X)(j*N + j + N - 1);
			if (j == 0)
				break;
		}
	}
	if (enlarge_rows) {
		X->resize(newN*newM);
#ifdef XXL
		std::copy(X->const_begin() + (newM-2)*newN, X->const_begin() + (newM-2)*newN + newN, X->begin() + (newM-1)*newN);
#else
		memcpy( X->begin() + (newM-1)*newN, X->begin() + (newM-2)*newN, newN*sizeof(REAL) );
#endif
		for (i = 0; i < newN; i++)
			(*X)(i + (newM-1)*newN) = (*X)(i + (newM-2)*newN);
	}

	// decomp in "OY" direction (column by column)

	extvec * buf = create_extvec(newM/2, 0, 0, 0); // don't fill this vector

	for (i = 0; i < newN; i++) 
		_decomp1d(X->begin() + i, newM, newN, undef_value, flag, buf);

	// decomp in "OX" direction
	buf->resize(newN*newM/4);
	_decomp1d(X->begin(), newN*newM/2, 1, undef_value, flag, buf);

	Xa = create_extvec(newN*newM/4, 0, 0, 0); // don't fill this vector
#ifdef XXL
	std::copy(X->const_begin(), X->const_begin() + newN*newM/4, Xa->begin());
#else
	memcpy(Xa->begin(), X->begin(), newN*newM/4*sizeof(REAL));
#endif
	Xh = buf;

	buf = X;
	_decomp1d(X->begin() + newN*newM/2, newN*newM/2, 1, undef_value, flag, buf);

	Xv = create_extvec(newN*newM/4, 0, 0, 0);  // don't fill this vector
#ifdef XXL
	std::copy(X->const_begin() + newN*newM/2, X->const_begin() + newN*newM/2 + newN*newM/4, Xv->begin());
#else
	memcpy(Xv->begin(), X->begin() + newN*newM/2, newN*newM/4*sizeof(REAL));
#endif
	Xd = buf;
	Xd->resize(newN*newM/4);

	X = NULL;
	
	return;
};


void _recons1d(extvec::iterator X_begin, 
	       size_t N, 
	       int distance, 
	       REAL undef_value,
	       bool flag,
	       extvec * buf)
{

	size_t i;
	size_t pos = 0;

	REAL s1, s2;
	REAL a, d;

	// copy approximation coefficients to buf
	if (distance == 1) {
#ifdef XXL
		std::copy(X_begin, X_begin + N/2, buf->begin());
#else
		memcpy(buf->begin(), X_begin, N/2*sizeof(REAL)); 
#endif
	} else {
		for (i = 0; i < N/2; i++) 
			(*buf)(i) = *(X_begin + i*distance);
	}
	
	for (i = 0; i < N/2; i++) {
		a = (*buf)(i);
		d = *(X_begin + (i+N/2)*distance);

		if (( a != undef_value ) && ( d != undef_value )) {
			s1 = a + d;
			s2 = a - d;
		} else {
			if (flag) {
				if (a == undef_value)
					s2 = undef_value;
				else
					s2 = a;
				if (d == undef_value) 
					s1 = undef_value;
				else
					s1 = d;
			} else {
				if (a == undef_value) 
					s1 = undef_value;
				else
					s1 = a;
				if (d == undef_value)
					s2 = undef_value;
				else
					s2 = d;
			}
		}

		*(X_begin + pos*distance) = s1;
		pos++;
		*(X_begin + pos*distance) = s2;
		pos++;

	}
};


void _recons2d(extvec *& X,
	       const extvec * a,
	       const extvec * d,
	       const extvec * h,
	       const extvec * v,
	       size_t N, size_t M,
	       bool enlarged_cols,
	       bool enlarged_rows,
	       REAL undef_value,
	       bool flag)
{

	size_t newN = 2*N;
	size_t newM = 2*M;

	X = create_extvec(newN*newM, 0, 0, 0); // don't fill this vector

#ifdef XXL
	std::copy(a->const_begin(), a->const_end(), X->begin());
	std::copy(h->const_begin(), h->const_end(), X->begin() + newN*newM/4);
	std::copy(v->const_begin(), v->const_end(), X->begin() + newN*newM/2);
	std::copy(d->const_begin(), d->const_end(), X->begin() + 3*(newN*newM/4));
#else
	memcpy(X->begin(), a->const_begin(), a->size()*sizeof(REAL));
	memcpy(X->begin() + newN*newM/4, h->const_begin(), h->size()*sizeof(REAL));
	memcpy(X->begin() + newN*newM/2, v->const_begin(), v->size()*sizeof(REAL));
	memcpy(X->begin() + 3*(newN*newM/4), d->const_begin(), d->size()*sizeof(REAL));
#endif

	extvec * buf = create_extvec(newN*newM/4, 0, 0, 0);

	_recons1d(X->begin(), newN*newM/2, 1, undef_value, flag, buf);
 	_recons1d(X->begin() + newN*newM/2, newN*newM/2, 1, undef_value, flag, buf);

	size_t i,j;

	buf->resize(newM/2);
	for (i = 0; i < newN; i++) {
		_recons1d(X->begin() + i, newM, newN, undef_value, flag, buf);
	}
	
	buf->release();
	
	N = newN;
	M = newM;
	if (enlarged_rows) {
		newM--;
		X->resize(newN*newM);
	}
	if (enlarged_cols) {
		newN--;
		for (j = 1; j < newM; j++) {
#ifdef XXL
			size_t q;
			for (q = 0; q < newN; q++)
				*(X->begin() + j*newN + q) = *(X->const_begin() + j*N + q);
#else
			memmove(X->begin() + j*newN, X->begin() + j*N, newN*sizeof(REAL));
#endif
		}
		X->resize(newN*newM);		
	}


};



}; // namespace surfit;

