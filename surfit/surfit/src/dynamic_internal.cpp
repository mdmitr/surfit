
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
#include "fileio.h"
#include "dynamic.h"
#include "dynamic_internal.h"

namespace surfit {

bool _dynamic_unload(dynamic *& data) {
	if (!data)
		return false;
	if (data)
		delete data;
	data = NULL;
	return true;
};

dynamic * _dynamic_load(const char * iload_proc_name, const char * iunload_proc_name) {
	return new dynamic(iload_proc_name, iunload_proc_name);
};

void _dynamic_info(dynamic * data) {
	writelog(SURFIT_MESSAGE,"Dynamic: load \"%s\", unload \"%s\"",data->load_proc_name, data->unload_proc_name);
};

}; // namespace surfit;

