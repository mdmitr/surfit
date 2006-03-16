
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

namespace surfit {

SURFIT_EXPORT
bool func(const char * pos = "0");

SURFIT_EXPORT
bool func_add(REAL weight, const char * pos = "0");

SURFIT_EXPORT
bool func_leq(const char * pos = "0", REAL mult = 0.001);

SURFIT_EXPORT
bool func_geq(const char * pos = "0", REAL mult = 0.001);

SURFIT_EXPORT
bool trend(REAL D1 = 1, REAL D2 = 2, const char * pos = "0");
	
SURFIT_EXPORT
bool trend_add(REAL weight, REAL D1 = 1, REAL D2 = 2, const char * pos = "0");

SURFIT_EXPORT
bool mask(const char * Value, const char * pos = "0");
	
}; // namespace surfit;

