
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

#ifndef __surfit_wfunc_user_included__
#define __surfit_wfunc_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class wfunc;
class bitvec;
class vec;

/*! \ingroup surfit_data_variables
    \var surfit_wfunc
    \brief function for approximation

Function for approximation. By loading \ref wfunc object to surfit memory we modify \ref completer functional:
\f[
A_{i,j} + W_{i,j} = \min
\f]

\f[
W_{i,j} = w \left( u_{i,j} - f_{i,j} \right)^2 = \min,
\f]
where \f$A_{i,j}\f$ - \ref completer functional, \f$f_{i,j}\f$ - value in (i,j) cell, 
w - informational weight. See also \ref func.

About functional sequence and surfit method of function reconstruction (CMOFS) see \ref data.

\par Examples : 
\li \ref map_wfunc.tcl "Approximation of ordered data points"

\sa
\li \ref surfit_wfuncs
\li \ref wfunc
\li \ref tcl_wfunc "Tcl commands"

*/
extern SURFIT_EXPORT wfunc * surfit_wfunc;

/*! \ingroup surfit_variables_collections
    \var std::vector<wfunc *> * surfit_wfuncs
    collection of \ref wfunc objects
*/
extern SURFIT_EXPORT std::vector<wfunc *> * surfit_wfuncs;

SURFIT_EXPORT
int calcVecV_wfuncs(modifier1 * usr, vec * V, bitvec * mask_solved, bitvec * mask_undefined);

/*! \class wfunc_user
    \brief interface class for making equations from \ref wfunc
*/
class SURFIT_EXPORT wfunc_user : public user {
public:

	//! constructor
	wfunc_user();

	//! destructor
	~wfunc_user();
	
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

