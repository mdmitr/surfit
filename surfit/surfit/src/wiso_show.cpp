
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
#include "wiso_show.h"

namespace surfit {

int wiso_color_red;
int wiso_color_green;
int wiso_color_blue;
int wiso_color_alpha;
int draw_wiso;

};

#ifdef HAVE_GL_WORKS

#include "wiso.h"
#include "colors.h"
#include "curv_show.h"
#include "wiso_internal.h"

namespace surfit {

void wiso_color(const char * color_name) {
	set_colors(color_name, 
		   wiso_color_red, 
		   wiso_color_green, 
		   wiso_color_blue, 
		   wiso_color_alpha);
};

void wiso_show(const char * filename, const char * wisoname) {
	
	if (draw_wiso == 0)
		return;

	wiso * crv = NULL;
	
	if (filename)
		crv = surfit::_wiso_load(filename, wisoname, 0);
	else 
		crv = surfit::_get_surfit_wiso();

	if (crv)
		_curv_show(crv, "wiso", filename, crv->value,
		           wiso_color_red,
			   wiso_color_green,
			   wiso_color_blue,
			   wiso_color_alpha);
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif

