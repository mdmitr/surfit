
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

#ifndef __surfit_cntr_user_included__
#define __surfit_cntr_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class cntr;

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
extern SURFIT_EXPORT cntr * surfit_cntr;

/*! \ingroup surfit_variables_collections
    \var std::vector<cntr *> * surfit_cntrs;
    collection of \ref cntr objects
*/
extern SURFIT_EXPORT std::vector<cntr *> * surfit_cntrs;

/*! \class cntr_user
    \brief interface class for making equations from \ref cntr
*/
class SURFIT_EXPORT cntr_user : public user {
public:

	//! constructor
	cntr_user();

	//! destructor
	~cntr_user();
	
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

