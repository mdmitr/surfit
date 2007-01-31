
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
#include <algorithm>
#include <vector>
#include <errno.h>

#include "../solvers.h"
#include "vec.h"
#include "vec_alg.h"
#include "../matr.h"
#include "../variables_tcl.h"

using namespace std;

namespace surfit {

extvec * J(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, REAL undef_value) {

	int flag = 0;                                // initialization
	int iter = 0;
	
	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 

	extvec * x = NULL;
	if (!X) 
		x = create_extvec(*b);
	else 
	{
		x = X;
		X = NULL;
	}

	writelog2(LOG_MESSAGE,"jacobi: (%d) ",x->size());

	REAL error = FLT_MAX;
	REAL error_norm = bnrm2;	
	REAL sigma = 0;
	int i;

	int n = b->size();
	REAL a_ii;

	REAL MM = A->norm();
	REAL gamma = REAL(2)/(MM);
	REAL save_x;

	extvec * x_1 = create_extvec(*x);

	error_norm = norm2(x, undef_value);
		
	for (iter = 0; iter < max_it; iter++) {

		for (i = 0; i < n; i++) {
			
			a_ii = A->at(i,i);
			if (a_ii == REAL(0)) 
				continue;

			save_x = (*x)(i);
			(*x)(i) = 0;
			sigma = A->mult_line(i, x->const_begin(), x->const_end());
			(*x)(i) = save_x;

			(*x_1)(i) = ( ((*b)(i) - sigma )/a_ii -(*x)(i))*gamma + (*x)(i);
			
		}

		// compute residual
		error = 0;
		for (i = 0; i < n; i++) {
			error = MAX( error, fabs((*x_1)(i) - (*x)(i)) );
		}
		error /= error_norm;
		if ( (error < tol) || (stop_execution == 1))
			break;
		
		*x = *x_1;

	}

	if (x_1)
		x_1->release();
	
	log_printf("error : %12.6G iter : %d\n", error, iter);

	return x;
	
};

}; // namespace surfit;
