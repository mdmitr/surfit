
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

#include "surfit_ie.h"
#include "solvers.h"
#include "surfit_solvers.h"
#include "variables.h"
#include "variables_tcl.h"
#include "fileio.h"

#include "grid_user.h"
#include "matr.h"
#include "vec.h"
#include "vec_alg.h"
#include "functional.h"
#include "bitvec.h"
#include "intvec.h"
#include "surfit_threads.h"

#include <vector>
#include <algorithm>

namespace surfit {

static std::vector<solver *> solvers;
static solver_rf	solver_0;
static solver_cg	solver_1;
static solver_jacobi	solver_2;
static solver_jcg	solver_3;
static solver_ssor	solver_4;

bool add_solver(solver * slvr) {
	std::vector<solver *>::iterator it;
	it = std::find(solvers.begin(), solvers.end(), slvr);
	if (it != solvers.end())
		return false;
	solvers.push_back(slvr);
	return true;
};

bool remove_solver(solver * slvr) {
	std::vector<solver *>::iterator it;
	it = std::find(solvers.begin(), solvers.end(), slvr);
	if (it == solvers.end())
		return false;
	solvers.erase(it);
	return true;
};

void set_solver(const char * short_name) {
	if (solver_name)
		free(solver_name);
	solver_name = strdup(short_name);
};

int get_solvers_count() {
	return (int)solvers.size();
};

const char * get_solver_long_name(int pos) {
	solver * s = solvers[pos];
	if (s)
		return s->get_long_name();
	return NULL;
};

const char * get_solver_short_name(int pos) {
	solver * s = solvers[pos];
	if (s)
		return s->get_short_name();
	return NULL;
};

const char * get_current_solver_short_name() {
	if (solver_name == NULL)
		return NULL;
	unsigned int i;
	for (i = 0; i < solvers.size(); i++) {
		solver * slvr = solvers[i];
		const char * name = slvr->get_short_name();
		if ( strcmp(name, solver_name) != 0 )
			continue;
		return slvr->get_short_name();
	}
	return NULL;
};

const char * get_current_solver_long_name() {
	if (solver_name == NULL)
		return NULL;
	unsigned int i;
	for (i = 0; i < solvers.size(); i++) {
		solver * slvr = solvers[i];
		const char * name = slvr->get_short_name();
		if ( strcmp(name, solver_name) != 0 )
			continue;
		return slvr->get_long_name();
	}
	return NULL;
};

void solvers_info() {
	unsigned int i;
	for (i = 0; i < solvers.size(); i++) {
		solver * slvr = solvers[i];
		const char * short_name = slvr->get_short_name();
		const char * long_name = slvr->get_long_name();
		Tcl_printf("%s : \t %s\n", long_name, short_name);				
	}
};

void solve(matr * T, const vec * V, vec *& X) {

	if (solver_name == NULL) {
		writelog(LOG_ERROR,"Solver not found!");
		return;
	}
	bool solved = false;
	unsigned int i;
	for (i = 0; i < solvers.size(); i++) {
		solver * slvr = solvers[i];
		const char * name = slvr->get_short_name();
		if ( strcmp(name, solver_name) != 0 )
			continue;
		slvr->solve(T, V, X);
		solved = true;
		break;
	}
	if (!solved)
		writelog(LOG_ERROR,"Solver not found!");
};

bool solve_with_penalties(functional * fnc, matr * T, vec * V, vec *& X) {
		
	bitvec * test_mask_solved = create_bitvec(method_mask_solved);
	test_mask_solved->init_false();
	bitvec * test_mask_undefined = create_bitvec(method_mask_solved);
	test_mask_undefined->init_false();

	fnc->cond_mark_solved_and_undefined(test_mask_solved, test_mask_undefined);
	bool res = fnc->solvable_without_cond(test_mask_solved, test_mask_undefined, X);
	if (res)
		fnc->mark_solved_and_undefined(test_mask_solved, test_mask_undefined, false);

	bool res2 = fnc->solvable(test_mask_solved, test_mask_undefined, X) || res;

	if (res2 == false) {
		if (test_mask_solved)
			test_mask_solved->release();
		if (test_mask_undefined)
			test_mask_undefined->release();
		delete T; 
		if (V)
			V->release();
		return false;
	}
	
	test_mask_solved->copy(method_mask_solved);
	test_mask_undefined->copy(method_mask_undefined);
	fnc->mark_solved_and_undefined(test_mask_solved, test_mask_undefined, false);
	res = fnc->cond_solvable(test_mask_solved, test_mask_undefined, X);
			
	if (test_mask_solved)
		test_mask_solved->release();
	if (test_mask_undefined)
		test_mask_undefined->release();

	if (res2 == false) {
		delete T; 
		if (V)
			V->release();
		return false;
	}
	
	REAL weight = penalty_weight;
	REAL x_norm = norm2(X, FLT_MAX);
	int counter = 0;

	bitvec * parent_mask = create_bitvec(method_mask_solved->size());
	parent_mask->init_false();
	fnc->mark_solved_and_undefined(parent_mask, parent_mask, false);

	bool ok = false;
	while (!ok) {

		matr * P_matrix = NULL;
		vec * P_vec = NULL;
		fnc->cond_make_matrix_and_vector(P_matrix, P_vec, parent_mask);
		
		if (counter == 0)
			writelog(LOG_MESSAGE,"processing with penalties...");
		//else
		//	writelog(LOG_MESSAGE,"processing with penalties : %d iteration", counter);
		
		int matrix_size = X->size();
		
		
		matr_sum * S_matrix = new matr_sum(1, T, weight, P_matrix);
		S_matrix->set_const();

		vec * S_vec = create_vec(P_vec->size(),0,0);

		int i;
		for (i = 0; i < matrix_size; i++) {
			(*S_vec)(i) = (*P_vec)(i)*weight + (*V)(i);
		};
		
		
		solve(S_matrix, S_vec, X);
		counter++;
		
		delete S_matrix;
		if (S_vec)
			S_vec->release();
				
		weight *= penalty_weight_mult;
		
		REAL new_norm = norm2(X, FLT_MAX);
		if ( fabs(x_norm - new_norm) <= tol ) 
			ok = true;
		else
			x_norm = new_norm;

		if ((counter > penalty_max_iter) || (stop_execution == 1))
			ok = true;
		
		delete P_matrix;
		if (P_vec)
			P_vec->release();
	
	}

	if (parent_mask)
		parent_mask->release();
	delete T;
	if (V)
		V->release();
	return true;
	
};

#ifdef HAVE_THREADS
struct axpy_job : public job
{
	axpy_job()
	{
		a = 0;
		x = NULL;
		y = NULL;
		from = 0;
		to = 0;
	}
	void set(REAL ia, const vec * ix, vec * iy, unsigned int ifrom, unsigned int ito)
	{
		a = ia;
		x = ix;
		y = iy;
		from = ifrom;
		to = ito;
	};

	virtual void do_job()
	{
		unsigned int i;
		for (i = from; i < to; i++) {
			(*y)(i) += a*(*x)(i);
		}
	}

	REAL a;
	const vec * x;
	vec * y;
	unsigned int from, to;

};

axpy_job axpy_jobs[MAX_CPU];

void axpy(REAL a, const vec & x, vec & y)
{
	int m = 1;
	unsigned int N = x.size();
	unsigned int step = N/(cpu*m);
	unsigned int ost = N % (cpu*m);
	unsigned int J_from = 0;
	unsigned int J_to = 0;
	unsigned int i;
	for (i = 0; i < cpu*m; i++) {
		J_to = J_from + step;
		if (i == 0)
			J_to += ost;
		axpy_job & f = axpy_jobs[i];
		f.set(a, &x, &y, J_from, J_to);
		set_job(&f, i);
		J_from = J_to;
	}

	do_jobs();
};

struct xpay_job : public job
{
	xpay_job() 
	{
		a = 0;
		x = NULL;
		y = NULL;
		from = 0;
		to = 0;
	}
	void set(REAL ia, const vec * ix, vec * iy, unsigned int ifrom, unsigned int ito)
	{
		a = ia;
		x = ix;
		y = iy;
		from = ifrom;
		to = ito;
	};

	virtual void do_job()
	{
		unsigned int i;
		for (i = from; i < to; i++) {
			(*y)(i) = (*x)(i) + a*(*y)(i);
		}
	}

	REAL a;
	const vec * x;
	vec * y;
	unsigned int from, to;

};

xpay_job xpay_jobs[MAX_CPU];

void xpay(REAL a, const vec & x, vec & y)
{
	unsigned int N = x.size();
	unsigned int step = N/(cpu);
	unsigned int ost = N % (cpu);
	unsigned int J_from = 0;
	unsigned int J_to = 0;
	unsigned int i;
	for (i = 0; i < cpu; i++) {
		J_to = J_from + step;
		if (i == 0)
			J_to += ost;
		xpay_job & f = xpay_jobs[i];
		f.set(a, &x, &y, J_from, J_to);
		set_job(&f, i);
		J_from = J_to;
	}

	do_jobs();
};

struct times_job : public job
{
	times_job()
	{
		a = NULL;
		b = NULL;
		size = 0;
		res = 0;
	}

	void set(const REAL * ia, const REAL * ib, int isize) 
	{
		a = ia;
		b = ib;
		size = isize;
	}

	virtual void do_job() 
	{
		res = 0;
		unsigned int i;
		for (i = 0; i < size; i++) 
			res += *(a+i) * *(b+i);
	}
	const REAL * a;
	const REAL * b;
	unsigned int size;
	REAL res;
};

times_job times_jobs[MAX_CPU];

REAL threaded_times(const vec * a, const vec * b)
{
	unsigned int N = a->size();
	unsigned int step = N/(cpu);
	unsigned int ost = N % (cpu);
	unsigned int J_from = 0;
	unsigned int J_to = 0;
	unsigned int i;
	for (i = 0; i < cpu; i++) {
		J_to = J_from + step;
		if (i == 0)
			J_to += ost;
		times_job & f = times_jobs[i];
		f.set(a->begin()+J_from, b->begin()+J_from, J_to - J_from);
		set_job(&f, i);
		J_from = J_to;
	}

	do_jobs();

	REAL res = 0;
	for (i = 0; i < cpu; i++) {
		times_job & f = times_jobs[i];
		res += f.res;
	}

	res = times(a,b);

	return res;
};
#endif // HAVE_THREADS

}; // namespace surfit;

