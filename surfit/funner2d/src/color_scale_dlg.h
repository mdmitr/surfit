
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

#ifndef __color_scale_dlg_included__
#define __color_scale_dlg_included__

#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class Fl_Button;
class Fl_Float_Input;
struct Tcl_Interp;
class funner2d_wind;

#define DEFAULT_COLORS 89, 138, 237, 227, 46, 32

class color_scale {
public:
	color_scale(double from, double to, double step,
		    int r_from, int g_from, int b_from,
		    int r_to, int g_to, int b_to);

	~color_scale();

	void set(double from, double to, double step,
		 int r_from, int g_from, int b_from,
		 int r_to, int g_to, int b_to);

	void get_value(double value, int & r, int & g, int & b) const;
	int size() const;
	bool get_color(int pos, int & r, int & g, int &b) const;
	void set_color_from(int r, int g, int b);
	void set_color_to(int r, int g, int b);
	void set_min(double min_val);
	void set_max(double max_val);
	void set_step(double step_val);

	bool get_params(double & from, double & to, double & step,
		        int & r_from, int & g_from, int & b_from,
			int & r_to, int & g_to, int & b_to);

private:

	std::vector<int>  * r_values;
	std::vector<int>  * g_values;
	std::vector<int>  * b_values;
	std::vector<double> * values;

};


class color_scale_dlg : public Fl_Window {
	virtual void draw();
public:
	color_scale_dlg(color_scale * ics, Tcl_Interp * iinterp, funner2d_wind * iparent);

	void set_color_from(int r, int g, int b);
	void set_color_to(int r, int g, int b);
	void set_min(double min_val);
	void set_max(double max_val);
	void set_step(double step_val);
	void refresh();

	int result;
	color_scale * cs;
	Tcl_Interp * interp;
	funner2d_wind * parent;

private:

	Fl_Float_Input * inp_min;
	Fl_Float_Input * inp_max;
	Fl_Float_Input * inp_step;
	
	Fl_Button * btn_ok;
	Fl_Button * btn_cancel;

	Fl_Button * color_from;
	Fl_Button * color_to;

};

#endif

