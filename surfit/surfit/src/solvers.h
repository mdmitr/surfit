
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

#ifndef __surfit__solvers__
#define __surfit__solvers__

#define SOLVER_CG	       0
#define SOLVER_CG2		   1
#define SOLVER_SIMPITER    2
#define SOLVER_SIMPITER2   3
#define SOLVER_SOR	       4
#define SOLVER_SSOR	       5
#define SOLVER_JACOBI      6

#define SOLVER_DEFAULT  SOLVER_CG

#define SOLVER_CG_MAX          40
#define SOLVER_CG2_MAX         40
#define SOLVER_SIMPITER_MAX   100
#define SOLVER_SIMPITER2_MAX  100

// solvers
#include "cg.h"
#include "cg2.h"
#include "simpiter.h"
#include "simpiter2.h"
#include "sor.h"
#include "ssor.h"
#include "jacobi.h"

namespace surfit {

class vec;

/*! \ingroup internal
    \fn const char * solver_name(int code);
    \return solver name by code
*/
const char * solver_name(int code);

template <class Matr, class Vect>
void solve(Matr * T, Vect * V, int solver_code, vec *& X) {
	switch (solver_code) {
	case SOLVER_CG:
		X = cg(T,V,V->size()*SOLVER_CG_MAX,tol,X,FLT_MAX);
		break;
	case SOLVER_CG2:
		X = cg2(T,V,V->size()*SOLVER_CG2_MAX,tol,X);
		break;
	case SOLVER_SIMPITER:
		X = simpiter(T,V,V->size()*SOLVER_SIMPITER2_MAX,tol,X);
		break;
	case SOLVER_SIMPITER2:
		X = simpiter2(T,V,V->size()*SOLVER_SIMPITER2_MAX,tol,X);
		break;
	case SOLVER_SOR:
		X = sor(T,V,V->size()*SOLVER_SIMPITER2_MAX,tol,X);
		break;
	case SOLVER_SSOR:
		X = ssor(T,V,V->size()*SOLVER_SIMPITER2_MAX,tol,X);
		break;
	case SOLVER_JACOBI:
		X = jacobi(T,V,V->size()*SOLVER_SIMPITER2_MAX,tol,X);
		break;
	default:
		writelog(SURFIT_DEBUG, "isbsfm_bf : wrong solver_code" );
	}
};

};

#endif

