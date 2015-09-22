
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

#include "fileio.h"

#include "functional.h"
#include "matr.h"
#include "free_elements.h"
#include "vec.h"
#include "grid_line.h"
#include "intvec.h"
#include "bitvec.h"

#include "grid_user.h"

#include <string.h>
#include <stdarg.h>
#include <assert.h>

namespace surfit {

functional::functional(const char * newname, int itype) {
	name = NULL;
	setName(newname);
	functionals_add = new std::vector<functional *>;
	weights = new std::vector<REAL>();
	functionals_cond = new std::vector<functional *>;
	type = itype;
	pos = INT_MAX;
};

functional::~functional() {
	free(name);
	delete weights;
	release_elements(functionals_add->begin(), functionals_add->end());
	delete functionals_add;
	delete functionals_cond;
};

void functional::release() {
	delete this;
};

void functional::setName(const char * newname) {
	if (!newname)
		return;
	if (name) {
		free(name);
		name = NULL;
	}

	name = (char *)malloc(strlen(newname) + 1);
	strcpy(name, newname);
};

void functional::setNameF(const char *tmplt, ...) {
	va_list ap;
	va_start (ap, tmplt);
	char buf[1024];
	int written = vsprintf(buf,tmplt,ap);
	setName(buf);
};

const char * functional::getName() const {
	return name;
};

int functional::getType() const {
	return type;
};

void functional::setType(int itype) 
{
	type = itype;
};

void functional::add_functional(functional * isum, REAL iweights) {
	if (isum->getType() == F_MODIFIER)
	{
		assert(0);
		return;
	}
	isum->set_pos(get_pos());
	functionals_add->push_back(isum);
	weights->push_back(iweights);
};

bool functional::wrap_sums(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined) {
	if (functionals_add->size() == 0)
		return false;

	bool solvable = false;
	
	size_t size = functionals_add->size();
	std::vector<matr *> * matrs = new std::vector<matr *>(size+1);
	size_t i, q;

	for (q = 0; q < size; q++) {
		functional * f = (*functionals_add)[q];
		matr * sum_T = NULL;
		extvec * sum_vector = NULL;
		solvable = f->make_matrix_and_vector(sum_T, sum_vector, mask_solved, mask_undefined) || solvable;

		(*matrs)[q] = sum_T;

		REAL w = (*weights)[q];
		if (sum_vector) {
			for (i = 0; i < v->size(); i++) 
				(*v)(i) += w * (*sum_vector)(i);
			if (sum_vector)
				sum_vector->release();
		}

	}

	(*matrs)[size] = matrix;
	
	std::vector<REAL> * my_weights = new std::vector<REAL>(*weights);
	my_weights->push_back(1);

	matr_sums * sums = new matr_sums(my_weights, matrs);
	matrix = sums;
	return solvable;

};

void functional::mark_sums(bitvec * mask_solved, bitvec * mask_undefined) {
	
	int q;
	for (q = 0; q < (int)functionals_add->size(); q++) {
		functional * f = (*functionals_add)[q];
		f->mark_solved_and_undefined(mask_solved, mask_undefined, false);		
	}

};

void functional::info() {
	writelog(LOG_MESSAGE, "%s", getName());
	if (functionals_add->size() > 0) {
		int q;
		for (q = 0; q < (int)functionals_add->size(); q++) {
			functional * f = (*functionals_add)[q];
			REAL weight = (*weights)[q];
			writelog(LOG_MESSAGE, "\t + %g %s", weight, f->getName());
		};
	};
};

// cond
void functional::cond_add(functional * icond) {
	if (icond->getType() == F_MODIFIER)
		return;
	functionals_cond->push_back(icond);
};

void functional::cond_move(functional * fnc) {
	if ( fnc->cond() ) {
		int i;
		for (i = 0; i < fnc->cond_size(); i++) {
			functional * cnd = fnc->cond_get(i);
			cond_add(cnd);
		}
	}
	fnc->cond_erase_all();
};

int functional::cond_size() const {
	return functionals_cond->size();
};

functional * functional::cond_get(int pos) {
	return (*functionals_cond)[pos];
};

void functional::cond_erase_all() {
	functionals_cond->resize(0);
};

void functional::add_erase_all() {
	functionals_add->resize(0);
};

bool functional::cond() const {
	return (functionals_cond->size() > 0);
};

void functional::cond_mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined) {
	int i;
	for (i = 0; i < (int)functionals_cond->size(); i++) {
		functional * cond = (*functionals_cond)[i];
		cond->mark_solved_and_undefined(mask_solved, mask_undefined, true);
	}
};

bool functional::cond_make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * parent_mask, bitvec * mask_solved, bitvec * mask_undefined) 
{
	matrix = NULL;
	v = NULL;
	if ( !cond() ) 
		return false;
	
	bool res = true;
	size_t matrix_size = method_basis_cntX*method_basis_cntY;

	std::vector<matr *> * matrices = new std::vector<matr*>;
	std::vector<REAL> * weights = new std::vector<REAL>();
	v = create_extvec(matrix_size);

	size_t i,j;
	for (i = 0; i < functionals_cond->size(); i++) {
		functional * cond = (*functionals_cond)[i];
		matr * P_matr = NULL;
		extvec * P_v = NULL;
		res = cond->make_matrix_and_vector(P_matr,P_v,mask_solved,mask_undefined) && res;

		if (P_matr == NULL)
			continue;

		matrices->push_back(P_matr);
		weights->push_back(1);

		if (P_v) {
			for (j = 0; j < matrix_size; j++) {
				if (parent_mask) {
					if (parent_mask->get(j) == true)
						(*v)(j) += (*P_v)(j);
				} else 
					(*v)(j) += (*P_v)(j);
			};
			if (P_v)
				P_v->release();
		}

	}

	if (weights->size() == 0) {
		delete matrices;
		delete weights;
		matrix = NULL;
		v->release();
		v = NULL;
		return false;
	}

	matr * T = NULL;
	if (weights->size() > 1)
		T = new matr_sums(weights, matrices);
	if (weights->size() == 1) {
		T = (*matrices)[0];
		delete matrices;
		delete weights;
	}
			
	if (parent_mask->true_size() != parent_mask->size()) {
		matr_mask * M = new matr_mask(parent_mask, T); // !!! 
		matrix = M;
	} else
		matrix = T;
	
	return res;

};

bool functional::cond_solvable(const bitvec * mask_solved, 
			       const bitvec * mask_undefined, 
			       const extvec * X) 
{
	if (functionals_cond->size() == 0)
		return true;

	int i;
	for (i = 0; i < (int)functionals_cond->size(); i++) {
		functional * cond = (*functionals_cond)[i];
		bool res2 = cond->solvable(mask_solved, mask_undefined, X);
		if (res2 == false) 
			return false;
	}
	return true;
}

void functional::cond_erase(int pos) {
	functionals_cond->erase( functionals_cond->begin()+pos );
};

int functional::get_add_data_count() const {
	int cnt = 0;
	int i;
	for (i = 0; i < (int)functionals_add->size(); i++) {
		functional * f = (*functionals_add)[i];
		cnt += f->get_data_count();
	}
	return cnt;
};
	
const data * functional::get_add_data(int pos) const {
	int cnt = 0;
	int i;
	for (i = 0; i < (int)functionals_add->size(); i++) {
		functional * f = (*functionals_add)[i];
		cnt += f->get_data_count();
		if (cnt > pos) 
			return f->get_data(pos);
		pos -= cnt;
	}
	return NULL;
};

int functional::get_data_count() const {
	return this_get_data_count() + get_add_data_count();
};

const data * functional::get_data(int pos) const {
	int this_size = this_get_data_count();
	if (pos < this_size) 
		return this_get_data(pos);

	pos -= this_size;
	return get_add_data(pos);
};

bool functional::solvable(const bitvec * mask_solved,
			  const bitvec * mask_undefined,
			  const extvec * X) 
{
	if ( cond() )
		return cond_solvable(mask_solved, mask_undefined, X);

	bool res = solvable_without_cond(mask_solved, mask_undefined, X);
	
	if (res == false)
		return false;

	return true;
};

void functional::drop_private_data() {};

void functional::cleanup() {};

size_t functional::get_pos() const
{
	return pos;
};

void functional::set_pos(size_t ipos)
{
	pos = ipos;
};

functional * functional::get_last_added() const {
	if (functionals_add->size() == 0)
		return NULL;
	return (*functionals_add)[functionals_add->size()-1];
};

void set_solved(bitvec * mask_solved, bitvec * mask_undefined) {
	size_t N = mask_solved->size();
	size_t i;
	for (i = 0; i < N; i++) {
		if (mask_undefined->get(i) == false)
			mask_solved->set_true(i);
	}
};

void set_undefined(bitvec * mask_solved, bitvec * mask_undefined) {
	size_t N = mask_solved->size();
	size_t i;
	for (i = 0; i < N; i++) {
		if (mask_solved->get(i) == false)
			mask_undefined->set_true(i);
	}
};

REAL get_mult(REAL speed)
{
	// 0 - average speed, mult == 1
	REAL res = pow(10., (double)speed);
	return res;
};

}; // namespace surfit;
