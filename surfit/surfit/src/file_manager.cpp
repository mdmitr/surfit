
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
#include "file_manager.h"
#include <string.h>
#include "fileio.h"
#include "grid_internal.h"
#include "grid.h"
#include "grid_tcl.h"
#include "grid_user.h"
#include "func.h"
#include "func_internal.h"
#include "func_tcl.h"
#include "funcs.h"
#include "func_user.h"
#include "wfunc.h"
#include "wfunc_internal.h"
#include "wfunc_tcl.h"
#include "wfuncs.h"
#include "wfunc_user.h"
#include "defarea.h"
#include "defarea_internal.h"
#include "defarea_tcl.h"
#include "defareas.h"
#include "defarea_user.h"
#include "trend.h"
#include "trend_internal.h"
#include "trend_tcl.h"
#include "trends.h"
#include "trend_user.h"
#include "task.h"
#include "task_internal.h"
#include "task_tcl.h"
#include "tasks.h"
#include "task_user.h"
#include "wtask.h"
#include "wtask_internal.h"
#include "wtask_tcl.h"
#include "wtasks.h"
#include "wtask_user.h"
#include "iso.h"
#include "iso_internal.h"
#include "iso_tcl.h"
#include "isos.h"
#include "iso_user.h"
#include "wiso.h"
#include "wiso_internal.h"
#include "wiso_tcl.h"
#include "wisos.h"
#include "wiso_user.h"
#include "flt.h"
#include "flt_internal.h"
#include "flt_tcl.h"
#include "flts.h"
#include "flt_user.h"
#include "area.h"
#include "area_internal.h"
#include "area_tcl.h"
#include "areas.h"
#include "area_user.h"
#include "warea.h"
#include "warea_internal.h"
#include "warea_tcl.h"
#include "wareas.h"
#include "warea_user.h"
#include "cntr.h"
#include "cntr_internal.h"
#include "cntr_tcl.h"
#include "cntrs.h"
#include "cntr_user.h"
#include "wcntr.h"
#include "wcntr_internal.h"
#include "wcntr_tcl.h"
#include "wcntrs.h"
#include "wcntr_user.h"
#include "curv.h"
#include "curv_internal.h"
#include "curv_tcl.h"
#include "curvs.h"
#include "curv_user.h"
#include "dynamic_tcl.h"
#include "dynamics.h"
#include "dynamic_user.h"
#include "completer_tcl.h"
#include "completer_user.h"
#include "grid_line_tcl.h"
#include "grid_line_user.h"
#include "datafile.h"
#include "sort_alg.h"
#include "free_elements.h"
#include "fill_with_tcl.h"
#include "variables.h"
#include "variables_internal.h"
#include "variables_tcl.h"

#ifdef HAVE_GL_WORKS
#include "colors.h"
#include "task_show.h"
#include "wtask_show.h"
#include "grid_show.h"
#include "func_show.h"
#include "wfunc_show.h"
#include "trend_show.h"
#include "defarea_show.h"
#include "curv_show.h"
#include "iso_show.h"
#include "wiso_show.h"
#include "flt_show.h"
#include "area_show.h"
#include "warea_show.h"
#include "cntr_show.h"
#include "wcntr_show.h"
#include "draw.h"
#endif

namespace surfit {


//////////////////////////////
//
// data_manager
//
//////////////////////////////

data_manager::data_manager() {
	managers = new std::vector<manager*>;
	managers->reserve(1000);
};

data_manager::~data_manager() {
	if (managers) {
		release_elements(managers->begin(), managers->end());
	}
	delete managers;
};

bool data_manager::load(datafile * df) const {

	char tagname[TAG_WORD_SIZE];
	if ( !df->readTagName(tagname) ) 
		return false;

	int res = 0;
	while ( strcmp(tagname,"eof") != 0 ) {
		
		if (managers) {
			std::vector<manager *>::iterator it;
			for (it = managers->begin(); it != managers->end(); it++) {
				res = (*it)->load_tag(df, tagname);
				if (res == -1)
					return false;
				if (res == 1)
					break;
			}
		}
		
		if (res == 0) {
			df->skipTag(false);
			
			if ( !df->readTagName(tagname) ) 
				return false;
		}
		
	};

	return true;
};

void data_manager::clear_data() const {
	
	if (managers) {
		std::vector<manager *>::iterator it;
		for (it = managers->begin(); it != managers->end(); it++) 
			if (*it)
				(*it)->clear_data();
	}
	
};

void data_manager::mem_info() const {
	
	if (managers) {
		std::vector<manager *>::iterator it;
		for (it = managers->begin(); it != managers->end(); it++) 
			(*it)->mem_info();
	}
	
};

#ifdef HAVE_GL_WORKS
void data_manager::mem_show() const {
	
	if (managers) {
		std::vector<manager *>::iterator it;
		for (it = managers->begin(); it != managers->end(); it++) 
			(*it)->mem_show();
	}
	
};

bool data_manager::check_for_drawing(const char * type) const {
	
	bool res = true;

	if (managers) {
		std::vector<manager *>::iterator it;
		for (it = managers->begin(); it != managers->end(); it++) {
			res = res && (*it)->check_for_drawing(type);
			if (res == false)
				return res;
		}
	}
	return res;

};

void data_manager::getMinMaxZ(REAL & minZ, REAL & maxZ) const {
	
	minZ = FLT_MAX;
	maxZ = -FLT_MAX;

	int count = data_count();
	int i;
	for (i = 0; i < count; i++) {
		REAL minz = FLT_MAX;
		REAL maxz = -FLT_MAX;
		const data * dat = data_get(i);
		if (dat->getMinMaxZ(minz, maxz)) {
			minZ = MIN(minZ, minz);
			maxZ = MAX(maxZ, maxz);
		};
	}
		
};

#endif

bool data_manager::save(datafile * df) const {
	if (managers) {
		std::vector<manager *>::iterator it;
		for (it = managers->begin(); it != managers->end(); it++)
			if ((*it)->save(df) == false)
				return false;
	}
	return true;
};

int data_manager::data_count() const {
	int res = 0;
	if (managers) {
		std::vector<manager *>::iterator it;
		for (it = managers->begin(); it != managers->end(); it++)
			res += (*it)->data_count();
	}
	return res;
};

const data * data_manager::data_get(int i) const {
	int sum = 0;
	int res = 0;
	if (managers) {
		std::vector<manager *>::iterator it;
		for (it = managers->begin(); it != managers->end(); it++) {
			res = (*it)->data_count();
			if (sum + res > i) {
				return (*it)->data_get(i-sum);
			}
			sum += res;
		};
	};
	return NULL;
};

//////////////////////////////
//
// surfit_manager
//
//////////////////////////////

void surfit_manager::release() {
	delete this;
};

int surfit_manager::load_tag(datafile * df, char * tagname) const {
	
	if (strcmp(tagname, "task") == 0) {
		
		task * res = _task_load_df(df, NULL);
		
		if (res) {
			if (!surfit_task)
				surfit_task = res;
			else
				surfit_tasks->push_back(res);
			_task_info(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "wtask") == 0) {
		
		wtask * res = _wtask_load_df(df, NULL);
		
		if (res) {
			if (!surfit_wtask)
				surfit_wtask = res;
			else
				surfit_wtasks->push_back(res);
			_wtask_info(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
		
	if (strcmp(tagname, "func") == 0) {
		
		func * res = _func_load_df(df, NULL);
		
		if (res) {
			if (!surfit_func)
				surfit_func = res;
			else
				surfit_funcs->push_back(res);
			_func_info(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "wfunc") == 0) {
		
		wfunc * res = _wfunc_load_df(df, NULL);
		
		if (res) {
			if (!surfit_wfunc)
				surfit_wfunc = res;
			else
				surfit_wfuncs->push_back(res);
			_wfunc_info(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "defarea") == 0) {
		
		defarea * res = _defarea_load_df(df, NULL);
		
		if (res) {
			if (!surfit_defarea)
				surfit_defarea = res;
			else
				surfit_defareas->push_back(res);
			_defarea_info(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "trend") == 0) {
		
		trend * res = _trend_load_df(df, NULL);
		
		if (res) {
			if (!surfit_trend)
				surfit_trend = res;
			else
				surfit_trends->push_back(res);
			_trend_info(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "iso") == 0) {
		
		iso * res = _iso_load_df(df, NULL);
		if (res) {
			_iso_info(res);
			surfit_isos->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "wiso") == 0) {
		
		wiso * res = _wiso_load_df(df, NULL);
		if (res) {
			_wiso_info(res);
			surfit_wisos->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "cntr") == 0) {
		
		cntr * res = _cntr_load_df(df, NULL);
		if (res) {
			_cntr_info(res);
			surfit_cntrs->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "wcntr") == 0) {
		
		wcntr * res = _wcntr_load_df(df, NULL);
		if (res) {
			_wcntr_info(res);
			surfit_wcntrs->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "area") == 0) {
		
		area * res = _area_load_df(df, NULL);
		if (res) {
			_area_info(res);
			surfit_areas->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "warea") == 0) {
		
		warea * res = _warea_load_df(df, NULL);
		if (res) {
			_warea_info(res);
			surfit_wareas->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "flt") == 0) {
		
		flt * res = _flt_load_df(df, NULL);
		if (res) {
			_flt_info(res);
			surfit_flts->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "curv") == 0) {
		
		curv * res = _curv_load_df(df, NULL);
		if (res) {
			_curv_info(res);
			surfit_curvs->push_back(res);
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "grid") == 0) {
		
		grid * res = _grid_load_df(df, NULL);
		if (res) {
			delete surfit_grid;
			surfit_grid = res;
			grid_info();
		}
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
	
	return 0;
};

bool surfit_manager::save(datafile *df) const {

	unsigned int cnt;

	if (surfit_grid) {
		if (!_grid_save_df(surfit_grid, df))
			return false;
	}

	if (surfit_func) {
		if (!_func_save_df(surfit_func, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_funcs->size(); cnt++) {
		func * fnc = *(surfit_funcs->begin()+cnt);
		if (!_func_save_df(fnc, df))
			return false;
	}

	if (surfit_wfunc) {
		if (!_wfunc_save_df(surfit_wfunc, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_wfuncs->size(); cnt++) {
		wfunc * fnc = *(surfit_wfuncs->begin()+cnt);
		if (!_wfunc_save_df(fnc, df))
			return false;
	}

	if (surfit_defarea) {
		if (!_defarea_save_df(surfit_defarea, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_defareas->size(); cnt++) {
		defarea * fnc = *(surfit_defareas->begin()+cnt);
		if (!_defarea_save_df(fnc, df))
			return false;
	}

	if (surfit_trend) {
		if (!_trend_save_df(surfit_trend, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_trends->size(); cnt++) {
		trend * fnc = *(surfit_trends->begin()+cnt);
		if (!_trend_save_df(fnc, df))
			return false;
	}

	if (surfit_task) {
		if (!_task_save_df(surfit_task, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_tasks->size(); cnt++) {
		task * tsk = *(surfit_tasks->begin()+cnt);
		if (!_task_save_df(tsk, df))
			return false;
	}

	if (surfit_wtask) {
		if (!_wtask_save_df(surfit_wtask, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_wtasks->size(); cnt++) {
		wtask * tsk = *(surfit_wtasks->begin()+cnt);
		if (!_wtask_save_df(tsk, df))
			return false;
	}

	if (surfit_iso) {
		if (!_iso_save_df(surfit_iso, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_isos->size(); cnt++) {
		iso * isoline = *(surfit_isos->begin()+cnt);
		if (!_iso_save_df(isoline, df))
			return false;
	}

	if (surfit_wiso) {
		if (!_wiso_save_df(surfit_wiso, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_wisos->size(); cnt++) {
		wiso * wisoline = *(surfit_wisos->begin()+cnt);
		if (!_wiso_save_df(wisoline, df))
			return false;
	}

	if (surfit_cntr) {
		if (!_cntr_save_df(surfit_cntr, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_cntrs->size(); cnt++) {
		cntr * cntrline = *(surfit_cntrs->begin()+cnt);
		if (!_cntr_save_df(cntrline, df))
			return false;
	}

	if (surfit_wcntr) {
		if (!_wcntr_save_df(surfit_wcntr, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_wcntrs->size(); cnt++) {
		wcntr * wcntrline = *(surfit_wcntrs->begin()+cnt);
		if (!_wcntr_save_df(wcntrline, df))
			return false;
	}

	if (surfit_flt) {
		if (!_flt_save_df(surfit_flt, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_flts->size(); cnt++) {
		flt * fault = *(surfit_flts->begin()+cnt);
		if (!_flt_save_df(fault, df))
			return false;
	}

	if (surfit_area) {
		if (!_area_save_df(surfit_area, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_areas->size(); cnt++) {
		area * ar = *(surfit_areas->begin()+cnt);
		if (!_area_save_df(ar, df))
			return false;
	}

	if (surfit_warea) {
		if (!_warea_save_df(surfit_warea, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_wareas->size(); cnt++) {
		warea * ar = *(surfit_wareas->begin()+cnt);
		if (!_warea_save_df(ar, df))
			return false;
	}

	if (surfit_curv) {
		if (!_curv_save_df(surfit_curv, df))
			return false;
	}

	for (cnt = 0; cnt < surfit_curvs->size(); cnt++) {
		curv * ar = *(surfit_curvs->begin()+cnt);
		if (!_curv_save_df(ar, df))
			return false;
	}

	return true;

};

void surfit_manager::clear_data() const {

	grid_unload();
	
	func_unload();
	funcs_delall();

	defarea_unload();
	defareas_delall();

	wfunc_unload();
	wfuncs_delall();
	
	trend_unload();
	trends_delall();
	
	task_unload();
	tasks_delall();

	wtask_unload();
	wtasks_delall();
	
	dynamic_unload();
	dynamics_delall();
	
	flt_unload();
	flts_delall();

	iso_unload();
	isos_delall();

	wiso_unload();
	wisos_delall();
	
	area_unload();
	areas_delall();

	warea_unload();
	wareas_delall();
	
	cntr_unload();
	cntrs_delall();
	
	wcntr_unload();
	wcntrs_delall();

	completer_set(1, 2);

	grid_line_unload();

	curv_unload();
	curvs_delall();

	fill_with_unload();

	tol = float(0);

};

void surfit_manager::mem_info() const {

	grid_info();
	funcs_info();
	defareas_info();
	wfuncs_info();
	trends_info();
	tasks_info();
	wtasks_info();
	dynamics_info();
	flts_info();
	isos_info();
	wisos_info();
	areas_info();
	wareas_info();
	cntrs_info();
	wcntrs_info();
	completer_info();
	curvs_info();

};

int surfit_manager::data_count() const {
	int res = 0;

	if (surfit_func) 
		res++;
	res += surfit_funcs->size();

	if (surfit_wfunc) 
		res++;
	res += surfit_wfuncs->size();

	if (surfit_defarea)
		res++;
	res += surfit_defareas->size(); 

	if (surfit_trend) 
		res++;
	res += surfit_trends->size();

	if (surfit_task) 
		res++;
	res += surfit_tasks->size(); 

	if (surfit_wtask) 
		res++;
	res += surfit_wtasks->size();

	if (surfit_iso) 
		res++;
	res += surfit_isos->size();

	if (surfit_wiso) 
		res++;
	res += surfit_wisos->size(); 

	if (surfit_cntr) 
		res++;
	res += surfit_cntrs->size(); 

	if (surfit_wcntr) 
		res++;
	res += surfit_wcntrs->size(); 

	if (surfit_flt) 
		res++;
	res += surfit_flts->size(); 

	if (surfit_area) 
		res++;
	res += surfit_areas->size(); 

	if (surfit_warea) 
		res++;
	res += surfit_wareas->size(); 

	if (surfit_curv) 
		res++;
	res += surfit_curvs->size();

	return res;
};

const data * surfit_manager::data_get(int i) const {
	
	int res = 0;
	int sum = 0;

	res = 0;
	if (surfit_func) 
		res = 1;
	if (res + sum > i)
		return surfit_func;
	sum += res;

	res = surfit_funcs->size();
	if (res + sum > i)
		return (*surfit_funcs)[i-sum];
	sum += res;

	res = 0;
	if (surfit_wfunc) 
		res = 1;
	if (res + sum > i)
		return surfit_wfunc;
	sum += res;

	res = surfit_wfuncs->size();
	if (res + sum > i)
		return (*surfit_wfuncs)[i-sum];
	sum += res;

	res = 0;
	if (surfit_defarea) 
		res = 1;
	if (res + sum > i)
		return surfit_defarea;
	sum += res;

	res = surfit_defareas->size();
	if (res + sum > i)
		return (*surfit_defareas)[i-sum];
	sum += res;

	res = 0;
	if (surfit_trend) 
		res = 1;
	if (res + sum > i)
		return surfit_trend;
	sum += res;

	res = surfit_trends->size();
	if (res + sum > i)
		return (*surfit_trends)[i-sum];
	sum += res;
		
	res = 0;
	if (surfit_task) 
		res = 1;
	if (res + sum > i)
		return surfit_task;
	sum += res;

	res = surfit_tasks->size();
	if (res + sum > i)
		return (*surfit_tasks)[i-sum];
	sum += res;

	res = 0;
	if (surfit_wtask) 
		res = 1;
	if (res + sum > i)
		return surfit_wtask;
	sum += res;

	res = surfit_wtasks->size();
	if (res + sum > i)
		return (*surfit_wtasks)[i-sum];
	sum += res;

	res = 0;
	if (surfit_iso) 
		res = 1;
	if (res + sum > i)
		return surfit_iso;
	sum += res;

	res = surfit_isos->size();
	if (res + sum > i)
		return (*surfit_isos)[i-sum];
	sum += res;
	
	res = 0;
	if (surfit_wiso) 
		res = 1;
	if (res + sum > i)
		return surfit_wiso;
	sum += res;

	res = surfit_wisos->size();
	if (res + sum > i)
		return (*surfit_wisos)[i-sum];
	sum += res;
	
	res = 0;
	if (surfit_cntr) 
		res = 1;
	if (res + sum > i)
		return surfit_cntr;
	sum += res;

	res = surfit_cntrs->size();
	if (res + sum > i)
		return (*surfit_cntrs)[i-sum];
	sum += res;

	res = 0;
	if (surfit_wcntr) 
		res = 1;
	if (res + sum > i)
		return surfit_wcntr;
	sum += res;

	res = surfit_wcntrs->size();
	if (res + sum > i)
		return (*surfit_wcntrs)[i-sum];
	sum += res;

	res = 0;
	if (surfit_flt) 
		res = 1;
	if (res + sum > i)
		return surfit_flt;
	sum += res;

	res = surfit_flts->size();
	if (res + sum > i)
		return (*surfit_flts)[i-sum];
	sum += res;

	res = 0;
	if (surfit_area) 
		res = 1;
	if (res + sum > i)
		return surfit_area;
	sum += res;

	res = surfit_areas->size();
	if (res + sum > i)
		return (*surfit_areas)[i-sum];
	sum += res;

	res = 0;
	if (surfit_warea) 
		res = 1;
	if (res + sum > i)
		return surfit_warea;
	sum += res;

	res = surfit_wareas->size();
	if (res + sum > i)
		return (*surfit_wareas)[i-sum];
	sum += res;

	res = 0;
	if (surfit_curv) 
		res = 1;
	if (res + sum > i)
		return surfit_curv;
	sum += res;

	res = surfit_curvs->size();
	if (res + sum > i)
		return (*surfit_curvs)[i-sum];
	sum += res;

	return NULL;
};

#ifdef HAVE_GL_WORKS

void surfit_manager::mem_show() const {

	int pos;
	int size;

	// func
	if ( _func_check() )
		func_show();
	
	size = funcs_size();
	for (pos = 0; pos < size; pos++) {
		_func_show( funcs_at(pos), draw_func );
	};
	
	// wfunc
	if (draw_wfunc) {
		if ( _wfunc_check() )
			wfunc_show();
		
		size = wfuncs_size();
		for (pos = 0; pos < size; pos++) {
			_wfunc_show( wfuncs_at(pos) );
		};
	}

	// trend
	if (draw_trend) {
		if ( _trend_check() )
			trend_show();
		
		size = trends_size();
		for (pos = 0; pos < size; pos++) {
			_trend_show( trends_at(pos) );
		};
	}

	// defarea
	if (draw_defarea) {
		if ( _defarea_check() )
			defarea_show();
		
		size = defareas_size();
		for (pos = 0; pos < size; pos++) {
			_defarea_show( defareas_at(pos) );
		};
	}

	// task
	if (draw_task) {
		if ( _task_check() )
			task_show();
		
		size = tasks_size();
		for (pos = 0; pos < size; pos++) {
			_task_show( tasks_at(pos) );
		};
	}

	// wtask
	if (draw_wtask) {
		if ( _wtask_check() )
			wtask_show();
		
		size = wtasks_size();
		for (pos = 0; pos < size; pos++) {
			_wtask_show( wtasks_at(pos) );
		};
	}

	// iso
	if (draw_iso) {
		if ( _iso_check() )
			iso_show();
		
		size = isos_size();
		for (pos = 0; pos < size; pos++) {
			iso * isoline = isos_at(pos);
			_curv_show(isoline, "iso", 
				NULL, 
				isoline->value,
				iso_color_red,
				iso_color_green,
				iso_color_blue,
				iso_color_alpha);
		};
	}

	// curv
	if (draw_curv) {
		if ( _curv_check() )
			curv_show();
		
		size = curvs_size();
		for (pos = 0; pos < size; pos++) {
			curv * curvline = curvs_at(pos);
			_curv_show(curvline, 
				"curv", 
				NULL, 
				FLT_MAX,
				curv_color_red,
				curv_color_green,
				curv_color_blue,
				curv_color_alpha);
		};
	}

	// wiso 
	if (draw_wiso) {
		if ( _wiso_check() )
			wiso_show();
		
		size = wisos_size();
		for (pos = 0; pos < size; pos++) {
			wiso * wisoline = wisos_at(pos);
			_curv_show(wisoline, 
				"wiso",
				NULL, 
				wisoline->value,
				wiso_color_red,
				wiso_color_green,
				wiso_color_blue,
				wiso_color_alpha);
		};
	}

	// flt 
	if (draw_flt) {
		if ( _flt_check() )
			flt_show();
		
		size = flts_size();
		for (pos = 0; pos < size; pos++) {
			flt * fault = flts_at(pos);
			_curv_show(fault, 
				"flt", 
				NULL, 
				FLT_MAX,
				flt_color_red,
				flt_color_green,
				flt_color_blue,
				flt_color_alpha);
		};
	}

	// area
	if (draw_area) {
		if ( _area_check() )
			area_show();
		
		size = areas_size();
		for (pos = 0; pos < size; pos++) {
			area * ar = areas_at(pos);
			_curv_show(ar, "area", 
				NULL, ar->value,
				area_color_red,
				area_color_green,
				area_color_blue,
				area_color_alpha);
		};
	}

	// warea
	if (draw_warea) {
		if ( _warea_check() )
			warea_show();
		
		size = wareas_size();
		for (pos = 0; pos < size; pos++) {
			warea * ar = wareas_at(pos);
			_curv_show(ar, "warea", 
				NULL, ar->value,
				warea_color_red,
				warea_color_green,
				warea_color_blue,
				warea_color_alpha);
		};
	}

	// cntr
	if (draw_cntr) {
		if ( _cntr_check() )
			cntr_show();
		
		size = cntrs_size();
		for (pos = 0; pos < size; pos++) {
			cntr * ar = cntrs_at(pos);
			_cntr_show(ar, "cntr", NULL,
				cntr_color_red,
				cntr_color_green,
				cntr_color_blue,
				cntr_color_alpha);
		};
	}

	// wcntr
	if (draw_wcntr) {
		if ( _wcntr_check() )
			wcntr_show();
		
		size = wcntrs_size();
		for (pos = 0; pos < size; pos++) {
			wcntr * ar = wcntrs_at(pos);
			_cntr_show(ar, "wcntr", NULL,
				wcntr_color_red,
				wcntr_color_green,
				wcntr_color_blue,
				wcntr_color_alpha);
		};
	}

	// grid
	if (draw_grid) {
		if ( _grid_check() )
			grid_show();
	}

};

bool surfit_manager::check_for_drawing(const char * type) const {

	if ( strcmp(type,"isolines") == 0)
		return (isoline != 0);

	if ( strcmp(type,"grid") == 0) 
		return (draw_grid != 0);

	if ( strcmp(type,"task") == 0) 
		return (draw_task != 0);

	if ( strcmp(type,"wtask") == 0) 
		return (draw_wtask != 0);

	if ( strcmp(type,"func") == 0) 
		return (draw_func != 0);

	if ( strcmp(type,"wfunc") == 0) 
		return (draw_wfunc != 0);

	if ( strcmp(type,"trend") == 0) 
		return (draw_trend != 0);

	if ( strcmp(type,"iso") == 0) 
		return (draw_iso != 0);

	if ( strcmp(type,"wiso") == 0) 
		return (draw_wiso != 0);
	
	if ( strcmp(type,"cntr") == 0) 
		return (draw_cntr != 0);

	if ( strcmp(type,"wcntr") == 0) 
		return (draw_wcntr != 0);
		
	if ( strcmp(type,"area") == 0) 
		return (draw_area != 0);

	if ( strcmp(type,"warea") == 0) 
		return (draw_warea != 0);

	if ( strcmp(type,"flt") == 0) 
		return (draw_flt != 0);

	if ( strcmp(type,"curv") == 0) 
		return (draw_curv != 0);

	if ( strcmp(type,"grid") == 0) 
		return (draw_grid != 0);

	if ( strcmp(type,"defarea") == 0) 
		return (draw_defarea != 0);

	return true;

};

void surfit_manager::getMinMaxZ(REAL & minz, REAL & maxz) const {
	
	REAL minZ, maxZ;
	if (surfit_func) {
		surfit_func->getMinMaxZ(minZ, maxZ);
		minz = MIN(minZ, maxZ);
		maxz = MAX(minZ, maxZ);
	}
			
	if (surfit_funcs) {
		func * fnc;
		int i;
		for (i = 0; i < funcs_size(); i++) {
			fnc = funcs_at(i);
			fnc->getMinMaxZ(minZ, maxZ);
			minz = MIN(minZ, maxZ);
			maxz = MAX(minZ, maxZ);
		}
	}
	
	if (surfit_trend) {
		surfit_trend->getMinMaxZ(minZ, maxZ);
		minz = MIN(minZ, maxZ);
		maxz = MAX(minZ, maxZ);
	}

	if (surfit_trends) {
		trend * fnc;
		int i;
		for (i = 0; i < trends_size(); i++) {
			fnc = trends_at(i);
			fnc->getMinMaxZ(minZ, maxZ);
			minz = MIN(minZ, maxZ);
			maxz = MAX(minZ, maxZ);
		}
	}

	if (surfit_task) {
		surfit_task->getMinMaxZ(minZ, maxZ);
		minz = MIN(minZ, maxZ);
		maxz = MAX(minZ, maxZ);
	}



};

#endif

///////////////////////
//
// Tcl functions
//
//////////////////////

void clear_data() {

	if (surfit_data_manager)
		surfit_data_manager->clear_data();

};

void mem_info() {

	if (surfit_data_manager)
		surfit_data_manager->mem_info();

};

#ifdef HAVE_GL_WORKS
void mem_show() {

	if (surfit_data_manager)
		surfit_data_manager->mem_show();

};
#endif

void file_load(const char * filename) {

	datafile *df = new datafile(filename, DF_MODE_READ, get_rw_mode()); // write
	
	if (!df->condition()) {
		delete df;
		return;
	}

	if (surfit_data_manager)
		surfit_data_manager->load(df);
	

	delete df;

};

bool file_save(const char * filename) {

	bool res = true;
	bool op = true;
	
	datafile *df = new datafile(filename, DF_MODE_WRITE, get_rw_mode()); // write
	if (!df->condition())
		return false;

	
	if (surfit_data_manager)
		res = surfit_data_manager->save(df);
	

	op = df->writeEof(); res = (op && res);

	delete df;
	return res;

};

#ifdef HAVE_GL_WORKS
void file_show(const char * filename) {

	file_load(filename);
	mem_show();
};
#endif


}; // namespace surfit;

