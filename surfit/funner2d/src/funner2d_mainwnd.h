
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

#ifndef __funner2d_mainwfnd_included__
#define __funner2d_mainwnd_included__

#include "defines.h"
#include "real.h"

#include <FL/Fl_Window.H>

#include <tcl.h>

#include <vector>

class Fl_Scroll;
class Fl_Pack;
class Fl_Button;
class Fl_Light_Button;
class Fl_Round_Button;
class draw_hist_wnd;
class Fl_Slider;
class Fl_Multiline_Output;
class Fl_Float_Input;
class Fl_Box;
class gl_view_funner2d;
class color_scale;
class color_scale_dlg;

void cb_file_open(Fl_Widget * w, void * p);
void cb_file_save(Fl_Widget * w, void * p);
void cb_decomp(Fl_Widget * w, void * p);
void cb_recons(Fl_Widget * w, void * p);
void cb_exit(Fl_Widget * w, void * p);
void cb_details_btn(Fl_Widget * w, void * p);
void cb_view(Fl_Widget * w, void * p);
void cb_fix_view(Fl_Widget * w, void * p);
void cb_auto_decomp(Fl_Widget * w, void * p);

void cb_show_total(Fl_Widget * w, void * p);
void cb_select_area(Fl_Widget * w, void * p);

void cb_color(Fl_Widget * w, void * p);
void cb_light(Fl_Widget * w, void * p);
void cb_smooth(Fl_Widget * w, void * p);
void cb_showiso(Fl_Widget * w, void * p);

void cb_task(Fl_Widget * w, void * p);
void cb_wtask(Fl_Widget * w, void * p);
void cb_ptask(Fl_Widget * w, void * p);
void cb_func(Fl_Widget * w, void * p);
void cb_wfunc(Fl_Widget * w, void * p);
void cb_trend(Fl_Widget * w, void * p);
void cb_iso(Fl_Widget * w, void * p);
void cb_piso(Fl_Widget * w, void * p);
void cb_wiso(Fl_Widget * w, void * p);
void cb_cntr(Fl_Widget * w, void * p);
void cb_wcntr(Fl_Widget * w, void * p);
void cb_pcntr(Fl_Widget * w, void * p);
void cb_area(Fl_Widget * w, void * p);
void cb_warea(Fl_Widget * w, void * p);
void cb_parea(Fl_Widget * w, void * p);
void cb_flt(Fl_Widget * w, void * p);
void cb_curv(Fl_Widget * w, void * p);
void cb_grid(Fl_Widget * w, void * p);
void cb_defarea(Fl_Widget * w, void * p);

class funner2d_wind : public Fl_Window {
public:
	funner2d_wind(const char * iexec, const char * filename = NULL);
	~funner2d_wind();

	void enable_disable();
	void show_details_btns();
	void show_view(int show);
	void redraw_view();
	void fix_view(int fix);
	void auto_decomp();
	
	void show_total();
	void select_area();
	
	void set_color();
	void save_to_file();
	void set_light();
	void set_smooth();
	void set_showiso();
	void file_open(const char * filename);

	void task(int status);
	void wtask(int status);
	void ptask(int status);
	void func(int status);
	void wfunc(int status);
	void trend(int status);
	void iso(int status);
	void piso(int status);
	void wiso(int status);
	void cntr(int status);
	void wcntr(int status);
	void pcntr(int status);
	void area(int status);
	void warea(int status);
	void parea(int status);
	void flt(int status);
	void curv(int status);
	void grid(int status);
	void defarea(int status);
	void set_btn_values();

	
	Tcl_Interp * get_interp();

private:

	char * exec;
	char cmd[512];
	char text[1024];

	void init_tcl();
	bool prefabula;
	Tcl_Interp * interp;
	Tcl_Channel channel;

	void set_hist_params(REAL * v, int size);
	double hist_min_val;
	double hist_max_val;
	double hist_val_step;
	std::vector<int> values;
	std::vector<double> marks;
	
	// controls
	void init_controls();
	void set_callbacks();
	//void update_out_text();
	void delete_all_details_btns();

	bool select_area_mode;
			
	int show_func_number;
	bool view_fixed;
	int details_type;

	Fl_Scroll * details_scroll;
	Fl_Pack   * details_pack;

	Fl_Button * btn_file_open;
	Fl_Button * btn_file_save;
	Fl_Light_Button * btn_view;
	Fl_Light_Button * btn_fix_view;
	Fl_Light_Button * btn_showiso;
	Fl_Button * btn_color;
	Fl_Light_Button * btn_light;
	Fl_Light_Button * btn_smooth;
	Fl_Button * btn_decomp;
	Fl_Button * btn_recons;
	Fl_Button * btn_auto_decomp;
	Fl_Float_Input * btn_eps;

	Fl_Light_Button * btn_task;
	Fl_Light_Button * btn_ptask;
	Fl_Light_Button * btn_wtask;

	Fl_Light_Button * btn_func;
	Fl_Light_Button * btn_wfunc;
	Fl_Light_Button * btn_trend;

	Fl_Light_Button * btn_iso;
	Fl_Light_Button * btn_wiso;
	Fl_Light_Button * btn_piso;

	Fl_Light_Button * btn_cntr;
	Fl_Light_Button * btn_pcntr;
	Fl_Light_Button * btn_wcntr;

	Fl_Light_Button * btn_area;
	Fl_Light_Button * btn_warea;
	Fl_Light_Button * btn_parea;

	Fl_Light_Button * btn_flt;
	Fl_Light_Button * btn_curv;

	Fl_Light_Button * btn_grid;
	Fl_Light_Button * btn_defarea;
	
	Fl_Box          * txt_show;
	Fl_Light_Button * btn_show_total;
	Fl_Button       * btn_select_area;
			

	Fl_Button * btn_exit;

	gl_view_funner2d * view;

	color_scale * cs;
	color_scale_dlg * dlg;

};

#endif


