
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

#ifndef __surfit_solver_simpiter__
#define __surfit_solver_simpiter__

namespace surfit {

template <class M, class V>
REAL make_iter(M * A, V * B, REAL tau, vec * x_0, vec * x_1, REAL bnrm2) {

	A->mult(x_0,x_1);
	
	int N = B->size();
	int i;

	REAL err = 0;

	for (i = 0; i < N; i++) 
		err += ((*B)(i)-(*x_1)(i))*((*B)(i)-(*x_1)(i));
	
	err = sqrt(err);
	err /= bnrm2;
		
	for (i = 0; i < N; i++)
		(*x_1)(i) = (*x_0)(i) - tau *( (*x_1)(i) - (*B)(i));
	
	*x_0 = *x_1;

	return err;
};

template <class MM, class V>
vec * simpiter(MM * A, V * b, int max_it, REAL tol = 1e-6, vec * X = NULL) {
	
	vec * x_0 = NULL;
	if (!X) {
		x_0 = new vec(b->size());
		int cnt;
		for (cnt = 0; cnt < b->size(); cnt++) {
			(*x_0)(cnt) = (*b)(cnt);
		};
	}
	else
		x_0 = X;

	REAL M = A->norm();
	REAL tau = REAL(2)/M;
		
	vec * x_1 = new vec(x_0->size());
	
	int iter;

	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 
		
	REAL err;
	for (iter = 1; iter <= max_it; iter++)  {  // begin iteration

		err = make_iter(A,b,tau,x_0,x_1,bnrm2);
		if (err < tol)
			break;
		
	}
	
	if (!X)
		delete x_0;
	
	writelog(SURFIT_MESSAGE,"simpiter: (%d)\terror : %lf iter : %d",x_1->size(), err, iter);

	return x_1;
};

}; // namespace surfit;


#endif

