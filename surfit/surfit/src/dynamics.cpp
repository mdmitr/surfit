
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
#include "fileio.h"
#include "dynamic.h"
#include "dynamic_internal.h"

#include "dynamic_user.h"

namespace surfit {

bool dynamics_load(const char * iload_proc_name, const char * iunload_proc_name) {
	dynamic * data = _dynamic_load(iload_proc_name, iunload_proc_name);

	if (!data) 
		return false;

	surfit_dynamics->push_back(data);
	return true;
};

bool dynamics_delall() {
	if (surfit_dynamics->size() == 0) {
		//writelog(SURFIT_WARNING,"dynamics_delall : empty surfit_dynamics");
	}
	std::vector<dynamic *>::iterator it5;
	for (it5 = surfit_dynamics->begin(); it5 != surfit_dynamics->end(); ++it5)
		delete *it5;
	surfit_dynamics->resize(0);
	return true;
};

int dynamics_info() {
	int max_priority = 0;
	if (surfit_dynamic) {
		_dynamic_info(surfit_dynamic);
		max_priority = MAX(max_priority, surfit_dynamic->get_priority());
	}
	
	unsigned int dynamic_counter;
	for (dynamic_counter = 0; dynamic_counter < surfit_dynamics->size(); dynamic_counter++) {
		dynamic * dyn_data = *(surfit_dynamics->begin()+dynamic_counter);
		_dynamic_info(dyn_data);
		max_priority = MAX(max_priority, dyn_data->get_priority());
	}
	return max_priority;
};

}; // namespace surfit;

