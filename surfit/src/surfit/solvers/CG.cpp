
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
#include <time.h>

#include "threads.h"
#include "../solvers.h"
#include "vec.h"
#include "vec_alg.h"
#include "../matr.h"
#include "../variables_tcl.h"

using namespace std;

namespace surfit {

extvec * CG(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, REAL undef_value) {
	writelog2(LOG_MESSAGE,"cg: (%d) ", b->size());

	time_t ltime_begin;
	time( &ltime_begin );

#ifdef HAVE_THREADS	
	if (sstuff_get_threads() == 1) {
#endif
		
		int flag = 0;                                // initialization
		int iter = 0;
		int i;
		
		REAL bnrm2 = norm2( b );
		if  ( bnrm2 == REAL(0) )
			bnrm2 = REAL(1); 
		
		int N = b->size();
		extvec * r = create_extvec(N,0,0); // don't fill
		
		extvec * x = NULL;
		if (!X) 
			x = create_extvec(*b);
		else 
		{
			x = X;
			X = NULL;
		}
		
		// r = b - A*x;
		A->mult(x,r);
		REAL error_norm = bnrm2;	
		REAL error = 0;
		for (i = 0; i < N; i++) {
			(*r)(i) = (*b)(i) - (*r)(i);
			error = MAX(error, fabs((*r)(i)) );
		}
		error = error/bnrm2;
		///////////////		

		REAL from = log10(REAL(1)/error);
		REAL to = log10(REAL(1)/tol);
		REAL step = (to-from)/REAL(PROGRESS_POINTS+1);
		short prp = 0;
		
		if (( error < tol ) || (stop_execution)) {
			if (r)
				r->release();
			log_printf(" - nothing to do.\n");
			return x;
		}
		
		extvec * p = create_extvec(*r);
		
		extvec * q = create_extvec(N,0,0); // don't fill
		
		REAL rho_1, rho, beta;
		rho = REAL(0);
		
		error_norm = norm2(x, undef_value);
		
		for (iter = 1; iter <= max_it; iter++) {    // begin iteration

			rho_1 = rho;
			rho = times(r,r); 
						
			if ( iter > 1 ) {                        // direction vector
				beta = rho / rho_1;
				// p = beta*p;
				for (i = 0 ; i < N; i++) 
					(*p)(i) = (*r)(i) + (*p)(i)*beta;
				//////////////
			}
			
			A->mult(p,q);
			
			REAL times_pq = times(p,q);
			REAL alpha = 0;
			if (fabs(times_pq) > MIN(1e-4,tol))
				alpha = rho / times_pq;
			
			if (alpha == 0) {
				bool stop = true;
			}
			
			error = 0;
			
			// x = x + alpha * p;                    // update approximation vector
			for (i = 0; i < N ; i++) {
				(*x)(i) += alpha * (*p)(i);
				error = MAX(error, fabs( (*p)(i) ));
			}
			error *= fabs(alpha);
			/////////////////////
			
			// REAL Error = norm2( r ) / bnrm2;      // check convergence
			error = error/error_norm;
			if (error_norm == 0)
				error = 0;

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
				(*r)(i) -= alpha * (*q)(i);
			}
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
		
		time_t ltime_end;
		time( &ltime_end );
		
		double sec = difftime(ltime_end,ltime_begin);
		int minutes = (int)(sec/REAL(60));
		sec -= minutes*60;
		
		if (minutes > 0)
			log_printf(" iter : %d, error : %12.6G, %d min %G sec\n", iter, error, minutes, sec);
		else
			log_printf(" iter : %d, error : %12.6G, %G sec\n", iter, error, sec);
		
		return x;
#ifdef HAVE_THREADS
	} else {

		int flag = 0;     // initialization
		int iter = 0;
		int i;
		int N = b->size();
		
		REAL bnrm2 = norm2( b );
		if  ( bnrm2 == REAL(0) )
			bnrm2 = REAL(1); 
		
		extvec * r = create_extvec(N,0,0); // don't fill
		
		extvec * x = NULL;
		if (!X) 
			x = create_extvec(*b);
		else 
		{
			x = X;
			X = NULL;
		}
		
		// r = b - A*x;
		A->mult(x,r);
		REAL error_norm = bnrm2;	
		REAL error = 0;
		for (i = 0; i < N; i++) {
			(*r)(i) = (*b)(i) - (*r)(i);
			error = MAX(error, fabs((*r)(i)) );
		}
		error = error/bnrm2;
		///////////////
		
		REAL from = log10(REAL(1)/error);
		REAL to = log10(REAL(1)/tol);
		REAL step = (to-from)/REAL(PROGRESS_POINTS+1);
		short prp = 0;
		
		if (( error < tol ) || (stop_execution)) {
			if (r)
				r->release();
			log_printf(" - nothing to do.\n");
			return x;
		}
		
		extvec * p = create_extvec(*r);
		
		extvec * q = create_extvec(N,0,0); // don't fill
		
		REAL rho_1, rho, beta;
		rho = REAL(0);
		
		error_norm = norm2(x, undef_value);
		
		for (iter = 1; iter <= max_it; iter++) {    // begin iteration
		
			rho_1 = rho;
			//rho = times(r,r); 
			rho = threaded_times(r,r);
			
			if ( iter > 1 ) {                        // direction vector
				beta = rho / rho_1;
				// p = r + beta*p;
				xpay(beta, *r, *p);
				//////////////
			}
			
			A->mult(p,q);
			
			REAL times_pq = times(p,q);
			//REAL times_pq = threaded_times(p,q);
			REAL alpha = 0;
			if (fabs(times_pq) > MIN(1e-4,tol))
				alpha = rho / times_pq;
			
			if (alpha == 0) {
				bool stop = true;
			}
			
			error = 0;
			
			// x = x + alpha * p;                    // update approximation vector
			axpy(alpha, *p, *x);
			for (i = 0; i < N; i++)
				error = MAX(error, fabs( (*p)(i) ));
			error *= fabs(alpha);
			/////////////////////
			
			// REAL Error = norm2( r ) / bnrm2;      // check convergence
			error = error/error_norm;
			if (error_norm == 0)
				error = 0;
			
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
			axpy(-alpha,*q,*r);
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
		
		time_t ltime_end;
		time( &ltime_end );
		
		double sec = difftime(ltime_end,ltime_begin);
		int minutes = (int)(sec/REAL(60));
		sec -= minutes*60;

		if (minutes > 0)
			log_printf(" iter : %d, error : %12.6G, %d min %G sec\n", iter, error, minutes, sec);
		else
			log_printf(" iter : %d, error : %12.6G, %G sec\n", iter, error, sec);
		
		return x;

	}
	return NULL;
#endif
};

}; // namespace surfit;

