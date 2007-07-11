
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
#include "variables_internal.h"
#include "fileio.h"

#include "grid_user.h"
#include "matr.h"
#include "vec.h"
#include "vec_alg.h"
#include "functional.h"
#include "bitvec.h"
#include "intvec.h"
#include "threads.h"

#include <time.h>
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
	size_t i;
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
	size_t i;
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
	size_t i;
	for (i = 0; i < solvers.size(); i++) {
		solver * slvr = solvers[i];
		const char * short_name = slvr->get_short_name();
		const char * long_name = slvr->get_long_name();
		Tcl_printf("%s : \t %s\n", long_name, short_name);				
	}
};

#ifdef DEBUG
static int debug_cnt = 0;
int get_real_index(std::vector<int> * zero_rows, int pos, int max)
{
	int cnt = zero_rows->size();
	int res = 0;
	int i;
	for (i = 0; i < max; i++) {
		if ( std::find(zero_rows->begin(), zero_rows->end(), i) == zero_rows->end() )
			pos--;
		
		if (pos == 0)
			break;

		res++;

	}
	return res;
}
#endif
size_t solve(matr * T, const extvec * V, extvec *& X) {

#ifdef DEBUG
	/*
	if (true) {
		std::vector<int> zero_rows;
		T->get_zero_rows(zero_rows);
		T->writeMAT("c:\\matr.mat","A",&zero_rows,false);
		matlabWriteVector(V->const_begin(), V->const_end(), "c:\\matr.mat","b",&zero_rows);
	}
	//*/
	/*
	{
		writelog(LOG_DEBUG,"checking for matrix symmety...");
		size_t i, j;
		for (i = 0; i < T->rows(); i++) {
			for (j = i; j < T->rows();) {
				///*
				size_t next_j;
				REAL val2 = T->at(j,i);
				REAL val1 = T->at(i,j,&next_j);
				if (val1 != val2) {
					val2 = T->at(j,i);
					val1 = T->at(i,j,&next_j);
				}
				assert(val1 == val2);
				if (j == next_j) {
					bool stop = true;
					T->at(i,j,&next_j);
				}
				assert(j != next_j);
				j = next_j;
			}
		}
	}
	//*/
	
#endif

	if (solver_name == NULL) {
		writelog(LOG_ERROR,"Solver not found!");
		return 0;
	}
	bool solved = false;
	size_t iters = 0;
	size_t i;
	for (i = 0; i < solvers.size(); i++) {
		solver * slvr = solvers[i];
		const char * name = slvr->get_short_name();
		if ( strcmp(name, solver_name) != 0 )
			continue;
		iters = slvr->solve(T, V, X);
		solved = true;
		break;
	}
	if (!solved)
		writelog(LOG_ERROR,"Solver not found!");
	return iters;
};

bool penalty_solvable(functional * fnc, const extvec * X)
{
	// create empty masks for testing functionals
	bitvec * test_mask_solved = create_bitvec(method_mask_solved->size());
	test_mask_solved->init_false();
	bitvec * test_mask_undefined = create_bitvec(method_mask_solved->size());
	test_mask_undefined->init_false();

	fnc->cond_mark_solved_and_undefined(test_mask_solved, test_mask_undefined);
	bool res = fnc->solvable_without_cond(test_mask_solved, test_mask_undefined, X);
	if (res == false) {
		test_mask_solved->init_false();
		test_mask_undefined->init_false();
		fnc->mark_solved_and_undefined(test_mask_solved, test_mask_undefined, false);
	}

	bool res2 = res || fnc->solvable(test_mask_solved, test_mask_undefined, X);

	if (res2) {
		test_mask_solved->copy(method_mask_solved);
		test_mask_undefined->copy(method_mask_undefined);
		fnc->mark_solved_and_undefined(test_mask_solved, test_mask_undefined, false);
		res2 = fnc->cond_solvable(test_mask_solved, test_mask_undefined, X);
	}

	if (test_mask_solved)
		test_mask_solved->release();
	if (test_mask_undefined)
		test_mask_undefined->release();
	
	return res2;
};

bool solve_with_penalties(functional * fnc, matr * T, extvec * V, extvec *& X) 
{
	int prev_loglevel = loglevel;
	loglevel = LOG_SILENT;

	// check for possibility of applying penalty algorithm
	bool solvable = penalty_solvable(fnc, X);

	if (solvable == false) {
		delete T; 
		if (V)
			V->release();
		loglevel = prev_loglevel;
		return false;
	}
					
	REAL weight = penalty_weight;
	REAL x_norm = norm2(X, FLT_MAX);
	
	bitvec * parent_mask = create_bitvec(method_mask_solved->size());
	parent_mask->init_false();
	bitvec * fake_mask = create_bitvec(method_mask_solved->size());
	fake_mask->init_false();
	fnc->mark_solved_and_undefined(parent_mask, fake_mask, false);
	fake_mask->copy(method_mask_undefined);
	bitvec * fake_mask2 = create_bitvec(method_mask_solved);
	fnc->mark_solved_and_undefined(fake_mask2, fake_mask, false);
	fake_mask2->release();
		
	REAL from = FLT_MAX;
	REAL to = FLT_MAX;
	REAL step = FLT_MAX;
	short prp = 0;
	size_t iters = 0;

	time_t ltime_begin;
	time( &ltime_begin );

	REAL penalty_tol = tol;

	std::vector<REAL> norms;
	norms.reserve(penalty_max_iter);

	penalty_iter_counter = 0;

	bool ok = false;
	while (!ok) 
	{
		matr * S_matrix = NULL;
		extvec * S_vec = NULL;
		matr * P_matrix = NULL;
		extvec * P_vec = NULL;
		if (penalty_iter_counter == 0) 
			loglevel = prev_loglevel;

		if (penalty_iter_counter == 0) 
			loglevel = LOG_SILENT;

		if (penalty_iter_counter == 0) {
			loglevel = prev_loglevel;
			writelog(LOG_MESSAGE,"processing with penalties : ");
			loglevel = LOG_SILENT;
		}

		bool res = false;
		
		if (penalty_iter_counter == 0) {
			loglevel = prev_loglevel;
			res = fnc->cond_make_matrix_and_vector(P_matrix, P_vec, parent_mask, method_mask_solved, fake_mask);
			writelog2(LOG_MESSAGE,"penalty algorithm progress : ");
			loglevel = LOG_SILENT;
		} else
			res = fnc->cond_make_matrix_and_vector(P_matrix, P_vec, parent_mask, method_mask_solved, fake_mask);
	
					
		size_t matrix_size = X->size();
			
		if (P_matrix != NULL) {
			matr_sum * S_matr = new matr_sum(1, T, weight, P_matrix);
			S_matr->set_const(); // leave matrix T undeleted
			S_matrix = S_matr;

			S_vec = create_extvec(P_vec->size(),0,0);

			size_t i;
			if (V) {
				for (i = 0; i < matrix_size; i++)
					(*S_vec)(i) = (*P_vec)(i)*weight + (*V)(i);
			} else {
				for (i = 0; i < matrix_size; i++)
					(*S_vec)(i) = (*P_vec)(i)*weight;
			}
		} else {
			S_matrix = T;
			S_vec = V;
			ok = true;
		}

		if (S_matrix == NULL)
			break;
		
		iters += solve(S_matrix, S_vec, X);
		penalty_iter_counter++;
		
		if (P_matrix != NULL) {
			delete S_matrix;
			if (S_vec)
				S_vec->release();

			delete P_matrix;
			if (P_vec)
				P_vec->release();
		}
				
		weight *= penalty_weight_mult;
		
		REAL new_norm = norm2(X, FLT_MAX);
		REAL error = FLT_MAX;
		size_t q;
		for (q = 0; q < norms.size(); q++) {
			REAL old_norm = norms[q];
			REAL err = fabs(new_norm - old_norm);
			error = MIN(err, error);
		}
		norms.push_back(new_norm);

		if (from == FLT_MAX) {
			from = log10(REAL(1)/error);
			to = log10(REAL(1)/penalty_tol);
			step = (to-from)/REAL(PROGRESS_POINTS+1);
			prp = 0;
		}

		REAL prp_pos = (log10(REAL(1)/error)-from)/step;
		if (prp_pos > prp ) {
			short new_prp =MIN(PROGRESS_POINTS,short(prp_pos));
			short prp_cnt;
			loglevel = prev_loglevel;
			for (prp_cnt = 0; prp_cnt < new_prp-prp; prp_cnt++)
				log_printf(".");
			loglevel = LOG_SILENT;
			prp = (short)prp_pos;
		}

		if ( error <= penalty_tol ) 
			ok = true;
		else
			x_norm = new_norm;

		if ((penalty_iter_counter > penalty_max_iter) || (stop_execution == true))
			ok = true;

		if (stop_execution == true)
			ok = true;
	
	}

	if (parent_mask)
		parent_mask;
	if (fake_mask)
		fake_mask->release();
	delete T;
	if (V)
		V->release();

	time_t ltime_end;
	time( &ltime_end );

	double sec = difftime(ltime_end,ltime_begin);
	int minutes = (int)(sec/REAL(60));
	sec -= minutes*60;

	loglevel = prev_loglevel;
	log_printf(" %s: %d iterations, penalty: %d iterations, %d min %G sec\n", get_current_solver_short_name(), iters, penalty_iter_counter, minutes, sec);
	penalty_iter_counter = 0;
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
	void set(REAL ia, const extvec * ix, extvec * iy, size_t ifrom, size_t ito)
	{
		a = ia;
		x = ix;
		y = iy;
		from = ifrom;
		to = ito;
	};

	virtual void do_job()
	{
		size_t i;
		for (i = from; i < to; i++) {
			(*y)(i) += a*(*x)(i);
		}
	}

	REAL a;
	const extvec * x;
	extvec * y;
	size_t from, to;

};

axpy_job axpy_jobs[MAX_CPU];

void axpy(REAL a, const extvec & x, extvec & y)
{
	int m = 1;
	size_t N = x.size();
	size_t step = N/(sstuff_get_threads()*m);
	size_t ost = N % (sstuff_get_threads()*m);
	size_t J_from = 0;
	size_t J_to = 0;
	size_t i;
	for (i = 0; i < (size_t)(sstuff_get_threads()*m); i++) {
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
	void set(REAL ia, const extvec * ix, extvec * iy, size_t ifrom, size_t ito)
	{
		a = ia;
		x = ix;
		y = iy;
		from = ifrom;
		to = ito;
	};

	virtual void do_job()
	{
		size_t i;
		for (i = from; i < to; i++) {
			(*y)(i) = (*x)(i) + a*(*y)(i);
		}
	}

	REAL a;
	const extvec * x;
	extvec * y;
	size_t from, to;

};

xpay_job xpay_jobs[MAX_CPU];

void xpay(REAL a, const extvec & x, extvec & y)
{
	size_t N = x.size();
	size_t step = N/(sstuff_get_threads());
	size_t ost = N % (sstuff_get_threads());
	size_t J_from = 0;
	size_t J_to = 0;
	size_t i;
	for (i = 0; i < (size_t)sstuff_get_threads(); i++) {
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
#ifndef XXL
		a = NULL;
		b = NULL;
#endif
		size = 0;
		res = 0;
	}

	void set(extvec::const_iterator ia, extvec::const_iterator ib, int isize) 
	{
		a = ia;
		b = ib;
		size = isize;
	}

	virtual void do_job() 
	{
		res = 0;
		size_t i;
		for (i = 0; i < size; i++) 
			res += *(a+i) * *(b+i);
	}
	extvec::const_iterator a;
	extvec::const_iterator b;
	size_t size;
	REAL res;
};

times_job times_jobs[MAX_CPU];

REAL threaded_times(const extvec * a, const extvec * b)
{
	size_t N = a->size();
	size_t step = N/(sstuff_get_threads());
	size_t ost = N % (sstuff_get_threads());
	size_t J_from = 0;
	size_t J_to = 0;
	size_t i;
	for (i = 0; i < (size_t)sstuff_get_threads(); i++) {
		J_to = J_from + step;
		if (i == 0)
			J_to += ost;
		times_job & f = times_jobs[i];
		f.set(a->const_begin()+J_from, b->const_begin()+J_from, J_to - J_from);
		set_job(&f, i);
		J_from = J_to;
	}

	do_jobs();

	REAL res = 0;
	for (i = 0; i < (size_t)sstuff_get_threads(); i++) {
		times_job & f = times_jobs[i];
		res += f.res;
	}

	res = times(a,b);

	return res;
};
#endif // HAVE_THREADS

}; // namespace surfit;


