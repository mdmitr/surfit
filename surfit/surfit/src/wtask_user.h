
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

#ifndef __surfit_wtask_user_included__
#define __surfit_wtask_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class wtask;
class vec;
class sub_points;
class bitvec;

/*! \ingroup surfit_data_variables
    \var surfit_wtask
    \brief approximation scattered data points

This class describes the set of scattered data points with informational weights. 
These points are for surface reconstruction.
Each point describes by four values \f$ (x_i, y_i, z_i, w_i) \f$, 
where \f$ z_i \f$ is 
some physical value or something else value, \f$ w_i \f$ - informational weight, 
\f$ x_i. y_i \f$ point coordinates. 
You must use wtask if you don't want to fit points exactly, 
but if you want to approximate them.

By loading \ref wtask object to surfit memory we modify \ref completer functional by adding functional:
\f[
W_{i,j} = \sum\limits_{p=1}^P w_p( u_{i,j} - z_p)^2 = \min,
\f]
where \f$ u_{i,j} \f$ - cell (i,j),
\f$ z_p \f$ are the values of points \f$ (x_i,y_i), \ i=\overline{1,P}\f$ belong to cell (i,j).

We write \ref completer functional with wtask functional:
\f[
A_{i,j} + W_{i,j} = \min
\f]

About functional sequence and surfit method of function reconstruction see \ref data.
For details about functions see (\ref func).

\par Example : 
\li \ref map_wtask.tcl

\sa
\li \ref surfit_wtasks
\li \ref wtask
\li \ref tcl_wtask "Tcl commands"

*/
extern SURFIT_EXPORT wtask * surfit_wtask;

/*! \ingroup surfit_variables_collections
    \var std::vector<wtask *> * surfit_wtasks
    collection of \ref wtask objects (scattered data-points with weights)
*/
extern SURFIT_EXPORT std::vector<wtask *> * surfit_wtasks;

typedef std::vector<sub_points *> sub_tasks;
extern SURFIT_EXPORT sub_tasks * sub_wtsks;
extern SURFIT_EXPORT wtask * wtsk;
extern SURFIT_EXPORT std::vector<wtask *> * wtasks_garbage;

SURFIT_EXPORT
int calcVecV_points(modifier1 * usr, 
		    vec * V, 
		    wtask * wtsk, 
		    std::vector<sub_points *> * sub_wtsks,
		    bitvec * mask_solved,
		    bitvec * mask_undefined);

/*! \class wtask_user
    \brief interface class for making equations from \ref wtask
*/
class SURFIT_EXPORT wtask_user : public user {
public:

	//! constructor
	wtask_user();

	//! destructor
	~wtask_user();

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

