
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

#include "flow_ie.h"
#include "flow_func_internal.h"

#include "func_user.h"

namespace surfit {

REAL func_debit(REAL x, REAL y) {

	return _func_debit(surfit_func, x, y);

};

REAL func_debit_rect(REAL x1, REAL y1, REAL x2, REAL y2) {

	return _func_debit_rect(surfit_func, x1, y1, x2, y2);

};

}; // namespace surfit;

