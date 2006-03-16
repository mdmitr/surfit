
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

#ifndef __mklsolver_included__
#define __mklsolver_included__

#include "solvers.h"
#include "variables_tcl.h"

namespace surfit {

void init_mkl_solvers();

vec * cg_with_mkl(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value);

struct mkl_cg : public solver 
{
	mkl_cg() {
		add_solver(this);
		set_solver("cg_mkl");
	}
	~mkl_cg() {
		remove_solver(this);
	}
	virtual void solve(matr * T, const vec * V, vec *& X);
	virtual const char * get_short_name() const { return "cg_mkl"; };
	virtual const char * get_long_name() const { return "Conjugate Gradients (MKL)"; }
	
};

void threaded_DAXPY(int *n,double *alpha,double *x,int *incx,double *y,int *incy);
void threaded_DSCAL(int *n,double *a,double *x,int *incx);
double threaded_DDOT(int *n,double *x,int *incx,double *y,int *incy);

}; // namespace surfit;

#endif

