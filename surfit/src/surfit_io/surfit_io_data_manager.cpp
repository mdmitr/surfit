
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
#include "surfit_io_data_manager.h"
#include "variables.h"
#include "fileio.h"
#include "surf_io_tcl.h"
#include "pnts_io_tcl.h"
#include "curv_io_tcl.h"
#include "cntr_io_tcl.h"
#include "area_io_tcl.h"

#include "sstuff.h"

#include "shapelib/shapefil.h"

#include "free_elements.h"

namespace surfit {

void surfit_io_manager::release() {
	clear_rules();
	clear_data();
	delete this;
};

bool load_ESRI_shape(const char * filename, const char * name) {
	SHPHandle hSHP = SHPOpen(filename, "rb");
	if( hSHP == NULL )
		return false;
	int shpType;
	SHPGetInfo(hSHP, NULL, &shpType, NULL, NULL);
	SHPClose( hSHP );

	switch (shpType) {
	case SHPT_POINT:
		return pnts_load_shp(filename, name);
	case SHPT_ARC:
		return curv_load_shp(filename);
	case SHPT_POLYGON:
		return area_load_shp(filename);
	case SHPT_POLYGONZ:
		return cntr_load_shp(filename);
	default:
		return false;
	}
};

bool surfit_io_manager::auto_load(const char * filename, const char * first1024, int readed) const
{
	
	char * ext = get_ext(filename);
	char * uext = strdup(ext);
	str_toupper(uext);
	char * name = get_name(filename);
	char * uname = strdup(name);
	str_toupper(uname);

	bool res = false;

	int columns = calc_columns(first1024, readed, " \t");

	if (columns == 3) {
		res = surf_load_xyz(filename, name);
		goto exit;
	}

	if (ext != NULL) {
		if (strcmp( uext, ".BLN" ) == 0) {
			res = cntr_load_bln(filename);
			if (res)
				goto exit;
			res = curv_load_bln(filename);
			if (res)
				goto exit;
			res = area_load_bln(filename, name);
			goto exit;
		}
		if (strcmp( uext, ".JPG" ) == 0) {
			res = surf_load_jpg(filename, name);
			goto exit;
		}
		if (strcmp( uext, ".BMP" ) == 0) {
			res = surf_load_bmp(filename, name);
			goto exit;
		}
		if (strcmp( uext, ".XYZ" ) == 0) {
			res = surf_load_xyz(filename, name);
			goto exit;
		}
	}

	if ( strncmp(first1024,"\0x00\0x00\0x27\0x0A",4) == 0 ) {
		try {
			res = load_ESRI_shape(filename, name);
		} catch (...) {
			goto exit;
		}
		goto exit;
	}

	if ( strncmp(first1024, "CDF", 3) == 0 ) {
		try {
			res = surf_load_gmt(filename);
		} catch (...) {
			goto exit;
		}
		goto exit;
	}
	
	if ( strncmp(first1024,"DSAA",4) == 0 ) {
		try {
			res = surf_load_grd(filename);
		} catch (...) {
			goto exit;
		}
		goto exit;
	}

	if ( strncmp(first1024,"north:",6) == 0 ) {
		try {
			res = surf_load_grass(filename);
		} catch (...) {
			goto exit;
		}
		goto exit;
	}
	if ( strncmp(first1024,"ncols ",6) == 0 ) {
		try {
			res = surf_load_arcgis(filename);
		} catch (...) {
			goto exit;
		}
		goto exit;
	}

exit:
	free(uext);
	free(uname);
	sstuff_free_char(ext);
	sstuff_free_char(name);
	return res;
};

}; // namespace surfit;

