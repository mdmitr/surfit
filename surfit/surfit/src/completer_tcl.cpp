
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
#include "completer.h"
#include "completer_tcl.h"
#include "fileio.h"

#include "completer_user.h"

namespace surfit {

bool completer_set(REAL D1, REAL D2) {
	if (surfit_completer) {
		surfit_completer->D1 = D1;
		surfit_completer->D2 = D2;
		return true;
	}
	return false;
};

int completer_info() {
	if (!surfit_completer)
		return 0;
	writelog(SURFIT_MESSAGE,"completer : D1 = %g, D2 = %g", surfit_completer->D1, surfit_completer->D2);
	return surfit_completer->get_priority();
};

}; // namespace surfit;

