
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

#include "flow_ie.h"
#include "flow_data_manager.h"

#include "datafile.h"
#include "flow_variables.h"

namespace surfit {

void freeflow_manager::release() {
	clear_rules();
	clear_data();
	delete this;
};

int freeflow_manager::load_tag(datafile * df, char * tagname) const {
		
	return 0;
}

bool freeflow_manager::save(datafile *df) const {

	return true;

};

void freeflow_manager::clear_data() const {
	
};

#define FREEFLOW_TYPES "freeflow \n"

char * freeflow_manager::types_info() const {
	return (char*)FREEFLOW_TYPES;
};

void freeflow_manager::mem_info() const {

};

#ifdef HAVE_GL_WORKS
void freeflow_manager::mem_show() const {

};

bool freeflow_manager::check_for_drawing(const char * type) const {

	return false;

};

#endif

int freeflow_manager::data_count() const {
	int res = 0;
	
	return res;
};

const data * freeflow_manager::data_get(int i) const {
	
	return NULL;
};

bool freeflow_manager::auto_load(const char * filename, const char * first1024, int readed) const
{
	return false;
};

}; // namespace surfit;

