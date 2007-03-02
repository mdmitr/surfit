
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

#include "interp.h"
#include <tcl.h>
#include <algorithm>

#include <errno.h>

namespace surfit {

bool curv_load_bln(const char * filename, const char * curvname) {

	if (curvname != NULL) {
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
			
			if ( StringMatch(curvname, crv->getName()) == false ) {
				crv->release();
				crv = _curv_load_bln(file, orient);
				continue;
			}
			writelog(LOG_MESSAGE,"loading curve \"%s\" from Surfer BLN file %s", crv->getName(), filename);
			surfit_curvs->push_back(crv);
			crv = _curv_load_bln(file, orient);
			res = true;
			continue;
		}
		
		fclose(file);
		return res;
	}
	
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
	return _curv_load_shp(filename, curvname);
};

struct regexp_curv_save_bln
{
	regexp_curv_save_bln(const char * ifilename, const char * icurv_pos, int iorient, FILE * ifile)
	{
		filename = ifilename;
		curv_pos = icurv_pos;
		orient = iorient;
		res = true;
		file = ifile;
	}

	void operator()(d_curv * crv)
	{
		if (res == false)
			return;

		if ( StringMatch(curv_pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"saving curve \"%s\" to Surfer BLN file %s",
				 crv->getName(), filename);
			res = _curv_save_bln(crv, file, orient);
		}
	};

	const char * filename;
	const char * curv_pos;
	int orient;
	bool res;
	FILE * file;
};

bool curv_save_bln(const char * filename, const char * curv_pos, int orient) 
{
	FILE * file = fopen(filename, "a");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "saving BLN: file error.");
		fclose(file);
		return false;
	}

	regexp_curv_save_bln saver(filename, curv_pos, orient, file);
	saver = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), saver);

	fclose(file);
	return saver.res;
};

struct regexp_curv_save_shp
{
	regexp_curv_save_shp(const char * ifilename, const char * icurv_pos)
	{
		filename = ifilename;
		curv_pos = icurv_pos;
		res = true;
	}

	void operator()(d_curv * crv)
	{
		if (res == false)
			return;

		if ( StringMatch(curv_pos, crv->getName()) )
		{
			res = _curv_save_shp(crv, filename);
		}
	};

	const char * filename;
	const char * curv_pos;
	bool res;
};


bool curv_save_shp(const char * filename, const char * curv_pos) {
	regexp_curv_save_shp saver(filename, curv_pos);
	saver = std::for_each(surfit_curvs->begin(), surfit_curvs->end(), saver);
	return saver.res;
};



}; // namespace surfit;


