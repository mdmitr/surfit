
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

#include "defarea.h"
#include "task.h"
#include "datafile.h"
#include "grid.h"
#include "boolvec.h"

namespace surfit {

defarea::defarea(boolvec *icoeff, grid *igrd, const char * newname) {
	grd = igrd;
	coeff = icoeff;
	setName(newname);
	show_smooth = true;
};

defarea::~defarea() {
	delete grd;
	delete coeff;
};

bool defarea::bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const {
	minx = grd->getCoordNodeX(0) - grd->stepX/REAL(2);
	maxx = grd->getCoordNodeX(grd->getCountX()-1) + grd->stepX/REAL(2);
	miny = grd->getCoordNodeY(0) - grd->stepY/REAL(2);
	maxy = grd->getCoordNodeY(grd->getCountY()-1) + grd->stepY/REAL(2);
	return true;
};

bool defarea::getValue(REAL x, REAL y) const {
	
    REAL start_x, start_y;
	getCoordNode(0,0,start_x,start_y);
	
	x = x - start_x + grd->stepX/REAL(2);
	int i = (int)floor(x / grd->stepX);
	if ((i >= grd->getCountX()) || (i < 0))
		return false;

	y = y - start_y + grd->stepY/REAL(2);
	int j = (int)floor(y / grd->stepY);
	if ((j >= grd->getCountY()) || (j < 0))
		return false;

    return (*coeff)( i + grd->getCountX()*j );
};

REAL defarea::getMinX() const {
	return grd->startX - grd->stepX/REAL(2);
};

REAL defarea::getMaxX() const {
	return grd->endX + grd->stepX/REAL(2);
};

REAL defarea::getMinY() const {
	return grd->startY - grd->stepY/REAL(2);
};

REAL defarea::getMaxY() const {
	return grd->endY + grd->stepY/REAL(2);
};

int defarea::getQuadsCount() const {
	return grd->getCountX()*grd->getCountY();
};

bool defarea::getQuad(int q_number, 
		      float &x0, float &y0,
		      float &x1, float &y1,
		      float &x2, float &y2,
		      float &x3, float &y3) const {

	REAL X, Y;
	REAL X0, Y0;
	REAL X1, Y1;
	REAL X2, Y2;
	REAL X3, Y3;

	bool value = (*coeff)(q_number);
	if (!value)
		return false;
	
	int i,j;
	int NN = grd->getCountX();
	
	
	j = q_number / grd->getCountX();
	i = q_number - j*grd->getCountX();
	
	grd->getCoordNode(i,j,X,Y);

	X0 = X - grd->stepX/REAL(2);
	Y0 = Y - grd->stepY/REAL(2);

	X1 = X + grd->stepX/REAL(2);
	Y1 = Y - grd->stepY/REAL(2);

	X2 = X + grd->stepX/REAL(2);
	Y2 = Y + grd->stepY/REAL(2);

	X3 = X - grd->stepX/REAL(2);
	Y3 = Y + grd->stepY/REAL(2);		
	
	x0 = float(X0);
	x1 = float(X1);
	x2 = float(X2);
	x3 = float(X3);
	
	y0 = float(Y0);
	y1 = float(Y1);
	y2 = float(Y2);
	y3 = float(Y3);
	
	return true;
};

bool defarea::writeTags(datafile *df) const {
		
	bool res = true;
	bool op;
	
	op = df->writeTag("defarea"); res = (res && op);

	if (getName()) {
		op = df->writeString("name", getName()); res = (res && op);
	}
	
	op = grd->writeTags(df); res = (res && op);
	op = df->writeBoolArray("coeff", coeff->begin(), coeff->size()); res = (res && op);
	op = df->writeEndTag();	res = (res && op);

	return res;
	
};

int defarea::getCountX() const {
	return grd->getCountX();
};

int defarea::getCountY() const {
	return grd->getCountY();
};

bool defarea::compare_grid(const defarea * defarea) const {
	return ( 
		(grd->operator ==(defarea->grd)) &&
		(coeff->size() == defarea->coeff->size())
	       );
};

void defarea::getCoordNode(int i, int j, REAL & x, REAL & y) const {
	grd->getCoordNode(i,j,x,y);
};

REAL defarea::getCoordNodeX(int i) const {
	return grd->getCoordNodeX(i);
};

REAL defarea::getCoordNodeY(int j) const {
	return grd->getCoordNodeY(j);
};

int defarea::get_i(REAL x) const {
	return grd->get_i(x);
};

int defarea::get_j(REAL y) const {
	return grd->get_j(y);
};

void defarea::OR(const defarea * def) {
	int i;
	for (i = 0; i < coeff->size(); i++) {
		(*coeff)(i) = (*coeff)(i) || (*def->coeff)(i);
	}
};

void defarea::XOR(const defarea * def) {
	int i;
	for (i = 0; i < coeff->size(); i++) {
		(*coeff)(i) = (*coeff)(i) ^ (*def->coeff)(i);
	}
};

void defarea::AND(const defarea * def) {
	int i;
	for (i = 0; i < coeff->size(); i++) {
		(*coeff)(i) = (*coeff)(i) && (*def->coeff)(i);
	}
};

void defarea::NOT(const defarea * def) {
	int i;
	for (i = 0; i < coeff->size(); i++) {
		(*coeff)(i) = !(*def->coeff)(i);
	}
};

bool defarea::getMinMaxZ(REAL & minz, REAL & maxz) const {
	return false;
};

}; // namespace surfit;

