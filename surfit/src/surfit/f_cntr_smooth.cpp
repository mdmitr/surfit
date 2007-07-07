
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
#include "f_cntr_smooth.h"
#include "grid.h"
#include "cntr.h"
#include "grid_user.h"
#include "bitvec.h"
#include "matr_cntrs.h"
#include "geom_alg.h"

#include <algorithm>

namespace surfit {

f_cntr_smooth::f_cntr_smooth(REAL imult) : functional("f_cntr_smooth", F_CONDITION)
{
	contours = new std::vector<const d_cntr *>();
	sects_grid = NULL;
	sects = NULL;
	mult = imult;
};

f_cntr_smooth::~f_cntr_smooth() 
{
	if (sects_grid)
		sects_grid->release();
	delete sects;
};


void f_cntr_smooth::cleanup() 
{
	delete sects;
	sects = NULL;
};

int f_cntr_smooth::this_get_data_count() const 
{
	return contours->size();
};

const data * f_cntr_smooth::this_get_data(int pos) const 
{
	if (pos == 0)
		return (*contours)[pos];
	return NULL;
};

void f_cntr_smooth::add_contour(const d_cntr * cntr)
{
	contours->push_back(cntr);
};

bool f_cntr_smooth::minimize()
{
	return false;
};

bool f_cntr_smooth::solvable_without_cond(const bitvec * mask_solved, 
				    const bitvec * mask_undefined,
				    const extvec * X)
{
	return true;
};

bool f_cntr_smooth::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined)
{
	calc_sects(sects_grid, sects, contours, mask_solved, mask_undefined);
	if (sects == NULL)
		return false;
	if (sects->size() == 0)
		return false;
	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();
	
	std::vector<REAL> D;
	std::vector<REAL> Z;

	sect prev_s = (*sects)[0];

	std::vector<cntr_rec> * matr_data = new std::vector<cntr_rec>();
	
	size_t i;
	for (i = 0; i < sects->size(); i++) {
		sect & s = (*sects)[i];
		if ((s.pos1 == prev_s.pos1) && (s.pos2 == prev_s.pos2)) 
		{
			D.push_back(s.d);
			Z.push_back(s.z);
			prev_s = s;
			if (i != sects->size()-1)
				continue;
		}

		prev_s = s;
		i--;
		sect S = (*sects)[i];

		size_t diff = S.pos2 - S.pos1;

		REAL d0, d1;

		size_t pos1_i, pos1_j;
		if (one2two(S.pos1, pos1_i, pos1_j, NN, MM) == false) {
			assert(0);
			Z.clear();
			D.clear();
			continue;
		}

		size_t pos2_i, pos2_j;
		if (one2two(S.pos2, pos2_i, pos2_j, NN, MM) == false) {
			assert(0);
			Z.clear();
			D.clear();
			continue;
		}

		if (diff == 1) {
			d0 = method_grid->getCoordNodeX(pos1_i);
			d1 = method_grid->getCoordNodeX(pos2_i);
		} else {
			d0 = method_grid->getCoordNodeY(pos1_j);
			d1 = method_grid->getCoordNodeY(pos2_j);
		}

		REAL sum1 = 0;
		REAL sum2 = 0;
		REAL sum3 = 0;
		REAL sum4 = 0;
		REAL sum5 = 0;
		size_t q;
		for (q = 0; q < Z.size(); q++) {
			D[q] -= d0;
			REAL v1 = (D[q])/(d1-d0);
			REAL v2 = (1 - v1);

			sum1 += v2*v2;
			sum2 += v1*v2;
			sum3 += v1*v1;
			sum4 += Z[q]*v2;
			sum5 += Z[q]*v1;
		}

		cntr_rec rec;
		rec.pos1 = S.pos1;
		rec.pos2 = S.pos2;
		rec.sum1 = sum1/REAL(Z.size());
		rec.sum2 = sum2/REAL(Z.size());
		rec.sum3 = sum3/REAL(Z.size());
		rec.sum4 = sum4/REAL(Z.size());
		rec.sum5 = sum5/REAL(Z.size());
		matr_data->push_back(rec);
		mask->set_true(S.pos1);
		mask->set_true(S.pos2);

		Z.clear();
		D.clear();

		if (i == sects->size()-2)
			break;

	}

	if (matr_data->size() == 0)
	{
		assert(0);
	}

	matr_cntrs * T = new matr_cntrs(mult, matr_data, matrix_size, mask, NN, MM);
	T->fill_vector(v);
	matrix = T;

	bool solvable = true;

	solvable = wrap_sums(matrix, v, mask_solved, mask_undefined) || solvable;
	return solvable;
};
	
void f_cntr_smooth::mark_solved_and_undefined(bitvec * mask_solved, 
				        bitvec * mask_undefined,
				        bool i_am_cond)
{
	mark_sums(mask_solved, mask_undefined);
};














#define DIRECTION_UNDEF    0
#define DIRECTION_UP	   1
#define DIRECTION_RIGHT    2
#define DIRECTION_DOWN     3
#define DIRECTION_LEFT     4

inline
bool eq_points(REAL x0, REAL y0, REAL x1, REAL y1) 
{
	if (x0 != x1)
		return false;
	if (y0 != y1)
		return false;
	return true;
};

bool moving(size_t i, size_t j, 
	    REAL x0, REAL y0, REAL z0, 
	    REAL x1, REAL y1, REAL z1,
	    REAL & x, REAL & y, REAL & z,
	    int & direction,
	    d_grid * grd)
{
	REAL X0, Y0;

	grd->getCoordNode(i, j, X0, Y0);
	X0 -= grd->stepX/REAL(2);
	Y0 -= grd->stepY/REAL(2);
	REAL X1 = X0 + grd->stepX;
	REAL Y1 = Y0;
	REAL X2 = X1;
	REAL Y2 = Y0 + grd->stepY;
	REAL X3 = X0;
	REAL Y3 = Y2;

	z = z1; //!!!!!!!!!!!!!!!!!!!!!!!

	if (direction != DIRECTION_DOWN) {
		bool res = intersect(x0, y0, x1, y1, X2, Y2, X3, Y3, x, y);
		res = (res && (eq_points(x0, y0, x, y) == false));
		if (res) {
			direction = DIRECTION_UP;
			goto ret_true;
		}
	}

	if (direction != DIRECTION_LEFT) {
		bool res = intersect(x0, y0, x1, y1, X1, Y1, X2, Y2, x, y);
		res = (res && (eq_points(x0, y0, x, y) == false));
		if (res) {
			direction = DIRECTION_RIGHT;
			goto ret_true;
		}
	}

	if (direction != DIRECTION_UP) {
		bool res = intersect(x0, y0, x1, y1, X0, Y0, X1, Y1, x, y);
		res = (res && (eq_points(x0, y0, x, y) == false));
		if (res) {
			direction = DIRECTION_DOWN;
			goto ret_true;
		}
	}

	if (direction != DIRECTION_RIGHT) {
		bool res = intersect(x0, y0, x1, y1, X0, Y0, X3, Y3, x, y);
		res = (res && (eq_points(x0, y0, x, y) == false));
		if (res) {
			direction = DIRECTION_LEFT;
			goto ret_true;
		}
	}

	direction = DIRECTION_UNDEF;
	return false;
ret_true:
	if (z0 == z1)
		z = z0;
	else {
		REAL dist = (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0);
		REAL sub_dist = (x-x0)*(x-x0) + (y-y0)*(y-y0);
		z = (z1-z0)*sub_dist/dist + z0;
	}
	return true;
};

inline
bool sect_cmp(const sect & s1, const sect & s2)
{
	if (s1.pos1 == s2.pos1)
		return (s1.pos2 < s2.pos2);
	return (s1.pos1 < s2.pos1);
};

inline
bool sect_cmp_z(const sect & s1, const sect & s2)
{
	return (s1.z < s2.z);
};

bool add_sect(std::vector<sect> * sects, sect & s)
{
	sects->push_back(s);
	return true;
};

bool calc_sects(d_grid *& sects_grid, 
		std::vector<sect> *& sects,
		std::vector<const d_cntr *> * contours,
		bitvec * mask_solved, 
		bitvec * mask_undefined)
{
#ifdef DEBUG
	bool enable_drawing = false;
#endif
	if (sects_grid) {
		if (sects_grid->operator ==(method_grid))
			return false;
		sects_grid->release();
	}
	sects_grid = create_grid(method_grid);
	sects = new std::vector<sect>();
	
#ifdef DEBUG
	FILE * ff = NULL;
	if (enable_drawing) {
		ff = fopen("c:\\sects.m","w");
		draw_grid_matlab(ff, method_grid, "black");
	}
#endif
	

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	REAL stepX = method_grid->stepX;
	REAL stepY = method_grid->stepY;
	REAL stepX2 = method_grid->stepX/REAL(2);
	REAL stepY2 = method_grid->stepY/REAL(2);

	d_grid * grd = create_grid(method_grid);
	grd->startX -= stepX2;
	grd->endX += stepX2;
	grd->startY -= stepY2;
	grd->endY += stepY2;

	size_t NNN = grd->getCountX();
	size_t MMM = grd->getCountY();

#ifdef DEBUG
	if (enable_drawing)
		draw_grid_matlab(ff, grd, "green");
#endif
	

	size_t i;
	for (i = 0; i < contours->size(); i++) 
	{
		
#ifdef DEBUG
		if (enable_drawing)
			draw_curv_matlab(ff, (*contours)[i], "blue", 1, ".");
#endif
		
		const d_cntr * cntr = (*contours)[i];
		size_t j;
		for (j = 0; j < cntr->size()-1; j++) {
			REAL x0, y0;
			REAL x1, y1;
			REAL z0, z1;
			size_t i0, j0;
			size_t i1, j1;
			x0 = (*(cntr->X))(j);
			x1 = (*(cntr->X))(j+1);
			y0 = (*(cntr->Y))(j);
			y1 = (*(cntr->Y))(j+1);
			z0 = (*(cntr->Z))(j);
			z1 = (*(cntr->Z))(j+1);
			grd->getCoordPoint(x0, y0, i0, j0);
			grd->getCoordPoint(x1, y1, i1, j1);
			if ((i0 == i1) && (j0 == j1))
				continue;

			int direction = DIRECTION_UNDEF;
			REAL x = x0, y = y0, z = z0;

			sect s;

			while ( moving( i0, j0, 
					x, y, z, 
					x1, y1, z1, 
					x, y, z, 
					direction, grd ) )
			{
				switch (direction) {
					case DIRECTION_UP:
						j0++;
						if ((i0 == NNN-1) || (i0 == 0))
							continue;
						s.pos1 = two2one(i0-1, j0-1, NN, MM);
						s.pos2 = s.pos1+1;
						s.z = z;
						s.d = x;
						add_sect(sects, s);
						break;
					case DIRECTION_RIGHT:
						i0++;
						if ((j0 == MMM-1) || (j0 == 0))
							continue;
						s.pos1 = two2one(i0-1, j0-1, NN, MM);
						s.pos2 = s.pos1 + NN;
						s.z = z;
						s.d = y;
						add_sect(sects, s);
						break;
					case DIRECTION_DOWN:
						j0--;
						if ((i0 == NNN-1) || (i0 == 0))
							continue;
						s.pos1 = two2one(i0-1, j0, NN, MM);
						s.pos2 = s.pos1+1;
						s.z = z;
						s.d = x;
						add_sect(sects, s);
						break;
					case DIRECTION_LEFT:
						i0--;
						if ((j0 == MMM-1) || (j0 == 0))
							continue;
						s.pos1 = two2one(i0, j0-1, NN, MM);
						s.pos2 = s.pos1 + NN;
						s.z = z;
						s.d = y;
						add_sect(sects, s);
						break;
				}

#ifdef DEBUG
				if (enable_drawing)
					fprintf(ff,"plot(%g,%g,'.','color','red');\n",x,y);
#endif
				
				
			}

		}
	}

	grd->release();

	//std::sort(sects->begin(), sects->end(), sect_cmp_z);
	
	std::sort(sects->begin(), sects->end(), sect_cmp);

	if (sects->size() == 0)
		return true;

#ifdef DEBUG
	if (enable_drawing)
		fclose(ff);
#endif

	return true;
};

}; // namespace surfit

