
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
#include "wfuncs.h"
#include "wfunc.h"
#include "wfunc_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "wfunc_user.h"

#include <vector>

namespace surfit {

bool wfuncs_delall() {
	unsigned int i;

	if (surfit_wfuncs->size() == 0) {
		//writelog(SURFIT_WARNING,"wfuncs_delall : empty surfit_wfuncs");
		return false;
	}
	
	for (i = 0; i < surfit_wfuncs->size(); i++)
		delete *(surfit_wfuncs->begin()+i);

	surfit_wfuncs->resize(0);

	return true;
};

bool wfuncs_del(int pos) {
	if ((int)surfit_wfuncs->size() <= pos) {
		writelog(SURFIT_ERROR,"wfuncs_del : wrong pos");
		return false;
	}

	_wfunc_unload(*(surfit_wfuncs->begin()+pos));
	surfit_wfuncs->erase(surfit_wfuncs->begin()+pos);

	return true;
};

bool wfuncs_unload(const char * name) {
	unsigned int i;

	if (surfit_wfuncs->size() == 0) {
		writelog(SURFIT_WARNING,"wfuncs_delall : empty surfit_wfuncs");
		return false;
	}
	
	wfunc * fnc = NULL;
	for (i = 0; i < surfit_wfuncs->size(); i++) {
		fnc = *(surfit_wfuncs->begin()+i);
		if (fnc->getName()) {
			if ( strcmp(fnc->getName(),name) == 0 ) {
				return wfuncs_del(i);
			}
		}
	}
	
	return false;
};


bool wfuncs_load(const char * filename, const char * wfuncname) {
	wfunc * fnc = _wfunc_load(filename, wfuncname, get_rw_mode());
	if (!fnc)
		return false;

	std::vector< wfunc* > * aa;
	aa = surfit_wfuncs;
	surfit_wfuncs->push_back(fnc);
	std::vector<wfunc *> * bb = surfit_wfuncs;
	return true;
};

wfunc * wfuncs_at(int pos) {
	if (pos >= (int)surfit_wfuncs->size()) {
		writelog(SURFIT_ERROR,"wfuncs_at : wrong pos");
		return NULL;
	}
	return *(surfit_wfuncs->begin()+pos);
};

wfunc * wfuncs_first() {
	if (surfit_wfuncs->size() == 0) {
		writelog(SURFIT_ERROR,"wfuncs_first : empty surfit_wfuncs");
		return NULL;
	}
	return *surfit_wfuncs->begin();
};

wfunc * wfuncs_last() {
	if (surfit_wfuncs->size() == 0) {
		writelog(SURFIT_ERROR,"wfuncs_last : empty surfit_wfuncs");
		return NULL;
	}
	return *(surfit_wfuncs->end()-1);
};

int wfuncs_size() {
	return surfit_wfuncs->size();
};

int wfuncs_info() {
	int max_priority = 0;
	if (surfit_wfunc) {
		_wfunc_info(surfit_wfunc);
		max_priority = MAX(max_priority, surfit_wfunc->get_priority());
	}
	
	if (surfit_wfuncs->size() > 0) {
		unsigned int wfunc_cnt;
		for (wfunc_cnt = 0; wfunc_cnt < surfit_wfuncs->size(); wfunc_cnt++) {
			wfunc * a_fnc = *(surfit_wfuncs->begin()+wfunc_cnt);
			if (a_fnc) {
				_wfunc_info(a_fnc);
				max_priority = MAX(max_priority, a_fnc->get_priority());
			}
		}
	}
	return max_priority;
};

bool wfuncs_load_grd(const char * filename, REAL weight, const char * funcname) {
	wfunc * fnc = _wfunc_load_grd(filename, weight, funcname);
	if (!fnc)
		return false;

	surfit_wfuncs->push_back(fnc);
	return true;
};

}; // namespace surfit;

