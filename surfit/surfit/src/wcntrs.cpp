
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
#include "wcntrs.h"
#include "wcntr.h"
#include "wcntr_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "wcntr_user.h"

namespace surfit {

bool wcntrs_delall() {
	if (surfit_wcntrs->size() == 0) {
		//writelog(SURFIT_WARNING,"wcntrs_delall : empty surfit_wcntrs");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_wcntrs->size(); i++) 
		delete *(surfit_wcntrs->begin()+i);
	surfit_wcntrs->resize(0);
	return true;
};

bool wcntrs_del(int pos) {
	if ( ((int)surfit_wcntrs->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"wcntrs_del : wrong pos");
		return false;
	}

	surfit_wcntrs->erase(surfit_wcntrs->begin()+pos);

	return true;
};

bool wcntrs_read(const char * filename, const char * wcntrname, REAL weight,
		 int columns, 
                 int col1, int col2, int col3,
		 const char* delimiter, int grow_by) {
	wcntr * fault = _wcntr_read(filename, wcntrname, weight, columns, col1, col2, col3, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_wcntrs->push_back(fault);
	return true;
};

bool wcntrs_load(const char * filename, const char * wcntrname) {
	wcntr * fault = _wcntr_load(filename, wcntrname, get_rw_mode());
	if (!fault)
		return false;
	surfit_wcntrs->push_back(fault);
	return true;
};

wcntr * wcntrs_at(int pos) {
	if ((int)surfit_wcntrs->size() <= pos) {
		writelog(SURFIT_ERROR,"wcntrs_at : wrong pos");
		return NULL;
	}
	return *(surfit_wcntrs->begin()+pos);
};

wcntr * wcntrs_first() {
	if (surfit_wcntrs->size() == 0) {
		writelog(SURFIT_ERROR,"wcntrs_first : empty surfit_wcntrs");
		return NULL;
	}
	return *(surfit_wcntrs->begin());
};

wcntr * wcntrs_last() {
	if (surfit_wcntrs->size() == 0) {
		writelog(SURFIT_ERROR,"wcntrs_first : empty surfit_wcntrs");
		return NULL;
	}
	return *(surfit_wcntrs->end()-1);
};

int wcntrs_size() {
	return surfit_wcntrs->size();
};

int wcntrs_info() {
	int max_priority = 0;
	if (surfit_wcntr) {
		_wcntr_info(surfit_wcntr);
		max_priority = MAX(max_priority, surfit_wcntr->get_priority());
	}

	unsigned int wcntrs_counter;
	for (wcntrs_counter = 0; wcntrs_counter < surfit_wcntrs->size(); wcntrs_counter++) {
		wcntr * a_wcntr = *(surfit_wcntrs->begin()+wcntrs_counter);
		_wcntr_info(a_wcntr);
		max_priority = MAX(max_priority, a_wcntr->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;



