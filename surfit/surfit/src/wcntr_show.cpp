
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

#include "ie.h"
#include "wcntr_show.h"

namespace surfit {

int wcntr_color_red;
int wcntr_color_green;
int wcntr_color_blue;
int wcntr_color_alpha;
int draw_wcntr;

};

#ifdef HAVE_GL_WORKS

#include "wcntr.h"
#include "colors.h"
#include "cntr_show.h"
#include "wcntr_internal.h"
#include "variables_tcl.h"

namespace surfit {

void wcntr_color(const char * color_name) {
	set_colors(color_name, 
		   wcntr_color_red, 
		   wcntr_color_green, 
		   wcntr_color_blue, 
		   wcntr_color_alpha);
};

void wcntr_show(const char * filename, const char * cntrname) {

	if (draw_wcntr == 0)
		return;
	
	wcntr * crv = NULL;
	
	if (filename)
		crv = _wcntr_load(filename, cntrname, 0);
	else 
		crv = _get_surfit_wcntr();

	if (crv)
		_cntr_show(crv, "wcntr", filename,
		           wcntr_color_red,
			   wcntr_color_green,
			   wcntr_color_blue,
			   wcntr_color_alpha);
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif

