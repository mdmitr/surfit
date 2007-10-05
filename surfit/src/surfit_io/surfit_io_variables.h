
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

#ifndef __surfit_surfit_io_variables_included__
#define __surfit_surfit_io_variables_included__

struct Tcl_Interp;
#include <vector>

namespace surfit {

#define SURFIT_IO_VERSION "3.0"

//! inits libsurfit_io global variables
SURFIT_IO_EXPORT
void surfit_io_init_variables(Tcl_Interp * interp);

}; // namespace surfit;

#endif

