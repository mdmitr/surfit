
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

#include "boolvec.h"
#include "findfile.h"

#include "area.h"
#include "area_io.h"

#include <algorithm>

namespace surfit {

boolvec * area_load_bln(const char * filename, const char * areaname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_area * area = _area_load_bln(fname, areaname);
		if (area)
			surfit_areas->push_back(area);
		res->push_back( area != NULL );
		fname = find_next();	
	}
	find_close();
	return res;
};

boolvec * area_load_shp(const char * filename, const char * areaname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		res->push_back(_area_load_shp(fname, areaname));
		fname = find_next();	
	}
	find_close();
	return res;
};

struct save_oper
{
	virtual bool do_oper(const char * filename, d_area * area) = 0;
};

struct match_area_save
{
	match_area_save(const char * ifilename, const char * ipos, save_oper * ioper) 
		: filename(ifilename), pos(ipos), oper(ioper), res(NULL) {};
	void operator()(d_area * area)
	{
		if ( StringMatch(pos, area->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(filename, area) );
		}
	}
	const char * filename;
	const char * pos;
	save_oper * oper;
	boolvec * res;
};

struct oper_save_bln : save_oper
{
	virtual bool do_oper(const char * filename, d_area * area)
	{
		if (area == NULL)
			return false;

		bool res = _area_save_bln(area, filename);
		return res;
	}
};

boolvec * area_save_bln(const char * filename, const char * area_pos) 
{
	oper_save_bln oper;
	match_area_save qq(filename, area_pos, &oper);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

struct oper_save_shp : save_oper
{
	virtual bool do_oper(const char * filename, d_area * area)
	{
		if (area == NULL)
			return false;

		bool res = _area_save_shp(area, filename);
		return res;
	}
};

boolvec * area_save_shp(const char * filename, const char * area_pos) 
{
	oper_save_shp oper;
	match_area_save qq(filename, area_pos, &oper);
	qq = std::for_each(surfit_areas->begin(), surfit_areas->end(), qq);
	return qq.res;
};

}; // namespace surfit;


