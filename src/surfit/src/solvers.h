
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

//! solves system of linear equations T*X=V with current solver
SURFIT_EXPORT
size_t solve(matr * T, const extvec * V, extvec *& X);

//! solves system of linear equations T*X=V with corrent solver with respect to given functional
SURFIT_EXPORT
bool solve_with_penalties(functional * fnc, 
			  matr * T, extvec * V, extvec *& X);

//! interface class for all supported systems of linear equations solvers
struct solver {
	//! solves system of linear equations T*X=V
	virtual size_t solve(matr * T, const extvec * V, extvec *& X) = 0;
	//! returns solvers long name
	virtual const char * get_long_name() const = 0;
	//! returns solvers short name
	virtual const char * get_short_name() const = 0;
};

//! adds solver to the solvers collection
SURFIT_EXPORT
bool add_solver(solver * slvr);

//! removes solver from the solvers collection
SURFIT_EXPORT
bool remove_solver(solver * slvr);

//! returns number of solvers in solvers collection
SURFIT_EXPORT
int get_solvers_count();

//! returns solvers long name by its number in solvers collection
SURFIT_EXPORT
const char * get_solver_long_name(int pos);

//! returns solvers short name by its number in solvers collection
SURFIT_EXPORT
const char * get_solver_short_name(int pos);

//! returns short name of the current solver
SURFIT_EXPORT
const char * get_current_solver_short_name();

//! returns long name of the current solver
SURFIT_EXPORT
const char * get_current_solver_long_name();

//! sets current solver by short name
SURFIT_EXPORT
void set_solver(const char * short_name);

//! prints information about available solvers
SURFIT_EXPORT
void solvers_info();

#ifdef HAVE_THREADS
//! y = ax + y
SURFIT_EXPORT
void axpy(REAL a, const extvec & x, extvec & y);

//! y = x + ay
SURFIT_EXPORT
void xpay(REAL a, const extvec & x, extvec & y);

//! multithreading version for "times" operation
SURFIT_EXPORT
REAL threaded_times(const extvec * a, const extvec * b);
#endif

//! implementation of RF solver
extvec *     RF(matr * A, const extvec * b, int max_it, REAL tol, extvec * X, size_t & iters, REAL undef_value = FLT_MAX);

//! implementation of Conjugate Gradients method
extvec *     CG(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX);

//! implementation of Jacobi method
extvec *      J(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX);

//! implementation of Jacobi-Conjugate Gradients method
extvec *    JCG(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX);

//! implementation of SSOR method
extvec *   SSOR(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX, REAL omega = REAL(1.6));

//! implementation of SSOR-CG method
extvec * SSORCG(matr * A, const extvec * b, int max_it, REAL tol, extvec *& X, size_t & iters, REAL undef_value = FLT_MAX, REAL omega = REAL(1.6));

};

#endif

