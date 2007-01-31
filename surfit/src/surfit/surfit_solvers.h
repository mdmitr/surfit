
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

#ifndef __surfit__surfit_solvers__
#define __surfit__surfit_solvers__

#include "solvers.h"

#include "variables.h"
#include "variables_tcl.h"
#include "vec.h"

namespace surfit {

#define SOLVER_MAX_ITER          40

struct solver_rf : public solver {
	solver_rf() {
		add_solver(this);
	}
	~solver_rf() {
		remove_solver(this);
	}
	virtual void solve(matr * T, const extvec * V, extvec *& X) { 
		X = RF(T,V,V->size()*SOLVER_MAX_ITER,tol,X);
	};
	virtual const char * get_short_name() const { return "rf"; };
	virtual const char * get_long_name() const { return "Richardson's method with Fixed parameter - Optimally Extrapolated"; };
};


struct solver_cg : public solver {
	solver_cg() {
		add_solver(this);
		set_solver("cg");
	}
	~solver_cg() {
		remove_solver(this);
	}
	virtual void solve(matr * T, const extvec * V, extvec *& X) { 
		X = CG(T,V,V->size()*SOLVER_MAX_ITER,tol,X,FLT_MAX);
	};
	virtual const char * get_short_name() const { return "cg"; };
	virtual const char * get_long_name() const { return "Conjugate Gradients"; };
};

struct solver_jacobi : public solver {
	solver_jacobi() {
		add_solver(this);
	}
	~solver_jacobi() {
		remove_solver(this);
	}
	virtual void solve(matr * T, const extvec * V, extvec *& X) { 
		X = J(T,V,V->size()*SOLVER_MAX_ITER,tol,X);
	};
	virtual const char * get_short_name() const { return "jacobi"; };
	virtual const char * get_long_name() const { return "Jacobi"; };
};

struct solver_jcg : public solver {
	solver_jcg() {
		add_solver(this);
	}
	~solver_jcg() {
		remove_solver(this);
	}
	virtual void solve(matr * T, const extvec * V, extvec *& X) { 
		X = JCG(T,V,V->size()*SOLVER_MAX_ITER,tol,X,FLT_MAX);
	};
	virtual const char * get_short_name() const { return "jcg"; };
	virtual const char * get_long_name() const { return "Jacobi Conjugate Gradients"; };
};

struct solver_ssor : public solver {
	solver_ssor() {
		add_solver(this);
	}
	~solver_ssor() {
		remove_solver(this);
	}
	virtual void solve(matr * T, const extvec * V, extvec *& X) { 
		X = SSOR(T,V,V->size()*SOLVER_MAX_ITER,tol,X);
	};
	virtual const char * get_short_name() const { return "ssor"; };
	virtual const char * get_long_name() const { return "Symmetric Successive OverRelaxation"; };
};

}; // namespace surfit;

#endif


