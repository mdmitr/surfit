
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
#include "variables_tcl.h"
#include "variables_internal.h"
#include "pareas.h"
#include "parea.h"
#include "parea_internal.h"
#include "fileio.h"

#include "parea_user.h"

namespace surfit {

bool pareas_delall() {
	if (flow_pareas->size() == 0) {
		//writelog(SURFIT_WARNING,"pareas_delall : empty flow_pareas");
		return false;
	}

	unsigned int i;
	for (i = 0; i < flow_pareas->size(); i++) 
		delete *(flow_pareas->begin()+i);
	flow_pareas->resize(0);
	return true;
};

bool pareas_del(int pos) {
	if ( ((int)flow_pareas->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"pareas_del : wrong pos");
		return false;
	}

	flow_pareas->erase(flow_pareas->begin()+pos);

	return true;
};

bool pareas_read(const char * filename, const char * pareaname, REAL value,
		 int columns, 
                 int col1, int col2, 
		 const char * delimiter, int grow_by) {
	parea * par = _parea_read(filename, pareaname, value, columns, col1, col2, grow_by, delimiter);
	if (!par)
		return false;
	flow_pareas->push_back(par);
	return true;
};

bool pareas_load(const char * filename, const char * pareaname) {
	parea * par = _parea_load(filename, pareaname, get_rw_mode());
	if (!par)
		return false;
	flow_pareas->push_back(par);
	return true;
};

parea * pareas_at(int pos) {
	if ((int)flow_pareas->size() <= pos) {
		writelog(SURFIT_ERROR,"pareas_at : wrong pos");
		return NULL;
	}
	return *(flow_pareas->begin()+pos);
};

parea * pareas_first() {
	if (flow_pareas->size() == 0) {
		writelog(SURFIT_ERROR,"pareas_first : empty flow_pareas");
		return NULL;
	}
	return *(flow_pareas->begin());
};

parea * pareas_last() {
	if (flow_pareas->size() == 0) {
		writelog(SURFIT_ERROR,"pareas_first : empty flow_pareas");
		return NULL;
	}
	return *(flow_pareas->end()-1);
};

int pareas_size() {
	return flow_pareas->size();
};

int pareas_info() {

	int max_priority = 0;
	if (flow_parea) {
		_parea_info(flow_parea);
		max_priority = MAX(max_priority, flow_parea->get_priority());
	}

	unsigned int areas_counter;
	for (areas_counter = 0; areas_counter < flow_pareas->size(); areas_counter++) {
		parea * a_area = *(flow_pareas->begin()+areas_counter);
		_parea_info(a_area);
		max_priority = MAX(max_priority, a_area->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;


