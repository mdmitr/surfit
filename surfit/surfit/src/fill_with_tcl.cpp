
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
#include "fill_with_tcl.h"
#include "fileio.h"
#include "fill_with.h"

#include "fill_with_user.h"

namespace surfit {

void fill_with_set(REAL value) {
	delete surfit_fill_with;
	surfit_fill_with = new fill_with(value);
};

bool fill_with_unload() {
	if (surfit_fill_with) {
		writelog(SURFIT_MESSAGE,"unloading surfit_fill_with");
		delete surfit_fill_with;
		surfit_fill_with = NULL;
	}
	return false;
};

bool fill_with_check() {
	return (surfit_fill_with != NULL);
};

}; // namespace surfit;


