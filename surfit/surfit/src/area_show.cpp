
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
#include "area_show.h"

namespace surfit {

int area_color_red;
int area_color_green;
int area_color_blue;
int area_color_alpha;
int draw_area;

};

#ifdef HAVE_GL_WORKS

#include "area.h"
#include "colors.h"
#include "curv_show.h"
#include "area_internal.h"
#include "variables_tcl.h"

namespace surfit {

void area_color(const char * color_name) {
	set_colors(color_name, 
		   area_color_red, 
		   area_color_green, 
		   area_color_blue, 
		   area_color_alpha);
};

void area_show(const char * filename, const char * areaname) {

	if (draw_area == 0)
		return;
	
	area * crv = NULL;
	
	if (filename)
		crv = _area_load(filename, areaname, 0);
	else
		crv = _get_surfit_area();

	if (crv) {
		if (crv->value == undef_value)
		_curv_show(crv, "area", filename, crv->value,
		           area_color_red,
			   area_color_green,
			   area_color_blue,
			   area_color_alpha);
	}
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif

