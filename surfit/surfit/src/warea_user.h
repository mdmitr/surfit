
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

#ifndef __surfit_warea_user_included__
#define __surfit_warea_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class warea;
class bitvec;
class vec;

/*! \ingroup surfit_data_variables
    \var surfit_warea
    \brief surface area with constant value for approximation

Surface area with constant value for approximation. warea is a closed curve (see \ref curv). This curve is the bound of warea. warea have two parameters: value for
the cells with centers in warea and informational weight to control approximation. 
warea is analogue of \ref area, but differs with the way of constructing functional
(see \ref data for details)

By loading \ref warea object to surfit memory we modify completer functional:

\f[
A_{i,j} + W_{i,j} = \min
\f]

\f[
W_{i,j} = w \left( u_{i,j} - z \right)^2 = \min,
\f]

where \f$(i,j)\f$ are the cells indexes, which are in the area, \f$A_{i,j}\f$ - 
\ref completer functional, \f$z\f$ - area value, w - informational weight,
\f$u_{i,j}\f$ - value of (i,j) cell.

\par Example : 
\li \ref map_warea.tcl "Approximation of areas" differs from \ref map_area.tcl "Interpolation of areas"

\sa
\li \ref surfit_wareas
\li \ref warea
\li \ref tcl_warea "Tcl commands"

*/
extern SURFIT_EXPORT warea * surfit_warea;

/*! \ingroup surfit_variables_collections
    \var std::vector<warea *>  * surfit_wareas;
    collection of \ref warea objects
*/
extern SURFIT_EXPORT std::vector<warea *>  * surfit_wareas;

SURFIT_EXPORT
int calcVecV_wareas(modifier1 * cmpltr_usr, vec * V, bitvec * mask_solved, bitvec * mask_undefined);

/*! \class warea_user
    \brief interface class for making equations from \ref warea
*/
class SURFIT_EXPORT warea_user : public user {
public:

	//! constructor
	warea_user();

	//! destructor
	~warea_user();
	
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

