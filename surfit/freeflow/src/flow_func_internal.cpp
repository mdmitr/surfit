
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

#include "flow_ie.h"
#include "variables_tcl.h"
#include "func.h"
#include "grid.h"
#include "vec.h"
#include "flow_variables.h"
#include "fileio.h"
#include "lcm_simple.h"

#include "func_user.h"
#include "lcm_simple_user.h"

#include <float.h>

namespace surfit {

REAL _func_debit(func * fnc, REAL x, REAL y) {
	if (!fnc) {
		writelog(SURFIT_ERROR,"_func_debit : no surfit_func loaded");
		return undef_value;
	}

	if (!flow_lcm_simple) {
		writelog(SURFIT_MESSAGE,"can't calc debit, load lcm_simple first!");
		return undef_value;
	}

	int i,j;

	REAL stepX = surfit_func->grd->stepX;
	REAL stepY = surfit_func->grd->stepY;

	x += stepX/REAL(2);
	y += stepY/REAL(2);

	surfit_func->grd->getCoordPoint(x, y, i, j);

	int NN = surfit_func->getCountX();
	int pos_0 = i + j*NN;
	int pos_1 = (i-1) +     j*NN;
	int pos_2 = i     + (j+1)*NN;
	int pos_3 = (i+1) +     j*NN;
	int pos_4 =  i    + (j-1)*NN;

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

	REAL perm = flow_lcm_simple->permeability;
	REAL visc = flow_lcm_simple->viscosity;
	REAL mult = flow_lcm_simple->multiplier;

	return ( (val0-val1) + (val0-val2) + (val0-val3) + (val0-val4) )*perm/visc*mult;

};

REAL _func_debit_rect(func * fnc, REAL x1, REAL y1, REAL x2, REAL y2) {
	
	if (!fnc) {
		writelog(SURFIT_ERROR,"_func_debit : no surfit_func loaded");
		return undef_value;
	}

	if (!flow_lcm_simple) {
		writelog(SURFIT_MESSAGE,"can't calc debit, load lcm_simple first!");
		return undef_value;
	}

	// swap points
	if (x1 > x2)
		std::swap( x1, x2 );
	
	if (y1 > y2)
		std::swap( y1, y2 );


	int i1, j1;
	int i2, j2;
	
	REAL stepX = fnc->grd->stepX;
	REAL stepY = fnc->grd->stepY;

	x1 += stepX/REAL(2) + stepX*1e-6;
	y1 += stepY/REAL(2) + stepY*1e-6;

	fnc->grd->getCoordPoint(x1, y1, i1, j1);

	x2 += stepX/REAL(2) + stepX*1e-6;
	y2 += stepY/REAL(2) + stepY*1e-6;

	fnc->grd->getCoordPoint(x2, y2, i2, j2);

	int NN = fnc->getCountX();
	int MM = fnc->getCountY();

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
	int pos1, pos2;
	REAL val1, val2;

	REAL hx = fnc->grd->stepX;
	REAL hy = fnc->grd->stepY;

	/*
	REAL div = hx/hy;
	if (div > 1) {
		hx = 1;
		hy = REAL(1)/div;
	} else {
		hx = div;
		hy = 1;
	}
	*/

	int i, j;

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

	REAL perm = flow_lcm_simple->permeability;
	REAL visc = flow_lcm_simple->viscosity;
	REAL mult = flow_lcm_simple->multiplier;

	return res*(perm/visc*mult);

};


}; // namespace surfit;

