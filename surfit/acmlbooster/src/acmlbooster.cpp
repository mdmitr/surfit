
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

#include "acmlbooster_ie.h"
#include "acmlbooster.h"
#include "matr.h"
#include "vec.h"
#include "intvec.h"
#include "fileio.h"
#include "vec_alg.h"

#include <acml.h>

#define SOLVER_CG_MAX          40

namespace surfit {

acml_cg * cg_acml = NULL;

struct acml_garb {
	acml_garb() {};
	~acml_garb() {
		delete cg_acml;
	};
};

acml_garb acml_garbage;

void init_acml_solvers() {
	log_printf("loading module acmlbooster v%s\n", "2.2");
	cg_acml = new acml_cg();
};

void acml_cg::solve(matr * T, const vec * V, vec *& X) 
{
	X = cg_with_acml(T,V,V->size()*40,tol,X,FLT_MAX);
};

}; // namespace surfit;

