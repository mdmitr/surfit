
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

#include "ie.h"

#include "variables.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "license.h"

#include "fileio.h"
#include "rnd.h"
#include "color_scale.h"
#include "file_manager.h"

#include "solvers.h"

#include "free_elements.h"

#include "user.h"
#include "grid_user.h"
#include "flt_user.h"
#include "task_user.h"
#include "wtask_user.h"
#include "iso_user.h"
#include "wiso_user.h"
#include "cntr_user.h"
#include "wcntr_user.h"
#include "area_user.h"
#include "warea_user.h"
#include "func_user.h"
#include "wfunc_user.h"
#include "trend_user.h"
#include "defarea_user.h"
#include "fill_with_user.h"
#include "dynamic_user.h"
#include "completer_user.h"

#include "draw.h"

#include <vector>
#include <float.h>
#include <tcl.h>

namespace surfit {

float tol = float(0);
int datafile_mode = 1;
int priority = 0;
int solver_code = 1;
bool write_mat = false;

REAL sor_omega = 0.6;
REAL ssor_omega = 0.6;

REAL undef_value = FLT_MAX;

Tcl_Interp * surfit_interp = NULL;

color_scale * surfit_color_scale = NULL;
data_manager *  surfit_data_manager = NULL;

std::vector<user *> * surfit_users = NULL;

char * map_name = NULL;

/*! \struct garbage
    \brief struct for init and deletion of different pointers (\ref user)
*/
struct garbage : public binman {
	//! init different pointers
	garbage() {
		surfit_init_all();		
	};
	
	//! removes different pointers (\ref user)
	virtual ~garbage() {
		delete surfit_color_scale;
		surfit_color_scale = NULL;
		delete surfit_data_manager;
		surfit_data_manager = NULL;
		if (surfit_users) {
			free_elements(surfit_users->begin(), surfit_users->end());
			delete surfit_users;
		}
	};
};

garbage garb;

char rw_mode[7];

void rw_mode_set(const char * newmode) {
	char text[5] = "text";
	char binary[7] = "binary";
	if (strcmp(newmode,text) == 0) {
		strcpy(rw_mode,text);
		return;
	};
	if (strcmp(newmode,binary) == 0) {
		strcpy(rw_mode,binary);
		return;
	};
	writelog(SURFIT_ERROR,"rw_mode_set : unknown mode. ");
	return;
};

const char * rw_mode_get() {
	return rw_mode;
};

int get_rw_mode() {
	if (strcmp(rw_mode,"text") == 0) {
		return 1;
	};
	if (strcmp(rw_mode,"binary") == 0) {
		return 0;
	};
	writelog(SURFIT_ERROR,"rw_mode : illegial rw_mode ");
	return -1;
};

static void
data_cleanup(ClientData clientData)
{
    clear_data();
#ifdef HAVE_GL_WORKS
    cleanup();
#endif
};


void surfit_init_all() {
	randomize();
	priority = 0;
	datafile_mode = 1;
	tol = float(0);
	undef_value = FLT_MAX;
	solver_code = SOLVER_CG;
	write_mat = false;
	rw_mode_set("binary");

	sor_omega = REAL(1.6);
	ssor_omega = REAL(1.6);

	surfit_data_manager = new data_manager;
	surfit_data_manager->managers->push_back(new surfit_manager);
	surfit_users = new std::vector<user *>;
	
	grid_user * grid_usr = new grid_user();
	surfit_users->push_back(grid_usr);

	defarea_user * defarea_usr = new defarea_user();
	surfit_users->push_back(defarea_usr);

	flt_user * flt_usr = new flt_user();
	surfit_users->push_back(flt_usr);

	task_user * task_usr = new task_user();
	surfit_users->push_back(task_usr);

	wtask_user * wtask_usr = new wtask_user();
	surfit_users->push_back(wtask_usr);

	iso_user * iso_usr = new iso_user();
	surfit_users->push_back(iso_usr);

	wiso_user * wiso_usr = new wiso_user();
	surfit_users->push_back(wiso_usr);

	cntr_user * cntr_usr = new cntr_user();
	surfit_users->push_back(cntr_usr);

	wcntr_user * wcntr_usr = new wcntr_user();
	surfit_users->push_back(wcntr_usr);

	area_user * area_usr = new area_user();
	surfit_users->push_back(area_usr);

	warea_user * warea_usr = new warea_user();
	surfit_users->push_back(warea_usr);

	func_user * func_usr = new func_user();
	surfit_users->push_back(func_usr);

	wfunc_user * wfunc_usr = new wfunc_user();
	surfit_users->push_back(wfunc_usr);

	trend_user * trend_usr = new trend_user();
	surfit_users->push_back(trend_usr);

	fill_with_user * fill_with_usr = new fill_with_user();
	surfit_users->push_back(fill_with_usr);

	dynamic_user * dynamic_usr = new dynamic_user();
	surfit_users->push_back(dynamic_usr);

	completer_user * completer_usr = new completer_user();
	surfit_users->push_back(completer_usr);

	//Tcl_printf("color_scale initialized!!!");
	surfit_color_scale = new color_scale(0, 1, 0.5, DEFAULT_COLORS);
		
	surfit_color_scale->set(-15000,0,10,
		                0,25,136,
				26,140,255);
	surfit_color_scale->add(0,350,10,
				25,101,25,
				153,102,1);
	surfit_color_scale->add(350,3500,10,
				153,102,1,
				155,204,204);
	surfit_color_scale->add(3500,15000,10,
				155,204,204,
				204,234,255);
	surfit_color_scale->set_default(true);
	//surfit_color_scale->set_default(false);

	Tcl_CreateThreadExitHandler(data_cleanup, NULL);
};


void surfit_init_variables(Tcl_Interp * iinterp) {

	/*
	surfit_color_scale = new color_scale(0, 1, 0.5,
					     0, 0, 0,
					     255, 255, 255);
	*/
	

	// 2d
	surfit_interp = iinterp;
	print_license();
	log_open();
	
	//init_all();
};


void set_tol(float val) {
	tol = val;
};

float get_tol() {
	return tol;
};

}; // namespace surfit;


