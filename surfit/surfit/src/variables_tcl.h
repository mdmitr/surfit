
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

#ifndef __surfit__variables_tcl__
#define __surfit__variables_tcl__

#include "real.h"

namespace surfit {

	SURFIT_EXPORT
	/*! \ingroup tcl
	    \fn void rw_mode_set(const char * new_mode)
	    \brief set the read-write mode
	    \param new_mode "text" or "binary"
	    \brief determines format of ROFF files (text of binary) (see \ref datafile for details)
	*/
	void rw_mode_set(const char * new_mode); 
	
	SURFIT_EXPORT 
	/*! \ingroup tcl
	    \fn const char * rw_mode_get();
	    \brief puts the read-write mode
	    \return active \ref rw_mode
            \brief prints ROFF files format (text or binary) (see \ref datafile for details)
	*/
	const char * rw_mode_get();
	
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
	    \var datafile_mode
	    \brief datafile mode ( 0 - always append file, 1 - rewrite file )
	*/
	extern SURFIT_EXPORT int datafile_mode;

	/*! \ingroup surfit_variables
	    \var priority
	    \brief all loaded data will have this value as priority
	*/
	extern SURFIT_EXPORT int priority;

	/*! \ingroup surfit_variables
	    \var solver_code
	    \brief identifies solver for system's of linear equations Ax=b. Avaliable are:

		0 - CG	(Conjugate gradient) - default \n
		1 - CG2	(Conjugate gradient	for A'Ax=A'b)\n
		2 - SIMPITER (Richardson iterations)\n
		3 - SIMPITER2 (Richardson iterations for A'Ax=A'b)\n
		4 - SOR (Successive OverRelaxation method, see \ref sor_omega)
		5 - SSOR (Symmetric Successive OverRelaxation method, see \ref ssor_omega)
	*/
	extern SURFIT_EXPORT int solver_code;

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

}; // namespace surfit

#endif

