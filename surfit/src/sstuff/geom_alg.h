
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

#ifndef __sstuff_geom_alg__
#define __sstuff_geom_alg__

#include <float.h>
#include <math.h>

namespace surfit {

SSTUFF_EXPORT
void line_equation(REAL x1, REAL y1,
		   REAL x2, REAL y2,
		   REAL & A, REAL & B, REAL & C);

SSTUFF_EXPORT
bool intersect(REAL x1, REAL y1, REAL x2, REAL y2,        // первый отрезок
               REAL a1, REAL b1, REAL a2, REAL b2,        // второй отрезок
               REAL &secx, REAL &secy,                    // точка пересечения
               REAL eps = 1e-6);

SSTUFF_EXPORT
bool point_in_rect(REAL rx1, REAL ry1,
                   REAL rx2, REAL ry2,
		   REAL px, REAL py);

SSTUFF_EXPORT
bool get_line_in_rect(REAL rx1, REAL ry1,
		      REAL rx2, REAL ry2,
		      REAL & lx1, REAL & ly1,
		      REAL & lx2, REAL & ly2);

inline
bool rotate(REAL center_x, REAL center_y, REAL angle,
	    REAL * x_begin, REAL * x_end,
	    REAL * y_begin, REAL * y_end) 
{
	REAL cos_alpha = (REAL)cos(angle/REAL(180)*3.1415926);
	REAL sin_alpha = (REAL)sin(angle/REAL(180)*3.1415926);

	int size = (x_end-x_begin);
	if (size != (y_end-y_begin))
		return false;

	REAL x1, y1;
	REAL x2, y2;
	int i;
	for (i = 0; i < size; i++) {
		x1 = *(x_begin + i);
		y1 = *(y_begin + i);
		x2 = (x1 - center_x)*cos_alpha - (y1 - center_y)*sin_alpha + center_x;
		y2 = (x1 - center_x)*sin_alpha + (y1 - center_y)*cos_alpha + center_y;
		*(x_begin + i) = x2;
		*(y_begin + i) = y2;
	}

	return true;
};

SSTUFF_EXPORT
bool in_region(REAL * p_x, REAL * p_y, int np, REAL x, REAL y);

}; // namespace surfit;

#endif

