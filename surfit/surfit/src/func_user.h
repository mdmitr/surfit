
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

#ifndef __surfit_func_user_included__
#define __surfit_func_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class func;

/*! \ingroup surfit_data_variables
    \var surfit_func
    \brief function for interpolation

Function for interpolation. We describe function with values in the cells of equidistant \ref grid
\n
\f[ u(x,y)=\sum\limits_{i=0}^{N-1} \sum\limits_{j=0}^{M-1}u_{i,j}, \f]
\n
where indexes i and j denotes (i,j) cell, \f$ u_{i,j} \f$ - value of (i,j) cell.
 
By loading \ref func to surfit memory we write the follow functionals to the sequence:
\f[
P_{i,j} = \left( u_{i,j} - f_{i,j} \right)^2 = \min,
\f]
where \f$f_{i,j}\f$ - funciton value in (i,j) cell. Before writing of functional, 
we use bilinear interpolation algortihm to recalc \ref func to \ref surfit_grid
  
About functional sequence and surfit method of function reconstruction CMOFS see \ref data.

\par Example : 
\li \ref map_func.tcl "Interpolation of ordered data points"

\sa 
\li \ref surfit_funcs
\li \ref func
\li \ref tcl_func "Tcl commands"

*/
extern SURFIT_EXPORT func * surfit_func;

/*! \ingroup surfit_variables_collections
    \var std::vector<func *> * surfit_funcs
    collection of \ref func objects
*/
extern SURFIT_EXPORT std::vector<func *> * surfit_funcs;

/*! \class func_user
    \brief interface class for making equations from \ref func
*/
class SURFIT_EXPORT func_user : public user {
public:

	//! constructor
	func_user();

	//! destructor
	~func_user();
	
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

