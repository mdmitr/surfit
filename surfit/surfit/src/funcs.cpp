
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

#include "ie.h"
#include "real.h"
#include "funcs.h"
#include "func.h"
#include "func_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "free_elements.h"

#include "func_user.h"

#include <vector>

namespace surfit {

bool funcs_delall() {

	if (surfit_funcs->size() == 0) {
		return false;
	}
	
	free_elements(surfit_funcs->begin(), surfit_funcs->end());
	surfit_funcs->resize(0);

	return true;
};

bool funcs_del(int pos) {
	if ((int)surfit_funcs->size() <= pos) {
		writelog(SURFIT_ERROR,"funcs_del : wrong pos");
		return false;
	}

	_func_unload(*(surfit_funcs->begin()+pos));
	surfit_funcs->erase(surfit_funcs->begin()+pos);

	return true;
};

bool funcs_unload(const char * name) {
	unsigned int i;

	if (surfit_funcs->size() == 0) {
		writelog(SURFIT_WARNING,"funcs_delall : empty surfit_funcs");
		return false;
	}
	
	func * fnc = NULL;
	for (i = 0; i < surfit_funcs->size(); i++) {
		fnc = *(surfit_funcs->begin()+i);
		if (fnc->getName()) {
			if ( strcmp(fnc->getName(),name) == 0 ) {
				return funcs_del(i);
			}
		}
	}
	
	return false;
};


bool funcs_load(const char * filename, const char * funcname) {
	func * fnc = _func_load(filename, funcname, get_rw_mode());
	if (!fnc)
		return false;

	std::vector< func* > * aa;
	aa = surfit_funcs;
	surfit_funcs->push_back(fnc);
	std::vector<func *> * bb = surfit_funcs;
	return true;
};

bool funcs_load_grd(const char * filename, const char * funcname) {
	func * fnc = _func_load_grd(filename, funcname);
	if (!fnc)
		return false;

	surfit_funcs->push_back(fnc);
	return true;
};

func * funcs_at(int pos) {
	if (pos >= (int)surfit_funcs->size()) {
		writelog(SURFIT_ERROR,"funcs_at : wrong pos");
		return NULL;
	}
	return *(surfit_funcs->begin()+pos);
};

func * funcs_first() {
	if (surfit_funcs->size() == 0) {
		writelog(SURFIT_ERROR,"funcs_first : empty surfit_funcs");
		return NULL;
	}
	return *surfit_funcs->begin();
};

func * funcs_last() {
	if (surfit_funcs->size() == 0) {
		writelog(SURFIT_ERROR,"funcs_last : empty surfit_funcs");
		return NULL;
	}
	return *(surfit_funcs->end()-1);
};

int funcs_size() {
	return surfit_funcs->size();
};

int funcs_info() {
	int max_priority = 0;
	if (surfit_func) {
		_func_info(surfit_func);
		max_priority = MAX(max_priority, surfit_func->get_priority());
	}
	
	if (surfit_funcs->size() > 0) {
		unsigned int func_cnt;
		for (func_cnt = 0; func_cnt < surfit_funcs->size(); func_cnt++) {
			func * a_fnc = *(surfit_funcs->begin()+func_cnt);
			if (a_fnc) {
				_func_info(a_fnc);
				max_priority = MAX(max_priority, a_fnc->get_priority());
			}
		}
	}
	return max_priority;
};

}; // namespace surfit;

