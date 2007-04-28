
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

#include "sstuff_ie.h"
#include "stepFunc.h"

#include <algorithm>
#include <vector>

#include <math.h>
#include <float.h>

namespace surfit {

double stepFunc(double StartX, double EndX, int amount) {
	if (StartX > EndX) return 0.;
	double step = (EndX - StartX)/(double)amount;
	if (step == 0)
		return step;

	int n = 0;
	double a = log(step)/log(10.);
	if( a >= 0. ) n = (int)a;
	else n = (int)a - 1;

	double n10 = 1.;
	int i;
	for( i = 0; i < abs(n); i++ ) n10 = n10*10.;

	if( n < 0 ) n10 = 1./n10;

	for( i = 1; i <= 8; i++ )
	{
		double step1 = i*n10,
			   step2 = (i+1)*n10;
		if( !i ) if( step < step1 ) return step1;
		if( i == 9 - 2 ) if( step > step2 ) return step2;
		
		if( step >= step1 && step < step2 )
		{
			if( step - step1 <= step2 - step ) return step1;
			else
				return step2;
		}
	}

	return FLT_MAX;
};


}; // namespace surfit;

