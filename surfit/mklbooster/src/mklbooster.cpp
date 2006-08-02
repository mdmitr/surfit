
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

#include "mklbooster_ie.h"
#include "mklbooster.h"
#include "matr.h"
#include "vec.h"
#include "intvec.h"
#include "fileio.h"
#include "vec_alg.h"

#include <mkl_blas.h>

#define SOLVER_CG_MAX          40

namespace surfit {

mkl_cg * cg_mkl = NULL;

struct mkl_garb {
	mkl_garb() {};
	~mkl_garb() {
		delete cg_mkl;
	};
};

mkl_garb mkl_garbage;

void init_mkl_solvers() {
	Tcl_printf("mklbooster version %s, Copyright (c) 2002-2006 M.V.Dmitrievsky\n", "2.1");
	Tcl_printf("mklbooster comes with ABSOLUTELY NO WARRANTY; for details type `show_w'.\n");
	Tcl_printf("This is free software, and you are welcome to redistribute it\n");
	Tcl_printf("under certain conditions; type `show_c' for details.\n");
	cg_mkl = new mkl_cg();
};

void mkl_cg::solve(matr * T, const vec * V, vec *& X) 
{
	X = cg_with_mkl(T,V,V->size()*40,tol,X,FLT_MAX);
};

}; // namespace surfit;

