
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

#ifndef __surfit__points__
#define __surfit__points__

#include <vector>
#include "data.h"

namespace surfit {

class wtask;

/*! \class points
    \brief scattered points in 3D 
*/
class SURFIT_EXPORT points {
public:

	//! constructor
	points();
	
	/*! another constructor
	    \param X_begin pointer to begin of X data array
	    \param X_end pointer to end of X data array
	    \param Y_begin pointer to begin of Y data array
	    \param Y_end pointer to end of Y data array
	    \param Z_begin pointer to begin of Z data array
	    \param Z_end pointer to end of Z data array
	    \param points_name name
	*/
	points(REAL *& X_begin, REAL * X_end, 
               REAL *& Y_begin, REAL * Y_end, 
               REAL *& Z_begin, REAL * Z_end,
               const char * points_name = NULL);

	//! destructor
	virtual ~points();

	//! returns amount of points
	int size() const;

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
                         
	//! pointer to begin of X data array
	REAL * X_begin;
	//! pointer to end of X data array
	REAL * X_end;
	//! pointer to begin of Y data array
	REAL * Y_begin; 
	//! pointer to end of Y data array
	REAL * Y_end;   
	//! pointer to begin of Z data array
	REAL * Z_begin; 
	//! pointer to end of Z data array
	REAL * Z_end;   

	//! this = this + pnts
	bool plus(const points * pnts);

	//! this = this - pnts
	bool minus(const points * pnts);
	
	//! this = this * pnts
	bool mult(const points * pnts);

	//! this = this/pnts
	bool div(const points * pnts);

	//! this = pnts
	bool set(const points * pnts);

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

};

/*! \class sub_points
    \brief subset of points for some cell
*/
class SURFIT_EXPORT sub_points {
public:

	//! constructor
	sub_points(int icell_number, 
		   std::vector<unsigned int> * ipoint_numbers);
	
	//! destructor
	~sub_points();

	//! calculates mean of values of all subset of points
	REAL value(const points * pnts) const;
	//! calculates sum of values of all subset of points values
	REAL sum_value(const points * pnts) const;
	//! calculates weighted mean of values of all subset weighted points
	REAL value(const wtask * wtsk) const;
	//! calculates average weight for cell
	REAL weight(const wtask * wtsk) const;

	//! number of cell
	unsigned int cell_number;
	//! numbers of points for cell
	std::vector<unsigned int> * point_numbers;
	
};

typedef std::vector<sub_points *> sub_tasks;

SURFIT_EXPORT
/*! \ingroup internal_points
    \fn void _sort_points(points * pnts, std::vector<unsigned int> * nums, REAL **& sortx_begin, REAL **& sortx_end, REAL **& sorty_begin, REAL **& sorty_end);
    \brief performs points sorting
*/
void _sort_points(points * pnts, 
		  std::vector<unsigned int> * nums,
		  REAL **& sortx_begin, 
		  REAL **& sortx_end, 
		  REAL **& sorty_begin, 
		  REAL **& sorty_end);

SURFIT_EXPORT
/*! \ingroup internal_points
    \fn void _points_transform(points * pnts, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes geometrical transform on \ref points class (shifting and scaling)
*/
void _points_transform(points * pnts, 
		       REAL shiftX, REAL scaleX, 
		       REAL shiftY, REAL scaleY);

SURFIT_EXPORT
/*! \ingroup internal_points
    \fn void _inverse_points_transform(points * pnts, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes inverse to \ref _points_transform operation
*/
void _inverse_points_transform(points * pnts, 
			       REAL shiftX, REAL scaleX, 
			       REAL shiftY, REAL scaleY);


}; // namespace surfit;

#endif

