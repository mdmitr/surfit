
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
#include "wtasks.h"
#include "wtask.h"
#include "wtask_internal.h"
#include "fileio.h"
#include "variables_internal.h"

#include "wtask_user.h"

namespace surfit {

bool wtasks_load(const char * filename, const char * wtaskname) {
	wtask * wtask = _wtask_load(filename, wtaskname, get_rw_mode());
	if (!wtask)
		return false;
	surfit_wtasks->push_back(wtask);
	return true;
};

bool wtasks_read(const char * filename, const char * wtaskname, int columns, int col1, int col2, int col3, int col4, const char* delimiter, int grow_by) {
	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf,delimiter );
	wtask * wtask = _wtask_read(filename, wtaskname, columns, col1, col2, col3, col4, buf, grow_by);
	if (!wtask)
		return false;
	surfit_wtasks->push_back(wtask);
	return true;
};

bool wtasks_delall() {
	if (surfit_wtasks->size() == 0) {
		//writelog(SURFIT_WARNING,"wtasks_delall : empty surfit_wtasks");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_wtasks->size(); i++) 
		delete *(surfit_wtasks->begin()+i);
	surfit_wtasks->resize(0);
	return true;
};

bool wtasks_del(int pos) {
	if ( ((int)surfit_wtasks->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"wtasks_del : wrong pos");
		return false;
	}

	surfit_wtasks->erase(surfit_wtasks->begin()+pos);

	return true;
};

wtask * wtasks_at(int pos) {
	if ((int)surfit_wtasks->size() <= pos) {
		writelog(SURFIT_ERROR,"wtasks_at : wrong pos");
		return NULL;
	}
	return *(surfit_wtasks->begin()+pos);
};

wtask * wtasks_first() {
	if (surfit_wtasks->size() == 0) {
		writelog(SURFIT_ERROR,"wtasks_first : empty surfit_wtasks");
		return NULL;
	}
	return *(surfit_wtasks->begin());
};

wtask * wtasks_last() {
	if (surfit_wtasks->size() == 0) {
		writelog(SURFIT_ERROR,"wtasks_first : empty surfit_wtasks");
		return NULL;
	}
	return *(surfit_wtasks->end()-1);
};

bool wtask_concat(wtask * wtask) {
	if (!_wtask_check())
		return false;

	if (!wtask) {
		writelog(SURFIT_ERROR,"wtask_concat : wrong argument");
		return false;
	}
	
	int old_cnt = surfit_wtask->size();
	int cnt = old_cnt + wtask->size();

	REAL * ptr;
	
	ptr = (REAL *) realloc (surfit_wtask->X_begin, cnt*sizeof(REAL) );
	if (ptr) {
		surfit_wtask->X_begin = ptr;
		surfit_wtask->X_end = ptr + cnt;
		ptr = surfit_wtask->X_begin + old_cnt;
		memcpy(ptr, wtask->X_begin, wtask->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"wtask_concat : not enought memory");
		return false;
	};

	ptr = (REAL *) realloc (surfit_wtask->Y_begin, cnt*sizeof(REAL) );
	if (ptr) {
		surfit_wtask->Y_begin = ptr;
		surfit_wtask->Y_end = ptr + cnt;
		ptr = surfit_wtask->Y_begin + old_cnt;
		memcpy(ptr, wtask->Y_begin, wtask->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"wtask_concat : not enought memory");
		return false;
	};

	ptr = (REAL *) realloc (surfit_wtask->Z_begin, cnt*sizeof(REAL) );
	if (ptr) {
		surfit_wtask->Z_begin = ptr;
		surfit_wtask->Z_end = ptr + cnt;
		ptr = surfit_wtask->Z_begin + old_cnt;
		memcpy(ptr, wtask->Z_begin, wtask->size()*sizeof(REAL));
	} else {
		writelog(SURFIT_ERROR,"wtask_concat : not enought memory");
		return false;
	};

	return true;
};

int wtasks_size() {
	return surfit_wtasks->size();
};

int wtasks_info() {
	int max_priority = 0;
	if (surfit_wtask) {
		_wtask_info(surfit_wtask);
		max_priority = MAX(max_priority, surfit_wtask->get_priority());
	}
	
	unsigned int wtasks_counter;
	for (wtasks_counter = 0; wtasks_counter < surfit_wtasks->size(); wtasks_counter++) {
		wtask * a_wtask = *(surfit_wtasks->begin()+wtasks_counter);
		_wtask_info(a_wtask);
		max_priority = MAX(max_priority, a_wtask->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;

