
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "surfit_ie.h"

#include "datafile.h"
#include "fileio.h"

#include "grid_line.h"
#include "grid_line_internal.h"
#include "grid_line_tcl.h"
#include "grid_internal.h"
#include "variables_internal.h"
#include "cntr.h"
#include "curv.h"
#include "mask.h"
#include "grid.h"
#include "boolvec.h"

#include "data_manager.h"
#include "variables.h"

#include "grid_user.h"
#include "grid_line_user.h"

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
	return _grid_line_write(surfit_grid_line, surfit_grid, filename, buf);
};

bool grid_line_save(const char * filename, const char * grid_linename) {
	if (!_grid_line_check()) 
		return false;

	writelog(LOG_MESSAGE,"Saving grid_line to file %s", filename);

	if (grid_linename)
		surfit_grid_line->setName(grid_linename);

	return _grid_line_save(surfit_grid_line, surfit_grid, filename);
};

bool grid_line_unload() {
	if (surfit_grid_line) {
		surfit_grid_line->release();
		surfit_grid_line = NULL;
		return true;
	};
	return false;
};

bool trace_grid_line() {

	if (surfit_grid_line) {
		surfit_grid_line->release();
		surfit_grid_line = NULL;
	}

	int cnt = surfit_data_manager->data_count();
	int i;
	for (i = 0; i < cnt; i++) {
		const data * dat = surfit_data_manager->data_get(i);
		if (!dat)
			continue;
		const d_curv * crv = NULL;
		try {
			crv = dynamic_cast<const d_curv *>(dat);
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

}; // namespace surfit;


