
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
#include "curvs.h"
#include "curv.h"
#include "curv_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "curv_user.h"

namespace surfit {

bool curvs_delall() {
	if (surfit_curvs->size() == 0) {
		//writelog(SURFIT_WARNING,"curvs_delall : empty surfit_curvs");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_curvs->size(); i++) 
		delete *(surfit_curvs->begin()+i);
	surfit_curvs->resize(0);
	return true;
};

bool curvs_del(int pos) {
	if ( ((int)surfit_curvs->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"curvs_del : wrong pos");
		return false;
	}

	surfit_curvs->erase(surfit_curvs->begin()+pos);

	return true;
};

bool curvs_read(const char * filename, const char * curvname,
		int columns, 
		int col1, int col2,
		const char* delimiter, int grow_by) {
	curv * fault = _curv_read(filename, curvname, columns, col1, col2, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_curvs->push_back(fault);
	return true;
};

bool curvs_load(const char * filename, const char * curvname) {
	curv * fault = _curv_load(filename, curvname, get_rw_mode());
	if (!fault)
		return false;
	surfit_curvs->push_back(fault);
	return true;
};

curv * curvs_at(int pos) {
	if ((int)surfit_curvs->size() <= pos) {
		writelog(SURFIT_ERROR,"curvs_at : wrong pos");
		return NULL;
	}
	return *(surfit_curvs->begin()+pos);
};

curv * curvs_first() {
	if (surfit_curvs->size() == 0) {
		writelog(SURFIT_ERROR,"curvs_first : empty surfit_curvs");
		return NULL;
	}
	return *(surfit_curvs->begin());
};

curv * curvs_last() {
	if (surfit_curvs->size() == 0) {
		writelog(SURFIT_ERROR,"curvs_first : empty surfit_curvs");
		return NULL;
	}
	return *(surfit_curvs->end()-1);
};

int curvs_size() {
	return surfit_curvs->size();
};

int curvs_info() {
	int max_priority = 0;
	if (surfit_curv) {
		_curv_info(surfit_curv);
		max_priority = MAX(max_priority, surfit_curv->get_priority());
	}

	unsigned int curvs_counter;
	for (curvs_counter = 0; curvs_counter < surfit_curvs->size(); curvs_counter++) {
		curv * a_curv = *(surfit_curvs->begin()+curvs_counter);
		_curv_info(a_curv);
		max_priority = MAX(max_priority, a_curv->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;



