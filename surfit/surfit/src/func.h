
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

#ifndef __surfit__func__
#define __surfit__func__

#include <vector>

#include "data.h"

namespace surfit {

class vec;
class datafile;
class grid;
class task;
class defarea;

/*! \class func
    \brief class for a function, based on the equidistant \ref grid with values set at the centers of the cells (see \ref surfit_func). See \ref tcl_func "Tcl commands" for \ref func.
*/
class SURFIT_EXPORT func : public data {

public:

	/*! constructor
	    \param igrd uniform 2d-grid
	    \param icoeff coefficients a_i
	    \param funcname name
	*/
	func(vec *icoeff, grid *igrd,
	     const char * funcname = 0);

	//! constructor
	func(defarea * def);

	//! destructor
	virtual ~func();
	
	//! calculates function value at point (x,y)
	virtual REAL getValue(REAL x, REAL y) const; 

	//! returns minimum X-coordinate for the function
	virtual REAL getMinX() const;

	//! returns maximum X-coordinate for the function
	virtual REAL getMaxX() const;

	//! returns minimum Y-coordinate for the function
	virtual REAL getMinY() const;

	//! returns maximum Y-coordinate for the function
	virtual REAL getMaxY() const;

	//! returns mean Z value for all nodes
	virtual REAL mean() const;

	//! returns standard deviation value from mean 'mean' value
	virtual REAL std(REAL mean) const;

	//! returns sum of all Z values for all nodes
	virtual REAL sum() const;

	//! calculates minimum and maximum Z values 
	virtual bool getMinMaxZ(REAL & minZ, REAL & maxZ) const;

	//! returns amount of triangles to draw function as surface
	virtual int getTrianglesCount() const;
	
	//! returns amount of triangles to draw function as surface in rect (show_x_from,show_x_to)X(show_y_from,show_y_to)
	virtual int getTrianglesCount(const REAL & show_x_from,
				      const REAL & show_x_to,
				      const REAL & show_y_from,
				      const REAL & show_y_to);

	//! calculates coordinates for triangle with number 'triangle_number'
	virtual void getTriangle(int triangle_number, 
	                         REAL &x0, REAL &y0, REAL &z0,
                     		 REAL &x1, REAL &y1, REAL &z1,
                      		 REAL &x2, REAL &y2, REAL &z2) const;
	
	//! calculates coordinates for triangle with number 'triangle_number' in rect (show_x_from,show_x_to)X(show_y_from,show_y_to)
	virtual void getTriangle(int triangle_number, 
                     		 REAL &x0, REAL &y0, REAL &z0,
                     		 REAL &x1, REAL &y1, REAL &z1,
                     		 REAL &x2, REAL &y2, REAL &z2,
				 const REAL & show_x_from,
                     		 const REAL & show_x_to,
				 const REAL & show_y_from,
				 const REAL & show_y_to) const;

	//! returns amount of cells for X direction
	virtual int getCountX() const;

	//! returns amount of cells for Y direction
	virtual int getCountY() const;

	//! returns distance between of centers of cells in X direction
	virtual REAL getStepX() const;

	//! returns distance between of centers of cells in Y direction
	virtual REAL getStepY() const;

	//! calculates coordinates of the center of the (i,j) cell
	virtual void getCoordNode(int i, int j, REAL & x, REAL & y) const;

	//! returns X-coordinate of the center of the (i,j) cell
	virtual REAL getCoordNodeX(int i) const;

	//! returns Y-coordinate of the center of the (i,j) cell
	virtual REAL getCoordNodeY(int j) const;

	//! returns i-cell number for X-coordinate
	virtual int get_i(REAL x) const;
	
	//! returns j-cell number for Y-coordinate
	virtual int get_j(REAL y) const;

	//! returns amount of cells with defined values
	virtual int defined() const;

	//! writes tag for saving func to datafile 
	virtual bool writeTags(datafile * df) const;

	//! compares two funcitons by their grids
	virtual bool compare_grid(const func * fnc) const;

	//! this = this + fnc
	virtual void plus(const func * fnc);
	
	//! this = this - fnc, undef means no operation
	virtual void minus(const func * fnc);

	//! this = this - fnc, undef means undef
	virtual void minus_undef(const func * fnc);
	
	//! this = this * fnc
	virtual void mult(const func * fnc);
	
	//! this = this / fnc
	virtual void div(const func * fnc);
	
	//! this = fnc
	virtual void set(const func * fnc);

	//! this = this + val
	virtual void plus(REAL val);

	//! this = this - val
	virtual void minus(REAL val);

	//! this = this * val
	virtual void mult(REAL val);

	//! this = this / val
	virtual void div(REAL val);

	//! this = val
	virtual void set(REAL val);

	//! adds normally-distributed noise with parameters N(0,std) to coeff
	virtual bool add_noise(REAL std);

	bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//
	// wavelets section
	//

	//! makes one wavelet-decomposition
	virtual bool decompose();

	//! calls decompose() while difference between calc_approx_norm() is lower than eps
	virtual bool auto_decompose(REAL eps, int norm = 0);
	
	//! makes one wavelet-reconstruction
	virtual bool reconstruct();

	//! calls reconstruct() until all details will be removed
	virtual bool full_reconstruct();

	//! returns details size
	virtual int  details_size() const;

	//! calculates function norm
	virtual REAL calc_approx_norm(int norm_type) const;

	//! grid for basis function placements
	grid * grd;

	//! coefficients for each basis function
	vec * coeff;
	
	//! sets function draw type - ( true - with triangles, false - with plates )
	bool show_smooth;

	//! all values in coeff equal to undef_value interprets as undefined
	REAL undef_value;

	//! horizontal details
	std::vector<vec *> * details_h;
 
	//! vertical details
	std::vector<vec *> * details_v; 

	//! diagonal details
	std::vector<vec *> * details_d; 

	//! X-direction enlarges
	std::vector<bool>  * enlarges_X; 

	//! Y-direction enlarges
	std::vector<bool>  * enlarges_Y; 

protected:

	//! i-cell number for show rect
	int show_i_from;
	//! i-cell number for show rect
	int show_i_to;
	//! j-cell number for show rect
	int show_j_from;
	//! j-cell number for show rect
	int show_j_to;

};

}; // namespace surfit;

#endif

