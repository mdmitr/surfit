
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

#ifndef __surfit__func__
#define __surfit__func__

#include <vector>

#include "surfit_data.h"

namespace surfit {

class vec;
class datafile;
class d_grid;
class d_mask;
class d_func;
class bitvec;

SURFIT_EXPORT
d_func * create_func(vec *icoeff, d_grid *igrd, const char * funcname = 0);
SURFIT_EXPORT
d_func * create_func_by_mask(d_mask * msk);

/*! \class func
    \brief class for a function, based on the equidistant \ref grid with values set at the centers of the cells (see \ref surfit_func). See \ref tcl_func "Tcl commands" for \ref func.
*/
class SURFIT_EXPORT d_func : public data {
protected:
	/*! constructor
	    \param igrd uniform 2d-grid
	    \param icoeff coefficients a_i
	    \param funcname name
	*/
	d_func(vec *icoeff, d_grid *igrd,
	       const char * funcname = 0);

	//! constructor
	d_func(d_mask * msk);

	//! destructor
	virtual ~d_func();
	
public:

	friend SURFIT_EXPORT
	d_func * create_func(vec *icoeff, d_grid *igrd, const char * funcname);
	friend SURFIT_EXPORT
	d_func * create_func_by_mask(d_mask * msk);

	//! calculates function value at point (x,y)
	virtual REAL getValue(REAL x, REAL y) const; 

	//! calculates function value at point (x,y) using bilinear interpolation
	virtual REAL getInterpValue(REAL x, REAL y) const;

	//! calculates function mean value for rect
	virtual REAL getMeanValue(REAL x_from, REAL x_to, REAL y_from, REAL y_to) const;

	//! returns function value at node (i,j)
	virtual REAL getValueIJ(int i, int j) const;

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

	virtual REAL wmean(const d_func * wfnc) const;

	//! returns standard deviation value from mean 'mean' value
	virtual REAL std(REAL mean) const;

	//! returns sum of all Z values for all nodes
	virtual REAL sum() const;

	//! calculates minimum and maximum Z values 
	virtual bool getMinMaxZ(REAL & minZ, REAL & maxZ) const;

	//! calculates minimum and maximum Z values with mask
	virtual bool getMinMaxZ_mask(REAL & minZ, REAL & maxZ, const bitvec * msk) const;

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
	virtual bool compare_grid(const d_func * fnc) const;

	//! this = this + fnc
	virtual void plus(const d_func * fnc);
	virtual void plus_mask(const d_func * fnc, const bitvec * mask);
	
	//! this = this - fnc, undef means no operation
	virtual void minus(const d_func * fnc);
	virtual void minus_mask(const d_func * fnc, const bitvec * mask);

	//! this = this - fnc, undef means undef
	virtual void minus_undef(const d_func * fnc);
	virtual void minus_undef_mask(const d_func * fnc, const bitvec * mask);
	
	//! this = this * fnc
	virtual void mult(const d_func * fnc);
	virtual void mult_mask(const d_func * fnc, const bitvec * mask);
	
	//! this = this / fnc
	virtual void div(const d_func * fnc);
	virtual void div_undef(const d_func * fnc);
	virtual void div_mask(const d_func * fnc, const bitvec * mask);
	
	//! this = fnc
	virtual void set(const d_func * fnc);
	virtual void set_mask(const d_func * fnc, const bitvec * mask);

	//! this = this + val
	virtual void plus(REAL val);
	virtual void plus_mask(REAL val, const bitvec * mask);

	//! this = this - val
	virtual void minus(REAL val);
	virtual void minus_mask(REAL val, const bitvec * mask);

	//! this = this * val
	virtual void mult(REAL val);
	virtual void mult_mask(REAL val, const bitvec * mask);

	//! this = this / val
	virtual void div(REAL val);
	virtual void div_mask(REAL val, const bitvec * mask);

	//! this = val
	virtual void set(REAL val);
	virtual void set_mask(REAL val, const bitvec * mask);

	//! sets new undef_value
	virtual void set_undef_value(REAL new_undef_value);

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
	d_grid * grd;

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

};

/*! \ingroup surfit_variables_collections
    \var std::vector<d_func *> * surfit_funcs
    collection of \ref func objects
*/
extern SURFIT_EXPORT std::vector<d_func *> * surfit_funcs;


}; // namespace surfit;

#endif

