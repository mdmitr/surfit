
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

#include "points.h"
#include "pnts_io.h"
#include "boolvec.h"
#include "findfile.h"

#include <algorithm>

namespace surfit {

boolvec * pnts_load_shp(const char * filename, const char * pntsname, const char * param) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname != NULL) {
		d_points * pnts = _pnts_load_shp(filename, pntsname, param);
		if (pnts) {
			surfit_pnts->push_back(pnts);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();
	}

	find_close();
	return res;
};

struct match_pnts_save_shp
{
	match_pnts_save_shp(const char * ifilename, const char * ipos) : pos(ipos), filename(ifilename), res(NULL) {};
	void operator()(d_points * pnts)
	{
		if ( StringMatch(pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			writelog(LOG_MESSAGE,"Saving points to ESRI shapefile format %s", filename);
			res->push_back( _pnts_save_shp(pnts, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * pnts_save_shp(const char * filename, const char * pos) 
{
	match_pnts_save_shp qq(filename, pos);
	qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
	return qq.res;
};

}; // namespace surfit;


