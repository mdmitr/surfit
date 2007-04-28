
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

#include "area.h"
#include "area_tcl.h"
#include "area_internal.h"
#include "variables_internal.h"
#include "free_elements.h"

#include <algorithm>

namespace surfit {

boolvec * area_read(const char * filename, const char * areaname,
               int col1, int col2,
               const char* delimiter, int skip_lines, int grow_by)
{

	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname != NULL) {

		d_area * area = _area_read(fname, areaname,
					   col1, col2, skip_lines, 
					   grow_by, delimiter);

		if (area != NULL) 
			surfit_areas->push_back(area);
		else {
			writelog(LOG_WARNING,"failed to read area from file %s", fname);
			res->push_back(false);
			fname = find_next();
			continue;
		}

		if (areaname == NULL)
		{
			char * name = get_name(fname);
			area->setName( name );
			sstuff_free_char(name);
		}
		
		res->push_back(true);
		fname = find_next();
		
	}

	find_close();
	return res;

};

boolvec * area_load(const char * filename, const char * areaname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname != NULL) {
		d_area * area = _area_load(fname, areaname);
		if (area) {
			surfit_areas->push_back(area);
			res->push_back(true);
		} else {
			res->push_back(false);
			fname = find_next();
			continue;
		}
		if (areaname == NULL)
		{
			char * name = get_name(fname);
			area->setName( name );
			sstuff_free_char(name);
		}
		
		fname = find_next();
	}

	find_close();
	return res;
};

struct match_area_write
{
	match_area_write(const char * ifilename, const char * ipos, const char * idelimiter) : filename(ifilename), pos(ipos), delimiter(idelimiter), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();

			char buf[80];
			strcpy( buf, "%lf" );
			strcat( buf, delimiter );
			strcat( buf, "%lf\n" );
			res->push_back( _area_write(area, filename, buf) );
		}
	}
	const char * filename;
	const char * pos;
	const char * delimiter;
	boolvec * res;
};

boolvec * area_write(const char * filename, const char * pos, const char * delimiter) 
{
	match_area_write qq(filename, pos, delimiter);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_save
{
	match_area_save(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			writelog(LOG_MESSAGE,"Saving area \"%s\" to file %s", area->getName(), filename);
			bool r = _area_save(area, filename);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(r);
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * area_save(const char * filename, const char * pos) 
{
	match_area_save qq(filename, pos);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_setName
{
	match_area_setName(const char * inew_name, const char * ipos) : new_name(inew_name), pos(ipos), res(NULL) {} ;
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			area->setName(new_name);
			res->push_back(true);
		}
	}
	const char * new_name;
	const char * pos;
	boolvec * res;
};

boolvec * area_setName(const char * new_name, const char * pos) 
{
	match_area_setName qq(new_name, pos);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct match_area_getName
{
	match_area_getName(const char * ipos) : pos(ipos), res(NULL) {} ;
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( area->getName() );
		}
	}
	const char * pos;
	strvec * res;
};

strvec * area_getName(const char * pos) 
{
	match_area_getName qq(pos);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

const char * area_getNameAt(int pos)
{
	if ((size_t)pos > surfit_areas->size())
		return NULL;
	return (*surfit_areas)[pos]->getName();
};

struct match_area_getId
{
	match_area_getId(const char * ipos) : pos(ipos), res(NULL) {} ;
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( area->getId() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * area_getId(const char * pos) 
{
	match_area_getId qq(pos);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

void area_del(const char * pos) 
{
	if (surfit_areas->size() == 0)
		return;
	size_t i;
	for (i = surfit_areas->size()-1; i >= 0; i--)
	{
		d_area * area = (*surfit_areas)[i];
		if ( StringMatch(pos, area->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing area \"%s\" from memory", area->getName());
			area->release();
			surfit_areas->erase(surfit_areas->begin()+i);
		}
		if (i == 0)
			break;
	}
};

struct match_area_invert
{
	match_area_invert(const char * ipos) : pos(ipos), res(NULL) {} ;
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			area->invert();
			res->push_back( true );
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * area_invert(const char * pos) 
{
	match_area_invert qq(pos);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

int area_size() {
	return surfit_areas->size();
};

void areas_info() {
	size_t areas_counter;
	for (areas_counter = 0; areas_counter < surfit_areas->size(); areas_counter++) {
		d_area * a_area = *(surfit_areas->begin()+areas_counter);
		_area_info(a_area);
	}
};

}; // namespace surfit;

