
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
#include "flt_show.h"

namespace surfit {

int flt_color_red;
int flt_color_green;
int flt_color_blue;
int flt_color_alpha;
int draw_flt;

};

#ifdef HAVE_GL_WORKS

#include "flt.h"
#include "colors.h"
#include "curv_show.h"
#include "flt_internal.h"

namespace surfit {

void flt_color(const char * color_name) {
	set_colors(color_name, 
		   flt_color_red, 
		   flt_color_green, 
		   flt_color_blue, 
		   flt_color_alpha);
};

void flt_show(REAL value, const char * filename, const char * fltname) {

	if (draw_flt == 0)
		return;
	
	flt * crv = NULL;
	
	if (filename)
		crv = _flt_load(filename, fltname, 0);
	else 
		crv = _get_surfit_flt();

	_curv_show(crv, "flt", filename, value,
                   flt_color_red,
                   flt_color_green,
                   flt_color_blue,
                   flt_color_alpha);
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif

