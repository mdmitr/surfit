
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
#include "findfile.h"
#include "strvec.h"
#include "boolvec.h"
#include "intvec.h"

#include "cntr.h"
#include "cntr_tcl.h"
#include "curv_tcl.h"
#include "cntr_internal.h"
#include "variables_internal.h"
#include "free_elements.h"

#include <algorithm>

namespace surfit {

boolvec * cntr_read(const char * filename, const char * cntrname,
	       int col1, int col2, int col3,
	       const char* delimiter, int skip_lines, int grow_by)
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {

		d_cntr * contour = _cntr_read(fname, cntrname,
			col1, col2, col3, skip_lines,
			grow_by, delimiter);

		if (contour != NULL) {
			surfit_cntrs->push_back(contour);
			res->push_back(true);
			
		} else
			res->push_back(false);

		fname = find_next();
	}

	find_close();
	return res;
};

boolvec * cntr_load(const char * filename, const char * cntrname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_cntr * contour = _cntr_load(fname, cntrname);
		if (contour) {
			surfit_cntrs->push_back(contour);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();
	}

	find_close();
	return res;
};

struct match_cntr_write
{
	match_cntr_write(const char * ifilename, const char * ipos, const char * idelimiter) : filename(ifilename), pos(ipos), delimiter(idelimiter), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			char buf[80];
			strcpy( buf, "%lf" );
			strcat( buf, delimiter );
			strcat( buf, "%lf" );
			strcat( buf, delimiter );
			strcat( buf, "%lf\n" );
			res->push_back( _cntr_write(cntr, filename, buf) );
		}
	}
	const char * filename;
	const char * pos;
	const char * delimiter;
	boolvec * res;
};

boolvec * cntr_write(const char * filename, const char * pos, const char * delimiter) 
{
	match_cntr_write qq(filename, pos, delimiter);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_cntr_save
{
	match_cntr_save(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Saving cntr to file %s", filename);
			res->push_back( _cntr_save(cntr, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * cntr_save(const char * filename, const char * pos) 
{
	match_cntr_save qq(filename, pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_cntr_plus_real
{
	match_cntr_plus_real(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Increasing contour \"%s\" Z-values at %lf", cntr->getName(), value);
			cntr->plus(value);
		}
	}
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec * cntr_plus_real(REAL value, const char * pos) 
{
	match_cntr_plus_real qq(value, pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_cntr_minus_real
{
	match_cntr_minus_real(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Decreasing contour \"%s\" Z-values at %lf", cntr->getName(), value);
			cntr->minus(value);
		}
	}
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec * cntr_minus_real(REAL value, const char * pos) 
{
	match_cntr_minus_real qq(value, pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_cntr_mult_real
{
	match_cntr_mult_real(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Multiplying contour \"%s\" Z-values at %lf", cntr->getName(), value);
			cntr->mult(value);
		}
	}
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec * cntr_mult_real(REAL value, const char * pos) 
{
	match_cntr_mult_real qq(value, pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_cntr_div_real
{
	match_cntr_div_real(REAL ivalue, const char * ipos) : value(ivalue), pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Dividing contour \"%s\" Z-values at %lf", cntr->getName(), value);
			cntr->div(value);
		}
	}
	REAL value;
	const char * pos;
	boolvec * res;
};

boolvec * cntr_div_real(REAL value, const char * pos) 
{
	match_cntr_div_real qq(value, pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
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

