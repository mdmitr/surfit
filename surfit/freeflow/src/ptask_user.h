
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

#ifndef __flow_ptask_user_included__
#define __flow_ptask_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class ptask;
class bitvec;
class sub_points;
typedef std::vector<sub_points *> sub_tasks;
class lcm_simple;

/*! \ingroup flow_data_variables
    \var flow_ptask
    \brief scattered data points (\ref ptask) with "production" values

This class describes the set of scattered data points for surface reconstruction.
Each point describes by three coordinates \f$ (x_i, y_i, z_i) \f$, where \f$ z_i \f$ is 
fluid rate/injectivity for point.

By loading \ref ptask object to memory we modify \ref flow_lcm_simple functional by adding functional:

\f[
W_{i,j} = - z_p u_{i,j}
\f]

So, we get \ref flow_lcm_simple functional for this cell:
\f[
A_{i,j} + W_{i,j} = \min
\f]

Differentiation of this expression by \f$ u_{i,j} \f$ leads to law of 
conservation of mass with external source of run-off written for the cell (i,j).

\par Example : 
\li \ref map_ptask.tcl

\sa
\li \ref flow_ptasks
\li \ref ptask
\li \ref tcl_ptask "Tcl commands"


*/
extern FLOW_EXPORT ptask * flow_ptask;

/*! \ingroup flow_variables_collections
    \var std::vector<task *> * flow_ptasks
    \brief collection of \ref ptask objects ("production" scattered data-points)
*/
extern FLOW_EXPORT std::vector<ptask *> * flow_ptasks;

extern FLOW_EXPORT sub_tasks * sub_ptsks;
extern FLOW_EXPORT std::vector<void *> * a_sub_ptsks;
extern FLOW_EXPORT std::vector<ptask *> * ptasks_garbage;

FLOW_EXPORT
int calcVecV_ptask(lcm_simple * usr, vec * V, bitvec * mask_solved, bitvec * mask_undefined);

/*! \class ptask_user
    \brief class for ptask usage in solving algorithm
*/
class FLOW_EXPORT ptask_user : public user {
public:

	//! constructor
	ptask_user();

	//! destructor
	~ptask_user();
	
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

