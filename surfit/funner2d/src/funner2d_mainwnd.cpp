
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
#include "color_scale_dlg.h"

#include <math.h>

#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Text_Display.H>

#include <algorithm>

funner2d_wind::funner2d_wind(const char * iexec, const char * filename) 
: Fl_Window(206,570) 
{
	exec = strdup(iexec);
	init_tcl();
	init_controls();
	set_callbacks();
	enable_disable();
	show_func_number = -1;
	values.resize(HIST_BARS);
	marks.resize(HIST_BARS);
	view = NULL;
	view_fixed = false;
	select_area_mode = false;
	cs = new color_scale(0, 1, 0.5,	DEFAULT_COLORS);
	dlg = new color_scale_dlg(cs, interp, this);
	if (filename)
		file_open(filename);
};

funner2d_wind::~funner2d_wind() {
	free(exec);
	Tcl_DeleteInterp(interp);
	delete_all_details_btns();
	delete cs;
	delete dlg;
};

Tcl_Interp * funner2d_wind::get_interp() {
	return interp;
};

void funner2d_wind::init_controls() {
	details_scroll = new Fl_Scroll(0,0,w(),180);
	{
		details_pack = new Fl_Pack(0, 0, w()-16, details_scroll->h());
		details_pack->box(FL_DOWN_FRAME);
		details_pack->end();
		resizable(details_pack);
	}
	details_scroll->end();
	int hor;
	btn_file_open = new Fl_Button(0,details_scroll->h(),101,20,"Open File...");
	btn_file_open->shortcut('o');
	hor = details_scroll->h();
	btn_file_save = new Fl_Button(btn_file_open->w()+2,hor,101,20,"Save File...");
	btn_file_save->shortcut('s');
	hor += btn_file_open->h()+1;

	/////////////////

	btn_view = new Fl_Light_Button(0,hor,w()-2,30,"V I E W");
	btn_view->align(FL_ALIGN_CENTER);
	btn_view->shortcut('v');
	hor += btn_view->h()+1;

	////////////////

	btn_fix_view = new Fl_Light_Button(0,hor,101,20,"fix axes");
	btn_fix_view->align(FL_ALIGN_CENTER);
	btn_fix_view->shortcut('f');

	btn_light = new Fl_Light_Button(btn_fix_view->w()+2,hor,101,20,"light");
	btn_light->align(FL_ALIGN_CENTER);
	btn_light->shortcut('l');

	hor += btn_light->h()+1;

	/////////////////////////

	btn_color = new Fl_Button(0,hor,101,20,"color");
	btn_color->shortcut('c');
	
	btn_smooth = new Fl_Light_Button(btn_color->w()+2,hor,101,20,"smooth");
	btn_smooth->align(FL_ALIGN_CENTER);
	btn_smooth->shortcut('s');
	hor += btn_smooth->h();

	//////////////////////////

	btn_showiso = new Fl_Light_Button(0,hor,w()-2,20,"isolines");
	btn_showiso->align(FL_ALIGN_CENTER);
	btn_showiso->shortcut('i');
	hor += btn_fix_view->h();

	/////////////////////////

	hor += 7;

	///////////////////////////

	btn_func = new Fl_Light_Button(0,hor,67,20,"func");
	btn_func->align(FL_ALIGN_CENTER);

	btn_wfunc = new Fl_Light_Button(btn_func->w()+1,hor,67,20,"wfunc");
	btn_wfunc->align(FL_ALIGN_CENTER);
	
	btn_trend = new Fl_Light_Button(btn_func->w()*2+2,hor,68,20,"trend");
	btn_trend->align(FL_ALIGN_CENTER);
	
	hor += btn_func->h();

	///////////////////////////

	btn_task = new Fl_Light_Button(0,hor,67,20,"task");
	btn_task->align(FL_ALIGN_CENTER);

	btn_wtask = new Fl_Light_Button(btn_task->w()+1,hor,67,20,"wtask");
	btn_wtask->align(FL_ALIGN_CENTER);

	btn_ptask = new Fl_Light_Button(btn_task->w()*2+2,hor,68,20,"ptask");
	btn_ptask->align(FL_ALIGN_CENTER);

	hor += btn_task->h();

	///////////////////////////

	btn_iso = new Fl_Light_Button(0,hor,67,20,"iso");
	btn_iso->align(FL_ALIGN_CENTER);

	btn_wiso = new Fl_Light_Button(btn_iso->w()+1,hor,67,20,"wiso");
	btn_wiso->align(FL_ALIGN_CENTER);
	
	btn_piso = new Fl_Light_Button(btn_iso->w()*2+2,hor,68,20,"piso");
	btn_piso->align(FL_ALIGN_CENTER);
	
	hor += btn_iso->h();

	///////////////////////////

	btn_cntr = new Fl_Light_Button(0,hor,67,20,"cntr");
	btn_cntr->align(FL_ALIGN_CENTER);

	btn_wcntr = new Fl_Light_Button(btn_cntr->w()+1,hor,67,20,"wcntr");
	btn_wcntr->align(FL_ALIGN_CENTER);
	
	btn_pcntr = new Fl_Light_Button(btn_cntr->w()*2+2,hor,68,20,"pcntr");
	btn_pcntr->align(FL_ALIGN_CENTER);

	hor += btn_cntr->h();

	///////////////////////////

	btn_area = new Fl_Light_Button(0,hor,67,20,"area");
	btn_area->align(FL_ALIGN_CENTER);

	btn_warea = new Fl_Light_Button(btn_area->w()+1,hor,67,20,"warea");
	btn_warea->align(FL_ALIGN_CENTER);
	
	btn_parea = new Fl_Light_Button(btn_area->w()*2+2,hor,68,20,"parea");
	btn_parea->align(FL_ALIGN_CENTER);
	
	hor += btn_area->h();

	///////////////////////////

	btn_flt = new Fl_Light_Button(0,hor,101,20,"flt");
	btn_flt->align(FL_ALIGN_CENTER);

	btn_curv = new Fl_Light_Button(btn_flt->w()+1,hor,102,20,"curv");
	btn_curv->align(FL_ALIGN_CENTER);

	hor += btn_flt->h();

	///////////////////////////

	btn_grid = new Fl_Light_Button(0,hor,101,20,"grid");
	btn_grid->align(FL_ALIGN_CENTER);

	btn_defarea = new Fl_Light_Button(btn_grid->w()+1,hor,102,20,"defarea");
	btn_defarea->align(FL_ALIGN_CENTER);
	
	hor += btn_area->h();

	///////////////////////////
	
	hor += 7;

	///////////////////////////
	
	btn_decomp = new Fl_Button(0,hor,101,20,"decompose");
	btn_decomp->shortcut('d');
	btn_recons = new Fl_Button(btn_file_open->w()+2,hor,101,20,"reconstruct");
	btn_recons->shortcut('r');
	hor += btn_file_open->h();

	btn_auto_decomp = new Fl_Button(0,hor,101,20,"auto decomp");
	btn_auto_decomp->shortcut('a');
	btn_eps = new Fl_Float_Input(btn_auto_decomp->w()+2+40,hor,50,20,"eps=");
	btn_eps->value("0.1");
	btn_eps->align(FL_ALIGN_LEFT);
	hor += btn_auto_decomp->h();

	////////////////////////////////

	txt_show = new Fl_Box(0,hor,50,20,"show :");
	btn_show_total = new Fl_Light_Button(txt_show->w(),hor,76,20,"total");
	btn_show_total->align(FL_ALIGN_CENTER);
	btn_select_area = new Fl_Button(txt_show->w()+btn_show_total->w()+2,hor,76,20,"select");
	
	hor += btn_show_total->h();

	btn_exit = new Fl_Button(0,hor,w()-2,20,"E X I T");
	btn_exit->shortcut(FL_CTRL + 'q');
	hor += btn_exit->h();
	h(hor);

};

void funner2d_wind::set_callbacks() {
	btn_file_open->callback(cb_file_open, this);
	btn_file_save->callback(cb_file_save, this);
	btn_decomp->callback(cb_decomp, this);
	btn_recons->callback(cb_recons, this);
	btn_exit->callback(cb_exit,interp);
	btn_view->callback(cb_view, this);
	btn_fix_view->callback(cb_fix_view, this);
	btn_auto_decomp->callback(cb_auto_decomp, this);
	
	btn_select_area->callback(cb_select_area, this);
	btn_show_total->callback(cb_show_total, this);
	btn_color->callback(cb_color, this);
	btn_light->callback(cb_light, this);
	btn_smooth->callback(cb_smooth, this);
	btn_showiso->callback(cb_showiso, this);

	btn_task->callback(cb_task, this);
	btn_wtask->callback(cb_wtask, this);
	btn_ptask->callback(cb_ptask, this);
	btn_func->callback(cb_func, this);
	btn_wfunc->callback(cb_wfunc, this);
	btn_trend->callback(cb_trend, this);
	btn_iso->callback(cb_iso, this);
	btn_piso->callback(cb_piso, this);
	btn_wiso->callback(cb_wiso, this);
	btn_cntr->callback(cb_cntr, this);
	btn_wcntr->callback(cb_wcntr, this);
	btn_pcntr->callback(cb_pcntr, this);
	btn_area->callback(cb_area, this);
	btn_warea->callback(cb_warea, this);
	btn_parea->callback(cb_parea, this);
	btn_flt->callback(cb_flt, this);
	btn_curv->callback(cb_curv, this);
	btn_grid->callback(cb_grid, this);
	btn_defarea->callback(cb_defarea, this);
	
};


void funner2d_wind::enable_disable() {

	const char * res = NULL;

	// task
	int show_task = 0;
	int task_check = 0;
	int tasks_size = 0;
	Tcl_Eval(interp,"task_check");
	res = Tcl_GetStringResult(interp);
	task_check = atoi(res);
	Tcl_Eval(interp,"tasks_size");
	res = Tcl_GetStringResult(interp);
	tasks_size = atoi(res);
	if ( (task_check) || (tasks_size > 0) )
		show_task = 1;

	// wtask
	int show_wtask = 0;
	int wtask_check = 0;
	int wtasks_size = 0;
	Tcl_Eval(interp,"wtask_check");
	res = Tcl_GetStringResult(interp);
	wtask_check = atoi(res);
	Tcl_Eval(interp,"wtasks_size");
	res = Tcl_GetStringResult(interp);
	wtasks_size = atoi(res);
	if ( (wtask_check) || (wtasks_size > 0) )
		show_wtask = 1;

	// ptask
	int show_ptask = 0;
	int ptask_check = 0;
	int ptasks_size = 0;
	Tcl_Eval(interp,"ptask_check");
	res = Tcl_GetStringResult(interp);
	ptask_check = atoi(res);
	Tcl_Eval(interp,"ptasks_size");
	res = Tcl_GetStringResult(interp);
	ptasks_size = atoi(res);
	if ( (ptask_check) || (ptasks_size > 0) )
		show_ptask = 1;

	// func
	int show_func = 0;
	int func_check = 0;
	int funcs_size = 0;
	Tcl_Eval(interp,"func_check");
	res = Tcl_GetStringResult(interp);
	func_check = atoi(res);
	Tcl_Eval(interp,"funcs_size");
	res = Tcl_GetStringResult(interp);
	funcs_size = atoi(res);
	if ( (func_check) || (funcs_size > 0) )
		show_func = 1;

	// wfunc
	int show_wfunc = 0;
	int wfunc_check = 0;
	int wfuncs_size = 0;
	Tcl_Eval(interp,"wfunc_check");
	res = Tcl_GetStringResult(interp);
	wfunc_check = atoi(res);
	Tcl_Eval(interp,"wfuncs_size");
	res = Tcl_GetStringResult(interp);
	wfuncs_size = atoi(res);
	if ( (wfunc_check) || (wfuncs_size > 0) )
		show_wfunc = 1;

	// trend
	int show_trend = 0;
	int trend_check = 0;
	int trends_size = 0;
	Tcl_Eval(interp,"trend_check");
	res = Tcl_GetStringResult(interp);
	trend_check = atoi(res);
	Tcl_Eval(interp,"trends_size");
	res = Tcl_GetStringResult(interp);
	trends_size = atoi(res);
	if ( (trend_check) || (trends_size > 0) )
		show_trend = 1;

	// iso
	int show_iso = 0;
	int iso_check = 0;
	int isos_size = 0;
	Tcl_Eval(interp,"iso_check");
	res = Tcl_GetStringResult(interp);
	iso_check = atoi(res);
	Tcl_Eval(interp,"isos_size");
	res = Tcl_GetStringResult(interp);
	isos_size = atoi(res);
	if ( (iso_check) || (isos_size > 0) )
		show_iso = 1;

	// wiso
	int show_wiso = 0;
	int wiso_check = 0;
	int wisos_size = 0;
	Tcl_Eval(interp,"wiso_check");
	res = Tcl_GetStringResult(interp);
	wiso_check = atoi(res);
	Tcl_Eval(interp,"wisos_size");
	res = Tcl_GetStringResult(interp);
	wisos_size = atoi(res);
	if ( (wiso_check) || (wisos_size > 0) )
		show_wiso = 1;

	// piso
	int show_piso = 0;
	int piso_check = 0;
	int pisos_size = 0;
	Tcl_Eval(interp,"piso_check");
	res = Tcl_GetStringResult(interp);
	piso_check = atoi(res);
	Tcl_Eval(interp,"pisos_size");
	res = Tcl_GetStringResult(interp);
	pisos_size = atoi(res);
	if ( (piso_check) || (pisos_size > 0) )
		show_piso = 1;

	// cntr
	int show_cntr = 0;
	int cntr_check = 0;
	int cntrs_size = 0;
	Tcl_Eval(interp,"cntr_check");
	res = Tcl_GetStringResult(interp);
	cntr_check = atoi(res);
	Tcl_Eval(interp,"cntrs_size");
	res = Tcl_GetStringResult(interp);
	cntrs_size = atoi(res);
	if ( (cntr_check) || (cntrs_size > 0) )
		show_cntr = 1;

	// wcntr
	int show_wcntr = 0;
	int wcntr_check = 0;
	int wcntrs_size = 0;
	Tcl_Eval(interp,"wcntr_check");
	res = Tcl_GetStringResult(interp);
	wcntr_check = atoi(res);
	Tcl_Eval(interp,"wcntrs_size");
	res = Tcl_GetStringResult(interp);
	wcntrs_size = atoi(res);
	if ( (wcntr_check) || (wcntrs_size > 0) )
		show_wcntr = 1;

	// pcntr
	int show_pcntr = 0;
	int pcntr_check = 0;
	int pcntrs_size = 0;
	Tcl_Eval(interp,"pcntr_check");
	res = Tcl_GetStringResult(interp);
	pcntr_check = atoi(res);
	Tcl_Eval(interp,"pcntrs_size");
	res = Tcl_GetStringResult(interp);
	pcntrs_size = atoi(res);
	if ( (pcntr_check) || (pcntrs_size > 0) )
		show_pcntr = 1;

	// area
	int show_area = 0;
	int area_check = 0;
	int areas_size = 0;
	Tcl_Eval(interp,"area_check");
	res = Tcl_GetStringResult(interp);
	area_check = atoi(res);
	Tcl_Eval(interp,"areas_size");
	res = Tcl_GetStringResult(interp);
	areas_size = atoi(res);
	if ( (area_check) || (areas_size > 0) )
		show_area = 1;

	// warea
	int show_warea = 0;
	int warea_check = 0;
	int wareas_size = 0;
	Tcl_Eval(interp,"warea_check");
	res = Tcl_GetStringResult(interp);
	warea_check = atoi(res);
	Tcl_Eval(interp,"wareas_size");
	res = Tcl_GetStringResult(interp);
	wareas_size = atoi(res);
	if ( (warea_check) || (wareas_size > 0) )
		show_warea = 1;

	// parea
	int show_parea = 0;
	int parea_check = 0;
	int pareas_size = 0;
	Tcl_Eval(interp,"parea_check");
	res = Tcl_GetStringResult(interp);
	parea_check = atoi(res);
	Tcl_Eval(interp,"pareas_size");
	res = Tcl_GetStringResult(interp);
	pareas_size = atoi(res);
	if ( (parea_check) || (pareas_size > 0) )
		show_parea = 1;
	
	// flt
	int show_flt = 0;
	int flt_check = 0;
	int flts_size = 0;
	Tcl_Eval(interp,"flt_check");
	res = Tcl_GetStringResult(interp);
	flt_check = atoi(res);
	Tcl_Eval(interp,"flts_size");
	res = Tcl_GetStringResult(interp);
	flts_size = atoi(res);
	if ( (flt_check) || (flts_size > 0) )
		show_flt = 1;

	// curv
	int show_curv = 0;
	int curv_check = 0;
	int curvs_size = 0;
	Tcl_Eval(interp,"curv_check");
	res = Tcl_GetStringResult(interp);
	curv_check = atoi(res);
	Tcl_Eval(interp,"curvs_size");
	res = Tcl_GetStringResult(interp);
	curvs_size = atoi(res);
	if ( (curv_check) || (curvs_size > 0) )
		show_curv = 1;

	// grid
	int show_grid = 0;
	int grid_check = 0;
	int grids_size = 0;
	Tcl_Eval(interp,"grid_check");
	res = Tcl_GetStringResult(interp);
	grid_check = atoi(res);
	Tcl_Eval(interp,"grids_size");
	res = Tcl_GetStringResult(interp);
	grids_size = atoi(res);
	if ( (grid_check) || (grids_size > 0) )
		show_grid = 1;

	// defarea
	int show_defarea = 0;
	int defarea_check = 0;
	int defareas_size = 0;
	Tcl_Eval(interp,"defarea_check");
	res = Tcl_GetStringResult(interp);
	defarea_check = atoi(res);
	Tcl_Eval(interp,"defareas_size");
	res = Tcl_GetStringResult(interp);
	defareas_size = atoi(res);
	if ( (defarea_check) || (defareas_size > 0) )
		show_defarea = 1;

	set_btn_values();

	btn_view->activate();
	btn_fix_view->activate();
	btn_light->activate();
	btn_smooth->activate();
	btn_showiso->activate();
	
	// approximation loaded
	if ( show_func ) {
		btn_func->activate();
		details_scroll->activate();
		details_pack->activate();
		btn_file_save->activate();
		btn_decomp->activate();
		btn_recons->activate();
		btn_auto_decomp->activate();
		btn_eps->activate();
	} else {
		btn_func->deactivate();
		details_scroll->deactivate();
		details_pack->deactivate();
		btn_file_save->deactivate();
		btn_decomp->deactivate();
		btn_recons->deactivate();
		btn_auto_decomp->deactivate();
		btn_eps->deactivate();
	}

	if (show_task)
		btn_task->activate();
	else
		btn_task->deactivate();

	if (show_wtask)
		btn_wtask->activate();
	else
		btn_wtask->deactivate();

	if (show_ptask)
		btn_ptask->activate();
	else
		btn_ptask->deactivate();

	if (show_trend)
		btn_trend->activate();
	else
		btn_trend->deactivate();

	if (show_wfunc)
		btn_wfunc->activate();
	else
		btn_wfunc->deactivate();

	if (show_iso)
		btn_iso->activate();
	else
		btn_iso->deactivate();

	if (show_piso)
		btn_piso->activate();
	else
		btn_piso->deactivate();

	if (show_wiso)
		btn_wiso->activate();
	else
		btn_wiso->deactivate();

	if (show_cntr)
		btn_cntr->activate();
	else
		btn_cntr->deactivate();

	if (show_wcntr)
		btn_wcntr->activate();
	else
		btn_wcntr->deactivate();

	if (show_pcntr)
		btn_pcntr->activate();
	else
		btn_pcntr->deactivate();

	if (show_area)
		btn_area->activate();
	else
		btn_area->deactivate();

	if (show_warea)
		btn_warea->activate();
	else
		btn_warea->deactivate();
	
	if (show_parea)
		btn_parea->activate();
	else
		btn_parea->deactivate();
	
	if (show_flt)
		btn_flt->activate();
	else
		btn_flt->deactivate();

	if (show_curv)
		btn_curv->activate();
	else
		btn_curv->deactivate();

	if (show_grid)
		btn_grid->activate();
	else
		btn_grid->deactivate();

	if (show_defarea)
		btn_defarea->activate();
	else
		btn_defarea->deactivate();
	
};

void funner2d_wind::delete_all_details_btns() {
	int child = details_pack->children();
	while (child != 0) {
		Fl_Widget* const* p_array = details_pack->array();
		Fl_Widget *p;
		p = p_array[0];
		details_pack->remove(p);
		child = details_pack->children();
	};
};


void funner2d_wind::set_btn_values() {

	const char * temp = NULL;



	int light = 0;
	temp = Tcl_GetVar(interp,"light",0);
	if (temp)
		light = atoi(temp);
	btn_light->value(light);
	
	int smooth = 0;
	temp = Tcl_GetVar(interp,"smooth",0);
	if (temp)
		smooth = atoi(temp);
	btn_smooth->value(smooth);

	int showiso = 0;
	temp = Tcl_GetVar(interp,"isoline",0);
	if (temp)
		showiso = atoi(temp);
	btn_showiso->value(showiso);





	// task
	int draw_task = 0;
	temp = Tcl_GetVar(interp,"draw_task",0);
	if (temp)
		draw_task = atoi(temp);
	btn_task->value(draw_task);

	// wtask
	int draw_wtask = 0;
	temp = Tcl_GetVar(interp,"draw_wtask",0);
	if (temp)
		draw_wtask = atoi(temp);
	btn_wtask->value(draw_wtask);
		
	// ptask
	int draw_ptask = 0;
	temp = Tcl_GetVar(interp,"draw_ptask",0);
	if (temp)
		draw_ptask = atoi(temp);
	btn_ptask->value(draw_ptask);

	// func
	int draw_func = 0;
	temp = Tcl_GetVar(interp,"draw_func",0);
	if (temp)
		draw_func = atoi(temp);
	btn_func->value(draw_func);

	// wfunc
	int draw_wfunc = 0;
	temp = Tcl_GetVar(interp,"draw_wfunc",0);
	if (temp)
		draw_wfunc = atoi(temp);
	btn_wfunc->value(draw_wfunc);

	// trend
	int draw_trend = 0;
	temp = Tcl_GetVar(interp,"draw_trend",0);
	if (temp)
		draw_trend = atoi(temp);
	btn_trend->value(draw_trend);

	// iso
	int draw_iso = 0;
	temp = Tcl_GetVar(interp,"draw_iso",0);
	if (temp)
		draw_iso = atoi(temp);
	btn_iso->value(draw_iso);

	// piso
	int draw_piso = 0;
	temp = Tcl_GetVar(interp,"draw_piso",0);
	if (temp)
		draw_piso = atoi(temp);
	btn_piso->value(draw_piso);

	// wiso
	int draw_wiso = 0;
	temp = Tcl_GetVar(interp,"draw_wiso",0);
	if (temp)
		draw_wiso = atoi(temp);
	btn_wiso->value(draw_wiso);

	// cntr
	int draw_cntr = 0;
	temp = Tcl_GetVar(interp,"draw_cntr",0);
	if (temp)
		draw_cntr = atoi(temp);
	btn_cntr->value(draw_cntr);

	// wcntr
	int draw_wcntr = 0;
	temp = Tcl_GetVar(interp,"draw_wcntr",0);
	if (temp)
		draw_wcntr = atoi(temp);
	btn_wcntr->value(draw_wcntr);
		
	// pcntr
	int draw_pcntr = 0;
	temp = Tcl_GetVar(interp,"draw_pcntr",0);
	if (temp)
		draw_pcntr = atoi(temp);
	btn_pcntr->value(draw_pcntr);

	// area
	int draw_area = 0;
	temp = Tcl_GetVar(interp,"draw_area",0);
	if (temp)
		draw_area = atoi(temp);
	btn_area->value(draw_area);

	// warea
	int draw_warea = 0;
	temp = Tcl_GetVar(interp,"draw_warea",0);
	if (temp)
		draw_warea = atoi(temp);
	btn_warea->value(draw_warea);

	// parea
	int draw_parea = 0;
	temp = Tcl_GetVar(interp,"draw_parea",0);
	if (temp)
		draw_parea = atoi(temp);
	btn_parea->value(draw_parea);

	// flt
	int draw_flt = 0;
	temp = Tcl_GetVar(interp,"draw_flt",0);
	if (temp)
		draw_flt = atoi(temp);
	btn_flt->value(draw_flt);

	// curv
	int draw_curv = 0;
	temp = Tcl_GetVar(interp,"draw_curv",0);
	if (temp)
		draw_curv = atoi(temp);
	btn_curv->value(draw_curv);

	// grid
	int draw_grid = 0;
	temp = Tcl_GetVar(interp,"draw_grid",0);
	if (temp)
		draw_grid = atoi(temp);
	btn_grid->value(draw_grid);

	// defarea
	int draw_defarea = 0;
	temp = Tcl_GetVar(interp,"draw_defarea",0);
	if (temp)
		draw_defarea = atoi(temp);
	btn_defarea->value(draw_defarea);

};


