
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

#include "surfit_ie.h"
#include "f_triangulate.h"
#include "grid_user.h"
#include "matr.h"
#include "solvers.h"
#include "fileio.h"
#include "bitvec.h"
#include "surf.h"
#include "surf_internal.h"
#include "points.h"
#include "matr_eye.h"
#include "f_surf.h"

#include "f_completer.h"

namespace surfit {

f_triangulate::f_triangulate() : f_method(get_method_name()) 
{
};

f_triangulate::~f_triangulate()
{
};

const char * f_triangulate::get_method_name()
{
	return "triangulation";
};

d_surf * f_triangulate::get_method_surf()
{
	vec * x = create_vec();
	vec * y = create_vec();
	vec * z = create_vec();

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	size_t size = NN*MM;

	size_t i;
	for (i = 0; i < size; i++) {
		if (method_mask_solved->get(i) == false)
			continue;
		REAL X, Y, Z;
		size_t I, J;
		one2two(i, I, J, NN, MM);
		method_grid->getCoordNode(I, J, X, Y);
		Z = (*method_X)(i);
		x->push_back(X);
		y->push_back(Y);
		z->push_back(Z);
	}

	d_points * pnts = create_points(x, y, z);
	d_surf * res = triangulate_points(pnts, method_grid);
	pnts->release();
	return res;
	
};

}; // namespace surfit;


