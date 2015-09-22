
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

#ifndef __surfit__points__
#define __surfit__points__

#include <vector>
#include "surfit_data.h"
#include "vec.h"

namespace surfit {

class vec;
class strvec;
class d_points;

//! constructs default \ref d_points object
SURFIT_EXPORT
d_points * create_points_default();

//! constructs \ref d_points from \ref vec "vectors"
SURFIT_EXPORT
d_points * create_points(vec *& iX, vec *& iY, vec *& iZ,
			 const char * points_name = NULL);

//! constructs \ref d_points from \ref vec "vectors" and strvec with names
SURFIT_EXPORT
d_points * create_points(vec *& iX, vec *& iY, vec *& iZ,
			 strvec *& names,
			 const char * points_name = NULL);

//! constructs \ref d_points from another \ref d_points
SURFIT_EXPORT
d_points * create_points(const d_points * ipnts);

/*! \class d_points
    \brief scattered points in 3D 
*/
class SURFIT_EXPORT d_points : public data {
protected:
	//! constructor
	d_points();
	
	/*! constructor from \ref vec "vectors"
	    \param iX X coords array
	    \param iY Y coords array
	    \param iZ Z coords array
	    \param points_name name
	*/
	d_points(vec *& iX, vec *& iY, vec *& iZ,
                 const char * points_name = NULL);

	/*! constructor from \ref vec "vectors" and with names
	    \param iX X coords array
	    \param iY Y coords array
	    \param iZ Z coords array
	    \param inames array with points names
	    \param points_name name
	*/
	d_points(vec *& iX, vec *& iY, vec *& iZ,
		 strvec *& inames,
		 const char * points_name = NULL);

	//! destructor
	~d_points();

public:

	friend SURFIT_EXPORT
	//! creates empty d_points object 
	d_points * create_points_default();

	friend SURFIT_EXPORT
	//! creates d_points object from \ref vec "vectors"
	d_points * create_points(vec *& iX, vec *& iY, vec *& iZ,
				 const char * points_name);

	friend SURFIT_EXPORT
	//! creates d_points object from \ref vec "vectors" and with names
	d_points * create_points(vec *& iX, vec *& iY, vec *& iZ,
				 strvec *& names,
				 const char * points_name);

	friend SURFIT_EXPORT
	//! creates d_points from another d_points
	d_points * create_points(const d_points * ipnts);

	// from surfit_data
	bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! returns amount of points
	size_t size() const;

	//! calculates mean value of all points values
	REAL mean() const;

	//! returns minimum X-coordinate for all points
	REAL minx() const;

	//! returns maximum X-coordinate for all points
	REAL maxx() const;

	//! returns minimum Y-coordinate for all points
	REAL miny() const;

	//! returns maximum Y-coordinate for all points
	REAL maxy() const;

	//! returns minimum Z value for all points
	REAL minz() const;

	//! returns maximum Z value for all points
	REAL maxz() const;

	//! calculates standart deviation value from mean value
	REAL std(REAL mean) const;

	//! calculates absolute Z values for all points
	void abs();
        
	//! X data array
	vec * X;

	//! Y data array
	vec * Y;

	//! Z data array
	vec * Z;

	//! names array
	strvec * names;
	
	//! this = this + pnts
	bool plus(const d_points * pnts);

	//! this = this - pnts
	bool minus(const d_points * pnts);
	
	//! this = this * pnts
	bool mult(const d_points * pnts);

	//! this = this/pnts
	bool div(const d_points * pnts);

	//! this = pnts
	bool set(const d_points * pnts);

	//! this = this + val
	void plus(REAL val);

	//! this = this - val
	void minus(REAL val);

	//! this = this * val
	void mult(REAL val);

	//! this = this / val
	void div(REAL val);

	//! this = val
	void set(REAL val);

	//! removes all points with z == val
	void remove_with_value(REAL val);

};

//! collection of \ref d_points objects (scattered data-points)
class SURFIT_EXPORT pnts_container : public objects_container<d_points>
{
public:
	virtual void push_back(d_points * elem);
};

//! container of \ref d_points objects
extern SURFIT_EXPORT pnts_container * surfit_pnts;

/*! \class sub_points
    \brief subset of points for some cell
*/
class SURFIT_EXPORT sub_points {
public:

	//! constructor
	sub_points(int icell_number, 
		   std::vector<size_t> * ipoint_numbers);
	
private:
	//! destructor
	~sub_points();

public:
	//! dectructor
	void release();

	//! calculates mean of values of all subset of points
	REAL value(const d_points * pnts) const;
	//! calculates sum of values of all subset of points values
	REAL sum_value(const d_points * pnts) const;

	//! calculate bounds
	void bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy, const d_points * pnts) const;
	
	//! number of cell
	size_t cell_number;
	//! numbers of points for cell
	std::vector<size_t> * point_numbers;
	
};

//! vector of \ref sub_points
typedef std::vector<sub_points *> sub_pnts;

//! performs points sorting
SURFIT_EXPORT
void _sort_points(const d_points * pnts, 
		  std::vector<size_t> * nums,
		  std::vector<size_t> & sortx,
		  std::vector<size_t> & sorty);

//! makes geometrical transform on \ref d_points (shifting and scaling)
SURFIT_EXPORT
void _points_transform(vec * X, vec * Y, 
		       REAL shiftX, REAL scaleX, 
		       REAL shiftY, REAL scaleY);

//! makes inverse to \ref _points_transform operation
SURFIT_EXPORT
void _inverse_points_transform(d_points * pnts, 
			       REAL shiftX, REAL scaleX, 
			       REAL shiftY, REAL scaleY);


}; // namespace surfit;

#endif

