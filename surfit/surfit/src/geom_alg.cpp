
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky, V. N. Kutrunov, L. L. Kotomin
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

#include "ie.h"
#include "geom_alg.h"
#include <math.h>

namespace surfit {

void line_equation(REAL x1, REAL y1,
		   REAL x2, REAL y2,
		   REAL & A, REAL & B, REAL & C)
{
	A = y2 - y1;
	B = x1 - x2;
	C = x1*(y1-y2) + y1*(x2-x1);
};

bool intersect(REAL x1, REAL y1, REAL x2, REAL y2,        // первый отрезок
               REAL a1, REAL b1, REAL a2, REAL b2,        // второй отрезок
               REAL &secx, REAL &secy,                    // точка пересечения
               REAL eps)                        
{
	secx = FLT_MAX;
	secy = FLT_MAX;
	
	// пересечение прямоугольников, в которых лежат отрезки
	if( ((x1>a1)&&(x1>a2)&&(x2>a1)&&(x2>a2)) ||
		((x1<a1)&&(x1<a2)&&(x2<a1)&&(x2<a2)) ||
		((y1>b1)&&(y1>b2)&&(y2>b1)&&(y2>b2)) ||
		((y1<b1)&&(y1<b2)&&(y2<b1)&&(y2<b2)) )  
		return false;
	
	REAL xx = x2 - x1, yy = y2 - y1, aa = a2 - a1, bb = b2 - b1;
	REAL f, g, c, d, p, q;
	
	// первый отрезок вертикальный
	if( fabs(xx) < eps ) { // второй отрезок не вертикальный
		if( fabs(aa)>eps ) { 
			if( ( (a1>=x1)&&(a2<=x1) )||( (a1<=x1)&&(a2>=x1) ) ) { 
				f = -bb/aa;
				g = -f*a1-b1;
				g = -g-f*x1;
				if( ((g>=y1)&&(g<=y2))||((g>=y2)&&(g<=y1)) ) { 
					secx = x1;
					secy = g;
					return true;
				}
			}
			return false;
		} else { // второй отрезок вертикальный
			if( (y1>b2 && y2>b2)||(y1<b1 && y2<b1) ) 
				return false;
			secx = x1;
			if( y1>=b1 && y1<= b2 ) { 
				secy = y1; 
			} else { 
				secy = y2; 
			}
			return true;
		}
	}

	// первый отрезок не вертикальный
	// второй отрезок вертикальный
	if( fabs(aa)<eps ) { 
		if( ((x1>=a1)&&(x2<=a1))||((x1<=a1)&&(x2>=a1)) ) { 
			f = -(REAL)yy/xx;
			g = -f*x1-y1;
			g = -g-f*a1;
			if( ((g>=b1)&&(g<=b2))||((g>=b2)&&(g<=b1)) ) { 
				secx = a1;
				secy = g;
				return true;
			}
		}
		return false;
	}
	
	// второй отрезок не вертикальный
	if(  xx*bb!=yy*aa )	{ 
		f = -(float)yy/xx;
		g = -f*x1-y1;
		c = -(float)bb/aa;
		d = -c*a1-b1;
		if(c-f) 
			p = (g-d)/(c-f);
		else 
			return false;
		q = -f*p-g;
		if( !(((p>x1+eps)&&(p>x2+eps))||((p<x1-eps)&&(p<x2-eps))||
	         ((p>a1+eps)&&(p>a2+eps))||((p<a1-eps)&&(p<a2-eps))))
		{
			secx = p;
			secy = q;
			return true;
		}
	}
	
	return false;
	
};

bool point_in_rect(REAL rx1, REAL ry1,
                   REAL rx2, REAL ry2,
		   REAL px, REAL py) {

	return (
			  (px >= rx1) && (px <= rx2) &&
			  (py >= ry1) && (py <= ry2)
	       );

};

bool get_line_in_rect(REAL rx1, REAL ry1,
		      REAL rx2, REAL ry2,
		      REAL & lx1, REAL & ly1,
		      REAL & lx2, REAL & ly2)
{

	REAL px1 = FLT_MAX, px2 = FLT_MAX, py1 = FLT_MAX, py2 = FLT_MAX;
	REAL px = FLT_MAX, py = FLT_MAX;

	bool p1_in_rect = point_in_rect(rx1, ry1, rx2, ry2, lx1, ly1);
	bool p2_in_rect = point_in_rect(rx1, ry1, rx2, ry2, lx2, ly2);

	if ((p1_in_rect) && (p2_in_rect))
		return true;

	int intersected = 0;

	if (p1_in_rect) {
		intersected++;
		px1 = lx1;
		py1 = ly1;
	}

	if (p2_in_rect) {
		intersected++;
		px1 = lx2;
		py1 = ly2;
	}

	// intersection with line (rx1,ry1)-(rx2,ry1)
	if ( intersect(rx1, ry1, rx2, ry1,
		           lx1, ly1, lx2, ly2,
				   px, py)
       )
	{
		if (point_in_rect(rx1, ry1, rx2, ry2, px, py)) {
			if (intersected == 0) {
				intersected++;
				px1 = px;
				py1 = py;
			} else {
				if ((px1 != px) || (py1 != py)) {
					px2 = px;
					py2 = py;
					goto ret;
				}
			}
		}
	}

	// intersection with line (rx2,ry1)-(rx2, ry2)
	if ( intersect(rx2, ry1, rx2, ry2,
		           lx1, ly1, lx2, ly2,
				   px, py)
       )
	{
		if (point_in_rect(rx1, ry1, rx2, ry2, px, py)) {
			if (intersected == 0) {
				intersected++;
				px1 = px;
				py1 = py;
			} else {
				if ((px1 != px) || (py1 != py)) {
					px2 = px;
					py2 = py;
					goto ret;
				}
			}
		}
	}

	// intersection with line (rx2,ry2)-(rx1, ry2)
	if ( intersect(rx2, ry2, rx1, ry2,
		           lx1, ly1, lx2, ly2,
				   px, py)
       )
	{
		if (point_in_rect(rx1, ry1, rx2, ry2, px, py)) {
			if (intersected == 0) {
				intersected++;
				px1 = px;
				py1 = py;
			} else {
				if ((px1 != px) || (py1 != py)) {
					px2 = px;
					py2 = py;
					goto ret;
				}
			}
		}
	}

	// intersection with line (rx1,ry2)-(rx1, ry1)
	if ( intersect(rx1, ry2, rx1, ry1,
		           lx1, ly1, lx2, ly2,
				   px, py)
       )
	{
		if (point_in_rect(rx1, ry1, rx2, ry2, px, py)) {
			if (intersected == 0) {
				intersected++;
				px1 = px;
				py1 = py;
			} else {
				if ((px1 != px) || (py1 != py)) {
					px2 = px;
					py2 = py;
					goto ret;
				}
			}
		}
	}

	return false;

ret:

	lx1 = px1;
	ly1 = py1;
	lx2 = px2;
	ly2 = py2;

	return true;
};
                
}; // namespace surfit;

