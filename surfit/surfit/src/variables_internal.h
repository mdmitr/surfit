
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

#ifndef __surfit__variables_internal__
#define __surfit__variables_internal__

#include <vector>
#include "real.h"

struct Tcl_Interp;

namespace surfit {

	/*! \ingroup internal
	    \var surfit_interp
	    \brief Tcl scripting language interpretator
	*/
	extern SURFIT_EXPORT Tcl_Interp * surfit_interp;
	
	/*! \ingroup internal
	    \var rw_mode
	    \brief ROFF file format (see \ref datafile for details)
	*/
	extern char rw_mode[7];

	SURFIT_EXPORT
	/*! \ingroup internal
	    \fn int get_rw_mode();
	    \brief returns current \ref rw_mode
	    \return 0 - binary, 1 - text, -1 - error
	*/
	int get_rw_mode();

	class color_scale;
	/*! \ingroup internal
	    \var surfit_color_scale
	    \brief color scale for functions
	*/
	extern SURFIT_EXPORT color_scale * surfit_color_scale;
	
	/*! \ingroup internal
	    \fn void surfit_init_all();
	    \brief inits all variables
	*/
	SURFIT_EXPORT
	void surfit_init_all();

	/*! \ingroup internal
	    \fn void surfit_init_variables(Tcl_Interp * interp);
	    \brief inits surfit variables 
	*/
	SURFIT_EXPORT
	void surfit_init_variables(Tcl_Interp * interp);

};

#endif

