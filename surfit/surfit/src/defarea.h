
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

#ifndef __surfit__defarea__
#define __surfit__defarea__

#include "data.h"

namespace surfit {

class func;
class grid;
class defarea;
class boolvec;
class datafile;

/*! \class defarea
    \brief sets domain of the function (see \ref surfit_defarea). See \ref tcl_defarea "Tcl commands" for \ref defarea.
*/
class SURFIT_EXPORT defarea : public data {

public:

	/*! constructor 
	    \param igrd uniform 2d-grid
	    \param icoeff coefficients a_i
	    \param funcname name
	*/
	defarea(boolvec *icoeff, grid *igrd, const char * funcname = 0);

	//! destructor
	virtual ~defarea();

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;
	
	//! returns function value at point (x,y)
	virtual bool getValue(REAL x, REAL y) const; 
	
	//! returns minimum X for defined value
	virtual REAL getMinX() const;

	//! returns maximum X for defined value
	virtual REAL getMaxX() const;

	//! returns minimum Y for defined value
	virtual REAL getMinY() const;

	//! returns maximum Y for defined value
	virtual REAL getMaxY() const;

	//! returns amount of triangles to draw
	virtual int getQuadsCount() const;

	//! returns coord's for triangle with trianlge_number to draw
	virtual bool getQuad(int qe_number, 
			     float &x0, float &y0,
			     float &x1, float &y1,
			     float &x2, float &y2,
			     float &x3, float &y3) const;

	//! returns amount of X-nodes
	virtual int getCountX() const;

	//! returns amount of Y-nodes
	virtual int getCountY() const;

	//! calculates coordinate of i,j node
	virtual void getCoordNode(int i, int j, REAL & x, REAL & y) const;
	
	//! returns X-coordinate of the center of the (i,j) cell
	REAL getCoordNodeX(int i) const;

	//! returns Y-coordinate of the center of the (i,j) cell
	REAL getCoordNodeY(int j) const;
	
	//! returns i-cell number for X-coordinate
	virtual int get_i(REAL x) const;
	//! returns j-cell number for Y-coordinate
	virtual int get_j(REAL y) const;

	//! writes defarea to datafile
	virtual bool writeTags(datafile *df) const;

	//! compares defareas by thier grids
	virtual bool compare_grid(const defarea * defarea) const;
	//! and operation with another defarea
	virtual void AND(const defarea * def);
	//! not operation with another defarea
	virtual void NOT(const defarea * def);
	//! or operation with another defarea
	virtual void OR(const defarea * def);
	//! xor operation with another defarea
	virtual void XOR(const defarea * def);

	//! equidistant grid for defarea
	grid * grd;

	//! coefficients for each basis function
	boolvec * coeff;

	//! drawing flag
	bool show_smooth;

};

}; // namespace surfit

#endif



