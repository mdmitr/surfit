
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

/*! \file
    \brief declaration of various geometrical functions
*/

#include <float.h>
#include <math.h>

namespace surfit {

/*! \brief fills coeffs of line equations
    fills coeffs of line equation Ax + By + C by two points
*/
SSTUFF_EXPORT
void line_equation(REAL x1, REAL y1,
		   REAL x2, REAL y2,
		   REAL & A, REAL & B, REAL & C);

//! calculates intersection point of two sects
SSTUFF_EXPORT
bool intersect(REAL x1, REAL y1, REAL x2, REAL y2,        // first section
               REAL a1, REAL b1, REAL a2, REAL b2,        // second section
               REAL &secx, REAL &secy,                    // intersection point
               REAL eps = 1e-6);

//! returns true if point is inside rect and false otherwise
SSTUFF_EXPORT
bool point_in_rect(REAL rx1, REAL ry1,
                   REAL rx2, REAL ry2,
		   REAL px, REAL py);

//! calculates intersection of rect and section
SSTUFF_EXPORT
bool get_line_in_rect(REAL rx1, REAL ry1,
		      REAL rx2, REAL ry2,
		      REAL & lx1, REAL & ly1,
		      REAL & lx2, REAL & ly2);

//! rotates points
template<class iter>
bool rotate(REAL center_x, REAL center_y, REAL angle,
	    iter x_begin, iter x_end,
	    iter y_begin, iter y_end) 
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

//! returns true if point is inside polygonal region and false otherwise
SSTUFF_EXPORT
bool in_region(REAL * p_x, REAL * p_y, int np, REAL x, REAL y);

//! returns true if point is on section
SSTUFF_EXPORT
bool point_on_sect(REAL x0, REAL y0, REAL x1, REAL y1, REAL x, REAL y, REAL eps=1e-6);

}; // namespace surfit;

#endif

