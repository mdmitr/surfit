
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
#include "warea_show.h"

namespace surfit {

int warea_color_red;
int warea_color_green;
int warea_color_blue;
int warea_color_alpha;
int draw_warea;

};

#ifdef HAVE_GL_WORKS

#include "warea.h"
#include "colors.h"
#include "curv_show.h"
#include "warea_internal.h"
#include "variables_tcl.h"

namespace surfit {

void warea_color(const char * color_name) {
	set_colors(color_name, 
		   warea_color_red, 
		   warea_color_green, 
		   warea_color_blue, 
		   warea_color_alpha);
};

void warea_show(const char * filename, const char * wareaname) {
	
	if (draw_warea == 0)
		return;

	warea * crv = NULL;
	
	if (filename)
		crv = _warea_load(filename, wareaname, 0);
	else
		crv = _get_surfit_warea();

	if (crv) {
		if (crv->value == undef_value)
		_curv_show(crv, "warea", filename, crv->value,
		           warea_color_red,
			   warea_color_green,
			   warea_color_blue,
			   warea_color_alpha);
	}
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif



