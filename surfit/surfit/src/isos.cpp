
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
#include "isos.h"
#include "iso.h"
#include "iso_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "iso_user.h"

namespace surfit {

bool isos_delall() {
	if (surfit_isos->size() == 0) {
		//writelog(SURFIT_WARNING,"isos_delall : empty surfit_isos");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_isos->size(); i++) 
		delete *(surfit_isos->begin()+i);
	surfit_isos->resize(0);
	return true;
};

bool isos_del(int pos) {
	if ( ((int)surfit_isos->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"isos_del : wrong pos");
		return false;
	}

	surfit_isos->erase(surfit_isos->begin()+pos);

	return true;
};

bool isos_read(const char * filename, const char * isoname, REAL value,
	       int columns, 
               int col1, int col2, const char* delimiter, int grow_by) {
	iso * fault = _iso_read(filename, isoname, value, columns, col1, col2, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_isos->push_back(fault);
	return true;
};

bool isos_load(const char * filename, const char * isoname) {
	iso * fault = _iso_load(filename, isoname, get_rw_mode());
	if (!fault)
		return false;
	surfit_isos->push_back(fault);
	return true;
};

iso * isos_at(int pos) {
	if ((int)surfit_isos->size() <= pos) {
		writelog(SURFIT_ERROR,"isos_at : wrong pos");
		return NULL;
	}
	return *(surfit_isos->begin()+pos);
};

iso * isos_first() {
	if (surfit_isos->size() == 0) {
		writelog(SURFIT_ERROR,"isos_first : empty surfit_isos");
		return NULL;
	}
	return *(surfit_isos->begin());
};

iso * isos_last() {
	if (surfit_isos->size() == 0) {
		writelog(SURFIT_ERROR,"isos_first : empty surfit_isos");
		return NULL;
	}
	return *(surfit_isos->end()-1);
};

int isos_size() {
	return surfit_isos->size();
};

int isos_info() {
	int max_priority = 0;
	if (surfit_iso) {
		_iso_info(surfit_iso);
		max_priority = MAX(max_priority, surfit_iso->get_priority());
	}

	unsigned int isos_counter;
	for (isos_counter = 0; isos_counter < surfit_isos->size(); isos_counter++) {
		iso * a_iso = *(surfit_isos->begin()+isos_counter);
		_iso_info(a_iso);
		max_priority = MAX(max_priority, a_iso->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;


