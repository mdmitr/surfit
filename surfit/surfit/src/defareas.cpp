
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
#include "defareas.h"
#include "defarea.h"
#include "defarea_internal.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "defarea_user.h"

namespace surfit {

bool defareas_delall() {
	unsigned int i;

	if (surfit_defareas->size() == 0) {
		//writelog(SURFIT_WARNING,"defareas_delall : empty surfit_defareas");
		return false;
	}
	
	for (i = 0; i < surfit_defareas->size(); i++)
		_defarea_unload( *(surfit_defareas->begin()+i) );

	surfit_defareas->resize(0);

	return true;
};

bool defareas_del(int pos) {
	if ((int)surfit_defareas->size() <= pos) {
		writelog(SURFIT_ERROR,"defareas_del : wrong pos");
		return false;
	}

	_defarea_unload(*(surfit_defareas->begin()+pos));
	surfit_defareas->erase(surfit_defareas->begin()+pos);

	return true;
};

bool defareas_load(const char * filename, const char * defareaname) {
	defarea * defarea = _defarea_load(filename, defareaname, get_rw_mode());
	if (!defarea)
		return false;

	surfit_defareas->push_back(defarea);
	return true;
};

bool defareas_load_grd(const char * filename, const char * defareaname) {
	defarea * defarea = _defarea_load_grd(filename, defareaname);
	if (!defarea)
		return false;

	surfit_defareas->push_back(defarea);
	return true;
};

defarea * defareas_at(int pos) {
	if (pos <= (int)surfit_defareas->size()) {
		writelog(SURFIT_ERROR,"defareas_at : wrong pos");
		return NULL;
	}
	return *(surfit_defareas->begin()+pos);
};

defarea * defareas_first() {
	if (surfit_defareas->size() == 0) {
		writelog(SURFIT_ERROR,"defareas_first : empty surfit_defareas");
		return NULL;
	}
	return *surfit_defareas->begin();
};

defarea * defareas_last() {
	if (surfit_defareas->size() == 0) {
		writelog(SURFIT_ERROR,"defareas_last : empty surfit_defareas");
		return NULL;
	}
	return *(surfit_defareas->end()-1);
};

int defareas_info() {
	int max_priority = 0;
	if (surfit_defarea) {
		_defarea_info(surfit_defarea);
		max_priority = MAX(max_priority, surfit_defarea->get_priority());
	}
	
	if (surfit_defareas->size() > 0) {
		unsigned int defarea_cnt;
		for (defarea_cnt = 0; defarea_cnt < surfit_defareas->size(); defarea_cnt++) {
			defarea * a_fnc = *(surfit_defareas->begin()+defarea_cnt);
			if (a_fnc) {
				_defarea_info(a_fnc);
				max_priority = MAX(max_priority, a_fnc->get_priority());
			}
		}
	}
	return max_priority;
};

int defareas_size() {
	return surfit_defareas->size();
};

bool defareas_unload(const char * name) {
	unsigned int i;

	if (surfit_defareas->size() == 0) {
		writelog(SURFIT_WARNING,"defareas_delall : empty surfit_defareas");
		return false;
	}
	
	defarea * fnc = NULL;
	for (i = 0; i < surfit_defareas->size(); i++) {
		fnc = *(surfit_defareas->begin()+i);
		if (fnc->getName()) {
			if ( strcmp(fnc->getName(),name) == 0 ) {
				return defareas_del(i);
			}
		}
	}
	
	return false;
};


}; // namespace surfit;

