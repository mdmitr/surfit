
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
#include "real.h"
#include "details_btn.h"
#include "gl_view_funner2d.h"
#include "color_scale_dlg.h"
#include "init_surfit.h"

#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Round_Button.H>

void funner2d_wind::init_tcl() {

	interp  = Tcl_CreateInterp();
	Tcl_FindExecutable(exec);
	Tcl_Init(interp);

	funnerChannelInfo *infoPtr;
	infoPtr = (funnerChannelInfo *) ckalloc((unsigned) sizeof(funnerChannelInfo));
	infoPtr->data = NULL;

	channel = Tcl_CreateChannel(&funnerChannelType, "stdoudt",
	    (ClientData) infoPtr, TCL_WRITABLE);

	Tcl_RegisterChannel(interp,channel);
	Tcl_SetStdChannel(channel,TCL_STDOUT);

	char * filepos = NULL;
	prefabula = false;
	prefabula = init_surfit_libs(filepos,interp,&channel);

	while (!prefabula) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
			filepos = fl_dir_chooser("Pick a dir to libsurfit.dll", NULL);
#else
			filepos = fl_dir_chooser("Pick a dir to libsurfit.so", NULL);
#endif
			prefabula = init_surfit_libs(filepos, interp, &channel);
			if (!prefabula) {
				Tcl_Obj *res = Tcl_GetObjResult(interp);
				char * str_err = Tcl_GetStringFromObj(res,NULL);
				fl_alert(str_err);
				Tcl_Exit(0);
			}
	}

	free(filepos);

	Tcl_Eval(interp,"log_open 3");

};

void funner2d_wind::show_details_btns() {

	Tcl_Eval(interp,"func_get_details_level");
	const char * res = Tcl_GetStringResult(interp);
	int level = atoi(res);

	delete_all_details_btns();
	int child = details_pack->children();

	if (level == -1)
		return;

	int i;
	for (i = 0; i <= level; i++) {
		details_btn * b = new details_btn(0,0,10,20,i);
		b->callback(cb_details_btn,this);
		if (i == show_func_number)
			b->set();
		details_pack->add(b);
	}
	details_pack->redraw();
	details_scroll->redraw();

};

void funner2d_wind::show_view(int show) {
	if (show == 0) {
		if (view)
			view->hide();
	} else {
		if (! view) {
			int scr_h = Fl::h();
			int scr_w = Fl::w();
			scr_w -= (int) (x() + w() + w()/10.);
			scr_h -= (int) (scr_h/10.);
			view = new gl_view_funner2d( (int) (x()+w()+w()/10.),
						     (int) (h()/10.),
						     scr_w,scr_h,interp,"V I E W");
			
		}
		view->show();
		redraw_view();
	};
	if (btn_view->value() != show)
		btn_view->value(show);
};

void funner2d_wind::redraw_view() {

	if (!view)
		return;

	if (!view->visible())
		return;

	const char * res = NULL;

	view->make_current();

	Tcl_Eval(interp,"cleanup");
	res = Tcl_GetStringResult(interp);
	Tcl_Eval(interp,"mem_show");
	res = Tcl_GetStringResult(interp);

	view->redraw();

	show();

};

void funner2d_wind::fix_view(int flag) {
	view_fixed = (flag != 0);
	if (view_fixed) 
		Tcl_Eval(interp,"set fix_axes 1");
	else 
		Tcl_Eval(interp,"set fix_axes 0");
};

void funner2d_wind::auto_decomp() {

	// make full reconstruction
	Tcl_Eval(interp, "func_full_recons");

	sprintf(cmd,"func_auto_decomp %s", btn_eps->value());
	Tcl_Eval(interp, cmd);

	redraw_view();
	show_details_btns();
	enable_disable();
};

void funner2d_wind::set_color() {

	Tcl_Eval(interp, "draw_minz");
	const char * res = Tcl_GetStringResult(interp);
	double from = atof(res);
	
	Tcl_Eval(interp, "draw_maxz");
	res = Tcl_GetStringResult(interp);
	double to = atof(res);
	
	double step = (to-from)/20.;

	double d1, d2, d3;
	int i1, i2, i3, i4, i5, i6;

	dlg->cs->get_params(d1,d2,d3,i1,i2,i3,i4,i5,i6);
	dlg->cs->set(from,to,step,i1,i2,i3,i4,i5,i6);
	dlg->refresh();
	
	dlg->show();

};

void funner2d_wind::save_to_file() {

	char * filename = fl_file_chooser("Save func to file", "*",NULL);
	
	if (filename) {

		sprintf(cmd,"func_save %s",filename);
				
		Tcl_Channel chan = Tcl_GetStdChannel(TCL_STDOUT);
		Tcl_Flush(chan);
		
		funnerChannelInfo * infoPtr = (funnerChannelInfo *)Tcl_GetChannelInstanceData(chan);
		
		if (infoPtr) {
			free(infoPtr->data);
			infoPtr->data = NULL;
		}

		Tcl_Eval(interp, cmd);
		const char * R = Tcl_GetStringResult(interp);
		Tcl_Flush(chan);
		
		char * res = NULL;

		if (infoPtr)
			res = infoPtr->data;

		if (res)		
			fl_message(res);
	
	}

};

void funner2d_wind::set_light() {

	int light = btn_light->value();
	if (light == 0)
		Tcl_Eval(interp, "set light 0");
	else 
		Tcl_Eval(interp, "set light 1");

	redraw_view();
};

void funner2d_wind::set_smooth() {

	int smooth = btn_smooth->value();
	if (smooth == 0)
		Tcl_Eval(interp, "set smooth 0");
	else 
		Tcl_Eval(interp, "set smooth 1");
	
	redraw_view();
};

void funner2d_wind::set_showiso() {
	int showiso = btn_showiso->value();
	if (showiso == 0)
		Tcl_Eval(interp, "set isoline 0");
	else
		Tcl_Eval(interp, "set isoline 1");

	redraw_view();
};

void funner2d_wind::file_open(const char * filename) {

	bool load_datafile = true; // else - load surfer grd file

	const char * find_string = filename;
	int find_pos = -1;
	while (find_string != NULL) {
		find_string = strchr(find_string, '.');
		if (find_string != NULL) { // something found
			find_pos = find_string - filename;
			find_string++;
		}
	}
	if (find_pos != -1) {
		if (strcmp(".grd", filename+find_pos) == 0)
			load_datafile = false;
	}

	char * new_filename = (char*)malloc( strlen(filename)+3);
	*new_filename = '"';
	strcpy(new_filename+1,filename);
	*(new_filename+strlen(filename)+1) = '"';
	*(new_filename+strlen(filename)+2) = '\0';
	char * w = NULL;
	if (load_datafile) {
		w = (char*)malloc(strlen("file_load ")+1+strlen(new_filename));
		strcpy(w, "file_load ");
	} else {
		w = (char*)malloc(strlen("func_load_grd ")+1+strlen(new_filename));
		strcpy(w, "func_load_grd ");
	}
		
	strcat(w, new_filename);

	free(new_filename);

	Tcl_Channel chan = Tcl_GetStdChannel(TCL_STDOUT);
	Tcl_Flush(chan);
	funnerChannelInfo * infoPtr = (funnerChannelInfo *)Tcl_GetChannelInstanceData(chan);
	if (infoPtr) {
		free(infoPtr->data);
		infoPtr->data = NULL;
	}
	
	Tcl_Eval(interp, w);
	Tcl_Flush(chan);
	free(w);
	
	char * res = NULL;
	
	if (infoPtr)
		res = infoPtr->data;
	
	if (res)		
		fl_message(res);

	/*
	const char * Res = Tcl_GetStringResult(interp);
	int int_res = atoi(Res);
	if (int_res == 1) {
		
		Tcl_Eval(interp, "func_mean");
		const char * R = Tcl_GetStringResult(interp);
		double mean = atof(R);
		sprintf(cmd,"func_std %lf",mean);
		Tcl_Eval(interp, cmd);
		R = Tcl_GetStringResult(interp);
		double std = atof(R);
		std = std*std/double(100);
		sprintf(cmd,"%lf",std);
		btn_eps->value(cmd);	
		
		Tcl_Flush(chan);
		if (infoPtr)
			res = infoPtr->data;
		
		if (res)		
			fl_message(res);
		
		show_view(0);
		Tcl_Eval(interp, "set_default_color_scale");

		auto_decomp();
	}
	*/

	show_details_btns();
	enable_disable();
	redraw_view();

};

void funner2d_wind::show_total() {
	int show_total = btn_show_total->value();
	if (show_total == 0) {
		Tcl_Eval(interp, "set show_in_area 1");
		btn_show_total->value(0);
	} else {
		Tcl_Eval(interp, "set show_in_area 0");
		btn_show_total->value(1);
	}
	
	redraw_view();
};

void funner2d_wind::select_area() {

	Tcl_Eval(interp, "init_quat");
	Tcl_Eval(interp, "set show_in_area 1");

	if (view) {
			sprintf(cmd,"get_selection_from_screen %d %d", view->w(), view->h());
			Tcl_Eval(interp, cmd);
	}

	btn_show_total->value(0);
	redraw_view();
};




void funner2d_wind::task(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_task %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_task",0);
	btn_task->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::wtask(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_wtask %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_wtask",0);
	btn_wtask->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::ptask(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_ptask %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_ptask",0);
	btn_ptask->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::func(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_func %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_func",0);
	btn_func->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::wfunc(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_wfunc %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_wfunc",0);
	btn_wfunc->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::trend(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_trend %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_trend",0);
	btn_trend->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::iso(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_iso %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_iso",0);
	btn_iso->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::piso(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_piso %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_piso",0);
	btn_piso->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::wiso(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_wiso %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_wiso",0);
	btn_wiso->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::cntr(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_cntr %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_cntr",0);
	btn_cntr->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::wcntr(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_wcntr %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_wcntr",0);
	btn_wcntr->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::pcntr(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_pcntr %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_pcntr",0);
	btn_pcntr->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::area(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_area %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_area",0);
	btn_area->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::warea(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_warea %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_warea",0);
	btn_warea->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::parea(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_parea %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_parea",0);
	btn_parea->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::flt(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_flt %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_flt",0);
	btn_flt->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::curv(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_curv %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_curv",0);
	btn_curv->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::grid(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_grid %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_grid",0);
	btn_grid->value(atoi(res));
	redraw_view();
	
};

void funner2d_wind::defarea(int status) {
	
	const char * res;
	sprintf(cmd, "set draw_defarea %d", status);
	Tcl_Eval(interp, cmd);
	res = Tcl_GetVar(interp,"draw_defarea",0);
	btn_defarea->value(atoi(res));
	redraw_view();
	
};

