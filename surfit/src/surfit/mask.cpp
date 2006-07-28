
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

#include "mask.h"
#include "datafile.h"
#include "grid.h"
#include "bitvec.h"
#include "free_elements.h"

namespace surfit {

d_mask * create_mask(bitvec *icoeff, d_grid *igrd, const char * funcname) {
	return new d_mask(icoeff, igrd, funcname);
};

d_mask::d_mask(bitvec *icoeff, d_grid *igrd, const char * newname) : data("mask") {
	grd = igrd;
	coeff = icoeff;
	setName(newname);
	show_smooth = true;
};

d_mask::~d_mask() {
	if (grd)
		grd->release();
	if (coeff)
		coeff->release();
};

bool d_mask::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	minx = grd->getCoordNodeX(0) - grd->stepX/REAL(2);
	maxx = grd->getCoordNodeX(grd->getCountX()-1) + grd->stepX/REAL(2);
	miny = grd->getCoordNodeY(0) - grd->stepY/REAL(2);
	maxy = grd->getCoordNodeY(grd->getCountY()-1) + grd->stepY/REAL(2);
	return true;
};

bool d_mask::getValue(REAL x, REAL y) const {
	
	REAL start_x, start_y;
	getCoordNode(0,0,start_x,start_y);
	
	x = x - start_x + grd->stepX/REAL(2);
	size_t i = (size_t)MAX(0,floor(x / grd->stepX));
	if ((i >= grd->getCountX()) || (i < 0))
		return false;

	y = y - start_y + grd->stepY/REAL(2);
	size_t j = (size_t)MAX(0,floor(y / grd->stepY));
	if ((j >= grd->getCountY()) || (j < 0))
		return false;

	return getValueIJ(i, j);
};

bool d_mask::getValueIJ(size_t i, size_t j) const {
	size_t NN = grd->getCountX();
	return coeff->get(i + j*NN);
};

REAL d_mask::getMinX() const {
	return grd->startX - grd->stepX/REAL(2);
};

REAL d_mask::getMaxX() const {
	return grd->endX + grd->stepX/REAL(2);
};

REAL d_mask::getMinY() const {
	return grd->startY - grd->stepY/REAL(2);
};

REAL d_mask::getMaxY() const {
	return grd->endY + grd->stepY/REAL(2);
};

REAL d_mask::getStepX() const {
	return grd->stepX;
};

REAL d_mask::getStepY() const {
	return grd->stepY;
};

bool d_mask::writeTags(datafile *df) const {
		
	bool res = true;
	bool op;
	
	op = df->writeTag("mask"); res = (res && op);

	if (getName()) {
		op = df->writeString("name", getName()); res = (res && op);
	}
	
	op = grd->writeTags(df); res = (res && op);
	op = df->writeBitArray("coeff", coeff); res = (res && op);
	op = df->writeEndTag();	res = (res && op);

	return res;
	
};

size_t d_mask::getCountX() const {
	return grd->getCountX();
};

size_t d_mask::getCountY() const {
	return grd->getCountY();
};

bool d_mask::compare_grid(const d_mask * mask) const {
	return ( 
		(grd->operator ==(mask->grd)) &&
		(coeff->size() == mask->coeff->size())
	       );
};

void d_mask::getCoordNode(size_t i, size_t j, REAL & x, REAL & y) const {
	grd->getCoordNode(i,j,x,y);
};

REAL d_mask::getCoordNodeX(size_t i) const {
	return grd->getCoordNodeX(i);
};

REAL d_mask::getCoordNodeY(size_t j) const {
	return grd->getCoordNodeY(j);
};

size_t d_mask::get_i(REAL x) const {
	return grd->get_i(x);
};

size_t d_mask::get_j(REAL y) const {
	return grd->get_j(y);
};

void d_mask::OR(const d_mask * msk) {
	size_t i;
	for (i = 0; i < coeff->size(); i++) {
		bool b1 = coeff->get(i);
		bool b2 = msk->coeff->get(i);
		bool res = b1 || b2;
		if (res)
			coeff->set_true(i);
		else
			coeff->set_false(i);
	}
};

void d_mask::XOR(const d_mask * msk) {
	size_t i;
	for (i = 0; i < coeff->size(); i++) {
		bool b1 = coeff->get(i);
		bool b2 = msk->coeff->get(i);
		bool res = b1 ^ b2;
		if (res)
			coeff->set_true(i);
		else
			coeff->set_false(i);
	}
};

void d_mask::AND(const d_mask * msk) {
	size_t i;
	for (i = 0; i < coeff->size(); i++) {
		bool b1 = coeff->get(i);
		bool b2 = msk->coeff->get(i);
		bool res = b1 && b2;
		if (res)
			coeff->set_true(i);
		else
			coeff->set_false(i);
	}
};

void d_mask::NOT(const d_mask * msk) {
	size_t i;
	for (i = 0; i < coeff->size(); i++) {
		bool b2 = msk->coeff->get(i);
		bool res = !b2;
		if (res)
			coeff->set_true(i);
		else
			coeff->set_false(i);
	}
};

bool d_mask::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

bitvec * d_mask::get_bitvec_mask(const d_grid * grid) const {
	size_t NN = grid->getCountX();
	size_t MM = grid->getCountY();

	bitvec * res = create_bitvec( NN*MM );
	res->init_false();

	size_t i,j;
	REAL x,y;

	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			grid->getCoordNode(i, j, x, y);
			if ( getValue(x,y) == true )
				res->set_true( i + j*NN );
		}
	}

	return res;
};




std::vector<d_mask *>  * surfit_masks  = NULL;

/*! \struct mask_garbage
    \brief struct for deletion of \ref mask pointers
*/
struct mask_garbage : public binman {
	//! inits \ref surfit_mask and \ref surfit_masks
	mask_garbage() {
		surfit_masks  = new std::vector<d_mask *>;
	};
	//! removes \ref surfit_mask and \ref surfit_masks
	~mask_garbage() {
		if (surfit_masks) {
			release_elements(surfit_masks->begin(), surfit_masks->end());
			delete surfit_masks;
			surfit_masks = NULL;
		}
	};
};

mask_garbage mask_garb;


}; // namespace surfit;

