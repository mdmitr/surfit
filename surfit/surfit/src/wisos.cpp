
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
#include "wisos.h"
#include "wiso.h"
#include "wiso_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "wiso_user.h"

namespace surfit {

bool wisos_delall() {
	if (surfit_wisos->size() == 0) {
		//writelog(SURFIT_WARNING,"wisos_delall : empty surfit_wisos");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_wisos->size(); i++) 
		delete *(surfit_wisos->begin()+i);
	surfit_wisos->resize(0);
	return true;
};

bool wisos_del(int pos) {
	if ( ((int)surfit_wisos->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"wisos_del : wrong pos");
		return false;
	}

	surfit_wisos->erase(surfit_wisos->begin()+pos);

	return true;
};

bool wisos_read(const char * filename, const char * wisoname, REAL value, REAL weight,
		int columns, 
                int col1, int col2, 
		const char* delimiter, int grow_by) {
	wiso * fault = _wiso_read(filename, wisoname, value, weight, columns, col1, col2, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_wisos->push_back(fault);
	return true;
};

bool wisos_load(const char * filename, const char * wisoname) {
	wiso * fault = _wiso_load(filename, wisoname, get_rw_mode());
	if (!fault)
		return false;
	surfit_wisos->push_back(fault);
	return true;
};

wiso * wisos_at(int pos) {
	if ((int)surfit_wisos->size() <= pos) {
		writelog(SURFIT_ERROR,"wisos_at : wrong pos");
		return NULL;
	}
	return *(surfit_wisos->begin()+pos);
};

wiso * wisos_first() {
	if (surfit_wisos->size() == 0) {
		writelog(SURFIT_ERROR,"wisos_first : empty surfit_wisos");
		return NULL;
	}
	return *(surfit_wisos->begin());
};

wiso * wisos_last() {
	if (surfit_wisos->size() == 0) {
		writelog(SURFIT_ERROR,"wisos_first : empty surfit_wisos");
		return NULL;
	}
	return *(surfit_wisos->end()-1);
};

int wisos_size() {
	return surfit_wisos->size();
};

int wisos_info() {
	int max_priority = 0;
	if (surfit_wiso) {
		_wiso_info(surfit_wiso);
		max_priority = MAX(max_priority, surfit_wiso->get_priority());
	}

	unsigned int wisos_counter;
	for (wisos_counter = 0; wisos_counter < surfit_wisos->size(); wisos_counter++) {
		wiso * a_wiso = *(surfit_wisos->begin()+wisos_counter);
		_wiso_info(a_wiso);
		max_priority = MAX(max_priority, a_wiso->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;


