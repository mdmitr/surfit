
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
#include "pcntr_show.h"

namespace surfit {

int pcntr_color_red;
int pcntr_color_green;
int pcntr_color_blue;
int pcntr_color_alpha;
int draw_pcntr;

};

#ifdef HAVE_GL_WORKS

#include "pcntr.h"
#include "colors.h"
#include "cntr_show.h"
#include "pcntr_internal.h"
#include "variables_tcl.h"

namespace surfit {

void pcntr_color(const char * color_name) {
	set_colors(color_name, 
		   pcntr_color_red, 
		   pcntr_color_green, 
		   pcntr_color_blue, 
		   pcntr_color_alpha);
};

void pcntr_show(const char * filename, const char * cntrname) {

	if (draw_pcntr == 0)
		return;
	
	pcntr * crv = NULL;
	
	if (filename)
		crv = _pcntr_load(filename, cntrname, 0);
	else 
		crv = _get_flow_pcntr();

	if (crv)
		_cntr_show(crv, "pcntr", filename,
		           cntr_color_red,
			   cntr_color_green,
			   cntr_color_blue,
			   cntr_color_alpha);
	
	if (filename)
		delete crv;
};

}; // namespace surfit;

#endif

