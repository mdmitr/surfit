
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
%{
#include "cmofs.h"
%}

namespace surfit {

void cmofs();
void clear_cmofs();

// solvers
int get_solvers_count();
const char * get_solver_long_name(int pos);
const char * get_solver_short_name(int pos);
const char * get_current_solver_short_name();
const char * get_current_solver_long_name();
void set_solver(const char * short_name);
void solvers_info();

}; // namespace surfit;

