
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
#include "grid_line.h"
#include "grid_line_internal.h"
#include "grid_line_tcl.h"
#include "fileio.h"
#include "grid_internal.h"
#include "flt_internal.h"
#include "variables_internal.h"
#include "flt.h"
#include "iso.h"
#include "wiso.h"
#include "area.h"
#include "warea.h"
#include "cntr.h"
#include "wcntr.h"
#include "curv.h"
#include "defarea.h"
#include "grid.h"
#include "boolvec.h"

#include "file_manager.h"
#include "variables.h"

#include "grid_user.h"
#include "grid_line_user.h"
#include "flt_user.h"
#include "iso_user.h"
#include "wiso_user.h"
#include "area_user.h"
#include "warea_user.h"
#include "cntr_user.h"
#include "wcntr_user.h"
#include "curv_user.h"
#include "defarea_user.h"


#include <vector>

namespace surfit {

bool grid_line_check() {
	return (surfit_grid_line != NULL);
};
	
bool grid_line_write(const char * filename, const char * delimiter) {
	if (!_grid_line_check())
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _grid_line_write(surfit_grid_line, filename, buf);
};

bool grid_line_save(const char * filename, const char * grid_linename) {
	if (!_grid_line_check()) 
		return false;

	writelog(SURFIT_MESSAGE,"Saving grid_line to file %s", filename);

	if (grid_linename)
		surfit_grid_line->setName(grid_linename);

	return _grid_line_save(surfit_grid_line, filename, get_rw_mode());
};

bool grid_line_unload() {
	if (surfit_grid_line) {
		delete surfit_grid_line;
		surfit_grid_line = NULL;
		return true;
	};
	return false;
};

bool trace_grid_line() {

	if (surfit_grid_line) {
		delete surfit_grid_line;
		surfit_grid_line = NULL;
	}

	int cnt = surfit_data_manager->data_count();
	int i;
	for (i = 0; i < cnt; i++) {
		const data * dat = surfit_data_manager->data_get(i);
		if (!dat)
			continue;
		const curv * crv = NULL;
		try {
			crv = dynamic_cast<const curv*>(dat);
		} catch (...) {
			continue;
		}
		if (!crv)
			continue;
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, crv, surfit_grid);
	}

/*
	unsigned int i;

	if (surfit_iso)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_iso, surfit_grid);

	for (i = 0; i < surfit_isos->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_isos)[i], surfit_grid);
	}

	if (surfit_wiso)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_wiso, surfit_grid);

	for (i = 0; i < surfit_wisos->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_wisos)[i], surfit_grid);
	}

	if (surfit_flt)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_flt, surfit_grid);

	for (i = 0; i < surfit_flts->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_flts)[i], surfit_grid);
	}

	if (surfit_area)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_area, surfit_grid);

	for (i = 0; i < surfit_areas->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_areas)[i], surfit_grid);
	}
	
	if (surfit_warea)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_warea, surfit_grid);

	for (i = 0; i < surfit_wareas->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_wareas)[i], surfit_grid);
	}

	if (surfit_cntr)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_cntr, surfit_grid);

	for (i = 0; i < surfit_cntrs->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_cntrs)[i], surfit_grid);
	}

	if (surfit_wcntr)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_wcntr, surfit_grid);

	for (i = 0; i < surfit_wcntrs->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_wcntrs)[i], surfit_grid);
	}

	if (surfit_curv)
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, surfit_curv, surfit_grid);

	for (i = 0; i < surfit_curvs->size(); i++) {
		surfit_grid_line = curv_to_grid_line(surfit_grid_line, (*surfit_curvs)[i], surfit_grid);
	}
	*/

	return true;
};

bool grid_line_fill_true(REAL x, REAL y) {

	if (!_grid_check())
		return false;
	if (!_grid_line_check())
		return false;

	int i,j;
	i = surfit_grid->get_i(x);
	j = surfit_grid->get_j(y);

	int pos = i + j*surfit_grid->getCountX();
	int size = surfit_grid->getCountX()*surfit_grid->getCountY();

	if ((pos < 0) || (pos >= size)) {
		writelog(SURFIT_ERROR,"grid_line_fill_true : node is out of surfit_grid");
		return false;
	}

	boolvec * coeff = new boolvec(size);
	flood_fill_boolvec(surfit_grid, surfit_grid_line, coeff, pos, NULL);

	surfit_defarea = new defarea(coeff, new grid(surfit_grid));

	return true;

};

}; // namespace surfit;


