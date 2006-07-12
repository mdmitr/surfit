
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

#include "curv.h"
#include "curv_io.h"

#include <errno.h>

namespace surfit {

bool curv_load_bln(const char * filename) {
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
		surfit_curvs->push_back(crv);
		crv = _curv_load_bln(file, orient);
	}

	fclose(file);
	return res;
};

bool curv_load_shp(const char * filename, const char * curvname) {
	d_curv * curve = _curv_load_shp(filename, curvname);
	if (curve) {
		surfit_curvs->push_back(curve);
		return false;
	}
	return true;
};

bool curvs_load_shp(const char * filename) {
	return _curvs_load_shp(filename);
};

bool curv_save_bln(const char * filename, const char * curv_pos, int orient) {
	d_curv * crv = get_element<d_curv>(curv_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;

	FILE * file = fopen(filename, "a");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "saving BLN: file error.");
		fclose(file);
		return false;
	}

	bool res = _curv_save_bln(crv, file, orient);
	fclose(file);

	return res;
};

bool curv_save_shp(const char * filename, const char * pos) {
	d_curv * curve = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	writelog(LOG_MESSAGE,"Saving curv to ERSI shp file %s", filename);

	return _curv_save_shp(curve, filename);
};



}; // namespace surfit;


