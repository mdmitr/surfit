
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
#include "license.h"
#include "fileio.h"

namespace surfit {

void print_license() {
#ifdef XXL
	log_printf("loading surfit v%s (XXL build)\n", VERSION);
	log_printf("surfit version %s (XXL build), Copyright (c) 2002-2007 M.V.Dmitrievsky & V.N.Kutrunov\n", VERSION);
#else
	log_printf("loading surfit v%s\n", VERSION);
	log_printf("surfit version %s, Copyright (c) 2002-2007 M.V.Dmitrievsky & V.N.Kutrunov\n", VERSION);
#endif
	log_printf("surfit comes with ABSOLUTELY NO WARRANTY; for details type `show_w'.\n");
	log_printf("This is free software, and you are welcome to redistribute it\n");
	log_printf("under certain conditions; type `show_c' for details.\n");
};

void show_c() {
	log_printf("See COPYING file or GNU General Public License for copying and\n");
	log_printf("redistribution conditions.\n");
};

void show_w() {
	log_printf("This program is distributed in the hope that it will be useful,\n");
	log_printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
	log_printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
	log_printf("GNU General Public License for more details.\n");
};

}; // namespace surfit;

