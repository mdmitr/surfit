
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

namespace surfit {

void _decomp1d(REAL * X_begin, 
	       int N, 
	       int distance, 
	       REAL undef_value,
	       bool flag,
	       vec * buf)
{
	int i;
	int pos = 0;

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

	int buf_size = N/2;
	for (i = 0; i < buf_size; i++) 
		*(X_begin + buf_size*distance + i*distance) = (*buf)(i);
	
};

void _decomp2d(vec *& X,
	       vec *& Xa, vec *& Xd, vec *& Xh, vec *& Xv,
	       int N, int M, bool enlarge_cols, bool enlarge_rows,
	       REAL undef_value,
	       bool flag)
{

	int newN = N;
	int newM = M;

	if (enlarge_cols)
		newN++;
	if (enlarge_rows)
		newM++;

	int i, j;

	if (enlarge_cols) {
		X->resize(newN*M);
		for (j = M-1; j >= 0; j--) {
			memmove(X->begin() + j*N + j, X->begin() + j*N, N*sizeof(REAL));
			(*X)(j*N + j + N) = (*X)(j*N + j + N - 1);
		}
	}
	if (enlarge_rows) {
		X->resize(newN*newM);
		memcpy( X->begin() + (newM-1)*newN, X->begin() + (newM-2)*newN, newN*sizeof(REAL) );
		for (i = 0; i < newN; i++)
			(*X)(i + (newM-1)*newN) = (*X)(i + (newM-2)*newN);
	}

	// decomp in "OY" direction (column by column)

	vec * buf = create_vec(newM/2, 0, 0, 0); // don't fill this vector

	for (i = 0; i < newN; i++) 
		_decomp1d(X->begin() + i, newM, newN, undef_value, flag, buf);

	// decomp in "OX" direction
	buf->resize(newN*newM/4);
	_decomp1d(X->begin(), newN*newM/2, 1, undef_value, flag, buf);

	Xa = create_vec(newN*newM/4, 0, 0, 0); // don't fill this vector
	memcpy(Xa->begin(), X->begin(), newN*newM/4*sizeof(REAL));
	Xh = buf;

	buf = X;
	_decomp1d(X->begin() + newN*newM/2, newN*newM/2, 1, undef_value, flag, buf);

	Xv = create_vec(newN*newM/4, 0, 0, 0);  // don't fill this vector
	memcpy(Xv->begin(), X->begin() + newN*newM/2, newN*newM/4*sizeof(REAL));
	Xd = buf;
	Xd->resize(newN*newM/4);

	X = NULL;
	
	return;
};


void _recons1d(REAL * X_begin, 
	       int N, 
	       int distance, 
	       REAL undef_value,
	       bool flag,
	       vec * buf)
{

	int i;
	int pos = 0;

	REAL s1, s2;
	REAL a, d;

	// copy approximation coefficients to buf
	if (distance == 1)
		memcpy(buf->begin(), X_begin, N/2*sizeof(REAL)); 
	else {
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


void _recons2d(vec *& X,
	       const vec * a,
	       const vec * d,
	       const vec * h,
	       const vec * v,
	       int N, int M,
	       bool enlarged_cols,
	       bool enlarged_rows,
	       REAL undef_value,
	       bool flag)
{

	int newN = 2*N;
	int newM = 2*M;

	X = create_vec(newN*newM, 0, 0, 0); // don't fill this vector

	memcpy(X->begin(), a->begin(), a->size()*sizeof(REAL));
	memcpy(X->begin() + newN*newM/4, h->begin(), h->size()*sizeof(REAL));
	memcpy(X->begin() + newN*newM/2, v->begin(), v->size()*sizeof(REAL));
	memcpy(X->begin() + 3*(newN*newM/4), d->begin(), d->size()*sizeof(REAL));

	vec * buf = create_vec(newN*newM/4, 0, 0, 0);

	_recons1d(X->begin(), newN*newM/2, 1, undef_value, flag, buf);
 	_recons1d(X->begin() + newN*newM/2, newN*newM/2, 1, undef_value, flag, buf);

	int i,j;

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
		for (j = 1; j < newM; j++)
			memmove(X->begin() + j*newN, X->begin() + j*N, newN*sizeof(REAL));
		X->resize(newN*newM);		
	}


};



}; // namespace surfit;

