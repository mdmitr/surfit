
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

#include "globe_ie.h"
#include "dem.h"
#include "shortvec.h"
#include "grid.h"
#include "datafile.h"
#include "vec_alg.h"
#include "free_elements.h"
#include "shortmrf.h"
#include "bitvec.h"

#include <float.h>

namespace surfit {

d_dem * create_dem(shortvec *icoeff, d_grid *igrd, 
		   const char * demname, short dem_undef_value)
{
	return new d_dem(icoeff, igrd, demname, dem_undef_value);
};

d_dem::d_dem(shortvec * icoeff, d_grid * igrd, const char * idemname, short idem_undef_value) 
: data("dem")
{
	grd = igrd;
	coeff = icoeff;
	undef_value = idem_undef_value;
	setName(idemname);

	coeffs_store = new std::vector<shortvec*>;
	grids_store = new std::vector<d_grid*>;
	store_pos = 0;

};

d_dem::~d_dem() {
	if (grids_store->size() == 0) {
		if (grd)
			grd->release();
	}

	if (coeff) {
		if (coeffs_store->size() == 0)
			coeff->release();
	}

	std::vector<shortvec*>::iterator it;
	for (it = coeffs_store->begin(); it != coeffs_store->end(); it++) {
		if (*it)
			(*it)->release();
	}
	delete coeffs_store;

	std::vector<d_grid *>::iterator git;
	for (git = grids_store->begin(); git != grids_store->end(); git++) {
		if (*git)
			(*git)->release();
	}
	delete grids_store;
};

short d_dem::getValue(REAL x, REAL y) const {
	
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

REAL d_dem::getInterpValue(REAL x, REAL y) const {
	
	REAL value = 0;
	size_t I0, J0, I1, J1;
	size_t func_sizeX = getCountX();
	size_t func_sizeY = getCountY();
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
	
	I0 = MIN(MAX( 0, I0 ), func_sizeX-1);
	I1 = MIN(MAX( 0, I1 ), func_sizeX-1);
	J0 = MIN(MAX( 0, J0 ), func_sizeY-1);
	J1 = MIN(MAX( 0, J1 ), func_sizeY-1);
	
	getCoordNode(I0, J0, x0, y0);
	
	z0 = (*(coeff))(I0 + func_sizeX*J0);
	z1 = (*(coeff))(I1 + func_sizeX*J0);
	z2 = (*(coeff))(I1 + func_sizeX*J1);
	z3 = (*(coeff))(I0 + func_sizeX*J1);
	
	if (
		(z0 == this->undef_value) ||
		(z1 == this->undef_value) ||
		(z2 == this->undef_value) ||
		(z3 == this->undef_value) 
		) 
	{
		
		REAL sum = REAL(0);
		int cnt = 0;
		
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

REAL d_dem::getMeanValue(REAL x_from, REAL x_to, REAL y_from, REAL y_to) const {
	int i_from, i_to;
	int j_from, j_to;

	
	i_from = get_i(x_from);
	i_from = MAX(0, i_from);
	
	i_to   = get_i(x_to);
	i_to   = MIN(i_to, getCountX()-1);
	
	j_from = get_j(y_from);
	j_from = MAX(0, j_from);
	
	j_to   = get_j(y_to);
	j_to   = MIN(j_to, getCountY()-1);

	int NN = getCountX();

	int i,j;
	int cnt = 0;
	REAL sum_value = 0;
	REAL value;
	for (j = j_from; j <= j_to; j++) {
		for (i = i_from; i <= i_to; i++) {
		
			int pos = i + j*NN;
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

REAL d_dem::getMinX() const {
	return grd->startX - grd->stepX/REAL(2);
};

REAL d_dem::getMaxX() const {
	return grd->endX + grd->stepX/REAL(2);
};

REAL d_dem::getMinY() const {
	return grd->startY - grd->stepY/REAL(2);
};

REAL d_dem::getMaxY() const {
	return grd->endY + grd->stepY/REAL(2);
};

bool d_dem::writeTags(datafile *df) const {
		
	bool res = true;
	bool op;
	
	op = df->writeTag("dem");		res = (res && op);

	if (getName()) {
		op = df->writeString("name", getName()); res = (res && op);
	}
	
	op = grd->writeTags(df);			res = (res && op);
	op = df->writeShortArray("coeff", coeff); res = (res && op);
	op = df->writeShort("undef_value", undef_value); res = (res && op);
	op = df->writeEndTag();					res = (res && op);

	return res;
	
};

int d_dem::getCountX() const {
	return grd->getCountX();
};

int d_dem::getCountY() const {
	return grd->getCountY();
};

REAL d_dem::getStepX() const {
	return grd->stepX;
};

REAL d_dem::getStepY() const {
	return grd->stepY;
};

void d_dem::getCoordNode(int i, int j, REAL & x, REAL & y) const {
	grd->getCoordNode(i,j,x,y);
};

REAL d_dem::getCoordNodeX(int i) const {
	return grd->getCoordNodeX(i);
};

REAL d_dem::getCoordNodeY(int j) const {
	return grd->getCoordNodeY(j);
};

int d_dem::get_i(REAL x) const {
	return grd->get_i(x);
};

int d_dem::get_j(REAL y) const {
	return grd->get_j(y);
};

void d_dem::plus(const d_dem * fnc) {
	size_t i;
	short val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) += val1;
	}
};

void d_dem::minus(const d_dem * fnc) {
	size_t i;
	short val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) -= val1;
	}
};

void d_dem::mult(const d_dem * fnc) {
	size_t i;
	short val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) *= val1;
	}
};

void d_dem::div(const d_dem * fnc) {
	size_t i;
	short val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) /= val1;
	}
};

void d_dem::set(const d_dem * fnc) {
	size_t i;
	short val1, val2;
	for (i = 0; i < coeff->size(); i++) {
		val1 = (*fnc->coeff)(i);
		val2 = (*coeff)(i);
		if ((val1 != fnc->undef_value) && (val2 != this->undef_value))
			(*coeff)(i) = val1;
	}
};

void d_dem::plus(short val) {
	size_t i;
	short val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) += val;
	}
};

void d_dem::minus(short val) {
	size_t i;
	short val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) -= val;
	}
};

void d_dem::mult(short val) {
	size_t i;
	short val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) *= val;
	}
};

void d_dem::div(short val) {
	size_t i;
	short val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) /= val;
	}
};

void d_dem::set(short val) {
	size_t i;
	short val2;
	for (i = 0; i < coeff->size(); i++) {
		val2 = (*coeff)(i);
		if (val2 != this->undef_value)
			(*coeff)(i) = val;
	}
};

int d_dem::defined() const {
	int defined = 0;
	size_t i;
	if (coeff) {
		const short * ptr = coeff->begin();
		for (i = 0; i < coeff->size(); i++) {
			if ( *(ptr+i) != undef_value )
				defined++;
		}
	};
	return defined;
};

bool d_dem::getMinMaxZ(REAL & minZ, REAL & maxZ) const {

	minZ = FLT_MAX;
	maxZ = -FLT_MAX;

	short minz = SHRT_MAX;
	short maxz = -SHRT_MAX;

	minmax_value(coeff->begin(), coeff->end(), minz, maxz, undef_value);

	minZ = MIN(minZ, minz);
	maxZ = MAX(maxZ, maxz);

	return true;
};

bool d_dem::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	minx = grd->getCoordNodeX(0) - grd->stepX/REAL(2);
	maxx = grd->getCoordNodeX(grd->getCountX()-1) + grd->stepX/REAL(2);
	miny = grd->getCoordNodeY(0) - grd->stepY/REAL(2);
	maxy = grd->getCoordNodeY(grd->getCountY()-1) + grd->stepY/REAL(2);
	return true;
};

bool d_dem::compare_grid(const d_dem * fnc) const {
	return ( 
		(grd->operator ==(fnc->grd)) &&
		(coeff->size() == fnc->coeff->size())
	       );
};

//
//
// wavelets section
//
//

int d_dem::details_size() const {
	return store_pos;
};

bool d_dem::decompose() {

	if (coeffs_store->size() == 0) {
		coeffs_store->push_back(coeff);
		grids_store->push_back( new d_grid(*grd) );
		store_pos++;
	}

	if (store_pos == coeffs_store->size()) {
		
		writelog(LOG_MESSAGE,"dem : make decomposition");
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
		
		shortvec * new_coeff = _decomp2d(coeff, 
			grd->getCountX(), grd->getCountY(),
			undef_value, 
			(store_pos % 2 == 1));
		
		coeff = new_coeff;
		
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
		
		coeffs_store->push_back(coeff);
		grids_store->push_back( new d_grid(*grd) );
		store_pos++;
				
	} else {

		store_pos++;
		coeff = (*coeffs_store)[store_pos];
		grd = (*grids_store)[store_pos];
		
	}
	return true;

};

bool d_dem::auto_decompose(REAL eps, int norm) {

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

REAL d_dem::calc_approx_norm(int norm_type) const {

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

bool d_dem::reconstruct() {
	
	int N = store_pos;

	if (N == 0)
		return false;

	store_pos--;

	coeff = (*coeffs_store)[store_pos];
	grd = (*grids_store)[store_pos];
	
	return true;

};

bool d_dem::full_reconstruct() {

	writelog(LOG_MESSAGE,"dem : make reconstruction");
	
	int N = store_pos;
	bool res = true;

	while ( (N > 0) && res ) {
		res = reconstruct() && res;
		N = store_pos;
	}

	return res;

};



std::vector<d_dem *>     * globe_dems     = NULL;

/*! \struct dem_garbage
    \brief struct for deletion of \ref dem pointers
*/
struct dem_garbage : public binman {
	//! inits \ref globe_dem and \ref globe_dems
	dem_garbage() {
		globe_dems = new std::vector<d_dem *>;
	};
	//! removes \ref globe_dem and \ref globe_dems
	~dem_garbage() {
		if (globe_dems) {
			release_elements(globe_dems->begin(), globe_dems->end());
			delete globe_dems;
			globe_dems = NULL;
		}
	};
};

dem_garbage dem_garb;

}; // namespace surfit;


