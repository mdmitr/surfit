
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

#ifndef __surfit__surf__
#define __surfit__surf__

#include <vector>

#include "surfit_data.h"

namespace surfit {

class vec;
class datafile;
class d_grid;
class d_mask;
class d_surf;
class bitvec;

SURFIT_EXPORT
d_surf * create_surf(vec *icoeff, d_grid *igrd, const char * surfname = 0);
SURFIT_EXPORT
d_surf * create_surf_by_mask(d_mask * msk);

/*! \class d_surf
    \brief class for a surface, based on the equidistant \ref d_grid with values 
    set at the centers of the cells.
*/
class SURFIT_EXPORT d_surf : public data {
protected:
	/*! constructor
	    \param igrd uniform 2d-grid
	    \param icoeff coefficients a_i
	    \param surfname name
	*/
	d_surf(vec *icoeff, d_grid *igrd,
	       const char * surfname = 0);

	//! constructor
	d_surf(d_mask * msk);

	//! destructor
	virtual ~d_surf();
	
public:

	//! constructor
	friend SURFIT_EXPORT
	d_surf * create_surf(vec *icoeff, d_grid *igrd, const char * surfname);

	//! constructor
	friend SURFIT_EXPORT
	d_surf * create_surf_by_mask(d_mask * msk);

	//! calculates surface value at point (x,y)
	virtual REAL getValue(REAL x, REAL y) const; 

	//! calculates surface value at point (x,y) using bilinear interpolation
	virtual REAL getInterpValue(REAL x, REAL y) const;

	//! calculates surface mean value for rect
	virtual REAL getMeanValue(REAL x_from, REAL x_to, REAL y_from, REAL y_to) const;

	//! returns surface value at node (i,j)
	virtual REAL getValueIJ(size_t i, size_t j) const;

	//! returns minimum X-coordinate for the surface
	virtual REAL getMinX() const;

	//! returns maximum X-coordinate for the surface
	virtual REAL getMaxX() const;

	//! returns minimum Y-coordinate for the surface
	virtual REAL getMinY() const;

	//! returns maximum Y-coordinate for the surface
	virtual REAL getMaxY() const;

	//! returns mean Z value for all nodes
	virtual REAL mean() const;

	//! returns weighted mean value for all nodes
	virtual REAL wmean(const d_surf * wsrf) const;

	//! returns standard deviation value from mean 'mean' value
	virtual REAL std(REAL mean) const;

	//! returns sum of all Z values for all nodes
	virtual REAL sum() const;

	//! calculates minimum and maximum Z values 
	virtual bool getMinMaxZ(REAL & minZ, REAL & maxZ) const;

	//! calculates minimum and maximum Z values with mask
	virtual bool getMinMaxZ_mask(REAL & minZ, REAL & maxZ, const bitvec * msk) const;

	//! returns amount of cells for X direction
	virtual size_t getCountX() const;

	//! returns amount of cells for Y direction
	virtual size_t getCountY() const;

	//! returns distance between of centers of cells in X direction
	virtual REAL getStepX() const;

	//! returns distance between of centers of cells in Y direction
	virtual REAL getStepY() const;

	//! calculates coordinates of the center of the (i,j) cell
	virtual void getCoordNode(size_t i, size_t j, REAL & x, REAL & y) const;

	//! returns X-coordinate of the center of the (i,j) cell
	virtual REAL getCoordNodeX(size_t i) const;

	//! returns Y-coordinate of the center of the (i,j) cell
	virtual REAL getCoordNodeY(size_t j) const;

	//! returns i-cell number for X-coordinate
	virtual size_t get_i(REAL x) const;
	
	//! returns j-cell number for Y-coordinate
	virtual size_t get_j(REAL y) const;

	//! returns amount of cells with defined values
	virtual size_t defined() const;

	//! writes tag for saving surf to datafile 
	virtual bool writeTags(datafile * df) const;

	//! compares two surfitons by their grids
	virtual bool compare_grid(const d_surf * srf) const;

	//! this = this + srf
	virtual void plus(const d_surf * srf);
	//! this = this + srf where mask == true
	virtual void plus_mask(const d_surf * srf, const bitvec * mask);
	
	//! this = this - srf, undef means no operation
	virtual void minus(const d_surf * srf);
	//! this = this - srf where mask == true
	virtual void minus_mask(const d_surf * srf, const bitvec * mask);

	//! this = this * srf
	virtual void mult(const d_surf * srf);
	//! this = this * srf where mask == true
	virtual void mult_mask(const d_surf * srf, const bitvec * mask);
	
	//! this = this / srf
	virtual void div(const d_surf * srf);
	//! this = this / srf where mask == true
	virtual void div_mask(const d_surf * srf, const bitvec * mask);
	
	//! this = srf
	virtual void set(const d_surf * srf);
	//! this = this = srf where mask == true
	virtual void set_mask(const d_surf * srf, const bitvec * mask);

	//! this = this + val
	virtual void plus(REAL val);
	//! this = this + val where mask == true
	virtual void plus_mask(REAL val, const bitvec * mask);

	//! this = this - val
	virtual void minus(REAL val);
	//! this = this - val where mask == true
	virtual void minus_mask(REAL val, const bitvec * mask);

	//! this = this * val
	virtual void mult(REAL val);
	//! this = this * val where mask == true
	virtual void mult_mask(REAL val, const bitvec * mask);

	//! this = this / val
	virtual void div(REAL val);
	//! this = this / val where mask == true
	virtual void div_mask(REAL val, const bitvec * mask);

	//! this = val
	virtual void set(REAL val);
	//! this = val where mask == true
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
	virtual size_t  details_size() const;

	//! calculates surface norm
	virtual REAL calc_approx_norm(int norm_type) const;

	//! grid for basis surface placements
	d_grid * grd;

	//! coefficients for each basis surface
	vec * coeff;
	
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
    \var std::vector<d_surf *> * surfit_surfs
    collection of \ref surf objects
*/
extern SURFIT_EXPORT std::vector<d_surf *> * surfit_surfs;


}; // namespace surfit;

#endif

