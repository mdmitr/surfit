
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

#include "funner2d_mainwnd.h"
#include "funner_channel.h"
#include "details_btn.h"

#include <tcl.h>

#include <FL/Fl_File_Chooser.H>

void cb_file_open(Fl_Widget * w, void * p) {

	funner2d_wind * fw = (funner2d_wind *)p;
	Tcl_Interp * interp = fw->get_interp();
	if (!interp)
		return;
	char * filename = fl_file_chooser("Open func from file", "*.{dat,grd}",NULL);

	if (filename) 
		fw->file_open(filename);
};

void cb_file_save(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->save_to_file();
};

void cb_decomp(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Tcl_Interp * interp = fw->get_interp();
	if (!interp)
		return;

	Tcl_Eval(interp,"func_decomp");

	fw->show_details_btns();
	fw->enable_disable();
	fw->redraw_view();
};

void cb_recons(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Tcl_Interp * interp = fw->get_interp();
	if (!interp)
		return;

	Tcl_Eval(interp,"func_recons");

	fw->show_details_btns();
	fw->enable_disable();
	fw->redraw_view();
};

void cb_exit(Fl_Widget * w, void * p) {
	Tcl_Interp * interp = (Tcl_Interp *)p;
	if (interp)
		Tcl_Eval(interp,"exit");
};

void cb_details_btn(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	details_btn * btn = (details_btn *)w;
	//fw->set_showfunc(btn->get_detail_number());
	fw->enable_disable();
};

void cb_view(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->show_view(lb->value());
};

void cb_fix_view(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->fix_view(lb->value());
};

void cb_auto_decomp(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->auto_decomp();
};

void cb_color(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->set_color();
};

void cb_light(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->set_light();
};

void cb_smooth(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->set_smooth();
};

void cb_showiso(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->set_showiso();
};

void cb_show_total(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->show_total();
};

void cb_select_area(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	fw->select_area();
};


//
//
//


void cb_task(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->task(lb->value());
};
void cb_wtask(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->wtask(lb->value());
};
void cb_ptask(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->ptask(lb->value());
};
void cb_func(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->func(lb->value());
};
void cb_wfunc(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->wfunc(lb->value());
};
void cb_trend(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->trend(lb->value());
};
void cb_iso(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->iso(lb->value());
};
void cb_piso(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->piso(lb->value());
};
void cb_wiso(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->wiso(lb->value());
};
void cb_cntr(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->cntr(lb->value());
};
void cb_wcntr(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->wcntr(lb->value());
};
void cb_pcntr(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->pcntr(lb->value());
};
void cb_area(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->area(lb->value());
};
void cb_warea(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->warea(lb->value());
};
void cb_parea(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->parea(lb->value());
};
void cb_flt(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->flt(lb->value());
};
void cb_curv(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->curv(lb->value());
};
void cb_grid(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->grid(lb->value());
};
void cb_defarea(Fl_Widget * w, void * p) {
	funner2d_wind * fw = (funner2d_wind *)p;
	Fl_Light_Button * lb = (Fl_Light_Button *)w;
	fw->defarea(lb->value());
};

