
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
#include "sstuff.h"
#include "boolvec.h"
#include "strvec.h"
#include "intvec.h"

#include "curv.h"
#include "curv_tcl.h"
#include "curv_internal.h"
#include "cntr.h"
#include "variables_internal.h"
#include "free_elements.h"

#include <errno.h>
#include <algorithm>

namespace surfit {

boolvec * curv_read(const char * filename, const char * curvname,
	       int col1, int col2,
	       const char* delimiter, int skip_lines, int grow_by)
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);
	
	while (fname) {
		
		d_curv * curve = _curv_read(fname, curvname,
					    col1, col2, skip_lines,
					    grow_by, delimiter);
		
		if (curve != NULL) {
			if (curvname == NULL) 
			{
				char * name = get_name(fname);
				curve->setName( name );
				sstuff_free_char(name);
			}
			surfit_curvs->push_back(curve);
			res->push_back(true);
		} else {
			res->push_back(false);
		}

		fname = find_next();
		
	}

	find_close();
	return res;
};

boolvec * curv_load(const char * filename, const char * curvname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_curv * curve = _curv_load(fname, curvname);
		if (curve) {
			surfit_curvs->push_back(curve);
			res->push_back(true);
		} else
			res->push_back(false);
	}

	return res;
};

struct match_curv_write
{
	match_curv_write(const char * ifilename, const char * ipos, const char * idelimiter) : filename(ifilename), pos(ipos), delimiter(idelimiter), res(NULL) {};
	void operator()(d_curv * curv)
	{
		if ( StringMatch(pos, curv->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			char buf[80];
			strcpy( buf, "%lf" );
			strcat( buf, delimiter );
			strcat( buf, "%lf\n" );
			res->push_back( _curv_write(curv, filename, buf) );;
		}
	}
	const char * filename;
	const char * pos;
	const char * delimiter;
	boolvec * res;
};

boolvec * curv_write(const char * filename, const char * pos, const char * delimiter) 
{
	match_curv_write qq(filename, pos, delimiter);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curv_save {
	match_curv_save(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {}
	void operator()(d_curv * curv)
	{
		if ( StringMatch(pos, curv->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Saving curv to file %s", filename);
			res->push_back( _curv_save(curv, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};
boolvec * curv_save(const char * filename, const char * pos) 
{
	match_curv_save qq(filename, pos);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curv_setName
{
	match_curv_setName(const char * inew_name, const char * ipos) : new_name(inew_name), pos(ipos), res(NULL) {};
	void operator()(d_curv * curv)
	{
		if ( StringMatch(pos, curv->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			curv->setName( new_name );
			res->push_back(true);
		}
	}
	const char * new_name; 
	const char * pos;
	boolvec * res;
};

boolvec * curv_setName(const char * new_name, const char * pos) 
{
	match_curv_setName qq(new_name, pos);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

struct match_curv_getName
{
	match_curv_getName(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_curv * curv)
	{
		if ( StringMatch(pos, curv->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( curv->getName() );
		}
	}
	const char * pos;
	strvec * res;
};

strvec * curv_getName(const char * pos) 
{
	match_curv_getName qq(pos);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

const char * curv_getNameAt(int pos)
{
	if ((size_t)pos > surfit_curvs->size())
		return NULL;
	return (*surfit_curvs)[pos]->getName();
};

struct match_curv_getId
{
	match_curv_getId(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_curv * curv)
	{
		if ( StringMatch(pos, curv->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( curv->getId() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * curv_getId(const char * pos) 
{
	match_curv_getId qq(pos);
	qq = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), qq);
	return qq.res;
};

void curv_del(const char * pos) 
{
	if (surfit_curvs->size() == 0)
		return;
	size_t i;
	for (i = surfit_curvs->size()-1; i >= 0; i--)
	{
		d_curv * curv = (*surfit_curvs)[i];
		if ( StringMatch(pos, curv->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing curve \"%s\" from memory", curv->getName());
			curv->release();
			surfit_curvs->erase(surfit_curvs->begin()+i);
		}
		if (i == 0)
			break;
	}
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

boolvec * curv_to_cntr(REAL value, const char * pos) 
{
	boolvec * res = create_boolvec();
	size_t i;
	for (i = 0; i < surfit_curvs->size(); i++)
	{
		d_curv * curv = (*surfit_curvs)[i];
		if (StringMatch(pos, curv->getName()) == false)
			continue;
		writelog(LOG_MESSAGE,"converting curve \"%s\" to contour", curv->getName());
		d_cntr * cntr = create_cntr(curv, value, curv->getName());
		surfit_cntrs->push_back(cntr);
		res->push_back(true);
	}
	return res;
};

}; // namespace surfit;

