
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

#include "flow_ie.h"
#include "flow_file_manager.h"

// delete this include!!!
#include "iso_show.h"
#include "area_show.h"
#include "cntr_show.h"

#include "ptask.h"
#include "ptask_internal.h"
#include "ptask_tcl.h"
#include "ptasks.h"
#include "ptask_show.h"
#include "parea.h"
#include "parea_internal.h"
#include "parea_tcl.h"
#include "pareas.h"
#include "pcntr.h"
#include "pcntr_internal.h"
#include "pcntr_tcl.h"
#include "pcntrs.h"
#include "piso.h"
#include "piso_internal.h"
#include "piso_tcl.h"
#include "pisos.h"
#include "flow_curv_show.h"
#include "curv_show.h"
#include "datafile.h"
#include "flow_variables.h"
#include "lcm_simple_tcl.h"
#include "colors.h"

#include "ptask_user.h"
#include "piso_user.h"
#include "pcntr_user.h"
#include "parea_user.h"

#ifdef HAVE_GL_WORKS
#include "ptask_show.h"
#include "parea_show.h"
#include "piso_show.h"
#include "pcntr_show.h"
#endif

namespace surfit {

void freeflow_manager::release() {
	delete this;
};

int freeflow_manager::load_tag(datafile * df, char * tagname) const {
		
	if (strcmp(tagname, "ptask") == 0) {
		
		ptask * res = _ptask_load_df(df, NULL);
		
		if (res) {
			if (!flow_ptask)
				flow_ptask = res;
			else
				flow_ptasks->push_back(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
	
	if (strcmp(tagname, "pcntr") == 0) {
		
		pcntr * res = _pcntr_load_df(df, NULL);
		if (res)
			flow_pcntrs->push_back(res);
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}

	if (strcmp(tagname, "piso") == 0) {
		
		piso * res = _piso_load_df(df, NULL);
		if (res)
			flow_pisos->push_back(res);
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}

	if (strcmp(tagname, "parea") == 0) {
		
		parea * res = _parea_load_df(df, NULL);
		if (res)
			flow_pareas->push_back(res);
		
		if ( !df->readTagName(tagname) ) 
			return -1;
		
		return 1;
	}
		
	return 0;
}

bool freeflow_manager::save(datafile *df) const {

	unsigned int cnt;

	if (flow_ptask) {
		if (!_ptask_save_df(flow_ptask, df))
			return false;
	}

	for (cnt = 0; cnt < flow_ptasks->size(); cnt++) {
		ptask * ptsk = *(flow_ptasks->begin()+cnt);
		if (!_ptask_save_df(ptsk, df))
			return false;
	}

	if (flow_pcntr) {
		if (!_pcntr_save_df(flow_pcntr, df))
			return false;
	}

	for (cnt = 0; cnt < flow_pcntrs->size(); cnt++) {
		pcntr * pcntrline = *(flow_pcntrs->begin()+cnt);
		if (!_pcntr_save_df(pcntrline, df))
			return false;
	}

	if (flow_parea) {
		if (!_parea_save_df(flow_parea, df))
			return false;
	}

	for (cnt = 0; cnt < flow_pareas->size(); cnt++) {
		parea * parealine = *(flow_pareas->begin()+cnt);
		if (!_parea_save_df(parealine, df))
			return false;
	}
	
	if (flow_piso) {
		if (!_piso_save_df(flow_piso, df))
			return false;
	}

	for (cnt = 0; cnt < flow_pisos->size(); cnt++) {
		piso * pisoline = *(flow_pisos->begin()+cnt);
		if (!_piso_save_df(pisoline, df))
			return false;
	}

	return true;

};

void freeflow_manager::clear_data() const {
	
	ptask_unload();
	ptasks_delall();
	
	parea_unload();
	pareas_delall();
	
	pcntr_unload();
	pcntrs_delall();

	piso_unload();
	pisos_delall();

	lcm_simple_unload();
};

void freeflow_manager::mem_info() const {
	
	ptasks_info();
	pareas_info();
	pcntrs_info();
	pisos_info();
	lcm_simple_info();
};

#ifdef HAVE_GL_WORKS
void freeflow_manager::mem_show() const {

	int pos;
	int size;

	// ptask
	if ( _ptask_check() )
		ptask_show();

	size = ptasks_size();
	for (pos = 0; pos < size; pos++) {
		_ptask_show( ptasks_at(pos) );
	};

	// piso 
	if (draw_piso) {
		if ( _piso_check() )
			piso_show();
		
		size = pisos_size();
		for (pos = 0; pos < size; pos++) {
			piso * pisoline = pisos_at(pos);
			_curv_show(pisoline, 
				"piso",
				NULL, 
				FLT_MAX, //pisoline->value,
				piso_color_red,
				piso_color_green,
				piso_color_blue,
				piso_color_alpha);
		};
	}

	// parea
	if (draw_parea) {
		if ( _parea_check() )
			parea_show();
		
		size = pareas_size();
		for (pos = 0; pos < size; pos++) {
			parea * ar = pareas_at(pos);
			_curv_show(ar, "parea", 
				NULL, 
				FLT_MAX, //ar->value,
				parea_color_red,
				parea_color_green,
				parea_color_blue,
				parea_color_alpha);
		};
	}

	// pcntr
	if (draw_pcntr) {
		if ( _pcntr_check() )
			pcntr_show();
		
		size = pcntrs_size();
		for (pos = 0; pos < size; pos++) {
			pcntr * ar = pcntrs_at(pos);
			_cntr_show(ar, "pcntr", NULL,
				cntr_color_red,
				cntr_color_green,
				cntr_color_blue,
				cntr_color_alpha);
		};
	}

};

bool freeflow_manager::check_for_drawing(const char * type) const {

	if ( strcmp(type,"ptask") == 0) 
		return (draw_ptask != 0);

	if ( strcmp(type,"piso") == 0) 
		return (draw_piso != 0);

	if ( strcmp(type,"pcntr") == 0) 
		return (draw_pcntr != 0);

	if ( strcmp(type,"parea") == 0) 
		return (draw_parea != 0);

	return true;

};

void freeflow_manager::getMinMaxZ(REAL & minz, REAL & maxz) const {
	
//	REAL minZ, maxZ;
	return;
};


#endif

int freeflow_manager::data_count() const {
	int res = 0;

	if (flow_ptask) 
		res++;
	res += flow_ptasks->size();

	if (flow_parea) 
		res++;
	res += flow_pareas->size();

	if (flow_pcntr)
		res++;
	res += flow_pcntrs->size(); 

	if (flow_piso) 
		res++;
	res += flow_pisos->size();

	return res;
};

const data * freeflow_manager::data_get(int i) const {
	
	int res = 0;
	int sum = 0;

	res = 0;
	if (flow_ptask) 
		res = 1;
	if (res + sum > i)
		return flow_ptask;
	sum += res;

	res = flow_ptasks->size();
	if (res + sum > i)
		return (*flow_ptasks)[i-sum];
	sum += res;

	res = 0;
	if (flow_parea) 
		res = 1;
	if (res + sum > i)
		return flow_parea;
	sum += res;

	res = flow_pareas->size();
	if (res + sum > i)
		return (*flow_pareas)[i-sum];
	sum += res;

	res = 0;
	if (flow_pcntr) 
		res = 1;
	if (res + sum > i)
		return flow_pcntr;
	sum += res;

	res = flow_pcntrs->size();
	if (res + sum > i)
		return (*flow_pcntrs)[i-sum];
	sum += res;

	res = 0;
	if (flow_piso) 
		res = 1;
	if (res + sum > i)
		return flow_piso;
	sum += res;

	res = flow_pisos->size();
	if (res + sum > i)
		return (*flow_pisos)[i-sum];
	sum += res;

	return NULL;
};


}; // namespace surfit;

