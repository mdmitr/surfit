
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

#ifndef __surfit_solver_cg2__
#define __surfit_solver_cg2__

#include <algorithm>
#include <vector>

#include "vec.h"

using namespace std;

namespace surfit {

template <class M, class V>
vec * cg2(M * A, V * b, int max_it, REAL tol, vec *& X) {

	int flag = 0;                                // initialization
	int iter = 0;
	
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

	vec * r = new vec(b->size());
	vec * temp = new vec(b->size());

	// b = A*b
	A->mult_transposed(b,r);
	*b = *r;

	REAL bnrm2 = norm2( b );
	if  ( bnrm2 == REAL(0) )
		bnrm2 = REAL(1); 

	// r = b - A*A*x;
	A->mult(x,temp);
	A->mult_transposed(temp,r);
	int r_cnt;
	REAL error_norm = bnrm2;	
	REAL error = 0;
	for (r_cnt = 0; r_cnt < r->size(); r_cnt++) {
		(*r)(r_cnt) = (*b)(r_cnt) - (*r)(r_cnt);
		error = MAX(error, fabs((*r)(r_cnt)) );
	}
	error = error/bnrm2;
	///////////////		

	if ( error < tol ) {
		delete r;
		delete temp;
		return x;
	}
	
	vec * p = new vec(b->size());
	for (r_cnt = 0; r_cnt < r->size(); r_cnt++) {
		(*p)(r_cnt) = (*r)(r_cnt);
	}

	vec * q = new vec(b->size());
	
	REAL rho_1, rho, beta;
	rho = REAL(0);

	error_norm = norm2(x, undef_value);
	
	for (iter = 1; iter <= max_it; iter++) {    // begin iteration
		
		rho_1 = rho;
		rho = times(r,r); 
		
		if ( iter > 1 ) {                        // direction vector
			beta = rho / rho_1;
			// p = beta*p;
			vec::iterator p_it;
			vec::const_iterator r_it;
			for (p_it = p->begin(), r_it = r->begin(); p_it != p->end(); ++p_it, ++r_it) 
				*p_it = *r_it + *p_it * beta;
			//////////////
		}

		A->mult(p,temp);
		A->mult_transposed(temp,q);
	
		REAL times_pq = times(p,q);
		REAL alpha = 0;
		if (fabs(times_pq) > MIN(1e-4,tol))
			alpha = rho / times_pq;

		if (alpha == 0) {
			bool stop = true;
		}


		error = 0;
				
		// x = x + alpha * p;                    // update approximation vector
		vec::iterator x_it;
		vec::const_iterator p_it;
		for (x_it = x->begin(), p_it = p->begin(); x_it != x->end(); ++x_it, ++p_it) {
			if (*x_it == undef_value)
				continue;
			*x_it = *x_it + alpha * *p_it;
			error = MAX(error, fabs(alpha * *p_it));
		}
		/////////////////////

		// REAL Error = norm2( r ) / bnrm2;      // check convergence
		error = error/error_norm;
		if (error_norm == 0)
			error = 0;
		
		if ( error <= tol )
			break;
		
		// r = r - alpha * q;                    // compute residual
		vec::iterator r_it;
		vec::const_iterator q_it;
		for (r_it = r->begin(), q_it = q->begin(); r_it != r->end(); ++r_it, ++q_it) {
			*r_it = *r_it - alpha * *q_it;
		}
		//////////////////////
		
	}
	
	if ( error > tol ) 
		flag = 1;                                // no convergence
		
	delete p;
	delete q;
	delete r;
	delete temp;

	writelog(SURFIT_MESSAGE,"cg2: (%d)\terror : %12.6G iter : %d",x->size(), error, iter);

	return x;

};

}; // namespace surfit;

#endif

