
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

#include "flow_ie.h"
#include "parea_show.h"

namespace surfit {

int parea_color_red;
int parea_color_green;
int parea_color_blue;
int parea_color_alpha;
int draw_parea;

};

#ifdef HAVE_GL_WORKS

#include "parea.h"
#include "colors.h"
#include "curv_show.h"
#include "parea_internal.h"
#include "variables_tcl.h"

namespace surfit {

void parea_color(const char * color_name) {
	set_colors(color_name, 
		   parea_color_red, 
		   parea_color_green, 
		   parea_color_blue, 
		   parea_color_alpha);
};

void parea_show(const char * filename, const char * pareaname) {
	
	if (draw_parea == 0)
		return;

	parea * crv = NULL;
	
	if (filename)
		crv = _parea_load(filename, pareaname, 0);
	else
		crv = _get_flow_parea();

	if (crv) {
		if (crv->value == undef_value)
		_curv_show(crv, "parea", filename, crv->value,
		           parea_color_red,
			   parea_color_green,
			   parea_color_blue,
			   parea_color_alpha);
	}
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif

