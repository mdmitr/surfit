
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

#include "../surfit_ie.h"
#include <errno.h>

#include "../solvers.h"
#include "vec.h"
#include "vec_alg.h"
#include "../matr.h"
#include "../variables_tcl.h"

using namespace std;

namespace surfit {

REAL make_iter(matr * A, const vec * B, REAL tau, vec * x_0, vec * x_1, REAL error_norm) {

	A->mult(x_0,x_1);
	
	int N = B->size();
	int i;

	for (i = 0; i < N; i++)
		(*x_1)(i) = (*x_0)(i) - tau *( (*x_1)(i) - (*B)(i));


	REAL err = 0;
	for (i = 0; i < N; i++) 
		err = MAX( err, fabs((*x_0)(i) - (*x_1)(i)) );
	
	err = sqrt(err);
	err /= error_norm;
	
	*x_0 = *x_1;

	return err;
};

vec * RF(matr * A, const vec * b, int max_it, REAL tol, vec * X, REAL undef_value) {
	
	vec * x_0 = NULL;
	if (!X) {
		x_0 = create_vec(b->size());
		size_t cnt;
		for (cnt = 0; cnt < b->size(); cnt++) {
			(*x_0)(cnt) = (*b)(cnt);
		};
	}
	else
		x_0 = X;

	REAL M = A->norm();
	REAL tau = REAL(2)/M;
		
	vec * x_1 = create_vec(x_0->size());
	
	int iter;

	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 
		
	REAL error_norm = norm2(X, undef_value);
	REAL err;
	for (iter = 1; iter <= max_it; iter++)  {  // begin iteration

		err = make_iter(A,b,tau,x_0,x_1,error_norm);
		if ( (err < tol) || (stop_execution == 1) )
			break;
		
	}
	
	if (!X) {
		if (x_0)
			x_0->release();
	}
	
	writelog(LOG_MESSAGE,"ri: (%d)\terror : %lf iter : %d",x_1->size(), err, iter);

	return x_1;
};

}; // namespace surfit;

