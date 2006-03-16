
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

#include "curv.h"
#include "curv_tcl.h"
#include "curv_internal.h"
#include "variables_internal.h"
#include "free_elements.h"

#include <errno.h>

namespace surfit {

bool curv_read(const char * filename, const char * curvname,
	       int col1, int col2,
	       const char* delimiter, int skip_lines, int grow_by)
{
	d_curv * curve = _curv_read(filename, curvname,
				    col1, col2, skip_lines,
				    grow_by, delimiter);

	if (curve != NULL) {
		surfit_curvs->push_back(curve);
		return true;
	}
	return false;

};

bool curv_read_bln(const char * filename) {
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
	d_curv * crv = _curv_read_bln(file, orient);
	while (crv != NULL) {
		res = true;
		surfit_curvs->push_back(crv);
		crv = _curv_read_bln(file, orient);
	}

	fclose(file);
	return res;
};

bool curv_write(const char * filename, const char * pos, const char * delimiter) 
{
	d_curv * curve = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _curv_write(curve, filename, buf);
};

bool curv_write_bln(const char * filename, const char * curv_pos, int orient) {
	d_curv * crv = get_element<d_curv>(curv_pos, surfit_curvs->begin(), surfit_curvs->end());
	if (crv == NULL)
		return false;

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

	bool res = _curv_write_bln(crv, file, orient);
	fclose(file);

	return res;
};

bool curv_save(const char * filename, const char * pos) {
	d_curv * curve = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;

	writelog(LOG_MESSAGE,"Saving curv to file %s", filename);

	return _curv_save(curve, filename);
};

bool curv_load(const char * filename, const char * curvname) {
	d_curv * curve = _curv_load(filename, curvname);
	if (curve) {
		surfit_curvs->push_back(curve);
		return false;
	}
	return true;
};

bool curv_setName(const char * new_name, const char * pos) {
	d_curv * curve = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;
	curve->setName(new_name);
	return true;
};

const char * curv_getName(const char * pos) {
	d_curv * curve = get_element<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == NULL)
		return false;
	return curve->getName();
};

bool curv_delall() {
	if (surfit_curvs->size() == 0) {
		//writelog(SURFIT_WARNING,"curvs_delall : empty surfit_curvs");
		return false;
	}

	release_elements(surfit_curvs->begin(), surfit_curvs->end());
	surfit_curvs->resize(0);
	return true;
};

bool curv_del(const char * pos) {
	std::vector<d_curv *>::iterator curve = get_iterator<d_curv>(pos, surfit_curvs->begin(), surfit_curvs->end());
	if (curve == surfit_curvs->end())
		return false;
	if (*curve)
		(*curve)->release();
	surfit_curvs->erase(curve);
	return true;
};

int curv_size() {
	return surfit_curvs->size();
};

void curvs_info() {
	unsigned int curvs_counter;
	for (curvs_counter = 0; curvs_counter < surfit_curvs->size(); curvs_counter++) {
		d_curv * a_curv = *(surfit_curvs->begin()+curvs_counter);
		_curv_info(a_curv);
	}
};

}; // namespace surfit;
