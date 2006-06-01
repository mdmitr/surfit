
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
#include <float.h>
#include <string.h>

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "surf.h"
#include "mask.h"
#include "datafile.h"
#include "grid.h"
#include "vec.h"
#include "bitvec.h"
#include "vec_alg.h"
#include "mrf.h"
#include "rnd.h"
#include "free_elements.h"
#include "grid_internal.h"
#include "surf_internal.h"

#include "grid_user.h"

namespace surfit {

d_surf * create_surf(vec *icoeff, d_grid *igrd, const char * surfname) {
	return new d_surf(icoeff, igrd, surfname);
};

d_surf * create_surf_by_mask(d_mask * msk) {
	return new d_surf(msk);
};

d_surf::d_surf(vec *icoeff, d_grid *igrd, 
	       const char * newname) : data("surf") {
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

d_surf::d_surf(d_mask * msk) : data("d_surf") {
	size_t size = msk->coeff->size();
	coeff = create_vec(size);
	size_t i;
	for (i = 0; i < size; i++) {
		bool val = msk->coeff->get(i);
		if (val)
			(*coeff)(i) = 1;
		else
			(*coeff)(i) = 0;
	}
	grd = create_grid(msk->grd);
	setName(msk->getName());
	show_smooth = true;
	undef_value = FLT_MAX;

	details_d = new std::vector<vec*>;
	details_h = new std::vector<vec*>;
	details_v = new std::vector<vec*>;
	enlarges_X = new std::vector<bool>;
	enlarges_Y = new std::vector<bool>;
};

d_surf::~d_surf() {
	if (grd)
		grd->release();
	if (coeff)
		coeff->release();
	
	std::vector<vec*>::iterator it;
	
	for (it = details_h->begin(); it != details_h->end(); it++) {
		if (*it)
			(*it)->release();
	}
	delete details_h;

	for (it = details_v->begin(); it != details_v->end(); it++) {
		if (*it)
			(*it)->release();
	}
	delete details_v;

	for (it = details_d->begin(); it != details_d->end(); it++) {
		if (*it)
			(*it)->release();
	}
	delete details_d;

	delete enlarges_X;
	delete enlarges_Y;
};

bool d_surf::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	minx = grd->getCoordNodeX(0) - grd->stepX/REAL(2);
	maxx = grd->getCoordNodeX(grd->getCountX()-1) + grd->stepX/REAL(2);
	miny = grd->getCoordNodeY(0) - grd->stepY/REAL(2);
	maxy = grd->getCoordNodeY(grd->getCountY()-1) + grd->stepY/REAL(2);
	return true;
};

bool d_surf::getMinMaxZ(REAL & minZ, REAL & maxZ) const {
	return getMinMaxZ_mask(minZ, maxZ, NULL);
};

bool d_surf::getMinMaxZ_mask(REAL & minZ, REAL & maxZ, const bitvec * msk) const {
	size_t i;
	REAL value;

	minZ = FLT_MAX;
	maxZ = -FLT_MAX;

	for (i = 0; i < grd->getCountX()*grd->getCountY(); i++) {

		if (msk) {
			if (msk->get(i) == false)
				continue;
		}

		value = (*coeff)(i);
		if (value == this->undef_value)
			continue;

		minZ = MIN(minZ, value);
		maxZ = MAX(maxZ, value);

	}

	return true;
};

REAL d_surf::getValue(REAL x, REAL y) const {
	
	REAL start_x, start_y;
	getCoordNode(0,0,start_x,start_y);
	
	x = x - start_x + grd->stepX/REAL(2);
	size_t i = (size_t)MAX(0,floor(x / grd->stepX));
	if ((i >= grd->getCountX()) || (i < 0))
		return undef_value;

	y = y - start_y + grd->stepY/REAL(2);
	size_t j = (size_t)MAX(0,floor(y / grd->stepY));
	if ((j >= grd->getCountY()) || (j < 0))
		return undef_value;

	return (*coeff)( i + grd->getCountX()*j );
			
};

REAL d_surf::getInterpValue(REAL x, REAL y) const {
	
	REAL value = 0;
	size_t I0, J0, I1, J1;
	size_t surf_sizeX = getCountX();
	size_t surf_sizeY = getCountY();
	REAL z0, z1, z2, z3;
	REAL x0, y0;
	REAL delta_x, delta_y;
	REAL hX = grd->stepX;
	REAL hY = grd->stepY;
	
	const d_grid * g = grd;
	I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
	J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));
	
	I1 = I0+1;
	J1 = J0+1;
	
	I0 = MIN(MAX( 0, I0 ), surf_sizeX-1);
	I1 = MIN(MAX( 0, I1 ), surf_sizeX-1);
	J0 = MIN(MAX( 0, J0 ), surf_sizeY-1);
	J1 = MIN(MAX( 0, J1 ), surf_sizeY-1);
	
	getCoordNode(I0, J0, x0, y0);
	
	z0 = (*(coeff))(I0 + surf_sizeX*J0);
	z1 = (*(coeff))(I1 + surf_sizeX*J0);
	z2 = (*(coeff))(I1 + surf_sizeX*J1);
	z3 = (*(coeff))(I0 + surf_sizeX*J1);
	
	if (
		(z0 == this->undef_value) ||
		(z1 == this->undef_value) ||
		(z2 == this->undef_value) ||
		(z3 == this->undef_value) 
		) 
	{
		
		REAL sum = REAL(0);
		size_t cnt = 0;
		
		if (z0 != this->undef_value) {
			sum += z0;
			cnt++;
		}
		if (z1 != this->undef_value) {
			sum += z1;
			cnt++;
		}
		if (z2 != this->undef_value) {
			sum += z2;
			cnt++;
		}
		if (z3 != this->undef_value) {
			sum += z3;
			cnt++;
		}
		
		if (cnt == 0) {
			return this->undef_value;
		}
		
		REAL mean_z = sum/REAL(cnt);
		if (z0 == this->undef_value)
			z0 = mean_z;
		if (z1 == this->undef_value)
			z1 = mean_z;
		if (z2 == this->undef_value)
			z2 = mean_z;
		if (z3 == this->undef_value)
			z3 = mean_z;
		
	}
	
	delta_x = x - x0;
	delta_y = y - y0;
	
	// первый шаг линейной интерпол€ции
	REAL z11 = (z2-z1)*delta_y/hY+z1;
	REAL z22 = (z3-z0)*delta_y/hY+z0;
	
	// второй шаг линейной интерпол€ции
	REAL res = (z11-z22)*delta_x/hX+z22;
								
	return res;
	
};

REAL d_surf::getMeanValue(REAL x_from, REAL x_to, REAL y_from, REAL y_to) const {
	size_t i_from, i_to;
	size_t j_from, j_to;

	
	i_from = get_i(x_from);
	i_from = MAX(0, i_from);
	
	i_to   = get_i(x_to);
	i_to   = MIN(i_to, getCountX()-1);
	
	j_from = get_j(y_from);
	j_from = MAX(0, j_from);
	
	j_to   = get_j(y_to);
	j_to   = MIN(j_to, getCountY()-1);

	size_t NN = getCountX();

	size_t i,j;
	size_t cnt = 0;
	REAL sum_value = 0;
	REAL value;
	for (j = j_from; j <= j_to; j++) {
		for (i = i_from; i <= i_to; i++) {
		
			size_t pos = i + j*NN;
			value = (*coeff)(pos);
			if (value == this->undef_value)
				continue;
			sum_value += value;
			cnt++;
		};
	};

	if (cnt == 0)
		return this->undef_value;

	REAL res = sum_value/REAL(cnt);
	return res;

};

REAL d_surf::getValueIJ(size_t I, size_t J) const {
	if (I < 0)
		return FLT_MAX;
	if (I >= grd->getCountX())
		return FLT_MAX;
	if (J < 0)
		return FLT_MAX;
	if (J >= grd->getCountY())
		return FLT_MAX;

	return (*coeff)( I + grd->getCountX()*J );
};

REAL d_surf::getMinX() const {
	return grd->startX - grd->stepX/REAL(2);
};

REAL d_surf::getMaxX() const {
	return grd->endX + grd->stepX/REAL(2);
};

REAL d_surf::getMinY() const {
	return grd->startY - grd->stepY/REAL(2);
};

REAL d_surf::getMaxY() const {
	return grd->endY + grd->stepY/REAL(2);
};

bool d_surf::writeTags(datafile *df) const {
		
	bool res = true;
	bool op;
	
	op = df->writeTag("surf");		res = (res && op);

	if (getName()) {
		op = df->writeString("name", getName()); res = (res && op);
	}
	
	op = grd->writeTags(df);			res = (res && op);
	op = df->writeRealArray("coeff", coeff); res = (res && op);
	op = df->writeReal("undef_value", undef_value); res = (res && op);
	op = df->writeEndTag();					res = (res && op);

	return res;
	
};

size_t d_surf::getCountX() const {
	return grd->getCountX();
};

size_t d_surf::getCountY() const {
	return grd->getCountY();
};

REAL d_surf::getStepX() const {
	return grd->stepX;
};

REAL d_surf::getStepY() const {
	return grd->stepY;
};

void d_surf::getCoordNode(size_t i, size_t j, REAL & x, REAL & y) const {
	grd->getCoordNode(i,j,x,y);
};

REAL d_surf::getCoordNodeX(size_t i) const {
	return grd->getCoordNodeX(i);
};

REAL d_surf::getCoordNodeY(size_t j) const {
	return grd->getCoordNodeY(j);
};

size_t d_surf::get_i(REAL x) const {
	return grd->get_i(x);
};

size_t d_surf::get_j(REAL y) const {
	return grd->get_j(y);
};

REAL d_surf::mean() const {
	return mean_value(coeff->begin(), coeff->end(), undef_value);
};

REAL d_surf::wmean(const d_surf * wsrf) const {
	
	REAL res = REAL(0);

	size_t aux_X_from, aux_X_to;
	size_t aux_Y_from, aux_Y_to;
	
	_grid_intersect1(grd, wsrf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_grid * aux_grid = _create_sub_grid(grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	
	d_surf * w_srf = _surf_project(wsrf, aux_grid);

	size_t nn = aux_grid->getCountX();
	size_t mm = aux_grid->getCountY();

	size_t NN = getCountX();
	size_t MM = getCountY();

	REAL denom = 0;
	REAL sum = 0;

	size_t i, j, pos;
	for (i = 0; i < NN; i++) {
		for (j = 0; j < MM; j++) {
			
			two2one(pos, i, j, NN, MM);

			REAL value = (*coeff)(pos);
			if (value == this->undef_value)
				continue;

			REAL weight = 0;
			if ((i >= aux_X_from) && (i <= aux_X_to) && (j >= aux_Y_from) && (j <= aux_Y_to)) {
				size_t I = i-aux_X_from;
				size_t J = j-aux_Y_from;
				weight = (*(w_srf->coeff))(I + J*nn);
				if (weight == w_srf->undef_value)
					weight = 0;
			}
			
			if (weight <= 0)
				continue;

			denom += weight;
			sum += weight*value;

		}
	}

	if (aux_grid)
		aux_grid->release();
	
	delete w_srf;
	
	return sum/denom;
};

REAL d_surf::std(REAL mean) const {
	return std_value(mean, coeff->begin(), coeff->end(), undef_value);
};

REAL d_surf::sum() const {
	return sum_value(coeff->begin(), coeff->end(), undef_value);
};

bool d_surf::compare_grid(const d_surf * srf) const {
	return ( 
		(grd->operator ==(srf->grd)) &&
		(coeff->size() == srf->coeff->size())
	       );
};

void d_surf::plus(const d_surf * srf) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) += val1;
	}
};

void d_surf::plus_mask(const d_surf * srf, const bitvec * mask) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) += val1;
	}
};

void d_surf::minus(const d_surf * srf) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) -= val1;
	}
};

void d_surf::minus_mask(const d_surf * srf, const bitvec * mask) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) -= val1;
	}
};

void d_surf::mult(const d_surf * srf) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) *= val1;
	}
};

void d_surf::mult_mask(const d_surf * srf, const bitvec * mask) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) *= val1;
	}
};

void d_surf::div(const d_surf * srf) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) /= val1;
		if (val1 == 0) {
			(*coeff)(i) = 0;
		}
	}
};

void d_surf::div_mask(const d_surf * srf, const bitvec * mask) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) /= val1;
		if (val1 == 0) {
			(*coeff)(i) = 0;
		}
	}
};

void d_surf::set(const d_surf * srf) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) = val1;
	}
};

void d_surf::set_mask(const d_surf * srf, const bitvec * mask) {
	size_t i;
	REAL val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val1 = (*srf->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != srf->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) = val1;
	}
};

void d_surf::plus(REAL val) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) += val;
	}
};

void d_surf::plus_mask(REAL val, const bitvec * mask) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) += val;
	}
};

void d_surf::minus(REAL val) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) -= val;
	}
};

void d_surf::minus_mask(REAL val, const bitvec * mask) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) -= val;
	}
};

void d_surf::mult(REAL val) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) *= val;
	}
};

void d_surf::mult_mask(REAL val, const bitvec * mask) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) *= val;
	}
};

void d_surf::div(REAL val) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) /= val;
	}
};

void d_surf::div_mask(REAL val, const bitvec * mask) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) /= val;
	}
};

void d_surf::set(REAL val) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) = val;
	}
};

void d_surf::set_mask(REAL val, const bitvec * mask) {
	size_t i;
	REAL val2;
	for (i = 0; i < coeff->size(); i++) {
		if (mask->get(i) == false)
			continue;
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

size_t d_surf::details_size() const {
	return 1+MIN(details_h->size(),MIN(details_v->size(),details_d->size()));
};

bool d_surf::decompose() {

	writelog(LOG_MESSAGE,"surf : make decomposition");
	bool enlarge_X = false;
	bool enlarge_Y = false;

	size_t countX = grd->getCountX();
	size_t countY = grd->getCountY();

	if (countX % 2 != 0)
		enlarge_X = true;

	if (countY % 2 != 0)
		enlarge_Y = true;
	
	size_t N = coeff->size()/4;

	if (N <= 1)
		return false;

	vec * xa = NULL; // new approx vector
	vec * xd = NULL; // diagonal details
	vec * xh = NULL; // horizontal details
	vec * xv = NULL; // vertical details

	_decomp2d(coeff, 
		  xa,
		  xd,
		  xh,
		  xv,
		  grd->getCountX(), grd->getCountY(),
		  enlarge_X,
		  enlarge_Y,
		  undef_value,
		  (details_d->size() % 2 == 1));

	details_d->push_back(xd);
	details_h->push_back(xh);
	details_v->push_back(xv);
	enlarges_X->push_back(enlarge_X);
	enlarges_Y->push_back(enlarge_Y);

	if (coeff)
		coeff->release();
	coeff = xa;

	size_t new_size_x = 0;
	if (enlarge_X) {
		new_size_x = (grd->getCountX() + 1) / 2;
	} else {
		new_size_x = (grd->getCountX()) / 2;
	}
	grd->startX += grd->stepX/REAL(2);
	grd->stepX  *= REAL(2);
	grd->endX    = grd->startX + (new_size_x-1) * grd->stepX;
	new_size_x = grd->getCountX();
	
	
	size_t new_size_y = 0;
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

bool d_surf::auto_decompose(REAL eps, int norm) {

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

REAL d_surf::calc_approx_norm(int norm_type) const {

	REAL res = REAL(0);

	switch(norm_type) {
	case 0:
		{
			size_t i;
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

bool d_surf::reconstruct() {
	
	size_t N = details_d->size();

	if (N == 0)
		return false;

	vec * approx = NULL;

	std::vector<vec*>::iterator d_it = details_d->end()-1;
	std::vector<vec*>::iterator h_it = details_h->end()-1;
	std::vector<vec*>::iterator v_it = details_v->end()-1;
	std::vector<bool>::iterator b_itX = enlarges_X->end()-1;
	std::vector<bool>::iterator b_itY = enlarges_Y->end()-1;

	_recons2d(approx,
		  coeff,
		  (*d_it),
		  (*h_it),
		  (*v_it),
		  grd->getCountX(), grd->getCountY(),
		  *b_itX,
		  *b_itY,
		  undef_value,
		  ((details_d->size() + 1) % 2 == 1));
							   
	if (coeff)
		coeff->release();
	if (*d_it)
		(*d_it)->release(); 
	details_d->erase(d_it);
	if (*h_it)
		(*h_it)->release();
	details_h->erase(h_it);
	if (*v_it)
		(*v_it)->release();
	details_v->erase(v_it);
	
	coeff = approx;

	// X
	size_t new_count_x = grd->getCountX()*2;
	grd->stepX  /= REAL(2);
	grd->startX -= grd->stepX/REAL(2);
	grd->endX    = grd->startX + grd->stepX*(new_count_x-1);
	if (*b_itX)
		grd->endX -= grd->stepX;

	size_t new_count_y = grd->getCountY()*2;
	grd->stepY  /= REAL(2);
	grd->startY -= grd->stepY/REAL(2);
	grd->endY    = grd->startY + grd->stepY*(new_count_y-1);
	if (*b_itY)
		grd->endY -= grd->stepY;

	enlarges_X->erase(b_itX);
	enlarges_Y->erase(b_itY);

	size_t check_x = getCountX();
	size_t check_y = getCountY();
	
	return true;
};

bool d_surf::full_reconstruct() {

	writelog(LOG_MESSAGE,"surf : make reconstruction");
	
	size_t N = details_d->size();
	bool res = true;

	while ( (N > 0) && res ) {
		res = reconstruct() && res;
		N = details_d->size();
	}

	return res;

};

bool d_surf::add_noise(REAL std) {
	size_t size = coeff->size();
	size_t i;
	for (i = 0; i < size; i++) {
		(*coeff)(i) += norm_rand(std);
	}
	return true;
};

size_t d_surf::defined() const {
	size_t defined = 0;
	size_t i;
	if (coeff) {
		const REAL * ptr = coeff->begin();
		for (i = 0; i < coeff->size(); i++) {
			if ( *(ptr+i) != undef_value )
				defined++;
		}
	};
	return defined;
};

void d_surf::set_undef_value(REAL new_undef_value) {
	size_t i;
	REAL old_undef = this->undef_value;
	for (i = 0; i < coeff->size(); i++) {
		REAL value = (*coeff)(i);
		if (value == old_undef)
			(*coeff)(i) = new_undef_value;
	}
	this->undef_value = new_undef_value;
};

std::vector<d_surf *> * surfit_surfs = NULL;

/*! \struct surf_garbage
    \brief struct for deletion of \ref surf pointers
*/
struct surf_garbage : public binman {
	//! inits \ref surfit_surf and \ref surfit_surfs
	surf_garbage() {
		surfit_surfs = new std::vector<d_surf *>;
	};
	//! removes \ref surfit_surf and \ref surfit_surfs
	~surf_garbage() {
		if (surfit_surfs) {
			release_elements(surfit_surfs->begin(), surfit_surfs->end());
			delete surfit_surfs;
			surfit_surfs = NULL;
		}
	};
};

surf_garbage surf_garb;



}; // namespace surfit;

