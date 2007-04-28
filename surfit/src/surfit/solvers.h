
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
#include "vec.h"

namespace surfit {

class matr;
class functional;

SURFIT_EXPORT
size_t solve(matr * T, const extvec * V, extvec *& X);

SURFIT_EXPORT
bool solve_with_penalties(functional * fnc, 
			  matr * T, extvec * V, extvec *& X);

struct solver {
	virtual size_t solve(matr * T, const extvec * V, extvec *& X) = 0;
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
void axpy(REAL a, const extvec & x, extvec & y);

// y = x + ay
SURFIT_EXPORT
void xpay(REAL a, const extvec & x, extvec & y);

SURFIT_EXPORT
REAL threaded_times(const extvec * a, const extvec * b);
#endif

extvec *     RF(matr * A, const extvec * b, int max_it, REAL tol, extvec * X, size_t & iters, REAL undef_value = FLT_MAX);
extvec *     CG(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX);
extvec *      J(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX);
extvec *    JCG(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX);
extvec *   SSOR(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX, REAL omega = REAL(1.6));
extvec * SSORCG(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX, REAL omega = REAL(1.6));

};

#endif

