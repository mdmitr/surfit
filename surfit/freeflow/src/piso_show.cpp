
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
#include "piso_show.h"

namespace surfit {

int piso_color_red;
int piso_color_green;
int piso_color_blue;
int piso_color_alpha;
int draw_piso;

};

#ifdef HAVE_GL_WORKS

#include "piso.h"
#include "colors.h"
#include "curv_show.h"
#include "piso_internal.h"
#include "variables_tcl.h"

namespace surfit {

void piso_color(const char * color_name) {
	set_colors(color_name, 
		   piso_color_red, 
		   piso_color_green, 
		   piso_color_blue, 
		   piso_color_alpha);
};

void piso_show(const char * filename, const char * pisoname) {
	
	if (draw_piso == 0)
		return;

	piso * crv = NULL;
	
	if (filename)
		crv = _piso_load(filename, pisoname, 0);
	else 
		crv = _get_flow_piso();

	if (crv)
		_curv_show(crv, "piso", filename, crv->value,
		           piso_color_red,
			   piso_color_green,
			   piso_color_blue,
			   piso_color_alpha);
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif

