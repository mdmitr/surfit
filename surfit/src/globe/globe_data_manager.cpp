
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

#include "globe_ie.h"
#include "globe_data_manager.h"
#include "variables.h"

#include "sstuff.h"

#include "dem.h"
#include "dem_internal.h"
#include "dem_tcl.h"
#include "datafile.h"
#include "free_elements.h"

namespace surfit {

void globe_manager::release() {
	clear_rules();
	clear_data();
	delete this;
};

int globe_manager::load_tag(datafile * df, char * tagname) const {
		
	if (strcmp(tagname, "dem") == 0) {
		
		d_dem * res = _dem_load_df(df, NULL);
		
		if (res) {
			globe_dems->push_back(res);
		}
		
		if ( !df->readTagName(tagname) )
			return -1;
		
		return 1;
	}
			
	return 0;
}

bool globe_manager::save(datafile *df) const {

	size_t cnt;

	for (cnt = 0; cnt < globe_dems->size(); cnt++) {
		d_dem * fnc = *(globe_dems->begin()+cnt);
		if (!_dem_save_df(fnc, df))
			return false;
	}

	return true;

};

void globe_manager::clear_data() const {
	
	dem_delall();
	
};

#define GLOBE_TYPES "globe dem\n"

char * globe_manager::types_info() const {
	return GLOBE_TYPES;
};


void globe_manager::mem_info() const {
	
	dems_info();
	
};

int globe_manager::data_count() const {
	int res = 0;

	res += globe_dems->size();

	return res;
};

const data * globe_manager::data_get(int i) const {
	
	int res = 0;
	int sum = 0;

	res = globe_dems->size();
	if (res + sum > i)
		return (*globe_dems)[i-sum];
	sum += res;

	return NULL;
};

bool globe_manager::auto_load(const char * filename, const char * first1024, int readed) const
{
	
	char * ext = get_ext(filename);
	char * uext = strdup(ext);
	str_toupper(uext);
	char * name = get_name(filename);
	char * uname = strdup(name);
	str_toupper(uname);

	bool res = false;

	if (ext != NULL) {
		if (strcmp( uext, ".HDR" ) == 0) {
			res = dem_load_dtm(filename, strdup(name));
			goto exit;
		}
		if (strcmp( uext, ".HGT" ) == 0) {
			res = dem_load_hgt(filename, strdup(name));
			goto exit;
		}
		if (strcmp( uext, ".ZIP" ) == 0) {
			sstuff_free_char(ext);
			ext = get_full_ext(filename);				
			if (strcmp(ext, ".hgt.zip") == 0) {
				char * name2 = get_name(name);
				res = dem_load_hgt_zip(filename, strdup(name2));
				sstuff_free_char(name2);
				goto exit;
			}
		}
	}
	if (name != NULL) {
		if (strlen(name) == 4) {
			if (strcmp( uname+1, "10G") == 0) {
				res = dem_load_globe(filename);
				goto exit;
			}
		}
	}

exit:
	free(uext);
	free(uname);
	sstuff_free_char(ext);
	sstuff_free_char(name);
	return res;
};

}; // namespace surfit;

