
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
#include "pcntrs.h"
#include "pcntr.h"
#include "pcntr_internal.h"
#include "fileio.h"

#include "pcntr_user.h"

namespace surfit {

bool pcntrs_delall() {
	if (flow_pcntrs->size() == 0) {
		//writelog(SURFIT_WARNING,"pcntrs_delall : empty flow_pcntrs");
		return false;
	}

	unsigned int i;
	for (i = 0; i < flow_pcntrs->size(); i++) 
		delete *(flow_pcntrs->begin()+i);
	flow_pcntrs->resize(0);
	return true;
};

bool pcntrs_del(int pos) {
	if ( ((int)flow_pcntrs->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"pcntrs_del : wrong pos");
		return false;
	}

	flow_pcntrs->erase(flow_pcntrs->begin()+pos);

	return true;
};

bool pcntrs_read(const char * filename, const char * pcntrname,
                 int columns, 
                 int col1, int col2, int col3,
                 const char * delimiter, int grow_by) {
	pcntr * pc = _pcntr_read(filename, pcntrname, columns, col1, col2, col3, grow_by, delimiter);
	if (!pc)
		return false;
	flow_pcntrs->push_back(pc);
	return true;
};

bool pcntrs_load(const char * filename, const char * pcntrname) {
	pcntr * pc = _pcntr_load(filename, pcntrname, get_rw_mode());
	if (!pc)
		return false;
	flow_pcntrs->push_back(pc);
	return true;
};

pcntr * pcntrs_at(int pos) {
	if ((int)flow_pcntrs->size() <= pos) {
		writelog(SURFIT_ERROR,"pcntrs_at : wrong pos");
		return NULL;
	}
	return *(flow_pcntrs->begin()+pos);
};

pcntr * pcntrs_first() {
	if (flow_pcntrs->size() == 0) {
		writelog(SURFIT_ERROR,"pcntrs_first : empty flow_pcntrs");
		return NULL;
	}
	return *(flow_pcntrs->begin());
};

pcntr * pcntrs_last() {
	if (flow_pcntrs->size() == 0) {
		writelog(SURFIT_ERROR,"pcntrs_first : empty flow_pcntrs");
		return NULL;
	}
	return *(flow_pcntrs->end()-1);
};

int pcntrs_size() {
	return flow_pcntrs->size();
};

int pcntrs_info() {
	int max_priority = 0;
	if (flow_pcntr) {
		_pcntr_info(flow_pcntr);
		max_priority = MAX(max_priority, flow_pcntr->get_priority());
	}

	unsigned int pcntrs_counter;
	for (pcntrs_counter = 0; pcntrs_counter < flow_pcntrs->size(); pcntrs_counter++) {
		pcntr * a_cntr = *(flow_pcntrs->begin()+pcntrs_counter);
		_pcntr_info(a_cntr);
		max_priority = MAX(max_priority, a_cntr->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;



