
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

/*! \file grid.cpp
	implementation of the grid class
*/

#include "ie.h"
#include <math.h>
#include <string.h>
#include "grid.h"
#include "datafile.h"

namespace surfit {

grid::grid(REAL istartX, REAL iendX, REAL istepX,
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
};

grid::grid(const grid * igrid) {
	startX = igrid->startX;
	endX   = igrid->endX;
	stepX  = igrid->stepX;
	startY = igrid->startY;
	endY   = igrid->endY;
	stepY  = igrid->stepY;
	gridname = NULL;
	setName(igrid->getName());
};

grid::~grid() {
    free(gridname);
}

int grid::getCountX() const {
	if (stepX == 0) return 0;
	return (int)floor((endX-startX)/stepX + 0.5) + 1;
};

int grid::getCountY() const {
	if (stepY == 0) return 0;
	return (int)floor((endY-startY)/stepY + 0.5) + 1;
};

void grid::getCoordNode(int i, int j, REAL &x, REAL &y) const {
	x = startX + (i)*stepX;
    y = startY + (j)*stepY;
};

void grid::getCoordPoint(REAL x, REAL y, int & i, int & j) const {
	i = get_i(x);
	j = get_j(y);
};

bool grid::writeTags(datafile *df) const {
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


const char * grid::getName() const {
	return gridname;
};

void grid::setName(const char * newname) {
	if (!newname)
		return;
	if (gridname) {
		free(gridname);
		gridname = NULL;
	}

	gridname = (char *)malloc(strlen(newname) + 1);
	strcpy(gridname, newname);
};

int grid::getLinesCount() const {
    return getCountX()+getCountY();
};

void grid::getLine(int line_number, float &x0, float &y0, float &x1, float &y1) const {

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

bool grid::operator==(const grid * test) const 
{
	if (test == this)
		return true;

	return (
			(test->startX == startX) &&
			(test->endX   ==   endX) &&
			(test->stepX  ==  stepX) &&
			(test->startY == startY) &&
			(test->endY   ==   endY) &&
			(test->stepY  ==  stepY)
	       );
};

}; // namespace surfit;

