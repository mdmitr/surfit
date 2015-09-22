
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

flow_garbage::~flow_garbage() {

	if (release_manager(flow_manager))
		flow_manager = NULL;
};

flow_garbage flow_garb;

void freeflow_init_variables(Tcl_Interp * iinterp) {

	if (flow_manager == NULL) {
		
		if (!init_surfit_lib(iinterp)) {
			return;
		}
		
		flow_manager = new freeflow_manager;
		add_manager(flow_manager);

#ifdef XXL
		log_printf("loading module freeflow v%s (XXL build)\n", FREEFLOW_VERSION);
#else
		log_printf("loading module freeflow v%s\n", FREEFLOW_VERSION);
#endif

	}

};


}; // namespace surfit;

