
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "fileio.h"

#include "flow_variables.h"
#include "flow_data_manager.h"
#include "variables.h"
#include "sort_alg.h"
#include "surfit.h"
#include "surfit_data.h"
#include "functional.h"

#include "free_elements.h"

#include "tcl.h"

namespace surfit {

freeflow_manager * flow_manager = NULL;

/*! \struct flow_garbage
    \brief struct for deletion of pointers
*/
struct flow_garbage : public binman {
	//! garbage sweeper
	~flow_garbage();
};

void remove_functional(int pos, functional * f) {
	functionals->erase( functionals->begin() + pos );
	f->release();
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

	Tcl_printf("freeflow version %s, Copyright (c) 2002-2006 M.V.Dmitrievsky & V.N.Kutrunov\n", FREEFLOW_VERSION);
	Tcl_printf("freeflow comes with ABSOLUTELY NO WARRANTY; for details type `show_w'.\n");
	Tcl_printf("This is free software, and you are welcome to redistribute it\n");
	Tcl_printf("under certain conditions; type `show_c' for details.\n");

};


}; // namespace surfit;

