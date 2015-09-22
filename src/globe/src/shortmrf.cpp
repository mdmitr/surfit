
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

#include "globe_ie.h"

#include "shortmrf.h"
#include "fileio.h"
#include "shortvec.h"
#include "bitvec.h"

#include <memory.h>
#include <string.h>


namespace surfit {

shortvec * _decomp2d(const shortvec * X,
		     int N, int M, 
		     short undef_value,
		     bool flag)
{

	int newN = N/2;
	int newM = M/2;

	if (N % 2 != 0)
		newN++;
	if (M % 2 != 0)
		newM++;

	shortvec * a = create_shortvec(newN*newM, 0, 0);

	short s1, s2, s3, s4;
	int I, J;

	int i, j;
	for (j = 0; j < newM; j++) {
		for (i = 0; i < newN; i++) {
			I = MIN(N-1,MAX(0,2*i));
			J = MIN(M-1,MAX(0,2*j));
			s1 = (*X)(I + J*N);
			I = MIN(N-1,MAX(0,2*i+1));
			J = MIN(M-1,MAX(0,2*j));
			s2 = (*X)(I + J*N);
			I = MIN(N-1,MAX(0,2*i));
			J = MIN(M-1,MAX(0,2*j+1));
			s3 = (*X)(I + J*N);
			I = MIN(N-1,MAX(0,2*i+1));
			J = MIN(M-1,MAX(0,2*j+1));
			s4 = (*X)(I + J*N);

			if ( (s1 != undef_value) && 
			     (s2 != undef_value) &&
			     (s3 != undef_value) &&
			     (s4 != undef_value) )
				(*a)(i + j*newN) = short( (s1 + s2 + s3 + s4)/REAL(4));
			else {
				if (flag) 
					(*a)(i + j*newN) = undef_value;
				else {
					double sum = 0;
					int cnt = 0;
					if (s1 != undef_value) {
						sum += s1;
						cnt++;
					}
					if (s2 != undef_value) {
						sum += s2;
						cnt++;
					}
					if (s3 != undef_value) {
						sum += s3;
						cnt++;
					}
					if (s4 != undef_value) {
						sum += s4;
						cnt++;
					}
					if (cnt > 0)
						(*a)(i + j*newN) = short( sum/double(cnt));
					else 
						(*a)(i + j*newN) = undef_value;
				}

			}

		}
	}

	return a;
	
};

}; // namespace surfit;

