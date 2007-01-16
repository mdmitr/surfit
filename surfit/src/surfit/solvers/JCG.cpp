
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

vec * JCG(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value) {
	
	int flag = 0;				     // initialization
	int iter = 0;
	REAL val;
	int i;
	int N = b->size();
	
	writelog2(LOG_MESSAGE,"jcg: (%d) ",N);

	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 
		
	// pseudo-residual vector
	vec * r = create_vec(N,0,0); // don't fill
	// direction vector
	vec * p = create_vec(N,0,0); // don't fill
	// temporary vector
	vec * temp = create_vec(N,0,0); // don't fill
	// vector for matrix multiplication
	vec * q = create_vec(N,0,0); // don't fill
	
	vec * x = NULL;
	if (!X) 
		x = create_vec(*b);
	else 
	{
		x = X;
		X = NULL;
	}
	
	// diagonal^-1 from matrix A
	vec * D = create_vec(N,0,0); // don't fill
	// symmetrization matrix W
	vec * W = create_vec(N,0,0); // don't fill;
	// G = D^-1*A

	for (i = 0; i < N; i++) {
		val = A->at(i,i);
		if (val != 0) {
			(*D)(i) = REAL(1)/val;
			(*W)(i) = sqrt(val);
		} else {
			(*D)(i) = 0;
			(*W)(i) = 0;
		}
	}
	
	REAL error_norm = bnrm2;	
	REAL error = 0;
	REAL alpha = 0;

	REAL rho_1, rho = REAL(0), beta;

	error_norm = norm2(x, undef_value);

	REAL from, to, step;
	short prp = 0;
		
	for (iter = 1; iter <= max_it; iter++) {    // begin iteration

		// update direction vector
		if (iter == 1) {
			// update pseugo-residual vector
			// r = G*x + k - x
			A->mult(x,r);
			for (i = 0; i < N; i++)
				(*r)(i) = (*D)(i) * ( (*b)(i) - (*r)(i) );
			// update Wr
			for (i = 0; i < N; i++)
				(*temp)(i) = (*r)(i)*(*W)(i);
			
			rho = times(temp,temp);
			
			*p = *r;
		} else {

			// update Wr
			for (i = 0; i < N; i++)
				(*temp)(i) = (*r)(i)*(*W)(i);

			rho_1 = rho;
			rho = times(temp,temp);

			beta = rho / rho_1;

			// p = r + beta*p;
			for (i = 0; i < N; i++) 
				(*p)(i) = (*r)(i) + beta * (*p)(i);
			for (i = 0; i < N; i++)
				(*temp)(i) = (*p)(i)*(*W)(i);
		}

		// q = W*D^-1*A*p
		A->mult(p,q);
		for (i = 0; i < N; i++)
			(*temp)(i) *= (*W)(i) * (*D)(i);

		REAL times_pq = times(temp,q);

		REAL alpha = 0;
		if (fabs(times_pq) > MIN(1e-4,tol))
			alpha = rho / times_pq;
		
		if (alpha == 0) {
			bool stop = true;
		}

		error = 0;
		
		// x = x + alpha * p;                    // update approximation vector
		for (i = 0; i < N; i++) {
			(*x)(i) += alpha * (*p)(i);
			error = MAX(error, fabs( (*p)(i) ) );
		}
		error *= fabs(alpha);
		/////////////////////

		// REAL Error = norm2( r ) / bnrm2;      // check convergence
		error = error/error_norm;
		if (error_norm == 0)
			error = 0;

		if (iter == 1) {
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
		
		if (( error <= tol ) || (stop_execution) )
			break;
		
		
		// r = r - alpha * q;                    // compute residual
		for (i = 0; i < N; i++) {
			(*r)(i) -= alpha * (*q)(i) * (*D)(i);
		}
		
		//////////////////////


		
	}
	
	if (( error > tol ) || (stop_execution))
		flag = 1;				 // no convergence
	
	if (p)
		p->release();
	if (r)
		r->release();
	if (D)
		D->release();
	if (W)
		W->release();
	if (temp)
		temp->release();
	if (q)
		q->release();
	
	log_printf(" error : %12.6G iter : %d\n",error, iter);
	
	return x;
};

}; // namespace surfit;

