
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
#include "real.h"
#include "trends.h"
#include "trend.h"
#include "trend_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "trend_user.h"

namespace surfit {

bool trends_delall() {
	unsigned int i;

	if (surfit_trends->size() == 0) {
		//writelog(SURFIT_WARNING,"trends_delall : empty surfit_trends");
		return false;
	}
	
	for (i = 0; i < surfit_trends->size(); i++)
		_trend_unload( *(surfit_trends->begin()+i) );

	surfit_trends->resize(0);

	return true;
};

bool trends_unload(const char * name) {
	unsigned int i;

	if (surfit_trends->size() == 0) {
		writelog(SURFIT_WARNING,"trends_delall : empty surfit_trends");
		return false;
	}
	
	trend * a_func = NULL;
	for (i = 0; i < surfit_trends->size(); i++) {
		a_func = *(surfit_trends->begin()+i);
		if (a_func->getName()) {
			if ( strcmp(a_func->getName(),name) == 0 ) {
				return trends_del(i);
			}
		}
	}
	
	return false;
};

bool trends_del(int pos) {
	if ((int)surfit_trends->size() <= pos) {
		writelog(SURFIT_ERROR,"trends_del : wrong pos");
		return false;
	}

	_trend_unload(*(surfit_trends->begin()+pos));
	surfit_trends->erase(surfit_trends->begin()+pos);

	return true;
};

bool trends_load(const char * filename, const char * trendname) {
	trend * trend = _trend_load(filename, trendname, get_rw_mode());
	if (!trend)
		return false;

	surfit_trends->push_back(trend);
	return true;
};

bool trends_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname) {
	trend * trnd = _trend_load_grd(filename, D1, D2, trendname);
	if (!trnd)
		return false;

	surfit_trends->push_back(trnd);
	return true;
};

trend * trends_at(int pos) {
	if (pos <= (int)surfit_trends->size()) {
		writelog(SURFIT_ERROR,"trends_at : wrong pos");
		return NULL;
	}
	return *(surfit_trends->begin()+pos);
};

trend * trends_first() {
	if (surfit_trends->size() == 0) {
		writelog(SURFIT_ERROR,"trends_first : empty surfit_trends");
		return NULL;
	}
	return *surfit_trends->begin();
};

trend * trends_last() {
	if (surfit_trends->size() == 0) {
		writelog(SURFIT_ERROR,"trends_last : empty surfit_trends");
		return NULL;
	}
	return *(surfit_trends->end()-1);
};

int trends_info() {
	int max_priority = 0;
	if (surfit_trend) {
		_trend_info(surfit_trend);
		max_priority = MAX(max_priority, surfit_trend->get_priority());
	}

	unsigned int trends_counter;
	for (trends_counter = 0; trends_counter < surfit_trends->size(); trends_counter++) {
		trend * a_trend = *(surfit_trends->begin()+trends_counter);
		_trend_info(a_trend);
		max_priority = MAX(max_priority, a_trend->get_priority());
	}
	return max_priority;
};

int trends_size() {
	return surfit_trends->size();
};

}; // namespace surfit;

