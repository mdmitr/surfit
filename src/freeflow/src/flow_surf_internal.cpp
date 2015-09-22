
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

#include "flow_ie.h"

#include "fileio.h"

#include "flow_surf_internal.h"
#include "variables_tcl.h"
#include "surf.h"
#include "grid.h"
#include "vec.h"

#include <float.h>

namespace surfit {

REAL _surf_debit(d_surf * fnc, REAL x, REAL y, REAL perm, REAL visc, REAL mult) {

	if (!fnc) {
		writelog(LOG_ERROR,"_surf_debit : no surfit_surf loaded");
		return undef_value;
	}

	size_t i,j;

	REAL stepX = fnc->grd->stepX;
	REAL stepY = fnc->grd->stepY;

	x += stepX/REAL(2);
	y += stepY/REAL(2);

	fnc->grd->getCoordPoint(x, y, i, j);

	size_t NN = fnc->getCountX();
	size_t pos_0 = i + j*NN;
	size_t pos_1 = (i-1) +     j*NN;
	size_t pos_2 = i     + (j+1)*NN;
	size_t pos_3 = (i+1) +     j*NN;
	size_t pos_4 =  i    + (j-1)*NN;

	REAL val0 = (*fnc->coeff)(pos_0);
	REAL val1 = (*fnc->coeff)(pos_1);
	REAL val2 = (*fnc->coeff)(pos_2);
	REAL val3 = (*fnc->coeff)(pos_3);
	REAL val4 = (*fnc->coeff)(pos_4);

	if (val0 == undef_value)
		return undef_value;

	if (val1 == undef_value)
		return undef_value;

	if (val2 == undef_value)
		return undef_value;

	if (val3 == undef_value)
		return undef_value;
	
	if (val4 == undef_value)
		return undef_value;
	
	return ( (val0-val1) + (val0-val2) + (val0-val3) + (val0-val4) )*perm/visc*mult;
	
};

REAL _surf_debit_rect(d_surf * fnc, REAL x1, REAL y1, REAL x2, REAL y2,
		      REAL perm, REAL visc, REAL mult) {
	
	if (!fnc) {
		writelog(LOG_ERROR,"_surf_debit : no surfit_surf loaded");
		return undef_value;
	}

	// swap points
	if (x1 > x2)
		std::swap( x1, x2 );
	
	if (y1 > y2)
		std::swap( y1, y2 );


	size_t i1, j1;
	size_t i2, j2;
	
	REAL stepX = fnc->grd->stepX;
	REAL stepY = fnc->grd->stepY;

	x1 += stepX/REAL(2) + stepX*1e-6;
	y1 += stepY/REAL(2) + stepY*1e-6;

	fnc->grd->getCoordPoint(x1, y1, i1, j1);

	x2 += stepX/REAL(2) + stepX*1e-6;
	y2 += stepY/REAL(2) + stepY*1e-6;

	fnc->grd->getCoordPoint(x2, y2, i2, j2);

	size_t NN = fnc->getCountX();
	size_t MM = fnc->getCountY();

	if ((i1 < 1)   || 
		(i1 >= NN-1) || 
		(i2 < 1)   || 
		(i2 >= NN-1) ||
		(j1 < 1)   ||
		(j1 >= MM-1) ||
		(j2 < 1)     ||
		(j2 >= MM-1) )
		return FLT_MAX;

	REAL res = REAL(0);
	size_t pos1, pos2;
	REAL val1, val2;

	REAL hx = fnc->grd->stepX;
	REAL hy = fnc->grd->stepY;

	size_t i, j;

	//         4
	//    |--------|
	//  1 |        | 3
	//    |--------|
	//         2

	// side 1
	i = i1;
	for (j = j1; j <= j2; j++) {
		
		pos2 = i + j*NN;
		pos1 = (i-1) + j*NN;
		
		val2 = (*fnc->coeff)(pos2);
		val1 = (*fnc->coeff)(pos1);
		
		if (val2 == undef_value)
			return undef_value;

		if (val1 == undef_value)
			return undef_value;

		res += (val2 - val1)*hy/hx;
	};

	// side 2
	j = j1;
	for (i = i1; i <= i2; i++) {
		
		pos2 = i + j*NN;
		pos1 = i + (j-1)*NN;
		
		val2 = (*fnc->coeff)(pos2);
		val1 = (*fnc->coeff)(pos1);
		
		if (val2 == undef_value)
			return undef_value;

		if (val1 == undef_value)
			return undef_value;

		res += (val2 - val1)*hx/hy;
	};

	// side 3
	i = i2;
	for (j = j1; j <= j2; j++) {
		
		pos2 = (i+1) + j*NN;
		pos1 = i + j*NN;
		
		val2 = (*fnc->coeff)(pos2);
		val1 = (*fnc->coeff)(pos1);
		
		if (val2 == undef_value)
			return undef_value;

		if (val1 == undef_value)
			return undef_value;

		res -= (val2 - val1)*hy/hx;
	};

	// side 4
	j = j2;
	for (i = i1; i <= i2; i++) {
		
		pos2 = i + (j+1)*NN;
		pos1 = i + j*NN;
		
		val2 = (*fnc->coeff)(pos2);
		val1 = (*fnc->coeff)(pos1);
		
		if (val2 == undef_value)
			return undef_value;

		if (val1 == undef_value)
			return undef_value;

		res -= (val2 - val1)*hx/hy;
	};

	return res*(perm/visc*mult);

};


}; // namespace surfit;

