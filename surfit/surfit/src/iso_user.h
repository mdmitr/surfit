
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

#ifndef __surfit_iso_user_included__
#define __surfit_iso_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class iso;

/*! \ingroup surfit_data_variables
    \var surfit_iso
    \brief isoline for interpolation

Isoline for interpolation. Isoline is a curv with one fixed z-value. 

By loading \ref iso object to surfit memory we write the follow functionals to the sequence:

\f[
P_{i,j} = \left( u_{i,j} - z \right)^2 = \min,
\f]

where \f$(i,j)\f$ are the cells indexes, crossed with isoline,
\f$z\f$ - isoline value, \f$u_{i,j}\f$ - value of (i,j) cell.

\par Example : 
\li \ref map_iso.tcl "Interpolation of isolines"

\sa
\li \ref surfit_isos
\li \ref iso
\li \ref tcl_iso "Tcl commands"

*/
extern SURFIT_EXPORT iso * surfit_iso;

/*! \ingroup surfit_variables_collections
    \var std::vector<iso *> * surfit_isos;
    collection of \ref iso objects
*/
extern SURFIT_EXPORT std::vector<iso *> * surfit_isos;

/*! \class iso_user
    \brief interface class for making equations from \ref iso
*/
class SURFIT_EXPORT iso_user : public user {
public:

	iso_user();
	~iso_user();
	
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

