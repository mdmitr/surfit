
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
#include "wareas.h"
#include "warea.h"
#include "warea_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "warea_user.h"

namespace surfit {

bool wareas_delall() {
	if (surfit_wareas->size() == 0) {
		//writelog(SURFIT_WARNING,"wareas_delall : empty surfit_wareas");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_wareas->size(); i++) 
		delete *(surfit_wareas->begin()+i);
	surfit_wareas->resize(0);
	return true;
};

bool wareas_del(int pos) {
	if ( ((int)surfit_wareas->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"wareas_del : wrong pos");
		return false;
	}

	surfit_wareas->erase(surfit_wareas->begin()+pos);

	return true;
};

bool wareas_read(const char * filename, const char * wareaname, REAL value, REAL weight,
		int columns, 
                int col1, int col2, 
		const char* delimiter, int grow_by) {
	warea * fault = _warea_read(filename, wareaname, value, weight, columns, col1, col2, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_wareas->push_back(fault);
	return true;
};

bool wareas_load(const char * filename, const char * wareaname) {
	warea * fault = _warea_load(filename, wareaname, get_rw_mode());
	if (!fault)
		return false;
	surfit_wareas->push_back(fault);
	return true;
};

warea * wareas_at(int pos) {
	if ((int)surfit_wareas->size() <= pos) {
		writelog(SURFIT_ERROR,"wareas_at : wrong pos");
		return NULL;
	}
	return *(surfit_wareas->begin()+pos);
};

warea * wareas_first() {
	if (surfit_wareas->size() == 0) {
		writelog(SURFIT_ERROR,"wareas_first : empty surfit_wareas");
		return NULL;
	}
	return *(surfit_wareas->begin());
};

warea * wareas_last() {
	if (surfit_wareas->size() == 0) {
		writelog(SURFIT_ERROR,"wareas_first : empty surfit_wareas");
		return NULL;
	}
	return *(surfit_wareas->end()-1);
};

int wareas_size() {
	return surfit_wareas->size();
};

int wareas_info() {
	int max_priority = 0;
	if (surfit_warea) {
		_warea_info(surfit_warea);
		max_priority = MAX(max_priority, surfit_warea->get_priority());
	}
	
	unsigned int wareas_counter;
	for (wareas_counter = 0; wareas_counter < surfit_wareas->size(); wareas_counter++) {
		warea * a_warea = *(surfit_wareas->begin()+wareas_counter);
		_warea_info(a_warea);
		max_priority = MAX(max_priority, a_warea->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;


