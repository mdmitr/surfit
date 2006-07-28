
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

#ifndef __surfit__mask__
#define __surfit__mask__

#include "surfit_data.h"

namespace surfit {

class d_func;
class d_grid;
class datafile;
class bitvec;
class d_mask;

SURFIT_EXPORT
d_mask * create_mask(bitvec *icoeff, d_grid *igrd, const char * funcname = 0);

/*! \class d_mask
    \brief sets domain for the surface 
*/
class SURFIT_EXPORT d_mask : public data {
protected:
	/*! constructor 
	    \param igrd uniform 2d-grid
	    \param icoeff coefficients a_i
	    \param funcname name
	*/
	d_mask(bitvec *icoeff, d_grid *igrd, const char * funcname = 0);

	//! destructor
	~d_mask();

public:

	//! constructor
	friend SURFIT_EXPORT
	d_mask * create_mask(bitvec *icoeff, d_grid *igrd, const char * funcname);

	bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	bool getMinMaxZ(REAL & minz, REAL & maxz) const;
	
	//! calculates mask value at point (x,y)
	bool getValue(REAL x, REAL y) const; 

	//! returns mask value at node (i,j)
	bool getValueIJ(size_t i, size_t j) const;
	//! sets mask value for node (i,j)
	void setValueIJ(size_t i, size_t j, bool value);

	//! returns minimum X-coordinate for the mask
	REAL getMinX() const;

	//! returns maximum X-coordinate for the mask
	REAL getMaxX() const;

	//! returns minimum Y-coordinate for the mask
	REAL getMinY() const;

	//! returns maximum Y-coordinate for the smask
	REAL getMaxY() const;

	//! returns amount of cells for X direction
	size_t getCountX() const;

	//! returns amount of cells for Y direction
	size_t getCountY() const;

	//! returns distance between of centers of cells in X direction
	REAL getStepX() const;

	//! returns distance between of centers of cells in Y direction
	REAL getStepY() const;

	//! calculates coordinates of the center of the (i,j) cell
	void getCoordNode(size_t i, size_t j, REAL & x, REAL & y) const;

	//! returns X-coordinate of the center of the (i,j) cell
	REAL getCoordNodeX(size_t i) const;

	//! returns Y-coordinate of the center of the (i,j) cell
	REAL getCoordNodeY(size_t j) const;

	//! returns i-cell number for X-coordinate
	size_t get_i(REAL x) const;

	//! returns j-cell number for Y-coordinate
	size_t get_j(REAL y) const;

	//! for saving in surfit datafile
	bool writeTags(datafile *df) const;

	//! compares grid with other mask grid
	bool compare_grid(const d_mask * mask) const;
	
	//! and operation with another mask
	virtual void AND(const d_mask * msk);
	//! not operation with another mask
	virtual void NOT(const d_mask * msk);
	//! or operation with another mask
	virtual void OR(const d_mask * msk);
	//! xor operation with another mask
	virtual void XOR(const d_mask * msk);

	bitvec * get_bitvec_mask(const d_grid * grid) const;

	//! equidistant grid for mask
	d_grid * grd;

	//! coefficients for each basis function
	bitvec * coeff;

	//! drawing flag
	bool show_smooth;

};

/*! \ingroup surfit_variables_collections
    \var std::vector<d_mask *> * surfit_masks
    collection of \ref mask objects
*/
extern SURFIT_EXPORT std::vector<d_mask *> * surfit_masks;

}; // namespace surfit

#endif



