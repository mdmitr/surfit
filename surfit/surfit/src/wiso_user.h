
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

#ifndef __surfit_wiso_user_included__
#define __surfit_wiso_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class wiso;

/*! \ingroup surfit_data_variables
    \var surfit_wiso
    \brief isoline for approximation

Isoline for approximation. \ref wiso is an isoline (\ref iso) with informational weight. \ref wiso 
differs from \ref iso with the way of constructing functional 
(see \ref data and \ref surfit_iso for details)

By loading \ref wiso object to surfit memory we modify completer functional:

\f[
A_{i,j} + W_{i,j} = \min
\f]

\f[
W_{i,j} = w \left( u_{i,j} - z \right)^2 = \min,
\f]

where \f$(i,j)\f$ are the cells indexes, crossed with isoline, \f$A_{i,j}\f$ - 
\ref completer functional, \f$z\f$ - isoline value, w - informational weight,
\f$u_{i,j}\f$ - value of (i,j) cell.

\par Example : 
\li \ref map_wiso.tcl "Approximation of isolines" differs from \ref map_iso.tcl "Interpolation of isolines"

\sa
\li \ref surfit_wiso
\li \ref wiso
\li \ref tcl_wiso "Tcl commands"

*/
extern SURFIT_EXPORT wiso * surfit_wiso;

/*! \ingroup surfit_variables_collections
    \var std::vector<wiso *> * surfit_wisos;
    collection of \ref wiso objects
*/
extern SURFIT_EXPORT std::vector<wiso *> * surfit_wisos;

/*! \class wiso_user
    \brief interface class for making equations from \ref wiso
*/
class SURFIT_EXPORT wiso_user : public user {
public:

	wiso_user();
	~wiso_user();
	
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

