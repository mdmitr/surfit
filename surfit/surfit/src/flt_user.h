
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

#ifndef __surfit_flt_user_included__
#define __surfit_flt_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class flt;
class grid_line;
class grid;

/*! \ingroup surfit_data_variables
    \var surfit_flt
    \brief tectonical fault line

Tectonical fault line. Fault line is a curv which breaks connection between 
neighbour cells, crossed with fault line. See (\ref data for details)

To take fault line in terms of grid, fault line transforms to \ref grid_line using modified 
Brezengham algorithm. After that fault line presented as a set of cell borders. 

By loading \ref flt object to surfit memory we modify \ref completer functional:
\f[
A_{i,j} = \min.
\f]

The summands, for which two neighbour cells have the "faulted" borders will be removed from the functional.

\par Example : 
\li \ref map_flt.tcl "Interpolation of scattered data points with faults"

\sa
\li \ref surfit_flts
\li \ref flt
\li \ref tcl_flt "Tcl commands"

*/
extern SURFIT_EXPORT flt * surfit_flt;

/*! \ingroup surfit_variables_collections
     \var std::vector<flt *> * surfit_flts;
     collection of \ref flt objects
*/
extern SURFIT_EXPORT std::vector<flt *> * surfit_flts;

extern SURFIT_EXPORT grid_line * fault_grd_line;

SURFIT_EXPORT
grid_line * trace_faults(int current_priority,
			 grid * grd);

/*! \class flt_user
    \brief interface class for making equations from \ref flt_user
*/
class SURFIT_EXPORT flt_user : public user {
public:

	//! constructor
	flt_user();

	//! destructor
	~flt_user();

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

