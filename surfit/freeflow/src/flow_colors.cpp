
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
#include "flow_colors.h"
#include "colors.h"

#ifdef HAVE_GL_WORKS

#include "ptask_show.h"
#include "parea_show.h"
#include "piso_show.h"
#include "pcntr_show.h"

namespace surfit {

struct flow_gl_init{
	flow_gl_init() {
		ptask_color("magenta");
		draw_ptask = 1;
		parea_color("magenta");
		draw_parea = 1;
		piso_color("magenta");
		draw_piso = 1;
		pcntr_color("magenta");
		draw_pcntr = 1;
	}
};

flow_gl_init flow_gl_initializer;


}; // namespace surfit

#endif

