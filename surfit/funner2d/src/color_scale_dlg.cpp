
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

#include "color_scale_dlg.h"
#include "funner2d_mainwnd.h"

#include <math.h>
#include <float.h>
#include <algorithm>

#include <tcl.h>

#include <FL/Fl_Button.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Color_Chooser.H>

#ifndef MIN
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#endif

double stepFunc(double StartX, double EndX, int amount) {
	if (StartX >= EndX) return 0.;
	double step = (EndX - StartX)/(double)amount;

	int n = 0;
	double a = log(step)/log(10.);
	if( a >= 0. ) n = (int)a;
	else n = (int)a - 1;

	double n10 = 1.;
	int i;
	for( i = 0; i < abs(n); i++ ) n10 = n10*10.;

	if( n < 0 ) n10 = 1./n10;

	for( i = 1; i <= 8; i++ )
	{
		double step1 = i*n10,
			   step2 = (i+1)*n10;
		if( !i ) if( step < step1 ) return step1;
		if( i == 9 - 2 ) if( step > step2 ) return step2;
		
		if( step >= step1 && step < step2 )
		{
			if( step - step1 <= step2 - step ) return step1;
			else
				return step2;
		}
	}

	return FLT_MAX;
};

void cb_color_from(Fl_Widget * w, void * p);
void cb_color_to(Fl_Widget * w, void * p);
void cb_ok(Fl_Widget * w, void * p);
void cb_cancel(Fl_Widget * w, void * p);
void cb_min(Fl_Widget * w, void * p);
void cb_max(Fl_Widget * w, void * p);
void cb_step(Fl_Widget * w, void * p);

color_scale_dlg::color_scale_dlg(color_scale * ics, Tcl_Interp * iinterp, funner2d_wind * iparent) 
: Fl_Window(200,100,"Color Scale") 
{
	cs = ics;
	interp = iinterp;
	parent = iparent;
	new Fl_Box(0,0,w()/3,20,"Min");
	new Fl_Box(w()/3,0,w()/3,20,"Max");
	new Fl_Box(w()/3*2,0,w()/3,20,"Step");

	inp_min = new Fl_Float_Input(0,20,w()/3,20);
	inp_min->callback(cb_min,this);
	
	inp_max = new Fl_Float_Input(w()/3,20,w()/3,20);
	inp_max->callback(cb_max,this);

	inp_step = new Fl_Float_Input(w()/3*2,20,w()/3,20);
	inp_step->callback(cb_step,this);

	color_from = new Fl_Button(1,40,10,10);
	color_from->callback(cb_color_from, this);
	color_to = new Fl_Button(w()-13,40,10,10);
	color_to->callback(cb_color_to, this);

	btn_cancel = new Fl_Button(0,h()-20,w()/2,20,"Cancel");
	btn_cancel->callback(cb_cancel,this);
	btn_ok = new Fl_Button(w()/2,h()-20,w()/2,20,"Ok");
	btn_ok->callback(cb_ok,this);
	btn_ok->take_focus();
	//set_modal();
	result = 0;

	refresh();
};

void color_scale_dlg::refresh() {
	double from, to, step;
	int r1,g1,b1,r2,g2,b2;
	cs->get_params(from, to, step, r1, g1, b1, r2, g2, b2);

	int amount = (int)((to-from)/step);
	step = stepFunc(from, to, amount);
	from = ((int)(from/step))*step;
	to = ((int)(to/step))*step;

	char str[128];
	sprintf(str,"%.2lf",from);
	inp_min->value(str);

	sprintf(str,"%.2lf",to);
	inp_max->value(str);

	sprintf(str,"%.2lf",step);
	inp_step->value(str);

};

void color_scale_dlg::draw() {
	Fl_Window::draw();
	
	fl_color(FL_BACKGROUND2_COLOR);
    
	fl_rectf(0,50,w(),30);

	int total = w();
	int cs_size = cs->size();

	double draw_step = double(total)/(double)cs_size;
	int i;
	int r,g,b;
	int pos = 0;
	int shift;
	double kk = 0;
	for (i = 0; i < cs_size; i++) {
		if ( cs->get_color(i, r, g, b) ) {
			Fl_Color color = fl_rgb_color(r, g, b);
			fl_color(color);
			shift = (int)floor(draw_step);
			kk += draw_step-floor(draw_step);
			if (kk >= 1) {
				shift += 1;
				kk -= 1;
			}
			fl_rectf(pos,50,shift,30);
			pos += shift;
		}
	}
};

void color_scale_dlg::set_color_from(int r, int g, int b) {
	cs->set_color_from(r,g,b);
	redraw();
};

void color_scale_dlg::set_color_to(int r, int g, int b) {
	cs->set_color_to(r,g,b);
	redraw();
};

void color_scale_dlg::set_min(double min_val) {
	cs->set_min(min_val);
	redraw();
};

void color_scale_dlg::set_max(double max_val) {
	cs->set_max(max_val);
	redraw();
};

void color_scale_dlg::set_step(double step_val) {
	cs->set_step(step_val);
	redraw();
};

void cb_color_from(Fl_Widget * w, void * p) {
	color_scale_dlg * dlg = (color_scale_dlg *)p;
	uchar r, g, b;
	int qq = fl_color_chooser("", r, g, b);
	if (qq) 
		dlg->set_color_from(r, g, b);
};

void cb_color_to(Fl_Widget * w, void * p) {
	color_scale_dlg * dlg = (color_scale_dlg *)p;
	uchar r, g, b;
	int qq = fl_color_chooser("", r, g, b);
	if (qq) 
		dlg->set_color_to(r, g, b);
};

void cb_ok(Fl_Widget * w, void * p) {
	color_scale_dlg * dlg = (color_scale_dlg *)p;

	double from, to, step;
	int r1, g1, b1;
	int r2, g2, b2;
	dlg->cs->get_params(from, to, step, r1, g1, b1, r2, g2, b2);

	char cmd[512];
	sprintf(cmd,"set_color_scale %lf %lf %lf %d %d %d %d %d %d",from, to, step, r1, g1, b1, r2, g2, b2);
	Tcl_Eval(dlg->interp, cmd);
	const char * res = Tcl_GetStringResult(dlg->interp);

	dlg->parent->redraw_view();

	dlg->result = 0;
	dlg->hide();
}

void cb_cancel(Fl_Widget * w, void * p) {
	color_scale_dlg * dlg = (color_scale_dlg *)p;
	dlg->result = 1;
	dlg->hide();
}

void cb_min(Fl_Widget * w, void * p) {
	color_scale_dlg * dlg = (color_scale_dlg *)p;
	Fl_Float_Input * f = (Fl_Float_Input *)w;
	dlg->set_min(atof(f->value()));
}

void cb_max(Fl_Widget * w, void * p) {
	color_scale_dlg * dlg = (color_scale_dlg *)p;
	Fl_Float_Input * f = (Fl_Float_Input *)w;
	dlg->set_max(atof(f->value()));
}

void cb_step(Fl_Widget * w, void * p) {
	color_scale_dlg * dlg = (color_scale_dlg *)p;
	Fl_Float_Input * f = (Fl_Float_Input *)w;
	dlg->set_step(atof(f->value()));
}

int check_color(int color) {
	color = MIN(255, color);
	color = MAX(0, color);
	return color;
}

color_scale::color_scale(double from, double to, double step,
                         int r_from, int g_from, int b_from,
                         int r_to, int g_to, int b_to) 
{
	r_values = NULL;
	g_values = NULL;
	b_values = NULL;
	values = NULL;
	set(from, to, step, 
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);
};

color_scale::~color_scale() 
{
	delete r_values;
	delete g_values;
	delete b_values;
	delete values;
};

void color_scale::set(double from, double to, double step,
                      int r_from, int g_from, int b_from,
                      int r_to, int g_to, int b_to)
{
	delete r_values;
	delete g_values;
	delete b_values;
	delete values;
	r_values = NULL;
	g_values = NULL;
	b_values = NULL;
	values = NULL;

	int size = (int) ( (to-from)/step + 1 );
	if (size <= 0)
		return;
	r_values = new std::vector<int>(size+1);
	g_values = new std::vector<int>(size+1);
	b_values = new std::vector<int>(size+1);
	values   = new std::vector<double>(size);
	int i;
	double r_step = (r_to-r_from)/double(size);
	double g_step = (g_to-g_from)/double(size);
	double b_step = (b_to-b_from)/double(size);
	int r_val, g_val, b_val;
	for (i = 0; i < size; i++) {
		r_val = check_color( int(r_from + i*r_step) );
		g_val = check_color( int(g_from + i*g_step) );
		b_val = check_color( int(b_from + i*b_step) );
		(*values)[i] = from + i*step;
		(*r_values)[i] = r_val;
		(*g_values)[i] = g_val;
		(*b_values)[i] = b_val;
	};
	r_val = check_color( int(r_from + i*r_step) );
	g_val = check_color( int(g_from + i*g_step) );
	b_val = check_color( int(b_from + i*b_step) );
	(*r_values)[i] = r_val;
	(*g_values)[i] = g_val;
	(*b_values)[i] = b_val;

}

void color_scale::get_value(double value, int & r, int & g, int & b) const
{
	if (!values)
		return;
	int size = values->size();
	if (size == 0)
		return;
	
	std::vector<double>::const_iterator it = std::lower_bound(values->begin(), values->end(), value);
	
	if (it == values->end()) {
		r = (*r_values)[size];
		g = (*g_values)[size];
		b = (*b_values)[size];
	} else {
		int pos = it-values->begin();
		r = (*r_values)[pos];
		g = (*g_values)[pos];
		b = (*b_values)[pos];
	}
	return;
	
};

int color_scale::size() const {
	if (!r_values)
		return 0;

	return r_values->size();
};

bool color_scale::get_color(int pos, int & r, int & g, int &b) const {
	if (!r_values)
		return false;

	if ((pos < 0) || ( (unsigned int)pos > r_values->size()))
		return false;

	r = (*r_values)[pos];
	g = (*g_values)[pos];
	b = (*b_values)[pos];
	return true;
};

bool color_scale::get_params(double & from, double & to, double & step,
                             int & r_from, int & g_from, int & b_from,
                             int & r_to, int & g_to, int & b_to) 
{
	if (!values)
		return false;

	if (values->size() == 0)
		return false;

	from = (*values)[0];
	to = (*values)[values->size()-1];
	step = (to-from)/(values->size()-1);

	int size = r_values->size();
	r_from = (*r_values)[0];
	g_from = (*g_values)[0];
	b_from = (*b_values)[0];

	r_to = (*r_values)[size-1];
	g_to = (*g_values)[size-1];
	b_to = (*b_values)[size-1];

	return true;
};

void color_scale::set_color_from(int r, int g, int b) {
	double from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	r_from = r;
	g_from = g;
	b_from = b;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

void color_scale::set_color_to(int r, int g, int b) {
	double from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	r_to = r;
	g_to = g;
	b_to = b;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

void color_scale::set_min(double min_val) {
	double from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	from = min_val;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

void color_scale::set_max(double max_val) {
	double from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	to = max_val;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

void color_scale::set_step(double step_val) {
	double from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	step = step_val;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

