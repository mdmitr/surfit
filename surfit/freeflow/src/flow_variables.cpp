
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
#include "flow_variables.h"
#include "fileio.h"
#include "flow_file_manager.h"
#include "variables.h"
#include "sort_alg.h"
#include "surfit.h"
#include "lcm_simple.h"

#include "free_elements.h"

#include "user.h"
#include "grid_user.h"
#include "flt_user.h"
#include "task_user.h"
#include "wtask_user.h"
#include "ptask_user.h"
#include "iso_user.h"
#include "wiso_user.h"
#include "piso_user.h"
#include "cntr_user.h"
#include "wcntr_user.h"
#include "pcntr_user.h"
#include "area_user.h"
#include "warea_user.h"
#include "parea_user.h"
#include "func_user.h"
#include "wfunc_user.h"
#include "trend_user.h"
#include "defarea_user.h"
#include "dynamic_user.h"
#include "lcm_simple_user.h"
#include "completer_user.h"

#include "tcl.h"

namespace surfit {

std::vector<user *> * freeflow_users = NULL;
freeflow_manager * flow_manager = NULL;

/*! \struct flow_garbage
    \brief struct for deletion of pointers
*/
struct flow_garbage : public binman {
	//! garbage sweeper
	~flow_garbage();
};

flow_garbage::~flow_garbage() {

	if (surfit_data_manager) {
		unsigned int i;
		for (i = 0; i < surfit_data_manager->managers->size(); i++) {
			manager * man = *(surfit_data_manager->managers->begin()+i);
			if ( (manager*)flow_manager == man ) {
				delete flow_manager;
				flow_manager = NULL;
				*(surfit_data_manager->managers->begin()+i) = NULL;
			}
		}
	}

	if (freeflow_users) {
		free_elements(freeflow_users->begin(), freeflow_users->end());
		delete freeflow_users;
	}

	delete flow_lcm_simple;

};

flow_garbage flow_garb;

void freeflow_init_variables(Tcl_Interp * iinterp) {

	if (!init_surfit_lib(iinterp)) {
		return;
	}
	
	data_manager * m = surfit_data_manager;
	if (surfit_data_manager) {
		flow_manager = new freeflow_manager;
		surfit_data_manager->managers->push_back(flow_manager);
	}

	Tcl_printf("freeflow version %s, Copyright (C) 2002-2004 M.V.Dmitrievsky & V.N.Kutrunov\n", FREEFLOW_VERSION);
	Tcl_printf("freeflow comes with ABSOLUTELY NO WARRANTY; for details type `show_w'.\n");
	Tcl_printf("This is free software, and you are welcome to redistribute it\n");
	Tcl_printf("under certain conditions; type `show_c' for details.\n");

	freeflow_users = new std::vector<user *>;

	grid_user * grid_usr = new grid_user();
	freeflow_users->push_back(grid_usr);

	defarea_user * defarea_usr = new defarea_user();
	freeflow_users->push_back(defarea_usr);

	flt_user * flt_usr = new flt_user();
	freeflow_users->push_back(flt_usr);

	task_user * task_usr = new task_user();
	freeflow_users->push_back(task_usr);

	wtask_user * wtask_usr = new wtask_user();
	freeflow_users->push_back(wtask_usr);

	ptask_user * ptask_usr = new ptask_user();
	freeflow_users->push_back(ptask_usr);

	iso_user * iso_usr = new iso_user();
	freeflow_users->push_back(iso_usr);

	wiso_user * wiso_usr = new wiso_user();
	freeflow_users->push_back(wiso_usr);

	piso_user * piso_usr = new piso_user();
	freeflow_users->push_back(piso_usr);

	cntr_user * cntr_usr = new cntr_user();
	freeflow_users->push_back(cntr_usr);

	wcntr_user * wcntr_usr = new wcntr_user();
	freeflow_users->push_back(wcntr_usr);

	pcntr_user * pcntr_usr = new pcntr_user();
	freeflow_users->push_back(pcntr_usr);

	area_user * area_usr = new area_user();
	freeflow_users->push_back(area_usr);

	warea_user * warea_usr = new warea_user();
	freeflow_users->push_back(warea_usr);

	parea_user * parea_usr = new parea_user();
	freeflow_users->push_back(parea_usr);

	func_user * func_usr = new func_user();
	freeflow_users->push_back(func_usr);

	wfunc_user * wfunc_usr = new wfunc_user();
	freeflow_users->push_back(wfunc_usr);

	trend_user * trend_usr = new trend_user();
	freeflow_users->push_back(trend_usr);

	dynamic_user * dynamic_usr = new dynamic_user();
	freeflow_users->push_back(dynamic_usr);

	completer_user * completer_usr = new completer_user();
	freeflow_users->push_back(completer_usr);

	lcm_simple_user * lcm_simple_usr = new lcm_simple_user();
	freeflow_users->push_back(lcm_simple_usr);

};


}; // namespace surfit;

