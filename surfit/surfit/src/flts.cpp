
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
#include "flt.h"
#include "flts.h"
#include "flt_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "flt_user.h"

namespace surfit {

bool flts_delall() {
	
	if (surfit_flts->size() == 0) {
		//writelog(SURFIT_WARNING,"flts_delall : empty surfit_flts");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_flts->size(); i++) 
		delete *(surfit_flts->begin()+i);
	surfit_flts->resize(0);
	return true;
};

bool flts_del(int pos) {

	if ( ((int)surfit_flts->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"flts_del : wrong pos");
		return false;
	}

	surfit_flts->erase(surfit_flts->begin()+pos);

	return true;
};

bool flts_read(const char * filename, const char * fltname, int columns, 
               int col1, int col2, 
	       const char* delimiter, int grow_by) {

	flt * fault = _flt_read(filename, fltname, columns, col1, col2, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_flts->push_back(fault);
	return true;

};

bool flts_load(const char * filename, const char * fltname) {
	flt * fault = _flt_load(filename, fltname, get_rw_mode());
	if (!fault)
		return false;
	surfit_flts->push_back(fault);
	return true;
};

flt * flts_at(int pos) {
	if ((int)surfit_flts->size() <= pos) {
		writelog(SURFIT_ERROR,"flts_at : wrong pos");
		return NULL;
	}
	return *(surfit_flts->begin()+pos);
};

flt * flts_first() {
	if (surfit_flts->size() == 0) {
		writelog(SURFIT_ERROR,"flts_first : empty surfit_flts");
		return NULL;
	}
	return *(surfit_flts->begin());
};

flt * flts_last() {
	if (surfit_flts->size() == 0) {
		writelog(SURFIT_ERROR,"flts_first : empty surfit_flts");
		return NULL;
	}
	return *(surfit_flts->end()-1);
};

int flts_size() {
	return surfit_flts->size();
};

int flts_info() {
	int max_priority = 0;
	if (surfit_flt) {
		_flt_info(surfit_flt);
		max_priority = MAX(max_priority, surfit_flt->get_priority());
	}
	
	unsigned int flts_counter;
	for (flts_counter = 0; flts_counter < surfit_flts->size(); flts_counter++) {
		flt * a_fault = *(surfit_flts->begin()+flts_counter);
		_flt_info(a_fault);
		max_priority = MAX(max_priority, a_fault->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;


