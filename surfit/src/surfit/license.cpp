
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

#include "surfit_ie.h"

#include "fileio.h"

namespace surfit {

void print_license() {
	Tcl_printf("surfit version %s, Copyright (c) 2002-2006 M.V.Dmitrievsky & V.N.Kutrunov\n", VERSION);
	Tcl_printf("surfit comes with ABSOLUTELY NO WARRANTY; for details type `show_w'.\n");
	Tcl_printf("This is free software, and you are welcome to redistribute it\n");
	Tcl_printf("under certain conditions; type `show_c' for details.\n");
};

void show_c() {
	Tcl_printf("See COPYING file or GNU General Public License for copying and\n");
	Tcl_printf("redistribution conditions.\n");
};

void show_w() {
	Tcl_printf("This program is distributed in the hope that it will be useful,\n");
	Tcl_printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
	Tcl_printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
	Tcl_printf("GNU General Public License for more details.\n");
};

}; // namespace surfit;

