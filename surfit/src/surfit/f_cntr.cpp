
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

#define DIRECTION_UNDEF    0
#define DIRECTION_UP	   1
#define DIRECTION_RIGHT    2
#define DIRECTION_DOWN     3
#define DIRECTION_LEFT     4

bool moving(size_t i, size_t j, REAL x0, REAL y0, REAL x1, REAL y1, REAL & x, REAL & y, int & direction)
{
	REAL X0, Y0;

	method_grid->getCoordNode(i, j, X0, Y0);
	X0 -= method_grid->stepX/REAL(2);
	Y0 -= method_grid->stepY/REAL(2);
	REAL X1 = X0 + method_grid->stepX;
	REAL Y1 = Y0;
	REAL X2 = X1;
	REAL Y2 = Y0 + method_grid->stepY;
	REAL X3 = X0;
	REAL Y3 = Y2;

	if (direction != DIRECTION_DOWN) {
		bool res = intersect(x0, y0, x1, y1, X2, Y2, X3, Y3, x, y);
		if (res) {
			direction = DIRECTION_UP;
			return true;
		}
	}

	if (direction != DIRECTION_LEFT) {
		bool res = intersect(x0, y0, x1, y1, X1, Y1, X2, Y2, x, y);
		if (res) {
			direction = DIRECTION_RIGHT;
			return true;
		}
	}

	if (direction != DIRECTION_UP) {
		bool res = intersect(x0, y0, x1, y1, X0, Y0, X1, Y1, x, y);
		if (res) {
			direction = DIRECTION_DOWN;
			return true;
		}
	}

	if (direction != DIRECTION_RIGHT) {
		bool res = intersect(x0, y0, x1, y1, X0, Y0, X3, Y3, x, y);
		if (res) {
			direction = DIRECTION_LEFT;
			return true;
		}
	}

	direction = DIRECTION_UNDEF;
	return false;
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

			int direction = DIRECTION_UNDEF;
			REAL x = x0, y = y0;

			while ( moving( i0, j0, x, y, x1, y1, x, y, direction ) )
			{
				switch (direction) {
					case DIRECTION_UP:
						j0++;
						break;
					case DIRECTION_RIGHT:
						i0++;
						break;
					case DIRECTION_DOWN:
						j0--;
						break;
					case DIRECTION_LEFT:
						i0--;
						break;
				}
#ifdef DEBUG
				fprintf(ff,"plot(%g,%g,'.','color','red');\n",x,y);
#endif
			}

		}
	}

#ifdef DEBUG
	fclose(ff);
#endif
	return res;
};

}; // namespace surfit;

