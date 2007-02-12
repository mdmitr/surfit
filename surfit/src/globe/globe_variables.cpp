
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

#include "globe_ie.h"

#include "fileio.h"

#include "globe_variables.h"
#include "globe_data_manager.h"
#include "variables.h"
#include "sort_alg.h"
#include "surfit.h"
#include "surfit_data.h"
#include "free_elements.h"

#include <tcl.h>

namespace surfit {

globe_manager * my_globe_manager = NULL;

/*! \struct globe_garbage
    \brief struct for deletion of pointers
*/
struct globe_garbage : public binman {
	//! garbage sweeper
	~globe_garbage();
};

globe_garbage::~globe_garbage() {

	if (release_manager(my_globe_manager))
		my_globe_manager = NULL;
};

globe_garbage globe_garb;

void globe_init_variables(Tcl_Interp * iinterp) {

	if (my_globe_manager == NULL) {
		
		if (!init_surfit_lib(iinterp)) {
			return;
		}
		
		my_globe_manager = new globe_manager;
		add_manager(my_globe_manager);

#ifdef XXL
		log_printf("loading module globe v%s (XXL build)\n", GLOBE_VERSION);
#else
		log_printf("loading module globe v%s\n", GLOBE_VERSION);
#endif
	}

};


}; // namespace surfit;

