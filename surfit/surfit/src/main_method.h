
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

#ifndef __surfit_main_method_included__
#define __surfit_main_method_included__

#include <vector>

namespace surfit {

extern SURFIT_EXPORT bool method_ok;

class user;

SURFIT_EXPORT 
void universal_solver(std::vector<user *> * users_holder);

SURFIT_EXPORT 
/*! \ingroup tcl
    \fn void solve();
    \brief executes solve procedure (gridding)
*/    
void solve();

};

#endif

