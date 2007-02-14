
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
#include "surfit_data.h"
#include "variables_tcl.h"
#include "variables.h"
#include "functional.h"

#include <string.h>

namespace surfit {

static int noname_counter = 0;

data::data(const char * itype) {
	name = NULL;
	type = strdup(itype);
};

data::~data() {
	free(name);
	free(type);
};

void data::setName(const char * newname) {
	if (!newname) {
		name = (char*)malloc(6+20);
		sprintf(name, "noname%d", noname_counter);
		noname_counter++;
		return;
	}
	if (name) {
		if (name == newname)
			return;
		free(name);
		name = NULL;
	}

	name = (char *)malloc(strlen(newname) + 1);
	strcpy(name, newname);
};

void data::setType(const char * newtype) {
	if (!newtype)
		return;
	if (type) {
		if (type == newtype)
			return;
		free(type);
		type = NULL;
	}

	type = (char *)malloc(strlen(newtype) + 1);
	strcpy(type, newtype);
};

const char * data::getName() const {
	return name;
};

const char * data::getType() const {
	return type;
};

void data::release() {

	int i, j;
	if (functionals) {
		for (i = functionals->size()-1; i >= 0; i--) {
			functional * f = (*functionals)[i];
			if (f == NULL)
				continue;
			int max_data = f->get_data_count();
			for (j = 0; j < max_data; j++) {
				const data * d = f->get_data(j);
				if (d == this) {
					if (f->getName())
						writelog(LOG_WARNING,"Removing functional %s from memory", f->getName());
					std::vector<functional *>::iterator it = functionals->begin()+i;
					functionals->erase(it);
					f->release();
					break;
				}
			}
		}
	}

	release_private();
};

void data::release_private() {

	delete this;

};

}; // namespace surfit;

