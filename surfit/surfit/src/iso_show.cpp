
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
#include "iso_show.h"

namespace surfit {

int iso_color_red;
int iso_color_green;
int iso_color_blue;
int iso_color_alpha;
int draw_iso;

};

#ifdef HAVE_GL_WORKS

#include "iso.h"
#include "colors.h"
#include "curv_show.h"
#include "iso_internal.h"

namespace surfit {

void iso_color(const char * color_name) {
	set_colors(color_name, 
		   iso_color_red, 
		   iso_color_green, 
		   iso_color_blue, 
		   iso_color_alpha);
};

void iso_show(const char * filename, const char * isoname) {

	if (draw_iso == 0)
		return;
	
	iso * crv = NULL;
	
	if (filename)
		crv = surfit::_iso_load(filename, isoname, 0);
	else 
		crv = surfit::_get_surfit_iso();

	if (crv)
		_curv_show(crv, "iso", filename, crv->value,
		           iso_color_red,
			   iso_color_green,
			   iso_color_blue,
			   iso_color_alpha);
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif



