
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

#ifndef __surfit_task_user_included__
#define __surfit_task_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class task;

/*! \ingroup surfit_data_variables
    \var surfit_task
    \brief interpolation scattered data points

This class describes the set of scattered data points for surface reconstruction.
Each point describes by three coordinates \f$ (x_i, y_i, z_i) \f$, where \f$ z_i \f$ is 
some physical value or something else value. Use task if you want to fit data exactly.

By loading \ref task object to surfit memory we write the follow functionals to the sequence:
\f[
P_{i,j} = \sum\limits_{p=1}^P ( u_{i,j} - z_p)^2 = \min,
\f]
where \f$ u_{i,j} \f$ - cell (i,j),
\f$ z_p \f$ are the values of points \f$ (x_i,y_i), \ i=\overline{1,P}\f$ belong to cell (i,j).

About functional sequence and surfit method of function reconstruction see \ref data.
For details about functions see (\ref func).

Here is simple example. Function was reconstructed from scattered data points using 
following parameters for \ref completer:
  

\ref completer_set 0 1\n
  
\image html points.jpg "scattered data points"

\image html surface_and_points.jpg "function reconstructed by scattered data points"

\par Example: 
\li \ref map_task.tcl

\sa
\li \ref surfit_tasks
\li \ref task
\li \ref tcl_task "Tcl commands"

*/
extern SURFIT_EXPORT task * surfit_task;

/*! \ingroup surfit_variables_collections
    \var std::vector<task *> * surfit_tasks
    collection of \ref task objects (scattered data-points)
*/
extern SURFIT_EXPORT std::vector<task *> * surfit_tasks;


class points;
class sub_points;
class grid;
typedef std::vector<sub_points *> sub_tasks;

extern SURFIT_EXPORT sub_tasks * sub_tsks;
extern SURFIT_EXPORT std::vector<void *> * a_sub_tsks;
extern SURFIT_EXPORT std::vector<task *> * tasks_garbage;

SURFIT_EXPORT
void prepare_scattered_points(const points * pnts, 
                              std::vector<sub_points *> *& proc_sub_tsks);

SURFIT_EXPORT
void free_scattered_points(std::vector<sub_points *> * proc_sub_tsks);

SURFIT_EXPORT
void bind_points_to_grid(grid *& old_grid, 
				         points * pnts,
				         std::vector<sub_points *> *& old_tasks,
				         grid *& grd);

/*! \class task_user
    \brief interface class for making equations from \ref task
*/
class SURFIT_EXPORT task_user : public user {
public:

	//! constructor
	task_user();

	//! destructor
	~task_user();

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

