
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit_solver_sor__
#define __surfit_solver_sor__

#include <algorithm>
#include <vector>

#include <errno.h>

#include "vec.h"
#include "vec_alg.h"

#include <float.h>

using namespace std;

namespace surfit {

template <class M, class V>
vec * sor(M * A, V * b, int max_it, REAL tol, vec *& X, REAL omega = REAL(1.6), REAL undef_value = FLT_MAX) {
	int flag = 0;                                // initialization
	int iter = 0;
	
	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 

	vec * r = new vec(b->size());
	
	vec * x = NULL;
	if (!X) {
		x = new vec(b->size());
		int cnt;
		for (cnt = 0; cnt < b->size(); cnt++) {
			(*x)(cnt) = (*b)(cnt);
		};
	}
	else 
	{
		x = X;
		X = NULL;
	}

	REAL error = FLT_MAX;
	REAL error_norm = bnrm2;	
	REAL sigma = 0;
	int i,j,prev_j;

	int n = b->size();
	REAL a_ii;

	vec * x_1 = new vec(*x);

	for (iter = 0; iter < max_it; iter++) {

		for (i = 0; i < n; i++) {
			
			a_ii = A->at(i,i);
			if (a_ii == REAL(0)) 
				continue;

			sigma = 0;
			
			for (j = 0; j < i;) {
				prev_j = j;
				sigma += (*x)(prev_j)*A->at(i,j,&j);
			}
			
			for (j = i+1; j < n;) {
				prev_j = j;
				sigma += (*x_1)(prev_j)*A->at(i,j,&j);
			}
			
			sigma = ( (*b)(i) - sigma )/a_ii;
			
			(*x)(i) = (*x_1)(i) + omega*( sigma - (*x_1)(i) );

		}
		
		error = 0;
		for (i = 0; i < n; i++) {
			error += ((*x)(i) - (*x_1)(i))*((*x)(i) - (*x_1)(i));
		}
		error /= error_norm;
		if (error < tol)
			break;
		
		*x_1 = *x;

	}

	delete x_1;

	writelog(SURFIT_MESSAGE,"sor: (%d)\terror : %12.6G iter : %d",x->size(), error, iter);

	return x;
	
};

}; // namespace surfit;

#endif 

