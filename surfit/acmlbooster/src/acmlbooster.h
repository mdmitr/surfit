
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

#ifndef __acmlsolver_included__
#define __acmlsolver_included__

#include "solvers.h"
#include "variables_tcl.h"

namespace surfit {

void init_acml_solvers();

vec * cg_with_acml(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value);

struct acml_cg : public solver 
{
	acml_cg() {
		add_solver(this);
		set_solver("cg_acml");
	}
	~acml_cg() {
		remove_solver(this);
	}
	virtual void solve(matr * T, const vec * V, vec *& X);
	virtual const char * get_short_name() const { return "cg_acml"; };
	virtual const char * get_long_name() const { return "Conjugate Gradients (ACML)"; }
	
};

void threaded_DAXPY(int *n,double *alpha,double *x,int *incx,double *y,int *incy);
void threaded_DSCAL(int *n,double *a,double *x,int *incx);
double threaded_DDOT(int *n,double *x,int *incx,double *y,int *incy);

}; // namespace surfit;

#endif

