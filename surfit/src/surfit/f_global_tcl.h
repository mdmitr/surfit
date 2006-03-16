
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

#ifndef __surfit_f_completer_tcl_included__
#define __surfit_f_completer_tcl_included__

namespace surfit {

SURFIT_EXPORT
bool completer(REAL D1 = 1, REAL D2 = 2);

SURFIT_EXPORT
bool completer_add(REAL weight = 1, REAL D1 = 1, REAL D2 = 2);

SURFIT_EXPORT
bool value(REAL value = 0);

SURFIT_EXPORT
bool value_add(REAL weight = 1, REAL value = 0);

SURFIT_EXPORT
bool mean(REAL value, REAL mult = 0.001);

SURFIT_EXPORT
bool wmean(REAL value, const char * func_pos = "0", REAL mult = 0.001);

SURFIT_EXPORT
bool leq(REAL value, REAL mult = 0.001);

SURFIT_EXPORT
bool geq(REAL value, REAL mult = 0.001);

SURFIT_EXPORT
bool hist(const char * pos = "0", REAL mult = 1);

}; // namespace surfit;

#endif

