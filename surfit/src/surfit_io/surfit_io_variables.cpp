
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

#include "surfit_io_ie.h"

#include "fileio.h"

#include "surfit_io_variables.h"
#include "surfit_io_data_manager.h"
#include "variables.h"
#include "sort_alg.h"
#include "surfit.h"
#include "surfit_data.h"
#include "free_elements.h"

#include <tcl.h>

namespace surfit {

surfit_io_manager * my_surfit_io_manager = NULL;

/*! \struct surfit_io_garbage
    \brief struct for deletion of pointers
*/
struct surfit_io_garbage : public binman {
	//! garbage sweeper
	~surfit_io_garbage();
};

surfit_io_garbage::~surfit_io_garbage() {

	if (release_manager(my_surfit_io_manager))
		my_surfit_io_manager = NULL;
};

surfit_io_garbage surfit_io_garb;

void surfit_io_init_variables(Tcl_Interp * iinterp) {

	if (!init_surfit_lib(iinterp)) {
		return;
	}
	
	my_surfit_io_manager = new surfit_io_manager;
	add_manager(my_surfit_io_manager);

	Tcl_printf("surfit_io version %s, Copyright (c) 2006 M.V.Dmitrievsky \n", SURFIT_IO_VERSION);
	Tcl_printf("surfit_io comes with ABSOLUTELY NO WARRANTY; for details type `show_w'.\n");
	Tcl_printf("This is free software, and you are welcome to redistribute it\n");
	Tcl_printf("under certain conditions; type `show_c' for details.\n");

};


}; // namespace surfit;

