
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

#include "flow_ie.h"
#include "ptask.h"
#include "ptask_internal.h"
#include "ptask_tcl.h"
#include "ptasks.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "fileio.h"

#include "ptask_user.h"

namespace surfit {

bool ptasks_load(const char * filename, const char * ptaskname) {
	ptask * ptsk = _ptask_load(filename, ptaskname, get_rw_mode());
	if (!ptsk)
		return false;
	flow_ptasks->push_back(ptsk);
	return true;
};

bool ptasks_read(const char * filename, const char * ptaskname, 
		 int columns, 
		 int col1, int col2, int col3, 
		 const char * delimiter, int grow_by) {
	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf,delimiter );
	ptask * ptsk = _ptask_read(filename, ptaskname, columns, col1, col2, col3, buf, grow_by);
	if (!ptsk)
		return false;
	flow_ptasks->push_back(ptsk);
	return true;
};

bool ptasks_delall() {
	if (flow_ptasks->size() == 0) {
		//writelog(SURFIT_WARNING,"tasks_delall : empty flow_ptasks");
		return false;
	}

	unsigned int i;
	for (i = 0; i < flow_ptasks->size(); i++) 
		delete *(flow_ptasks->begin()+i);
	flow_ptasks->resize(0);
	return true;
};

bool ptasks_del(int pos) {
	if ( ((int)flow_ptasks->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"ptasks_del : wrong pos");
		return false;
	}

	flow_ptasks->erase(flow_ptasks->begin()+pos);

	return true;
};

ptask * ptasks_at(int pos) {
	if ((int)flow_ptasks->size() <= pos) {
		writelog(SURFIT_ERROR,"ptasks_at : wrong pos");
		return NULL;
	}
	return *(flow_ptasks->begin()+pos);
};

ptask * ptasks_first() {
	if (flow_ptasks->size() == 0) {
		writelog(SURFIT_ERROR,"ptasks_first : empty flow_ptasks");
		return NULL;
	}
	return *(flow_ptasks->begin());
};

ptask * ptasks_last() {
	if (flow_ptasks->size() == 0) {
		writelog(SURFIT_ERROR,"ptasks_first : empty flow_ptasks");
		return NULL;
	}
	return *(flow_ptasks->end()-1);
};

bool ptask_concat(ptask * ptsk) {
	if (!ptask_check())
		return false;

	if (!ptsk) {
		writelog(SURFIT_ERROR,"ptask_concat : wrong argument");
		return false;
	}
	
	int old_cnt = flow_ptask->size();
	int cnt = old_cnt + ptsk->size();

	REAL * ptr;
	
	ptr = (REAL *) realloc (flow_ptask->X_begin, cnt*sizeof(REAL) );
	if (ptr) {
		flow_ptask->X_begin = ptr;
		flow_ptask->X_end = ptr + cnt;
		ptr = flow_ptask->X_begin + old_cnt;
		memcpy(ptr, ptsk->X_begin, ptsk->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"ptask_concat : not enought memory");
		return false;
	};

	ptr = (REAL *) realloc (flow_ptask->Y_begin, cnt*sizeof(REAL) );
	if (ptr) {
		flow_ptask->Y_begin = ptr;
		flow_ptask->Y_end = ptr + cnt;
		ptr = flow_ptask->Y_begin + old_cnt;
		memcpy(ptr, ptsk->Y_begin, ptsk->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"ptask_concat : not enought memory");
		return false;
	};

	ptr = (REAL *) realloc (flow_ptask->Z_begin, cnt*sizeof(REAL) );
	if (ptr) {
		flow_ptask->Z_begin = ptr;
		flow_ptask->Z_end = ptr + cnt;
		ptr = flow_ptask->Z_begin + old_cnt;
		memcpy(ptr, ptsk->Z_begin, ptsk->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"ptask_concat : not enought memory");
		return false;
	};

	return true;
};

int ptasks_size() {
	return flow_ptasks->size();
};

int ptasks_info() {
	int max_priority = 0;
	if (flow_ptask) {
		_ptask_info(flow_ptask);
		max_priority = MAX(max_priority, flow_ptask->get_priority());
	}
	
	unsigned int tasks_counter;
	for (tasks_counter = 0; tasks_counter < flow_ptasks->size(); tasks_counter++) {
		ptask * a_ptsk = *(flow_ptasks->begin()+tasks_counter);
		_ptask_info(a_ptsk);
		max_priority = MAX(max_priority, a_ptsk->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;

