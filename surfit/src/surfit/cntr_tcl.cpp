
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

#include "cntr.h"
#include "cntr_tcl.h"
#include "curv_tcl.h"
#include "cntr_internal.h"
#include "variables_internal.h"
#include "free_elements.h"

namespace surfit {

bool cntr_read(const char * filename, const char * cntrname,
	       int col1, int col2, int col3,
	       const char* delimiter, int skip_lines, int grow_by)
{

	d_cntr * contour = _cntr_read(filename, cntrname,
				      col1, col2, col3, skip_lines,
				      grow_by, delimiter);

	if (contour != NULL) {
		surfit_cntrs->push_back(contour);
		return true;
	}
	return false;

};

bool cntr_load(const char * filename, const char * cntrname) {
	
	d_cntr * contour = _cntr_load(filename, cntrname);
	if (contour) {
		surfit_cntrs->push_back(contour);
		return true;
	}
	return false;
};

bool cntr_load_shp(const char * filename, const char * cntrname) {
	
	d_cntr * contour = _cntr_load_shp(filename, cntrname);
	if (contour) {
		surfit_cntrs->push_back(contour);
		return true;
	}
	return false;
};

bool cntrs_load_shp(const char * filename) {
	return _cntrs_load_shp(filename);
};

bool cntr_write(const char * filename, const char * pos, const char * delimiter) 
{
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf\n" );
	return _cntr_write(contour, filename, buf);
};

bool cntr_save(const char * filename, const char * pos) {

	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	
	writelog(LOG_MESSAGE,"Saving cntr to file %s", filename);

	return _cntr_save(contour, filename);
};

bool cntr_save_shp(const char * filename, const char * pos) {

	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	
	writelog(LOG_MESSAGE,"Saving cntr to ESRI shape file %s", filename);

	return _cntr_save_shp(contour, filename);
};

bool cntr_plus_real(REAL value, const char * pos) {
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	writelog(LOG_MESSAGE,"Increasing cntr Z-values at %lf", value);
	contour->plus(value);
	return true;
};

bool cntr_minus_real(REAL value, const char * pos) {
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	writelog(LOG_MESSAGE,"Decreasing cntr Z-values at %lf", value);
	contour->minus(value);
	return true;
};

bool cntr_mult_real(REAL value, const char * pos) {
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	writelog(LOG_MESSAGE,"Multiplying cntr Z-values at %lf", value);
	contour->mult(value);
	return true;
};

bool cntr_div_real(REAL value, const char * pos) {
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	writelog(LOG_MESSAGE,"Dividing cntr Z-values at %lf", value);
	contour->div(value);
	return true;
};

bool cntr_to_curv(const char * pos) {
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	std::vector<d_cntr *>::iterator pcontour = get_iterator<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	surfit_cntrs->erase(pcontour);
	surfit_curvs->push_back(contour);
	return true;
};

bool cntr_setName(const char * new_name, const char * pos) {
	
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	contour->setName(new_name);
	return true;
};

const char * cntr_getName(const char * pos) {
	d_cntr * contour = get_element<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == NULL)
		return false;
	return contour->getName();
};

bool cntr_delall() {

	if (surfit_cntrs == NULL)
		return false;

	if (surfit_cntrs->size() == 0) {
		//writelog(SURFIT_WARNING,"cntrs_delall : empty surfit_cntrs");
		return false;
	}

	release_elements(surfit_cntrs->begin(), surfit_cntrs->end());
	surfit_cntrs->resize(0);
	return true;
};

bool cntr_del(const char * pos) {
	std::vector<d_cntr *>::iterator contour = get_iterator<d_cntr>(pos, surfit_cntrs->begin(), surfit_cntrs->end());
	if (contour == surfit_cntrs->end())
		return false;
	if (*contour)
		(*contour)->release();
	surfit_cntrs->erase(contour);
	return true;
};

int cntr_size() {
	return surfit_cntrs->size();
};

void cntrs_info() {
	size_t cntrs_counter;
	for (cntrs_counter = 0; cntrs_counter < surfit_cntrs->size(); cntrs_counter++) {
		d_cntr * a_cntr = *(surfit_cntrs->begin()+cntrs_counter);
		_cntr_info(a_cntr);
	}
};

}; // namespace surfit;

