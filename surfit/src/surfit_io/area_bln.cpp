
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

#include "surfit_io_ie.h"
#include "surf_io.h"

// sstuff includes
#include "sstuff.h"
#include "boolvec.h"
#include "vec.h"

// surfit includes
#include "curv.h"
#include "curv_io.h"
#include "area.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "grid.h"

#include <errno.h>

namespace surfit {

bool _area_save_bln(const d_area * area, const char * filename) {
	
	FILE * file = fopen(filename, "a");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "writing BLN: file error.");
		fclose(file);
		return false;
	}

	writelog(LOG_MESSAGE,"writing area (%s) to bln file %s", area->getName(), filename);

	bool res = true;

	int i;
	for (i = 0; i < area->size(); i++) {
		const d_curv * crv = area->get_curv(i);
		res = _curv_save_bln(crv, file, area->get_curv_orient(i));
		if (res == false)
			break;
	}
	fclose(file);

	return res;

};

d_area * _area_load_bln(const char * filename, const char * areaname) {
	
	d_area * area_res = NULL;
	std::vector<d_curv *> * area_data = new std::vector<d_curv *>;
	boolvec * orients = create_boolvec();

	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "loading from BLN: file error.");
		fclose(file);
		return false;
	}

	bool res = false;

	int orient = 1;
	d_curv * crv = _curv_load_bln(file, orient);
	while (crv != NULL) {
		res = true;
		crv->close();
		area_data->push_back(crv);
		orients->push_back(orient != 0);
		orient = 1;
		crv = _curv_load_bln(file, orient);
	}

	fclose(file);

	if (area_data->size() == 0)
		return area_res;

	area_res = create_area(area_data, orients, areaname);
	return area_res;
};


};

