
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
#include "areas.h"
#include "area.h"
#include "area_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "area_user.h"

namespace surfit {

bool areas_delall() {
	if (surfit_areas->size() == 0) {
		//writelog(SURFIT_WARNING,"areas_delall : empty surfit_areas");
		return false;
	}

	unsigned int i;
	for (i = 0; i < surfit_areas->size(); i++) 
		delete *(surfit_areas->begin()+i);
	surfit_areas->resize(0);
	return true;
};

bool areas_del(int pos) {
	if ( ((int)surfit_areas->size() <= pos) || (pos < 0) ) {
		writelog(SURFIT_ERROR,"areas_del : wrong pos");
		return false;
	}

	surfit_areas->erase(surfit_areas->begin()+pos);

	return true;
};

bool areas_read(const char * filename, const char * areaname, REAL value,
		int columns, 
		int col1, int col2, 
		const char* delimiter, int grow_by) {
	area * fault = _area_read(filename, areaname, value, columns, col1, col2, grow_by, delimiter);
	if (!fault)
		return false;
	surfit_areas->push_back(fault);
	return true;
};

bool areas_load(const char * filename, const char * areaname) {
	area * fault = _area_load(filename, areaname, get_rw_mode());
	if (!fault)
		return false;
	surfit_areas->push_back(fault);
	return true;
};

area * areas_at(int pos) {
	if ((int)surfit_areas->size() <= pos) {
		writelog(SURFIT_ERROR,"areas_at : wrong pos");
		return NULL;
	}
	return *(surfit_areas->begin()+pos);
};

area * areas_first() {
	if (surfit_areas->size() == 0) {
		writelog(SURFIT_ERROR,"areas_first : empty surfit_areas");
		return NULL;
	}
	return *(surfit_areas->begin());
};

area * areas_last() {
	if (surfit_areas->size() == 0) {
		writelog(SURFIT_ERROR,"areas_first : empty surfit_areas");
		return NULL;
	}
	return *(surfit_areas->end()-1);
};

int areas_size() {
	return surfit_areas->size();
};

int areas_info() {
	int max_priority = 0;
	if (surfit_area) {
		_area_info(surfit_area);
		max_priority = MAX(max_priority, surfit_area->get_priority());
	}
	
	unsigned int areas_counter;
	for (areas_counter = 0; areas_counter < surfit_areas->size(); areas_counter++) {
		area * a_area = *(surfit_areas->begin()+areas_counter);
		_area_info(a_area);
		max_priority = MAX(max_priority, a_area->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;


