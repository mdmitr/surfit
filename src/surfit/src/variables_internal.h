
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

#ifndef __surfit__variables_internal__
#define __surfit__variables_internal__

#include <vector>

struct Tcl_Interp;

namespace surfit {

	//! inits all variables
	SURFIT_EXPORT
	void surfit_init_all();

	//! inits surfit variables 
	SURFIT_EXPORT
	void surfit_init_variables(Tcl_Interp * interp);

	//! contains number of iteration made by penalty algorithm
	SURFIT_EXPORT
	extern size_t penalty_iter_counter;

};

#endif

