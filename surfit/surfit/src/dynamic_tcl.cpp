
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
#include "dynamic.h"
#include "dynamic_internal.h"
#include "dynamic_tcl.h"

#include "dynamic_user.h"

namespace surfit {

bool dynamic_unload() {
	return _dynamic_unload(surfit_dynamic);
};

bool dynamic_load(const char * load_proc_name, const char * unload_proc_name) {
	dynamic_unload();
	surfit_dynamic = _dynamic_load(load_proc_name, unload_proc_name);
	return true;
};

bool dynamic_name(const char * new_name, dynamic * dynam) {
	if (dynam) {
		dynam->setName(new_name);
		return true;
	}
	if (!surfit_dynamic)
		return false;
	surfit_dynamic->setName(new_name);
	return true;
};

}; // namespace surfit;

