
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
#include "cntrs.h"
#include "cntr.h"
#include "cntr_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "cntr_user.h"
#include "wcntr_user.h"

namespace surfit {

bool cntrs_delall() {
	if (surfit_cntrs->size() == 0) {
		//writelog(SURFIT_WARNING,"cntrs_delall : empty surfit_cntrs");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_cntrs->size(); i++) 
		delete *(surfit_cntrs->begin()+i);
	surfit_cntrs->resize(0);
	return true;
};

bool cntrs_del(int pos) {
	if ( ((int)surfit_cntrs->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"cntrs_del : wrong pos");
		return false;
	}

	surfit_cntrs->erase(surfit_cntrs->begin()+pos);

	return true;
};

bool cntrs_read(const char * filename, const char * cntrname,
		int columns, 
		int col1, int col2, int col3,
		const char* delimiter, int grow_by) {
	cntr * fault = _cntr_read(filename, cntrname, columns, col1, col2, col3, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_cntrs->push_back(fault);
	return true;
};

bool cntrs_load(const char * filename, const char * cntrname) {
	cntr * fault = _cntr_load(filename, cntrname, get_rw_mode());
	if (!fault)
		return false;
	surfit_cntrs->push_back(fault);
	return true;
};

cntr * cntrs_at(int pos) {
	if ((int)surfit_cntrs->size() <= pos) {
		writelog(SURFIT_ERROR,"cntrs_at : wrong pos");
		return NULL;
	}
	return *(surfit_cntrs->begin()+pos);
};

cntr * cntrs_first() {
	if (surfit_cntrs->size() == 0) {
		writelog(SURFIT_ERROR,"cntrs_first : empty surfit_cntrs");
		return NULL;
	}
	return *(surfit_cntrs->begin());
};

cntr * cntrs_last() {
	if (surfit_cntrs->size() == 0) {
		writelog(SURFIT_ERROR,"cntrs_first : empty surfit_cntrs");
		return NULL;
	}
	return *(surfit_cntrs->end()-1);
};

int cntrs_size() {
	return surfit_cntrs->size();
};

int cntrs_info() {
	int max_priority = 0;
	if (surfit_cntr) {
		_cntr_info(surfit_cntr);
		max_priority = MAX(max_priority, surfit_cntr->get_priority());
	}

	unsigned int cntrs_counter;
	for (cntrs_counter = 0; cntrs_counter < surfit_cntrs->size(); cntrs_counter++) {
		cntr * a_cntr = *(surfit_cntrs->begin()+cntrs_counter);
		_cntr_info(a_cntr);
		max_priority = MAX(max_priority, a_cntr->get_priority());
	}
	return max_priority;
};

bool cntrs_to_wcntrs(REAL weight) {
	if (surfit_cntrs->size() == 0) {
		writelog(SURFIT_WARNING,"cntrs_to_wcntrs : empty surfit_cntrs");
		return false;
	}
	int i;
	for (i = cntrs_size(); i >= 0; i--) {
		wcntr * wcontour = _cntr_to_wcntr(cntrs_at(i), weight);
		if (wcontour) {
			surfit_wcntrs->push_back(wcontour);
			cntrs_del(i);
		}
	}
	return true;
};

}; // namespace surfit;



