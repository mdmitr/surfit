
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

#ifndef __surfit_dynamic_tcl_included__
#define __surfit_dynamic_tcl_included__

namespace surfit {

class dynamic;

SURFIT_EXPORT
/*! \ingroup tcl_dynamic
    \fn bool dynamic_unload();
    \brief unloads \ref surfit_dynamic from memory
*/
bool dynamic_unload();

SURFIT_EXPORT
/*! \ingroup tcl_dynamic
    \fn bool dynamic_load(const char * load_proc_name, const char * unload_proc_name);
    \brief inits \ref surfit_dynamic with load and unload procedures
*/
bool dynamic_load(const char * load_proc_name, const char * unload_proc_name);

SURFIT_EXPORT
/*! \ingroup tcl_dynamic
    \fn bool dynamic_name(const char * new_name, dynamic * dynam);
    \brief sets name for \ref surfit_dynamic or \ref dynamic class called "dynam"
*/
bool dynamic_name(const char * new_name, dynamic * dynam);

}; // namespace surfit;

#endif

