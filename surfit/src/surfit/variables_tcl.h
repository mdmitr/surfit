
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
	    \var undef_value
	    value to interprete as undefined
	*/
	extern SURFIT_EXPORT REAL undef_value;

	/*! \ingroup surfit_variables
	    \var tol
	    use this variable to manage tolerance of iterative linear 
	    system solver algorithm. If this value is too big, iterative algorithm 
	    will make low number of iterations. It leads to rought result.
	*/
	extern SURFIT_EXPORT float tol;

	/*! \ingroup surfit_variables
	    \var sor_omega
	    parameter for SOR method
	*/
	extern REAL sor_omega;

	/*! \ingroup surfit_variables
	    \var ssor_omega
	    parameter for SSOR method
	*/
	extern REAL ssor_omega;

	/*! \ingroup surfit_variables
	    \var write_mat
	    if write_mat=1, then surfit dumps matrices to file surfit.mat
	*/
	extern bool write_mat;

	#define SURFIT_MAT "surfit.mat"

	/*! \ingroup surfit_variables
	    \var map_name
	    this name prints in solve procedure
	*/
	extern char * map_name;

	/*! \ingroup surfit_variables
	    \var reproject_faults
	    enables/disables reprojecting with faults
	*/
	extern SURFIT_EXPORT int reproject_faults;

	/*! \ingroup surfit_variables
	    \var reproject_undef_areas
	    enables/disables reprojecting with \ref d_area "areas" with undefined vale
	*/
	extern SURFIT_EXPORT int reproject_undef_areas;

	/*! \ingroup surfit_variables
	    \var process_isolated_areas
	    enables/disables processing of areas, isolated by faults and areas with undefined value
	*/
	extern SURFIT_EXPORT int process_isolated_areas;

	extern size_t penalty_max_iter;
	extern REAL penalty_weight;
	extern REAL penalty_weight_mult;

	const char * datafile_mode();
	const char * datafile_new();
	const char * datafile_append();

}; // namespace surfit

#endif

