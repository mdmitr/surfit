
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

%{
#include "lcm_simple_tcl.h"
#include "flow_func_tcl.h"
%}

namespace surfit {

void lcm_simple_set(REAL permeability = 1, REAL viscosity = 1, REAL multiplier = 1);
bool lcm_simple_unload();
bool lcm_simple_read(const char * filename, const char * lcm_simple_name);
bool lcm_simple_load(const char * filename, const char * lcm_simple_name = NULL);
bool lcm_simple_write(const char * filename);
bool lcm_simple_save(const char * filename, const char * lcm_simple_name = NULL);
bool lcm_simple_check();
int lcm_simple_info();

REAL func_debit(REAL x, REAL y);
REAL func_debit_rect(REAL x1, REAL y1, REAL x2, REAL y2);

}; // namespace surfit;