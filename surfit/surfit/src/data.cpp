
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "ie.h"
#include "data.h"
#include "variables_tcl.h"

#include <string.h>

namespace surfit {

data::data() {
	priority = surfit::priority;
	name = NULL;
};

data::~data() {
	free(name);
};

void data::set_priority(int prior) {
	priority = prior;
};

int data::get_priority() const {
	return priority;
};

void data::setName(const char * newname) {
	if (!newname)
		return;
	if (name) {
		free(name);
		name = NULL;
	}

	name = (char *)malloc(strlen(newname) + 1);
	strcpy(name, newname);
};

const char * data::getName() const {
	return name;
};

}; // namespace surfit;

