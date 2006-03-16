
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

namespace surfit {

	extern SURFIT_EXPORT int cpu;

	extern SURFIT_EXPORT int stop_execution;

	/*! \ingroup surfit_variables
	    \var undef_value
	    \brief value to interprete as undefined
	*/
	extern SURFIT_EXPORT REAL undef_value;

	/*! \ingroup surfit_variables
	    \var tol
	    \brief use this variable to manage tolerance of iterative linear 
	    system solver algorithm. If this value is too big, iterative algorithm 
	    will make low number of iterations. It leads to rought result.
	*/
	extern SURFIT_EXPORT float tol;

	/*! \ingroup surfit_variables
	    \var sor_omega
	    \brief parameter for SOR method
	*/
	extern SURFIT_EXPORT REAL sor_omega;

	/*! \ingroup surfit_variables
	    \var ssor_omega
	    \brief parameter for SSOR method
	*/
	extern SURFIT_EXPORT REAL ssor_omega;

	/*! \ingroup surfit_variables
	    \var write_mat
	    \brief if write_mat=1, then surfit dumps matrices to file surfit.mat
	*/
	extern SURFIT_EXPORT bool write_mat;

	#define SURFIT_MAT "surfit.mat"

	/*! \ingroup surfit_variables
	    \var map_name
	    \brief this name prints in solve procedure
	*/
	extern SURFIT_EXPORT char * map_name;

	/*! \ingroup surfit_variables
	    \var reproject_faults
	    \brief enables/disables reprojecting with faults
	*/
	extern SURFIT_EXPORT int reproject_faults;

	/*! \ingroup surfit_variables
	    \var reproject_undef_areas
	    \brief enables/disables reprojecting with \ref d_area "areas" with undefined vale
	*/
	extern SURFIT_EXPORT int reproject_undef_areas;

	/*! \ingroup surfit_variables
	    \var process_isolated_areas
	    \brief enables/disables processing of areas, isolated by faults and areas with undefined value
	*/
	extern SURFIT_EXPORT int process_isolated_areas;

	extern SURFIT_EXPORT int penalty_max_iter;
	extern SURFIT_EXPORT REAL penalty_weight;
	extern SURFIT_EXPORT REAL penalty_weight_mult;

	extern SSTUFF_EXPORT int datafile_mode;

}; // namespace surfit

#endif

