
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit__variables_tcl__
#define __surfit__variables_tcl__

#include "vec.h"

namespace surfit {

	extern SURFIT_EXPORT bool stop_execution;

	/*! \ingroup surfit_variables
	    value to interprete as undefined
	*/
	extern SURFIT_EXPORT REAL undef_value;

	/*! \ingroup surfit_variables
	    use this variable to manage tolerance of iterative linear 
	    system solver algorithm. If this value is too big, iterative algorithm 
	    will make low number of iterations. It leads to rought result.
	*/
	extern SURFIT_EXPORT float tol;

	/*! \ingroup surfit_variables
	    parameter for SOR method
	*/
	extern SURFIT_EXPORT REAL sor_omega;

	/*! \ingroup surfit_variables
	    parameter for SSOR method
	*/
	extern SURFIT_EXPORT REAL ssor_omega;

	/*! \ingroup surfit_variables
	    if write_mat=1, then surfit dumps matrices to file surfit.mat
	*/
	extern SURFIT_EXPORT bool write_mat;

	#define SURFIT_MAT "surfit.mat"

	/*! \ingroup surfit_variables
	    this name prints in solve procedure
	*/
	extern SURFIT_EXPORT char * map_name;

	/*! \ingroup surfit_variables
	    enables/disables reprojecting with faults
	*/
	extern SURFIT_EXPORT int reproject_faults;

	/*! \ingroup surfit_variables
	    enables/disables reprojecting with \ref d_area "areas" with undefined vale
	*/
	extern SURFIT_EXPORT int reproject_undef_areas;

	/*! \ingroup surfit_variables
	    enables/disables processing of areas, isolated by faults and areas with undefined value
	*/
	extern SURFIT_EXPORT int process_isolated_areas;

	/*! \ingroup surfit_variables
	    number of maximum iterations for \ref penalty "penalty algorithm"
	*/
	extern SURFIT_EXPORT size_t penalty_max_iter;

	/*! \ingroup surfit_variables
	    starting weight in \ref penalty "penalty algorithm"
	*/
	extern SURFIT_EXPORT REAL penalty_weight;

	/*! \ingroup surfit_variables
	    multiplication factor for \ref penalty_weight() "penalty_weight"
        */
	extern SURFIT_EXPORT REAL penalty_weight_mult;

}; // namespace surfit

#endif

