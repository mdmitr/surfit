
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

#ifndef __surfit_area_user_included__
#define __surfit_area_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class area;

/*! \ingroup surfit_data_variables
    \var surfit_area
    \brief surface area with constant value for interpolation

Surface area with constant value for interpolation. Area is a closed curve 
(see \ref curv). This curve is the bound of the area. 
Area have one parameter - the value for the cells wich centers are in area.

By loading \ref area object to surfit memory we write the follow functionals 
to the sequence:

\f[
P_{i,j} = \left( u_{i,j} - z \right)^2 = \min,
\f]

where \f$(i,j)\f$ are the cells indexes, which are in the area,
\f$z\f$ - value of the area, \f$u_{i,j}\f$ - value of (i,j) cell.

\par Example: 
\li \ref map_area.tcl "Interpolation of areas"

\sa 
\li \ref surfit_areas
\li \ref area
\li \ref tcl_area "Tcl commmands"

*/
extern SURFIT_EXPORT area * surfit_area;

/*! \ingroup surfit_variables_collections
    \var std::vector<area *>  * surfit_areas;
    collection of \ref area objects
*/
extern SURFIT_EXPORT std::vector<area *>  * surfit_areas;

class grid_line;

extern SURFIT_EXPORT grid_line * area_grd_line;

/*! \class area_user
    \brief interface class for making equations from \ref area
*/
class SURFIT_EXPORT area_user : public user {
public:

	//! constructor
	area_user();

	//! destructor
	~area_user();
	
	int max_priority();
	void init();
	void prepare();
	void begin();
	void stage1(int priority);
	void stage2(int priority);
	void stage3(int priority);
	void stage4(int priority);
	void stage5(int priority);
	void finish();
	void release();

};

}; // namespace surfit;

#endif

