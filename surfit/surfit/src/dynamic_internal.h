
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

#ifndef __surfit_dynamic_internal_included__
#define __surfit_dynamic_internal_included__

namespace surfit {

class dynamic;

SURFIT_EXPORT
bool _dynamic_unload(dynamic *& data);

SURFIT_EXPORT
dynamic * _dynamic_load(const char * iload_proc_name, const char * iunload_proc_name);

SURFIT_EXPORT
void _dynamic_info(dynamic * data);

}; // namespace surfit;

#endif

