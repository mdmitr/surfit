
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
#include "grid_user.h"
#include "points.h"

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
	match_cntr_write(const char * ifilename, const char * ipos, const char * idelimiter) : filename(ifilename), pos(ipos), delimiter(idelimiter), res(NULL), first(false) {};
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
			if (first == false)
				fileio_append = false;
			else
				fileio_append = true;
			res->push_back( _cntr_write(cntr, filename, buf) );
			first = true;
		}
	}
	const char * filename;
	const char * pos;
	const char * delimiter;
	boolvec * res;
	bool first;
};

boolvec * cntr_write(const char * filename, const char * pos, const char * delimiter) 
{
	match_cntr_write qq(filename, pos, delimiter);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	fileio_append = false;
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

boolvec * cntr_to_curv(const char * pos) 
{
	boolvec * res = create_boolvec();
	size_t i;
	for (i = 0; i < surfit_cntrs->size(); i++)
	{
		d_cntr * cntr = (*surfit_cntrs)[i];
		if (StringMatch(pos, cntr->getName()) == false)
			continue;
		writelog(LOG_MESSAGE,"converting contour \"%s\" to curve", cntr->getName());
		d_curv * curv = create_curv(cntr);
		surfit_curvs->push_back(curv);
		res->push_back(true);
	}
	return res;
};

boolvec * cntr_to_pnts(REAL step, const char * pos) 
{
	boolvec * res = create_boolvec();
	size_t i;
	for (i = 0; i < surfit_cntrs->size(); i++)
	{
		d_cntr * cntr = (*surfit_cntrs)[i];
		if (StringMatch(pos, cntr->getName()) == false)
			continue;
		writelog(LOG_MESSAGE,"converting contour \"%s\" to points", cntr->getName());
		d_points * pnts = discretize_cntr(cntr, step, cntr->getName());
		if (pnts) {
			surfit_pnts->push_back(pnts);
			res->push_back(true);
		} else {
			res->push_back(false);
		}
		
	}
	return res;
};

struct match_cntr_setName
{
	match_cntr_setName(const char * inew_name, const char * ipos) : new_name(inew_name), pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			cntr->setName(new_name);
			res->push_back(true);
		}
	}
	const char * new_name;
	const char * pos;
	boolvec * res;
};

boolvec * cntr_setName(const char * new_name, const char * pos) 
{
	match_cntr_setName qq(new_name, pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

struct match_cntr_getName
{
	match_cntr_getName(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( cntr->getName() );
		}
	}
	const char * pos;
	strvec * res;
};

strvec * cntr_getName(const char * pos) 
{
	match_cntr_getName qq(pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

const char * cntr_getNameAt(int pos)
{
	if ((size_t)pos > surfit_cntrs->size())
		return NULL;
	return (*surfit_cntrs)[pos]->getName();
};

struct match_cntr_getId
{
	match_cntr_getId(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( cntr->getId() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * cntr_getId(const char * pos) 
{
	match_cntr_getId qq(pos);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

void cntr_del(const char * pos) 
{
	if (surfit_cntrs->size() == 0)
		return;
	size_t i;
	for (i = surfit_cntrs->size()-1; i >= 0; i--)
	{
		d_cntr * cntr = (*surfit_cntrs)[i];
		if ( StringMatch(pos, cntr->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing contour \"%s\" from memory", cntr->getName());
			cntr->release();
			surfit_cntrs->erase(surfit_cntrs->begin()+i);
		}
		if (i == 0)
			break;
	}
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

struct match_cntr_smooth
{
	match_cntr_smooth(const char * ipos, size_t icnt) : pos(ipos), res(NULL), cnt(icnt) {};
	void operator()(d_cntr * cntr)
	{
		if ( StringMatch(pos, cntr->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Smoothing contour \"%s\"", cntr->getName());
			size_t i;
			bool r = true;

			// first remove dupe points
			cntr->normalize();

			// now call 'cnt' times _cntr_smooth
			for (i = 0; i < cnt; i++) {
				r = _cntr_smooth(cntr) && r;
			}
			res->push_back( r );
		}
	}
	const char * pos;
	boolvec * res;
	size_t cnt;
};

boolvec * cntr_smooth(const char * pos, size_t cnt) 
{
	match_cntr_smooth qq(pos, cnt);
	qq = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), qq);
	return qq.res;
};

}; // namespace surfit;

