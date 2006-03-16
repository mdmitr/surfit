
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

#ifndef __surfit__solvers__
#define __surfit__solvers__

#include <float.h>

namespace surfit {

class vec;
class matr;
class functional;

SURFIT_EXPORT
void solve(matr * T, const vec * V, vec *& X);

SURFIT_EXPORT
bool solve_with_penalties(functional * fnc, 
			  matr * T, vec * V, vec *& X);

struct solver {
	virtual void solve(matr * T, const vec * V, vec *& X) = 0;
	virtual const char * get_long_name() const = 0;
	virtual const char * get_short_name() const = 0;
};

SURFIT_EXPORT
bool add_solver(solver * slvr);

SURFIT_EXPORT
bool remove_solver(solver * slvr);

SURFIT_EXPORT
int get_solvers_count();

SURFIT_EXPORT
const char * get_solver_long_name(int pos);

SURFIT_EXPORT
const char * get_solver_short_name(int pos);

SURFIT_EXPORT
const char * get_current_solver_short_name();

SURFIT_EXPORT
const char * get_current_solver_long_name();

SURFIT_EXPORT
void set_solver(const char * short_name);

SURFIT_EXPORT
void solvers_info();

#ifdef HAVE_THREADS
// y = ax + y
SURFIT_EXPORT
void axpy(REAL a, const vec & x, vec & y);

// y = x + ay
SURFIT_EXPORT
void xpay(REAL a, const vec & x, vec & y);

SURFIT_EXPORT
REAL threaded_times(const vec * a, const vec * b);
#endif

vec * RF(matr * A, const vec * b, int max_it, REAL tol = 1e-6, vec * X = NULL, REAL undef_value = FLT_MAX);
vec * CG(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value = FLT_MAX);
vec * J(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value = FLT_MAX);
vec * JCG(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value = FLT_MAX);
vec * SSOR(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value = FLT_MAX, REAL omega = REAL(1.6));
vec * SSORCG(matr * A, const vec * b, int max_it, REAL tol, vec *& X, REAL undef_value = FLT_MAX, REAL omega = REAL(1.6));

};

#endif

