
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

#ifndef __surfit_geom_alg__
#define __surfit_geom_alg__

#include <float.h>

namespace surfit {

SURFIT_EXPORT
void line_equation(REAL x1, REAL y1,
		   REAL x2, REAL y2,
		   REAL & A, REAL & B, REAL & C);

SURFIT_EXPORT
bool intersect(REAL x1, REAL y1, REAL x2, REAL y2,        // первый отрезок
               REAL a1, REAL b1, REAL a2, REAL b2,        // второй отрезок
               REAL &secx, REAL &secy,                    // точка пересечения
               REAL eps = 1e-6);

SURFIT_EXPORT
bool point_in_rect(REAL rx1, REAL ry1,
                   REAL rx2, REAL ry2,
		   REAL px, REAL py);

SURFIT_EXPORT
bool get_line_in_rect(REAL rx1, REAL ry1,
		      REAL rx2, REAL ry2,
		      REAL & lx1, REAL & ly1,
		      REAL & lx2, REAL & ly2);

}; // namespace surfit;

#endif

