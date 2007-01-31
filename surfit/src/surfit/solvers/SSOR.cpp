
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

extvec * SSOR(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, REAL undef_value, REAL omega) {

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

	REAL error = FLT_MAX;
	REAL error_norm = bnrm2;	
	REAL sigma = 0;
	int i;

	int n = b->size();

	writelog2(LOG_MESSAGE,"ssor: (%d) ",n);

	REAL a_ii;

	extvec * x_1 = create_extvec(*x);
	extvec * x_12 = create_extvec(*x);
	extvec * r = create_extvec(x->size(), 0, 0); // don't fill this vector;

	REAL from, to, step;
	short prp = 0;
		
	for (iter = 0; iter < max_it; iter++) {

		*r = *x_1;

		for (i = 0; i < n; i++) {
			
			a_ii = A->at(i,i);
			if (a_ii == REAL(0)) {
				(*r)(i) = (*x_12)(i);
				continue;
			}
			
			(*r)(i) = 0;
			sigma = A->mult_line(i, r->const_begin(), r->const_end());
			sigma = ( (*b)(i) - sigma )/a_ii;
			
			(*x_12)(i) = (1 - omega)*(*x_1)(i) + omega*sigma;
			(*r)(i) = (*x_12)(i);

		}

		*r = *x_12;

		for (i = n-1; i >= 0; i--) {

			a_ii = A->at(i,i);
			if (a_ii == REAL(0)) {
				(*r)(i) = (*x)(i);
				continue;
			}

			(*r)(i) = 0;
			sigma = A->mult_line(i, r->const_begin(), r->const_end());
					
			sigma = ( (*b)(i) - sigma )/a_ii;
			(*x)(i) = (*x_12)(i) + omega*( sigma - (*x_12)(i) );
			(*r)(i) = (*x)(i);

		}

		
		error = 0;
		REAL err;
		for (i = 0; i < n; i++) {
			err = fabs((*x)(i) - (*x_1)(i));
			error = MAX(error, err);
		}
		error /= error_norm;

		if (iter == 0) {
			from = log10(REAL(1)/error);
			to = log10(REAL(1)/tol);
			step = (to-from)/REAL(PROGRESS_POINTS+1);
	
		}

		REAL prp_pos = (log10(REAL(1)/error)-from)/step;
		if (prp_pos > prp ) {
			short new_prp =MIN(PROGRESS_POINTS,short(prp_pos));
			short prp_cnt;
			for (prp_cnt = 0; prp_cnt < new_prp-prp; prp_cnt++)
				log_printf(".");
			prp = (short)prp_pos;
		}

		if ( (error < tol) || (stop_execution == 1) )
			break;
		
		*x_1 = *x;

	}

	if (x_1)
		x_1->release();
	if (x_12)
		x_12->release();
	if (r)
		r->release();
	
	log_printf(" error : %12.6G iter : %d\n", error, iter);

	return x;
	
};

}; // namespace surfit;
