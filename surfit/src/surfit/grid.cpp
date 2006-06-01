
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

/*! \file grid.cpp
	implementation of the grid class
*/

#include "surfit_ie.h"
#include <math.h>
#include <string.h>
#include "grid.h"
#include "datafile.h"
#include "fileio.h"

namespace surfit {

d_grid * create_grid(REAL startX, REAL endX, REAL stepX,
		     REAL startY, REAL endY, REAL stepY,
		     const char * iname)
{
	return new d_grid(startX, endX, stepX,
			  startY, endY, stepY,
			  iname);
};

d_grid * create_grid(const d_grid * igrid, const char * iname)
{
	return new d_grid(igrid, iname);
};

d_grid::d_grid(REAL istartX, REAL iendX, REAL istepX,
	       REAL istartY, REAL iendY, REAL istepY,
	       const char * iname) {

	startX = istartX;
	endX = iendX;
	stepX = istepX;
	startY = istartY;
	endY = iendY;
	stepY = istepY;
	gridname = NULL;
	setName(iname);

	if ((startX > endX) || (startY > endY))
		writelog(LOG_ERROR,"Wrong grid");
};

d_grid::d_grid(const d_grid * igrid, const char * iname) {
	startX = igrid->startX;
	endX   = igrid->endX;
	stepX  = igrid->stepX;
	startY = igrid->startY;
	endY   = igrid->endY;
	stepY  = igrid->stepY;
	gridname = NULL;
	if (iname)
		setName(iname);
	else
		setName(igrid->getName());
};

d_grid::~d_grid() {
    free(gridname);
}

void d_grid::release() {
	delete this;
};

size_t d_grid::getCountX() const {
	if (stepX == 0) return 0;
	return (size_t)floor((endX-startX)/stepX + 0.5) + 1;
};

bool d_grid::setCountX(size_t countX) {
	if (endX == startX)
		return false;
	stepX = (endX-startX)/REAL(countX-1);
	return true;
};

size_t d_grid::getCountY() const {
	if (stepY == 0) return 0;
	return (size_t)floor((endY-startY)/stepY + 0.5) + 1;
};

bool d_grid::setCountY(size_t countY) {
	if (endY == startY)
		return false;
	stepY = (endY-startY)/REAL(countY-1);
	return true;
};

void d_grid::getCoordNode(size_t i, size_t j, REAL &x, REAL &y) const {
	x = startX + (i)*stepX;
	y = startY + (j)*stepY;
};

void d_grid::getCoordPoint(REAL x, REAL y, size_t & i, size_t & j) const {
	i = get_i(x);
	j = get_j(y);
};

bool d_grid::writeTags(datafile *df) const {
    bool res = true; bool op = false;
	op = df->writeTag("grid");		         res = (op&&res);
    if (getName()) 
		op = df->writeString("name",getName());  res = (op && res);
	op = df->writeReal("startX",startX);	     res = (op&&res);
	op = df->writeReal("endX",    endX);	     res = (op&&res);
	op = df->writeReal("stepX",  stepX);	     res = (op&&res);
	op = df->writeReal("startY",startY);	     res = (op&&res);
	op = df->writeReal("endY",    endY);	     res = (op&&res);
	op = df->writeReal("stepY",  stepY);	     res = (op&&res);
	op = df->writeEndTag();				         res = (op&&res);
	return res;
};


const char * d_grid::getName() const {
	return gridname;
};

void d_grid::setName(const char * newname) {
	if (!newname)
		return;
	if (gridname) {
		free(gridname);
		gridname = NULL;
	}

	gridname = (char *)malloc(strlen(newname) + 1);
	strcpy(gridname, newname);
};

size_t d_grid::getLinesCount() const {
    return getCountX()+getCountY();
};

void d_grid::getLine(size_t line_number, float &x0, float &y0, float &x1, float &y1) const {

    REAL X0, Y0, X1, Y1;

    if ( (line_number >= 0) && (line_number < getCountX()) ) {
        getCoordNode(line_number,0,X0,Y0);
        getCoordNode(line_number,getCountY()-1,X1,Y1);
        x0 = float(X0);
        x1 = float(X1);
        y0 = float(Y0);
        y1 = float(Y1);
        return;
    }

    line_number -= getCountX();

    if ( (line_number >= 0) && (line_number < getCountY()) ) {
        getCoordNode(0,line_number,X0,Y0);
        getCoordNode(getCountX()-1,line_number,X1,Y1);
        x0 = float(X0);
        x1 = float(X1);
        y0 = float(Y0);
        y1 = float(Y1);
        return;
    }

};

bool d_grid::operator==(const d_grid * test) const 
{
	REAL eps = REAL(1e-6);
	if (test == this)
		return true;

	return (
			( fabs(test->startX - startX) < eps ) &&
			( fabs(test->endX   -   endX) < eps ) &&
			( fabs(test->stepX  -  stepX) < eps ) &&
			( fabs(test->startY - startY) < eps ) &&
			( fabs(test->endY   -   endY) < eps ) &&
			( fabs(test->stepY  -  stepY) < eps)
	       );
};

void d_grid::x_from_to(size_t i, REAL & from, REAL & to) const {
	from = startX + (i - REAL(0.5))*stepX;
	to   = startX + (i + REAL(0.5))*stepX;
};

REAL d_grid::x_from(size_t i) const {
	return startX + (i - REAL(0.5))*stepX;
};

REAL d_grid::x_to(size_t i) const {
	return startX + (i + REAL(0.5))*stepX;
};

void d_grid::y_from_to(size_t i, REAL & from, REAL & to) const {
	from = startY + (i - REAL(0.5))*stepY;
	to   = startY + (i + REAL(0.5))*stepY;
};

REAL d_grid::y_from(size_t i) const {
	return startY + (i - REAL(0.5))*stepY;
};

REAL d_grid::y_to(size_t i) const {
	return startY + (i + REAL(0.5))*stepY;
};

}; // namespace surfit;

