
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

#include "cntr.h"
#include "cntr_io.h"

#include "interp.h"
#include <tcl.h>
#include <algorithm>
#include <errno.h>

namespace surfit {

bool cntr_load_bln(const char * filename, const char * cntrname) {
	if (cntrname != NULL) {

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
		d_cntr * crv = _cntr_load_bln(file, orient);
		while (crv != NULL) {
			if (crv->getName() == NULL) {
				crv->release();
				crv = _cntr_load_bln(file, orient);
				continue;
			}
			if ( RegExpMatch(cntrname, crv->getName()) == false ) {
				crv->release();
				crv = _cntr_load_bln(file, orient);
				continue;
			}

			writelog(LOG_MESSAGE,"loading contour \"%s\" from Surfer BLN file %s", crv->getName(), filename);

			surfit_cntrs->push_back(crv);
			res = true;
			crv = _cntr_load_bln(file, orient);
			continue;
		}
		
		fclose(file);
		return res;
	}

	writelog(LOG_MESSAGE,"loading contours from BLN file %s", filename);

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
	d_cntr * crv = _cntr_load_bln(file, orient);
	while (crv != NULL) {
		res = true;
		surfit_cntrs->push_back(crv);
		crv = _cntr_load_bln(file, orient);
	}
	
	fclose(file);
	return res;
};

bool cntr_load_shp(const char * filename, const char * cntrname, const char * zfield) {
	return _cntr_load_shp(filename, cntrname, zfield);
};

struct regexp_cntr_save_shp
{
	regexp_cntr_save_shp(const char * ifilename, const char * icntr_pos)
	{
		filename = ifilename;
		cntr_pos = icntr_pos;
		res = true;
	}

	void operator()(d_cntr * crv)
	{
		if (res == false)
			return;

		if (crv->getName() == NULL)
			return;

		if ( RegExpMatch(cntr_pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"saving contour \"%s\" to ESRI shape file %s",
				 crv->getName()?crv->getName():"noname", filename);
			res = _cntr_save_shp(crv, filename);
		}
	};

	const char * filename;
	const char * cntr_pos;
	bool res;
};

bool cntr_save_shp(const char * filename, const char * cntr_pos) {
	regexp_cntr_save_shp saver(filename, cntr_pos);
	saver = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), saver);
	return saver.res;
};

struct regexp_cntr_save_bln
{
	regexp_cntr_save_bln(const char * ifilename, const char * icntr_pos, int iorient, FILE * ifile)
	{
		filename = ifilename;
		cntr_pos = icntr_pos;
		orient = iorient;
		res = true;
		file = ifile;
	}

	void operator()(d_cntr * crv)
	{
		if (res == false)
			return;

		if (crv->getName() == NULL)
			return;

		if ( RegExpMatch(cntr_pos, crv->getName()) )
		{
			writelog(LOG_MESSAGE,"saving contour \"%s\" to Surfer BLN file %s",
				 crv->getName()?crv->getName():"noname", filename);
			res = _cntr_save_bln(crv, file, orient);
		}
	};

	const char * filename;
	const char * cntr_pos;
	int orient;
	bool res;
	FILE * file;
};

bool cntr_save_bln(const char * filename, const char * cntr_pos, int orient) 
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

	regexp_cntr_save_bln saver(filename, cntr_pos, orient, file);
	saver = std::for_each(surfit_cntrs->begin(), surfit_cntrs->end(), saver);

	fclose(file);

	return saver.res;
};

}; // namespace surfit;


