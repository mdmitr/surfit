
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

#ifndef __surfit_wcntr_user_included__
#define __surfit_wcntr_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class wcntr;

/*! \ingroup surfit_data_variables
    \var surfit_wcntr
    \brief 3D contour for approximation

3D contour for approximation. Contour with weight is a line in 3D which 
set with points \f$(x_i,y_i,z_i)\f$. Between points
countour is a straight line segment. Additionaly wcntr have informational weight. 
\ref wcntr differs from \ref cntr with the way of constructing functional 
(see \ref data for details).

By loading \ref wcntr object to surfit memory we modify completer functional:

\f[
A_{i,j} + W_{i,j} = \min
\f]

\f[
W_{i,j} = w \left( u_{i,j} - z_{i,j} \right)^2 = \min,
\f]

where \f$(i,j)\f$ are the cells indexes, crossed with contour, \f$A_{i,j}\f$ - 
\ref completer functional, \f$z_{i,j}\f$ - mean value of contour for the (i,j) cell, 
w - informational weight, \f$u_{i,j}\f$ - value of (i,j) cell.

\par Example: 
\li \ref map_wcntr.tcl "Approximation of contours" differs from 
\ref map_cntr.tcl "Interpolation of contours"

\sa 
\li \ref surfit_wcntrs
\li \ref wcntr
\li \ref tcl_wcntr "Tcl commands"

*/
extern SURFIT_EXPORT wcntr * surfit_wcntr;

/*! \ingroup surfit_variables_collections
    \var std::vector<wcntr *> * surfit_wcntrs;
    collection of \ref wcntr objects
*/
extern SURFIT_EXPORT std::vector<wcntr *> * surfit_wcntrs;

/*! \class wcntr_user
    \brief interface class for making equations from \ref wcntr
*/
class SURFIT_EXPORT wcntr_user : public user {
public:

	//! constructor
	wcntr_user();

	//! destructor
	~wcntr_user();
	
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

