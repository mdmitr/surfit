
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

#ifndef __flow_ptask_included__
#define __flow_ptask_included__

#include "task.h"

namespace surfit {

/*!
  \class ptask
  \brief scattered "production" data points for \ref func calculation

  This class describes the set of scattered so-called "production" data points used for 
  surface reconstruction. Each point describes by three coordinates \f$ (x_i, y_i, z_i) \f$.

  By loading ptask object to surfit memory we modify \ref completer functional:
  \f[
	A_{i,j} - \sum\limits_{p=1}^P z_p = \min,
  \f]
  where \f$A_i,j=0\f$ - \ref completer functional, \f$ \sum\limits_{p=1}^P z_p \f$ - is sum of values
  of points from ptask belong to cell (i,j)

  About functional sequence and surfit method of function reconstruction see \ref data.
  For details about functions see (\ref func).

  For example of \ref ptask usage see \ref map_debit.tcl, \ref map_press_debit.tcl
  
*/
class FLOW_EXPORT ptask : public task {
public:
	//! constructor
	ptask();
	//! another constructor
	ptask(REAL *& X_begin, REAL * X_end, 
              REAL *& Y_begin, REAL * Y_end, 
              REAL *& Z_begin, REAL * Z_end,
              const char * ptaskname = NULL);

	//! another constructor
	ptask(task * tsk);

};

}; // namespace surfit;

#endif

