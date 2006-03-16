
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

#include "mklbooster_ie.h"
#include "mklbooster.h"
#include "matr.h"
#include "vec.h"
#include "intvec.h"
#include "fileio.h"
#include "vec_alg.h"

#include <mkl_blas.h>

#define SOLVER_CG_MAX          40

namespace surfit {

vec * cg_with_mkl_threaded(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value) 
{
	int flag = 0;                                // initialization
	int iter = 0;
	int N = b->size();
	int odin = 1;
	double dodin = 1;

	double mult;
	
	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 

	vec * r = create_vec(N,0,0); // don't fill
	
	vec * x = NULL;
	if (!X) 
		x = create_vec(*b);
	else 
	{
		x = X;
		X = NULL;
	}

	// r = b - A*x;
	A->mult(x,r);
	REAL error_norm = bnrm2;	
	REAL error = 0;
	mult = -1;
	threaded_DSCAL(&N, &mult, r->begin(), &odin);
	mult = 1;
	threaded_DAXPY(&N, &mult, const_cast<double*>(b->begin()), &odin, r->begin(), &odin);
	int max_pos = IDAMAX(&N, r->begin(), &odin) - 1;
	error = fabs((*r)(max_pos));
	error = error/bnrm2;
	///////////////		

	if (( error < tol ) || (stop_execution)) {
		if (r)
			r->release();
		return x;
	}
	
	vec * p = create_vec(*r);
	
	vec * q = create_vec(b->size(),0,0); // don't fill
	
	REAL rho_1, rho, beta;
	rho = REAL(0);

	error_norm = norm2(x, undef_value);
	
	for (iter = 1; iter <= max_it; iter++) {    // begin iteration
		
		rho_1 = rho;
		//rho = times(r,r); 
		rho = threaded_DDOT(&N, r->begin(), &odin, r->begin(), &odin);
		
		if ( iter > 1 ) {                        // direction vector
			beta = rho / rho_1;
			// p = beta*p;
			threaded_DSCAL(&N, &beta, p->begin(), &odin);
			threaded_DAXPY(&N, &dodin, r->begin(), &odin, p->begin(), &odin);
			//////////////
		}

		A->mult(p,q);
	
		//REAL times_pq = times(p,q);
		REAL times_pq = threaded_DDOT(&N, p->begin(), &odin, q->begin(), &odin);
		REAL alpha = 0;
		if (fabs(times_pq) > MIN(1e-4,tol))
			alpha = rho / times_pq;

		if (alpha == 0) {
			bool stop = true;
		}

		error = 0;
				
		// x = x + alpha * p;                    // update approximation vector
		threaded_DAXPY(&N, &alpha, p->begin(), &odin, x->begin(), &odin);
		max_pos = IDAMAX(&N, p->begin(), &odin) - 1;
		error = fabs((*p)(max_pos));
		error *= fabs(alpha);
		/////////////////////

		// REAL Error = norm2( r ) / bnrm2;      // check convergence
		error = error/error_norm;
		if (error_norm == 0)
			error = 0;
		
		if (( error <= tol ) || (stop_execution) )
			break;
		
		// r = r - alpha * q;                    // compute residual
		mult = -alpha;
		threaded_DAXPY(&N, &mult, q->begin(), &odin, r->begin(), &odin);
		//////////////////////
	}
	
	if (( error > tol ) || (stop_execution))
		flag = 1;                                // no convergence
		
	if (p)
		p->release();
	if (q)
		q->release();
	if (r)
		r->release();

	writelog(LOG_MESSAGE,"mkl_cg: (%d)\terror : %12.6G iter : %d",x->size(), error, iter);

	return x;
	
};


vec * cg_with_mkl(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value) 
{
	if (cpu > 1) {
		return cg_with_mkl_threaded(A, b, max_it, tol, X, undef_value);
	} 
	int flag = 0;                                // initialization
	int iter = 0;
	int N = b->size();
	int odin = 1;
	double dodin = 1;

	double mult;
	
	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 

	vec * r = create_vec(N,0,0); // don't fill
	
	vec * x = NULL;
	if (!X) 
		x = create_vec(*b);
	else 
	{
		x = X;
		X = NULL;
	}

	// r = b - A*x;
	A->mult(x,r);
	REAL error_norm = bnrm2;	
	REAL error = 0;
	mult = -1;
	DSCAL(&N, &mult, r->begin(), &odin);
	mult = 1;
	DAXPY(&N, &mult, const_cast<double*>(b->begin()), &odin, r->begin(), &odin);
	int max_pos = IDAMAX(&N, r->begin(), &odin) - 1;
	error = fabs((*r)(max_pos));
	error = error/bnrm2;
	///////////////		

	if (( error < tol ) || (stop_execution)) {
		if (r)
			r->release();
		return x;
	}
	
	vec * p = create_vec(*r);
	
	vec * q = create_vec(b->size(),0,0); // don't fill
	
	REAL rho_1, rho, beta;
	rho = REAL(0);

	error_norm = norm2(x, undef_value);
	
	for (iter = 1; iter <= max_it; iter++) {    // begin iteration
		
		rho_1 = rho;
		//rho = times(r,r); 
		rho = DDOT(&N, r->begin(), &odin, r->begin(), &odin);
		
		if ( iter > 1 ) {                        // direction vector
			beta = rho / rho_1;
			// p = beta*p;
			DSCAL(&N, &beta, p->begin(), &odin);
			DAXPY(&N, &dodin, r->begin(), &odin, p->begin(), &odin);
			//////////////
		}

		A->mult(p,q);
	
		//REAL times_pq = times(p,q);
		REAL times_pq = DDOT(&N, p->begin(), &odin, q->begin(), &odin);
		REAL alpha = 0;
		if (fabs(times_pq) > MIN(1e-4,tol))
			alpha = rho / times_pq;

		if (alpha == 0) {
			bool stop = true;
		}

		error = 0;
				
		// x = x + alpha * p;                    // update approximation vector
		DAXPY(&N, &alpha, p->begin(), &odin, x->begin(), &odin);
		max_pos = IDAMAX(&N, p->begin(), &odin) - 1;
		error = fabs((*p)(max_pos));
		error *= fabs(alpha);
		/////////////////////

		// REAL Error = norm2( r ) / bnrm2;      // check convergence
		error = error/error_norm;
		if (error_norm == 0)
			error = 0;
		
		if (( error <= tol ) || (stop_execution) )
			break;
		
		// r = r - alpha * q;                    // compute residual
		mult = -alpha;
		DAXPY(&N, &mult, q->begin(), &odin, r->begin(), &odin);
		//////////////////////
	}
	
	if (( error > tol ) || (stop_execution))
		flag = 1;                                // no convergence
		
	if (p)
		p->release();
	if (q)
		q->release();
	if (r)
		r->release();

	writelog(LOG_MESSAGE,"mkl_cg: (%d)\terror : %12.6G iter : %d",x->size(), error, iter);

	return x;
	
};

}; // namespace surfit;

