
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

#ifndef __surfit_curv_user_included__
#define __surfit_curv_user_included__

#include <vector>

namespace surfit {

class curv;
class task;
class grid;

/*! \ingroup surfit_data_variables
    \var surfit_curv
    just curve
    \sa 
    \li \ref curv
    \li \ref tcl_curv "Tcl commands"
*/
extern SURFIT_EXPORT curv * surfit_curv;

/*! \ingroup surfit_variables_collections
    \var std::vector<curv *> * surfit_curvs;
    collection of \ref curv objects
*/
extern SURFIT_EXPORT std::vector<curv *> * surfit_curvs;

SURFIT_EXPORT
task * discretize_curv(curv * crv, grid * grd, REAL value, const char * task_name);


}; // namespace surfit;

#endif

