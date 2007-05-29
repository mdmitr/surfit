
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
#include "vec.h"
#include "sizetvec.h"
#include "bitvec.h"
#include "geom_alg.h"
#include "matr_diag.h"

#include "grid_user.h"
#include "grid_line_user.h"

#include <float.h>
#include <algorithm>
#include <set>

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



f_cntr2::f_cntr2(bool iflag, REAL imult) : functional("f_cntr2", F_CONDITION)
{
	flag = iflag;
	if (flag)
		setType(F_USUAL);
	contours = new std::vector<const d_cntr *>();
	sects_grid = NULL;
	sects = NULL;
	mult = imult;
};

f_cntr2::~f_cntr2() 
{
	if (sects_grid)
		sects_grid->release();
	delete sects;
};

bool f_cntr2::get_flag() const {
	return flag;
};

void f_cntr2::cleanup() 
{
	delete sects;
	sects = NULL;
};

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

void add_DZ(std::vector<REAL> & D, std::vector<REAL> & Z, sect & s)
{
	size_t N = Z.size();
	if (N > 0) {
		if (fabs(s.z - Z[N-1]) < 1e-6)
		{
			if (fabs(s.d - D[N-1]) < 1e-6) {
				return;
			}
		}
	}
	D.push_back(s.d);
	Z.push_back(s.z);
};

bool f_cntr2::minimize()
{
	if (get_flag() == false)
		return false;

	calc_sects(method_mask_solved, method_mask_undefined);
	if (sects == NULL)
		return true;

	recs.clear();
	std::vector<REAL> D;
	std::vector<REAL> Z;

	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();

	sect prev_s = (*sects)[0];
	
	size_t i;
	for (i = 0; i < sects->size(); i++) {
		sect & s = (*sects)[i];
		if ((s.pos1 == prev_s.pos1) && (s.pos2 == prev_s.pos2)) 
		{
			add_DZ(D,Z,s);
			prev_s = s;
		} else {
			prev_s = s;
			i--;
			sect S = (*sects)[i];
			size_t diff = S.pos2 - S.pos1;
			size_t pos1_i, pos1_j;
			if (one2two(S.pos1, pos1_i, pos1_j, NN, MM) == false)
				continue;
			size_t pos2_i, pos2_j;
			if (one2two(S.pos2, pos2_i, pos2_j, NN, MM) == false)
				continue;
			REAL d0, d1;
			if (diff == 1) {
				d0 = method_grid->getCoordNodeX(pos1_i);
				d1 = method_grid->getCoordNodeX(pos2_i);
			} else {
				d0 = method_grid->getCoordNodeY(pos1_j);
				d1 = method_grid->getCoordNodeY(pos2_j);
			}
			if (Z.size() > 1) {
				size_t N = Z.size();
				REAL a = 0, b = 0, c = 0, d = 0;
				size_t k;
				for (k = 0; k < N; k++) {
					a += D[k]*D[k];
					b += D[k];
					c += D[k]*Z[k];
					d += Z[k];
				}

				REAL val0 = -(b*d-c*N)/(a*N-b*b)*d0 + (a*d-b*c)/(a*N-b*b);
				REAL val1 = -(b*d-c*N)/(a*N-b*b)*d1 + (a*d-b*c)/(a*N-b*b);

				if (val0 < 3000)
					bool stop = true;

				if (val1 < 3000)
					bool stop = true;

				(*method_X)(S.pos1) = val0;
				(*method_X)(S.pos2) = val1;
				method_mask_solved->set_true(S.pos1);
				method_mask_solved->set_true(S.pos2);

				bool stop = true;
			} 
			Z.clear();
			D.clear();
		}
	}
			


	return true;
};

bool f_cntr2::solvable_without_cond(const bitvec * mask_solved, 
				    const bitvec * mask_undefined,
				    const extvec * X)
{
	return true;
};

bool f_cntr2::make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined)
{
	calc_sects(mask_solved, mask_undefined);
	if (sects == NULL)
		return false;
	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	bitvec * mask = create_bitvec(matrix_size);
	mask->init_false();
	extvec * diag = create_extvec(matrix_size);

	std::vector<REAL> D;
	std::vector<REAL> Z;

	size_t dbg_cnt = 0;

	sect prev_s = (*sects)[0];
	
	size_t i;
	for (i = 0; i < sects->size(); i++) {
		sect & s = (*sects)[i];
		if ((s.pos1 == prev_s.pos1) && (s.pos2 == prev_s.pos2)) 
		{
			D.push_back(s.d);
			Z.push_back(s.z);
			prev_s = s;
		} else {
			prev_s = s;
			i--;
			sect S = (*sects)[i];
			size_t diff = S.pos2 - S.pos1;
			size_t pos1_i, pos1_j;
			if (one2two(S.pos1, pos1_i, pos1_j, NN, MM) == false)
				continue;
			size_t pos2_i, pos2_j;
			if (one2two(S.pos2, pos2_i, pos2_j, NN, MM) == false)
				continue;
			REAL d0, d1;
			if (diff == 1) {
				d0 = method_grid->getCoordNodeX(pos1_i);
				d1 = method_grid->getCoordNodeX(pos2_i);
			} else {
				d0 = method_grid->getCoordNodeY(pos1_j);
				d1 = method_grid->getCoordNodeY(pos2_j);
			}
			if (get_flag()) {
				if (Z.size() > 1) {
					size_t N = Z.size();
					REAL a = 0, b = 0, c = 0, d = 0;
					size_t k;
					for (k = 0; k < N; k++) {
						a += D[k]*D[k];
						b += D[k];
						c += D[k]*Z[k];
						d += Z[k];
					}

					REAL val0 = -(b*d-c*N)/(a*N-b*b)*d0 + (a*d-b*c)/(a*N-b*b);
					REAL val1 = -(b*d-c*N)/(a*N-b*b)*d1 + (a*d-b*c)/(a*N-b*b);

					REAL x_val0 = (*method_X)(S.pos1);
					REAL x_val1 = (*method_X)(S.pos2);

					REAL dist0 = fabs(val0 - x_val0);
					REAL dist1 = fabs(val1 - x_val1);
					dist0 = 0;
					dist1 = 0;

					mask->set_true(S.pos1);
					(*v)(S.pos1) += val0*(dist0+1)*mult;
					(*diag)(S.pos1) += (dist0+1)*mult;
					
					mask->set_true(S.pos2);
					(*v)(S.pos2) += val1*(dist1+1)*mult;
					(*diag)(S.pos2) += (dist1+1)*mult;

					// a = sum(xi.^2)
					// b= sum(xi)
					// c = sum(xi.*yi)
					// d = sum(yi)
					// n = length(xi)

					// Y0 = -(b*d-c*N)/(a*N-b^2)*x0 + (a*d-b*c)/(a*N-b^2)
					// Y1 = -(b*d-c*N)/(a*N-b^2)*x1 + (a*d-b*c)/(a*N-b^2)

					bool stop = true;
				} 
			} else { // get_flag
				if (Z.size() == 1) 
				{
					if (mask_solved->get(S.pos1))
						goto next_mark;
					if (mask_solved->get(S.pos2))
						goto next_mark;
					REAL z0 = (*method_X)(S.pos1);
					REAL z1 = (*method_X)(S.pos2);
					REAL z = Z[0];
					REAL d = D[0];
					
					REAL val0 = (d0*d0*z0+d0*d1*z1-2*d*d0*z0-d0*d*z1-d1*d0*z+d*d0*z-d*d1*z1+d*d*z0+d*d*z1+d1*d1*z-d*d1*z)/(-2*d*d0-2*d*d1+d0*d0+d1*d1+2*d*d);
					REAL val1 = (-d1*d0*z+d1*d0*z0+d1*d1*z1-d1*d*z0-2*d*d1*z1+d*d1*z-d*d0*z+d0*d0*z-d*d0*z0+d*d*z0+d*d*z1)/(-2*d*d0-2*d*d1+d0*d0+d1*d1+2*d*d);

					REAL plus = -(((d1-d)/(d1-d0))*(z1-z0) + z0 - z);
					//val0 = z0 + plus;
					//val1 = z1 + plus;
					//val0 = z;
					//val1 = z;
					if (z < 3000)
						bool stop = true;

					mask->set_true(S.pos1);
					(*v)(S.pos1) += val0;
					(*diag)(S.pos1) += 1;

					mask->set_true(S.pos2);
					(*v)(S.pos2) += val1;
					(*diag)(S.pos2) += 1;

					// Y0 = (x0^2*y0+x0*x1*y1-2*x*x0*y0-x0*x*y1-x1*x0*y+x*x0*y-x*x1*y1+x^2*y0+x^2*y1+x1^2*y-x*x1*y)/(-2*x*x0-2*x*x1+x0^2+x1^2+2*x^2)
					// Y1 = (-x1*x0*y+x1*x0*y0+x1^2*y1-x1*x*y0-2*x*x1*y1+x*x1*y-x*x0*y+x0^2*y-x*x0*y0+x^2*y0+x^2*y1)/(-2*x*x0-2*x*x1+x0^2+x1^2+2*x^2)

					bool stop = true;
				}
			}
next_mark:
			D.clear();
			Z.clear();
		}
	}

	dbg_cnt = 0;

	if (get_flag() == false)
	{
		size_t i;
		for (i = 0; i < matrix_size; i++) {
			if (mask->get(i) == false)
				continue;
			dbg_cnt++;
			(*v)(i) = (*v)(i) / (*diag)(i);
			REAL test = (*v)(i);
			if (test < 3000)
				bool stop = true;
			REAL dist = fabs((*method_X)(i) - test);
			(*diag)(i) = 1;

			(*diag)(i) = (dist+1)*mult;
			(*v)(i) = (dist+1)*mult*test;
			if (dbg_cnt == 1)
				bool stop = true;
		}
	}

	matr_diag * T = new matr_diag(diag, matrix_size, mask);
	matrix = T;

	bool solvable = true;

	solvable = wrap_sums(matrix, v, mask_solved, mask_undefined) || solvable;
	return solvable;

	return false;
};
	
void f_cntr2::mark_solved_and_undefined(bitvec * mask_solved, 
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

bool sect_cmp(sect & s1, sect & s2)
{
	if (s1.pos1 == s2.pos1)
		return (s1.pos2 < s2.pos2);
	return (s1.pos1 < s2.pos1);
};

bool sect_cmp_z(sect & s1, sect & s2)
{
	return (s1.z < s2.z);
};

void f_cntr2::calc_sects(bitvec * mask_solved, bitvec * mask_undefined)
{
	if (sects_grid) {
		if (sects_grid->operator ==(method_grid))
			return;
		sects_grid->release();
	}
	sects_grid = create_grid(method_grid);
	sects = new std::vector<sect>();
#ifdef DEBUG
	FILE * ff = fopen("c:\\sects.m","w");
	draw_grid_matlab(ff, method_grid, "black");
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
	draw_grid_matlab(ff, grd, "green");
#endif

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
						sects->push_back(s);
						break;
					case DIRECTION_RIGHT:
						i0++;
						if ((j0 == MMM-1) || (j0 == 0))
							continue;
						s.pos1 = two2one(i0-1, j0-1, NN, MM);
						s.pos2 = s.pos1 + NN;
						s.z = z;
						s.d = y;
						sects->push_back(s);
						break;
					case DIRECTION_DOWN:
						j0--;
						if ((i0 == NNN-1) || (i0 == 0))
							continue;
						s.pos1 = two2one(i0-1, j0, NN, MM);
						s.pos2 = s.pos1+1;
						s.z = z;
						s.d = x;
						sects->push_back(s);
						break;
					case DIRECTION_LEFT:
						i0--;
						if ((j0 == MMM-1) || (j0 == 0))
							continue;
						s.pos1 = two2one(i0, j0-1, NN, MM);
						s.pos2 = s.pos1 + NN;
						s.z = z;
						s.d = y;
						sects->push_back(s);
						break;
				}

#ifdef DEBUG
				fprintf(ff,"plot(%g,%g,'.','color','red');\n",x,y);
#endif
				
			}

		}
	}

	grd->release();

	//std::sort(sects->begin(), sects->end(), sect_cmp_z);
	
	std::sort(sects->begin(), sects->end(), sect_cmp);

	if (sects->size() == 0)
		return;

	#ifdef DEBUG
	fclose(ff);
#endif
	return;
};


/*

	std::vector<REAL> D;
	std::vector<REAL> Z;

	sect prev_s = (*res)[0];
	
	for (i = 0; i < res->size(); i++) {
		sect & s = (*res)[i];
		if ((s.pos1 == prev_s.pos1) && (s.pos2 == prev_s.pos2)) 
		{
			D.push_back(s.d);
			Z.push_back(s.z);
			prev_s = s;
		} else {
			prev_s = s;
			i--;
			sect S = (*res)[i];
			size_t diff = S.pos2 - S.pos1;
			size_t pos1_i, pos1_j;
			if (one2two(S.pos1, pos1_i, pos1_j, NN, MM) == false)
				continue;
			size_t pos2_i, pos2_j;
			if (one2two(S.pos2, pos2_i, pos2_j, NN, MM) == false)
				continue;
			REAL d0, d1;
			if (diff == 1) {
				d0 = method_grid->getCoordNodeX(pos1_i);
				d1 = method_grid->getCoordNodeX(pos2_i);
			} else {
				d0 = method_grid->getCoordNodeY(pos1_j);
				d1 = method_grid->getCoordNodeY(pos2_j);
			}
			if (Z.size() > 1) {
				size_t N = Z.size();
				REAL a = 0, b = 0, c = 0, d = 0;
				size_t k;
				for (k = 0; k < N; k++) {
					a += D[k]*D[k];
					b += D[k];
					c += D[k]*Z[k];
					d += Z[k];
				}
				
				REAL val0 = -(b*d-c*N)/(a*N-b*b)*d0 + (a*d-b*c)/(a*N-b*b);
				REAL val1 = -(b*d-c*N)/(a*N-b*b)*d1 + (a*d-b*c)/(a*N-b*b);

				// a = sum(xi.^2)
				// b= sum(xi)
				// c = sum(xi.*yi)
				// d = sum(yi)
				// n = length(xi)

				// Y0 = -(b*d-c*N)/(a*N-b^2)*x0 + (a*d-b*c)/(a*N-b^2)
				// Y1 = -(b*d-c*N)/(a*N-b^2)*x1 + (a*d-b*c)/(a*N-b^2)

				bool stop = true;
			} else {
				REAL z0 = (*method_X)(S.pos1);
				REAL z1 = (*method_X)(S.pos2);
				REAL z = Z[0];
				REAL d = D[0];
				REAL val0 = (d0*d0*z0+d0*d1*z1-2*d*d0*z0-d0*d*z1-d1*d0*z+d*d0*z-d*d1*z1+d*d*z0+d*d*z1+d1*d1*z-d*d1*z)/(-2*d*d0-2*d*d1+d0*d0+d1*d1+2*d*d);
				REAL val1 = (-d1*d0*z+d1*d0*z0+d1*d1*z1-d1*d*z0-2*d*d1*z1+d*d1*z-d*d0*z+d0*d0*z-d*d0*z0+d*d*z0+d*d*z1)/(-2*d*d0-2*d*d1+d0*d0+d1*d1+2*d*d);

				// Y0 = (x0^2*y0+x0*x1*y1-2*x*x0*y0-x0*x*y1-x1*x0*y+x*x0*y-x*x1*y1+x^2*y0+x^2*y1+x1^2*y-x*x1*y)/(-2*x*x0-2*x*x1+x0^2+x1^2+2*x^2)
				// Y1 = (-x1*x0*y+x1*x0*y0+x1^2*y1-x1*x*y0-2*x*x1*y1+x*x1*y-x*x0*y+x0^2*y-x*x0*y0+x^2*y0+x^2*y1)/(-2*x*x0-2*x*x1+x0^2+x1^2+2*x^2)

				bool stop = true;
			}
			D.clear();
			Z.clear();
		}
	}
*/


}; // namespace surfit;

