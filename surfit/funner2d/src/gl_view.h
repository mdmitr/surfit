
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

#ifndef __gl_view_included__
#define __gl_view_included__

#include <FL/Fl_Gl_Window.H>

struct Tcl_Interp;

class gl_view : public Fl_Gl_Window {
	virtual int handle(int event);
public:
	gl_view(int x,int y,int w,int h, Tcl_Interp * iinterp, const char * label);

	bool select_area_mode;
	
protected:
	Tcl_Interp * interp;

	char cmd[1024];

	void process_push_mouse();
	void process_drag_mouse();
	void process_wheel();

	int mouse_x, mouse_y;

};

#endif

