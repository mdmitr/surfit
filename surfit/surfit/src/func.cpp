
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
#include <float.h>
#include <string.h>

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "func.h"
#include "defarea.h"
#include "datafile.h"
#include "grid.h"
#include "vec.h"
#include "boolvec.h"
#include "vec_alg.h"
#include "mrf.h"
#include "rnd.h"

namespace surfit {

func::func(vec *icoeff, grid *igrd, 
	   const char * newname) : data() {
	grd = igrd;
	coeff = icoeff;
	setName(newname);
	show_smooth = true;
	undef_value = FLT_MAX;

	details_d = new std::vector<vec*>;
	details_h = new std::vector<vec*>;
	details_v = new std::vector<vec*>;
	enlarges_X = new std::vector<bool>;
	enlarges_Y = new std::vector<bool>;
	
};

func::func(defarea * def) {
	int size = def->coeff->size();
	coeff = new vec(size);
	int i;
	for (i = 0; i < size; i++) {
		bool val = (*(def->coeff))(i);
		if (val)
			(*coeff)(i) = 1;
		else
			(*coeff)(i) = 0;
	}
	grd = new grid(def->grd);
	setName(def->getName());
	show_smooth = true;
	undef_value = FLT_MAX;

	details_d = new std::vector<vec*>;
	details_h = new std::vector<vec*>;
	details_v = new std::vector<vec*>;
	enlarges_X = new std::vector<bool>;
	enlarges_Y = new std::vector<bool>;
};

func::~func() {
	delete grd;
	delete coeff;

	std::vector<vec*>::iterator it;
	
	for (it = details_h->begin(); it != details_h->end(); it++)
		delete *it;
	delete details_h;

	for (it = details_v->begin(); it != details_v->end(); it++) 
		delete *it;
	delete details_v;

	for (it = details_d->begin(); it != details_d->end(); it++) 
		delete *it;
	delete details_d;

	delete enlarges_X;
	delete enlarges_Y;
};

bool func::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	minx = grd->getCoordNodeX(0) - grd->stepX/REAL(2);
	maxx = grd->getCoordNodeX(grd->getCountX()-1) + grd->stepX/REAL(2);
	miny = grd->getCoordNodeY(0) - grd->stepY/REAL(2);
	maxy = grd->getCoordNodeY(grd->getCountY()-1) + grd->stepY/REAL(2);
	return true;
};

bool func::getMinMaxZ(REAL & minZ, REAL & maxZ) const {
	int i;
	int max_i = getTrianglesCount();

	minZ = FLT_MAX;
	maxZ = -FLT_MAX;

	REAL x0, y0, z0;
	REAL x1, y1, z1;
	REAL x2, y2, z2;
	for (i = 0; i < max_i; i++) {
		getTriangle(i, x0, y0, z0,
			    x1, y1, z1,
			    x2, y2, z2);

		if (z0 != undef_value) {
			minZ = MIN(minZ, z0);
			maxZ = MAX(maxZ, z0);
		}

		if (z1 != undef_value) {
			minZ = MIN(minZ, z1);
			maxZ = MAX(maxZ, z1);
		}

		if (z2 != undef_value) {
			minZ = MIN(minZ, z2);
			maxZ = MAX(maxZ, z2);
		}
		
		if ( (z0 == undef_value) || (z1 == undef_value) || (z2 == undef_value) )
			continue;
	}

	return true;
};

REAL func::getValue(REAL x, REAL y) const {
	
	REAL start_x, start_y;
	getCoordNode(0,0,start_x,start_y);
	
	x = x - start_x + grd->stepX/REAL(2);
	int i = (int)floor(x / grd->stepX);
	if ((i >= grd->getCountX()) || (i < 0))
		return undef_value;

	y = y - start_y + grd->stepY/REAL(2);
	int j = (int)floor(y / grd->stepY);
	if ((j >= grd->getCountY()) || (j < 0))
		return undef_value;

    return (*coeff)( i + grd->getCountX()*j );
			
};

REAL func::getMinX() const {
	return grd->startX - grd->stepX/REAL(2);
};

REAL func::getMaxX() const {
	return grd->endX + grd->stepX/REAL(2);
};

REAL func::getMinY() const {
	return grd->startY - grd->stepY/REAL(2);
};

REAL func::getMaxY() const {
	return grd->endY + grd->stepY/REAL(2);
};

int func::getTrianglesCount() const {
	if (show_smooth)
		return (grd->getCountX()-1)*(grd->getCountY()-1)*2;
	else
		return grd->getCountX()*grd->getCountY()*2;
};

int func::getTrianglesCount(const REAL & ishow_x_from,
                            const REAL & ishow_x_to,
			    const REAL & ishow_y_from,
			    const REAL & ishow_y_to) {
	
	int res1, res2;
	
	show_i_from = MAX(0,get_i(ishow_x_from));
	show_i_to   = MIN(grd->getCountX(), get_i(ishow_x_to));
	show_j_from = MAX(0,get_j(ishow_y_from));
	show_j_to   = MIN(grd->getCountY(), get_j(ishow_y_to));

	res1 = (show_i_to-show_i_from);
	res2 = (show_j_to-show_j_from);
	
	if (show_smooth) {
		res1--;
		res2--;
	}

	return MAX(0, res1*res2*2);

};

void func::getTriangle(int triangle_number, 
                       REAL &X0, REAL &Y0, REAL &Z0,
                       REAL &X1, REAL &Y1, REAL &Z1,
                       REAL &X2, REAL &Y2, REAL &Z2) const {

	int ost = triangle_number % 2;
	int plate_num = (triangle_number - ost) / 2;
	int i,j;
	int NN = grd->getCountX();
	
	if (show_smooth) {
		i = plate_num % (grd->getCountX()-1);
		j = (plate_num - i)/(grd->getCountX()-1);
		if (ost == 0) {
			grd->getCoordNode(i,j,X0,Y0);
			Z0 = (*coeff)(i + j*NN);

			i += 1;
			grd->getCoordNode(i,j,X1,Y1);
			Z1 = (*coeff)(i + j*NN);

			i -= 1; j += 1;
			grd->getCoordNode(i,j,X2,Y2);
			Z2 = (*coeff)(i + j*NN);
		
		} else {
			i += 1; 
			grd->getCoordNode(i,j,X0,Y0);
			Z0 = (*coeff)(i + j*NN);

			j += 1; 
			grd->getCoordNode(i,j,X1,Y1);
			Z1 = (*coeff)(i + j*NN);

			i -= 1;
			grd->getCoordNode(i,j,X2,Y2);
			Z2 = (*coeff)(i + j*NN);
		}

	} else {
		
		j = plate_num / grd->getCountX();
		i = plate_num - j*grd->getCountX();
		if (ost == 0) {
			grd->getCoordNode(i,j,X0,Y0);
			X0 -= grd->stepX/REAL(2);
			Y0 -= grd->stepY/REAL(2);
			X1 = X0 + grd->stepX;
			Y1 = Y0;
			X2 = X0;
			Y2 = Y0 + grd->stepY;
		} else {
			grd->getCoordNode(i,j,X0,Y0);
			X0 += grd->stepX/REAL(2);
			Y0 += grd->stepY/REAL(2);
			X1 = X0 - grd->stepX;
			Y1 = Y0;
			X2 = X0;
			Y2 = Y0 - grd->stepY;
		}
		
		Z0 = (*coeff)(plate_num);
		Z1 = Z0;
		Z2 = Z0;
		
		X0 -= 0.5;
		X1 -= 0.5;
		X2 -= 0.5;
		
		Y0 -= 0.5;
		Y1 -= 0.5;
		Y2 -= 0.5;

	}


};

void func::getTriangle(int triangle_number, 
                       REAL &X0, REAL &Y0, REAL &Z0,
                       REAL &X1, REAL &Y1, REAL &Z1,
                       REAL &X2, REAL &Y2, REAL &Z2,
		       const REAL & show_x_from,
                       const REAL & show_x_to,
		       const REAL & show_y_from,
		       const REAL & show_y_to) const {

	int ost = triangle_number % 2;
	int plate_num = (triangle_number - ost) / 2;
	int i,j;
	int NN = grd->getCountX();
	
	int areaNN = show_i_to-show_i_from;
	int area_i,area_j;

	if (show_smooth) {
		area_i = plate_num % (areaNN-1);
		area_j = (plate_num - area_i)/(areaNN-1);
		i = show_i_from + area_i; //plate_num % grd->getCountCellX() + area_i;
		j = show_j_from + area_j; //(plate_num - i)/grd->getCountCellX() + area_j;
		if (ost == 0) {
			grd->getCoordNode(i,j,X0,Y0);
			Z0 = (*coeff)(i + j*NN);

			i += 1;
			grd->getCoordNode(i,j,X1,Y1);
			Z1 = (*coeff)(i + j*NN);

			i -= 1; j += 1;
			grd->getCoordNode(i,j,X2,Y2);
			Z2 = (*coeff)(i + j*NN);
		
		} else {
			i += 1; 
			grd->getCoordNode(i,j,X0,Y0);
			Z0 = (*coeff)(i + j*NN);

			j += 1; 
			grd->getCoordNode(i,j,X1,Y1);
			Z1 = (*coeff)(i + j*NN);

			i -= 1;
			grd->getCoordNode(i,j,X2,Y2);
			Z2 = (*coeff)(i + j*NN);
		}

	} else {
		
		j = plate_num / grd->getCountX();
		i = plate_num - j*grd->getCountX();
		if (ost == 0) {
			grd->getCoordNode(i,j,X0,Y0);
			grd->getCoordNode(i+1,j,X1,Y1);
			grd->getCoordNode(i,j+1,X2,Y2);
		} else {
			grd->getCoordNode(i+1,j+1,X0,Y0);
			grd->getCoordNode(i,j+1,X1,Y1);
			grd->getCoordNode(i+1,j,X2,Y2);
			
		}
		
		Z0 = (*coeff)(plate_num);
		Z1 = Z0;
		Z2 = Z0;
		
		X0 -= 0.5;
		X1 -= 0.5;
		X2 -= 0.5;
		
		Y0 -= 0.5;
		Y1 -= 0.5;
		Y2 -= 0.5;

	}
	
};

bool func::writeTags(datafile *df) const {
		
	bool res = true;
	bool op;
	
	op = df->writeTag("func");		res = (res && op);

	if (getName()) {
		op = df->writeString("name", getName()); res = (res && op);
	}
	
	op = grd->writeTags(df);			res = (res && op);
	op = df->writeRealArray("coeff", coeff->begin(), coeff->size()); res = (res && op);
	op = df->writeReal("undef_value", undef_value); res = (res && op);
	op = df->writeEndTag();					res = (res && op);

	return res;
	
};

int func::getCountX() const {
	return grd->getCountX();
};

int func::getCountY() const {
	return grd->getCountY();
};

REAL func::getStepX() const {
	return grd->stepX;
};

REAL func::getStepY() const {
	return grd->stepY;
};

void func::getCoordNode(int i, int j, REAL & x, REAL & y) const {
	grd->getCoordNode(i,j,x,y);
};

REAL func::getCoordNodeX(int i) const {
	return grd->getCoordNodeX(i);
};

REAL func::getCoordNodeY(int j) const {
	return grd->getCoordNodeY(j);
};

int func::get_i(REAL x) const {
	return grd->get_i(x);
};

int func::get_j(REAL y) const {
	return grd->get_j(y);
};

REAL func::mean() const {
	return mean_value(coeff->begin(), coeff->end(), undef_value);
};

REAL func::std(REAL mean) const {
	return std_value(mean, coeff->begin(), coeff->end(), undef_value);
};

REAL func::sum() const {
	return sum_value(coeff->begin(), coeff->end(), undef_value);
};

bool func::compare_grid(const func * fnc) const {
	return ( 
		(grd->operator ==(fnc->grd)) &&
		(coeff->size() == fnc->coeff->size())
	       );
};

void func::plus(const func * fnc) {
	int i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) += val1;
	}
};

void func::minus(const func * fnc) {
	int i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) -= val1;
	}
};

void func::minus_undef(const func * fnc) {
	int i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ( (val1 == undef_value) || (val2 == undef_value) ) {
			(*coeff)(i) = undef_value;
			continue;
		}
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) -= val1;
	}
};

void func::mult(const func * fnc) {
	int i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) *= val1;
	}
};

void func::div(const func * fnc) {
	int i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) /= val1;
	}
};

void func::set(const func * fnc) {
	int i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) = val1;
	}
};

void func::plus(REAL val) {
	int i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) += val;
	}
};

void func::minus(REAL val) {
	int i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) -= val;
	}
};

void func::mult(REAL val) {
	int i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) *= val;
	}
};

void func::div(REAL val) {
	int i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) /= val;
	}
};

void func::set(REAL val) {
	int i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) = val;
	}
};

//
//
// wavelets section
//
//

int func::details_size() const {
	return 1+MIN(details_h->size(),MIN(details_v->size(),details_d->size()));
};

bool func::decompose() {

	writelog(SURFIT_MESSAGE,"func : make decomposition");
	bool enlarge_X = false;
	bool enlarge_Y = false;

	int countX = grd->getCountX();
	int countY = grd->getCountY();

	if (countX % 2 != 0)
		enlarge_X = true;

	if (countY % 2 != 0)
		enlarge_Y = true;
	
	int N = coeff->size()/4;

	if (N <= 1)
		return false;

	REAL * xa_begin = NULL, * xa_end = NULL; // new approx vector
	REAL * xd_begin = NULL, * xd_end = NULL; // diagonal details
	REAL * xh_begin = NULL, * xh_end = NULL; // horizontal details
	REAL * xv_begin = NULL, * xv_end = NULL; // vertical details

	_decomp2d(coeff->ref_begin(), coeff->end(),
		  xa_begin, xa_end,
		  xd_begin, xd_end,
		  xh_begin, xh_end,
		  xv_begin, xv_end,
		  grd->getCountX(),
		  enlarge_X,
		  enlarge_Y);

	vec * xa = new vec(xa_begin, xa_end);
	vec * xd = new vec(xd_begin, xd_end);
	vec * xh = new vec(xh_begin, xh_end);
	vec * xv = new vec(xv_begin, xv_end);

	details_d->push_back(xd);
	details_h->push_back(xh);
	details_v->push_back(xv);
	enlarges_X->push_back(enlarge_X);
	enlarges_Y->push_back(enlarge_Y);

	delete coeff;
	coeff = xa;

	int new_size_x = 0;
	if (enlarge_X) {
		new_size_x = (grd->getCountX() + 1) / 2;
	} else {
		new_size_x = (grd->getCountX()) / 2;
	}
	grd->startX += grd->stepX/REAL(2);
	grd->stepX  *= REAL(2);
	grd->endX    = grd->startX + (new_size_x-1) * grd->stepX;
	new_size_x = grd->getCountX();
	
	
	int new_size_y = 0;
	if (enlarge_Y) {
		new_size_y = (grd->getCountY() + 1) / 2;
	} else {
		new_size_y = (grd->getCountY()) / 2;
	}
	grd->startY += grd->stepY/REAL(2);
	grd->stepY  *= REAL(2);
	grd->endY    = grd->startY + (new_size_y-1) * grd->stepY;
	new_size_y = grd->getCountY();
		
	return true;
};

bool func::auto_decompose(REAL eps, int norm) {

	REAL initial_norm = calc_approx_norm(norm);
	REAL next_norm = initial_norm;
	
	while ( fabs(initial_norm-next_norm) < eps ) {
		
		initial_norm = next_norm;
		
		if ( ! decompose() )
			return true;
		
		next_norm = calc_approx_norm(norm);
		
	}
	
	reconstruct();
	return true;
};

REAL func::calc_approx_norm(int norm_type) const {

	REAL res = REAL(0);

	switch(norm_type) {
	case 0:
		{
			int i;
			for (i = 0; i < coeff->size(); i++) {
				res += (*coeff)(i)*(*coeff)(i);
			}
			return res/(grd->getCountX()*grd->getCountY());
		}
	default:
		{
			return calc_approx_norm(0);
		};
	}
};

bool func::reconstruct() {
	
	int N = details_d->size();

	if (N == 0)
		return false;

	REAL * approx_begin = NULL, * approx_end = NULL;

	std::vector<vec*>::iterator d_it = details_d->end()-1;
	std::vector<vec*>::iterator h_it = details_h->end()-1;
	std::vector<vec*>::iterator v_it = details_v->end()-1;
	std::vector<bool>::iterator b_itX = enlarges_X->end()-1;
	std::vector<bool>::iterator b_itY = enlarges_Y->end()-1;

	_recons2d(approx_begin, approx_end,
		  coeff->begin(), coeff->end(),
		  (*d_it)->begin(), (*d_it)->end(),
		  (*h_it)->begin(), (*h_it)->end(),
		  (*v_it)->begin(), (*v_it)->end(),
		  grd->getCountX(),
		  *b_itX,
		  *b_itY);
							   
	delete coeff;
	delete *d_it; 
	details_d->erase(d_it);
	delete *h_it;
	details_h->erase(h_it);
	delete *v_it;
	details_v->erase(v_it);
	
	coeff = new vec(approx_begin, approx_end);

	// X
	int new_count_x = grd->getCountX()*2;
	grd->stepX  /= REAL(2);
	grd->startX -= grd->stepX/REAL(2);
	grd->endX    = grd->startX + grd->stepX*(new_count_x-1);
	if (*b_itX)
		grd->endX -= grd->stepX;

	int new_count_y = grd->getCountY()*2;
	grd->stepY  /= REAL(2);
	grd->startY -= grd->stepY/REAL(2);
	grd->endY    = grd->startY + grd->stepY*(new_count_y-1);
	if (*b_itY)
		grd->endY -= grd->stepY;

	enlarges_X->erase(b_itX);
	enlarges_Y->erase(b_itY);

	int check_x = getCountX();
	int check_y = getCountY();
	
	return true;
};

bool func::full_reconstruct() {

	writelog(SURFIT_MESSAGE,"func : make reconstruction");
	
	int N = details_d->size();
	bool res = true;

	while ( (N > 0) && res ) {
		res = res && reconstruct();
		N = details_d->size();
	}

	return res;

};

bool func::add_noise(REAL std) {
	int size = coeff->size();
	int i;
	for (i = 0; i < size; i++) {
		(*coeff)(i) += norm_rand(std);
	}
	return true;
};

int func::defined() const {
	int defined = 0;
	int i;
	if (coeff) {
		const REAL * ptr = coeff->begin();
		for (i = 0; i < coeff->size(); i++) {
			if ( *(ptr+i) != undef_value )
				defined++;
		}
	};
	return defined;
};

}; // namespace surfit;

