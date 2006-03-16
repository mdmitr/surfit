
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

/*! \class mask
    \brief sets domain of the function (see \ref surfit_mask). See \ref tcl_mask "Tcl commands" for \ref mask.
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

	friend SURFIT_EXPORT
	d_mask * create_mask(bitvec *icoeff, d_grid *igrd, const char * funcname);

	bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	bool getMinMaxZ(REAL & minz, REAL & maxz) const;
	
	bool getValue(REAL x, REAL y) const; 
	bool getValueIJ(int i, int j) const;
	void setValueIJ(int i, int j, bool value);
	REAL getMinX() const;
	REAL getMaxX() const;
	REAL getMinY() const;
	REAL getMaxY() const;
	
	int getCountX() const;
	int getCountY() const;
	REAL getStepX() const;
	REAL getStepY() const;
	void getCoordNode(int i, int j, REAL & x, REAL & y) const;
	REAL getCoordNodeX(int i) const;
	REAL getCoordNodeY(int j) const;
	int get_i(REAL x) const;
	int get_j(REAL y) const;
	bool writeTags(datafile *df) const;

	bool compare_grid(const d_mask * mask) const;
	
	//! and operation with another mask
	virtual void AND(const d_mask * msk);
	//! not operation with another mask
	virtual void NOT(const d_mask * msk);
	//! or operation with another mask
	virtual void OR(const d_mask * msk);
	//! xor operation with another mask
	virtual void XOR(const d_mask * msk);

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



