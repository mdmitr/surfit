
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

#include "bula_view.h"
#include <math.h>

//#define BULA_W 1024
//#define BULA_H 768

#define BULA_W 800
#define BULA_H 600

class bula : public Fl_Window {

public:
	bula(const char * exec, int w, int h, const char * text, const char * script_name);
	~bula();

	virtual int handle(int);
	virtual void resize(int x, int y, int w, int h);
	
	bula_view *view;

private:

	const char * exec;

		
};

bula::bula(const char * iexec, int w, int h, const char * text,  const char * script_name) : Fl_Window(w,h,text) 
{
	exec = iexec;
	Fl_Window::size_range(1,1);
	view = new bula_view(exec,0,0,Fl_Window::w(),Fl_Window::h(),text,script_name);
	view->end();
	resizable(view);
};

bula::~bula() 
{
	delete view;
};

void bula::resize(int x, int y, int w, int h) 
{
	Fl_Window::resize(x,y,w,h);
};

int bula::handle(int event) 
{
	switch(event) {
	case FL_PUSH:
		{
			if (!view->shown_cmd()) {
				view->process_push_mouse();
			};
		};
		break;
	case FL_MOUSEWHEEL:
		{
			if (!view->shown_cmd()) {
				view->process_wheel();
			};
		};
		break;
	case FL_DRAG:
		{
			if (!view->shown_cmd()) {
				view->process_drag_mouse();
			};
		};
		break;
	case FL_KEYBOARD:
		{
			if (Fl::event_key() == FL_Escape) {
				if (view->shown_cmd()) 
					view->show_cmd(false);
				else 
					view->show_cmd(true);
				view->redraw();
				return 1;
			}
			
			if (view->shown_cmd()) {
				if (!view->process_key(Fl::event_text())) 
					return Fl_Window::handle(event);
			} else {
				if (!view->process_cmd_key(Fl::event_text())) 
					return Fl_Window::handle(event);
			}

			return Fl_Window::handle(event);
		};
		break;
	};
	return Fl_Window::handle(event);
};

int main(int argc, char **argv) {

    bula * window;

    const char bula_startup[] = "bula.tcl";
	if (argc > 1)
	    window = new bula(argv[0], BULA_W, BULA_H, "Meine BULA", argv[1]);
    else
        window = new bula(argv[0], BULA_W, BULA_H, "Meine BULA", bula_startup);

	window->show(1, argv);
	int res = Fl::run();
	delete window;
	return res;

}

