
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
#include "pisos.h"
#include "piso.h"
#include "piso_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "piso_user.h"

namespace surfit {

bool pisos_delall() {
	if (flow_pisos->size() == 0) {
		//writelog(SURFIT_WARNING,"pisos_delall : empty flow_pisos");
		return false;
	}

	unsigned int i;
	for (i = 0; i < flow_pisos->size(); i++) 
		delete *(flow_pisos->begin()+i);
	flow_pisos->resize(0);
	return true;
};

bool pisos_del(int pos) {
	if ( ((int)flow_pisos->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"pisos_del : wrong pos");
		return false;
	}

	flow_pisos->erase(flow_pisos->begin()+pos);

	return true;
};

bool pisos_read(const char * filename, const char * pisoname, REAL value,
		int columns, 
                int col1, int col2, const char * delimiter, int grow_by) {
	piso * fault = _piso_read(filename, pisoname, value, columns, col1, col2, grow_by, delimiter);
	if (!fault)
		return false;
	flow_pisos->push_back(fault);
	return true;
};

bool pisos_load(const char * filename, const char * pisoname) {
	piso * fault = _piso_load(filename, pisoname, get_rw_mode());
	if (!fault)
		return false;
	flow_pisos->push_back(fault);
	return true;
};

piso * pisos_at(int pos) {
	if ((int)flow_pisos->size() <= pos) {
		writelog(SURFIT_ERROR,"pisos_at : wrong pos");
		return NULL;
	}
	return *(flow_pisos->begin()+pos);
};

piso * pisos_first() {
	if (flow_pisos->size() == 0) {
		writelog(SURFIT_ERROR,"pisos_first : empty flow_pisos");
		return NULL;
	}
	return *(flow_pisos->begin());
};

piso * pisos_last() {
	if (flow_pisos->size() == 0) {
		writelog(SURFIT_ERROR,"pisos_first : empty flow_pisos");
		return NULL;
	}
	return *(flow_pisos->end()-1);
};

int pisos_size() {
	return flow_pisos->size();
};

int pisos_info() {
	int max_priority = 0;
	if (flow_piso) {
		_piso_info(flow_piso);
		max_priority = MAX(max_priority, flow_piso->get_priority());
	}

	unsigned int pisos_counter;
	for (pisos_counter = 0; pisos_counter < flow_pisos->size(); pisos_counter++) {
		piso * a_piso = *(flow_pisos->begin()+pisos_counter);
		_piso_info(a_piso);
		max_priority = MAX(max_priority, a_piso->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;


