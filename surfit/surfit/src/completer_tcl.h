
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

#ifndef __surfit_completer_tcl_included__
#define __surfit_completer_tcl_included__

namespace surfit {

SURFIT_EXPORT
/*! \ingroup tcl_completer
    \fn bool completer_set(REAL D1, REAL D2);
    \brief sets parameters for \ref surfit_completer ( see \ref completer for details )
    \param D1 weight1 
    \param D2 weight2 
*/
bool completer_set(REAL D1, REAL D2);

/*! \ingroup tcl_completer
    \fn int completer_info();
    \brief prints some info about \ref surfit_completer
*/
int completer_info();

}; // namespace surfit;

#endif

