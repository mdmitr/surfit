
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
#include "f_cntr.h"
#include "f_points.h"
#include "points.h"
#include "grid.h"
#include "cntr.h"
#include "surf.h"
#include "surf_internal.h"
#include "sizetvec.h"
#include "geom_alg.h"

#include "grid_user.h"
#include "grid_line_user.h"

#include <float.h>

namespace surfit {

f_cntr::f_cntr(const d_cntr * icontour) :
f_points_user("f_cntr")
{
	contour = icontour;
	if (contour->getName()) {
		setNameF("f_cntr %s", contour->getName());
	}
};

f_cntr::~f_cntr() {};

int f_cntr::this_get_data_count() const 
{
	return 1;;
};

const data * f_cntr::this_get_data(int pos) const 
{
	if (pos == 0)
		return contour;
	return NULL;
};

d_points * f_cntr::get_points() 
{
	d_grid * grd = create_last_grd();
	//pnts = discretize_cntr8(contour, grd, contour->getName());
	pnts = discretize_cntr(contour, MIN(grd->stepX, grd->stepY)/2., contour->getName());
	if (grd)
		grd->release();
	return pnts;
};

//
//
// f_cntr2
//
//



f_cntr2::f_cntr2() : functional("f_cntr2", F_CONDITION)
{
	contours = new std::vector<const d_cntr *>();
};

f_cntr2::~f_cntr2() {};

void f_cntr2::cleanup() {};

int f_cntr2::this_get_data_count() const 
{
	return contours->size();
};

const data * f_cntr2::this_get_data(int pos) const 
{
	if (pos == 0)
		return (*contours)[pos];
	return NULL;
};

void f_cntr2::add_contour(const d_cntr * cntr)
{
	contours->push_back(cntr);
};

bool f_cntr2::minimize()
{
	return false;
};

bool f_cntr2::solvable_without_cond(const bitvec * mask_solved, 
				    const bitvec * mask_undefined,
				    const extvec * X)
{
	return true;
};

bool f_cntr2::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined)
{
	std::vector<sect> * sects = get_sects(mask_solved, mask_undefined);
	return false;
};
	
void f_cntr2::mark_solved_and_undefined(bitvec * mask_solved, 
				        bitvec * mask_undefined,
				        bool i_am_cond)
{
};

std::vector<sect> * f_cntr2::get_sects(const bitvec * mask_solved, const bitvec * mask_undefined)
{
	std::vector<sect> * res = new std::vector<sect>();
#ifdef DEBUG
	FILE * ff = fopen("c:\\sects.m","w");
	draw_grid_matlab(ff, method_grid);
#endif

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	REAL stepX = method_grid->stepX;
	REAL stepY = method_grid->stepY;
	REAL stepX2 = method_grid->stepX/REAL(2);
	REAL stepY2 = method_grid->stepY/REAL(2);

	size_t i;
	for (i = 0; i < contours->size(); i++) 
	{
#ifdef DEBUG
		draw_curv_matlab(ff, (*contours)[i], "blue", 1, ".");
#endif
		const d_cntr * cntr = (*contours)[i];
		size_t j;
		for (j = 0; j < cntr->size()-1; j++) {
			REAL x0, y0;
			REAL x1, y1;
			size_t i0, j0;
			size_t i1, j1;
			x0 = (*(cntr->X))(j);
			x1 = (*(cntr->X))(j+1);
			y0 = (*(cntr->Y))(j);
			y1 = (*(cntr->Y))(j+1);
			method_grid->getCoordPoint(x0, y0, i0, j0);
			method_grid->getCoordPoint(x1, y1, i1, j1);
			if ((i0 == i1) && (j0 == j1))
				continue;

			sizetvec * nns = create_sizetvec();
			add_sect(nns, x0, y0, x1, y1, method_grid);

			size_t q;
			for (q = 0; q < nns->size()-1; q++) {
				size_t pos1 = (*nns)(q);
				size_t pos2 = (*nns)(q+1);
				REAL X0, Y0, X1, Y1, px, py;
				size_t I, J;
				if (one2two(pos1, I, J, NN, MM) == false)
					continue;
				method_grid->getCoordNode(I, J, X0, Y0);
				int diff = pos2-pos1;
				if (diff == 1) {

					X0 += stepX2;
					X1 = X0;
					Y0 -= stepY2;
					Y1 = Y0 + stepY;

					bool bingo = intersect(x0, y0, x1, y1,
							       X0, Y0, X1, Y1,
							       px, py);

					//assert(bingo);
					if (bingo == false)
						continue;

					bool stop = true;
				}
				if (diff == -1) {
				}
				if (diff == NN) {
				}
				if (diff+NN == 0) {
				}
			}

			nns->release();

		}
	}

#ifdef DEBUG
	fclose(ff);
#endif
	return res;
};

}; // namespace surfit;

