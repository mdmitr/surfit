
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

#ifndef __surfit_mrf_included__
#define __surfit_mrf_included__

#include "real.h"

namespace surfit {

bool func_decomp();
bool func_auto_decomp(REAL eps);
bool func_add_noise(REAL eps);

bool func_recons();
bool func_full_recons();

SURFIT_EXPORT
void _decomp1d(const REAL * X_begin, const REAL * X_end, 
	       REAL * Xa_begin,      REAL * Xa_end,
	       REAL * Xd_begin,      REAL * Xd_end,
	       bool enlarge);

SURFIT_EXPORT		
void _recons1d(REAL * X_begin,        REAL * X_end, 
	       const REAL * Xa_begin, const REAL * Xa_end,
	       const REAL * Xd_begin, const REAL * Xd_end,
	       bool enlarge);

SURFIT_EXPORT
void _decomp2d(REAL *& X_begin,  REAL *  X_end,
	       REAL *& Xa_begin, REAL *& Xa_end,
	       REAL *& Xd_begin, REAL *& Xd_end,
	       REAL *& Xh_begin, REAL *& Xh_end,
	       REAL *& Xv_begin, REAL *& Xv_end,
	       int N,
	       bool enlarge_X,
	       bool enlarge_Y);

SURFIT_EXPORT
bool _recons2d(REAL *& X_begin,        REAL *& X_end,
	       const REAL *  Xa_begin, const REAL *  Xa_end,
	       const REAL *  Xd_begin, const REAL *  Xd_end,
	       const REAL *  Xh_begin, const REAL *  Xh_end,
	       const REAL *  Xv_begin, const REAL *  Xv_end,
	       int N,
	       bool enlarge_X,
	       bool enlarge_Y);

}; // namespace surfit;


#endif

