
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

#include "gl_view_funner2d.h"

#include <FL/Fl.H>
#include <FL/gl.h>

#include <tcl.h>

#ifndef MIN
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#endif

gl_view_funner2d::gl_view_funner2d(int x,int y,int w,int h, Tcl_Interp * iinterp, const char * label)
: gl_view(x,y,w,h,iinterp,label) 
{
};

void gl_view_funner2d::draw() {

	if (!valid()) {
		valid(1);
		char draw_cmd[100];
		sprintf(draw_cmd,"init %d %d",MAX(w(),h()),MAX(w(),h()));
		Tcl_EvalEx(interp, draw_cmd, -1, TCL_EVAL_DIRECT);
		const char * res = Tcl_GetStringResult(interp);
		sprintf(draw_cmd,"draw %d %d ",w(),h());
		Tcl_EvalEx(interp, draw_cmd, -1, TCL_EVAL_DIRECT);
	} else {
		char draw_cmd[100];
		//sprintf(draw_cmd,"draw_obj %d %d func2d mrf2d_show",w(),h());
		sprintf(draw_cmd,"draw %d %d ",w(),h());
		Tcl_EvalEx(interp, draw_cmd, -1, TCL_EVAL_DIRECT);
		const char * res = Tcl_GetStringResult(interp);
	}
	
};

