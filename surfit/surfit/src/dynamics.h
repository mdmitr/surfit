
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

#ifndef __surfit_dynamics_included__
#define __surfit_dynamics_included__

namespace surfit {

SURFIT_EXPORT
/*! \ingroup tcl_dynamic
    \fn bool dynamics_load(const char * load_proc_name, const char * unload_proc_name);
    \brief inits \ref dynamic with load and unload procedures and adds it to \ref surfit_dynamics
*/
bool dynamics_load(const char * load_proc_name, const char * unload_proc_name);

SURFIT_EXPORT
/*! \ingroup tcl_dynamic
    \fn bool dynamics_delall();
    \brief removes all elements from \ref surfit_dynamics
*/
bool dynamics_delall();

SURFIT_EXPORT
/*! \ingroup tcl_dynamic
    \fn int dynamics_info();
    \brief prints some info about elements of \ref surfit_dynamics
*/
int dynamics_info();

}; // namespace surfit;

#endif

