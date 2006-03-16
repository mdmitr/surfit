
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

#ifndef __surfit_cntr_included__
#define __surfit_cntr_included__

#include "curv.h"

namespace surfit {

class d_cntr;
class vec;

SURFIT_EXPORT
d_cntr * create_cntr(vec * iX, vec * iY, vec * iZ,
	             const char * cntr_name = NULL);

/*! \class cntr
    \brief 3D contour for interpolation (see \ref surfit_cntr). See \ref tcl_cntr "Tcl commands" for \ref cntr.
*/
class SURFIT_EXPORT d_cntr : public d_curv {
protected:
	/*! constructor
	    \param iX_begin pointer to the first element of X-coordinates vector
	    \param iX_end   pointer to the last+1 element of X-coordinates vector
	    \param iY_begin pointer to the first element of Y-coordinates vector
	    \param iY_end   pointer to the last+1 element of Y-coordinates vector
	    \param iZ_begin pointer to the first element of line values vector
	    \param iZ_end   pointer to the last+1 element of line values vector
	    \param cntr_name name of contour
	*/
	d_cntr(vec * iX, vec * iY, vec * iZ,
	       const char * cntr_name = NULL);

	//! destructor
	~d_cntr();

public:

	friend SURFIT_EXPORT
	d_cntr * create_cntr(vec * iX, vec * iY, vec * iZ,
	                     const char * cntr_name);

	//! Z = Z + value
	void plus(REAL value);
	//! Z = Z - value
	void minus(REAL value);
	//! Z = Z * value
	void mult(REAL value);
	//! Z = Z / value
	void div(REAL value);

	//! returns minimum Z value of all data-points
	REAL minz() const;

	//! returns maximum Z value of all data-points
	REAL maxz() const;

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! pointer to the first element of line values vector
	vec * Z;

};

class d_points;
class d_grid;

/*! \ingroup surfit_data_variables
    \var surfit_cntr
    \brief 3D contour for interpolation

3D contour for interpolation. Contour is a line in 3D which set with 
points \f$(x_i,y_i,z_i)\f$. Between points countour is a straight line segment.

By loading \ref cntr object to surfit memory we write the follow functionals to the sequence:

\f[
P_{i,j} = \left( u_{i,j} - z_{i,j} \right)^2 = \min,
\f]

where \f$(i,j)\f$ are the cells indexes, crossed with contour,
\f$z_{i,j}\f$ - mean value of contour for the (i,j) cell, \f$u_{i,j}\f$ - value of (i,j) cell.

\par Example: 
\li \ref map_cntr.tcl "Interpolation of contours"

\sa
\li \ref surfit_cntrs
\li \ref cntr
\li \ref tcl_cntr "Tcl commands"

*/
extern SURFIT_EXPORT std::vector<d_cntr *> * surfit_cntrs;

SURFIT_EXPORT
d_points * discretize_cntr(const d_cntr * crv, d_grid * grd, const char * pnts_name);



}; // namespace surfit;

#endif

