
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

#ifndef __fill_with_tcl_included__
#define __fill_with_tcl_included__

#include <float.h>

#include "variables_tcl.h"

namespace surfit {

SURFIT_EXPORT
/*! \ingroup tcl_fill_with
    \fn void fill_with_set(REAL value);
    \brief inits \ref surfit_fill_with 
*/
void fill_with_set(REAL value = undef_value);

SURFIT_EXPORT
/*! \ingroup tcl_fill_with
    \fn bool fill_with_unload();
    \brief unloads \ref surfit_fill_with from memory
*/
bool fill_with_unload();

SURFIT_EXPORT
/*! \ingroup tcl_fill_with
    \fn bool fill_with_check();
    \brief checks for \ref surfit_fill_with existance
*/
bool fill_with_check();

}; // namespace surfit;

#endif

