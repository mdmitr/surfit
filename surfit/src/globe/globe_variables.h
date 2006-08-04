
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

#ifndef __surfit_globe_variables_included__
#define __surfit_globe_variables_included__

struct Tcl_Interp;
#include <vector>

namespace surfit {

#define GLOBE_VERSION "2.1"

GLOBE_EXPORT
void globe_init_variables(Tcl_Interp * interp);

class user;

extern GLOBE_EXPORT std::vector<user *> * globe_users;

}; // namespace surfit;

#endif

