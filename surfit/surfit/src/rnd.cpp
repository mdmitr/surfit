
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

#include "ie.h"
#include "rnd.h"
#include <math.h>
#include <time.h>

namespace surfit {

#define MAGIC_NUMBER 30
#define STD 0.0526971

void randomize() {
	srand( (unsigned)time( NULL ) );
};

REAL norm_rand(REAL std) {
	REAL res = REAL(0);
	int i;
	for (i = 0; i < MAGIC_NUMBER; i++) {
		res += REAL(rand())/REAL(RAND_MAX);
	}
	return REAL((std/STD)*(res/REAL(MAGIC_NUMBER)-REAL(0.5)));
};

}; // namespace surfit;

