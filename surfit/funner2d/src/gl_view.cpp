
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

#include "gl_view.h"
#include <FL/Fl.H>
#include <FL/gl.h>
#include <stdlib.h>
#include <tcl.h>

gl_view::gl_view(int x,int y,int w,int h, Tcl_Interp * iinterp, const char * label)
: Fl_Gl_Window(x,y,w,h,label) {
	interp = iinterp;
	Tcl_Eval(interp, "bg_color gray");
	Tcl_Eval(interp, "set axis_labels 1");
	//Tcl_Eval(interp, "set light 1");
	Tcl_Eval(interp, "color black");
	size_range(100,100);
	select_area_mode = false;
};

int gl_view::handle(int event) {
	switch(event) {
	case FL_PUSH:
		{
			process_push_mouse();
		};
		break;
	case FL_DRAG:
		{
			process_drag_mouse();
		};
		break;
	case FL_MOUSEWHEEL:
		{
			process_wheel();
		};
		break;
	};
	return Fl_Gl_Window::handle(event);
};

void gl_view::process_wheel() {
	int dy = -Fl::event_dy();

	char buf[2048];
	const char * temp = NULL;

	double z_scale = 5.;
	temp = Tcl_GetVar(interp,"z_scale",0);
	if (temp)
		z_scale = atof(temp);

	z_scale += z_scale*dy/10. + dy/50.;
	if (z_scale < 0.0001) 
		z_scale = 0.0001;
	
	sprintf(buf,"%lf",z_scale);
	Tcl_SetVar(interp, "z_scale", buf, TCL_GLOBAL_ONLY);
	Fl_Widget::redraw();
};

void gl_view::process_push_mouse() {
	mouse_x = Fl::event_x();
	mouse_y = Fl::event_y();
};

void gl_view::process_drag_mouse() {
	
	char buf[2048];
	const char * temp = NULL;

	double dx = Fl::event_x() - mouse_x;
	double dy = Fl::event_y() - mouse_y;

	switch (Fl::event_button()) {
	case FL_LEFT_MOUSE :
		{
			if (Fl::event_state(FL_CAPS_LOCK)) 
			{
				double z_scale = 5.;
				temp = Tcl_GetVar(interp,"z_scale",0);
					if (temp)
						z_scale = atof(temp);
				
				z_scale += z_scale*dy/10. + dy/50.;
				if (z_scale < 0.0001) 
					z_scale = 0.0001;

				sprintf(buf,"%lf",z_scale);
				Tcl_SetVar(interp, "z_scale", buf, TCL_GLOBAL_ONLY);
				
			} else 
			{
				int pos_x = Fl::event_x();
				int pos_y = Fl::event_y();
				int ww = w();
				int hh = h();
				sprintf(cmd,"moving %d %d %d %d %d %d", mouse_x, mouse_y, pos_x, pos_y, ww, hh);
				Tcl_EvalEx(interp, cmd, -1, TCL_EVAL_DIRECT);
				Tcl_Obj *res = Tcl_GetObjResult(interp);
			}

			Fl_Widget::redraw();
		}
		break;
	case FL_MIDDLE_MOUSE :
		{
			double scale = 5.;
			temp = Tcl_GetVar(interp,"scale",0);
			if (temp) scale = atof(temp);

			scale -=  dy/100.*scale;
			sprintf(buf,"%lf",scale);
			Tcl_SetVar(interp, "scale", buf, TCL_GLOBAL_ONLY);
						
			Fl_Widget::redraw();
		}
		break;
	case FL_RIGHT_MOUSE :
		{
			if (Fl::event_state(FL_CAPS_LOCK)) {
				double scale = 5.;
				temp = Tcl_GetVar(interp,"scale",0);
				if (temp) scale = atof(temp);

				scale -=  dy/100.*scale;
				sprintf(buf,"%lf",scale);
				Tcl_SetVar(interp, "scale", buf, TCL_GLOBAL_ONLY);
			} else {
				double scale = 5.;
				temp = Tcl_GetVar(interp,"scale",0);
				if (temp) scale = atof(temp);

				dx *= 2.;
				dx /= scale;
				dy *= 2.;
				dy /= scale;
				
				double x_shift = 0;
				temp = Tcl_GetVar(interp,"x_shift",0);
				if (temp) x_shift = atof(temp);
				x_shift += dx*scale;
				sprintf(buf,"%lf",x_shift);
				Tcl_SetVar(interp, "x_shift", buf, TCL_GLOBAL_ONLY);

				double y_shift = 0;
				temp = Tcl_GetVar(interp,"y_shift",0);
				if (temp) y_shift = atof(temp);
				y_shift -= dy*scale;
				sprintf(buf,"%lf",y_shift);
				Tcl_SetVar(interp, "y_shift", buf, TCL_GLOBAL_ONLY);

			}
			
			Fl_Widget::redraw();
		}
		break;
	};
	mouse_x = Fl::event_x();
	mouse_y = Fl::event_y();

};


